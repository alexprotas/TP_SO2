
#include <stdio.h>
#include "Messages.h"
#include "Auth.h"
#include "Game.h"

//this is suposed to run in a thread
//what this does is sort incoming messages into the apropriate queues
//so the other threads can read them

MessageQueue* DefendersQueue;
AuthDB* AuthDatabase;
Game* CurrentGame;

#define DEFENDER_MOVE_COMMAND "MOVE"
#define DEFENDER_SHOOT_COMMAND "SHOOT"
#define DEFENDER_USE_LASER_COMMAND "LAZOR"
#define DEFENDER_USE_BOMB_COMMAND "KABOOM"

#define PLAYER_LOGIN_COMMAND "LOGIN"
#define PLAYER_LOGOUT_COMMAND "LOGOUT"
#define PLAYER_JOINGAME_COMMAND "JOIN"
#define NEW_PLAYER_COMMAND "NEW"

#define DB_PATH _T("./auth.db")

#define AUTH_SUCCESS_MESSAGE "AUTH_SUCCESS"
#define AUTH_INVALID_MESSAGE "AUTH_FAILED_PARAMETERS"
#define AUTH_FAILED_MESSAGE "AUTH_FAILED_PASSWORD"

#define CREATE_USER_SUCCESS_MESSAGE	"CREATE_USER_SUCCESS"
#define CREATE_USER_DUPLICATE_MESSAGE "USER_ALREADY_EXISTS"
#define CREATE_USER_INVALID_MESSAGE "CREATE_USER_FAILED_PARAMETERS"

#define JOINGAME_SUCCESS_MESSAGE "JOINGAME_SUCCESS"
#define JOINGAME_NOTLOGGED_MESSAGE "NO_LOGIN"
#define JOINGAME_GAMEFULL_MESSAGE "GAME_FULL"
#define JOINGAME_INVALID_MESSAGE "JOINGAME_PARAMETERS"

#define DEAUTH_SUCCESS_MESSAGE "DEAUTH_SUCCESS"
#define DEAUTH_INVALID_MESSAGE "DEAUTH_INVALID"
#define DEAUTH_FAILED_MESSAGE "DEAUTH_FAILED"

int mainThreadloop () {
	FILE* logFile=stdout;
	fprintf (logFile, "[MAIN THREAD] :: Main loop starting");
	DefendersQueue=createQueue ();
	AuthDatabase=LoadDBFromFile (DB_PATH);

	int commandMessageSize=256;
	char* commandMessage=malloc (sizeof (char) * commandMessageSize);

	/*if (CM->argumentCount >= X) {
		BOOL result=XXXXXXXX;
		if (result) {
			fprintf (logFile, "[MAIN THREAD] :: XXXXXXX");
			char* message=calloc (strlen (YYYYYYY) + XXXXXX, sizeof (message[0]));
			sprintf (message, "%s %s", YYYYYYY, XXXXXX);
			WriteSHMCommand (message);
		} else {
			fprintf (logFile, "[MAIN THREAD] :: XXXXXX");
			char* message=calloc (strlen (ZZZZZZZ) + XXXXXX), sizeof (message[0]));
			sprintf (message, "%s %s", ZZZZZZ, XXXXXXX);
			WriteSHMCommand (message);
		}
	} else {
		fprintf (logFile, "[MAIN THREAD] :: XXXXXXXXXXXXXXX");
		char* message=calloc (strlen (XXXXXXXX) + XXXXXX, sizeof (message[0]));
		sprintf (message, "%s %s", XXXXXX, XXXXXXX);
		WriteSHMCommand (message);
	}*/
	
	while (1) {
		GetSHMCommand (commandMessage);
		if (commandMessage != NULL) {//This should never happen
			if (strlen (commandMessage) > 0) {//This may happen
				CommandMessage* CM=parseMessage (commandMessage);
				if (stringEquals (CM->message, DEFENDER_MOVE_COMMAND)) {
					putIntoQueue (CM, DefendersQueue);
				} else if (stringEquals (CM->message, DEFENDER_SHOOT_COMMAND)) {
					putIntoQueue (CM, DefendersQueue);
				} else if (stringEquals (CM->message, DEFENDER_USE_LASER_COMMAND)) {
					putIntoQueue (CM, DefendersQueue);
				} else if (stringEquals (CM->message, DEFENDER_USE_BOMB_COMMAND)) {
					putIntoQueue (CM, DefendersQueue);
				} else if (stringEquals (CM->message, PLAYER_LOGIN_COMMAND)) {
					if (CM->argumentCount >= 2) {
						BOOL result=authenticateUserByName (CM->messageArguments[0], CM->messageArguments[1], AuthDatabase);
						if (result) {
							fprintf (logFile, "[MAIN THREAD] :: Player %s authenticated", CM->messageArguments[0]);
							char* message=calloc (strlen (AUTH_SUCCESS_MESSAGE) + 16, sizeof (message[0]));
							sprintf (message, "%s %s", AUTH_SUCCESS_MESSAGE, CM->messageId);
							WriteSHMCommand (message);
						} else {
							fprintf (logFile, "[MAIN THREAD] :: Player %s authentication failed, wrong password or no such player", CM->messageArguments[0]);
							char* message=calloc (strlen (AUTH_FAILED_MESSAGE) + 16, sizeof (message[0]));
							sprintf (message, "%s %s", AUTH_FAILED_MESSAGE, CM->messageId);
							WriteSHMCommand (message);
						}
					} else {
						fprintf (logFile, "[MAIN THREAD] :: Invalid authentication attemp, incorrect parameter count");
						char* message=calloc (strlen (AUTH_INVALID_MESSAGE) + 16, sizeof (message[0]));
						sprintf (message, "%s %s", AUTH_INVALID_MESSAGE, CM->messageId);
						WriteSHMCommand (message);
					}
				} else if (stringEquals (CM->message, NEW_PLAYER_COMMAND)) {
					if (CM->argumentCount >= 2) {
						BOOL result=createUserInDB (CM->messageArguments[0], CM->messageArguments[1], AuthDatabase);
						if (result) {
							fprintf (logFile, "[MAIN THREAD] :: New user %s created", CM->messageArguments[0]);
							char* message=calloc (strlen (CREATE_USER_SUCCESS_MESSAGE) + 16, sizeof (message[0]));
							sprintf (message, "%s %d", CREATE_USER_SUCCESS_MESSAGE, CM->messageId);
							WriteSHMCommand (message);
						} else {
							fprintf (logFile, "[MAIN THREAD] :: New user %s already exists", CM->messageArguments[0]);
							char* message=calloc (strlen (CREATE_USER_DUPLICATE_MESSAGE) + 16, sizeof (message[0]));
							sprintf (message, "%s %d", CREATE_USER_DUPLICATE_MESSAGE, CM->messageId);
							WriteSHMCommand (message);
						}
					} else {
						fprintf (logFile, "[MAIN THREAD] :: Create user request invalid, invalid argument count");
						char* message=calloc (strlen (CREATE_USER_INVALID_MESSAGE) + 16, sizeof (message[0]));
						sprintf (message, "%s %d", CREATE_USER_INVALID_MESSAGE, CM->messageId);
						WriteSHMCommand (message);
					}
				} else if (stringEquals (CM->message, PLAYER_JOINGAME_COMMAND)) {
					if (CM->argumentCount >= 1) {
						if (isUserLogged (CM->messageArguments[0], AuthDatabase)) {
							if (CurrentGame->HumanCount < CurrentGame->MaxHumanCount) {//player can join
								AddPlayerToGame (CM->messageArguments[0], CurrentGame);
								fprintf (logFile, "[MAIN THREAD] :: Player join game success");
								char* message=calloc (strlen (JOINGAME_SUCCESS_MESSAGE) + 16, sizeof (message[0]));
								sprintf (message, "%s %d", JOINGAME_SUCCESS_MESSAGE, CM->messageId);
								WriteSHMCommand (message);
							} else {
								fprintf (logFile, "[MAIN THREAD] :: Player tried to join a full game");
								char* message=calloc (strlen (JOINGAME_GAMEFULL_MESSAGE) + 16, sizeof (message[0]));
								sprintf (message, "%s %d", JOINGAME_GAMEFULL_MESSAGE, CM->messageId);
								WriteSHMCommand (message);
							}
						} else {
							fprintf (logFile, "[MAIN THREAD] :: Player tried to join game and is not logged in");
							char* message=calloc (strlen (JOINGAME_NOTLOGGED_MESSAGE) + 16, sizeof (message[0]));
							sprintf (message, "%s %d", JOINGAME_NOTLOGGED_MESSAGE, CM->messageId);
							WriteSHMCommand (message);
						}
					} else {
						fprintf (logFile, "[MAIN THREAD] :: Invalid parameters to join game");
						char* message=calloc (strlen (JOINGAME_INVALID_MESSAGE) + 16, sizeof (message[0]));
						sprintf (message, "%s %d", JOINGAME_INVALID_MESSAGE, CM->messageId);
						WriteSHMCommand (message);
					}
				} else if (stringEquals (CM->message, PLAYER_LOGOUT_COMMAND)) {
					if (CM->argumentCount >= 1) {
						if (isUserLogged (CM->messageArguments[0], AuthDatabase)) {
							removePlayerFromGame (CM->messageArguments[0],CurrentGame);
							unlogPlayer (CM->messageArguments[0]);
							fprintf (logFile, "[MAIN THREAD] :: Player %s has left",CM->messageArguments[0]);
							char* message=calloc (strlen (DEAUTH_SUCCESS_MESSAGE) + 16, sizeof (message[0]));
							sprintf (message, "%s %s", DEAUTH_SUCCESS_MESSAGE, CM->messageId);
							WriteSHMCommand (message);
						} else {
							fprintf (logFile, "[MAIN THREAD] :: Invalid deauthentication attempt, player not logged in");
							char* message=calloc (strlen (DEAUTH_FAILED_MESSAGE) + 16, sizeof (message[0]));
							sprintf (message, "%s %s", DEAUTH_FAILED_MESSAGE, CM->messageId);
							WriteSHMCommand (message);
						}
					} else {
						fprintf (logFile, "[MAIN THREAD] :: Invalid deauthentication attempt, incorrect parameter count");
						char* message=calloc (strlen (DEAUTH_INVALID_MESSAGE) + 16, sizeof (message[0]));
						sprintf (message, "%s %s", DEAUTH_INVALID_MESSAGE, CM->messageId);
						WriteSHMCommand (message);
					}
				}
			}
		}
		memset (commandMessage, sizeof (char) * commandMessageSize, 0x00);
	}
}

