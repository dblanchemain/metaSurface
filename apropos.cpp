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
#include <sstream>
#include <iostream>
#include <fstream>
#include <dirent.h>
#include <stdlib.h>
#include <ctgmath>
#include <string>
#include <cstring>
#include <boost/filesystem.hpp>

#include "apropos.h"

using namespace std;

Apropos::Apropos(){
  winAproposWidth=420;
  winAproposHeight=650;
}

Apropos::~Apropos(){
}

void Apropos::setApropos(string config, string Theme, string gui, string lg){
   stringstream adr;
	adr << std::fixed <<gui;
   fGui=adr.str();
   fTheme=Theme;
   dossierConfig=config;
   std::cout << "lang apropos" <<lg<< std::endl;
   adr.clear();
   adr.str("");
   adr << std::fixed << fGui<<"/"<<"Arial.ttf";
   font.loadFromFile(adr.str());
   adr.clear();
   adr.str("");
   adr << std::fixed << fGui<<"/apropos2.png";
   selectF1.loadFromFile(adr.str());
   sApropos.setTexture(selectF1);
   sApropos.setPosition(sf::Vector2f(0, 0));
   adr.clear();
   adr.str("");
   adr << std::fixed << fGui<<"/bvide.png";
   svide.loadFromFile(adr.str());
   adr.clear();
   adr.str("");
   bFermer.setTexture(svide);
   bFermer.setPosition(sf::Vector2f(312, 610));

   
   
   string contenu;
   sf::Text st;
   string pf[2];
   int i=0;
   wstring ws;
   adr << std::fixed <<lg;
   string file=adr.str();
   adr.clear();
   adr.str("");
   ifstream fichier(file, ios::in); 
   
   if(fichier){ 
     while(getline(fichier, contenu)){
       char * cstr = new char [contenu.length()+1];
       std::strcpy (cstr, contenu.c_str());
       char * p = std::strtok (cstr,"=");
       i=0;
       while (p!=0){
 	     pf[i]=p;
 	     i++;
	     p = std::strtok(NULL,"=");
       }
       if(pf[0]=="apropos1"){
       	wstring ws=sf::String::fromUtf8(pf[1].begin(), pf[1].end());
         AproposT[0].setString(ws);
       }
       if(pf[0]=="apropos2"){
       	wstring ws=sf::String::fromUtf8(pf[1].begin(), pf[1].end());
         AproposT[1].setString(ws);
       }
       if(pf[0]=="apropos3"){
       	wstring ws=sf::String::fromUtf8(pf[1].begin(), pf[1].end());
         AproposT[2].setString(ws);
       }
       if(pf[0]=="apropos4"){
       	wstring ws=sf::String::fromUtf8(pf[1].begin(), pf[1].end());
         AproposT[3].setString(ws);
       }
       if(pf[0]=="apropos5"){
       	wstring ws=sf::String::fromUtf8(pf[1].begin(), pf[1].end());
         AproposT[4].setString(ws);
       }
       if(pf[0]=="apropos6"){
       	wstring ws=sf::String::fromUtf8(pf[1].begin(), pf[1].end());
         AproposT[5].setString(ws);
       }
       if(pf[0]=="apropos7"){
       	wstring ws=sf::String::fromUtf8(pf[1].begin(), pf[1].end());
         AproposT[6].setString(ws);
       }
       if(pf[0]=="apropos8"){
       	wstring ws=sf::String::fromUtf8(pf[1].begin(), pf[1].end());
         AproposT[7].setString(ws);
       }
       if(pf[0]=="apropos9"){
       	wstring ws=sf::String::fromUtf8(pf[1].begin(), pf[1].end());
         AproposT[8].setString(ws);
       }
       if(pf[0]=="fermer"){
       	wstring ws=sf::String::fromUtf8(pf[1].begin(), pf[1].end());
         tFermer.setString(ws);
       }
       if(pf[0]=="licence1"){
         licenceT[0].setString(pf[1]);
       }
       if(pf[0]=="licence2"){
         licenceT[1].setString(pf[1]);
       }
       if(pf[0]=="licence3"){
         licenceT[2].setString(pf[1]);
       }
       if(pf[0]=="licence4"){
         licenceT[3].setString(pf[1]);
       }
       if(pf[0]=="licence5"){
         licenceT[4].setString(pf[1]);
       }
       if(pf[0]=="licence6"){
         licenceT[5].setString(pf[1]);
       }
       if(pf[0]=="licence7"){
         licenceT[6].setString(pf[1]);
       }
       if(pf[0]=="licence8"){
         licenceT[7].setString(pf[1]);
       }
       if(pf[0]=="licence9"){
         licenceT[8].setString(pf[1]);
       }
       if(pf[0]=="licencea"){
         licenceT[9].setString(pf[1]);
       }
       if(pf[0]=="licenceb"){
         licenceT[10].setString(pf[1]);
       }
       if(pf[0]=="licencec"){
         licenceT[11].setString(pf[1]);
       }
     }
     fichier.close();		
  }else{  // sinon
       cerr << "Erreur à l'ouverture Theme!" << endl;
  }
   
   ifstream fichier2(Theme, ios::in); 
   contenu="";

   if(fichier2){ 
     while(getline(fichier2, contenu)){
       char * cstr = new char [contenu.length()+1];
       std::strcpy (cstr, contenu.c_str());
       char * p = std::strtok (cstr,"=");
       i=0;
       while (p!=0){
 	     pf[i]=p;
 	     i++;
	     p = std::strtok(NULL," ");
       }
       if(pf[0]=="infoTxtSize"){
         AproposTxtSize=stoi(pf[1]);
       }
       if(pf[0]=="infoTxtFillColor"){
         AproposTxtFillColor=sf::Color(std::stoul(pf[1],nullptr,16));
       }
       if(pf[0]=="infoBkgColor"){
         AproposBkgColor=sf::Color(std::stoul(pf[1],nullptr,16));
       }
     }
     fichier2.close();		
  }else{  // sinon
       cerr << "Erreur à l'ouverture Theme!" << endl;
  }
  
  for(int i=0;i<9;i++){
   	AproposT[i].setFont(font);   
   	AproposT[i].setCharacterSize(AproposTxtSize);
   	AproposT[i].setFillColor(AproposTxtFillColor);
   }
   
   AproposT[3].setFillColor(sf::Color(19,152,207));
   AproposT[7].setFillColor(sf::Color(19,152,207));
   
   float lb=AproposT[0].getLocalBounds().height;
   float wx=(420-AproposT[0].getLocalBounds().width)/2;
   AproposT[0].setPosition(wx,318);
   wx=(420-AproposT[1].getLocalBounds().width)/2;
   AproposT[1].setPosition(wx,330);
   wx=(420-AproposT[2].getLocalBounds().width)/2;
   AproposT[2].setPosition(24,342);
   AproposT[3].setPosition(286,342);
   AproposT[4].setPosition(325,342);
   wx=(420-AproposT[5].getLocalBounds().width)/2;
   AproposT[5].setPosition(wx,354);
   wx=(420-AproposT[6].getLocalBounds().width)/2;
   AproposT[6].setPosition(wx,366);
   wx=(420-AproposT[7].getLocalBounds().width)/2;
   AproposT[7].setPosition(wx,390);
   wx=(420-AproposT[8].getLocalBounds().width)/2;
   AproposT[8].setPosition(wx,416);
   
   tFermer.setFont(font);   
   tFermer.setCharacterSize(AproposTxtSize);
   tFermer.setFillColor(AproposTxtFillColor);
   tFermer.setPosition(sf::Vector2f(319, 616));
   
   for(int i=0;i<12;i++){
   	licenceT[i].setFont(font);   
   	licenceT[i].setCharacterSize(AproposTxtSize);
   	licenceT[i].setFillColor(AproposTxtFillColor);
   }
   licenceT[11].setFillColor(sf::Color(19,152,207));
   wx=(420-licenceT[0].getLocalBounds().width)/2;
   licenceT[0].setPosition(wx,452);
   wx=(420-licenceT[1].getLocalBounds().width)/2;
   licenceT[1].setPosition(wx,464);
   wx=(420-licenceT[2].getLocalBounds().width)/2;
   licenceT[2].setPosition(wx,476);
   wx=(420-licenceT[3].getLocalBounds().width)/2;
   licenceT[3].setPosition(wx,488);
   wx=(420-licenceT[4].getLocalBounds().width)/2;
   licenceT[4].setPosition(wx,500);
   wx=(420-licenceT[5].getLocalBounds().width)/2;
   licenceT[5].setPosition(wx,512);
   wx=(420-licenceT[6].getLocalBounds().width)/2;
   licenceT[6].setPosition(wx,524);
   wx=(420-licenceT[7].getLocalBounds().width)/2;
   licenceT[7].setPosition(wx,536);
   wx=(420-licenceT[8].getLocalBounds().width)/2;
   licenceT[8].setPosition(wx,548);
   wx=(420-licenceT[9].getLocalBounds().width)/2;
   licenceT[9].setPosition(wx,560);
   wx=(420-licenceT[10].getLocalBounds().width)/2;
   licenceT[10].setPosition(wx,572);
   wx=(420-licenceT[11].getLocalBounds().width)/2;
   licenceT[11].setPosition(wx,584);
}

bool Apropos::drawApropos(string Config, string Gui, string Th, string lg, string nav){
  
  titreWApropos="A propos";
  rtf=0;
  
  stringstream adr;
  
  sf::Sprite sApropos(selectF1);
  sApropos.setPosition(sf::Vector2f(0, 0));
  
  winApropos.create(sf::VideoMode(winAproposWidth, winAproposHeight), titreWApropos);
  
  
  
  while (winApropos.isOpen()) {                             // Événements
	sf::Event event;
	while (winApropos.pollEvent(event)){                // Gestion des évènements de la fenêtre principale
		switch (event.type){
			case sf::Event::Closed:            // Fermeture de la fenêtre
				onClose();
				break;
			case sf::Event::MouseButtonPressed:
				onClick(event, nav);
				break;
			case sf::Event::MouseMoved:
				onMouseMove(event);
				break;
        				  					
			default:                            // on ne traite pas les autres types d'évènements
				break;
		}            
        
	}
        // Clear screen
	winApropos.setActive(true);
	winApropos.pushGLStates();
	winApropos.clear(AproposBkgColor);
	winApropos.draw(sApropos);
	
	for(int i=0;i<9;i++){
		winApropos.draw(AproposT[i]);
   }
   for(int i=0;i<12;i++){
		winApropos.draw(licenceT[i]);
   }
   winApropos.draw(bFermer);
   winApropos.draw(tFermer);
       
	winApropos.display();
	winApropos.popGLStates();
	winApropos.setActive(false);
  }
  return rtf;
}
void Apropos::onClose(){
  rtf=0;
  winApropos.close();
}

void Apropos::onMouseMove(sf::Event e){
   std::cout << "mouse x: " << e.mouseMove.x << std::endl;
   std::cout << "mouse y: " << e.mouseMove.y << std::endl;
  
}
void Apropos::onClick(sf::Event e, string nav){
   if (e.mouseButton.button == sf::Mouse::Left){
      std::cout << "the left button was pressed" << std::endl;
      std::cout << "mouse x: " << e.mouseButton.x << std::endl;
      std::cout << "mouse y: " << e.mouseButton.y << std::endl;
   }
   if(e.mouseButton.x>312 && e.mouseButton.x<370 && e.mouseButton.y>612 && e.mouseButton.y<640){
     rtf=0;
     winApropos.close();
   }
   if(e.mouseButton.x>182 && e.mouseButton.x<236 && e.mouseButton.y>394 && e.mouseButton.y<406){
	  string cmd=nav+" http://blanchemain.info/Documents/Programmation/index.php?page=metaSurface &";
  	  char* dest = new char[cmd.length() + 1];
     std::copy(cmd.begin(), cmd.end(), dest);
     system(dest);
   }
   if(e.mouseButton.x>124 && e.mouseButton.x<290 && e.mouseButton.y>588 && e.mouseButton.y<602){
     string cmd=nav+" http://www.gnu.org/licenses/ &";
  	  char* dest = new char[cmd.length() + 1];
     std::copy(cmd.begin(), cmd.end(), dest);
     system(dest);
   }
   if(e.mouseButton.x>286 && e.mouseButton.x<321 && e.mouseButton.y>346 && e.mouseButton.y<356){
     string cmd=nav+" https://faust.grame.fr/ &";
  	  char* dest = new char[cmd.length() + 1];
     std::copy(cmd.begin(), cmd.end(), dest);
     system(dest);
   }
}

