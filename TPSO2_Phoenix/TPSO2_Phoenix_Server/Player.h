#pragma once
#include "Defender.h"
#include "AuthEntry.h"

typedef struct _player{
	AuthEntry* PlayerAuthEntry;
	int PlayerLives;
	Defender* PlayerShip;
	int PlayerID;
}Player;