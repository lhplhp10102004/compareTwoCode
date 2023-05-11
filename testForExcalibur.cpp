#include<iostream>
#include<cstdlib>
#include<fstream>

#define MAX_KNIGHTS 50
#define MAX_EVENTS  100

using namespace std;

int ranInt(int min, int max)
{
    int range = max - min + 1;
    return rand() % range + min;
}

int main()
{
    srand(time(NULL));

    ofstream fileArmyKnights("test1");
    ofstream fileEvents("test2");

    // GENERATE ARMYKNIGHT FILE
    int numOfKnight = ranInt(1, MAX_KNIGHTS);     // Random number of knights
    fileArmyKnights << numOfKnight << endl;
    for (int i = 1; i <= numOfKnight; ++i)
    {
        int hp = ranInt(1, 999);
        int level = ranInt(1, 10);
        int phoenixDown = ranInt(0, 5);
        int gil = ranInt(1, 999);
        int antidote = ranInt(0, 5); 
        
        fileArmyKnights << hp << ' ' << level << ' ' << phoenixDown << ' ' << gil << ' ' << antidote << endl;
    }

    // GENERATE EVENTS FILE
    int events[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 112, 113, 114, 95, 96, 97, 98, 99};
    int numOfEvent = ranInt(1, MAX_EVENTS);
    fileEvents << numOfEvent << endl;
    for (int i = 1; i <= numOfEvent; ++i)
    {
        int eventID = events[ranInt(0, sizeof(events)/sizeof(events[0]) - 1)];
        fileEvents << eventID << ' ';
    }

    return 2;
}