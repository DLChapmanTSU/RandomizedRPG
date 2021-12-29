#include "Player.h"
#include "Item.h"
#include "Enemy.h"

#include <iostream>
#include <string>
#include <Windows.h>
#include <fstream>
#include <vector>
#include <string>

Player::Player(char _race, char _class, std::string _name)
{
	m_race = _race;
	m_class = _class;
	m_name = _name;

	switch (_race)
	{
	case 'h':
		m_health = 20;
		m_mana = 5;
		m_strength = 5;
		m_dexterity = 5;
		m_wisdom = 5;
		break;
	case 'd':
		m_health = 25;
		m_mana = 2;
		m_strength = 8;
		m_dexterity = 4;
		m_wisdom = 4;
		break;
	case 'e':
		m_health = 15;
		m_mana = 8;
		m_strength = 3;
		m_dexterity = 7;
		m_wisdom = 10;
		break;
	case 'o':
		m_health = 30;
		m_mana = 1;
		m_strength = 10;
		m_dexterity = 1;
		m_wisdom = 1;
		break;
	default:
		break;
	}

	switch (_class)
	{
	case 'w':
		m_weapon = std::make_shared<Weapon>(ItemCode::E_W1);
		break;
	case 'm':
		m_weapon = std::make_shared<Weapon>(ItemCode::E_W2);
		break;
	case 'r':
		m_weapon = std::make_shared<Weapon>(ItemCode::E_W3);
		break;
	default:
		break;
	}

	m_armour = std::make_shared<Armour>(ItemCode::E_A1);

	m_currentHealth = m_health;
	m_currentMana = m_mana;
}

void Player::ShowStats()
{
	std::cout << "---Stats---" << std::endl;
	std::cout << "Name: " << m_name << std::endl;
	std::cout << "Race: " << m_race << std::endl;
	std::cout << "Class: " << m_class << std::endl;
	std::cout << "Health: " << m_currentHealth << "/" << m_health << std::endl;
	std::cout << "Mana: " << m_currentMana << "/" << m_mana << std::endl;
	std::cout << "Strength: " << m_strength << std::endl;
	std::cout << "Dexterity: " << m_dexterity << std::endl;
	std::cout << "Wisdom: " << m_wisdom << std::endl;
	std::cout << "Gold: " << m_gold << std::endl;
	std::cout << "Level: " << m_level << std::endl;
	std::cout << "Experience: " << m_experience << std::endl;
	std::cout << "Weapon:" << std::endl;
	m_weapon->PrintData();
	std::cout << "Armour: " << std::endl;
	m_armour->PrintData();
	Sleep(500);
}

void Player::TakeDamage(int _d)
{
	_d -= m_armour->GetDamageReduction();

	if (_d < 0) {
		_d = 0;
	}

	m_currentHealth -= _d;
	std::cout << "OUCH!" << std::endl;
	std::cout << "You take " << _d << " damage!" << std::endl;
	Sleep(500);
	ShowStats();
	CheckIsAlive();
}

void Player::Attack(Enemy& _enemy)
{
	if (m_stunned) {
		std::cout << "You are too tired to move!" << std::endl;
		m_stunned = false;
		Sleep(500);
		return;
	}

	std::cout << "You swing at the enemy!" << std::endl;
	Sleep(500);
	_enemy.Damage(m_strength + m_weapon->GetStrengthBuff(), *this);
}

void Player::Pass()
{
	std::cout << "You do nothing..." << std::endl;
	Sleep(500);
	if (m_stunned) {
		m_stunned = false;
	}
}

void Player::GainXP(int _xp)
{
	m_experience += _xp;

	if (m_experience >= m_xpToNextLevel) {
		LevelUp();
	}
}

void Player::GainGold(int _g)
{
	m_gold += _g;
	std::cout << "Gold gained: " << _g << std::endl;
	Sleep(500);
}

void Player::LoseGold(int _g)
{
	m_gold -= _g;
}

void Player::GainHealth(int _h)
{
	m_currentHealth += _h;

	if (m_currentHealth > m_health) {
		m_currentHealth = m_health;
	}

	std::cout << "You feel rejuvinated!" << std::endl;
	Sleep(500);
	ShowStats();
}

void Player::SetWeapon(ItemCode _c)
{
	//delete m_weapon;
	m_weapon = std::make_shared<Weapon>(_c);
}

void Player::SetArmour(ItemCode _c)
{
	//delete m_armour;
	m_armour = std::make_shared<Armour>(_c);
}

void Player::SaveData()
{
	//Player is able to save its own data
	std::ofstream writer("saveData.txt");

	if (!writer) {
		return;
	}

	//Converts each stat into one long string
	//Each stat is divided by a line break
	//The string is then written to a .txt file
	std::string dataToWrite;
	dataToWrite = std::to_string(m_race) + "\n" + std::to_string(m_class) + "\n" + m_name + "\n" + std::to_string(m_health) + "\n" + std::to_string(m_currentHealth) + "\n" + std::to_string(m_mana) + "\n" + std::to_string(m_currentMana) + "\n"
		+ std::to_string(m_strength) + "\n" + std::to_string(m_dexterity) + "\n" + std::to_string(m_wisdom) + "\n" + std::to_string(m_gold) + "\n" + std::to_string(m_level) + "\n" + std::to_string(m_xpToNextLevel) + "\n"
		+ std::to_string((int)m_weapon->GetCode()) + "\n" + std::to_string((int)m_armour->GetCode());

	writer << dataToWrite;
	writer.close();
}

void Player::UniqueAttack(Enemy& _enemy)
{
	std::cout << "Ability Not Available" << std::endl;
	return;
}

void Player::CheckIsAlive()
{
	if (m_currentHealth <= 0) {
		m_alive = false;
	}
	else {
		m_alive = true;
	}
}

void Player::LevelUp()
{
	m_level++;
	int temp = m_experience - m_xpToNextLevel;
	m_experience = temp;

	m_xpToNextLevel += 10;

	switch (m_class)
	{
	case 'w':
		m_health += 5;
		m_currentHealth += 5;
		m_strength += 3;
		m_dexterity += 1;
		m_wisdom += 1;
		break;
	case 'm':
		m_health += 2;
		m_currentHealth += 2;
		m_mana += 4;
		m_currentMana += 4;
		m_strength += 1;
		m_dexterity += 2;
		m_wisdom += 3;
		break;
	case 'r':
		m_health += 3;
		m_currentHealth += 3;
		m_strength += 2;
		m_dexterity += 3;
		m_wisdom += 1;
		break;
	default:
		break;
	}

	std::cout << "Level Up!" << std::endl;
	Sleep(500);
	ShowStats();

	if (m_experience >= m_xpToNextLevel) {
		LevelUp();
	}
}

void Warrior::UniqueAttack(Enemy& _enemy)
{
	//This attack deals high damage but stuns the player, making them unable to attack for a turn
	if (m_stunned) {
		std::cout << "You are too tired to move!" << std::endl;
		m_stunned = false;
		Sleep(500);
		return;
	}

	std::cout << "SMASH!!!" << std::endl;
	Sleep(500);
	_enemy.Damage((m_strength + m_weapon->GetStrengthBuff()) * 2, *this);
	m_stunned = true;
	return;
}

void Rogue::UniqueAttack(Enemy& _enemy)
{
	//Generates a random number to hit the enemy with damage equal to the random number * the players dexterity
	std::cout << "RUSH ATTACK!!!" << std::endl;

	Sleep(500);

	int hits = rand() % 5 + 1;

	std::cout << "Hits " << hits << " times!" << std::endl;

	Sleep(500);

	_enemy.Damage((m_dexterity + m_weapon->GetDexterityBuff()) * hits, *this);
}

void Mage::UniqueAttack(Enemy& _enemy)
{
	//The mage gets a list of different spells with different effects
	//The mage gains an additional spell based on their level
	int input;
	int knownSpells = 2;
	std::cout << "Choose a spell:" << std::endl;

	switch (m_level)
	{
	case 1:
	case 2:
		std::cout << "1 = Fireball" << std::endl;
		std::cout << "2 = Heal" << std::endl;
		knownSpells = 2;
		break;
	case 3:
	case 4:
		std::cout << "1 = Fireball" << std::endl;
		std::cout << "2 = Heal" << std::endl;
		std::cout << "3 = Confusion" << std::endl;
		knownSpells = 3;
		break;
	default:
		std::cout << "1 = Fireball" << std::endl;
		std::cout << "2 = Heal" << std::endl;
		std::cout << "3 = Confusion" << std::endl;
		knownSpells = 3;
		break;
		break;
	}

	std::cin >> input;

	switch (input)
	{
	case 1:
		Fireball(_enemy);
		break;
	case 2:
		Heal();
		break;
	case 3:
		if (knownSpells < 3) {
			std::cout << "Spell Too Strong!!!" << std::endl;
			Sleep(500);
		}
		else {
			Confusion(_enemy);
		}
		break;
	default:
		std::cout << "No valid spell" << std::endl;
		break;
	}
}

void Mage::Fireball(Enemy& _enemy)
{
	if (m_currentMana >= 2) {
		std::cout << "You cast Fireball!" << std::endl;
		m_currentMana -= 2;
		Sleep(500);
		_enemy.Damage((m_wisdom + m_weapon->GetWisdomBuff()) + 2, *this);
	}
	else {
		std::cout << "The spell fizzles out..." << std::endl;
		Sleep(500);
	}
}

void Mage::Heal()
{
	if (m_currentMana >= 3) {
		std::cout << "You cast Heal!" << std::endl;
		m_currentMana -= 2;
		m_currentHealth += 2;

		if (m_currentHealth > m_health) {
			m_currentHealth = m_health;
		}

		Sleep(500);
		
		std::cout << "You feel stronger!" << std::endl;

		Sleep(500);
	}
	else {
		std::cout << "The spell fizzles out..." << std::endl;
		Sleep(500);
	}
}

void Mage::Confusion(Enemy& _enemy)
{
	if (m_currentMana >= 5) {
		std::cout << "You cast Confusion!" << std::endl;
		m_currentMana -= 5;
		Sleep(500);
		_enemy.Damage((m_wisdom + m_weapon->GetWisdomBuff()) * 2, *this);
	}
	else {
		std::cout << "The spell fizzles out..." << std::endl;
		Sleep(500);
	}
}

void PlayerLoadingSpace::LoadData(std::string(&a)[15])
{
	std::ifstream reader("saveData.txt");

	if (!reader) {
		return;
	}

	std::string data[15];
	size_t target{ 0 };

	while (!reader.eof() && target < 15) {
		std::string dataToAdd;
		std::getline(reader, a[target++], '\n');
	}

	return;
}

void PlayerLoadingSpace::SetNewData(std::shared_ptr<Player>& p, std::string(&a)[15])
{
	p->m_health = std::stoi(a[3]);
	p->m_currentHealth = std::stoi(a[4]);
	p->m_mana = std::stoi(a[5]);
	p->m_currentMana = std::stoi(a[6]);
	p->m_strength = std::stoi(a[7]);
	p->m_dexterity = std::stoi(a[8]);
	p->m_wisdom = std::stoi(a[9]);
	p->m_gold = std::stoi(a[10]);
	p->m_level = std::stoi(a[11]);
	p->m_xpToNextLevel = std::stoi(a[12]);
	p->m_weapon = std::make_shared<Weapon>(ItemCode(std::stoi(a[13])));
	p->m_armour = std::make_shared<Armour>(ItemCode(std::stoi(a[14])));
}
