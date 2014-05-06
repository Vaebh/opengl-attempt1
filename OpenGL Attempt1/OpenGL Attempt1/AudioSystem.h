#include <fmod.hpp>
#include <fmod_errors.h>
#include <string>

class AudioSystem
{
public:
	AudioSystem();
	~AudioSystem();
	void PlaySound(const std::string& inSoundName);

	static bool FMODErrorCheck(FMOD_RESULT inResult);

private:
	void Initialise();
	
	void CheckSoundcards();

private:
	FMOD::System* mSystem;

	FMOD::Channel* musicChannel;
	FMOD::Channel* soundFXChannel;

	int mNumDrivers;
};