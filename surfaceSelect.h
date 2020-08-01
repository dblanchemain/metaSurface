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
#ifndef DEF_SURFACESELECT
#define DEF_SURFACESELECT

#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdlib.h>
#include <string>

#include "newSurface.h"

class surfaceSelect{

 public :
  
  surfaceSelect();
  ~surfaceSelect();
  
  int drawSurface(std::string path,std::string gui, std::string theme,std::string user);
  void setPath(std::string path);
  void setGui(std::string gui);
  void setSwidth(float sw);
  void setSheight(float sh);
  float getSwidth();
  float getSheight();
  std::string getSUser();
  void onClose();
  
  void onClick(sf::Event e);
  void onMouseMove(sf::Event e);
  void createSurface();
  std::string selectReturnPath();
  std::string selectReturnFile();
  

 private :
  sf::RenderWindow winSurface;
  std::string surfaceConfig;
  std::string surfaceGui;
  std::string surfaceTheme;
  std::string userConfig;
  sf::Font font;
  int type;
  float swidth;
  float sheight;
  sf::RectangleShape selectShape;
  bool surfaceS=0;
  bool defNewSurface;
  std::string nameReturnFile;
  std::string pathReturnFile;
};
#endif
