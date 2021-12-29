#pragma once

#include <string>

#include "Item.h"

class Enemy;
class Weapon;
class Armour;
class Player;

//enum ItemCode;

namespace PlayerLoadingSpace {
	void LoadData(std::string(&a)[15]);
	void SetNewData(std::shared_ptr<Player>& p, std::string(&a)[15]);
}

class Player {
protected:
	std::shared_ptr<Weapon> m_weapon;
	std::shared_ptr<Armour> m_armour;
	char m_race;
	char m_class;
	std::string m_name;
	int m_health;
	int m_currentHealth;
	int m_mana;
	int m_currentMana;
	int m_strength;
	int m_dexterity;
	int m_wisdom;
	int m_gold{ 5 };
	int m_level{ 1 };
	int m_experience{ 0 };
	int m_xpToNextLevel{ 10 };
	bool m_alive{ true };
	bool m_stunned{ false };
public:
	Player(char _race, char _class, std::string _name);
	void ShowStats();
	void TakeDamage(int _d);
	void Attack(Enemy& _enemy);
	void Pass();
	void GainXP(int _xp);
	void GainGold(int _g);
	void LoseGold(int _g);
	void GainHealth(int _h);
	char GetClass() { return m_class; };
	int GetCurrentHealth() { return m_currentHealth; };
	bool GetAlive() { return m_alive; };
	int GetGold() { return m_gold; };
	std::string GetName() { return m_name; };
	std::shared_ptr<Weapon>& GetWeapon() { return m_weapon; };
	std::shared_ptr<Armour>& GetArmour() { return m_armour; };
	void SetWeapon(ItemCode _c);
	void SetArmour(ItemCode _c);
	void SaveData();

	//Each class has a unique attack that will override this function
	virtual void UniqueAttack(Enemy& _enemy);

	friend void PlayerLoadingSpace::SetNewData(std::shared_ptr<Player>& p, std::string(&a)[15]);
private:
	void CheckIsAlive();
	void LevelUp();
};

class Warrior : public Player {
public:
	Warrior(char r, char c, std::string n) : Player(r, c, n){ }
	void UniqueAttack(Enemy& _enemy);
};

class Mage : public Player {
public:
	Mage(char r, char c, std::string n) : Player(r, c, n) { }
	void UniqueAttack(Enemy& _enemy);
private:
	void Fireball(Enemy& _enemy);
	void Heal();
	void Confusion(Enemy& _enemy);
};

class Rogue : public Player {
public:
	Rogue(char r, char c, std::string n) : Player(r, c, n) { }
	void UniqueAttack(Enemy& _enemy);
};

