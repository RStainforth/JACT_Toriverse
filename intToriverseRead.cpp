#include "Toriverse.h"
#include "Harvester.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstring>

//class string;
using namespace std;

int main( int argc, char** argv ){
  cout << "Welcome to the Toriverse!" << endl;
  cout << endl;
  cout << "Map Loaded is: ";
  
  char str[80];
  strcpy (str,argv[1]);
  strcat (str,".map");
  puts (str);                 //cout of string

  Toriverse testTori(str);
  Harvester testHarvey(str);


  cout << "Before interaction" << endl; 
  testTori.printMap();  

  char str0[80];
  strcpy (str0,argv[1]);
  strcat (str0,".hpg");
  //puts (str0);

  ifstream harveyWay(str0);
  harveyWay.seekg(0);
  string cmdLine;
  getline(harveyWay, cmdLine);  //read command line


  char cmd;
  for(int i=0; i<cmdLine.size(); i++){
    cmd = cmdLine[i];
    testHarvey.HarvesterCMD(testTori, cmd);   //send cmd to harvester
    testTori.Interaction(testHarvey);         //interaction of harvester with toriverse
  }


  cout << "\nAfter harvester" <<endl;
  testTori.printMap();

  cout << "END OF HARVEST" << endl;
  cout << endl;
  cout << "Your fate is: " << testHarvey.getFate() << endl;
  cout <<"Energy is: " << testHarvey.getEnergy() << endl;
  cout <<"LifeTime is: " << testTori.getLifeTime() << endl;
  cout << "Your Score is: " << testHarvey.getScore() << endl;

}


