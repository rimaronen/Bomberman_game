#include "Sound.h"



Sound::Sound(sf::SoundBuffer & buffer)
{
	m_sound.setBuffer(buffer);
}

Sound::~Sound()
{
}

void Sound::play()
{
	if (!m_isPlaying) {
		m_sound.play();
		m_isPlaying = true;
		m_sound.setVolume(100);//set the volume
	}
}

void Sound::stop()
{
	m_sound.stop(); //stop the sound
	m_isPlaying = false;
	m_sound.setLoop(false);
}

void Sound::pause()
{
	m_sound.pause(); //pause the sound 
	m_isPlaying = false;
}

void Sound::loop()
{
	m_sound.setLoop(true);
}


bool Sound::isPlaying()
{
	return m_isPlaying;
}
