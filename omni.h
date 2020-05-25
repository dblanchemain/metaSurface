#ifndef DEF_OMNI
#define DEF_OMNI

#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdlib.h>
#include <string>


class Omni{

 public :
  
  Omni();
  ~Omni();
  void setEtat(bool e);
  bool getEtat();
  
  void setDirectionParam(float x, float y);
  void setDirectionParamX(float x);
  void setDirectionParamY(float y);
  void setDirection(float x, float y);
  void setDirectionX(float x);
  void setDirectionY(float y);
  void setComptimeD(float t);
  void setComptime(float t);
  void setExplose(int ex);
  void setDureeVie(int dv);
  void initComptime();
  
  float getDirectionParamX();
  float getDirectionParamY();
  float getDirectionX();
  float getDirectionY();
  float getComptime();
  int getExplose();
  int getDureeVie();
 
  sf::Sprite anneau;
  sf::Vector2f direction;
  sf::Vector2f directionParam; 
  
 private :
 
 
 bool etat;
 float comptime;
 float comptimeD;
 int explose=0; 
 int dureeVie=10000;
};
#endif
