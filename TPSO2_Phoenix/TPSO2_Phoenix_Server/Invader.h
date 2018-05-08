#pragma once
#include "Coords.h"
//Spawn chances
//by ships per thousand ships
#define PLAGUE_DEFAULT 999
#define COMMON_DEFAULT 500
#define UNCOMMON_DEFAULT 265
#define RARE_DEFAULT 125
#define MYTHIC_DEFAULT 63
#define MYTHIC_RARE_DEFAULT 32
#define LEGENDARY_DEFAULT 14
#define UNIQUE_DEFAULT 1

//Ship types
#define BASIC_TYPE 0
#define DODGER_TYPE 1
#define MIRROR_TYPE 2
#define BOSS_TYPE 3


typedef struct _invadership {
	Coords center;
	int XRadius;
	int YRadius;
	int MovementSpeed;
	int HP;
	int FireRate;
	int typeID;
	int MovementDirectionNext;
	int MovementDirectionPrev;
	int SpawnChance;
}Invader;