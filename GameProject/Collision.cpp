#include "Collision.hpp"

void CollisionManager::collision(){
    intersectedTiles.clear();
    collisionTiles.clear();
    sideIntersection = { false,false,false,false };
    sf::FloatRect nextPos = sf::FloatRect(*desiredPosition, rect->size);
    sf::FloatRect rectP = *rect;
    for (auto& e : *box_tiles) {
        if (!activeCollision) break;
        sf::FloatRect rectT(e.getRect());
        if (e.getTag() != "null" && rectT.findIntersection(nextPos)) {
            intersectedTiles.push_back(&e);
            if (e.getTag() == "active") {
                if (rectP.position.y < rectT.position.y &&
                    rectP.position.y + rectP.size.y < rectT.position.y + rectT.size.y &&
                    rectP.position.x < rectT.position.x + rectT.size.x &&
                    rectP.position.x + rectP.size.x > rectT.position.x) {
                    collisionTiles.push_back(std::make_pair(&e, Side::BOTTOM));
                    desiredPosition->y = rectT.position.y - rectP.size.y;
                    sideIntersection[(int)Side::BOTTOM] = true;
                }
                else if (rectP.position.y > rectT.position.y &&
                    rectP.position.y + rectP.size.y > rectT.position.y + rectT.size.y &&
                    rectP.position.x < rectT.position.x + rectT.size.x &&
                    rectP.position.x + rectP.size.x > rectT.position.x) {
                    collisionTiles.push_back(std::make_pair(&e, Side::TOP));
                    desiredPosition->y = rectT.position.y + rectT.size.y;
                    sideIntersection[(int)Side::TOP] = true;
                }
                if (rectP.position.x < rectT.position.x &&
                    rectP.position.x + rectP.size.x < rectT.position.x + rectT.size.x &&
                    rectP.position.y < rectT.position.y + rectT.size.y &&
                    rectP.position.y + rectP.size.y > rectT.position.y) {
                    collisionTiles.push_back(std::make_pair(&e, Side::RIGHT));
                    desiredPosition->x = rectT.position.x - rectP.size.x;
                    sideIntersection[(int)Side::RIGHT] = true;
                }
                else if (rectP.position.x > rectT.position.x &&
                    rectP.position.x + rectP.size.x > rectT.position.x + rectT.size.x &&
                    rectP.position.y < rectT.position.y + rectT.size.y &&
                    rectP.position.y + rectP.size.y > rectT.position.y) {
                    collisionTiles.push_back(std::make_pair(&e, Side::LEFT));
                    desiredPosition->x = rectT.position.x + rectT.size.x;
                    sideIntersection[(int)Side::LEFT] = true;
                }
            }
        }
        
    }

    rect->position = *desiredPosition;
    for (bool& e : sideIntersection) { 
        if (e == true) {
            didCollide = true;
            return;
        }
    }
    didCollide = false;
}
    
bool CollisionManager::collisionEntity(const CollisionManager& collisionManager){
    for (sf::FloatRect* e : collisionManager.getRects()) {
        if (e->findIntersection(*rect)) { return true; }
    }
    return false;
}
