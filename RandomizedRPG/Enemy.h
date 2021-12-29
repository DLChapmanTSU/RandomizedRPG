#pragma once

#include <string>
#include <memory>

class Player;
class Level;

enum class EnemyCode {
	E_E1,
	E_E2,
	E_E3,
	E_E4,
	E_E5
};

class Enemy {
private:
	std::string m_name{ "Enemy" };
	int m_health{ 10 };
	int m_currentHealth{ 10 };
	int m_power{ 1 };
	int m_xpDrop{ 1 };
	int m_goldDrop{ 1 };
	bool m_alive{ true };
	std::shared_ptr<Level> m_level;
public:
	Enemy(EnemyCode _c, Level& _l);
	void Attack(Player& _p);
	void Damage(int _d, Player& _p);
	void ShowStats();
	bool GetAlive() { return m_alive; };
private:
	void CheckIsAlive();
};
