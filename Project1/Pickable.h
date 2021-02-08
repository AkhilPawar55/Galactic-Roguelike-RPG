#pragma once
class Pickable
{
public:
	Pickable();
	~Pickable();

	bool pick(Actor *owner, Actor *wearer);
	virtual bool use(Actor *owner, Actor *wearer);
	
	friend std::ostream& operator<<(std::ostream&, const Pickable& pickable);

protected:
	virtual void displayPickableParameters(std::ostream& o) const;
};

class Healer : public Pickable {
public:
	float amount; // how many hp

	Healer(float amount);
	bool use(Actor *owner, Actor *wearer);
	virtual void displayPickableParameters(std::ostream & o) const;
};

class AirStrike : public Pickable {
public:
	float range, damage;

	AirStrike(float range, float damage);
	bool use(Actor *owner, Actor *wearer);
	virtual void displayPickableParameters(std::ostream & o) const;
};	

