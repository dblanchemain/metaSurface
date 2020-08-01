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
#ifndef DEF_PLUGIN
#define DEF_PLUGIN

#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <map>


class Plugin{

 private :
  
  int winPluginWidth;
  int winPluginHeight;
  int pluginBarHeight;
  int editMode;
  std::string pluginGui;
  std::string fTheme;
  std::string Theme;
  std::string userConfig;
  std::string editeur;
  std::string navigateur;
  sf::RenderWindow winPlugin;
  sf::RenderWindow winEditPlugin;
  sf::Font font;
  std::string titreWinPlugin;
  
  int pluginTxtSize;
  sf::Color pluginTxtFillColor;
  sf::Color pluginBkgColor;
  
  sf::RectangleShape winPluginCurseur;
  bool flagPluginCurseur;
  sf::Clock clockPluginCurseur;
  std::string apptxt;
  int textDef;
  
  sf::Text nameFx;
  sf::Text fonctionFx;
  sf::Text numparam;
  sf::Text refid;
  sf::Text id;
  sf::Text param;
  sf::Text min;
  sf::Text max;
  sf::Text adresse;
  sf::Texture selectF1;
  sf::Sprite fondPlugin;
  
  sf::Texture bNoSelect;
  sf::Texture bselect;
  sf::Sprite daw;
  sf::Texture idet;
  sf::Sprite faustIde;
  sf::Sprite flog;
  
  int wWidth;
  int wheight;
  sf::Text plugName[15];
  int asize;
  int listEditIndex;
  sf::RectangleShape winSelectCurseur;
  int selectId;
  sf::RectangleShape shapeEditSlider;
  sf::RectangleShape shapeEditMSlider;
  bool flagEditMSlider;
  float FxMdY;
  int nbplug;
  
  bool externe;
  bool flaglog;
  sf::Text labelLog;
  
  struct parametre{
    int id;
    std::string nom;
    float min;
    float max;
    std::string adr;
    bool mod;
  };
  std::map<std::string, int> listPlugin;
  int idparam;
  int numid;
  
  bool rtf;
  
 public :
  
  Plugin();
  ~Plugin();
  
  struct plugin{
  		int type;				// 0 interne non modifiable  1 interne utilisateur 2 externe
  		std::string nomFx;
  		std::string fx;
  		std::string path;
  		int nbpar;
  		std::vector<parametre>  param;
  };
  std::vector<parametre>  tabnparam ;
  std::vector<plugin> tabPlugin;
  
  void systemPlugin();
  void onClose();
  void onEventResized(sf::Event);
  void mouseWheel(sf::Event);
  void onKeyPressed(sf::Event e);
  void onClick(sf::Event e);
  void onMouseUp(sf::Event e);
  void onMouseMove(sf::Event e);
  void newPluginText(sf::Event e);
  
  const std::vector<std::string> explode(const std::string& s, const char& c);
  
  void setPlugin(std::string Theme, std::string gui, std::string uConfig, std::string edit, std::string nav);
  bool drawPlugin(bool edit,int ext,std::string titreWPlugin);
  void gesIndex(int id);
  void validerNewPlugin();
  void deletePlugin(std::string nm);
  void nettoyerPlugin();
  void addParamPlugin();
  void delParamPlugin();
  void readListPlugin();
  void afficheListPlugin();
  void writeListPlugin();
  void writeUsrPlugin();
  void newCodePlugin();
  void newFaustIde();
  std::map<std::string, int>& getListPlugin();
  std::vector<Plugin::plugin>& getTabPlugin();
  
  bool editListPlugin(std::string titreWPlugin);
  void editOnClose();
  void editOnClick(sf::Event e);
  void editMouseMove(sf::Event e);
  void onMouseUpWinEdit(sf::Event e);
  void defListPlugin();
  void mouseEditWheel(sf::Event e);
  
  void modifPlugin(int pid);
  int getEditMode();
  void setEditMode(int m);
};
#endif
