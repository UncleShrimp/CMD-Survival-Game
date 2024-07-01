#include <iostream>
#include <vector>
#include <string>
#include <Windows.h>
#include <conio.h>


using namespace std;
HANDLE hc = GetStdHandle(STD_OUTPUT_HANDLE);

string screen[25][81];
/*
                               QQQQQQQQQQ
                            QQQQQQQQQQQQQQQQ
                            QQQQQQQQQQQQQQQQ
                            QQQQQQQQQQQQQQQQ
                            QQQQQQQQQQQQQQQQ
                               QQQQQQQQQQ
                                   #
                                   #
                                   #
                                   #
                                   #
                                   #
33333333333333333333333333333333333333333333333333333333333333333333333333333333
                                                                               %







                                   OOOOO
                               OOOOOOOOOOOOO
                            OOOOOOOOOOOOOOOOOOO
                           OOOOOOOOOOOOOOOOOOOOO
                          OOOOOOOOOOOOOOOOOOOOOOO
                          OOOOOOOOOOOOOOOOOOOOOOO
33333333333333333333333333333333333333333333333333333333333333333333333333333333
                                  ___
                                  | |
                                  | |
                                  | |
                           _______| |_______
                          |                 |
                          |                 |
                          |       iiii      |
                          |      IIIIII     |
                          |                 |
33333333333333333333333333333333333333333333333333333333333333333333333333333333

*/

// chunk attributes: temperature, structure, safe
// temp = -20(2)   |   19(1)   |    60(6)
// stru = 0-none 1-tree 2-stone 3-dungeon 4-playersmth 5-coal 6-iron 7-ruby 8-lava
// safe = 0-no | 1-yes
int World[5000][5000];
int undergroundWorld[5000][5000];
int playerPosition[2]{ 2499, 2499 };
// 1 - wood; 2 - stone
vector<int> inventory;
vector<int> ItemAmount;
bool under = false;

class engine {
public:
    int tickHunger = 5;

    void printStats() {
        cout << playerPosition[0] << " " << playerPosition[1] << endl;
        cout << World[playerPosition[0]][playerPosition[1]] << endl;
        cout << tickHunger << endl;
    }

    int generator(int a, int b) {
        int result;
        result = a + rand() % b;
        return result;
    }
    void rainbow() {
        for (int i = 0; i < 256; i++) {
            SetConsoleTextAttribute(hc, i);
            cout << i << endl;
        }
    }
    void borders() {
        if (playerPosition[0] < 0) {
            playerPosition[0] = 0;
        }
        if (playerPosition[1] < 0) {
            playerPosition[1] = 0;
        }
        if (playerPosition[0] > 4999) {
            playerPosition[0] = 4998;
        }
        if (playerPosition[1] > 4999) {
            playerPosition[1] = 4998;
        }
    }
    void chunkGeneration(int y, int x) {
        if (World[y][x]==0) {
            int genRes = generator(0, 3);
            // Biome
            if (genRes == 0) {
                World[y][x] = 2 * 100;
            }
            if (genRes == 1) {
                World[y][x] = 1 * 100;
            }
            if (genRes == 2) {
                World[y][x] = 6 * 100;
            }
            // stru
            genRes = generator(0, 4);
            if (genRes == 0 && World[y][x] / 100 != 6) {
                World[y][x] += 1 * 10;
            }
            if (genRes == 1 && World[y][x] / 100 != 6) {
                World[y][x] += 2 * 10;
            }
            if (genRes == 2) {
                World[y][x] += 3 * 10;
            }
        }
    }
    void undergroundGeneration(int w, int l) {
        for (int y = 0; y < w; y++) {
            for (int x = 0; x < l; x++) {
                int genRes = generator(0, 4);
                // loot
                if (genRes == 0) {
                    undergroundWorld[y][x] = 5;
                }
                if (genRes == 1) {
                    undergroundWorld[y][x] = 6;
                }
                if (genRes == 2) {
                    undergroundWorld[y][x] = 7;
                }
                if (genRes == 3) {
                    undergroundWorld[y][x] = 8;
                }
            }
        }
    }
};
class graphics {
    engine engReference;
public:
    void printInventory(vector<int>& arr) {
        for (int i = 0; i < arr.size(); i++) {
            setColor(13);
            switch (arr[i])
            {
            case 1:
                if (arr[i] > 0) { cout << "Wood x" << ItemAmount[i] << " "; }
                break;
            case 2:
                if (arr[i] > 0) { cout << "Stone x" << ItemAmount[i] << " "; }
                break;
            default:
                break;
            }
        }
    }
    void printScreen() {
        for (int y = 0; y < 25; y++) {
            for (int x = 0; x < 81; x++) {
                if (y >= 20) {
                    grass();
                }
                if (y >= 8 && y < 14) {
                    if ((World[playerPosition[0]][playerPosition[1]] / 100) == 1 && (World[playerPosition[0]][playerPosition[1]] / 100) != 6) {
                        setColor(10);
                    }
                }
                if (y >= 14 && y < 20) { //8
                    if ((World[playerPosition[0]][playerPosition[1]] / 100) == 1 || (World[playerPosition[0]][playerPosition[1]] / 100) == 2 && (World[playerPosition[0]][playerPosition[1]] / 100) != 6) {
                        setColor(8);
                    }
                }
                if (y >= 14 && y < 20) {
                    if ((World[playerPosition[0]][playerPosition[1]] % 10) == 2) {
                        setColor(8);
                    }
                }
                cout << screen[y][x];
            }
            cout << "" << endl;
        }
    }
    void clearScreen() {
        for (int y = 0; y < 25; y++) {
            for (int x = 0; x < 81; x++) {
                screen[y][x] = " ";
            }
        }
    }

    void drawTerrain(int y, int x) {
        if (World[y][x] % 10 != 1) {
            for (int y = 24; y > 20; y--) {
                for (int x = 0; x < 81; x++) {
                    if ((World[playerPosition[0]][playerPosition[1]] / 100) == 1) {
                        screen[y][x] = "|";
                    }
                    if ((World[playerPosition[0]][playerPosition[1]] / 100) == 2) {
                        screen[y][x] = "*";
                    }
                    if ((World[playerPosition[0]][playerPosition[1]] / 100) == 6) {
                        screen[y][x] = "#";
                    }
                }
            }
        }
        //4
        if (World[y][x] % 10 >= 1) {
            for (int y = 24; y > 20; y--) {
                for (int x = 0; x < 81; x++) {
                    setColor(4);
                    screen[y][x] = "_";
                }
            }
        }
        setColor(7);
    }

    void drawMinimap(int pY, int pX) {
        int minimap[5][5];
        int pPosY = 3;
        int pPosX = 3;
        // 2f 7s 6d
        //0
        /*
        cout<<World[pY-2][pX-2]<<" "<<World[pY-2][pX-1]<<" "<<World[pY-2][pX]<<" "<<World[pY-2][pX+1]<<" "<<World[pY-2][pX+2]<<endl;
        cout<<World[pY-1][pX-2]<<" "<<World[pY-1][pX-1]<<" "<<World[pY-1][pX]<<" "<<World[pY-1][pX+1]<<" "<<World[pY-1][pX+2]<<endl;
        cout<<World[pY][pX-2]<<" "<<World[pY][pX-1]<<" "<<"P"<<" "<<World[pY-2][pX+1]<<" "<<World[pY][pX+2]<<endl;
        cout<<World[pY+1][pX-2]<<" "<<World[pY+1][pX-1]<<" "<<World[pY+1][pX]<<" "<<World[pY+1][pX+1]<<" "<<World[pY+1][pX+2]<<endl;
        cout<<World[pY+2][pX-2]<<" "<<World[pY+2][pX-1]<<" "<<World[pY+2][pX]<<" "<<World[pY+2][pX+1]<<" "<<World[pY+2][pX+2]<<endl;*/

        for (int x = -2; x < 3; x++) {
            switch (World[pY - 2][pX + x] / 100)
            {
            case 0:
                setColor(0);
                break;
            case 2:
                setColor(7);
                break;
            case 1:
                setColor(2);
                break;
            case 6:
                setColor(6);
                break;
            default:
                break;
            }
            if (World[pY - 2][pX + x] % 10 >= 1) {
                // 14
                setColor(4);
            }
            cout << World[pY - 2][pX + x] % 10 << "  ";
        }
        cout << endl;
        for (int x = -2; x < 3; x++) {
            switch (World[pY - 1][pX + x] / 100)
            {
            case 0:
                setColor(0);
                break;
            case 2:
                setColor(7);
                break;
            case 1:
                setColor(2);
                break;
            case 6:
                setColor(6);
                break;
            default:
                break;
            }
            if (World[pY - 2][pX + x] % 10 >= 1) {
                // 14
                setColor(4);
            }
            cout << World[pY - 1][pX + x] % 10 << "  ";
        }
        cout << endl;
        for (int x = -2; x < 3; x++) {
            switch (World[pY][pX + x] / 100)
            {
            case 0:
                setColor(0);
                break;
            case 2:
                setColor(7);
                break;
            case 1:
                setColor(2);
                break;
            case 6:
                setColor(6);
                break;
            default:
                break;
            }
            if (World[pY - 2][pX + x] % 10 >= 1) {
                // 14
                setColor(4);
            }
            if (x == 0) {
                cout << "X" << "  ";
            }
            else {
                cout << World[pY][pX + x] % 10 << "  ";
            }
        }
        cout << endl;
        for (int x = -2; x < 3; x++) {
            switch (World[pY + 1][pX + x] / 100)
            {
            case 0:
                setColor(0);
                break;
            case 2:
                setColor(7);
                break;
            case 1:
                setColor(2);
                break;
            case 6:
                setColor(6);
                break;
            default:
                break;
            }
            if (World[pY - 2][pX + x] % 10 >= 1) {
                // 14
                setColor(4);
            }
            cout << World[pY + 1][pX + x] % 10 << "  ";
        }
        cout << endl;
        for (int x = -2; x < 3; x++) {
            switch (World[pY + 2][pX + x] / 100)
            {
            case 0:
                setColor(0);
                break;
            case 2:
                setColor(7);
                break;
            case 1:
                setColor(2);
                break;
            case 6:
                setColor(6);
                break;
            default:
                break;
            }
            if (World[pY - 2][pX + x] % 10 >= 1) {
                // 14
                setColor(4);
            }
            cout << World[pY + 2][pX + x] % 10 << "  ";
        }
        cout << endl;
        /*
        0 0 0 0 0
        0 0 0 0 0
        0 0 p 0 0
        0 0 0 0 0
        0 0 0 0 0
        */
    }

    // 27 - 49
    // 36 - 41
    void drawUndergroundEnter(int structure) {
        if (structure == 3) {
            /*
            for (int y=24; y>20; y++) {
                for (int x=26; x<48; x++) {
                    screen[y][x]="!";
                }
            }*/
            for (int y = 14; y < 20; y++) {
                if (y == 14) {
                    for (int x = 35; x < 40; x++) {
                        screen[y][x] = "O";
                    }
                }
                if (y == 15) {
                    for (int x = 31; x < 44; x++) {
                        screen[y][x] = "O";
                    }
                }
                if (y == 16) {
                    for (int x = 28; x < 47; x++) {
                        screen[y][x] = "O";
                    }
                }
                if (y == 17) {
                    for (int x = 27; x < 48; x++) {
                        screen[y][x] = "O";
                    }
                }
                if (y > 17 && y < 20) {
                    for (int x = 26; x < 49; x++) {
                        screen[y][x] = "O";
                    }
                }
            }
            //130
            for (int y = 17; y < 20; y++) {
                for (int x = 35; x < 40; x++) {
                    screen[y][x] = " ";
                }
            }
        }
    }
    void drawTree(int biome) {
        if (biome == 1 && World[playerPosition[0]][playerPosition[1]] / 100 != 6) {
            // draw log
            for (int y = 14; y < 20; y++) {
                screen[y][35] = "#";
            }
            // draw leaves
            for (int y = 8; y < 14; y++) {
                if (y == 8 || y == 13) {
                    for (int x = 31; x < 40; x++) {
                        screen[y][x] = "Q";
                    }
                }
                if (y > 8 && y < 13) {
                    for (int x = 27; x < 44; x++) {
                        screen[y][x] = "Q";
                    }
                }
            }
        }
    }
    void drawStone(int structure) {
        if (structure == 2) {
            for (int y = 14; y < 20; y++) {
                if (y == 14) {
                    for (int x = 35; x < 40; x++) {
                        screen[y][x] = "O";
                    }
                }
                if (y == 15) {
                    for (int x = 31; x < 44; x++) {
                        screen[y][x] = "O";
                    }
                }
                if (y == 16) {
                    for (int x = 28; x < 47; x++) {
                        screen[y][x] = "O";
                    }
                }
                if (y == 17) {
                    for (int x = 27; x < 48; x++) {
                        screen[y][x] = "O";
                    }
                }
                if (y > 17 && y < 20) {
                    for (int x = 26; x < 49; x++) {
                        screen[y][x] = "O";
                    }
                }
            }
        }
    }
    /*


                                  ___
                                  | |
                                  | |
                                  | |
                           _______| |_______
                          |                 |
                          |                 |
                          |       iiii      |
                          |      IIIIII     |
                          |                 |
33333333333333333333333333333333333333333333333333333333333333333333333333333333

    */



    void drawFurnace(int structure) {
        if (World[playerPosition[0]][playerPosition[1]] % 10 == 2 && structure == 0) {
            for (int y = 14; y < 20; y++) {
                if (y == 14) {
                    for (int x = 35; x < 40; x++) {
                        screen[y][x] = "O";
                    }
                }
                if (y == 15) {
                    for (int x = 31; x < 44; x++) {
                        screen[y][x] = "O";
                    }
                }
                if (y == 16) {
                    for (int x = 28; x < 47; x++) {
                        screen[y][x] = "O";
                    }
                }
                if (y == 17) {
                    for (int x = 27; x < 48; x++) {
                        screen[y][x] = "O";
                    }
                }
                if (y > 17 && y < 20) {
                    for (int x = 26; x < 49; x++) {
                        screen[y][x] = "O";
                    }
                }
            }
            //130
            for (int y = 17; y < 20; y++) {
                for (int x = 35; x < 40; x++) {
                    screen[y][x] = " ";
                }
            }
            for (int y = 14; y > 10; y--) {
                for (int x = 37; x < 39; x++) {
                    screen[y][x] = "O";
                }
            }
        }
    }

    void grass() {
        if ((World[playerPosition[0]][playerPosition[1]] / 100) == 1) {
            // GRASS
            switch (engReference.generator(0, 2)) {
            case 0:
                SetConsoleTextAttribute(hc, 2); //2 or 10
                break;
            case 1:
                SetConsoleTextAttribute(hc, 10); //2 or 10
                break;

            default:
                break;
            }
        }
        if ((World[playerPosition[0]][playerPosition[1]] / 100) == 2) {
            // SNOW
            switch (engReference.generator(0, 2)) {
            case 0:
                SetConsoleTextAttribute(hc, 7);
                break;
            case 1:
                SetConsoleTextAttribute(hc, 8);
                break;

            default:
                break;
            }
        }
        if ((World[playerPosition[0]][playerPosition[1]] / 100) == 6) {
            // SAND
            switch (engReference.generator(0, 2)) {
            case 0:
                SetConsoleTextAttribute(hc, 6); //2 or 10
                break;
            case 1:
                SetConsoleTextAttribute(hc, 14); //2 or 10
                break;

            default:
                break;
            }
        }
        if ((World[playerPosition[0]][playerPosition[1]] % 10) >= 1) {
            setColor(4);
        }
    }
    void setColor(int color) { // color E [0, 15]
        SetConsoleTextAttribute(hc, color);
    }
    void printActions() {
        cout << "" << endl;
    }
};
class userInterface {
public:
    void coutDelay(int amount) {
        for (int i = 0; i < amount; i++) {
            cout << "" << endl;
        }
    }
};
class player {
    userInterface ui;
    graphics graphcs;

private:
    bool debugMode = true;
    int playerDamage = 5;
    int hpAm = 10;
    int hungerAm = 10;
    vector<string> hpUI{ "X", "X", "X", "X", "X", "X", "X", "X", "X", "X" };
    vector<string> hungrUI{ "X", "X", "X", "X", "X", "X", "X", "X", "X", "X" };

public:
    int inventory[10];
    int getDamage() {
        return playerDamage;
    }
    void switchDebug() {
        if (GetAsyncKeyState(VK_F3)) {
            debugMode = true;
        }
        if (GetAsyncKeyState(VK_F4)) {
            debugMode = false;
        }
    }
    bool getDegugState() {
        return debugMode;
    }
    int getPPosY() {
        return playerPosition[0];
    }
    int getPPosX() {
        return playerPosition[1];
    }
    void changePPosY(int n) {
        playerPosition[0] += n/*/2*/;
    }
    void changePPosX(int n) {
        playerPosition[1] += n/*/2*/;
    }
    void printHp(int hp) {
        graphcs.setColor(1);
        cout << "Health - ";
        for (int i = 0; i < hp - 1; i++) {
            graphcs.setColor(12);
            cout << hpUI[i];
        }
    }
    void printHungr(int hunger) {
        graphcs.setColor(1);
        cout << "Hunger - ";
        for (int i = 0; i < hunger - 1; i++) {
            graphcs.setColor(7);
            cout << hungrUI[i];
        }
        ui.coutDelay(1);
    }
};
class controls {
    player getPlayer;
    graphics getGraphics;
    engine getEngine;
public:
    int input() {
        int velocity = 0;
        if (GetAsyncKeyState('F')) {
            for (int i = 0; i < inventory.size(); i++) {
                if (inventory[i] == 2 && ItemAmount[i] >= 5) {
                    if (World[playerPosition[0]][playerPosition[1]] % 10 == 1) {
                        World[playerPosition[0]][playerPosition[1]]++;
                        ItemAmount[i] -= 5;

                        system("cls");
                        getGraphics.setColor(7);

                        getGraphics.clearScreen();
                        getGraphics.drawTerrain(playerPosition[0], playerPosition[1]);
                        getGraphics.drawTree(World[playerPosition[0]][playerPosition[1]] % 100 / 10);
                        getGraphics.drawStone(World[playerPosition[0]][playerPosition[1]] % 100 / 10);
                        getGraphics.drawFurnace(World[playerPosition[0]][playerPosition[1]] % 100 / 10);

                        getGraphics.printScreen();
                        getPlayer.printHp(10);
                        cout << "" << endl;
                        getPlayer.printHungr(10);
                        cout << "" << endl;
                        getGraphics.printInventory(inventory);
                        cout << "" << endl;
                        cout << "" << endl;
                        getGraphics.drawMinimap(playerPosition[0], playerPosition[1]);
                        cout << endl;
                        if (getPlayer.getDegugState() == true) {
                            getEngine.printStats();
                        }
                        getEngine.tickHunger -= 1;
                    }
                }
            }
        }
        if (GetAsyncKeyState('A')) {
            if (World[playerPosition[0]][playerPosition[1]] % 100 / 10 == 3) {
                int g = 0;
                g = World[playerPosition[0]][playerPosition[1]] / 100 * 100;
                World[playerPosition[0]][playerPosition[1]] = g;
                system("cls");
                getGraphics.setColor(7);

                getGraphics.clearScreen();
                getGraphics.drawTerrain(playerPosition[0], playerPosition[1]);
                getGraphics.drawTree(World[playerPosition[0]][playerPosition[1]] % 100 / 10);
                getGraphics.drawStone(World[playerPosition[0]][playerPosition[1]] % 100 / 10);
                getGraphics.drawFurnace(World[playerPosition[0]][playerPosition[1]] % 100 / 10);

                getGraphics.printScreen();
                getPlayer.printHp(10);
                cout << "" << endl;
                getPlayer.printHungr(10);
                cout << "" << endl;
                getGraphics.printInventory(inventory);
                cout << "" << endl;
                cout << "" << endl;
                getGraphics.drawMinimap(playerPosition[0], playerPosition[1]);
                cout << endl;
                if (getPlayer.getDegugState() == true) {
                    getEngine.printStats();
                }
                getEngine.tickHunger -= 1;
            }
        }
        if (GetAsyncKeyState('B')) {
            //build
            if (World[playerPosition[0]][playerPosition[1]] % 10 == 0 && World[playerPosition[0]][playerPosition[1]] % 100 / 10 == 0) {
                for (int i = 0; i < inventory.size(); i++) {
                    if (inventory[i] == 1) {
                        if (ItemAmount[i] > 0) {
                            World[playerPosition[0]][playerPosition[1]]++;
                            ItemAmount[i]--;
                            system("cls");
                            getGraphics.setColor(7);

                            getGraphics.clearScreen();
                            getGraphics.drawTerrain(playerPosition[0], playerPosition[1]);
                            getGraphics.drawTree(World[playerPosition[0]][playerPosition[1]] % 100 / 10);
                            getGraphics.drawStone(World[playerPosition[0]][playerPosition[1]] % 100 / 10);
                            getGraphics.drawFurnace(World[playerPosition[0]][playerPosition[1]] % 100 / 10);

                            getGraphics.printScreen();
                            getPlayer.printHp(10);
                            cout << "" << endl;
                            getPlayer.printHungr(10);
                            cout << "" << endl;
                            getGraphics.printInventory(inventory);
                            cout << "" << endl;
                            cout << "" << endl;
                            getGraphics.drawMinimap(playerPosition[0], playerPosition[1]);
                            cout << endl;
                            if (getPlayer.getDegugState() == true) {
                                getEngine.printStats();
                            }
                            getEngine.tickHunger -= 1;
                        }
                    }
                }
            }
        }
        if (GetAsyncKeyState(VK_SPACE)) {
            if (World[playerPosition[0]][playerPosition[1]] % 100 / 10 == 1 && World[playerPosition[0]][playerPosition[1]] / 100 != 6) {
                int g = 0;
                g = World[playerPosition[0]][playerPosition[1]] / 100 * 100;
                World[playerPosition[0]][playerPosition[1]] = g;
                bool foundItem = false;
                for (int i = 0; i < inventory.size(); i++) {
                    if (inventory[i] == 1) {
                        ItemAmount[i] += 1;
                        foundItem = true;
                    }
                }
                if (foundItem == false) {
                    inventory.push_back(1);
                    ItemAmount.push_back(1);
                }
                system("cls");
                getGraphics.setColor(7);

                getGraphics.clearScreen();
                getGraphics.drawTerrain(playerPosition[0], playerPosition[1]);
                getGraphics.drawTree(World[playerPosition[0]][playerPosition[1]] % 100 / 10);
                getGraphics.drawStone(World[playerPosition[0]][playerPosition[1]] % 100 / 10);
                getGraphics.drawFurnace(World[playerPosition[0]][playerPosition[1]] % 100 / 10);

                getGraphics.printScreen();
                getPlayer.printHp(10);
                cout << "" << endl;
                getPlayer.printHungr(10);
                cout << "" << endl;
                getGraphics.printInventory(inventory);
                cout << "" << endl;
                getGraphics.drawMinimap(playerPosition[0], playerPosition[1]);
                cout << endl;
                if (getPlayer.getDegugState() == true) {
                    getEngine.printStats();
                }
                getEngine.tickHunger -= 1;
            }

            if (World[playerPosition[0]][playerPosition[1]] % 100 / 10 == 2) {
                int g = 0;
                g = World[playerPosition[0]][playerPosition[1]] / 100 * 100;
                World[playerPosition[0]][playerPosition[1]] = g;
                bool foundItem = false;
                for (int i = 0; i < inventory.size(); i++) {
                    if (inventory[i] == 2) {
                        ItemAmount[i] += 1;
                        foundItem = true;
                    }
                }
                if (foundItem == false) {
                    inventory.push_back(2);
                    ItemAmount.push_back(1);
                }
                system("cls");
                getGraphics.setColor(7);

                getGraphics.clearScreen();
                getGraphics.drawTerrain(playerPosition[0], playerPosition[1]);
                getGraphics.drawTree(World[playerPosition[0]][playerPosition[1]] % 100 / 10);
                getGraphics.drawStone(World[playerPosition[0]][playerPosition[1]] % 100 / 10);
                getGraphics.drawUndergroundEnter(World[playerPosition[0]][playerPosition[1]] % 100 / 10);
                getGraphics.drawFurnace(World[playerPosition[0]][playerPosition[1]] % 100 / 10);

                getGraphics.printScreen();
                getPlayer.printHp(10);
                cout << "" << endl;
                getPlayer.printHungr(10);
                cout << "" << endl;
                getGraphics.printInventory(inventory);
                cout << "" << endl;
                getGraphics.drawMinimap(playerPosition[0], playerPosition[1]);
                cout << endl;
                if (getPlayer.getDegugState() == true) {
                    getEngine.printStats();
                }
                getEngine.tickHunger -= 1;
            }
        }

        return velocity;
    }
};
class world {
    controls getPlayerControls;
    player getPlayer;
private:
    int treeHp;
public:
    void setTreeHp(int structure) {
        if (structure == 1) {
            treeHp = 10;
        }
    }
    void hurtTree(int structure) {
        if (GetAsyncKeyState(VK_SPACE) && structure == 1) {
            treeHp -= getPlayer.getDamage();
        }
    }
    int getTreeHp() {
        return treeHp;
    }
    void killTree(int structure, int curHp) {
        curHp = getTreeHp();
        if (structure == 1 && curHp == 0) {
            int temp = World[playerPosition[0]][playerPosition[1]] / 100 * 100;
            int stru = World[playerPosition[0]][playerPosition[1]] % 100 / 10 * 10;
            int safe = World[playerPosition[0]][playerPosition[1]] % 10;
            stru = 0;
            World[playerPosition[0]][playerPosition[1]] = temp + stru + safe;
        }
    }
};

void menu() {
    string menuButtons[2];
}

int main() {
    graphics graphicsHandler;
    userInterface uiHandler;
    engine engineHandler;
    player player;
    controls controlsHandler;
    world getWorld;
    engineHandler.rainbow();
    graphicsHandler.setColor(11);
    system("cls");
    Sleep(200);
    engineHandler.undergroundGeneration(5000, 5000);
    /*for (int i=0; i<1000; i++) {
        for (int ii=0; ii<1000; ii++) {
            cout<<world[i][ii];
        }
        cout<<""<<endl;
    }*/
    system("cls");
    cout << World[playerPosition[0]][playerPosition[1]] << endl;
    system("cls");
    while (1) {
        engineHandler.chunkGeneration(playerPosition[0], playerPosition[1]);
        graphicsHandler.setColor(7);

        graphicsHandler.clearScreen();
        if (under == false) {
            graphicsHandler.drawTerrain(playerPosition[0], playerPosition[1]);
            graphicsHandler.drawTree(World[playerPosition[0]][playerPosition[1]] % 100 / 10);
            graphicsHandler.drawStone(World[playerPosition[0]][playerPosition[1]] % 100 / 10);
            graphicsHandler.drawUndergroundEnter(World[playerPosition[0]][playerPosition[1]] % 100 / 10);
            graphicsHandler.drawFurnace(World[playerPosition[0]][playerPosition[1]] % 100 / 10);
        }

        graphicsHandler.printScreen();
        player.printHp(10);
        cout << "" << endl;
        player.printHungr(10);
        cout << "" << endl;
        graphicsHandler.printInventory(inventory);
        cout << "" << endl;
        graphicsHandler.drawMinimap(playerPosition[0], playerPosition[1]);
        cout << endl;
        if (player.getDegugState() == true) {
            engineHandler.printStats();
        }
        if (engineHandler.tickHunger == 0) {
            engineHandler.tickHunger = 5;
        }
        /*
        while(1) {
            Sleep(10);
            controlsHandler.input();
            player.switchDebug();
            engineHandler.borders();
            if (controlsHandler.input()==1) {
                engineHandler.borders();
                break;
            }
        }*/
        /*
        Sleep(10);
        controlsHandler.input();
        player.switchDebug();
        engineHandler.borders();
        if (controlsHandler.input()==1) {
            engineHandler.borders();
        }*/

        while (1) {
            controlsHandler.input();
            if (GetAsyncKeyState(VK_UP)) {
                playerPosition[0] -= 1;
                engineHandler.tickHunger -= 1;
                break;
            }
            if (GetAsyncKeyState(VK_DOWN)) {
                playerPosition[0] += 1;
                engineHandler.tickHunger -= 1;
                break;
            }
            if (GetAsyncKeyState(VK_RIGHT)) {
                playerPosition[1] += 1;
                engineHandler.tickHunger -= 1;
                break;
            }
            if (GetAsyncKeyState(VK_LEFT)) {
                playerPosition[1] -= 1;
                engineHandler.tickHunger -= 1;
                break;
            }
            if (GetAsyncKeyState(VK_ESCAPE)) {
                exit(0);
            }
            engineHandler.borders();
        }
        Sleep(50);
        system("cls");
    }
}