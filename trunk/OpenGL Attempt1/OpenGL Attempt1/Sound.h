#include "AudioSystem.h"

class Sound
{
public:
	Sound(const std::string& inFilename);
	~Sound();

	bool IsSoundPlaying();
	bool IsSoundEnabled();

private:
	FMOD::Channel* mChannel;
};