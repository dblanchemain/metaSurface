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
#ifndef DEF_PARAMETRES
#define DEF_PARAMETRES

#include <SFML/Graphics.hpp>

#include <iostream>
#include <stdlib.h>
#include <string>
#include "selectFile.h"

class Parametres{

 public :
  
  Parametres();
  ~Parametres();
  
  void initParametres(std::string parametres);
  std::string drawParametres(std::string config, std::string gui, std::string Th, std::string user);
  void newText1(sf::Event e);
  void valider();
  void saveParametres();
  
  void onClose();
  void onEventResized(sf::Event);
  void mouseWheel(sf::Event);
  void onKeyPressed(sf::Event e);
  void onClick(sf::Event e);
  void onMouseUp(sf::Event e);
  void onMouseMove(sf::Event e);
  std::string getNavigateur();
  std::string getEditeur();
  std::string getServeur();
  int getOsc();
  int getPort();
  int getXmit();
  std::string getDaw();

 private :
  
  int winParamWidth=500;
  int winParamHeight=430;
  int ParamBarHeight=36;
  int type=0;
  std::string fGui;
  std::string fTheme;
  std::string Theme;
  std::string diversLang;
  std::string simpleLecteur;
  std::string dossierConfig;
  std::string dossierUser;

  sf::RenderWindow winParam;
  sf::Font font;
  std::string titreWinParam;
  sf::Color ongSelColor;
  sf::Color ongColor;
  sf::Color fOngColor;
  sf::Color fColor;
  int fSize;
  int fOngSize;
  sf::RectangleShape winCurseur;
  bool flagCurseur;
  sf::Clock clockCurseur;
  int ongletActif=0;
  sf::CircleShape circle;
  sf::CircleShape circle1;
  sf::CircleShape circle2;
  sf::CircleShape circle3;
  sf::CircleShape circle4;
  sf::CircleShape circle5;
  
  std::string Lang;
  std::string daw;
  std::string Editeur;
  sf::Text nEditeur;
  std::string Navigateur;
  sf::Text nNavigateur;
  std::string midiPlayer;
  sf::Text labelNavigateur;
  sf::Text labelOsc;
  
  int flagTxt=0;
  sf::Text portT;
  int port;
  sf::Text oscPortT;
  int oscPort;
  int xmit;
  sf::Text labelXmit;
  sf::Text xmitT;
  sf::Text serveurT;
  std::string serveur;
  int defText;
  
  std::string txt="";
  sf::Text nText;

};
#endif
