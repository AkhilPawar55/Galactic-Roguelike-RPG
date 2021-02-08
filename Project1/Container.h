#pragma once
class Container
{
public:
	int size;
	TCODList<Actor *> inventory;

	Container(int size);
	~Container();
	Container(const Container& otherContainer);
	Container& Container::operator=(Container const& otherContainer);
	bool add(Actor *actor);
	void remove(Actor *actor);
};

