#include "SubWeapon_Manager.hpp"
#include "Player.hpp"
bool SubWeapon_Manager::throwSubWeapon() {
	if (hearts == 0) return false;
	switch (subWeapon) {
	case Weapon::KNIFE:
		EntityFactory::invokeKnife(*gameSpace, rectPlayer->position, 
			(mainSprite->getScale().x > 0) ? true : false);
		break;
	case Weapon::AXE:
		EntityFactory::invokeAxe(*gameSpace, rectPlayer->position,
			(mainSprite->getScale().x > 0)? true : false);
		break;
	case Weapon::HOLY_WATER:
		EntityFactory::invokeHolyWater(*gameSpace, rectPlayer->position,
			(mainSprite->getScale().x > 0) ? true : false);
		break;
	case Weapon::CROSS:
		EntityFactory::invokeCross(*gameSpace, rectPlayer->position,
			(mainSprite->getScale().x > 0) ? true : false);
		break;
	}
	hearts--;
	return true;
}