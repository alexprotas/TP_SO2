#pragma once

#include "Coords.h"
typedef struct _defendershot {
	Coords center;
	int YRadius;
	int XRadius;
	int Speed; //times per 100ms, maybe ?
	int Damage;
	int MovementCooldown;
}Bullet;