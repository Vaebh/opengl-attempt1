#include <fmod.hpp>
#include <fmod_errors.h>
#include <string>

class AudioSystem
{
public:
	AudioSystem();
	~AudioSystem();
	void PlaySound(const std::string& inSoundName);

private:
	void Initialise();
	bool FMODErrorCheck(FMOD_RESULT inResult);
	void CheckSoundcards();

private:
	FMOD::System* mSystem;

	FMOD::Channel* musicChannel;
	FMOD::Channel* soundFXChannel;

	int mNumDrivers;
};