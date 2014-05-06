#include "AudioSystem.h"
#include <iostream>

AudioSystem::AudioSystem() : mNumDrivers(0), mSystem(NULL)
{

}

AudioSystem::~AudioSystem()
{
	mSystem->release();
}

void AudioSystem::Initialise()
{
	FMODErrorCheck(FMOD::System_Create(&mSystem));

	CheckSoundcards();
}

void AudioSystem::PlaySound(const std::string& inSoundName)
{
	FMOD::Sound *soundEffect;

	bool* isPlaying;
	soundFXChannel->isPlaying(isPlaying);
	if(FMODErrorCheck(mSystem->createSound(inSoundName.c_str() , FMOD_DEFAULT, 0, &soundEffect)))
	{
		FMODErrorCheck(mSystem->playSound(soundEffect, NULL, false, &soundFXChannel));
	}
}

void AudioSystem::CheckSoundcards()
{
	FMODErrorCheck(mSystem->getNumDrivers(&mNumDrivers));

	// No sound cards (disable sound)
	if (mNumDrivers == 0)
	{
		FMODErrorCheck(mSystem->setOutput(FMOD_OUTPUTTYPE_NOSOUND));
	}
}

bool AudioSystem::FMODErrorCheck(FMOD_RESULT inResult)
{
	if (inResult != FMOD_OK)
    {
        std::cout << "FMOD error! (" << inResult << ") " << FMOD_ErrorString(inResult) << std::endl;
    }
}