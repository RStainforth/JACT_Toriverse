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
    }

  }
  xMom = 0;
  yMom = 0;
  HStatus = 1;
  Score = 0;

}

Harvester::~Harvester(){}

void Harvester::HarvesterCMD(Toriverse& T, char cmd){
  if (HStatus && (Energy>=0) && T.getLifeTime() > 0){

    if ((cmd =='w') || (cmd == 'X') || (cmd == 'x') || (cmd == 'Y') || (cmd == 'y')){

      if (cmd == 'w'){
	xPos = modH(xPos + xMom, T.getXDim());
	yPos = modH(yPos + yMom, T.getYDim());
      }
      
      if (cmd=='X'){
	if (Energy == 0){
	  setStatus(0);
	  setFate("You ran out of Energy!");
	}
	else {
	  Energy--;
	  xMom++;
	  xMom = modH(xMom, T.getXDim());
	  xPos = modH(xPos + xMom, T.getXDim());
	  yPos = modH(yPos + yMom, T.getYDim());
	}
      }
      
      else if (cmd=='x'){
	if (Energy == 0){
	  setStatus(0);
	  setFate("You ran out of Energy!");
	}
	else{
	  Energy--;
	  xMom--;
	  xMom = modH(xMom, T.getXDim());
	  xPos = modH(xPos + xMom, T.getXDim());
	  yPos = modH(yPos + yMom, T.getYDim());
	}
      }
      else if (cmd=='y'){
	if (Energy == 0){
	  setStatus(0);
	  setFate("You ran out of Energy!");	  
	}
	else{
	  Energy--;
	  yMom--;
	  yMom = modH(yMom, T.getYDim());
	  xPos = modH(xPos + xMom, T.getXDim());
	  yPos = modH(yPos + yMom, T.getYDim());
	}
      }
      else if (cmd == 'Y'){
	if (Energy == 0){
	  setStatus(0);
	  setFate("You ran out of Energy!");
	}
	else{
	  Energy--;
	  yMom++;
	  yMom = modH(yMom, T.getYDim());
	  xPos = modH(xPos + xMom, T.getXDim());
	  yPos = modH(yPos + yMom, T.getYDim());
	}
      }
    }
      
    else if (cmd == 'e') {
      if ((xMom!=0) || (yMom!=0)){
	setFate("Error: Cannot end with momentum not 0!");
	setStatus(0);
	setScore(0);
      }
      else if (T.getNSLocks() != 0){
	setFate("Error: Space locks remain! Harvester DESTROYED!");
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
      setScore(0);
	}
    if (Energy<0) {
      setFate("Error: negative energy");
      setStatus(0);
      setScore(0);
      
    }
    if (T.getLifeTime() < 0){
      setStatus(0);
      setFate("Ran out of time!");
      setScore(0);
    }
  }
}
