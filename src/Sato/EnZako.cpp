#include "Sato/EnZako.hpp"
#include "Koga/GameModeUtil.hpp"
#include "Koga/ToolData.hpp"
#include "types.h"

dummy_float_data();
enemies_float_data();

EnZako::EnZako() {

}

EnZako::~EnZako() {
    
}


void EnZako::vt_0C() {
    _958 = _954;
    getStrategy()->update();
    fn_800C1FFC();
}


void EnZako::vt_10() {
    getStrategy()->mpZako = this;
    _954 = nullptr;
    _93C = 0.0;
    _940 = 0.0;
    _944 = 0.0;
    _948 = 0.0;
    _94C = 0;
    mPlayerID = 0;
}


void EnZako::attachPathData(const Koga::ToolData::JMapData* pPathData) {
    mPathData.attach(pPathData);
}


bool EnZako::attachPathData() {
    ToolDataRef temp = getToolDataRef();
    const char* pathName;

    if (!ToolDataRef::getValue(&temp, "path_name", &pathName)) {
        return false;
    }

    mPathData.attach(Koga::GameModeUtil::getPathResource(pathName));

    return true;
}


Koga::ToolData* EnZako::fn_800C1FF4() {
    return &mPathData;
}
