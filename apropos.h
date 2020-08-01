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
#ifndef DEF_APROPOS
#define DEF_APROPOS

#include <SFML/Graphics.hpp>

#include <iostream>
#include <stdlib.h>
#include <string>


class Apropos{

 public :
  
  Apropos();
  ~Apropos();
  
  void setFontColor(sf::Color dfc);
  void setFontSize(int dfs);
  void setApropos(std::string Config, std::string Theme, std::string gui, std::string lg);
  bool drawApropos(std::string Config, std::string Gui, std::string Th, std::string lg, std::string nav);
  void newText(sf::Event e);

  
  
  void onClose();
  void onEventResized(sf::Event);
  void mouseWheel(sf::Event);
  void onKeyPressed(sf::Event e);
  void onClick(sf::Event e, std::string nav);
  void onMouseUp(sf::Event e);
  void onMouseMove(sf::Event e);
  

 private :
  
  int winAproposWidth;
  int winAproposHeight;
  std::string fGui;
  std::string fTheme;
  std::string Theme;
  std::string dossierConfig;
  sf::Texture selectF1;
  sf::Sprite sApropos;
  
  sf::Texture svide;
  sf::Sprite bLicence;
  sf::Sprite bFermer;
  sf::Text tLicence;
  sf::Text tFermer;
  
  sf::Text infoTxt;
  int AproposTxtSize;
  sf::Color  AproposTxtFillColor;
  sf::Color  AproposBkgColor;
  sf::RenderWindow winApropos;
  sf::Font font;
  std::string titreWApropos;
  sf::Color dialogFontColor;
  int dialogFontSize;
  
  sf::Text AproposT[9];
  sf::Text licenceT[13];
  int rtf;
};
#endif
