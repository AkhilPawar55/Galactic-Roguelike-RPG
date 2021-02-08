// We are using int to store the ascii code of the character representing the character instead of char or unsigned char. 
#pragma once

class Actor {
public:
	int x, y; // position on map
	int ch; // ascii code
	const char *name;
	int score;
	TCODColor col; // color
	bool blocks; // can we walk on this actor?
	Attacker *attacker; // something that deals damage
	Destructible *destructible; // something that can be damaged
	Ai *ai; // something self-updating
	Pickable *pickable;
	Container *container;

	Actor(int x, int y, int ch,const char *name, const TCODColor &col);
	~Actor();
	void render() const;
	void update();
	float getDistance(int cx, int cy) const;
	friend void displayActorInfo(const Actor& actor);
	friend std::ostream& operator<<(std::ostream&, const Actor&);
	
};