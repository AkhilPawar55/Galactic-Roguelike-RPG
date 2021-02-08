#include "main.h"

Container::Container(int size) : size(size) {
	
}

Container::~Container() {
	inventory.clearAndDelete();
}

Container::Container(const Container& otherContainer)
{
	size = otherContainer.size;

	for (Actor **iterator = otherContainer.inventory.begin(); iterator != otherContainer.inventory.end(); iterator++) {
		Actor *currentInventorActor = *iterator;
		inventory.push(currentInventorActor); 
	}
}

Container& Container::operator=(Container const& otherContainer)
{
	if (this != &otherContainer)
	{
		size = otherContainer.size;

		for (Actor **iterator = otherContainer.inventory.begin(); iterator != otherContainer.inventory.end(); iterator++) {
			Actor *currentInventorActor = *iterator;
			inventory.push(currentInventorActor);
		}
	}
	return *this;
}

bool Container::add(Actor *actor) {
	if (size > 0 && inventory.size() >= size) {
		return false;
	}

	inventory.push(actor);
	return true;
}

void Container::remove(Actor *actor) {
	inventory.remove(actor);
}

