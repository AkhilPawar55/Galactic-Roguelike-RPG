#include "main.h"

Pickable::Pickable()
{
}

Pickable::~Pickable()
{
}

bool Pickable::pick(Actor *owner, Actor *wearer) {
	if (wearer->container && wearer->container->add(owner)) {
		engine.actors.remove(owner);
		return true;
	}
	return false;
}

bool Pickable::use(Actor *owner, Actor *wearer) {
	if (wearer->container) {
		wearer->container->remove(owner);
		delete owner;
		return true;
	}
	return false;
}

ostream& operator<<(ostream& o, const Pickable& pickable)
{
	pickable.displayPickableParameters(o);
	return o;
}

void Pickable::displayPickableParameters(ostream& o) const
{
	o << "Parameters : ";
}

Healer::Healer(float amount) : amount(amount) {
	cout << (*this);
}

bool Healer::use(Actor *owner, Actor *wearer) {
	if (wearer->destructible) {
		float amountHealed = wearer->destructible->heal(amount);
		if (amountHealed > 0) {
			return Pickable::use(owner, wearer);
		}
	}
	return false;
}

void Healer::displayPickableParameters(ostream& o) const
{
	Pickable::displayPickableParameters(o);
	o << "Heal: " << amount << endl;
}

AirStrike::AirStrike(float range, float damage) : range(range), damage(damage) {
	cout << (*this);
}

bool AirStrike::use(Actor *owner, Actor *wearer) {
	Actor *closestMonster = engine.getClosestMonster(wearer->x, wearer->y, range);
	if (!closestMonster) {
		//engine.gui->message(TCODColor::lightGrey, "No enemy is close enough to strike.");
		return false;
	}
	// hit closest monster for <damage> hit points
	//engine.gui->message(TCODColor::lightBlue, "A lighting bolt strikes the %s with a loud thunder!\n" "The damage is %g hit points.", closestMonster->name, damage);
	closestMonster->destructible->takeDamage(closestMonster, damage);

	return Pickable::use(owner, wearer);
}

void AirStrike::displayPickableParameters(ostream& o) const
{
	Pickable::displayPickableParameters(o);
	o << "Range: " << range;
	o << ", Damage: " << damage << endl;
}