#pragma once
#include "Coords.h"
#include "Invader.h"

#define SHIELD_ID 1001
#define ICE_ID 1002
#define BATTERY_ID 1003
#define PLUS_ID 1004
#define BOOZE_ID 2018
#define LAZOR_ID 1006
#define BOMB_ID 1007

typedef struct _powerups {
	Coords center;
	int XRadius;
	int YRadius;
	int Speed;
	int EffectID;
	int SpawnChance;
	int Duration;         //Blast radius for bombs
}Powerup;