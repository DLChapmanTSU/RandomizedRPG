#include "Item.h"

Weapon::Weapon(ItemCode _c)
{
	m_code = _c;

	switch (_c)
	{
	case ItemCode::E_W1:
		m_name = "Basic Axe";
		m_shopCost = 1;
		m_itemType = 'w';
		m_strengthBuff = 1;
		m_dexterityBuff = 0;
		m_wisdomBuff = 0;
		break;
	case ItemCode::E_W2:
		m_name = "Basic Dagger";
		m_shopCost = 1;
		m_itemType = 'w';
		m_strengthBuff = 0;
		m_dexterityBuff = 1;
		m_wisdomBuff = 0;
		break;
	case ItemCode::E_W3:
		m_name = "Basic Staff";
		m_shopCost = 1;
		m_itemType = 'w';
		m_strengthBuff = 0;
		m_dexterityBuff = 0;
		m_wisdomBuff = 1;
		break;
	case ItemCode::E_W4:
		m_name = "Blade Of Wisdom";
		m_shopCost = 20;
		m_itemType = 'w';
		m_strengthBuff = 3;
		m_dexterityBuff = 0;
		m_wisdomBuff = 5;
		break;
	case ItemCode::E_W5:
		m_name = "Knife Of The Kings Assassin";
		m_shopCost = 25;
		m_itemType = 'w';
		m_strengthBuff = 2;
		m_dexterityBuff = 7;
		m_wisdomBuff = 0;
		break;
	case ItemCode::E_W6:
		m_name = "A Stick";
		m_shopCost = 0;
		m_itemType = 'w';
		m_strengthBuff = 0;
		m_dexterityBuff = 0;
		m_wisdomBuff = 0;
		break;
	case ItemCode::E_W7:
		m_name = "Rabadons Sceptre";
		m_shopCost = 30;
		m_itemType = 'w';
		m_strengthBuff = 1;
		m_dexterityBuff = 0;
		m_wisdomBuff = 10;
		break;
	case ItemCode::E_W8:
		m_name = "Sharpened Broadsword";
		m_shopCost = 5;
		m_itemType = 'w';
		m_strengthBuff = 3;
		m_dexterityBuff = 0;
		m_wisdomBuff = 0;
		break;
	case ItemCode::E_W9:
		m_name = "Greatest Greataxe";
		m_shopCost = 25;
		m_itemType = 'w';
		m_strengthBuff = 6;
		m_dexterityBuff = 0;
		m_wisdomBuff = 0;
		break;
	case ItemCode::E_W10:
		m_name = "Irish Navy Can Opener";
		m_shopCost = 15;
		m_itemType = 'w';
		m_strengthBuff = 3;
		m_dexterityBuff = 3;
		m_wisdomBuff = 3;
		break;
	default:
		m_name = "Error";
		m_shopCost = 0;
		m_itemType = 'w';
		m_strengthBuff = 0;
		m_dexterityBuff = 0;
		m_wisdomBuff = 0;
		break;
	}
}

void Weapon::PrintData()
{
	std::cout << m_name << std::endl << "Cost: " << m_shopCost << std::endl << "S: " << m_strengthBuff << std::endl << "D: " << m_dexterityBuff << std::endl << "W: " << m_wisdomBuff << std::endl;
}

Armour::Armour(ItemCode _c)
{
	m_code = _c;

	switch (_c)
	{
	case ItemCode::E_A1:
		m_name = "Common Clothes";
		m_shopCost = 0;
		m_itemType = 'a';
		m_damageReduction = 0;
		break;
	case ItemCode::E_A2:
		m_name = "Leather Armour";
		m_shopCost = 3;
		m_itemType = 'a';
		m_damageReduction = 1;
		break;
	case ItemCode::E_A3:
		m_name = "Plate Armour";
		m_shopCost = 5;
		m_itemType = 'a';
		m_damageReduction = 2;
		break;
	case ItemCode::E_A4:
		m_name = "Overpriced Hype-Beast Shirt";
		m_shopCost = 100;
		m_itemType = 'a';
		m_damageReduction = 0;
		break;
	case ItemCode::E_A5:
		m_name = "Armour Of The Kings Knight";
		m_shopCost = 15;
		m_itemType = 'a';
		m_damageReduction = 5;
		break;
	default:
		m_name = "Error";
		m_shopCost = 0;
		m_itemType = 'a';
		m_damageReduction = 0;
		break;
	}
}

void Armour::PrintData()
{
	std::cout << m_name << std::endl << "Cost: " << m_shopCost << std::endl << "Reduction: " << m_damageReduction << std::endl;
}
