/* MetaSurface  .
 *
 * this file is part of the MetaSurface application
 *
 * Copyright 2020-2021 dominique Blanchemain
 *
 *
 * MetaSurface is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 3 of the License, or (at your option) any later version.
 *
* This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
* without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

* You should have received a copy of the GNU General Public License along with this program;
* If not, see http://www.gnu.org/licenses.
*/
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
