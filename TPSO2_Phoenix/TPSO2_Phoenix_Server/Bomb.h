#pragma once
#include "Coords.h"

typedef struct _invadershot{
	Coords centerCoordinates;
	int YRadius;
	int XRadius;
	double Speed; //pixels per 100ms
}Bomb;