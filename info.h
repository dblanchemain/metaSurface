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
#ifndef DEF_INFO
#define DEF_INFO

#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdlib.h>
#include <string>


class Info{

 public :
  
  Info();
  ~Info();
  
  void setInfo(std::string Theme, std::string gui);
  void setTxt(int i, sf::String txt);
  bool drawInfo(int ftype, std::string titreWDialog);
  void setInfoTxtSize(int size);
  void setInfoTxtFillColor(sf::Color color);
  void setInfoBkgColor(sf::Color color);
  void setTxtPosX(int i, int k);
  void setTxtPosY(int i, int k);

  void onClose();
  void onEventResized(sf::Event);
  void mouseWheel(sf::Event);
  void onKeyPressed(sf::Event e);
  void onClick(sf::Event e);
  void onMouseUp(sf::Event e);
  void onMouseMove(sf::Event e);
  

 private :
  
  int winInfoWidth;
  int winInfoHeight;
  int infoBarHeight;
  int type;
  std::string infoGui;
  std::string fTheme;
  std::string Theme;
  sf::RenderWindow winInfo;
  sf::Font font;
  std::string titreWinInfo;

  sf::Text infoTxt[2];  
  int infoTxtSize;
  sf::Color infoTxtFillColor;
  sf::Color infoBkgColor;

  
  bool  rtf=0;
};
#endif
