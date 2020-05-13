#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

// This singleton will provide game resources. we don't want textures sounds and fonts to be
// loaded more than once after all...
class GameResources
{
public:
	static GameResources& instance(); // provide instance via a special function that will always provide the same instance

	GameResources(const GameResources& other) = delete; // prevent instantiation by copying
	GameResources& operator=(const GameResources& other) = delete; // prevent instantiation by assignment

	sf::Texture & getRobotTexture();
	sf::Texture & getSimpleGuardTexture();
	sf::Texture & getCleverGuardTexture();
	sf::Texture & getRockTexture();
	sf::Texture & getWallTexture();
	sf::Texture & getDoorTexture();
	sf::Texture & getLifeFullTexture();
	sf::Texture & getLifeEmptyTexture();
	sf::Texture & getBombTexture();
	sf::Texture & getBombIconTexture();
	sf::Texture & getExplosionTexture();
	sf::Texture & getExplosionIconTexture();
	sf::Texture & getCoinTexture();
	sf::Texture & getBombBonusTexture();
	sf::Texture & getSpeedBonusTexture();
	sf::Texture & getLifeTexture();

	sf::Font & getCbFont();
	sf::SoundBuffer & getBgGameBuffer();
	sf::SoundBuffer & getRobotDieBuffer();
	sf::SoundBuffer & geAlarmBuffer();
	sf::SoundBuffer & getExplosionBuffer();
	sf::SoundBuffer & getBombBuffer();
	sf::SoundBuffer & getRunBuffer();
	sf::SoundBuffer & getMenuMusicBuffer();

private:
	GameResources(); // prevent public access to the constructor

	std::unique_ptr <sf::Texture> m_lifeTexture = std::make_unique<sf::Texture>();
	std::unique_ptr <sf::Texture> m_bombBonusTexture = std::make_unique<sf::Texture>();
	std::unique_ptr <sf::Texture> m_coinTexture = std::make_unique<sf::Texture>();
	std::unique_ptr <sf::Texture> m_robotTexture = std::make_unique<sf::Texture>();
	std::unique_ptr <sf::Texture> m_simpleGuardTexture = std::make_unique<sf::Texture>();
	std::unique_ptr <sf::Texture> m_cleverGuardTexture = std::make_unique<sf::Texture>();
	std::unique_ptr <sf::Texture> m_rockTexture = std::make_unique<sf::Texture>();
	std::unique_ptr <sf::Texture> m_wallTexture = std::make_unique<sf::Texture>();
	std::unique_ptr <sf::Texture> m_doorTexture = std::make_unique<sf::Texture>();
	std::unique_ptr <sf::Texture> m_lifeFullTexture = std::make_unique<sf::Texture>();
	std::unique_ptr <sf::Texture> m_lifeEmptyTexture = std::make_unique<sf::Texture>();
	std::unique_ptr <sf::Texture> m_bombTexture = std::make_unique<sf::Texture>();
	std::unique_ptr <sf::Texture> m_bombIconTexture = std::make_unique<sf::Texture>();
	std::unique_ptr <sf::Texture> m_explosionTexture = std::make_unique<sf::Texture>();
	std::unique_ptr <sf::Texture> m_explosionIconTexture = std::make_unique<sf::Texture>();
	std::unique_ptr <sf::Texture> m_speedTexture = std::make_unique <sf::Texture>();
	std::unique_ptr <sf::Font> m_cbFont = std::make_unique<sf::Font>();
	std::unique_ptr <sf::SoundBuffer> m_explosionBuffer = std::make_unique<sf::SoundBuffer>();
	std::unique_ptr <sf::SoundBuffer> m_menuBuffer = std::make_unique<sf::SoundBuffer>();
	std::unique_ptr <sf::SoundBuffer> m_bombBuffer = std::make_unique<sf::SoundBuffer>();
	std::unique_ptr <sf::SoundBuffer> m_playerRunBuffer = std::make_unique<sf::SoundBuffer>();
	std::unique_ptr <sf::SoundBuffer> m_alarmBuffer = std::make_unique<sf::SoundBuffer>();
	std::unique_ptr <sf::SoundBuffer> m_bgGameBuffer = std::make_unique<sf::SoundBuffer>();
	std::unique_ptr <sf::SoundBuffer> m_robotDieBuffer = std::make_unique<sf::SoundBuffer>();
};

