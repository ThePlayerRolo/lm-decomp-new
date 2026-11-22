#include <JSystem/JAudio/JAInterface/JAISystemInterface.hpp>
#include <JSystem/JAudio/JAInterface/JAISound.hpp>
#include <JSystem/JAudio/JAInterface/JAIGlobalParameter.hpp>
#include <JSystem/JAudio/JAInterface/JAIParameters.hpp>
#include <jaudio/jammain_2.h>
#include <jaudio/seqsetup.h>
#include <jaudio/dvdthread.h>
#include <jaudio/cmdstack.h>
#include <dolphin/types.h>

BOOL JAISystemInterface::checkFileExsistence(char* path)
{
	char fullPath[64];
	DVDT_ExtendPath(fullPath, path);
	if (DVDConvertPathToEntrynum(fullPath) != -1)
		return true;
	else
		return false;
}

BOOL JAISystemInterface::checkSeqActiveFlag(u32 seq_handle)
{
	seqp_* rootTrack = Jaq_HandleToSeq(seq_handle);

	if (rootTrack != 0
	    && rootTrack->trackState != 0) {
		if (rootTrack->children[0] || rootTrack->children[1]
		    || rootTrack->children[2] || rootTrack->children[3]
		    || rootTrack->children[4] || rootTrack->children[5]
		    || rootTrack->children[6] || rootTrack->children[7]
		    || rootTrack->children[8] || rootTrack->children[9]
		    || rootTrack->children[10] || rootTrack->children[11]
		    || rootTrack->children[12] || rootTrack->children[13]
		    || rootTrack->children[14] || rootTrack->children[15]) {
			return rootTrack->trackState;
		} else {
			return false;
		}
	}
	return false;
}

seqp_* JAISystemInterface::trackToSeqp(JAISound* sound, u8 track_no)
{
	seqp_* result = nullptr;
	if (sound->mSoundID & JAISoundID_SeqTwoLevelTracks) {
		seqp_* rootTrack = Jaq_HandleToSeq(
		    sound->getSeqParameter()->mSeqHandle);
		if (rootTrack->children[track_no >> 4])
			result
			    = rootTrack->children[track_no >> 4]->children[track_no & 0xF];
	} else {
		seqp_* rootTrack = Jaq_HandleToSeq(
		    sound->getSeqParameter()->mSeqHandle);
		result = rootTrack->children[track_no & 0xF];
	}
	return result;
}

void JAISystemInterface::setSeqPortargsF32(JAISeqUpdateData* update_data,
                                           u32 player_index, u8 arg_index,
                                           f32 value)
{
	update_data->mPlayerParams[player_index].mArgsAsF32[arg_index] = value;
}

void JAISystemInterface::setSeqPortargsU32(JAISeqUpdateData* update_data,
                                           u32 player_index, u8 arg_index,
                                           u32 value)
{
	update_data->mPlayerParams[player_index].mArgsAsU32[arg_index] = value;
}

JAISeqParameter* JAISystemInterface::rootInit(JAISeqUpdateData* update_data)
{
	JAISound* sound = update_data->mSound;
	seqp_* rootTrack
	    = Jaq_HandleToSeq(sound->getSeqParameter()->mSeqHandle);
	outerInit(update_data, rootTrack, JAIGlobalParameter::seqTrackMax,
	          0xffff, 0);
	return sound->getSeqParameter();
}

void JAISystemInterface::trackInit(JAISeqUpdateData* update_data)
{
	JAISound* sound = update_data->mSound;
	u32 trackCount  = 0x10;
	if (sound->mSoundID & JAISoundID_SeqTwoLevelTracks)
		trackCount = JAIGlobalParameter::seqTrackMax;

	for (u32 trackNo = 0; trackNo < trackCount; ++trackNo)
		if (!(update_data->mTrackInitFlags & (1 << trackNo))) {
			seqp_* track = trackToSeqp(sound, trackNo);
			outerInit(update_data, track, trackNo, 0xffff, 0);
		}
}
