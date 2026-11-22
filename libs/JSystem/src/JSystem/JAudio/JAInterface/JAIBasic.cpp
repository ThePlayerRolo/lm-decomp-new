#include <jaudio/aictrl.h>
#include <jaudio/jammain_2.h>
#include <jaudio/seqsetup.h>
#include <jaudio/dvdthread.h>
#include <jaudio/audiothread.h>
#include <jaudio/connect.h>
#include <jaudio/dummyrom.h>
#include <jaudio/memory.h>
#include <jaudio/virload.h>
#include <JSystem/JAudio/JAInterface/JAIBasic.hpp>
#include <JSystem/JAudio/JAInterface/JAISound.hpp>
#include <JSystem/JAudio/JAInterface/JAIData.hpp>
#include <JSystem/JAudio/JAInterface/JAIInter.hpp>
#include <JSystem/JAudio/JAInterface/JAIGlobalParameter.hpp>
#include <JSystem/JAudio/JAInterface/JAIParameters.hpp>
#include <JSystem/JAudio/JAInterface/JAISystemInterface.hpp>
#include <JSystem/JAudio/JASystem/JASTrackMgr.hpp>
#include <JSystem/JAudio/JASystem/JASDvdThread.hpp>
#include <JSystem/JAudio/JASystem/JASSystemHeap.hpp>
#include <JSystem/JAudio/JASystem/JASAudioThread.hpp>
#include <JSystem/JAudio/JASystem/JASDriverIF.hpp>
#include <JSystem/JAudio/JASystem/JASVload.hpp>
#include <JSystem/JAudio/JASystem/JASWaveBankMgr.hpp>
#include <JSystem/JAudio/JASystem/JASWaveArcLoader.hpp>
#include <JSystem/JAudio/JASystem/JASBankMgr.hpp>
#include <dolphin/mtx.h>
#include <stdio.h>

#include <JSystem/JAudio/JAInterface/JAIConst.hpp>

JAIBasic* JAIBasic::basic;

JAICamera JAInullCamera(&JAIConst::camTrans, &JAIConst::camPreTrans,
                        JAIConst::camMtx);

JAIBasic::JAIBasic()
{
	basic                  = this;

	unk1C.flag3 = 0;
	unk1C.flag1 = 0;
	unk1C.flag2 = 0;
	unk1C.flag4 = 0;
	unk1C.flag5 = 0;
	unk1C.flag6 = 0;
	unk1C.flag7 = 0;

	unk15 = 0;
	unk10 = 0;
	unk11 = 0;
	unk24 = 0;
	unk8  = nullptr;
	unk38 = nullptr;
	unk20 = 0;
	unk30 = 0;
	unk13 = 3;
	unk4C = nullptr;
	unk3C = nullptr;
	unk40 = nullptr;
	unk44 = 0;
	unk48 = 0;
	unk50 = 0;
	unk54 = nullptr;
	unk58 = nullptr;
	unk5C = 0;
	unk68 = nullptr;
	unk6C = nullptr;
	unk34 = -1;
	unk70 = 0;
	unkC  = nullptr;
	unk78 = 0;
}

void JAIBasic::startSeSequence() { }

const char* unkArray[] = {
	"One"
};

void JAIBasic::initInterfaceMain()
{
	mData = (JAIData*)OSAlloc2(sizeof(JAIData));
	mData->init();
	mData->unk1F4      = this;
	mData->unk204.unk0 = this;
	mData->unk1FC.unk0 = this;
	mData->unk200.unk0 = this;
	setRegisterTrackCallback();
	Jac_SetMixerLevel(JAIGlobalParameter::inputGainDown,
	                                JAIGlobalParameter::outputGainUp);


	char archivesPath[100];
	archivesPath[0] = 0;


	initReadFile();
	setWaveScene();
	initAllocParameter();
	initNullData();
	initSeqsLoadArea();


	strcat(archivesPath, "Seqs/");
	strcat(archivesPath, "JaiArcS.hed");

	if (!unk58) {
		JV_InitHeader(archivesPath);
	} else {
		JV_InitHeader_M(archivesPath, *unk58, nullptr);
	}
	Jac_ConnectTableInit();
	Jam_InitRegistTrack();
	unk2C = JV_GetArchiveHandle(
	    "JaiArcS.hed");
	unk38 = 0;
	startSoundDirectID(0x80000800, &unk38, nullptr, 1, 4);
	if (!unk1C.flag3)
		checkEntriedSeq();
}

void JAIBasic::setCameraInfo(VecPtr pos, VecPtr dir, MtxPtr mtx, u32 id)
{
	if (JAIGlobalParameter::audioCameraMax <= id)
		return;

	unk8[id].unk0 = pos;
	unk8[id].unk4 = dir;
	unk8[id].unk8 = mtx;
}

void JAIBasic::initStream() { JAInter::StreamLib::init(unk1C.flag7); }

void JAIBasic::setRegisterTrackCallback()
{
	Jam_RegisterTrackCallback(&JAIBasic::setParameterSeqSync);
}

void JAIBasic::initAudioThread(JKRSolidHeap* heap, u32 param1, u8 param2) { }

void JAIBasic::bootDSP() { }

void JAIBasic::initReadFile()
{
	switch (unk13) {
	case 0:
		break;
	case 1:
		checkInitListFile();
		break;
	case 2:
		checkInitDataFile();
		break;
	case 3:
		if (!checkInitListFile())
			checkInitDataFile();
		break;
	}
}

struct FabricatedFileHeader {
	/* 0x0 */ u16 unk0;
	/* 0x2 */ u16 unk2;
	/* 0x4 */ u16 unk4;
	/* 0x6 */ u16 unk6;
	/* 0x8 */ u16 unk8;
	/* 0xA */ u16 unkA;
};

BOOL JAIBasic::checkInitListFile()
{
	if (!JAISystemInterface::checkFileExsistence("JaiInit.bld"))
		return 0;

	void* file                   = loadDVDFile("JaiInit.bld");
	FabricatedFileHeader* header = (FabricatedFileHeader*)file;

	if (file) {

		strcpy("JaiArcS.hed",
		       (char*)((u8*)file + header->unk0));

		unk3C = (FabricatedUnk3CStruct*)((u8*)file + header->unk2);
		unk40 = (FabricatedUnk40Struct*)((u8*)file + header->unk4);

		strcpy("Seqs/JaiSeInf.bst",
		       (char*)((u8*)file + header->unk6));

		if (header->unk8) {
			strcpy("Seqs/JaiSqInf.bst",
			       (char*)((u8*)file + header->unk8));
			strcpy("Seqs/JaiStInf.bst",
			       (char*)((u8*)file + header->unkA));
			mData->mSeparateSoundTables = 1;
		} else {
			mData->mSeparateSoundTables = 0;
		}

		return 1;
	} else {
		return 0;
	}
}

BOOL JAIBasic::checkInitDataFile()
{
	if (!JAISystemInterface::checkFileExsistence(
	        JAIGlobalParameter::initDataFileName))
		return 0;

	loadTmpDVDFile(JAIGlobalParameter::initDataFileName, &unk4C);
	if (unk4C) {
		checkInitDataOnMemory();
		return 1;
	} else {
		return 0;
	}
}

void JAIBasic::checkInitDataOnMemory()
{
	JAIData* data = mData;

	bool shouldContinue = true;
	u32 i               = 0;
	while (shouldContinue) {
		u32 command = unk4C[i];
		++i;
		switch (command) {
		case 0:
			shouldContinue = false;
			break;
		case 1:
			if (unk4C[i] == 0) {
				u32 offset        = unk4C[i + 1];
				data->mSeTable.mDataSize = unk4C[i + 2];
				data->mSeTable.mData = (u8*)transInitDataFile(
				    ((u8*)unk4C) + offset, data->mSeTable.mDataSize);
				data->mSeparateSoundTables = 0;
				i += 4;
			} else {
				// TODO: should this all be done via header structs? probably
				u32 offset        = unk4C[i + 1];
				data->mSeTable.mDataSize = unk4C[i + 2];
				data->mSeTable.mData = (u8*)transInitDataFile(
				    ((u8*)unk4C) + offset, data->mSeTable.mDataSize);

				u8* buffer1      = ((u8*)unk4C) + unk4C[i + 3];
				data->mSeqTable.mDataSize = unk4C[i + 4];
				data->mSeqTable.mData
				    = (u8*)transInitDataFile(buffer1, data->mSeTable.mDataSize);

				u8* buffer         = ((u8*)unk4C) + unk4C[i + 5];
				data->mStreamTable.mDataSize = unk4C[i + 6];
				data->mStreamTable.mData
				    = (u8*)transInitDataFile(buffer, data->mStreamTable.mDataSize);
				data->mSeparateSoundTables = 0;

				i += 7;
			}
			break;
		case 2: {
			u32 uVar7 = 0;
			while (unk4C[i + uVar7] != 0)
				uVar7 += 3;

			unk50 = (FabricatedUnk50Struct*)transInitDataFile(
			    (u8*)&unk4C[i], (uVar7 / 3) * 0xC + 4);
			// TODO: lots more stuff in here but I'm sick of it tbh
			break;
		}
		}
	}
}

void* JAIBasic::transInitDataFile(u8* buffer, u32 size)
{
	u8* data = (u8*)allocHeap(size);
	if (data != nullptr)
		for (u32 i = 0; i < size; ++i)
			data[i] = buffer[i];

	return data;
}

void JAIBasic::initBankWave()
{
	JASystem::WaveArcLoader::setCurrentDir(JAIGlobalParameter::wavePath);
	JASystem::WaveBankMgr::init(0x100);
	JASystem::WaveArcLoader::init();

	if (unk54) {
		for (int i = 0; unk54[i].unk0; ++i) {
			void* data = unk54[i].unk0;
			if (data) {
				JASystem::WaveBankMgr::registWaveBankWS(i, data);
				unk60[i] = -1;
				unk64[i] = 0;
			}
		}
	}

	if (unk40) {
		for (int i = 0; unk40[i].unk0[0] != 0; ++i) {
			void* data = loadDVDFile(unk40[i].unk0);
			if (data)
				JASystem::WaveBankMgr::registWaveBankWS(i, data);
		}
	}

	JASystem::BankMgr::init(0x100);

	if (unk50) {
		int i;

		for (i = 0; unk50[i].unk0; ++i) {
			void* data = unk50[i].unk0;
			if (data)
				JASystem::BankMgr::registBankBNK(i, data);
		}

		for (i = 0; unk50[i].unk0; ++i)
			JASystem::BankMgr::assignWaveBank(i, unk50[i].unk8);
	}

	if (unk3C) {
		for (int i = 0; unk3C[i].unk0[0] != 0; ++i) {
			void* file = loadDVDFile(unk3C[i].unk0);
			if (file)
				JASystem::BankMgr::registBankBNK(i, file);
			loadGroupWave(i, 0);
		}
	}
}

void JAIBasic::setWaveScene()
{
	if (unk54 && !unk1C.flag3) {
		for (int i = 0; unk54[i].unk0; ++i)
			if (unk54[i].unk8 == 0)
				loadGroupWave(i, 0);

		unk1C.flag1 = true;
	}
}

void JAIBasic::readInitSoundData() { }

void JAIBasic::loadFirstStayWave() { }

void JAIBasic::loadSecondStayWave() { }

void JAIBasic::setSceneSetFinishCallback(s32 param1, s32 param2)
{
	u32 id        = (param1 << 16) + param2;
	unk34         = -1;
	unk64[param1] = 1;
	JASystem::Dvd::checkPassDvdT(id, nullptr, &finishSceneSet);
}

void JAIBasic::finishSceneSet(u32 param)
{
	basic->unk34              = param;
	basic->unk64[param >> 16] = 2;
}

void JAIBasic::loadSceneWave(s32 param1, s32 param2)
{
	if (unk54 && unk54[param1].unk8 == 2 && unk60[param1] != param2) {
		if (unk60[param1] != -1)
			JASystem::WaveBankMgr::eraseWave(param1, unk60[param1]);
		loadGroupWave(param1, param2);
	}
}

bool JAIBasic::checkSceneWaveOnMemory(s32 param1, s32 param2)
{
	if (param2 == unk60[param1] && unk64[param1] == 2)
		return true;
	return false;
}

void JAIBasic::loadGroupWave(s32 param1, s32 param2)
{
	JASystem::WaveBankMgr::loadWave(param1, param2);
	setSceneSetFinishCallback(param1, param2);
	unk60[param1] = param2;
}

void JAIBasic::getWaveGroupNumber(s32 param) { }

void JAIBasic::getWaveLoadStatus(s32 param) { }

void JAIBasic::checkAllWaveLoadStatus() { }

void JAIBasic::initNullData()
{
	JAInullCamera.unk0->x = 0.0f;
	JAInullCamera.unk0->y = 0.0f;
	JAInullCamera.unk0->z = -50.0f;

	JAInullCamera.unk4->x = 0.0f;
	JAInullCamera.unk4->y = 0.0f;
	JAInullCamera.unk4->z = -50.0f;

	Vec up;
	up.x       = 0.0f;
	up.y       = 1.0f;
	up.z       = 0.0f;
	Vec target = JAIConst::dummyZeroVec;
	MTXLookAt(JAIConst::camMtx, JAInullCamera.unk0, &up, &target);
}

void JAIBasic::initDriver(JKRSolidHeap* heap, u32 heapSize, u32 aramSize, u8 param4)
{
	s32 flags = 1;
	if (param4 & 1) {
		flags |= AUDIO_THREAD_FLAG_AUDIO;
	} else if (param4 & 2) {
		flags |= AUDIO_THREAD_FLAG_NEOS;
	}

	SetAudioThreadPriority(2, 3, 3);
	StartAudioThread(heap, heapSize, aramSize, flags);
	Jaq_Reset();
}

void JAIBasic::initInterface(u8 param)
{
	unk12 = param;
	initInterfaceMain();
}

void JAIBasic::initAllocParameter()
{
	mData->initData();
	unk18 = (u8*)allocHeap(JAIGlobalParameter::getParamSeCategoryMax()
	                       * sizeof(*unk18));
	unk28 = (f32*)allocHeap(JAIGlobalParameter::getParamSeCategoryMax()
	                        * sizeof(*unk28));
	unk8  = (JAICamera*)allocHeap(JAIGlobalParameter::audioCameraMax
	                              * sizeof(JAICamera));
	for (int i = 0; i < JAIGlobalParameter::getParamSeCategoryMax(); ++i) {
		unk18[i] = 0;
		unk28[i] = 1.0f;
	}
}

void JAIBasic::initSeqsLoadArea()
{
	for (int i = 0; i < JAIGlobalParameter::autoHeapMax; ++i) {
		mData->mAutoHeap[i].mPointer = allocHeap(JAIGlobalParameter::autoHeapRoomSize);
	}
	mData->mStayHeap->mPointer = allocHeap(JAIGlobalParameter::stayHeapSize);
}

void JAIBasic::setInitFileLoadSwitch(u8 flag) { unk13 = flag; }

void JAIBasic::startFrameInterfaceWork() { processFrameWork(); }

void JAIBasic::processFrameWork()
{
	checkDummyPositionBuffer();

	if (unk38->mState == SOUNDSTATE_Started && !unk1C.flag2 && unk54) {
		for (int i = 0; unk54[i].unk0; ++i)
			if (unk54[i].unk8 == 1)
				loadGroupWave(i, 0);

		unk1C.flag2 = true;
	}

	if (unk38->mState >= SOUNDSTATE_Playing)
		checkNextFrameSe();

	sendPlayingSeCommand();
	checkEntriedSeq();
	checkFadeoutSeq();
	checkStoppedSeq();
	checkSeMovePara();
	checkPlayingSeq();
	checkStartedSeq();
	checkReadSeq();
	checkSeqWave();
	if (!unk1C.flag6)
		checkStream();
	++unk20;
}

void JAIBasic::checkStream()
{
	checkPlayingStream();
	checkRequestStream();
	checkWaitStream();
	checkEntriedStream();
}

void JAIBasic::checkDummyPositionBuffer()
{
	JAIDummyVec* it = mData->mDummyVecUsedHead;
	while (it) {
		JAIDummyVec* next = it->mNext;
		--it->mLifeTime;
		if (it->mLifeTime == 0 || !it->mSound) {
			if (it->mSound)
				it->mSound->stop(0);
			releaseDummyVecPointer(it);
		}
		it = next;
	}
}

void JAIBasic::startSoundVec(u32 id, JAISound** sound, Vec* pos, u32 param1,
                             u32 param2, u8 param3)
{
}

void JAIBasic::startSoundVecReturnHandle(u32 id, Vec* pos, u32 param1,
                                         u32 param2, u8 param3)
{
}

void JAIBasic::startSoundActor(u32 id, JAISound** sound, JAIActor* actor,
                               u32 param, u8 flag)
{
	u32 format = getInfoFormat(getInfoPointerFromID(id), id);
	if (format & 1)
		startSoundIndirectID(id, sound, actor, param, flag);
	else
		startSoundDirectID(id, sound, actor, param, flag);
}

JAISound* JAIBasic::startSoundActorReturnHandle(u32 id, JAIActor* actor,
                                                u32 param, u8 flag)
{
	JAISound* sound = nullptr;
	startSoundActor(id, &sound, actor, param, flag);
	JAISound* result = sound;
	if (result)
		sound->release();
	return result;
}

void JAIBasic::startSoundDirectID(u32 id, JAISound** sound, JAIActor* actor,
                                  u32 param, u8 flag)
{
	void* ptr;
	mData->getInfoPointer(id, &ptr);
	if (ptr)
		startSoundBasic(id, sound, actor, param, flag, ptr);
}

void JAIBasic::startSoundIndirectID(u32 id, JAISound** sound, JAIActor* actor,
                                    u32 param, u8 flag)
{
	void* ptr;
	mData->getInfoPointer(id, &ptr);
	if (ptr)
		startSoundBasic((id & 0xFFFFFC00) + *(u16*)((u8*)ptr + 6), sound, actor,
		                param, flag, ptr);
}

void JAIBasic::startSoundBasic(u32 id, JAISound** sound, JAIActor* actor,
                               u32 param, u8 flag, void* data)
{
	switch (id & 0xC0000000) {
	case -0x80000000:
		if (unk1C.flag4 != 1
		    && (unk38 == nullptr || (unk38->mSoundID & 0x3ff) != (id & 0x3ff))) {
			if (sound == nullptr) {
				u8 num = getSeqTrackNumber(data);
				sound  = &mData->mDefaultSeqHandle[num];
			}

			mData->unk1FC.storeBuffer(sound, actor, id, param, flag, data);
		}
		break;

	case 0:
		if (unk18[id >> 12] == 0) {
			mData->unk200.storeBuffer(sound, actor, id, param, flag, data);
		} else if (sound != nullptr) {
			*sound = nullptr;
		}
		break;

	case 0xC0000000:
			mData->unk204.storeBuffer(sound, actor, id, param, flag, data);
		break;
	}
}

void JAIBasic::getPlayingSoundHandle(JAISound** sound, u32 param) { }

#pragma dont_inline on
void JAIBasic::stopSoundHandle(JAISound* sound, u32 param)
{
	if (sound) {
		switch (sound->mSoundID & 0xC0000000) {
		case -0x80000000:
			if (sound->mState < 4 || param == 0) {
				if (sound->mState >= 3)
					Jaq_StopSeq(sound->getSeqParameter()->mSeqHandle);
				else if (sound->mState >= 1)
					mData->releaseAutoHeapPointer(
					    sound->getSeqParameter()->mAutoHeapPosition);

				sound->clearMainSoundPPointer();
				stopSeq(sound);
			} else {
				mData->mSeqTrackInfo[sound->mTrack].unk8 |= 0x2;
				mData->mSeqTrackInfo[sound->mTrack].mSound->mFadeCounter = param;
			}
			break;

		case 0:
			if (sound->mState) {
				if (param == 0 || sound->mState == 1) {
					releaseSeRegist(sound);
				} else {
					sound->mFadeCounter = param;
					sound->setSeInterVolume(6, 0.0f, param, 0);
				}
			}
			break;

		case 0xC0000000:
			if (param == 0) {
				JAInter::StreamLib::stop();
				sound->mState         = 0;
				mData->mStreamUpdate->mSound = nullptr;
				sound->clearMainSoundPPointer();
				releaseStreamParameterPointer(
				    (JAIStreamParameter*)sound->mCustomParameter);
				releaseControllerHandle(&mData->mStreamControlBuffer, sound);
				DVDT_UnPause();

			} else {
				if (sound->getStreamParameter()->mUpdateData != nullptr) {
					sound->getStreamParameter()->mUpdateData->mActiveTrackFlag |= 0x2;
					sound->mFadeCounter = param;
				}
			}
			break;
		}
	}
}
#pragma dont_inline off

u32 JAIBasic::changeIDToCategory(u32 id) { return id >> 0xc & 0xff; }

void JAIBasic::stopPlayingObjectSe(void* obj) { }

void JAIBasic::stopPlayingIDObjectSe(u32 id, void* obj) { }

void JAIBasic::stopPlayingCategorySe(u8 category) { }

void JAIBasic::stopPlayingCategoryObjectSe(u8 category, void* obj) { }

void JAIBasic::stopAllSe(void* obj) { }

void JAIBasic::stopAllSe(u8 param)
{
	JAISound* sound = mData->mSeRegist[param].mUsedHead;
	while (sound) {
		JAISound* next = sound->mNextSound;
		stopSoundHandle(sound, 0);
		sound = next;
	}
}

void JAIBasic::stopAllSe(u8 param, void* obj) { }

void JAIBasic::stopAllSeq(void* obj) { }

void JAIBasic::stopAllStream(void* obj) { }

void JAIBasic::stopActorSoundOneBuffer(void* actor, JAISound* sound) { }

void JAIBasic::stopIDSoundOneBuffer(u32 id, JAISound* sound) { }

void JAIBasic::stopIDActorSoundOneBuffer(u32 id, void* actor, JAISound* sound)
{
}

void JAIBasic::stopAllSound(void* obj) { }

void JAIBasic::getPlayingSoundLinkHeadPointer(u32 param) { }

void JAIBasic::stopAllSound(u32 param) { }

void JAIBasic::stopAllSound(u32 param, void* obj) { }

void JAIBasic::deleteObject(void* obj) { }

void JAIBasic::releaseSoundHandle(JAISound* sound) { }

JAISound* JAIBasic::getControllerHandle(JAILinkBuffer* buffer)
{
	JAISound** var2 = &buffer->mUsedHead;
	if (buffer->mFreeHead) {
		JAISound* var1 = buffer->mFreeHead;
		buffer->mFreeHead   = var1->mNextSound;
		if (*var2) {
			var1->mNextSound    = *var2;
			(*var2)->mPrevSound = var1;
		} else {
			var1->mNextSound = nullptr;
		}
		var1->mPrevSound = nullptr;
		*var2       = var1;
		var1->mCustomParameter = nullptr;
		return var1;
	}
	return nullptr;
}

void JAIBasic::releaseControllerHandle(JAILinkBuffer* buffer, JAISound* sound)
{
	JAISound** ptr = &buffer->mUsedHead;

	sound->mCustomParameter = nullptr;
	sound->mMainSoundPPointer = nullptr;
	if (buffer->mUsedHead != sound) {
		sound->mPrevSound->mNextSound = sound->mNextSound;
		if (sound->mNextSound)
			sound->mNextSound->mPrevSound = sound->mPrevSound;
	} else {
		*ptr = sound->mNextSound;
		if (sound->mNextSound)
			sound->mNextSound->mPrevSound = nullptr;
	}
	sound->mNextSound = buffer->mFreeHead;
	sound->mNextSound->mPrevSound = sound;
	buffer->mFreeHead = sound;
}

JAIStreamParameter* JAIBasic::getStreamParameter()
{
	JAIStreamParameter* var1;
	JAIStreamParameter** var2;

	var2 = &mData->mStreamParameterUsedHead;
	if (mData->mStreamParameterFreeHead->mNext != nullptr) {
		var1         = mData->mStreamParameterFreeHead;
		mData->mStreamParameterFreeHead = var1->mNext;
		if (*var2 != nullptr) {
			var1->mNext    = *var2;
			(*var2)->mPrev = var1;
		} else {
			var1->mNext = nullptr;
		}
		var1->mPrev = nullptr;
		*var2        = var1;
		return var1;
	}
	return nullptr;
}

void JAIBasic::releaseStreamParameterPointer(JAIStreamParameter* param)
{
	JAIStreamParameter** start = &mData->mStreamParameterUsedHead;
	JAIStreamParameter** end   = &mData->mStreamParameterFreeHead;

	if (*start != param) {
		param->mPrev->mNext = param->mNext;
		if (param->mNext)
			param->mNext->mPrev = param->mPrev;
	} else {
		*start = param->mNext;
		if (param->mNext)
			param->mNext->mPrev = nullptr;
	}
	param->mNext = *end;
	if (param->mNext)
		param->mNext->mPrev = param;
	*end = param;
}

JAISeqParameter* JAIBasic::getSeqParametermeterPointer()
{
	JAISeqParameter** var2 = &mData->mSeqParameterUsedHead;
	if (mData->mSeqParameterFreeHead->mNext) {
		JAISeqParameter* var1 = mData->mSeqParameterFreeHead;
		mData->mSeqParameterFreeHead          = var1->mNext;
		if (*var2) {
			var1->mNext    = *var2;
			(*var2)->mPrev = var1;
		} else {
			var1->mNext = nullptr;
		}
		var1->mPrev = nullptr;
		*var2         = var1;
		return var1;
	}
	return nullptr;
}

void JAIBasic::releaseSeqParameterPointer(JAISeqParameter* param)
{
	JAISeqParameter** start = &mData->mSeqParameterUsedHead;
	JAISeqParameter** end   = &mData->mSeqParameterFreeHead;

	if (*start != param) {
		param->mPrev->mNext = param->mNext;
		if (param->mNext)
			param->mNext->mPrev = param->mPrev;
	} else {
		*start = param->mNext;
		if (param->mNext)
			param->mNext->mPrev = nullptr;
	}
	param->mNext = *end;
	if (param->mNext)
		param->mNext->mPrev = param;
	*end = param;
}

JAISeParameter* JAIBasic::getSeParametermeterPointer()
{
	JAISeParameter* var1;
	JAISeParameter** var2 = &mData->mSeParameterUsedHead;
	if (mData->mSeParameterFreeHead) {
		var1         = mData->mSeParameterFreeHead;
		mData->mSeParameterFreeHead = var1->mNext;
		if (*var2 != nullptr) {
			var1->mNext    = *var2;
			(*var2)->mPrev = var1;
		} else {
			var1->mNext = nullptr;
		}
		var1->mPrev = nullptr;
		*var2        = var1;
		mData->initSePara(var1);
	} else {
		var1 = nullptr;
	}
	return var1;
}

void JAIBasic::releaseSeParameterPointer(JAISeParameter* param)
{
	if (!param)
		return;

	JAISeParameter** start = &mData->mSeParameterUsedHead;
	JAISeParameter** end   = &mData->mSeParameterFreeHead;

	if (*start != param) {
		param->mPrev->mNext = param->mNext;
		if (param->mNext)
			param->mNext->mPrev = param->mPrev;
	} else {
		*start = param->mNext;
		if (param->mNext)
			param->mNext->mPrev = nullptr;
	}
	param->mNext = *end;
	if (param->mNext)
		param->mNext->mPrev = param;
	*end = param;
}

void JAIBasic::getDummyVecPointer() { }

void JAIBasic::releaseDummyVecPointer(JAIDummyVec* vec)
{
	JAIDummyVec** start = &mData->mDummyVecUsedHead;
	JAIDummyVec** end   = &mData->mDummyVecFreeHead;

	if (*start != vec) {
		vec->mPrev->mNext = vec->mNext;
		if (vec->mNext)
			vec->mNext->mPrev = vec->mPrev;
	} else {
		*start = vec->mNext;
		if (vec->mNext)
			vec->mNext->mPrev = nullptr;
	}
	vec->mNext = *end;
	if (vec->mNext)
		vec->mNext->mPrev = vec;
	*end = vec;
}

void JAIBasic::getGameFrameCounter() { }

void JAIBasic::setPauseFlagAll(u8 flag) { }

void JAIBasic::checkPlayingSoundTrack(u32 param) { }

void JAIBasic::changeSoundScene(u32 scene) { }

BOOL JAIBasic::getMapInfoFxline(u32 param)
{
	if (!param)
		return 0;
	else
		return 1;
}

u32 JAIBasic::getMapInfoGround(u32 param)
{
	if (!param)
		return 0;
	else
		return 1;
}

f32 JAIBasic::getMapInfoFxParameter(u32 param)
{
	if (!param)
		return 0.0f;
	else
		return 1.0f;
}

void JAIBasic::allocDvdBuffer(u8* buffer, u32 param1, u32 param2) { }

void JAIBasic::deallocDvdBuffer(u8* buffer) { }

void JAIBasic::getSeInfoMode() { }

void JAIBasic::getSeInfoStartPointer() { }

void JAIBasic::getSeInfoCategoryMax() { }

JAISoundTable* JAIBasic::getInfoPointerFromID(u32 id)
{
	static JAISoundTable* _dinfo;
	if (mData->mSeparateSoundTables == 0) {
		_dinfo = &mData->mSeTable;
	} else {
		switch (id & 0xC0000000) {
		case 0x00000000:
			_dinfo = &mData->mSeTable;
			break;
		case 0x80000000:
		_dinfo = &mData->mSeqTable;
			break;
		case 0xC0000000:
			_dinfo = &mData->mStreamTable;
			break;
		}
	}
	return _dinfo;
}

u32 JAIBasic::getInfoFormat(JAISoundTable* table, u32 id)
{
	u32 result = 0;
	switch (id & 0xC0000000) {
	case 0x00000000:
		result = ((u8*)table->mData)[0];
		break;
	case 0x80000000:
		result = ((u8*)table->mData)[1];
		break;
	case 0xC0000000:
		result = ((u8*)table->mData)[2];
		break;
	}
	return result;
}

void JAIBasic::setSeCancelSwitch(u8 param1, u8 param2) { }

void JAIBasic::setSeCategoryVolume(u8 category, u8 volume)
{
	unk28[category] = volume / 127.0f;
}

u16 JAIBasic::setParameterSeqSync(seqp_* param_1, u16 param_2)
{
	u16 result = 0;

	switch (param_2) {
	case 0:
		for (int i = 0; i < JAIGlobalParameter::seqPlayTrackMax; ++i) {
			if (basic->mData->mSeqTrackInfo[i].mSound == nullptr)
				continue;

			seqp_* track = Jaq_HandleToSeq(basic->mData->mSeqTrackInfo[i].mSound->getSeqParameter()->mSeqHandle);

			if (track != param_1->parent)
				continue;

			u32 route = basic->routeToTrack(param_1->trackId);
			JAISoundInfo* info
			    = basic->getSoundInfoFromID(basic->mData->mSeqTrackInfo[i].mSound->mSoundID);

			JAISystemInterface::outerInit(&basic->mData->mSeqTrackInfo[i], param_1,
			                              route, info->mSwBit >> 8, param_2 & 1);
			result = 0;
			basic->mData->mSeqTrackInfo[i].mTrackInitFlags |= 1 << route;
			i = JAIGlobalParameter::seqPlayTrackMax;
		}
		break;
	case 1: {
		u32 uVar8                            = param_1->trackId;
		OuterParam_* outer = param_1->outerParams;
		JAIData::FabricatedSeTrackParameter* params
		    = &basic->mData->unk0[uVar8 & 0xff];

		Jam_SetExtParam(params->mVolume, param_1, 1);
		Jam_SetExtParam(params->mPan, param_1, 8);
		Jam_SetExtParam(params->mPitch, param_1, 2);
		Jam_SetExtParam(params->mFxmix, param_1, 4);

		f32 thing;
		if (basic->mSoundOutputMode != 2)
			thing = 0.0f;
		else
			thing = params->mDolby;
		Jam_SetExtParam(thing, param_1, 16);
		break;
	case 0x7F:
	{
		break;
	}
	}
	}
	return result;
}

JAISoundInfo* JAIBasic::getSoundInfoFromID(u32 id)
{
	static JAISoundInfo* _info;
	mData->getInfoPointer(id, (void**)&_info);
	return _info;
}

u8 JAIBasic::getSeqTrackNumber(void* param)
{
	return ((JAISoundInfo*)param)->mTrackNumber;
}

u8 JAIBasic::getSoundPrioity(void* param)
{
	return ((JAISoundInfo*)param)->mPriority;
}

u32 JAIBasic::getSoundSwBit(void* param)
{
	return ((JAISoundInfo*)param)->mSwBit;
}

void JAIBasic::setSeExtParameter(JAISound* sound)
{
	if (!sound)
		return;
	JAISoundTable* table = getInfoPointerFromID(sound->mSoundID);
	u8 format            = getInfoFormat(table, sound->mSoundID);

	if (format & 4)
		sound->setVolume(((JAISoundInfo*)sound->mInfo)->mVolume / 127.0f, 0, 1);
	if (format & 8)
		sound->setFxmix(((JAISoundInfo*)sound->mInfo)->mFxmix / 127.0f, 0, 1);
	if (format & 2)
		sound->setPitch(((JAISoundInfo*)sound->mInfo)->mPitch, 0, 1);
}

u32 JAIBasic::routeToTrack(u32 param)
{
	u32 uVar2 = 0;
	if ((param & 0xf0000000) == 0x00000000)
		return 0;
	if ((param & 0xf0000000) == 0x10000000)
		uVar2 = 0xf;
	else if ((param & 0xf0000000) == 0x20000000)
		uVar2 = 0xff;
	return param & uVar2;
}

void JAIBasic::initHeap()
{
	u8* heap = (u8*)OSAlloc2(JAIGlobalParameter::interfaceHeapSize);
	Nas_HeapInit(mInterfaceHeap, heap, JAIGlobalParameter::interfaceHeapSize);

	mMotherHeap = static_cast<jaheap_*>(allocHeap(sizeof(jaheap_)));

	if (JAIGlobalParameter::motherHeapSize != 0) {
		Jac_InitMotherHeap(mMotherHeap, (u32)ARAlloc2(JAIGlobalParameter::motherHeapSize), JAIGlobalParameter::motherHeapSize, 0);
	}
}

void* JAIBasic::allocHeap(u32 size)
{
	return Nas_HeapAlloc(mInterfaceHeap,  size);
}

JAISound* JAIBasic::makeSound(u32 param)
{
	if (unkC)
		return new (unkC, 0) JAISound[param];
	else
		return new (JASDram, 0) JAISound[param];
}

void* JAIBasic::loadDVDFile(char* filename)
{
	u32 size = Jac_CheckFile(filename);
	if (!size) {
		return nullptr;
	} else {
		void* result = allocHeap(size);
		Jac_LoadFile(filename, (u8*)result);
		return result;
	}
}

void JAIBasic::loadTmpDVDFile(char* filename, u8** buffer)
{
	u32 size = JASystem::Dvd::checkFile(filename);
	if (!size) {
		*buffer = nullptr;
	} else {
		*buffer = (u8*)JASDram->alloc(size, ~0x1F);
		JASystem::Dvd::loadFile(filename, *buffer);
	}
}

void JAIBasic::deleteTmpDVDFile(u8** buffer)
{
	if (*buffer)
		JASDram->freeTail();
}

void JAIBasic::allocStreamBuffer(void* buffer, s32 size) { }

void JAIBasic::deallocStreamBuffer() { }

int JAIBasic::loadArcSeqData(u32 param_1)
{
	u32 uVar1   = param_1 & 0x3ff;
	u32 uVar2   = JV_CheckSize(uVar1);
	void* iVar3 = mData->checkOnMemory(uVar1, nullptr);

	u32 uVar6 = getSoundInfoFromID(param_1)->mSwBit;

	if (iVar3 == 0) {
		u8 unaff_r28;
		if ((uVar6 & 0x10) != 0) {
			iVar3    = mData->getFreeStayHeapPointer(uVar2, uVar1);
			unaff_r28 = 0xff;
		}

		if ((iVar3 == nullptr) || ((uVar6 & 0x20) != 0)) {
			unaff_r28 = mData->checkUsefulAutoHeapPosition();

			if (unaff_r28 >= JAIGlobalParameter::autoHeapMax)
				return 0xffffffff;

			if (uVar2 >= 0xC000)
				return 0xffffffff;

			iVar3 = (u8*)mData->getFreeAutoHeapPointer(unaff_r28, uVar1);
		}

		if ((uVar6 & 0x40) == 0) {
			mData->setAutoHeapLoadedFlag(unaff_r28, '\x01');
			u32 id =  0xFF | uVar1 << 16 | unaff_r28 << 8;
			JV_LoadFile_Async2(unk2C + uVar1, (u8*)iVar3, 0, uVar2,
			                               &checkDvdLoadArc, id);
			return 1;
		} else {
			JV_LoadFile(unk2C + uVar1, (u8*)iVar3, 0, uVar2);
			return 2;
		}
	}
	return 0;
}
