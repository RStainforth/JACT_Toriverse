#include "Toriverse.h"
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

// Constructor: Defaults NULL toriverse
Toriverse::Toriverse(){
  xDim = 1;
  yDim = 1;
  energyDensity = 0;
  lifeTime = 1;
  status = 1;
  nSLocks = 0;
}

// Constructor: Default to NULL Toriverse with given momentum
Toriverse::Toriverse(char* filename){
  nSLocks = 0;
  ifstream toriSpec(filename);
  toriSpec.seekg(0);       //set position to 0

  string line;
  string val;
 
  getline(toriSpec, line);   //read line in file
  istringstream lineStr(line);

  vector<int> valsDim;
  while(getline(lineStr, val, 'x')){
    valsDim.push_back(atoi(val.c_str()));
  }
  xDim = valsDim[0];           
  yDim = valsDim[1];
  
  Map.resize(xDim);
  for (int i =0; i < xDim; i++){
    Map[i].resize(yDim);
  }

  WHoles.resize(26);
  
  for(int i=0;i<yDim;i++){
    getline(toriSpec, line);//loop to read map
    for (int j = 0; j < line.length(); j++){
      Map[j][yDim-i-1] = line[j];
      if (line[j] == '\\'){
  nSLocks++;
      }
      if (96 < (int(line[j])) && (int(line[j])) < 123){
	vector<int> tmpVec(0);
	tmpVec.push_back(j);
	tmpVec.push_back(yDim-i-1);
	WHoles[int(line[j])-97].push_back(tmpVec);
      }
    }
  }

  getline(toriSpec, line);   //read line in file
  istringstream lineStrB(line);
  
  vector<int> valsLife;
  while(getline(lineStrB, val, ' ')){
    valsLife.push_back(atoi(val.c_str()));
  }
  lifeTime = valsLife[1];
  
  getline(toriSpec, line);   //read line in file
  istringstream lineStrC(line);
  
  vector<int> valsEngD;
  while(getline(lineStrC, val, ' ')){
    valsEngD.push_back(atoi(val.c_str()));
  }
  energyDensity = valsEngD[2];
  
  
  if (lifeTime > 0){
    status = 1;
  }
  else{
    status = 0;
  }
}

Toriverse::~Toriverse(){}

void Toriverse::Interaction(Harvester& Harvey){
  int tmpVecPosX = Harvey.getXPos();
  int tmpVecPosY = Harvey.getYPos();

  if (getObject(tmpVecPosX,tmpVecPosY)=="."){
    timeStep();
  }

  else if (getObject(tmpVecPosX,tmpVecPosY)=="*"){
    setObject(".",tmpVecPosX,tmpVecPosY);
    Harvey.setEnergy(energyDensity);
    timeStep();
  }

  else if (getObject(tmpVecPosX,tmpVecPosY)=="@"){
    Harvey.setScore(0);
    Harvey.setStatus(0);
    timeStep();
  }

  else if (getObject(tmpVecPosX,tmpVecPosY)=="//"){
    setObject(".",tmpVecPosX,tmpVecPosY);
    nSLocks--;
    timeStep();
  }

  else if (96 < atoi((getObject(tmpVecPosX,tmpVecPosY)).c_str()) &&
	   atoi((getObject(tmpVecPosX,tmpVecPosY)).c_str()) < 123){
    int lTmp = atoi((getObject(tmpVecPosX,tmpVecPosY)).c_str()) - 97;
    if (tmpVecPosX == getWHolePos(lTmp,0,0) &&
	tmpVecPosY == getWHolePos(lTmp,0,1)){
      Harvey.setXPos(getWHolePos(lTmp,1,0));
      Harvey.setYPos(getWHolePos(lTmp,1,1));
    }
    else if (tmpVecPosX == getWHolePos(lTmp,1,0) &&
	     tmpVecPosY == getWHolePos(lTmp,1,1)){
      Harvey.setXPos(getWHolePos(lTmp,0,0));
      Harvey.setYPos(getWHolePos(lTmp,0,1));    
    }
  }
  timeStep();
}
		     




