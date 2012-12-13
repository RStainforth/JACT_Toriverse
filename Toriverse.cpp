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
      else if (64 < (int(line[j])) && (int(line[j])) < 91){
	nSLocks++;
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
  //cout << "INT Val of WHole is: " << int((getObject(tmpVecPosX,tmpVecPosY)).at(0)) << endl;

  if (getObject(tmpVecPosX,tmpVecPosY)=="."){}

  else if (getObject(tmpVecPosX,tmpVecPosY)=="*"){
    setObject(".",tmpVecPosX,tmpVecPosY);
    Harvey.setEnergy(energyDensity);

  }

  else if (getObject(tmpVecPosX,tmpVecPosY)=="@"){
    Harvey.setScore(0);
    Harvey.setStatus(0);
    Harvey.setFate("DESTOYED BY BLACK HOLE!");

  }

  else if (getObject(tmpVecPosX,tmpVecPosY)=="\\"){
    setObject(".",tmpVecPosX,tmpVecPosY);
    nSLocks--;
    cout << "SSLock Removed!" << endl;
  }

  else if ((96 < int((getObject(tmpVecPosX,tmpVecPosY)).at(0)) &&
	    int((getObject(tmpVecPosX,tmpVecPosY)).at(0)) < 123))
    {
      int lTmp = int((getObject(tmpVecPosX,tmpVecPosY)).at(0)) - 97;
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

  else if ((64 < int((getObject(tmpVecPosX,tmpVecPosY)).at(0)) &&
	    int((getObject(tmpVecPosX,tmpVecPosY)).at(0)) < 91))
    {
      
      int lTmp = int((getObject(tmpVecPosX,tmpVecPosY)).at(0)) - 65;
      if (MLockStore.empty()){
	vector<int> tmpVecML;
	tmpVecML.push_back(tmpVecPosX);
	tmpVecML.push_back(tmpVecPosY);
	MLockStore.push_back(tmpVecML);
	lastMLock = lTmp;
      }
      else if (!MLockStore.empty() && lastMLock == lTmp){
	vector<int> tmpVecML;
	tmpVecML.push_back(tmpVecPosX);
	tmpVecML.push_back(tmpVecPosY);
	MLockStore.push_back(tmpVecML);
	setObject(".",MLockStore[0][0],MLockStore[0][1]);
	setObject(".",MLockStore[1][0],MLockStore[1][1]);
	nSLocks--;
    	cout << "MSLock Removed!" << endl;
	while(!MLockStore.empty()){
	  MLockStore.pop_back();
	}
      }
      else if (!MLockStore.empty() && lastMLock != lTmp){
	while(!MLockStore.empty()){
	  MLockStore.pop_back();
	}
	vector<int> tmpVecML;
	tmpVecML.push_back(tmpVecPosX);
	tmpVecML.push_back(tmpVecPosY);
	MLockStore.push_back(tmpVecML);
	lastMLock = lTmp;
      }
    }
  
  timeStep();
}
		     





