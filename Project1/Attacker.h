#pragma once

class Attacker {
public:
	float power; // hit points given

	Attacker(float power);
	~Attacker();
	void attack(Actor *owner, Actor *target);
};