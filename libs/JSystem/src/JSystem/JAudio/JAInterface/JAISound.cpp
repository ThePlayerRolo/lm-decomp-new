#include "jaudio/jammain_2.h"
#include "jaudio/random.h"
#include <JSystem/JAudio/JAInterface/JAISound.hpp>
#include <JSystem/JAudio/JAInterface/JAIBasic.hpp>
#include <JSystem/JAudio/JAInterface/JAIParameters.hpp>
#include <JSystem/JAudio/JAInterface/JAISystemInterface.hpp>
#include <JSystem/JAudio/JAInterface/JAIGlobalParameter.hpp>
#include <JSystem/JAudio/JAInterface/JAIConst.hpp>
#include <JSystem/JAudio/JAInterface/JAIInter.hpp>
#include <JSystem/JAudio/JASystem/JASTrackMgr.hpp>
#include <math.h>

JAISound::JAISound()
{
	mCustomParameter = 0;
	mState           = SOUNDSTATE_Inactive;
	mWaitTimer       = 10;
	mActor           = 0;
}

int JAISound::initMoveParameter(JAIMoveParaSet* set, f32 target, u32 moveTime)
{
	if (set->mMoveCounter == 0 && set->mCurrentValue == target)
		return 0;

	if (set->mMoveCounter != 0 && set->mTargetValue == target)
		return 0;

	set->mTargetValue = target;
	if (moveTime == 0) {
		set->mCurrentValue = target;
		return 0;
	}

	if (moveTime == 1)
		set->mMoveAmount = set->mCurrentValue - set->mTargetValue;
	else
		set->mMoveAmount
		    = (set->mCurrentValue - set->mTargetValue) / (f32)moveTime;
	set->mMoveCounter = moveTime;

	return 1;
}

// TODO: No.
u32 JAISound::getSeCategoryNumber()
{
    JAIBasic* basic = (JAIBasic*)mMainSoundPPointer[0];

	return basic->changeIDToCategory(mSoundID);
}


void JAISound::stop(u32 fadeout)
{
}

void JAISound::setVolume(f32 param_1, u32 param_2, u8 param_3)
{
	switch (mSoundID & JAISoundID_TypeMask) {
	case JAISoundID_Type_Sequence:
		setSeqInterVolume(param_3, param_1, param_2);
		break;
	case JAISoundID_Type_Se:
		setSeInterVolume(param_3, param_1, param_2, 0);
		break;
	case JAISoundID_Type_Stream:
		setStreamInterVolume(param_3, param_1, param_2);
		break;
	}
}

void JAISound::setPan(f32 param_1, u32 param_2, u8 param_3)
{
	switch (mSoundID & JAISoundID_TypeMask) {
	case JAISoundID_Type_Sequence:
		setSeqInterPan(param_3, param_1, param_2);
		break;
	case JAISoundID_Type_Se:
		setSeInterPan(param_3, param_1, param_2, 0);
		break;
    case JAISoundID_Type_Stream:
		break;
	}
}

void JAISound::setPitch(f32 param_1, u32 param_2, u8 param_3)
{
	switch (mSoundID & JAISoundID_TypeMask) {
	case JAISoundID_Type_Sequence:
		setSeqInterPitch(param_3, param_1, param_2);
		break;
	case JAISoundID_Type_Se:
		setSeInterPitch(param_3, param_1, param_2, 0.0f);
		break;
	case JAISoundID_Type_Stream:
		setStreamInterPitch(param_3, param_1, param_2);
		break;
	}
}


void JAISound::setFxmix(f32 param_1, u32 param_2, u8 param_3)
{
	switch (mSoundID & JAISoundID_TypeMask) {
	case JAISoundID_Type_Sequence:
		setSeqInterFxmix(param_3, param_1, param_2);
		break;
	case JAISoundID_Type_Se:
		setSeInterFxmix(param_3, param_1, param_2, 0.0f);
		break;
	case JAISoundID_Type_Stream:
		break;
	}
}

void JAISound::setDirectFxmix(f32, u32) { }

void JAISound::setDolby(f32 param_1, u32 param_2, u8 param_3)
{
	switch (mSoundID & JAISoundID_TypeMask) {
	case JAISoundID_Type_Sequence:
		setSeqInterDolby(param_3, param_1, param_2);
		break;
	case JAISoundID_Type_Se:
		setSeInterDolby(param_3, param_1, param_2, 0.0f);
		break;
	case JAISoundID_Type_Stream:
		break;
	}
}

void JAISound::setDirectDolby(f32, u32) { }

void JAISound::setTempoProportion(f32 param_1, u32 param_2)
{
	switch (mSoundID & JAISoundID_TypeMask) {
	case JAISoundID_Type_Sequence:
		setSeqTempoProportion(param_1, param_2);
		break;
	case JAISoundID_Type_Se:
		break;
	case JAISoundID_Type_Stream:
		break;
	}
}

void JAISound::setPortData(u8 param_1, u16 param_2)
{
	switch (mSoundID & JAISoundID_TypeMask) {
	case JAISoundID_Type_Sequence:
		setSeqPortData(param_1, param_2, 0);
		break;
	case JAISoundID_Type_Se:
		setSePortData(param_1, param_2);
		break;
	}
}

void JAISound::setPrepareFlag(u8) { }

void JAISound::checkReady() { }

void JAISound::setSeqInterVolume(u8 param, f32 volume, u32 moveTime)
{
	if ((mSoundID & JAISoundID_TypeMask) != JAISoundID_Type_Sequence)
		return;

	if (!getSeqParameter())
		return;

	if (getSeqParameter()->mUpdateData) {
		getSeqParameter()->mUpdateData->unk8 |= 0x40000;
	}

	int ret = initMoveParameter(&getSeqParameter()->mVolume[param], volume,
	                            moveTime);
	if (ret != 0)
		getSeqParameter()->mVolumeUpdate |= 1 << param;


}

void JAISound::setSeqInterPan(u8 param, f32 pan, u32 moveTime)
{
	if ((mSoundID & JAISoundID_TypeMask) != JAISoundID_Type_Sequence)
		return;

	if (!getSeqParameter())
		return;

	if (getSeqParameter()->mUpdateData)
		getSeqParameter()->mUpdateData->unk8 |= 0x80000;

	int ret = initMoveParameter(&getSeqParameter()->mPan[param], pan, moveTime);
	if (ret != 0)
		getSeqParameter()->mPanUpdate |= 1 << param;

}

void JAISound::setSeqInterPitch(u8 param, f32 pitch, u32 moveTime)
{
	if ((mSoundID & JAISoundID_TypeMask) != JAISoundID_Type_Sequence)
		return;

	if (!getSeqParameter())
		return;

	if (getSeqParameter()->mUpdateData)
		getSeqParameter()->mUpdateData->unk8 |= 0x100000;

	int ret
	    = initMoveParameter(&getSeqParameter()->mPitch[param], pitch, moveTime);
	if (ret != 0)
		getSeqParameter()->mPitchUpdate |= 1 << param;

}

void JAISound::setSeqInterFxmix(u8 param, f32 fxmix, u32 moveTime)
{
	if ((mSoundID & JAISoundID_TypeMask) != JAISoundID_Type_Sequence)
		return;

	if (!getSeqParameter())
		return;

	if (getSeqParameter()->mUpdateData)
		getSeqParameter()->mUpdateData->unk8 |= 0x200000;

	int ret
	    = initMoveParameter(&getSeqParameter()->mFxmix[param], fxmix, moveTime);
	if (ret != 0)
		getSeqParameter()->mFxmixUpdate |= 1 << param;
}

void JAISound::setSeqInterDolby(u8 param, f32 dolby, u32 moveTime)
{
	if ((mSoundID & JAISoundID_TypeMask) != JAISoundID_Type_Sequence)
		return;

	if (!getSeqParameter())
		return;

	if (interPointer->mSoundOutputMode != 2) {
		if (getSeqParameter()->mDolby[param].mCurrentValue != 0.0f)
			dolby = 0.0f;
		else
			return;
	}

	int ret
	    = initMoveParameter(&getSeqParameter()->mDolby[param], dolby, moveTime);
	if (ret == 1)
		getSeqParameter()->mDolbyUpdate |= 1 << param;

	if (getSeqParameter()->mUpdateData && ret != 2)
		getSeqParameter()->mUpdateData->unk8 |= 0x400000;
}

void JAISound::setSeqTempoProportion(f32 tempo, u32 moveTime)
{
	if ((mSoundID & JAISoundID_TypeMask) != JAISoundID_Type_Sequence)
		return;

	if (!getSeqParameter())
		return;

	int ret = initMoveParameter(&getSeqParameter()->mTempo, tempo, moveTime);

	if (getSeqParameter()->mUpdateData)
		getSeqParameter()->mUpdateData->unk8 |= 0x4;
}

void JAISound::setSeqPortData(u8 param_1, u16 param_2, u32 param_3)
{
	if ((mSoundID & JAISoundID_TypeMask) != JAISoundID_Type_Sequence)
		return;

	if (!getSeqParameter())
		return;

	if (getSeqParameter()->mUpdateData)
		getSeqParameter()->mUpdateData->unk8 |= 0x10;

	if (getSeqParameter()->mPortData[param_1].mCurrentValue == 0.0f
	    && mState >= SOUNDSTATE_Started) {
		u16 local_38;
		Jam_ReadPortApp(getSeqParameter()->mSeqHandle,
		                                param_1 << 16, &local_38);
		getSeqParameter()->mPortData[param_1].mCurrentValue = local_38;
	}

	// possible bug? this is missing the ret != 0 check
	int ret = initMoveParameter(&getSeqParameter()->mPortData[param_1], param_2,
	                            param_3);
	getSeqParameter()->mPortUpdate |= 1 << param_1;

}

void JAISound::setWaveReadMode(s32 bank_id, s32 group_no)
{
	if ((mSoundID & JAISoundID_TypeMask) != JAISoundID_Type_Sequence)
		return;

	if (!getSeqParameter())
		return;

	u32 id = bank_id << 16 | group_no;
    /*
	if (interPointer->mWaveGroupNumber[bank_id] == group_no
	    && interPointer->mWaveLoadStatus[bank_id]
	           == JAIBasic::WAVE_LOAD_STATUS_LOADING)
		getSeqParameter()->mWaitSceneSet = id;
        */
}

void JAISound::setTrackVolume(u8 param_1, f32 param_2, u32 param_3) { }

void JAISound::setTrackVolumeMulti(u8, u32, f32, u32) { }

void JAISound::setTrackMuteSwitch(u8, u8) { }

void JAISound::setTrackMuteSwitchMulti(u32, u8) { }

void JAISound::setTrackInterruptSwitch(u8 param_1, u8 param_2)
{
	if ((mSoundID & JAISoundID_TypeMask) != JAISoundID_Type_Sequence)
		return;

	if (!getSeqParameter())
		return;

	getSeqParameter()->mTrackInterruptSwitch[param_1] = param_2;
	if (getSeqParameter()->mUpdateData)
		getSeqParameter()->mUpdateData->unk8 |= 0x800000;
}

void JAISound::setTrackPan(u8, f32, u32) { }

void JAISound::setTrackPanMulti(u8, u32, f32, u32) { }

void JAISound::setTrackPitch(u8, f32, u32) { }

void JAISound::setTrackPitchMulti(u8, u32, f32, u32) { }

void JAISound::setTrackFxmix(u8, f32, u32) { }

void JAISound::setTrackFxmixMulti(u8, u32, f32, u32) { }

void JAISound::setTrackDolby(u8, f32, u32) { }

void JAISound::setTrackDolbyMulti(u8, u32, f32, u32) { }

void JAISound::setTrackFirU7(u8, u8, u32) { }

void JAISound::setTrackFirMultiU7(u8, u32, u8, u32) { }

void JAISound::setTrackPortData(u8 param_1, u8 param_2, u16 param_3)
{
	if ((mSoundID & JAISoundID_TypeMask) != JAISoundID_Type_Sequence)
		return;

	if (!getSeqParameter())
		return;

	if (!getSeqParameter()->mUpdateData)
		return;

	if (mState >= SOUNDSTATE_Playing) {
		JAISystemInterface::writePortApp(getSeqParameter()->mSeqHandle,
		                                 getTrackPortRoute(param_1, param_2),
		                                 param_3);
	} else {
		getSeqParameter()->mUpdateData->unk8 |= 0x1000;
		getSeqParameter()->mTrackPortUpdate |= 1 << param_1;
	}
	getSeqParameter()->mTrackPortData[param_1][param_2] = param_3;
}

void JAISound::setSeInterMovePara(JAIMoveParaSet* set, u32 moveTime)
{
	if (set->mCurrentValue != set->mTargetValue) {
		if (moveTime == 0) {
			set->mCurrentValue = set->mTargetValue;
		} else {
			set->mMoveCounter = moveTime;
			set->mMoveAmount
			    = (set->mTargetValue - set->mCurrentValue) / moveTime;
		}
	}
}

static inline u32 rand_u32()
{
	return JAIConst::random.get_ufloat_1() * 4294967300.0f;
}

void JAISound::setSeInterRandomPara(f32* target, u32 random, f32 min, f32 max)
{
	f32 rnd = ((f32)((GetRandom_u32() % (random * 2)) + 1) - (f32)random) / 1000.0f;
	if (*target + rnd > max) {
		*target = max;
	} else if (*target < min - rnd) {
		*target = min;
	} else {
		*target += rnd;
	}
}

void JAISound::setSeInterVolume(u8 param, f32 volume, u32 moveTime, u8 random)
{
	if ((mSoundID & JAISoundID_TypeMask) != JAISoundID_Type_Se)
		return;

	if (!getSeParameter())
		return;

	JAIMoveParaSet* set = &getSeParameter()->mVolume[param];
	set->mTargetValue   = volume;
	if (random != 0) {
		u32 rnd = (random * 1000) / 127U;
		setSeInterRandomPara(&set->mTargetValue, rnd, 0.0f, 1.0f);
	}

	setSeInterMovePara(set, moveTime);
}

void JAISound::setSeInterPan(u8 param, f32 pan, u32 moveTime, u8 random)
{
	if ((mSoundID & JAISoundID_TypeMask) != JAISoundID_Type_Se)
		return;

	if (!getSeParameter())
		return;

	JAIMoveParaSet* set = &getSeParameter()->mPan[param];
	set->mTargetValue   = pan;
	if (random != 0) {
		u32 rnd = (random * 1000) / 127U;
		setSeInterRandomPara(&set->mTargetValue, rnd, 0.0f, 1.0f);
	}

	setSeInterMovePara(set, moveTime);
}

void JAISound::setSeInterFxmix(u8 param, f32 fxmix, u32 moveTime, u8 random)
{
	if ((mSoundID & JAISoundID_TypeMask) != JAISoundID_Type_Se)
		return;

	if (!getSeParameter())
		return;

	JAIMoveParaSet* set = &getSeParameter()->mFxmix[param];
	set->mTargetValue   = fxmix;
	if (random != 0) {
		u32 rnd = (random * 1000) / 127U;
		setSeInterRandomPara(&set->mTargetValue, rnd, 0.0f, 1.0f);
	}

	setSeInterMovePara(set, moveTime);
}

void JAISound::setSeInterFir(u8, u8, u32, u8) { }

void JAISound::setSeInterDolby(u8 param_1, f32 param_2, u32 param_3, u8 param_4)
{
	if ((mSoundID & JAISoundID_TypeMask) != JAISoundID_Type_Se)
		return;

	if (!getSeParameter())
		return;

	JAIMoveParaSet* set = &getSeParameter()->mDolby[param_1];
	set->mTargetValue   = param_2;
	if (param_4 != 0) {
		u32 uVar5 = (param_4 * 1000) / 127U;
		setSeInterRandomPara(&set->mTargetValue, uVar5, 0.0f, 1.0f);
	}

	setSeInterMovePara(set, param_3);
}

void JAISound::setSeInterPitch(u8 param_1, f32 param_2, u32 param_3,
                               f32 param_4)
{
	if ((mSoundID & JAISoundID_TypeMask) != JAISoundID_Type_Se)
		return;

	if (!getSeParameter())
		return;

	JAIMoveParaSet* set = &getSeParameter()->mPitch[param_1];
	set->mTargetValue   = param_2;
	if (param_4 != 0) {
		u32 uVar5 = (param_4 * 1000);
		setSeInterRandomPara(&set->mTargetValue, uVar5, 0.1f, 16.0f);
	}

	setSeInterMovePara(set, param_3);
}

void JAISound::setSePortData(u8 param_1, u16 param_2)
{
	if ((mSoundID & JAISoundID_TypeMask) != JAISoundID_Type_Se)
		return;

	if (!getSeParameter())
		return;

	if (mState == SOUNDSTATE_Stored) {
		getSeParameter()->mPortData[param_1] = param_2;
		getSeParameter()->mPortUpdate |= 1 << param_1;
	} else {
        /*
		interPointer->mSeSequence->setTrackPortData(mTrack, param_1, param_2);
        */
	}
}

void JAISound::getSePortData(u8) { }

void JAISound::setStreamMode(u32) { }

void JAISound::setStreamInterVolume(u8 param_1, f32 param_2, u32 param_3)
{
	if ((mSoundID & JAISoundID_TypeMask) != JAISoundID_Type_Stream)
		return;
	if (!getStreamParameter())
		return;

	int iVar2 = initMoveParameter(&getStreamParameter()->mVolume[param_1],
	                              param_2, param_3);
	if (iVar2 == 1) {
		getStreamParameter()->mVolumeUpdate |= 1 << param_1;
	}

	if (getStreamParameter()->mUpdateData && iVar2 != 2) {
		getStreamParameter()->mUpdateData->mActiveTrackFlag |= 0x40000;
	}
}

void JAISound::setStreamInterPitch(u8 param_1, f32 param_2, u32 param_3)
{
	if ((mSoundID & JAISoundID_TypeMask) != JAISoundID_Type_Stream)
		return;
	if (!getStreamParameter())
		return;

	int iVar2 = initMoveParameter(&getStreamParameter()->mPitch[param_1],
	                              param_2, param_3);
	if (iVar2 == 1) {
		getStreamParameter()->mPitchUpdate |= 1 << param_1;
	}

	if (getStreamParameter()->mUpdateData && iVar2 != 2) {
		getStreamParameter()->mUpdateData->mActiveTrackFlag |= 0x100000;
	}
}

void JAISound::setStreamInterPan(u8 param_1, f32 param_2, u32 param_3)
{
	if ((mSoundID & JAISoundID_TypeMask) != JAISoundID_Type_Stream)
		return;
	if (!getStreamParameter())
		return;

	int iVar2 = initMoveParameter(&getStreamParameter()->mPan[param_1], param_2,
	                              param_3);
	if (iVar2 == 1) {
		getStreamParameter()->mPanUpdate |= 1 << param_1;
	}

	if (getStreamParameter()->mUpdateData && iVar2 != 2) {
		getStreamParameter()->mUpdateData->mActiveTrackFlag |= 0x80000;
	}
}

void JAISound::setStreamPrepareFlag(u8) { }

void JAISound::checkStreamReady() { }

void JAISound::setPauseMode(u8 mode, u8 volume)
{
	switch (mSoundID & JAISoundID_TypeMask) {
	case JAISoundID_Type_Sequence:
		if (getSeqParameter()) {
			if (mode == 3)
				mode = 4;
			if (mode) {
				switch (mode) {
				case 1:
					setSeqInterVolumeU7(11, volume, 1);
					break;
				case 2:
					JASystem::TrackMgr::handleToSeq(
					    getSeqParameter()->mSeqHandle)
					    ->pauseTrackAll();
					break;
				}
			} else {
				getSeqParameter();
				switch (getSeqParameter()->mPauseMode) {
				case 1:
					setSeqInterVolume(11, 1.0f, 1);
					break;
				case 2:
					JASystem::TrackMgr::handleToSeq(
					    getSeqParameter()->mSeqHandle)
					    ->unPauseTrackAll();
					break;
				}
			}

			getSeqParameter()->mPauseMode = mode;
		}
		break;
	case JAISoundID_Type_Stream:
		if (getStreamParameter()) {
			if (mode) {
				switch (mode) {
				case 1:
					setStreamInterVolume(11, volume / 127.0f, 1);
					break;
				case 2:
					JAInter::StreamLib::setPauseFlag(2);
					break;
				}
			} else {
				switch (getStreamParameter()->mPauseMode) {
				case 1:
					setStreamInterVolume(11, 1.0f, 1);
					break;
				case 2:
					JAInter::StreamLib::clearPauseFlag(2);
					break;
				}
			}

			getStreamParameter()->mPauseMode = mode;
		}
		break;
	}
}

void JAISound::setSeqPrepareFlag(u8) { }

void JAISound::checkSeqReady() { }

void JAISound::getVolume(u8) { }

void JAISound::getPan(u8) { }

void JAISound::getPitch(u8) { }

void JAISound::getFxmix(u8) { }

void JAISound::getDolby(u8) { }

void JAISound::getTempoProportion() { }

void JAISound::getPortData(u8) { }

f32 JAISound::getSeqInterVolume(u8 param_1)
{
	f32 result;
	if (mState == SOUNDSTATE_Playing || mState == SOUNDSTATE_Stopping) {
		result = getSeqParameter()->mVolume[param_1].mCurrentValue;
	} else {
		result = -1.0f;
	}
	return result;
}

void JAISound::getSeqInterPan(u8) { }

void JAISound::getSeqInterPitch(u8) { }

void JAISound::getSeqInterFxmix(u8) { }

void JAISound::getSeqInterDolby(u8) { }

void JAISound::getSeqTempoProportion() { }

void JAISound::getSeqPortData(u8) { }

void JAISound::getTrackParameterU7(u8, s8) { }

void JAISound::getTrackParameterF32(u8, s8) { }

void JAISound::getPointer(u8, s8) { }

void JAISound::getTrackPortData(u8, u8) { }

void JAISound::getSeParametermeterF32(u8, u8) { }

f32 JAISound::getStreamInterVolume(u8 param_1)
{
	if ((mSoundID & JAISoundID_TypeMask) == JAISoundID_Type_Stream
	    && getStreamParameter()) {
		if (mState == SOUNDSTATE_Playing || mState == SOUNDSTATE_Stopping)
			return getStreamParameter()->mVolume[param_1].mCurrentValue;

		return -1.0f;
	}

	return -1.0f;
}

void JAISound::getStreamInterPitch(u8) { }

u32 JAISound::getActorGroundNumber() { return mActorGroundNumber; }

JAISeqParameter* JAISound::getSeqParameter()
{
	return (JAISeqParameter*)mCustomParameter;
}

JAISeParameter* JAISound::getSeParameter()
{
	return (JAISeParameter*)mCustomParameter;
}

JAIStreamParameter* JAISound::getStreamParameter()
{
	return (JAIStreamParameter*)mCustomParameter;
}

u32 JAISound::getTrackPortRoute(u8 param_1, u8 param_2)
{
	if (mSoundID & 0x800)
		return (param_1 >> 4) + 0x20000000 + ((param_1 & 0xF) << 4)
		       + (param_2 << 16);
	return (param_1 & 0xf) + 0x10000000 + (param_2 << 16);
}

void* JAISound::getSeInfoPointer() { return mInfo; }
