#pragma once

#include<Windows.h>
typedef struct _message {
	char* message;
	char** messageArguments;
	int argumentCount;
	int messageId;
}CommandMessage;

typedef struct _messageQueue {
	CommandMessage* messagesInQueue;
	int messageCount;
	HANDLE queueMutex;
	HANDLE newMessageEvent;
}MessageQueue;

CommandMessage* getFromQueue (MessageQueue* mq);
void putIntoQueue (CommandMessage* msg, MessageQueue* mq);
MessageQueue* createQueue ();
CommandMessage* parseMessage (char* msg);
void closeMessage (CommandMessage* cm);
void closeQueue (MessageQueue* mq);