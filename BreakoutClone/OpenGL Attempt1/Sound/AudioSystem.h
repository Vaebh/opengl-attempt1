#ifndef AUDIO_SIMENGINE
#define AUDIO_SIMENGINE

#include <fmod.hpp>
#include <fmod_errors.h>
#include <string>

class AudioSystem
{
public:
	AudioSystem();
	~AudioSystem();

	void Initialise();

	void Update(float inDT);

	void PlaySound(const std::string& inSoundName);

	static bool FMODErrorCheck(FMOD_RESULT inResult);

private:
	void CheckSoundcards();

private:
	FMOD::System* mSystem;

	FMOD::ChannelGroup* mMusicChannelGroup;
	FMOD::ChannelGroup* mSoundFXChannelGroup;

	int mNumDrivers;
};

#endif