#include <dolphin/os.h>
#include <dolphin/vi/vifuncs.h>

#include <JSystem/JUtility/JUTGamePad.hpp>
#include <JSystem/JUtility/JUTDirectPrint.hpp>
#include <JSystem/JUtility/JUTException.hpp>

#include "System/ButtonCombo.hpp"
#include "System/DisplayUtil.hpp"
#include "System/Scenes/SceneManager.hpp"
#include "System/80009584.hpp"

#include "macros.h"

dummy_float_data()
enemies_float_data()

static u32 sCrashComboSequence[8] = {
    JUTGamePad::X, JUTGamePad::X, JUTGamePad::Y, JUTGamePad::Y,
    JUTGamePad::A, JUTGamePad::B, JUTGamePad::DPAD_DOWN, 0
};

enum CrashPage {
    CRASH_PAGE_STACK,
    CRASH_PAGE_GPR,
    CRASH_PAGE_FLOAT,
    CRASH_PAGE_MAX,
};

void exceptionCallback(u16 error, OSContext* pContext, u32 dsisr, u32 dar) {
    OSTime start = OSGetTime();
    while (OSTicksToMilliseconds(OSGetTime() - start) < 3000) {}

    static ButtonCombo lbl_803968E0(sCrashComboSequence);
    sGamePad->stopMotor();
    void* frameBuff = getMainFrameBuffer();
    JUTDirectPrint::getManager()->changeFrameBuffer(frameBuff, 640, 480);
    VISetNextFrameBuffer(getMainFrameBuffer());
    VIFlush();

    while (true) {
        OSTime curr = OSGetTime();
        while (OSTicksToMilliseconds(OSGetTime() - curr) < 50) {}

        JUTGamePad::read();
        if (lbl_803968E0.update()) {
            break;
        }

        SceneManager::sTotalFrameCount++;
    }

    BOOL redraw = 1;
    JUTDirectPrint::getManager()->print(160, 218, "%s %s", "Sep 24 2001", "14:49:49");
    while (true) {
        static CrashPage debugPage = CRASH_PAGE_STACK;
        
        OSTime curr = OSGetTime();
        while (OSTicksToMilliseconds(OSGetTime() - curr) < 50) {}

        JUTGamePad::read();
        if (sGamePad->testTrigger(JUTGamePad::A)) {
            redraw = 1;
            debugPage = CrashPage((debugPage + 1) % CRASH_PAGE_MAX);
        }

        if (redraw) {
            switch (debugPage) {
                case CRASH_PAGE_STACK:
                    JUTException::getManager()->showMainInfo(EINFO_PAGE_STACK, error, pContext, dsisr, dar);
                    break;
                case CRASH_PAGE_GPR:
                    JUTException::getManager()->showMainInfo(EINFO_PAGE_GPR, error, pContext, dsisr, dar);
                    break;
                case CRASH_PAGE_FLOAT:
                    JUTException::getManager()->showMainInfo(EINFO_PAGE_FLOAT, error, pContext, dsisr, dar);
                    break;
            }
        }

        redraw = 0;
    }
}
