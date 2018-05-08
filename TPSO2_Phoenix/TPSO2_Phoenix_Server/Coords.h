#pragma once
typedef struct _coordinates {
	int XPos;
	int YPos;
}Coords;

bool objectsColide (Coords o1Center, int o1XRadius, int o1YRadius, Coords o2Center, int o2XRadius, int o2YRadius);