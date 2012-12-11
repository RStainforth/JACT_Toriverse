#include "Harvester.h"
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <istream>
#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include <fstream>
#include <vector>

using namespace std;

// Constructor: Defaults NULL harvester
Harvester::Harvester(){
  xPos = 0;
  yPos = 0;
  xMom = 0;
  yMom = 0;
  Energy = 0;
  Score = 0;
  HStatus = 1;
}

// Constructor: Default to NULL Toriverse with given momentum
Harvester::Harvester(char* filename){
  ifstream toriSpec(filename);
  toriSpec.seekg(0);

  string line;
  string val;

  while(!toriSpec.eof()){
    getline(toriSpec, line);
    size_t foundEnergy = line.find('Harvester Energy: ');
    size_t foundPos = line.find("Harvester Position: ");
    size_t foundLifeTime = line.find("Lifetime: ");

    if(foundEnergy!=string::npos){
      istringstream lineStr(line);
      vector<int> valsEnergy;
      while(getline(lineStr, val, ' ')){
  valsEnergy.push_back(atoi(val.c_str()));
      }
      Energy = valsEnergy[2];
    }

    if(foundPos!=string::npos){
      istringstream lineStr(line);
      vector<int> valsPos;
      while(getline(lineStr, val, ' ')){
	valsPos.push_back(atoi(val.c_str()));
      }
      xPos = valsPos[2];
      yPos = valsPos[3];
    }

    if(foundLifeTime!=string::npos){
      istringstream lineStr(line);
      vector<int> valsLife;
      while(getline(lineStr, val, ' ')){
	valsLife.push_back(atoi(val.c_str()));
      }
      Score = valsLife[1];
    }
    Score += Energy;

  }

  HStatus = 1;

}

Harvester::~Harvester(){}

Harvester::Command(Toriverse T, char cmd){
  if (HStatus && (Energy>0)){

    if (cmd=='w') {xPos += xMom; yPos += yMom;};
    else if (cmd=='X') {xMom++; xPos += xMom; yPos += yMom; Energy--;}
    else if (cmd=='x') {xMom--; xPos += xMom; yPos += yMom; Energy--;}
    else if (cmd=='Y') {yMom++; xPos += xMom; yPos += yMom; Energy--;}
    else if (cmd=='y') {yMom--; xPos += xMom; yPos += yMom; Energy--;}
    else if (cmd=='e') {
      if ((xMom%T.getXDim())!=0 || (yMom%T.getYDim())!=0){
	cout << "Error: Cannot end with momentum not 0!" << endl;
      }
      else {Score = Energy + T.getLifeTime();}
    }
    else {      cout << "Error: Invalid command!" << endl;}

  }

  else {
    if (!HStatus) cout << "Error: Destroyed by black hole";
    if (Energy<0) cout << "Error: negative energy";
  }
}
