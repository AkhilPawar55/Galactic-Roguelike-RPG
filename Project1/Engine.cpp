#include "main.h"

#define ATTACKS 5
#define CONTAINERS 26
Engine::Engine(int screenWidth, int screenHeight) : gameStatus(STARTUP), screenWidth(screenWidth), screenHeight(screenHeight) {
	TCODConsole::initRoot(screenWidth, screenHeight, "RPPG", false);
	
	gui = new Gui();
}
void Engine::init()
{
   
	player = new Actor(5, 5, 2, "Player", TCODColor::copper);
	player->destructible = new PlayerDestructible(30, 2, "your cadaver");
	#ifdef ATTACKS
	player->attacker = new Attacker(ATTACKS);
	#endif // ATTACKS
    player->ai = new PlayerAi();
	#ifdef CONTAINERS
	player->container = new Container(CONTAINERS);
	#endif // CONTAINERS

	
	actors.push(player);
	map = new Map(screenWidth, screenHeight - 2);
	gameStatus = STARTUP;
}

Engine::~Engine() {
	 term();
	actors.clearAndDelete();
	delete map;
	delete gui;
}
//The term function clears the map, the actors and the message log so that engine is ready to restart.
void Engine::term()
{
	actors.clearAndDelete();
	if (map) delete map;
	gui->clear();
}
void Engine::load()
{
	engine.gui->menu.clear();
	engine.gui->menu.addItem(Menu::NEW_GAME, "New game");
	
	engine.gui->menu.addItem(Menu::EXIT, "Exit");
	Menu::MenuItemCode menuItem = engine.gui->menu.pick();
	if (menuItem == Menu::EXIT || menuItem == Menu::NONE) {
		// Exit or window closed
		exit(0);
	}
	else if (menuItem == Menu::NEW_GAME) {
		// New game
		engine.term();
		engine.init();
	
	}
}

void Engine::update() {
	if (gameStatus == STARTUP) {
		// map->computeFov();
	}
	gameStatus = IDLE;
	TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS, &lastKey, NULL);
	player->update();
	if (gameStatus == NEW_TURN) {
		newTurnCount++;
		for (Actor **iterator = actors.begin(); iterator != actors.end();
			iterator++) {
			Actor *actor = *iterator;
			if (actor != player) {
				actor->update();
			}
		}
	}

	if (newTurnCount == 10) {
		newTurnCount = 0;
		TCODRandom *rng = TCODRandom::getInstance();
		int nRandom = rng->getInt(0, 10);
		if (nRandom % 2 == 0) {
			engine.map->generateDungeon();
		}
	}
}

void Engine::render() {
	TCODConsole::root->clear();
	// draw the map
	map->render();
	// draw the actors
	for (Actor **iterator = actors.begin();
		iterator != actors.end(); iterator++) {
		Actor *actor = *iterator;
		if (actor != player /* && map->isInFov(actor->x, actor->y) */) {
			actor->render();
		}
	}
	player->render();
	gui->render();
	// show the player's stats
}

void Engine::sendToBack(Actor *actor) {
	actors.remove(actor);
	actors.insertBefore(actor, 0);
}

Actor *Engine::getClosestMonster(int x, int y, float range) const {
	Actor *closest = NULL;
	float bestDistance = 1E6F;

	for (Actor **iterator = actors.begin(); iterator != actors.end(); iterator++) {
		Actor *actor = *iterator;
		if (actor != player && actor->destructible && !actor->destructible->isDead()) {
			float distance = actor->getDistance(x, y);
			if (distance < bestDistance && (distance <= range || range == 0.0f)) {
				bestDistance = distance;
				closest = actor;
			}
		}
	}
	return closest;
}