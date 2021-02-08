#pragma once

struct Tile {
	bool canWalk; // can we walk through this tile?
	bool canHeal;
	Tile() : canWalk(true), canHeal(false) {}
};

class Map {
public:
	int width, height;
	
	Map(int width, int height);
	~Map();
	void generateDungeon();
	void generateAliens();
	void generateAliens(int x, int y);
	void generateItems();
	bool isWall(int x, int y) const;
	bool isHeal(int x, int y) const;
	void render() const;
	bool canWalk(int x, int y) const;

protected:
	int roomAliens, roomItems;
	int healWidth, healHeight;

	Tile *tiles;

	void setWall(int x, int y);
	void setHeal(int x, int y);
	//bool canWalk(int x, int y) const;
	void addMonsterToMap(int x, int y);
	
	void setCompound();
	void addItem(int x, int y);
};

