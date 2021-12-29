#pragma once

#include <string>
#include <iostream>

enum class ItemCode {
	E_W1,
	E_W2,
	E_W3,
	E_W4,
	E_W5,
	E_W6,
	E_W7,
	E_W8,
	E_W9,
	E_W10,
	E_A1,
	E_A2,
	E_A3,
	E_A4,
	E_A5
};

class Item {
protected:
	std::string m_name;
	char m_itemType;
	ItemCode m_code;
	int m_shopCost{ 0 };
public:
	std::string GetName() { return m_name; };
	int GetShopCost() { return m_shopCost; };
	char GetItemType() { return m_itemType; };
	ItemCode GetCode() { return m_code; };
	virtual void PrintData() = 0;
};

class Weapon : public Item {
private:
	int m_strengthBuff{ 0 };
	int m_dexterityBuff{ 0 };
	int m_wisdomBuff{ 0 };
public:
	Weapon(ItemCode _c);
	int GetStrengthBuff() { return m_strengthBuff; };
	int GetDexterityBuff() { return m_dexterityBuff; };
	int GetWisdomBuff() { return m_wisdomBuff; };
	void PrintData() override;
};

class Armour : public Item {
private:
	int m_damageReduction;
public:
	Armour(ItemCode _c);
	int GetDamageReduction() { return m_damageReduction; };
	void PrintData() override;
};