#include "Sound.h"

Sound::Sound(const std::string& inFilename) : mChannel(NULL)
{

}

Sound::~Sound()
{

}

bool Sound::IsSoundEnabled()
{
	bool* isMuted;
	AudioSystem::FMODErrorCheck(mChannel->getMute(isMuted));

	if(isMuted)
	{
		return *isMuted;
	}

	return false;
}