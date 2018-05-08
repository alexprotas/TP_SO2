#include"Game.h"

#define BULLET_THREAD_SLEEP_TIMER_MS 100000
DWORD WINAPI BulletsHandler (LPVOID lpParam) {
	BulletThreadParameters* BTP=lpParam;
	Game* G= BTP->gameToHandle;

	WaitForSingleObject (G->GameStartEvent,INFINITE);

	while (!BTP->TerminationFlag) {
		for (int i=0; i < G->BulletsCount; ++i) {
			G->BulletsOnField[i].center.YPos=G->BulletsOnField[i].center.YPos + G->BulletsOnField[i].Speed;
		}
		usleep (BULLET_THREAD_SLEEP_TIMER_MS);
	}
}