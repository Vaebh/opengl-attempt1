#include "Sound.h"

Sound::Sound(const std::string& inFilename, FMOD::System* inFMODSystem, FMOD::ChannelGroup* inChannelGroup) : mFMODSystem(inFMODSystem)
{
	AudioSystem::FMODErrorCheck(mFMODSystem->createSound(inFilename.c_str(), FMOD_DEFAULT, 0, &mSound));
	AudioSystem::FMODErrorCheck(mFMODSystem->playSound(mSound, NULL, true, &mChannel));

	mChannel->setChannelGroup(inChannelGroup);
}

Sound::~Sound()
{

}

void Sound::PlaySound()
{
	if(!IsSoundPlaying())
	{
		AudioSystem::FMODErrorCheck(mFMODSystem->playSound(mSound, NULL, false, &mChannel));
	}
}

bool Sound::IsSoundPlaying()
{
	bool isPlaying;
	AudioSystem::FMODErrorCheck(mChannel->isPlaying(&isPlaying));

	bool isPaused;
	AudioSystem::FMODErrorCheck(mChannel->getPaused(&isPaused));

	return isPlaying && !isPaused;
}

bool Sound::IsSoundEnabled()
{
	bool isMuted;
	AudioSystem::FMODErrorCheck(mChannel->getMute(&isMuted));

	return isMuted;
}