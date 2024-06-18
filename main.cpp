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
// stru = 0-none | 1-tree | 2-stone | 3-dungeon | 4-wall/furniture
// safe = 0-no | 1-yes
int world[20000][20000];
int playerPosition[2] {6, 6};

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
            playerPosition[0]+=1;
        }
        if (playerPosition[1]<0) {
            playerPosition[1]+=1;
        }
    }
    void overWorldGeneration(int w, int l) {
        for (int y=0; y<w; y++) {
            int cycle=2000;
            for (int x=0; x<l; x++) {
                int genRes = generator(0, 3);
                // Biome
                if (genRes==0) {
                    world[y][x]=2*100;
                }
                if (genRes==1) {
                    world[y][x]=1*100;
                }
                if (genRes==2) {
                    world[y][x]=6*100;
                }
                // stru
                genRes = generator(0, 4);
                if (genRes==0) {
                    world[y][x]+=1*10;
                }
                if (genRes==1 && world[y][x]/100!=6) {
                    world[y][x]+=2*10;
                }
                if (genRes==2) {
                    world[y][x]+=3*10;
                }
                if (genRes==3) {
                    world[y][x]+=4*10;
                }
            }
            cout<<"Generating ";
            int am=1;
            switch (y/2)
            {
            case 2000:
                am=2;
                break;
            case 3000:
                am=3;
                break;
            case 4000:
                am=4;
                break;
            case 5000:
                am=5;
                break;
            case 6000:
                am=6;
                break;
            case 7000:
                am=7;
                break;
            case 8000:
                am=8;
                break;
            case 9000:
                am=9;
                break;
            case 10000:
                am=10;
                break;
            }
            for (int ii=0; ii<am; ii++) {
                cout<<".";
                Sleep(20);
            }
            Sleep(100);
            system("cls");
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
                    if ((world[playerPosition[0]][playerPosition[1]]/100) == 1 && (world[playerPosition[0]][playerPosition[1]]/100) != 6) {
                        setColor(10);
                    }
                }
                if (y>=14 && y<20) { //8
                    if ((world[playerPosition[0]][playerPosition[1]]/100) == 1 || (world[playerPosition[0]][playerPosition[1]]/100) == 2 && (world[playerPosition[0]][playerPosition[1]]/100) != 6) {
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
                if ((world[playerPosition[0]][playerPosition[1]]/100) == 1) {
                    screen[y][x]="|";
                }
                if ((world[playerPosition[0]][playerPosition[1]]/100) == 2) {
                    screen[y][x]="*";
                }
                if ((world[playerPosition[0]][playerPosition[1]]/100) == 6) {
                    screen[y][x]="#";
                }
            }
        }
    }
    void drawTree(int biome) {
        if (biome == 2 && world[playerPosition[0]][playerPosition[1]]/100 != 6) {
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
        if (structure == 3) {
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
        if ((world[playerPosition[0]][playerPosition[1]]/100) == 1) {
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
        if ((world[playerPosition[0]][playerPosition[1]]/100) == 2) {
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
        if ((world[playerPosition[0]][playerPosition[1]]/100) == 6) {
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
    int hpAm=10;
    int hungerAm=10;
    vector<string> hpUI {"X", "X", "X", "X", "X", "X", "X", "X", "X", "X"};
    vector<string> hungrUI {"X", "X", "X", "X", "X", "X", "X", "X", "X", "X"};

    public:
    int getPPosY() {
        return playerPosition[0];
    }
    int getPPosX() {
        return playerPosition[1];
    }
    void changePPosY(int n) {
        playerPosition[0]+=n;
    }
    void changePPosX(int n) {
        playerPosition[1]+=n;
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
class structures {
    // tree | stone | burned tree | dungeon entrance
};

int main() {
    graphics graphicsHandler;
    userInterface uiHandler;
    engine engineHandler;
    player player;
    controls controlsHandler;
    engineHandler.rainbow();
    graphicsHandler.setColor(11);
    system("cls");
    Sleep(200);
    engineHandler.overWorldGeneration(20000, 20000);
    /*for (int i=0; i<1000; i++) {
        for (int ii=0; ii<1000; ii++) {
            cout<<world[i][ii];
        }
        cout<<""<<endl;
    }*/
    cout<<"Generated successfully!"<<endl;
    system("cls");
    cout<<world[playerPosition[0]][playerPosition[1]]<<endl;
    Sleep(150);
    while (1) {
        graphicsHandler.setColor(7);

        graphicsHandler.clearScreen();
        graphicsHandler.drawTerrain();
        graphicsHandler.drawTree(world[playerPosition[0]][playerPosition[1]]%100/10);
        graphicsHandler.drawStone(world[playerPosition[0]][playerPosition[1]]%100/10);

        graphicsHandler.printScreen();
        player.printHp(10);
        cout<<""<<endl;
        player.printHungr(10);
        cout<<""<<endl;
        cout<<playerPosition[0]<<" "<<playerPosition[1]<<endl;
        cout<<world[playerPosition[0]][playerPosition[1]]<<endl;
        while(1) {
            controlsHandler.input();
            engineHandler.borders();
            if (controlsHandler.input()!=0) {
                engineHandler.borders();
                break;
            }
        }
        Sleep(100);
        system("cls");
    }
}