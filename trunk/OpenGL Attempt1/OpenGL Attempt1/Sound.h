#include "AudioSystem.h"

class Sound
{
public:
	Sound(const std::string& inFilename, FMOD::System* inFMODSystem, FMOD::ChannelGroup* inChannelGroup);
	~Sound();

	void PlaySound();

	bool IsSoundPlaying();
	bool IsSoundEnabled();

private:
	FMOD::Sound* mSound;
	FMOD::Channel* mChannel;
	FMOD::System* mFMODSystem;
};