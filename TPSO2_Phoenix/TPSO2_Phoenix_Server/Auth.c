#include"Auth.h"

BOOL stringEquals (char* str1, char* str2) {
	return strcmp (str1, str2) == 0;
}
BOOL authenticateUserByName (char* username, char* password, AuthDB* database) {
	DWORD waitResult=WaitForSingleObject (database->DBMutex, INFINITE);
	for (size_t i=0; i < database->usersInDB; i++) {
		if (stringEquals (username, database->user[i].userName)) {
			if (stringEquals (password, database->user[i].userPassword)) {
				ReleaseMutex (database->DBMutex);
				return TRUE;
			}
			ReleaseMutex (database->DBMutex);//wrong password
			return FALSE;
		}
	}
	ReleaseMutex (database->DBMutex);
	return FALSE; //no such user
}
AuthEntry* getEntryFromName (char* username, AuthDB* database) {
	DWORD waitResult=WaitForSingleObject (database->DBMutex, INFINITE);
	for (size_t i=0; i < database->usersInDB; i++) {
		if (stringEquals (username, database->user[i].userName)) {
			ReleaseMutex (database->DBMutex);//wrong password
			return database->user+i;
		}
	}
	ReleaseMutex (database->DBMutex);
	return NULL; //no such user
}						  
BOOL userExists (char* user, AuthDB* database) {
	DWORD waitResult=WaitForSingleObject (database->DBMutex, INFINITE);
	for (size_t i=0; i < database->usersInDB; i++) {
		if (stringEquals (user, database->user[i].userName)) {
			ReleaseMutex (database->DBMutex);//wrong password
			return TRUE;
		}
	}
	ReleaseMutex (database->DBMutex);
	return NULL; //no such user
}
BOOL isUserLogged (char* user, AuthDB* database) {
	AuthEntry* p=getEntryFromName (user,database);
	return p->inUse;
}					  
AuthEntry createNewEntry (char* username, char* password) {
	AuthEntry AE;
	AE.inUse=FALSE;
	AE.entryMutex=CreateMutex (NULL, FALSE, NULL);
	strcpy (AE.userName, username);
	strcpy (AE.userPassword, password);

	return AE;
}
BOOL addUserToDB (AuthEntry* user, AuthDB* database) {
	AuthEntry* ae=realloc(database->user,sizeof(database->user[0]) * database->usersInDB);
	memcpy (&database->user[database->usersInDB], user, sizeof (user));
}
BOOL createUserInDB (char* username, char* password, AuthDB* database) {
	AuthEntry AE=createNewEntry (username, password);
	if(AE.inUse != -1)
		addUserToDB (&AE, database);
	return TRUE;
}