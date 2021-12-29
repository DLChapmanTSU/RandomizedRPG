// RandomizedRPG.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
//#include <typeinfo>
#include <Windows.h>
#include <fstream>

#include "Player.h"
#include "Enemy.h"
#include "Level.h"
#include "Item.h"

void Save(std::shared_ptr<Player>& _p);
//Player Load();

int main()
{
    std::shared_ptr<Player> player;
    player = std::make_shared<Player>('h', 'w', "Jim");
    int loadInput;

    std::cout << "Load save? (1 = yes, else = no)" << std::endl;
    std::cin >> loadInput;

    //Lets the player either load data from a text file or start with a new character
    if (loadInput == 1) {
        std::string dataToLoad[15];
        PlayerLoadingSpace::LoadData(dataToLoad);
        
        std::cout << "Data Loaded" << std::endl;

        if (dataToLoad[1] == "w") {
            player = std::make_shared<Warrior>(dataToLoad[0][0], dataToLoad[1][0], dataToLoad[2]);
        }
        else if (dataToLoad[1] == "m") {
            player = std::make_shared<Mage>(dataToLoad[0][0], dataToLoad[1][0], dataToLoad[2]);
        }
        else if (dataToLoad[1] == "r") {
            player = std::make_shared<Rogue>(dataToLoad[0][0], dataToLoad[1][0], dataToLoad[2]);
        }
        else {
            player = std::make_shared<Warrior>(dataToLoad[0][0], dataToLoad[1][0], dataToLoad[2]);
        }

        PlayerLoadingSpace::SetNewData(player, dataToLoad);
    }
    else {
        //Player inputs a name and class
        int classInput;
        int raceInput;
        char playerClass;
        std::string nameInput;

        std::cout << "Enter you name:" << std::endl;
        std::cin >> nameInput;

        std::cout << "Enter a race (1 = Human, 2 = Dwarf, 3 = Elf, 4 = Orc)" << std::endl;
        std::cin >> raceInput;

        switch (raceInput)
        {
        case 1:
            playerClass = 'h';
            break;
        case 2:
            playerClass = 'd';
            break;
        case 3:
            playerClass = 'e';
            break;
        case 4:
            playerClass = 'o';
            break;
        default:
            playerClass = 'h';
            break;
        }

        std::cout << "Enter a class (1 = Warrior, 2 = Mage, 3 = Rogue)" << std::endl;
        std::cin >> classInput;

        switch (classInput)
        {
        case 1:
            player = std::make_shared<Warrior>(playerClass, 'w', nameInput);
            break;
        case 2:
            player = std::make_shared<Mage>(playerClass, 'm', nameInput);
            break;
        case 3:
            player = std::make_shared<Rogue>(playerClass, 'r', nameInput);
            break;
        default:
            player = std::make_shared<Warrior>(playerClass, 'w', nameInput);
            break;
        }
    }

    player->GainGold(50);

    player->ShowStats();
    
    //Main game loop
    while (player->GetAlive() == true) {
        Level level;
        //level.Shop(player);
        level.Battle(player);
        player->SaveData();
        Sleep(500);
    }
}

//void Save(std::shared_ptr<Player>& _p) {
//    std::fstream file("playersave.txt", std::ios::binary | std::ios::in | std::ios::out | std::ios::trunc);
//
//    Player p = *_p;
//
//    file.write((char*)&p, sizeof(Player));
//
//    file.close();
//
//    std::cout << "Data Saved" << std::endl;
//}

//Player Load() {
//    std::fstream file("playersave.txt", std::ios::binary | std::ios::in | std::ios::out | std::ios::trunc);
//
//    Player p('h', 'w', "Jim");
//
//    file.read((char*)&p, sizeof(Player));
//
//    file.close();
//
//    p.ShowStats();
//
//    return p;
//}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
