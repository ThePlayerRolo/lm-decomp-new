#ifndef JUT_JUTEXCEPTION_HPP
#define JUT_JUTEXCEPTION_HPP

#include <JSystem/JKernel/JKRThread.hpp>
#include <dolphin/gx/GXEnum.h>
#include <dolphin/os/OSError.h>

typedef struct _GXRenderModeObj GXRenderModeObj;
typedef struct OSContext OSContext;
class JUTDirectPrint;

class JUTExternalFB {
public:
	JUTExternalFB(GXRenderModeObj*, GXGamma, void*, u32);

private:
	/* 0x00 */ _GXRenderModeObj* mRenderMode;
	/* 0x04 */ u32 mSize;
	/* 0x08 */ u32 field_0x08;
	/* 0x0C */ u16 field_0x0C;
	/* 0x0E */ u16 mGamma;
	/* 0x10 */ bool field_0x10;
	/* 0x11 */ u8 field_[3];
};

enum EInfoPage {
	EINFO_PAGE_GPR     = 1,
	EINFO_PAGE_FLOAT   = 2,
	EINFO_PAGE_STACK   = 3,
};

class JUTException : public JKRThread {
public:
	JUTException(JUTDirectPrint*);

	inline void showFloatSub(u16, u16, int, f32);
	void showFloat(OSContext*);
	void showStack(OSContext*);
	void showGPR(OSContext*);
	inline void showHeader(OSError, OSContext*, u32, u32);
	void showMainInfo(EInfoPage, OSError, OSContext*, u32, u32);
	void printContext(u16, OSContext*, u32, u32);
	void waitTime(s32);
	void createFB();

	/* vt[03] */ virtual void* run();

	static JUTException* create(JUTDirectPrint*);
	static void errorHandler(OSError, OSContext*, u32, u32);
	static void setFpscr(u32);
	static OSErrorHandler setPreUserCallback(OSErrorHandler);

	static JUTException* getManager() { return sErrorManager; }

private:
	static OSMessage sMessageBuffer[4];
	static OSMessageQueue sMessageQueue;
	static const char* sCpuExpName[16];
	static JUTException* sErrorManager;
	static OSErrorHandler sPreUserCallback;
	static u32 msr;
	static f64 fpscr;

	/* 0x60 */ JUTDirectPrint* mDirectPrint;
};

struct JUTWarn {
	JUTWarn& operator<<(const char*) { return *this; }
	JUTWarn& operator<<(long) { return *this; }
};

#endif
