#pragma once

#include "Components.hpp"
#include "SDL2/SDL.h"

class AttributesComponent: public Component {

private:
    int maxHealth;
    int health;
    int maxStamina;
    int stamina;
    int maxMana;
    int mana;
    int maxXP;
    int xp;
    int level;
public:
    AttributesComponent(int mH,int h,int mS,int s,int mM,int m,int mX,int x,int l) {
        maxHealth=mH;
        health=h;
        maxStamina=mS;
        stamina=s;
        maxMana=mM;
        mana=m;
        maxXP=mX;
        xp=x;
        level=l;
    }

    void setAttribute(int a,int v) {
        switch (a) {
            case 0:
            maxHealth=v;
            break;
            case 1:
            health=v;
            break;
            case 2:
            maxStamina=v;
            break;
            case 3:
            stamina=v;
            break;
            case 4:
            maxMana=v;
            break;
            case 5:
            mana=v;
            break;
            case 6:
            maxXP=v;
            break;
            case 7:
            xp=v;
            break;
            case 8:
            level=v;
            break;
        }
    }

    int getAttribute(int a) {
        switch (a) {
            case 0:
            return maxHealth;
            break;
            case 1:
            return health;
            break;
            case 2:
            return maxStamina;
            break;
            case 3:
            return stamina;
            break;
            case 4:
            return maxMana;
            break;
            case 5:
            return mana;
            break;
            case 6:
            return maxXP;
            break;
            case 7:
            return xp;
            break;
            case 8:
            return level;
            break;
        }
    return 0;
    }

    void addToAttribute(int a,int v) {
        switch (a) {
            case 0:
            maxHealth+=v;
            break;
            case 1:
            health+=v;
            break;
            case 2:
            maxStamina+=v;
            break;
            case 3:
            stamina+=v;
            break;
            case 4:
            maxMana+=v;
            break;
            case 5:
            mana+=v;
            break;
            case 6:
            maxXP+=v;
            break;
            case 7:
            xp+=v;
            break;
            case 8:
            level+=v;
            break;
        }
    }

    void update() {
        while (xp>maxXP) {
            xp-=maxXP;
            maxXP*=1.1;
            level+=1;
        }
    }
};