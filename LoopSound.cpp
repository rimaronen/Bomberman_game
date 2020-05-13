#include "LoopSound.h"

void LoopSound::play()
{
	Sound::play();
	loop();
}
