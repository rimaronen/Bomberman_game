#pragma once
#include <SFML/Audio.hpp>
#include "GameResources.h"

class Sound
{
public:
	//C-ctor
	Sound(sf::SoundBuffer & buffer);
	//D-ctor
	~Sound();
	//play the sound
	virtual void play();
	//stop the sound
	void stop();
	void pause();
	void loop();


protected:
	bool isPlaying();
private:

	sf::Sound m_sound;
	bool m_isPlaying = false;
};

