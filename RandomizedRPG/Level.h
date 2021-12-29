#pragma once

#include <vector>
#include <memory>

class Player;
class Enemy;

class Level {
private:
	std::vector<Enemy> enemies;
	int m_enemyCount;
	int m_levelCode{ 0 };
public:
	Level();
	void SpawnEnemies();
	void Battle(std::shared_ptr<Player>& _p);
	void RemoveEnemy(size_t _e);
	void Shop(std::shared_ptr<Player>& _p);
};
