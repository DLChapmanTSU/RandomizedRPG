#include "Enemy.h"
#include "Player.h"
#include "Level.h"

#include <iostream>
#include <string>
#include <Windows.h>

Enemy::Enemy(EnemyCode _c, Level& _l)
{
	
	m_level = std::make_shared<Level>(_l);

	switch (_c)
	{
	case EnemyCode::E_E1:
		m_name = "Zombie";
		m_health = 10;
		m_currentHealth = 10;
		m_power = 1;
		m_xpDrop = 1;
		m_goldDrop = 1;
		break;
	case EnemyCode::E_E2:
		m_name = "Skeleton";
		m_health = 12;
		m_currentHealth = 12;
		m_power = 2;
		m_xpDrop = 3;
		m_goldDrop = 1;
		break;
	case EnemyCode::E_E3:
		m_name = "Ghost";
		m_health = 20;
		m_currentHealth = 20;
		m_power = 4;
		m_xpDrop = 5;
		m_goldDrop = 3;
		break;
	case EnemyCode::E_E4:
		m_name = "Golem";
		m_health = 25;
		m_currentHealth = 25;
		m_power = 5;
		m_xpDrop = 10;
		m_goldDrop = 10;
		break;
	case EnemyCode::E_E5:
		m_name = "Slime";
		m_health = 5;
		m_currentHealth = 5;
		m_power = 2;
		m_xpDrop = 2;
		m_goldDrop = 2;
		break;
	default:
		break;
	}
}

void Enemy::Attack(Player& _p)
{
	std::cout << "The " << m_name << " Attacks!" << std::endl;
	Sleep(500);
	_p.TakeDamage(m_power);
}

void Enemy::Damage(int _d, Player& _p)
{
	//Applies damage and tells the user how much health the enemy has left
	m_currentHealth -= _d;
	std::cout << "The attack hits!" << std::endl;
	std::cout << _d << " damage dealt!" << std::endl;
	Sleep(500);
	CheckIsAlive();
	if (m_alive){
		std::cout << m_name << " is on " << m_currentHealth << " health" << std::endl;
		Sleep(500);
	}
	else {
		std::cout << m_name << " is dead!" << std::endl;
		Sleep(500);
		_p.GainXP(m_xpDrop);
		_p.GainGold(m_goldDrop);
	}
}

void Enemy::ShowStats()
{
	std::cout << "Enemy Stats:" << std::endl;
	std::cout << m_name << std::endl;
	std::cout << "Health: " << m_currentHealth << "/" << m_health << std::endl;
	Sleep(500);
}

void Enemy::CheckIsAlive()
{
	if (m_currentHealth <= 0) {
		m_alive = false;
	}
	else {
		m_alive = true;
	}
}
