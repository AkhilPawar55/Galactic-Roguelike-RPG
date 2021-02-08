#pragma once

class Engine {
public:
	enum GameStatus {
		STARTUP,
		IDLE,
		NEW_TURN,
		VICTORY,
		DEFEAT
	} gameStatus;

	TCODList<Actor *> actors;
	Actor *player;
	Map *map;
	Gui	*gui;
	int screenWidth;
	int screenHeight;
	int newTurnCount;
	TCOD_key_t lastKey;

	Engine(int screenWidth, int screenHeight);
	void init();
	~Engine();
	void term();
	void load();
	void update();
	void render();
	void sendToBack(Actor *actor);
	Actor *getClosestMonster(int x, int y, float range) const;
};

extern Engine engine;
