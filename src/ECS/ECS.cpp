#include "../../include/ECS/ECS.hpp"

void Entity::addGroup(Group mGroup) {
    this->groupBitset[mGroup]=true;
    this->manager.addToGroup(this,mGroup);
}