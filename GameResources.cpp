#include "GameResources.h"

// c-tor
GameResources::GameResources()
{
	if (!m_lifeTexture->loadFromFile("img/heart1.png"))
		exit(EXIT_FAILURE);
	if (!m_speedTexture->loadFromFile("img/thunder.png"))
		exit(EXIT_FAILURE);
	if (!m_bombBonusTexture->loadFromFile("img/bombbonus.png"))
		exit(EXIT_FAILURE);
	if (!m_coinTexture->loadFromFile("img/Coins.png"))
		exit(EXIT_FAILURE);
	if (!m_robotTexture->loadFromFile("img/guard1.png"))
		exit(EXIT_FAILURE);
	if (!m_simpleGuardTexture->loadFromFile("img/guard4.png"))
		exit(EXIT_FAILURE);
	if (!m_cleverGuardTexture->loadFromFile("img/guard2.png"))
		exit(EXIT_FAILURE);
	if (!m_doorTexture->loadFromFile("img/door.png"))
		exit(EXIT_FAILURE);
	if (!m_rockTexture->loadFromFile("img/rock.png"))
		exit(EXIT_FAILURE);
	if (!m_wallTexture->loadFromFile("img/newwall2.jpg"))
		exit(EXIT_FAILURE);
	if (!m_lifeFullTexture->loadFromFile("img/life_full.png"))
		exit(EXIT_FAILURE);
	if (!m_lifeEmptyTexture->loadFromFile("img/life_empty.png"))
		exit(EXIT_FAILURE);
	if (!m_bombTexture->loadFromFile("img/bomb.png"))
		exit(EXIT_FAILURE);
	if (!m_bombIconTexture->loadFromFile("img/bomb_icon.png"))
		exit(EXIT_FAILURE);
	if (!m_explosionTexture->loadFromFile("img/floorexplosion.png"))
		exit(EXIT_FAILURE);
	if (!m_explosionIconTexture->loadFromFile("img/explosion_icon.png"))
		exit(EXIT_FAILURE);
	if (!m_cbFont->loadFromFile("font/real-politik/realpolitik.ttf"))
		exit(EXIT_FAILURE);
	if(!m_explosionBuffer->loadFromFile("sound/bombexplosion.wav"))
		exit(EXIT_FAILURE);
	if (!m_bombBuffer->loadFromFile("sound/bombfuse.wav"))
		exit(EXIT_FAILURE);
	if (!m_playerRunBuffer->loadFromFile("sound/run.wav"))
		exit(EXIT_FAILURE);
	if (!m_alarmBuffer->loadFromFile("sound/alarm.wav"))
		exit(EXIT_FAILURE);
	if (!m_bgGameBuffer->loadFromFile("sound/gamesound.wav"))
		exit(EXIT_FAILURE);
	if (!m_robotDieBuffer->loadFromFile("sound/robotdie.wav"))
		exit(EXIT_FAILURE);
	if (!m_menuBuffer->loadFromFile("sound/menusound.wav"))
		exit(EXIT_FAILURE);
}

// instance provider
GameResources & GameResources::instance()
{
	static GameResources instance;
	return instance;
}

/*accessors*/

sf::Texture & GameResources::getRobotTexture()
{
	return *m_robotTexture;
}

sf::Texture & GameResources::getSimpleGuardTexture()
{
	return *m_simpleGuardTexture;
}

sf::Texture & GameResources::getCleverGuardTexture()
{
	return *m_cleverGuardTexture;
}

sf::Texture & GameResources::getRockTexture()
{
	return *m_rockTexture;
}

sf::Texture & GameResources::getWallTexture()
{
	return *m_wallTexture;
}

sf::Texture & GameResources::getDoorTexture()
{
	return *m_doorTexture;
}

sf::Texture & GameResources::getLifeFullTexture()
{
	return *m_lifeFullTexture;
}

sf::Texture & GameResources::getLifeEmptyTexture()
{
	return *m_lifeEmptyTexture;
}

sf::Texture & GameResources::getBombTexture()
{
	return *m_bombTexture;
}

sf::Texture & GameResources::getBombIconTexture()
{
	return *m_bombIconTexture;
}

sf::Texture & GameResources::getExplosionTexture()
{
	return *m_explosionTexture;
}

sf::Texture & GameResources::getExplosionIconTexture()
{
	return *m_explosionIconTexture;
}

sf::Texture & GameResources::getCoinTexture()
{
	return *m_coinTexture;
}

sf::Texture & GameResources::getBombBonusTexture()
{
	return *m_bombBonusTexture;
}

sf::Texture & GameResources::getSpeedBonusTexture()
{
	return *m_speedTexture;
}

sf::Texture & GameResources::getLifeTexture()
{
	return *m_lifeTexture;
}

sf::Font & GameResources::getCbFont()
{
	return *m_cbFont;
}

sf::SoundBuffer & GameResources::getBgGameBuffer()
{
	return *m_bgGameBuffer;
}

sf::SoundBuffer & GameResources::getRobotDieBuffer()
{
	return *m_robotDieBuffer;
}

sf::SoundBuffer & GameResources::geAlarmBuffer()
{
	return *m_alarmBuffer;
}

sf::SoundBuffer & GameResources::getExplosionBuffer()
{
	return *m_explosionBuffer;
}
sf::SoundBuffer & GameResources::getBombBuffer()
{
	return *m_bombBuffer;
}
sf::SoundBuffer & GameResources::getRunBuffer()
{
	return *m_playerRunBuffer;
}
sf::SoundBuffer & GameResources::getMenuMusicBuffer()
{
	return *m_menuBuffer;
}
