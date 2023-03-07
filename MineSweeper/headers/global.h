#ifndef MSUTILS_H_INCLUDED
#define MSUTILS_H_INCLUDED

#define ABSTRACT_SCREEN						\
		char* name;							\
		int type;							\
		void (*display)(void* this_t);		\
		void (*eventsHandler)(void* this_t);	\

typedef struct Button {
	int width;
	int height;
	char* content;
	void (*isClicked)(int x, int y);
	void (*callback)();
} Button;

typedef struct Menu {
	int* buttons;
} Menu;

typedef struct MainScreen {
	void* pScreenData;
	void (*display)(void* this_t);
	void (*eventsHandler)(void* this_t);
} MainScreen;

