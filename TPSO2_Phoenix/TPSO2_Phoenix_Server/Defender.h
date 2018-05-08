#pragma once
#include "Coords.h"

typedef struct _defendership {
	Coords center;
	int YRadius;
	int XRadius;
	int MovementSpeedInitial;
	int MovementSpeedCurrent
	Player controller;
	int FireRateInitial;
	int FireRateCurrent;
	int MovementDirectionNext;
	int MovementDirectionPrev;
}Defender;