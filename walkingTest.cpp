#include <iostream>
#include <vector>
#include <string>
#include <Windows.h>
#include <conio.h>


using namespace std;
int map[10][10];
int pPos[2];

int main() {
    while (1) {
        system("cls");
        if (GetAsyncKeyState(VK_UP)) {
            pPos[0]-=1;
        }
        if (GetAsyncKeyState(VK_DOWN)) {
            pPos[0]+=1;
        }
        if (GetAsyncKeyState(VK_RIGHT)) {
            pPos[1]+=1;
        }
        if (GetAsyncKeyState(VK_LEFT)) {
            pPos[1]-=1;
        }
        cout<<pPos[0]<<" "<<pPos[1]<<endl;
        Sleep(10);
    }
}