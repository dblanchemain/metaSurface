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
#ifndef DEF_MENU
#define DEF_MENU

#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdlib.h>
#include <string>

#include "configuration.h"

class Menu{

 public :
  
  Menu();
 
  ~Menu();
  void initMenu();
  
  void setGui(std::string g);
  void setFichierMenu(std::string s);
  void setSelectM1(bool m1);
  void setSelectM2(bool m2);
  void setSelectM3(bool m3);
  void setSelectM4(bool m4);
  void setSelectBarMenu(bool bm);
  void setSelectM1I(int id);
  void setSelectM2I(int id);
  void setSelectM3I(int id);
  void setSelectM4I(int id);
  void setAppBackGroundMenuBar(sf::Color cb);
  void setMenuBarHeight(int mNH);
  void setMenu1BkgColor(sf::Color mBc);
  void setMenu1bBkgColor(sf::Color m1b);
  void setItemShapBkgColor(sf::Color iBc);
  void setItemFontColor(sf::Color ifc);
  void setItemShapFontColor(sf::Color iSc); 
  
  std::string getFichierMenu();
  bool getSelectM1();
  bool getSelectM2();
  bool getSelectM3();
  bool getSelectM4();
  bool getSelectBarMenu();
  void appDrawMenu(sf::RenderWindow *surf);
  
  
 private :
  std::string appGui;
  std::string fichierMenu;
  
  sf::RectangleShape menu;
  sf::RectangleShape itemShap;
  sf::RectangleShape menu1;
  sf::RectangleShape menu1b;
  sf::RectangleShape menu2;
  sf::RectangleShape menu2b;
  sf::RectangleShape menu3;
  sf::RectangleShape menu3b;
  sf::RectangleShape menu4;
  sf::RectangleShape menu4b;
  sf::RectangleShape menuBar;
  sf::Color AppBackGroundMenuBar;
  float menuBarHeight;
  sf::Font font;
  sf::Color menu1BkgColor;
  sf::Color menu1bBkgColor;
  sf::Color itemShapBkgColor;
  sf::Color itemFontColor;
  sf::Color itemShapFontColor; 
  sf::Text menuItems[5][10];
  bool selectBarMenu=0;
  bool selectM1=0;
  bool selectM2=0;
  bool selectM3=0;
  bool selectM4=0;
  bool selectM5=0;
  
  int selectM1I=0;   
  int selectM2I=0;
  int selectM3I=0;   
  int selectM4I=0;
  
};
#endif
