#pragma once
#include "RemovableItem.h"
#include "BonusAnimation.h"
#include "Sound.h"

class BonusItem :
	public RemovableItem
{
public:
	//using removable item constractor
	using::RemovableItem::RemovableItem;
	//pause and unpause the animation , bonus animation 
	void pause();
	void unPause();
	//effect the robot by : increase bomb quantity , increase speed , increase life , increase score.
	virtual void affectRobot(Robot& robot) = 0;

private:
	Sound* m_sound;
};
