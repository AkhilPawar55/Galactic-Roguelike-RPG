#include "main.h"

Map::Map(int width, int height) : width(width), height(height) {

	try
	{
		ifstream mapTextFile("map.txt");
		if (mapTextFile)
		{
			mapTextFile >> roomAliens;
			mapTextFile >> roomItems;
			mapTextFile >> healWidth;
			mapTextFile >> healHeight;
		}
	}
	catch (exception e)
	{
		cout << "Map file not found" << endl;
	}

	

	
	tiles = new Tile[width*height];
	setCompound();
	generateDungeon();
}

Map::~Map() {
	delete[] tiles;
}

bool Map::isWall(int x, int y) const {
	return !tiles[x + y*width].canWalk;
}

bool Map::isHeal(int x, int y) const {
	return tiles[x + y*width].canHeal;
}

void Map::setWall(int x, int y) {
	tiles[x + y*width].canWalk = false;
}

void Map::setHeal(int x, int y) {
	tiles[x + y*width].canHeal = true;
}
void Map::render() const {
	static const TCODColor darkSpace(91, 91, 91);
	static const TCODColor lightSpace(0, 0, 0);

	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			TCODConsole::root->setCharBackground(x, y, isWall(x, y) ? darkSpace : lightSpace);
			if (isHeal(x, y) && isWall(x, y)) {
				TCODConsole::root->setCharBackground(x, y, TCODColor::blue);
			}
			else if (isWall(x, y)) {
				TCODConsole::root->setCharBackground(x, y, darkSpace);
			}
			else {
				TCODConsole::root->setCharBackground(x, y, lightSpace);
			}
		}
	}
}

void Map::addMonsterToMap(int x, int y) {
	TCODRandom *rng = TCODRandom::getInstance();
	int monsterCode = rng->getInt(0, 100);
	if (monsterCode < 70) {
		// create an Alien1
		Actor *alien1 = new Actor(x, y, '1', "Alien1", TCODColor::red);
		alien1->destructible = new MonsterDestructible(10, 0, "dead alien1");
		alien1->attacker = new Attacker(3);
		alien1->ai = new EnemyAi();
		engine.actors.push(alien1);
	}
	else {
		// create a Alien2
		Actor *alien2 = new Actor(x, y, '2', "Alien2", TCODColor::yellow);
		alien2->destructible = new MonsterDestructible(16, 1, "dead alien2");
		alien2->attacker = new Attacker(4);
		alien2->ai = new EnemyAi();
		engine.actors.push(alien2);
	}
}

bool Map::canWalk(int x, int y) const {
	if (isWall(x, y)) {
		printf("Cannot walk, Theres is a wall\n"); // this is a wall
		return false;
	}
	for (Actor **iterator = engine.actors.begin();
		iterator != engine.actors.end(); iterator++) {
		Actor *actor = *iterator;
		if (actor->x == x && actor->y == y) {
			// there is an actor there. cannot walk
			return false;
		}
	}
	return true;
}

void Map::generateDungeon()
{
	generateAliens();
	generateAliens(7, 7); // overloaded function to add enemy aliens at specific location
	generateItems();
}

void Map::generateAliens()
{
	TCODRandom *rng = TCODRandom::getInstance();
	int nbMonsters = rng->getInt(0, roomAliens);
	while (nbMonsters > 0) {
		int x = rng->getInt(0, engine.screenWidth - 4);
		int y = rng->getInt(0, engine.screenHeight - 4);
		if (canWalk(x, y)) {
			addMonsterToMap(x, y);
			nbMonsters--;
		}
	}
}

void Map::generateAliens(int x, int y)
{
	if (canWalk(x, y)) {
		addMonsterToMap(x, y);
	}
	else if (canWalk(x + 1, y)) {
		addMonsterToMap(x + 1, y);
	}
	else if (canWalk(x, y + 1)) {
		addMonsterToMap(x, y + 1);
	}
	else if (canWalk(x - 1, y)) {
		addMonsterToMap(x - 1, y);
	}
	else if (canWalk(x, y - 1)) {
		addMonsterToMap(x, y - 1);
	}
}

void Map::generateItems()
{
	TCODRandom *rng = TCODRandom::getInstance();
	int nbItems = rng->getInt(0, roomItems);
	while (nbItems > 0) {
		int x = rng->getInt(0, engine.screenWidth - 4);
		int y = rng->getInt(0, engine.screenHeight - 4);
		if (canWalk(x, y)) {
			addItem(x, y);
		}
		nbItems--;
	}
}

void Map::setCompound() {
	for (int x = 0; x < engine.screenWidth; x++) {
		for (int y = 0; y < engine.screenHeight; y++) {
			if (x == 0 || x == engine.screenWidth - 1 || y == 0 || y == engine.screenHeight - 4) {
				setWall(x, y);
			}
		}
	}

	for (int x = engine.screenWidth / 2 - (healWidth / 2); x <= engine.screenWidth / 2 + (healWidth / 2); x++) {
		for (int y = engine.screenHeight / 2 - (healHeight / 2); y <= engine.screenHeight / 2 + (healHeight / 2); y++) {
			setWall(x, y);
			setHeal(x, y);
		}
	}
}

void Map::addItem(int x, int y) {
	TCODRandom *rng = TCODRandom::getInstance();
	int dice = rng->getInt(0, 100);
	if (dice < 30) {
		// create a health potion
		Actor *healthPotion = new Actor(x, y, '!', "Healing potion", TCODColor::violet);
		healthPotion->blocks = false;
		healthPotion->pickable = new Healer(5);
		engine.actors.push(healthPotion);
	}

	else {
		// create a scroll of lightning bolt 
		Actor *airStrike = new Actor(x, y, 158, "Air Strike", TCODColor::white);
		airStrike->blocks = false;
		airStrike->pickable = new AirStrike(10, 20);
		engine.actors.push(airStrike);
	}
}

