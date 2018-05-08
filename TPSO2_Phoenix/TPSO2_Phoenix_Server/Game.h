#pragma once
#include <Windows.h>
#include "Bullets.h"
#include "Bomb.h"
#include "Powerup.h"
#include "Invader.h"
#include "Defender.h"
#include "Player.h"

typedef struct _game {
	int MaxFieldX;
	int MaxFieldY;
	int HumanCount;
	int MaxEnemiesOnScreen;
	Invader* EnemiesOnScreen;
	Player* Players;
	int PlayerCount;
	int EnemiesOnScreenCount;
	int MaxEnemiesOnBufferCount;
	int EnemiesOnBufferCount;
	Invader* EnemiesOnBuffer;
	Defender* Defenders;
	int DefendersCount;
	int MaxDefenders;
	Bullet* BulletsOnField;
	Bomb* BombsOnField;
	Powerup* PowerupsOnField;
	int PowersCount;
	int BombsCount;
	int BulletsCount;
	bool GameStarted;

	HANDLE GameUpdatedEvent;
	HANDLE GameStartEvent;
	
	HANDLE FieldMutex;
	HANDLE InvadersMutex;
	HANDLE GameMutex;

	HANDLE* InvaderTreads;
	int InvaderThreadsCount;
	HANDLE* DefenderTreads;
	int DefenderThreadsCount;
	HANDLE* BulletTreads;
	int BulletThreadsCount;
	HANDLE* BombTreads;
	int BombThreadsCount;
	HANDLE* PowerupTreads;
	int PowerupThreadsCount;

	Config GameConfig;
}Game;

typedef struct _config {

}Config;

char* createGameString (Game* G);