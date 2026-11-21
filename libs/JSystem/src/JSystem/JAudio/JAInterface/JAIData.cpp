#include "jaudio/dvdthread.h"
#include <JSystem/JAudio/JAInterface/JAIData.hpp>
#include <JSystem/JAudio/JAInterface/JAIBasic.hpp>
#include <JSystem/JAudio/JAInterface/JAIGlobalParameter.hpp>
#include <JSystem/JAudio/JAInterface/JAIParameters.hpp>
#include <JSystem/JAudio/JAInterface/JAISystemInterface.hpp>
#include <JSystem/JAudio/JAInterface/JAIConst.hpp>
#include <JSystem/JAudio/JASystem/JASDvdThread.hpp>
#include <JSystem/JUtility/JUTAssert.hpp>

JAIData::JAIData() { }

void JAIData::init()
{
	mSeTable.mData       = nullptr;
	mSeqTable.mData      = nullptr;
	mStreamTable.mData   = nullptr;
	mSeparateSoundTables = 0;
	mStreamList          = nullptr;
	mNextLoadOrder       = 0;
	mStayHeapCount       = 0;
}


void JAIData::initSeqTrackInfoParameter(u32 param)
{
	mSeqTrackInfo[param].mSeqVolume = 1.0f;
	mSeqTrackInfo[param].mSeqPan    = 0.5f;
	mSeqTrackInfo[param].mSeqPitch  = 1.0f;
	mSeqTrackInfo[param].mSeqFxmix  = 0.0f;
	mSeqTrackInfo[param].mSeqDolby  = 0.0f;
	//mSeqTrackInfo[param].mSeqTempo  = 1.0f;
	for (int i = 0; i < JAIGlobalParameter::seqTrackMax; ++i) {
		mSeqTrackInfo[param].mTrackVolume[i] = 1.0f;
		mSeqTrackInfo[param].mTrackPan[i]    = 64.0f;
		mSeqTrackInfo[param].mTrackPitch[i]  = 1.0f;
		mSeqTrackInfo[param].mTrackFxmix[i]  = 0.0f;
		mSeqTrackInfo[param].mTrackDolby[i]  = 0.0f;
		mSeqTrackInfo[param].mTrackUpdate[i] = 0;
	}
}

void JAIData::setSeMovePara(JAIMoveParaSet* moveParaSet)
{
	for (u8 i = 0; i < 8; ++i) {
		if (!moveParaSet[i].mMoveCounter)
			continue;

		--moveParaSet[i].mMoveCounter;
		if (moveParaSet[i].mMoveCounter == 0)
			moveParaSet[i].mCurrentValue = moveParaSet[i].mTargetValue;
		else
			moveParaSet[i].mCurrentValue += moveParaSet[i].mMoveAmount;
	}
}

BOOL JAIData::moveParameter(JAIMoveParaSet* moveParaSet)
{
	if (moveParaSet->mMoveCounter == 0)
		return false;

	if (--moveParaSet->mMoveCounter) {
		moveParaSet->mCurrentValue -= moveParaSet->mMoveAmount;
		return true;
	}

	moveParaSet->mCurrentValue = moveParaSet->mTargetValue;
	return false;
}

void* JAIData::checkOnMemory(u32 param1, u8* param2)
{
	for (u8 i = 0; i < JAIGlobalParameter::autoHeapMax; ++i) {
		if (param1 != mAutoHeap[i].mSeqNumber)
			continue;

		if (mAutoHeap[i].mLoadedFlag == 1)
			return (void*)0xffffffff;

		if (param2)
			*param2 = i;

		return mAutoHeap[i].mPointer;
	}

	for (u8 i = 0; i < mStayHeapCount; ++i) {
		if (param1 != mStayHeap[i].mSeqNumber)
			continue;

		if (param2 != 0)
			*param2 = 0xff;

		return mStayHeap[i].mPointer;
	}
	return nullptr;
}

u8 JAIData::checkUsefulAutoHeapPosition()
{
	int i            = 0;
	u32 smallestSize = -1;
	int smallest     = 0;

	for (; i < JAIGlobalParameter::autoHeapMax; ++i)
		if (mAutoHeap[i].mSeqNumber == -1)
			break;

	if (i == JAIGlobalParameter::autoHeapMax) {
		for (i = 0; i < JAIGlobalParameter::autoHeapMax; ++i) {
			if (smallestSize > mAutoHeap[i].mLoadOrder
			    && mAutoHeap[i].mUseOrder == -1) {
				smallest     = i;
				smallestSize = mAutoHeap[i].mLoadOrder;
			}
		}

		if (smallestSize != -1)
			i = smallest;
	}

	return i;
}

void* JAIData::getFreeAutoHeapPointer(u8 param1, u32 param2)
{
	mAutoHeap[param1].mSeqNumber = param2;
	void* result                 = mAutoHeap[param1].mPointer;
	mAutoHeap[param1].mUseOrder  = mNextLoadOrder;
	mAutoHeap[param1].mLoadOrder = mNextLoadOrder;
	++mNextLoadOrder;
	return result;
}

void JAIData::releaseAutoHeapPointer(u8 param)
{
	if (param == 0xff)
		return;
	mAutoHeap[param].mUseOrder = -1;
}

u8* JAIData::getFreeStayHeapPointer(u32 param1, u32 param2)
{
	u8* result;

	if (param1 + (u32)mStayHeap[mStayHeapCount].mPointer
	        < (u32)mStayHeap[0].mPointer
	              + 0x3500
	    && mStayHeapCount < JAIGlobalParameter::stayHeapMax) {
		result = (u8*)mStayHeap[mStayHeapCount].mPointer;
		mStayHeap[mStayHeapCount].mSeqNumber = param2;
		u8* ptr                              = (u8*)((param1 & ~0x1F)
                        + (u32)mStayHeap[mStayHeapCount].mPointer);
		if (param1 & 0x1F)
			ptr += 0x20;
		++mStayHeapCount;
		mStayHeap[mStayHeapCount].mPointer = ptr;
	} else {
		result = nullptr;
	}
	return result;
}

void JAIData::setAutoHeapLoadedFlag(u8 param1, u8 param2)
{
	mAutoHeap[param1].mLoadedFlag = param2;
}

void JAIData::getInfoPointer(u32 sound_id, void** result)
{
	JAISoundTable* table;
	u32 category;

	*result = &JAIConst::nullInfoData2;
	if (mSeparateSoundTables == 0) {
		table = &mSeTable;
		switch (sound_id & JAISoundID_TypeMask) {
		case JAISoundID_Type_Se:
			category = (u8)(sound_id >> 12);
			break;
		case JAISoundID_Type_Sequence:
			category = 16;
			break;
		case JAISoundID_Type_Stream:
			category = 17;
			break;
		}
	} else {
		switch (sound_id & JAISoundID_TypeMask) {
		case JAISoundID_Type_Se:
			category = (u8)(sound_id >> 12);
			table    = &mSeTable;
			break;
		case JAISoundID_Type_Sequence:
			table    = &mSeqTable;
			category = 16;
			break;
		case JAISoundID_Type_Stream:
			table    = &mStreamTable;
			category = 17;
			break;
		}
	}

	u32 index = sound_id & JAISoundID_IndexMask;
	if (table->mData && index < table->mSoundMax[category])
		*result = &table->mCategorySoundInfos[category][index];
	else
		*result = nullptr;
}

void JAIData::initData() {

}

void JAIData::reloadInfoDataWork(JAISoundTable* soundTable)
{
	char* path = *(char**)soundTable->unk2C;
	u32 size   = Jac_CheckFile(path);
	if (size == 0)
		return;
	if (!soundTable->mData) {
		soundTable->mData = (u8*)unk1F4->allocHeap(size);
		void* tmp         = soundTable->mData;
		Jac_LoadFile(path, (u8*)tmp);
		soundTable->mDataSize = size;
	}
}


void JAIData::initSeqParameter(JAISeqParameter* param)
{
	param->mWaitSceneSet        = 0xffffffff;
	param->mTempo.mCurrentValue = 1.0f;
	param->mTempo.mMoveCounter  = 0;
	param->mPauseMode           = 0;
	param->unk1756              = 0;

	param->mPortUpdate   = 0;
	param->mVolumeUpdate = 0;
	param->mPanUpdate    = 0;
	param->mPitchUpdate  = 0;

	param->mTrackVolumeUpdate = 0;
	param->mTrackPanUpdate    = 0;
	param->mTrackPitchUpdate  = 0;
	param->mTrackFxmixUpdate  = 0;
	param->mTrackDolbyUpdate  = 0;
	param->mTrackFirUpdate    = 0;
	param->mTrackPortUpdate   = 0;

	for (u32 i = 0; i < JAIGlobalParameter::seqTrackMax; ++i) {
		param->mTrackVolume[i].mCurrentValue = 1.0f;
		param->mTrackPan[i].mCurrentValue    = 0.5f;
		param->mTrackPitch[i].mCurrentValue  = 1.0f;
		param->mTrackFxmix[i].mCurrentValue  = 0.0f;
		param->mTrackDolby[i].mCurrentValue  = 0.0f;
		param->mTrackFir[i].mCurrentValue    = 0.0f;

		param->mTrackVolume[i].mTargetValue = 1.0f;
		param->mTrackPan[i].mTargetValue    = 0.5f;
		param->mTrackPitch[i].mTargetValue  = 1.0f;
		param->mTrackFxmix[i].mTargetValue  = 0.0f;
		param->mTrackDolby[i].mTargetValue  = 0.0f;
		param->mTrackFir[i].mTargetValue    = 0.0f;

		param->mTrackVolume[i].mMoveCounter = 0;
		param->mTrackPan[i].mMoveCounter    = 0;
		param->mTrackPitch[i].mMoveCounter  = 0;
		param->mTrackFxmix[i].mMoveCounter  = 0;
		param->mTrackDolby[i].mMoveCounter  = 0;
		param->mTrackFir[i].mMoveCounter    = 0;

		param->mTrackInterruptSwitch[i] = 0;

		for (u32 j = 0; j < 16; ++j)
			param->mTrackPortData[i][j] = 0;
	}

	for (u32 i = 0; i < 16; ++i) {
		param->mPortData[i].mCurrentValue = 0.0f;
		param->mPortData[i].mMoveCounter  = 0;
	}

	for (u32 i = 0; i < JAIGlobalParameter::seqPlayTrackMax + 0xC; ++i) {
		param->mVolume[i].mCurrentValue = 1.0f;
		param->mPan[i].mCurrentValue    = 0.5f;
		param->mPitch[i].mCurrentValue  = 1.0f;
		param->mFxmix[i].mCurrentValue  = 0.0f;
		param->mDolby[i].mCurrentValue  = 0.0f;

		param->mVolume[i].mTargetValue = 1.0f;
		param->mPan[i].mTargetValue    = 0.5f;
		param->mPitch[i].mTargetValue  = 1.0f;
		param->mFxmix[i].mTargetValue  = 0.0f;
		param->mDolby[i].mTargetValue  = 0.0f;

		param->mVolume[i].mMoveCounter = 0;
		param->mPan[i].mMoveCounter    = 0;
		param->mPitch[i].mMoveCounter  = 0;
		param->mFxmix[i].mMoveCounter  = 0;
		param->mDolby[i].mMoveCounter  = 0;
	}
}
