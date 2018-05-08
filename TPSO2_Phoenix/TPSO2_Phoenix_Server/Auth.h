#pragma once
#include <Windows.h>

typedef struct AuthenticationEntry{
	char userName[32];
	char userPassword[32];
	BOOL inUse;
	HANDLE entryMutex; //when changing this entry, must lock this mutex first
}AuthEntry;

typedef struct AuthenthicationDatabase{
	AuthEntry* user;
	int usersInDB;
	HANDLE DBMutex; //Functions that use this database must lock this mutex
}AuthDB;

BOOL authenticateUserByName (char* username, char* password, AuthDB* database);		  //	Not implemented
AuthEntry* getEntryFromName (char* username, AuthDB* database);					      //	Not implemented
BOOL userEntryExists (AuthEntry* user, AuthDB* database);							  //	Not implemented
BOOL userExists (char* user, AuthDB* database);										  //	Not implemented
BOOL isUserLogged (char* user, AuthDB* database);									  //	Not implemented
BOOL isUserEntryLogged (AuthEntry* user, AuthDB* database);							  //	Not implemented
AuthEntry createNewEntry (char* username, char* password);							  //	Not implemented
BOOL addUserToDB (AuthEntry* user, AuthDB* database);								  //	Not implemented
BOOL createUserInDB (char* username, char* password, AuthDB* database);				  //	Not implemented