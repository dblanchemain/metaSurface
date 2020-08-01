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
#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <fstream>
#include <ctgmath>
#include <string>
#include <cstring>

#include "menu.h"
#include "configuration.h"

using namespace std;

Menu::Menu(){
}

Menu::~Menu(){
}
void Menu::initMenu(){
	stringstream adr;
   adr << std::fixed << appGui<<"/"<<"Arial.ttf";
   font.loadFromFile(adr.str());
   adr.clear();
   adr.str("");
   menu1.setSize(sf::Vector2f(112,144));
   menu1.setFillColor(menu1BkgColor);
   menu1b.setSize(sf::Vector2f(110,142));
   menu1b.setFillColor(menu1bBkgColor);
   menu1.setPosition(sf::Vector2f(0, 26));
   menu1b.setPosition(sf::Vector2f(0, 26));
  
   menu2.setSize(sf::Vector2f(112,144));
   menu2.setFillColor(menu1BkgColor);
   menu2.setPosition(sf::Vector2f(56, 26));
   menu2b.setSize(sf::Vector2f(110,142));
   menu2b.setFillColor(menu1bBkgColor);
   menu2b.setPosition(sf::Vector2f(56, 26));
   
   menu3.setSize(sf::Vector2f(112,90));
   menu3.setFillColor(menu1BkgColor);
   menu3.setPosition(sf::Vector2f(112, 26));
   menu3b.setSize(sf::Vector2f(110,88));
   menu3b.setFillColor(menu1bBkgColor);
   menu3b.setPosition(sf::Vector2f(112, 26));
   
   menu4.setSize(sf::Vector2f(112,87));
   menu4.setFillColor(menu1BkgColor);
   menu4.setPosition(sf::Vector2f(168, 26));
   menu4b.setSize(sf::Vector2f(110,86));
   menu4b.setFillColor(menu1bBkgColor);
   menu4b.setPosition(sf::Vector2f(168, 26));
  
   itemShap.setSize(sf::Vector2f(108,26));
   itemShap.setFillColor(itemShapBkgColor);
 
   ifstream fichier(fichierMenu, ios::in); 
   string contenu;
   sf::String sfstr;
  
  if(fichier){
    int k=36;
    getline(fichier,contenu);
    sfstr = sf::String::fromUtf8(contenu.begin(), contenu.end());
    menuItems[0][0].setFont(font);
    menuItems[0][0].setString(sfstr);
    menuItems[0][0].setCharacterSize(13);
    menuItems[0][0].setPosition(sf::Vector2f(6, 5));
    menuItems[0][0].setFillColor(itemFontColor);
    for(int i=1;i<6;i++){
       getline(fichier,contenu);

       sfstr = sf::String::fromUtf8(contenu.begin(), contenu.end());
       menuItems[0][i].setFont(font);
       menuItems[0][i].setString(sfstr);
       menuItems[0][i].setCharacterSize(13);
       menuItems[0][i].setPosition(sf::Vector2f(6, k));
       menuItems[0][i].setFillColor(itemFontColor);
       k=k+28;
    }
    k=36;
    getline(fichier,contenu);
    sfstr = sf::String::fromUtf8(contenu.begin(), contenu.end());
    menuItems[1][0].setFont(font);   
    menuItems[1][0].setString(sfstr);
    menuItems[1][0].setCharacterSize(13);
    menuItems[1][0].setPosition(sf::Vector2f(60, 5));
    menuItems[1][0].setFillColor(itemFontColor);
    for(int i=1;i<6;i++){
       getline(fichier,contenu);
       sfstr = sf::String::fromUtf8(contenu.begin(), contenu.end());
       menuItems[1][i].setFont(font);
       menuItems[1][i].setString(sfstr);
       menuItems[1][i].setCharacterSize(13);
       menuItems[1][i].setPosition(sf::Vector2f(60, k));
       menuItems[1][i].setFillColor(itemFontColor);
       k=k+28;
    }
    k=36;
    getline(fichier,contenu);
    sfstr = sf::String::fromUtf8(contenu.begin(), contenu.end());
    menuItems[2][0].setFont(font);   
    menuItems[2][0].setString(sfstr);
    menuItems[2][0].setCharacterSize(13);
    menuItems[2][0].setPosition(sf::Vector2f(120, 5));
    menuItems[2][0].setFillColor(itemFontColor);
    for(int i=1;i<4;i++){
       getline(fichier,contenu);
       sfstr = sf::String::fromUtf8(contenu.begin(), contenu.end());
       menuItems[2][i].setFont(font);
       menuItems[2][i].setString(sfstr);
       menuItems[2][i].setCharacterSize(13);
       menuItems[2][i].setPosition(sf::Vector2f(120, k));
       menuItems[2][i].setFillColor(itemFontColor);
       k=k+28;
    }
    k=36;
    getline(fichier,contenu);
    sfstr = sf::String::fromUtf8(contenu.begin(), contenu.end());
    menuItems[3][0].setFont(font);   
    menuItems[3][0].setString(sfstr);
    menuItems[3][0].setCharacterSize(13);
    menuItems[3][0].setPosition(sf::Vector2f(180, 5));
    menuItems[3][0].setFillColor(itemFontColor);
    for(int i=1;i<4;i++){
       getline(fichier,contenu);
       sfstr = sf::String::fromUtf8(contenu.begin(), contenu.end());
       menuItems[3][i].setFont(font);
       menuItems[3][i].setString(sfstr);
       menuItems[3][i].setCharacterSize(13);
       menuItems[3][i].setPosition(sf::Vector2f(180, k));
       menuItems[3][i].setFillColor(itemFontColor);
       k=k+28;
    }
    
   
    		
  }else{  // sinon
       cerr << "Erreur à l'ouverture du fichier Lang!" << endl;
  }
}
void Menu::appDrawMenu(sf::RenderWindow *surf){
  surf->draw(menuItems[0][0]);
  surf->draw(menuItems[1][0]);
  surf->draw(menuItems[2][0]);
  surf->draw(menuItems[3][0]);
  if(selectM1){
    surf->draw(menu1);
    surf->draw(menu1b);
    for(int i=1;i<6;i++){
      surf->draw(menuItems[0][i]);
    }
    for(int i=1;i<6;i++){
    menuItems[0][i].setFillColor(itemFontColor);
    }
    itemShap.setPosition(sf::Vector2f(0,32+(selectM1I*28)));
    surf->draw(itemShap);
    menuItems[0][selectM1I+1].setFillColor(itemShapFontColor);
    surf->draw(menuItems[0][selectM1I+1]);

  }
  if(selectM2){
    surf->draw(menu2);
    surf->draw(menu2b);
    for(int i=0;i<6;i++){
      surf->draw(menuItems[1][i]);
    }
    for(int i=1;i<6;i++){
    menuItems[1][i].setFillColor(itemFontColor);
    }
    itemShap.setFillColor(sf::Color(103,113,117));
    itemShap.setPosition(sf::Vector2f(56,32+(selectM2I*28)));
    surf->draw(itemShap);
    menuItems[1][selectM2I+1].setFillColor(itemShapFontColor);
    surf->draw(menuItems[1][selectM2I+1]);
    
  }
  if(selectM3){
    surf->draw(menu3);
    surf->draw(menu3b);
    for(int i=0;i<4;i++){
      surf->draw(menuItems[2][i]);
    }
    for(int i=1;i<4;i++){
    menuItems[2][i].setFillColor(itemFontColor);
    }
    itemShap.setFillColor(sf::Color(103,113,117));
    itemShap.setPosition(sf::Vector2f(112,32+(selectM3I*28)));
    surf->draw(itemShap);
    menuItems[2][selectM3I+1].setFillColor(itemShapFontColor);
    surf->draw(menuItems[2][selectM3I+1]);
    
  }
  if(selectM4){
    surf->draw(menu4);
    surf->draw(menu4b);
    for(int i=0;i<4;i++){
      surf->draw(menuItems[3][i]);
    }
    for(int i=1;i<4;i++){
    menuItems[3][i].setFillColor(itemFontColor);
    }
    itemShap.setFillColor(sf::Color(103,113,117));
    itemShap.setPosition(sf::Vector2f(168,32+(selectM4I*28)));
    surf->draw(itemShap);
    menuItems[3][selectM4I+1].setFillColor(itemShapFontColor);
    surf->draw(menuItems[3][selectM4I+1]);
    
  }
}
void Menu::setGui(std::string g){
	appGui=g;
}
void Menu::setFichierMenu(std::string s){
	fichierMenu=s;
}
void Menu::setSelectM1(bool m1){
	selectM1=m1;
}
void Menu::setSelectM2(bool m2){
	selectM2=m2;
}
void Menu::setSelectM3(bool m3){
	selectM3=m3;
}
void Menu::setSelectM4(bool m4){
	selectM4=m4;
}
void Menu::setSelectBarMenu(bool bm){
	selectBarMenu=bm;
}
void Menu::setSelectM1I(int id){
	selectM1I=id;
}
void Menu::setSelectM2I(int id){
	selectM2I=id;
}
void Menu::setSelectM3I(int id){
	selectM3I=id;
}
void Menu::setSelectM4I(int id){
	selectM4I=id;
}

void Menu::setAppBackGroundMenuBar(sf::Color cb){
	 AppBackGroundMenuBar=cb;
}
void Menu::setMenuBarHeight(int mNH){
	 menuBarHeight=mNH;
}
void Menu::setMenu1BkgColor(sf::Color mBc){
	 menu1BkgColor=mBc;
}
void Menu::setMenu1bBkgColor(sf::Color m1b){
	 menu1bBkgColor=m1b;
}
void Menu::setItemShapBkgColor(sf::Color iBc){
	 itemShapBkgColor=iBc;
}
void Menu::setItemFontColor(sf::Color ifc){
	 itemFontColor=ifc;
}
void Menu::setItemShapFontColor(sf::Color iSc){
	itemShapFontColor=iSc;
}


string Menu::getFichierMenu(){
	return fichierMenu;
}
bool Menu::getSelectM1(){
	return selectM1;
}
bool Menu::getSelectM2(){
	return selectM2;
}
bool Menu::getSelectM3(){
	return selectM3;
}
bool Menu::getSelectM4(){
	return selectM4;
}
bool Menu::getSelectBarMenu(){
	return selectBarMenu;
}