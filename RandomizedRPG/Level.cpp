#include "Level.h"
#include "Enemy.h"
#include "Player.h"
#include "Item.h"

#include <iostream>
#include <ctime>
#include <Windows.h>

Level::Level()
{
	//Generates a random number
	//Decides what sort of room it is
	m_enemyCount = 0;
	srand((unsigned int)time(NULL));
	int rng = rand() % 10 + 1;

	std::cout << "rng made:" << rng << std::endl;

	switch (rng)
	{
	case 1:
	case 2:
	case 3:
		std::cout << "The room is empty" << std::endl;
		m_enemyCount = 0;
		m_levelCode = 0;
		break;
	case 4:
	case 5:
	case 6:
		std::cout << "There is a shop in this room" << std::endl;
		m_enemyCount = 0;
		m_levelCode = 2;
		break;
	case 7:
		std::cout << "There is an enemy in the room!" << std::endl;
		m_enemyCount = 1;
		m_levelCode = 1;
		break;
	case 8:
	case 9:
	case 10:
		std::cout << "There are two enemies in the room!" << std::endl;
		m_enemyCount = 2;
		m_levelCode = 1;
		break;
	default:
		break;
	}

	std::cout << m_enemyCount << std::endl;
}

void Level::SpawnEnemies()
{
	for (int i = 0; i < m_enemyCount; i++)
	{
		EnemyCode code = EnemyCode(rand() % 5);
		std::cout << "Enemy spawned" << std::endl;
		Enemy temp = Enemy(code, *this);
		enemies.push_back(temp);
	}
}

void Level::Battle(std::shared_ptr<Player>& _p)
{
	//Calls shop function if there is a shop or heals if the room is empty
	//Then returns early
	if (m_levelCode == 0) {
		std::cout << "No enemies to fight" << std::endl;
		_p->GainHealth(2);
		Sleep(100);
		return;
	}
	else if (m_levelCode == 2) {
		std::cout << "You found a shop!" << std::endl;
		Shop(_p);
		return;
	}
	else {
		std::cout << "Spawning enemies..." << std::endl;
		SpawnEnemies();
	}

	int input{ 0 };
	int target{ 0 };

	std::cout << enemies.size() << std::endl;

	//Battle loop
	//Lets the user input an attack and a target
	//Any enemies that survive get to attack back
	while (_p->GetAlive() == true && enemies.size() > 0)
	{
		for (Enemy e : enemies) {
			e.ShowStats();
		}

		std::cout << "Your turn:" << std::endl;
		std::cout << "Attack (enter 1), Special (enter 2), or Wait (anything else)?" << std::endl;
		std::cin >> input;

		if ((input == 1 || input == 2) && enemies.size() > 1) {
			std::cout << "Choose a target (1 = enemy one, 2 = enemy two):" << std::endl;
			std::cin >> target;

			if (target != 1 && target != 2) {
				target = 1;
			}
		}
		else if (enemies.size() <= 1) {
			target = 1;
		}

		switch (input)
		{
		case 1:
			_p->Attack(enemies[target - 1]);
			Sleep(500);
			break;
		case 2:
			_p->UniqueAttack(enemies[target - 1]);
			Sleep(500);
			break;
		default:
			_p->Pass();
			Sleep(500);
			break;
		}

		std::cout << "Enemy turn:" << std::endl;
		Sleep(500);

		for (unsigned int i = 0; i < enemies.size(); i++)
		{
			if (enemies.size() <= 0) {
				break;
			}

			if (enemies[i].GetAlive() == true) {
				enemies[i].Attack(*_p);
			}
			else {
				RemoveEnemy((size_t)i);
				i--;
			}
		}
	}

	if (_p->GetAlive() == true) {
		std::cout << "You win the battle!" << std::endl;
	}
	else {
		std::cout << "You died" << std::endl;
	}
}

void Level::RemoveEnemy(size_t _e)
{
	enemies.erase(enemies.begin() + _e);
}

void Level::Shop(std::shared_ptr<Player>& _p)
{
	std::vector<std::shared_ptr<Item>> items;

	//Generates three items
	for (size_t i = 0; i < 3; i++)
	{
		ItemCode code = ItemCode(rand() % 15);
		if ((int)code > 9) {
			items.push_back(std::make_shared<Armour>(code));
		}
		else {
			items.push_back(std::make_shared<Weapon>(code));
		}
	}

	for (std::shared_ptr<Item> i : items) {
		i->PrintData();
	}

	std::cout << "Buy an item? (1, 2, or 3):" << std::endl;
	int input;
	std::cin >> input;

	//User can buy an item, replacing their current weapon or armour with the chosen item
	//Only happens if the user has enough gold to buy the item
	switch (input)
	{
	case 1:
		if (_p->GetGold() >= items[0]->GetShopCost()) {
			std::cout << "Item bought!" << std::endl;
			_p->LoseGold(items[0]->GetShopCost());
			if (items[0]->GetItemType() == 'w') {
				_p->SetWeapon(items[0]->GetCode());
			}
			else {
				_p->SetArmour(items[0]->GetCode());
			}
			
		}
		else {
			std::cout << "Sorry " << _p->GetName() << ", I don't give credit! Come back when your a little, ummm... richer!" << std::endl;
		}
		break;
	case 2:
		if (_p->GetGold() >= items[1]->GetShopCost()) {
			std::cout << "Item bought!" << std::endl;
			_p->LoseGold(items[1]->GetShopCost());
			if (items[1]->GetItemType() == 'w') {
				_p->SetWeapon(items[1]->GetCode());
			}
			else {
				_p->SetArmour(items[1]->GetCode());
			}
		}
		else {
			std::cout << "Sorry " << _p->GetName() << ", I don't give credit! Come back when your a little, ummm... richer!" << std::endl;
		}
		break;
	case 3:
		if (_p->GetGold() >= items[2]->GetShopCost()) {
			std::cout << "Item bought!" << std::endl;
			_p->LoseGold(items[2]->GetShopCost());
			if (items[2]->GetItemType() == 'w') {
				_p->SetWeapon(items[2]->GetCode());
			}
			else {
				_p->SetArmour(items[2]->GetCode());
			}
		}
		else {
			std::cout << "Sorry " << _p->GetName() << ", I don't give credit! Come back when your a little, ummm... richer!" << std::endl;
		}
		break;
	default:
		std::cout << "You buy nothing" << std::endl;
		break;
	}

	_p->ShowStats();

	Sleep(2000);
}
