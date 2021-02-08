#include "main.h"

Actor::Actor(int x, int y, int ch, const char *name, const TCODColor &col) :
	x(x), y(y), ch(ch), name(name), col(col),blocks(true), attacker(NULL), destructible(NULL), ai(NULL), pickable(NULL), container(NULL) {
	cout << (*this);
}

Actor::~Actor() {
	if (attacker) delete attacker;
	if (destructible) delete destructible;
	if (ai) delete ai;
	if (pickable) delete pickable;
	if (container) delete container;
}

void Actor::render() const {
	TCODConsole::root->setChar(x, y, ch);
	TCODConsole::root->setCharForeground(x, y, col);
}

void Actor::update() 
{
	if (ai)
	{
		ai->update(this);
	}
}


float Actor::getDistance(int cx, int cy) const
{
	int dx = x - cx;
	int dy = y - cy;

	return sqrtf(dx * dx + dy * dy);
}
	


void displayActorInfo(const Actor& actor)
{
	printf("%s is at (%d, %d)\n ", actor.name, actor.x, actor.y);
}

ostream& operator<<(ostream& out, const Actor& actor) {
	return out << actor.name << " is at " << "(" << actor.x << "," << actor.y << ")" << endl;
}