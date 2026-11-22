#include <dolphin/os.h>
#include <dolphin/vi/vifuncs.h>

#include <JSystem/JUtility/JUTGamePad.hpp>
#include <JSystem/JUtility/JUTDirectPrint.hpp>
#include <JSystem/JUtility/JUTException.hpp>

#include "System/ButtonCombo.hpp"
#include "System/DisplayUtil.hpp"
#include "System/Scenes/SceneManager.hpp"
#include "Unsorted/GamePad.hpp"

#include "macros.h"

dummy_float_data()
enemies_float_data()

static u32 sCrashComboSequence[8] = {
    JUTGamePad::X, JUTGamePad::X, JUTGamePad::Y, JUTGamePad::Y,
    JUTGamePad::A, JUTGamePad::B, JUTGamePad::DPAD_DOWN, 0
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

        SceneManager::lbl_804D8090++;
    }

    s32 redraw = 1;
    JUTDirectPrint::getManager()->print(160, 218, "%s %s", "Sep 24 2001", "14:49:49");
    while (true) {
        static s32 debugPage = 0;
        
        OSTime curr = OSGetTime();
        while (OSTicksToMilliseconds(OSGetTime() - curr) < 50) {}

        JUTGamePad::read();
        if (sGamePad->testTrigger(JUTGamePad::A)) {
            redraw = 1;
            debugPage = (debugPage + 1) % 3;
        }

        if (redraw) {
            switch (debugPage) {
                case 0:
                    JUTException::getManager()->showMainInfo(3, error, pContext, dsisr, dar);
                    break;
                case 1:
                    JUTException::getManager()->showMainInfo(1, error, pContext, dsisr, dar);
                    break;
                case 2:
                    JUTException::getManager()->showMainInfo(2, error, pContext, dsisr, dar);
                    break;
            }
        }

        redraw = 0;
    }
}
