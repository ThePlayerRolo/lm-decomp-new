#include <JSystem/JUtility/JUTException.hpp>
#include <JSystem/JUtility/JUTConsole.hpp>
#include <JSystem/JUtility/JUTDirectFile.hpp>
#include <JSystem/JUtility/JUTDirectPrint.hpp>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include <dolphin/os/OSError.h>
#include <dolphin/gx.h>
#include <dolphin/os.h>
#include <dolphin/vi.h>
#include <dolphin/base/PPCArch.h>
#include <macros.h>

struct CallbackObject {
	/* 0x00 */ OSErrorHandler callback;
	/* 0x04 */ u16 error;
	/* 0x06 */ u16 pad_0x06;
	/* 0x08 */ OSContext* context;
	/* 0x0C */ int param_3;
	/* 0x10 */ int param_4;
};

void search_name_part(u8*, u8*, int);

u32 dummy1[4] = { 0, 0, 0, 0 };

OSMessageQueue JUTException::sMessageQueue = {};
const char* JUTException::sCpuExpName[]    = {
    "SYSTEM RESET",
    "MACHINE CHECK",
    "DSI",
    "ISI",
    "EXTERNAL INTERRUPT",
    "ALIGNMENT",
    "PROGRAM",
    "FLOATING POINT",
    "DECREMENTER",
    "SYSTEM CALL",
    "TRACE",
    "PERFORMACE MONITOR",
    "BREAK POINT",
    "SYSTEM INTERRUPT",
    "THERMAL INTERRUPT",
};
JUTException* JUTException::sErrorManager;
OSErrorHandler JUTException::sPreUserCallback;
OSErrorHandler JUTException::sPostUserCallback;

JUTException* JUTException::create(JUTDirectPrint* directPrint)
{
	if (!sErrorManager) {
		JKRHeap* systemHeap = JKRGetSystemHeap();
		sErrorManager       = new (systemHeap, 4) JUTException(directPrint);
		sErrorManager->resume();
	}

	return sErrorManager;
}

OSMessage JUTException::sMessageBuffer[1] = { 0 };

void* JUTException::run()
{
	OSInitMessageQueue(&sMessageQueue, nullptr, 4);
	OSMessage message;
	while (true) {
		OSReceiveMessage(&sMessageQueue, &message, OS_MESSAGE_BLOCK);
		CallbackObject* cb      = (CallbackObject*)message;
		OSErrorHandler callback = cb->callback;
		u16 error               = cb->error;
		OSContext* context      = cb->context;
		int r24                 = cb->param_3;
		int r23                 = cb->param_4;

		if (!sErrorManager->mDirectPrint->getFrameBuffer()) {
			sErrorManager->createFB();
		}
		if (callback) {
			callback(error, context, r24, r23);
		}
		sErrorManager->printContext(error, context, r24, r23);
	}
}

JUTException::JUTException(JUTDirectPrint* directPrint)
    : JKRThread(0x4000, 0x10, 0)
{
	mDirectPrint = directPrint;
	OSSetErrorHandler(__OS_EXCEPTION_DSI, (OSErrorHandler)errorHandler);
	OSSetErrorHandler(__OS_EXCEPTION_ISI, (OSErrorHandler)errorHandler);
	OSSetErrorHandler(__OS_EXCEPTION_PROGRAM, (OSErrorHandler)errorHandler);
	OSSetErrorHandler(__OS_EXCEPTION_FLOATING_POINT, (OSErrorHandler)errorHandler);
	OSSetErrorHandler(__OS_EXCEPTION_ALIGNMENT,
	                  (OSErrorHandler)errorHandler);

	sPreUserCallback  = nullptr;
}

static CallbackObject exCallbackObject;
void* JUTException::sConsoleBuffer;
u32 JUTException::sConsoleBufferSize;
JUTConsole* JUTException::sConsole;
u32 JUTException::msr;
u32 JUTException::fpscr;

void JUTException::errorHandler(OSError error, OSContext* context, u32 param_3,
                                u32 param_4)
{
	msr   = PPCMfmsr();
    PPCMtmsr(msr | 0x2000);
    setFpscr(fpscr);
	OSFillFPUContext(context);
	OSSetErrorHandler(error, nullptr);

	exCallbackObject.callback = sPreUserCallback;
	exCallbackObject.error    = error;
	exCallbackObject.context  = context;
	exCallbackObject.param_3  = param_3;
	exCallbackObject.param_4  = param_4;

	OSSendMessage(&sMessageQueue, &exCallbackObject, OS_MESSAGE_BLOCK);
}

void JUTException::showFloatSub(u16 position_x, u16 position_y, int index, f32 value)
{
	if (isnan(value)) {
		mDirectPrint->drawString_f(position_x, position_y, "F%02d: Nan", index);
	} else if (isinf(value)) {
		if (*((u8*)&value) & 0x80) {
			mDirectPrint->drawString_f(position_x, position_y, "F%02d:+Inf", index);
		} else {
			mDirectPrint->drawString_f(position_x, position_y, "F%02d:-Inf", index);
		}
	} else if (value == 0.0f) {
		mDirectPrint->drawString_f(position_x, position_y, "F%02d: 0.0", index);
	} else {
		mDirectPrint->drawString_f(position_x, position_y, "F%02d:%+.3E", index, value);
	}
}

void JUTException::showFloat(OSContext* context)
{

    mDirectPrint->erase(25, 75, 270, 130);
    int height;

	for (int i = 0, height = 80; i < 10; i++) {
        u16 height_2 = height;
		showFloatSub(26, height_2, i, context->fpr[i]);
		showFloatSub(117, height_2, i + 11, context->fpr[i + 11]);
		showFloatSub(208, height_2, i + 22, context->fpr[i + 22]);
        height += 10;
	}
	showFloatSub(26, 180, 10, context->fpr[10]);
	showFloatSub(117, 180, 21, context->fpr[21]);
}

bool JUTException::searchPartialModule(u32 address, u32* module_id,
                                       u32* section_id, u32* section_offset,
                                       u32* name_offset)
{
	if (!address) {
		return false;
	}

	OSModuleInfo* module = *(OSModuleInfo**)0x800030C8;
	for (; module != nullptr; module = (OSModuleInfo*)module->link.next) {
		OSSectionInfo* section = (OSSectionInfo*)module->sectionInfoOffset;
		for (u32 i = 0; i < module->numSections; section++, i++) {
			if (section->size != 0) {
				u32 addr = section->offset & ~0x01;
				if ((addr <= address) && (address < addr + section->size)) {
					if (module_id)
						*module_id = module->id;
					if (section_id)
						*section_id = i;
					if (section_offset)
						*section_offset = address - addr;
					if (name_offset)
						*name_offset = module->nameOffset;
					return true;
				}
			}
		}
	}

	return false;
}

void search_name_part(u8* src, u8* dst, int dst_length)
{
	for (u8* p = src; *p; p++) {
		if (*p == '\\') {
			src = p;
		}
	}

	if (*src == '\\') {
		src++;
	}

	for (int i = 0; (*src != 0) && (i < dst_length);) {
		if (*src == '.')
			break;
		*dst++ = *src++;
		i++;
	}

	*dst = '\0';
}

void JUTException::showStack(OSContext* context)
{
	u32 i;
	u32* stackPointer;

    mDirectPrint->erase(0x19, 0x19, 0x10e, 0xb4);
	mDirectPrint->drawString_f(54,25, "Address:      Back Chain    LR Save\n");

	for (i = 0, stackPointer = (u32*)context->gpr[1]; (stackPointer != nullptr) && 
		(stackPointer != (u32*)0xFFFFFFFF) && (i++ < 0x10);) {
        mDirectPrint->drawString_f(0x2E, i * 10 + 33, "0x%08x:   0x%08x    0x%08x\n", stackPointer,
		                  stackPointer[0], stackPointer[1]);
	}
}

void JUTException::showMainInfo(s32 page, u16 error, OSContext* pContext, u32 dsisr, u32 dar) {
    switch (page) {
		case 1:
			mDirectPrint->erase(25, 20, 270, 54);
            mDirectPrint->drawString_f(30, 25, "CONTEXT:%08X  (%s EXCEPTION)", pContext, sCpuExpName[error]);
            mDirectPrint->drawString_f(30, 40, " SRR0:%08X  SRR1:%08X", pContext->srr0, pContext->srr1);
            mDirectPrint->drawString_f(30, 50, "DSISR:%08X   DAR:%08X", dsisr, dar);
			showGPR(pContext);
			break;
        case 2:
            mDirectPrint->erase(25, 20, 270, 54);
            mDirectPrint->drawString_f(30, 25, "CONTEXT:%08X  (%s EXCEPTION)", pContext, sCpuExpName[error]);
            mDirectPrint->drawString_f(30, 40, " SRR0:%08X  SRR1:%08X", pContext->srr0, pContext->srr1);
            mDirectPrint->drawString_f(30, 50, "DSISR:%08X   DAR:%08X", dsisr, dar);
            showFloat(pContext);
			mDirectPrint->drawString_f(30, 50, " MSR:%08XH   FPSCR:%08XH", msr, &fpscr);
			break;
		case 3:
			showStack(pContext);
			break;
    }
}

void JUTException::showGPR(OSContext* context) {
    mDirectPrint->erase(25, 75, 270, 130);

	for (int i = 0; i < 10; i++) {
		mDirectPrint->drawString_f(30, i * 10 + 80, "R%02d:%08XH  R%02d:%08XH  R%02d:%08XH", i,
		    context->gpr[i], i + 11, context->gpr[i + 11], i + 22, context->gpr[i + 22]);
	}
	mDirectPrint->drawString_f(30, 180, "R%02d:%08XH  R%02d:%08XH", 10, context->gpr[10], 21,
	                  context->gpr[21]);
    mDirectPrint->drawString_f(30, 190, " LR:%08XH   CR:%08XH", context->lr, context->cr);
}

void JUTException::showGPRMap(OSContext* context)
{
	if (!sConsole) {
		return;
	}

	bool found_address_register = false;

	for (int i = 0; i < 31; i++) {
		u32 address = context->gpr[i];

		if (address >= 0x80000000 && 0x83000000 - 1 >= address) {
			found_address_register = true;

			//sConsole->print_f("R%02d: %08XH", i, address);
			JUTConsoleManager::sManager->drawDirect(true);
			//waitTime(mPrintWaitTime1);
		}
	}

	if (!found_address_register) {
	}
}

void JUTException::printDebugInfo(JUTException::EInfoPage page, OSError error,
                                  OSContext* context, u32 param_3, u32 param_4)
{
	switch (page) {
	case EINFO_PAGE_GPR:
		return showGPR(context);
	case EINFO_PAGE_FLOAT:
		showFloat(context);
		if (sConsole) {
			sConsole->print_f(" MSR:%08XH   FPSCR:%08XH", msr, fpscr);
		}
		break;
	case EINFO_PAGE_STACK:
		return showStack(context);
	case EINFO_PAGE_GPR_MAP:
		return showGPRMap(context);
	}
}



void JUTException::printContext(OSError error, OSContext* context, u32 dsisr,
                                u32 dar)
{
	if (!sErrorManager->mDirectPrint->isActive()) {
		return;
	}

    mDirectPrint->erase(25, 20, 270, 54);
    showMainInfo(0, error, context, dsisr, dar);
}

void JUTException::waitTime(s32 timeout_ms)
{
	OSTime start_time = OSGetTime();
	OSTime ms;
	do {
		OSTime ticks = OSGetTime() - start_time;
		ms           = ticks / (OS_TIMER_CLOCK / 1000);
	} while (ms < timeout_ms);
}

void JUTException::createFB()
{
	GXRenderModeObj* renderMode = &GXNtsc480Int;

	void* end = OSGetArenaHi();
	u32 size  = (u16)ALIGN_NEXT((u16)renderMode->fbWidth, 16)
	           * renderMode->xfbHeight * 2;

	void* begin  = (void*)ALIGN_PREV((u32)end - size, 32);
	void* object = (void*)ALIGN_PREV((s32)begin - sizeof(JUTExternalFB), 32);
	new ((JUTExternalFB*)object)
	    JUTExternalFB(renderMode, GX_GM_1_7, begin, size);

	mDirectPrint->changeFrameBuffer(object);
	VIConfigure(renderMode);
	VISetNextFrameBuffer(begin);
	VISetBlack(FALSE);
	VIFlush();
}

// TODO: this looks very asm-y but peephole is still on after
// it so maybe not? IDK!
asm u32 JUTException::getFpscr() {
#ifdef __MWERKS__ // clang-format off
  stwu  r1, -0x10(r1)

  // Enable the "floating-point available" flag just in case?
  mfmsr r5
  ori   r5, r5, 0x2000
  mtmsr r5

  isync

  // Get contents of the "floating point status and control register"
  mffs f1
  stfd f1, 0x8(r1)
  lwz  r3, 0xc(r1)

  addi r1, r1, 0x10
#endif // clang-format on
}

asm void JUTException::setFpscr(u32 fpscr) {
#ifdef __MWERKS__ // clang-format off
    nofralloc
    mffs f1
    stfd f1, 0x0(r3)
    blr
#endif // clang-format on
}

#pragma peephole on

OSErrorHandler JUTException::setPreUserCallback(OSErrorHandler callback)
{
	OSErrorHandler previous = sPreUserCallback;
	sPreUserCallback        = callback;
	return previous;
}

void JUTException::appendMapFile(char* path)
{
	if (!path) {
		return;
	}

	for (JSUListIterator<JUTExMapFile> iterator = sMapFileList.getFirst();
	     iterator != sMapFileList.getEnd(); iterator++) {
		if (strcmp(path, iterator->mPath) == 0) {
			return;
		}
	}

	JUTExMapFile* mapFile = new JUTExMapFile(path);
	sMapFileList.append(&mapFile->mLink);
}

bool JUTException::queryMapAddress(char* mapPath, u32 address, s32 section_id,
                                   u32* out_addr, u32* out_size, char* out_line,
                                   u32 line_length, bool print,
                                   bool begin_with_newline)
{
	if (mapPath) {
		char buffer[80];
		strcpy(buffer, mapPath);
		strcat(buffer, ".map");
		if (queryMapAddress_single(buffer, address, section_id, out_addr,
		                           out_size, out_line, line_length, print,
		                           begin_with_newline)
		    == true) {
			return true;
		}
	} else if (sMapFileList.getFirst() != sMapFileList.getEnd()) {
		if (queryMapAddress_single(sMapFileList.getFirst()->getObject()->mPath,
		                           address, -1, out_addr, out_size, out_line,
		                           line_length, print, begin_with_newline)
		    == true) {
			return true;
		}
	}

	return false;
}

bool JUTException::queryMapAddress_single(char* mapPath, u32 address,
                                          s32 section_id, u32* out_addr,
                                          u32* out_size, char* out_line,
                                          u32 line_length, bool print,
                                          bool begin_with_newline)
{
	if (!mapPath)
		return false;

	JUTDirectFile file;
	char buffer[0x200];
	char section_name[16];
	int section_idx = 0;
	if (!file.fopen(mapPath))
		return false;

	bool result = false;
	bool found_section;

	while (true) {
		section_idx++;
		found_section = false;

		while (true) {
			int i;
			char* src;

			if (file.fgets(buffer, ARRAY_COUNT(buffer)) < 0)
				break;
			if (buffer[0] != '.')
				continue;

			i   = 0;
			src = buffer + 1;
			while (*src != '\0') {
				section_name[i] = *src;
				if (*src == ' ' || i == 0xf)
					break;
				i++;
				src++;
			}

			section_name[i] = 0;
			if (*src == 0)
				break;

			if (src[1] == 's' && src[2] == 'e' && src[3] == 'c'
			    && src[4] == 't') {
				found_section = true;
				break;
			}
		}

		if (!found_section)
			break;

		if (section_id >= 0 && section_id != section_idx)
			continue;

		int length;

		while (true) {
			if ((length = file.fgets(buffer, ARRAY_COUNT(buffer))) <= 4)
				break;
			if ((length < 28))
				continue;
			if (buffer[28] != '4')
				continue;

			u32 addr
			    = ((buffer[18] - '0') << 28) | strtol(buffer + 19, nullptr, 16);
			int size = strtol(buffer + 11, nullptr, 16);
			if ((addr <= address && address < addr + size)) {
				if (out_addr)
					*out_addr = addr;

				if (out_size)
					*out_size = size;

				if (out_line) {
					const u8* src = (const u8*)&buffer[0x1e];
					u8* dst       = (u8*)out_line;
					u32 i         = 0;

					for (i = 0; i < line_length - 1; ++src) {
						if (*src < (u32)' ' && *src != (u32)'\t')
							break;
						if ((*src == ' ' || *src == (u32)'\t') && (i != 0)) {
							if (dst[-1] != ' ') {
								*dst = ' ';
								dst++;
								++i;
							}
						} else {
							*dst++ = *src;
							i++;
						}
					}
					if (i != 0 && dst[-1] == ' ') {
						dst--;
						i--;
					}
					(void)*src;
					*dst = 0;
					if (print) {
						if (begin_with_newline) {
							sConsole->print("\n");
						}
						begin_with_newline = false;
					}
				}
				result = true;
				break;
			}
		}

		if ((section_id >= 0 && section_id == section_idx)) {
			if (print && begin_with_newline) {
				sConsole->print("\n");
			}
			break;
		}
	}

	file.fclose();
	return result ? true : false;
}


JUTExternalFB::JUTExternalFB(GXRenderModeObj* renderMode, GXGamma gamma,
                             void* buffer, u32 size)
{
	mRenderMode = renderMode;
	mSize       = size;
	field_0x0C  = 1;
	mGamma      = gamma;
	field_0x10  = false;
}
