#include "Harvester.h"
#include "Toriverse.h"
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
    size_t foundEnergy = line.find("Harvester Energy: ");
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
  xMom = 0;
  yMom = 0;
  HStatus = 1;

}

Harvester::~Harvester(){}

void Harvester::HarvesterCMD(Toriverse& T, char cmd){
  if (HStatus && (Energy>=0)){

    if ((cmd =='w') || (cmd == 'X') || (cmd == 'x') || (cmd == 'Y') || (cmd == 'y')){

      if (cmd == 'w'){
	cout << "WAIT!" << endl;
	xPos = modH(xPos + xMom, T.getXDim());
	yPos = modH(yPos + yMom, T.getYDim());
      }
      
      if (cmd=='X'){
	Energy--;
	xMom++;
	xMom = modH(xMom, T.getXDim());
	xPos = modH(xPos + xMom, T.getXDim());
	yPos = modH(yPos + yMom, T.getYDim());

      }
      
      else if (cmd=='x'){
	Energy--;
	xMom--;
	xMom = modH(xMom, T.getXDim());
	xPos = modH(xPos + xMom, T.getXDim());
	yPos = modH(yPos + yMom, T.getYDim());
      }
      else if (cmd=='y'){
	yMom--;
	Energy--;
	yMom = modH(yMom, T.getYDim());
	xPos = modH(xPos + xMom, T.getXDim());
	yPos = modH(yPos + yMom, T.getYDim());

      }
      else if (cmd == 'Y'){
	Energy--;
	yMom++;
	yMom = modH(yMom, T.getYDim());
	xPos = modH(xPos + xMom, T.getXDim());
	yPos = modH(yPos + yMom, T.getYDim());

      }
      if(Energy < 0){
	setStatus(0);
	setScore(0);
	setFate("Harvester destroyed because of Energy < 0");
      }
      
    }
      
    else if (cmd == 'e') {
      if ((xMom!=0) || (yMom!=0)){
	setFate("Error: Cannot end with momentum not 0!");
	setStatus(0);
	setScore(0);
      }
      else if (T.getNSLocks() != 0){
	setFate("Error: Space locks remain!");
	setStatus(0);
	setScore(0);
      }
      else {
	Score = Energy + T.getLifeTime();
	setStatus(0);
	setFate("Harvester exited safely");
      }
    }
    else {
      cout << "Error: Invalid command!" << endl;
      setStatus(0);
      setScore(0);
      setFate("Harvester destroyed by false command");
    }
    
  }
      

  else {
    if (!HStatus) {
      setFate("Error: Destroyed by Black Hole!");
	}
    if (Energy<0) {
      cout << "Error: negative energy";
      setStatus(0);
    }
  }
}
