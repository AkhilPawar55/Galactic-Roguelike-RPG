#pragma once

class Destructible
{
public:
	float maxHp;
	float hp;
	float defense;
	const char *corpseName;

	Destructible(float maxHp, float defense, const char *corpseName);
	virtual ~Destructible();
	inline bool isDead() { return hp <= 0; }
	float takeDamage(Actor *owner, float damage);
	virtual void die(Actor *owner);
	float heal(float amount);
};

class PlayerDestructible : public Destructible
{
public:
	PlayerDestructible(float maxHp, float defense, const char *corpseName);
	//~PlayerDestructible();

	virtual void die(Actor *owner);
};

class MonsterDestructible : public Destructible
{
public:
	MonsterDestructible(float maxHp, float defense, const char *corpseName);
	//~MonsterDestructible();

	virtual void die(Actor *owner);
};

