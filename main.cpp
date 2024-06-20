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







                                   OOOOO
                               OOOOOOOOOOOOO
                            OOOOOOOOOOOOOOOOOOO
                           OOOOOOOOOOOOOOOOOOOOO
                          OOOOOOOOOOOOOOOOOOOOOOO
                          OOOOOOOOOOOOOOOOOOOOOOO
33333333333333333333333333333333333333333333333333333333333333333333333333333333

*/

// chunk attributes: temperature, structure, safe
// temp = -20(2)   |   19(1)   |    60(6)
// stru = 0-none 1-tree 2-stone 3-dungeon 4-playersmth
// safe = 0-no | 1-yes
int World[5000][5000];
int playerPosition[2] {0, 0};

class engine {
    public:
    int generator(int a, int b) {
        int result;
        result = a+rand()%b;
        return result; 
    }
    void rainbow() {
        for (int i=0; i<256; i++) {
            SetConsoleTextAttribute(hc, i);
            cout<<i<<endl;
        }
    }
    void borders() {
        if (playerPosition[0]<0) {
            playerPosition[0]=0;
        }
        if (playerPosition[1]<0) {
            playerPosition[1]=0;
        }
    }
    void overWorldGeneration(int w, int l) {
        for (int y=0; y<w; y++) {
            for (int x=0; x<l; x++) {
                int genRes = generator(0, 3);
                // Biome
                if (genRes==0) {
                    World[y][x]=2*100;
                }
                if (genRes==1) {
                    World[y][x]=1*100;
                }
                if (genRes==2) {
                    World[y][x]=6*100;
                }
                // stru
                genRes = generator(0, 4);
                if (genRes==0) {
                    World[y][x]+=1*10;
                }
                if (genRes==1 && World[y][x]/100!=6) {
                    World[y][x]+=2*10;
                }
                if (genRes==2) {
                    World[y][x]+=3*10;
                }
                if (genRes==3) {
                    World[y][x]+=4*10;
                }
            }
        }
    }
};
class graphics {
    engine engReference;
    public:
    void printScreen() {
        for (int y=0; y<25; y++) {
            for (int x=0; x<81; x++) {
                if (y>=20) {
                    grass();
                }
                if (y>=8 && y<14) {
                    if ((World[playerPosition[0]][playerPosition[1]]/100) == 1 && (World[playerPosition[0]][playerPosition[1]]/100) != 6) {
                        setColor(10);
                    }
                }
                if (y>=14 && y<20) { //8
                    if ((World[playerPosition[0]][playerPosition[1]]/100) == 1 || (World[playerPosition[0]][playerPosition[1]]/100) == 2 && (World[playerPosition[0]][playerPosition[1]]/100) != 6) {
                        setColor(8);
                    }
                }
                cout<<screen[y][x];
            }
            cout<<""<<endl;
        }
    }
    void clearScreen() {
        for (int y=0; y<25; y++) {
            for (int x=0; x<81; x++) {
                screen[y][x] = " ";
            }
        }
    }

    void drawTerrain() {
        for (int y=24; y>20; y--) {
            for (int x=0; x<81; x++) {
                if ((World[playerPosition[0]][playerPosition[1]]/100) == 1) {
                    screen[y][x]="|";
                }
                if ((World[playerPosition[0]][playerPosition[1]]/100) == 2) {
                    screen[y][x]="*";
                }
                if ((World[playerPosition[0]][playerPosition[1]]/100) == 6) {
                    screen[y][x]="#";
                }
            }
        }
    }
    void drawTree(int biome) {
        if (biome == 1 && World[playerPosition[0]][playerPosition[1]]/100 != 6) {
            // draw log
            for (int y=14; y<20; y++) {
                screen[y][35]="#"; 
            }
            // draw leaves
            for (int y=8; y<14; y++) {
                if (y==8 || y==13) {
                    for (int x=31; x<40; x++) {
                        screen[y][x]="Q";
                    }
                }
                if (y>8 && y<13) {
                    for (int x=27; x<44; x++) {
                        screen[y][x]="Q";
                    }
                }
            }
        }
    }
    void drawStone(int structure) {
        if (structure == 2) {
            for (int y=14; y<20; y++) {
                if (y==14) {
                    for (int x=35; x<40; x++) {
                        screen[y][x]="O";
                    }
                }
                if (y==15) {
                    for (int x=31; x<44; x++) {
                        screen[y][x]="O";
                    }
                }
                if (y==16) {
                    for (int x=28; x<47; x++) {
                        screen[y][x]="O";
                    }
                }
                if (y==17) {
                    for (int x=27; x<48; x++) {
                        screen[y][x]="O";
                    }
                }
                if (y>17 && y<20) {
                    for (int x=26; x<49; x++) {
                        screen[y][x]="O";
                    }
                }
            }
        }
    }

    void grass() {
        if ((World[playerPosition[0]][playerPosition[1]]/100) == 1) {
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
        if ((World[playerPosition[0]][playerPosition[1]]/100) == 2) {
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
        if ((World[playerPosition[0]][playerPosition[1]]/100) == 6) {
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
    }
    void setColor(int color) { // color E [0, 15]
        SetConsoleTextAttribute(hc, color);
    }
    void printActions() {
        cout<<""<<endl;
    }
};
class userInterface {
    public:
    void coutDelay(int amount) {
        for (int i=0; i<amount; i++) {
            cout<<""<<endl;
        }
    }
};
class player {
    userInterface ui;
    graphics graphcs;

    private:
    bool debugMode=false;
    int playerDamage=5;
    int hpAm=10;
    int hungerAm=10;
    int playerInventory;
    vector<string> hpUI {"X", "X", "X", "X", "X", "X", "X", "X", "X", "X"};
    vector<string> hungrUI {"X", "X", "X", "X", "X", "X", "X", "X", "X", "X"};

    public:
    int getDamage() {
        return playerDamage;
    }
    void switchDebug() {
        if (GetAsyncKeyState(VK_F3)) {
            debugMode=true;
        }
        if (GetAsyncKeyState(VK_F4)) {
            debugMode=false;
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
        playerPosition[0]+=n/*/2*/;
    }
    void changePPosX(int n) {
        playerPosition[1]+=n/*/2*/;
    }
    void printHp(int hp) {
        graphcs.setColor(1);
        cout<<"Health - ";
        for (int i=0; i<hp-1; i++) {
            graphcs.setColor(12);
            cout<<hpUI[i];
        }
    }
    void printHungr(int hunger) {
        graphcs.setColor(1);
        cout<<"Hunger - ";
        for (int i=0; i<hunger-1; i++) {
            graphcs.setColor(7);
            cout<<hungrUI[i];
        }
        ui.coutDelay(1);
    }
};
class controls {
    player getPlayer;
    graphics getGraphics;
    public:
    int input() {
        int velocity = 0;
        if (GetAsyncKeyState(VK_UP)) {
            getPlayer.changePPosY(-1); // upper in array
            velocity=1;
        }
        if (GetAsyncKeyState(VK_DOWN)) {
            getPlayer.changePPosY(1); // lower in array
            velocity=1;
        }
        if (GetAsyncKeyState(VK_RIGHT)) {
            getPlayer.changePPosX(1);
            velocity=1;
        }
        if (GetAsyncKeyState(VK_LEFT)) {
            getPlayer.changePPosX(-1);
            velocity=1;
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
        if (structure==1) {
            treeHp=10;
        }
    }
    void hurtTree(int structure) {
        if (GetAsyncKeyState(VK_SPACE) && structure==1) {
            treeHp-=getPlayer.getDamage();
        }
    }
    int getTreeHp() {
        return treeHp;
    }
    void killTree(int structure, int curHp) {
        curHp=getTreeHp();
        if (structure==1 && curHp==0) {
            int temp = World[playerPosition[0]][playerPosition[1]]/100*100;
            int stru = World[playerPosition[0]][playerPosition[1]]%100/10*10;
            int safe = World[playerPosition[0]][playerPosition[1]]%10;
            stru=0;
            World[playerPosition[0]][playerPosition[1]] = temp+stru+safe;
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
    cout<<"Generating ...";
    engineHandler.overWorldGeneration(5000, 5000);
    /*for (int i=0; i<1000; i++) {
        for (int ii=0; ii<1000; ii++) {
            cout<<world[i][ii];
        }
        cout<<""<<endl;
    }*/
    cout<<"Generated successfully!"<<endl;
    Sleep(150);
    system("cls");
    cout<<World[playerPosition[0]][playerPosition[1]]<<endl;
    Sleep(150);
    system("cls");
    while (1) {
        graphicsHandler.setColor(7);

        graphicsHandler.clearScreen();
        graphicsHandler.drawTerrain();
        graphicsHandler.drawTree(World[playerPosition[0]][playerPosition[1]]%100/10);
        graphicsHandler.drawStone(World[playerPosition[0]][playerPosition[1]]%100/10);

        graphicsHandler.printScreen();
        player.printHp(10);
        cout<<""<<endl;
        player.printHungr(10);
        cout<<""<<endl;
        if (player.getDegugState()==true) {
            cout<<playerPosition[0]<<" "<<playerPosition[1]<<endl;
            cout<<World[playerPosition[0]][playerPosition[1]]<<endl;
        }
        while(1) {
            Sleep(100);
            controlsHandler.input();
            player.switchDebug();
            engineHandler.borders();
            if (controlsHandler.input()!=0) {
                engineHandler.borders();
                break;
            }
        }
        Sleep(50);
        system("cls");
    }
}