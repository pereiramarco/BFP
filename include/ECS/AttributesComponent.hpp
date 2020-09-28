#pragma once

#include "Components.hpp"
#include "SDL2/SDL.h"

class AttributesComponent: public Component {

private:
    int maxHealth;
    float health;
    int maxStamina;
    float stamina;
    int maxMana;
    float mana;
    int maxXP;
    float xp;
    int level;
    float staminaSpendage;
public:
    AttributesComponent(int mH,int h,int mS,int s,int mM,int m,int mX,int x,int l,float sS) {
        maxHealth=mH;
        health=h;
        maxStamina=mS;
        stamina=s;
        maxMana=mM;
        mana=m;
        maxXP=mX;
        xp=x;
        level=l;
        staminaSpendage=sS;
    }

    void setAttribute(int a,float v) {
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
            case 9:
            staminaSpendage=v;
            break;
        }
    }

    float getAttribute(int a) {
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
            case 9:
            return staminaSpendage;
            break;
        }
    return 0;
    }

    void addToAttribute(int a,float v) {
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
            case 9:
            staminaSpendage+=v;
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