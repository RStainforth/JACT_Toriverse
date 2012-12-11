// Prevents the toriverse header file being included more than once
#ifndef TORIVERSE_h
#define TORIVERSE_h

#include <string>
#include <vector>

using namespace std;

class Toriverse {

public:

  // Constructors and destructors
  Toriverse();
  Toriverse(char* filename);
  ~Toriverse();

  void Interaction(Harvester& Harvey);
  //void objectInteract(char* object);
  //void harvester
  
  // Setters...

  //void setObject(char* ToriObject, int xPos, int yPos);
  //void timeStep(char cmd);
  //void destroyToriverse();

  //  Getters ...

  //char getObject(int xPos, int yPos); 
  int getXDim() const {return xDim;}
  int getYDim() const {return yDim;}
  int getLifeTime() {return lifeTime;}
  int getEnergyDensity() {return energyDensity;}
  int getStatus() {return status;}
  
  std::string getObject(int xPos, int yPos) {
  return Map[xPos][yPos];
  }

protected:

  int xDim;
  int yDim;
  int lifeTime;
  int energyDensity;
  int status;
  std::vector<std::vector<std::string> >  Map;

  int nSLocks;


};

#endif
