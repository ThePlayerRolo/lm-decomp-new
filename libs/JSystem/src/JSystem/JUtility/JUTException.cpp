#include <JSystem/JUtility/JUTException.hpp>
#include <JSystem/JUtility/JUTDirectPrint.hpp>
#include <math.h>

#include <dolphin/gx.h>
#include <dolphin/os.h>
#include <dolphin/vi.h>
#include <dolphin/os/OSContext.h>
#include <dolphin/os/OSError.h>
#include <dolphin/base/PPCArch.h>
#include <macros.h>

typedef void (*JUTErrorHandler)(OSError, OSContext*, u32, u32);

struct CallbackObject {
	/* 0x00 */ JUTErrorHandler callback;
	/* 0x04 */ OSError error;
	/* 0x08 */ OSContext* context;
	/* 0x0C */ u32 dsisr;
	/* 0x10 */ u32 dar;
};

OSMessage JUTException::sMessageBuffer[4] = { nullptr, nullptr, nullptr, nullptr };

OSMessageQueue JUTException::sMessageQueue = {};
const char* JUTException::sCpuExpName[] = {
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
static CallbackObject exCallbackObject;
u32 JUTException::msr;
f64 JUTException::fpscr;

JUTException* JUTException::create(JUTDirectPrint* pDirectPrint) {
	if (!sErrorManager) {
		JKRHeap* systemHeap = JKRGetSystemHeap();
		sErrorManager = new (systemHeap, 4) JUTException(pDirectPrint);
		sErrorManager->resume();
	}

	return sErrorManager;
}

void* JUTException::run() {
	OSInitMessageQueue(&sMessageQueue, sMessageBuffer, 4);
	OSMessage message;
	while (true) {
		OSReceiveMessage(&sMessageQueue, &message, OS_MESSAGE_BLOCK);
		CallbackObject* cb = (CallbackObject*)message;
		JUTErrorHandler callback = cb->callback;
		OSError error = cb->error;
		OSContext* context = cb->context;
		u32 dsisr = cb->dsisr;
		u32 dar = cb->dar;

		if (!sErrorManager->mDirectPrint->getFrameBuffer()) {
			sErrorManager->createFB();
		}
		if (callback) {
			callback(error, context, dsisr, dar);
		}
		sErrorManager->printContext(error, context, dsisr, dar);
	}
}

JUTException::JUTException(JUTDirectPrint* pDirectPrint)
    : JKRThread(0x4000, 0x10, 0) {

	mDirectPrint = pDirectPrint;
	OSSetErrorHandler(__OS_EXCEPTION_DSI, (OSErrorHandler)errorHandler);
	OSSetErrorHandler(__OS_EXCEPTION_ISI, (OSErrorHandler)errorHandler);
	OSSetErrorHandler(__OS_EXCEPTION_PROGRAM, (OSErrorHandler)errorHandler);
	OSSetErrorHandler(__OS_EXCEPTION_FLOATING_POINT, (OSErrorHandler)errorHandler);
	OSSetErrorHandler(__OS_EXCEPTION_ALIGNMENT, (OSErrorHandler)errorHandler);

	sPreUserCallback  = nullptr;
}

void JUTException::errorHandler(OSError error, OSContext* pContext, u32 dsisr, u32 dar) {
	msr = PPCMfmsr();
    PPCMtmsr(msr | 0x2000);
    setFpscr((u32)&fpscr);
	OSFillFPUContext(pContext);
	OSSetErrorHandler(error, nullptr);

	exCallbackObject.callback = (JUTErrorHandler)sPreUserCallback;
	exCallbackObject.error = error;
	exCallbackObject.context = pContext;
	exCallbackObject.dsisr = dsisr;
	exCallbackObject.dar = dar;

	OSSendMessage(&sMessageQueue, &exCallbackObject, OS_MESSAGE_BLOCK);
}

inline void JUTException::showFloatSub(u16 position_x, u16 position_y, int index, f32 value) {
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

void JUTException::showFloat(OSContext* pContext) {
    mDirectPrint->erase(25, 75, 270, 130);
    int height;

	for (int i = 0, height = 80; i < 10; i++) {
        u16 height_2 = height;
		showFloatSub(26, height_2, i, pContext->fpr[i]);
		showFloatSub(117, height_2, i + 11, pContext->fpr[i + 11]);
		showFloatSub(208, height_2, i + 22, pContext->fpr[i + 22]);
        height += 10;
	}
	showFloatSub(26, 180, 10, pContext->fpr[10]);
	showFloatSub(117, 180, 21, pContext->fpr[21]);
}

void JUTException::showStack(OSContext* pContext) {
	u32 i;
	u32* stackPointer;

    mDirectPrint->erase(25, 25, 270, 180);
	mDirectPrint->drawString_f(54, 25, "Address:      Back Chain    LR Save\n");

	for (i = 0, stackPointer = (u32*)pContext->gpr[1]; (stackPointer != nullptr) && 
		(stackPointer != (u32*)0xFFFFFFFF) && (i++ < 0x10); stackPointer = (u32*)*stackPointer) {
        mDirectPrint->drawString_f(46, i * 10 + 33, "0x%08x:   0x%08x    0x%08x\n", 
			stackPointer, stackPointer[0], stackPointer[1]);
	}
}

void JUTException::showGPR(OSContext* pContext) {
    mDirectPrint->erase(25, 75, 270, 130);

	for (int i = 0; i < 10; i++) {
		mDirectPrint->drawString_f(30, i * 10 + 80, "R%02d:%08XH  R%02d:%08XH  R%02d:%08XH", i,
		    pContext->gpr[i], i + 11, pContext->gpr[i + 11], i + 22, pContext->gpr[i + 22]);
	}
	mDirectPrint->drawString_f(30, 180, "R%02d:%08XH  R%02d:%08XH", 10, pContext->gpr[10], 21,
		pContext->gpr[21]);
    mDirectPrint->drawString_f(30, 190, " LR:%08XH   CR:%08XH", pContext->lr, pContext->cr);
}

inline void JUTException::showHeader(OSError error, OSContext* pContext, u32 dsisr, u32 dar) {
	mDirectPrint->erase(25, 20, 270, 54);
	mDirectPrint->drawString_f(30, 25, "CONTEXT:%08X  (%s EXCEPTION)", pContext, sCpuExpName[error]);
    mDirectPrint->drawString_f(30, 40, " SRR0:%08X  SRR1:%08X", pContext->srr0, pContext->srr1);
    mDirectPrint->drawString_f(30, 50, "DSISR:%08X   DAR:%08X", dsisr, dar);
}

void JUTException::showMainInfo(EInfoPage page, OSError error, OSContext* pContext, u32 dsisr, u32 dar) {
    switch (page) {
		case EINFO_PAGE_GPR:
			showHeader(error, pContext, dsisr, dar);
			showGPR(pContext);
			break;
        case EINFO_PAGE_FLOAT:
			showHeader(error, pContext, dsisr, dar);
            showFloat(pContext);
			mDirectPrint->drawString_f(30, 190, " MSR:%08XH   FPSCR:%08XH", msr, ((u32*)&fpscr)[1]);
			break;
		case EINFO_PAGE_STACK:
			showStack(pContext);
			break;
    }
}

void JUTException::printContext(OSError error, OSContext* pContext, u32 dsisr, u32 dar) {
	if (!sErrorManager->mDirectPrint->isActive()) {
		return;
	}

    showHeader(error, pContext, dsisr, dar);
	waitTime(2000);

	while (true) {
		showMainInfo(EINFO_PAGE_GPR, error, pContext, dsisr, dar);
		waitTime(2000);
		showMainInfo(EINFO_PAGE_STACK, error, pContext, dsisr, dar);
		waitTime(2000);
		showMainInfo(EINFO_PAGE_FLOAT, error, pContext, dsisr, dar);
		waitTime(2000);
	}
}

void JUTException::waitTime(s32 timeout_ms)
{
	OSTime start_time = OSGetTime();
	OSTime ms;
	do {
		OSTime ticks = OSGetTime() - start_time;
		ms = ticks / (OS_TIMER_CLOCK / 1000);
	} while (ms < timeout_ms);
}

void JUTException::createFB() {
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

asm void JUTException::setFpscr(u32 fpscr) {
#ifdef __MWERKS__ // clang-format off
    nofralloc
    mffs f1
    stfd f1, 0x0(r3)
    blr
#endif // clang-format on
}

OSErrorHandler JUTException::setPreUserCallback(OSErrorHandler callback) {
	OSErrorHandler previous = sPreUserCallback;
	sPreUserCallback        = callback;
	return previous;
}

JUTExternalFB::JUTExternalFB(GXRenderModeObj* renderMode, GXGamma gamma, void* buffer, u32 size) {
	mRenderMode = renderMode;
	field_0x08 = (u32)buffer;
	mSize       = size;
	field_0x0C  = 1;
	mGamma      = gamma;
	field_0x10  = false;
}
