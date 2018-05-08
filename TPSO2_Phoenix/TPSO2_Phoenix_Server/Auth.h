#pragma once
#include <Windows.h>

typedef struct AuthenticationEntry{
	char userName[32];
	char userPassword[32];
	bool inUse;
	HANDLE entryMutex; //when changing this entry, must lock this mutex first
}AuthEntry;

typedef struct AuthenthicationDatabase{
	AuthEntry* user;
	int usersInDB;
	HANDLE DBMutex; //Functions that use this database must lock this mutex
}AuthDB;

bool authenticateUserByName (char* username, char* password, AuthDB* database);		  //	Not implemented
bool authenticateUserByEntry (AuthEntry* user, AuthDB* database);					  //	Not implemented
AuthEntry getEntryFromName (char* username, AuthDB* database);					      //	Not implemented
bool userEntryExists (AuthEntry* user, AuthDB* database);							  //	Not implemented
bool userExists (char* user, AuthDB* database);										  //	Not implemented
bool isUserLogged (char* user, AuthDB* database);									  //	Not implemented
bool isUserEntryLogged (AuthEntry* user, AuthDB* database);							  //	Not implemented
AuthEntry createNewEntry (char* username, char* password);							  //	Not implemented
bool addUserToDB (AuthEntry* user, AuthDB* database);								  //	Not implemented
bool createUserInDB (char* username, char* password, AuthDB* database);				  //	Not implemented