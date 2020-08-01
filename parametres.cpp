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
#include <stdexcept>
#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <ctgmath>
#include <string>
#include <cstring>
#include <boost/filesystem.hpp>

#include "parametres.h"
#include "selectFile.h"

using namespace std;

Parametres::Parametres(){
  
}

Parametres::~Parametres(){
}

void Parametres::initParametres(string fconf){
  ifstream fichier(fconf, ios::in);       // ouverture du fichier parametres.conf
  string contenu;
  std::stringstream adr;
  string pf[2];
  int i=0;
  if(fichier){                                        // si l'ouverture a réussi
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
       if(pf[0]=="Thème"){
		  	  Theme=pf[1];
			  adr << std::fixed << Theme;
			  Theme=adr.str();
			  adr.clear();
			  adr.str("");
			  adr << std::fixed << dossierConfig <<"/Themes" << "/"<< Theme;
			  fTheme=adr.str();
			  adr.clear();
			  adr.str("");
       }
       if(pf[0]=="Lang"){
			  Lang=pf[1];
			  adr << std::fixed << dossierConfig <<"/Lang/divers."<<Lang;
			  diversLang=adr.str();
			  adr.clear();
			  adr.str("");
			  
       }
       if(pf[0]=="dossierConfig"){
		    dossierConfig=pf[1];
		    pf[1]="";
	     }
	     if(pf[0]=="Editeur"){
	     	 nEditeur.setString("");
		    Editeur=pf[1];
		    nEditeur.setString(Editeur);
		    pf[1]="";
	     }
	     if(pf[0]=="Navigateur"){
	     	 nNavigateur.setString("");
		    Navigateur=pf[1];
		    nNavigateur.setString(Navigateur);
		    pf[1]="";
	     }
	     if(pf[0]=="Daw"){
		    daw=pf[1];
		    pf[1]="";
	     }
	     if(pf[0]=="port"){
		    port=stoi(pf[1]);
		    portT.setString("");
		    portT.setString(pf[1]);
		    pf[1]="";
	     }
	     if(pf[0]=="serveur"){
		    serveur=pf[1];
		    serveurT.setString("");
		    serveurT.setString(pf[1]);
		    pf[1]="";
	     }
	     if(pf[0]=="OSC"){
		    oscPort=stoi(pf[1]);
		    oscPortT.setString("");
		    oscPortT.setString(pf[1]);
		    pf[1]="";
	     }
     }
      fichier.close();		
  }else{  // sinon
       cerr << "Erreur à l'ouverture Préférences!" << endl;
  }

}

string Parametres::drawParametres(string config, string gui, string Th,string user){
  initParametres(user+"/parametres.conf");
  fGui=gui;
  dossierConfig=config;
  fTheme=Th;
  dossierUser=user;
  stringstream adr;
  
  ifstream fichier(fTheme, ios::in);       // ouverture du fichier parametres.conf
  string contenu;
  string pf[2];
  int i=0;
  if(fichier){                                        // si l'ouverture a réussi
     while(getline(fichier, contenu)){
       char * cstr = new char [contenu.length()+1];
       std::strcpy (cstr, contenu.c_str());
       char * p = std::strtok (cstr,"=");
       i=0;
       while (p!=0){
 	     pf[i]=p;
 	     i++;
	     p = std::strtok(NULL," ");
       }
       if(pf[0]=="paramOngSelectColor"){
		  	 ongSelColor=sf::Color(std::stoul(pf[1],nullptr,16)); 
       }
       if(pf[0]=="paramOngColor"){
			 ongColor=sf::Color(std::stoul(pf[1],nullptr,16)); 
			  
       }
       if(pf[0]=="paramFontColoOng"){
		    fOngColor=sf::Color(std::stoul(pf[1],nullptr,16));
		    fColor=sf::Color(std::stoul(pf[1],nullptr,16));
		    pf[1]="";
	     }
	     if(pf[0]=="paramFontSizeOng"){
	     	 fSize=stoi(pf[1]);
	     	 fOngSize=stoi(pf[1]);
		    pf[1]="";
	     }
	     
     }	
      fichier.close();	
  }else{  // sinon
       cerr << "Erreur à l'ouverture Préférences!" << endl;
  }  
  sf::Text ongConf1;
  ongConf1.setFont(font);
  ongConf1.setString(L"Paramètres");
  ongConf1.setCharacterSize(fOngSize);
  ongConf1.setPosition(sf::Vector2f(6, 4));
  ongConf1.setFillColor(fColor);
  titreWinParam=ongConf1.getString();

  sf::RectangleShape planConf(sf::Vector2f(415, 360)); // bloc de titre
  planConf.setFillColor(ongSelColor);
  planConf.setPosition(sf::Vector2f(0,24));
  sf::RectangleShape shOngConf1(sf::Vector2f(80, 24)); // bloc de titre
  shOngConf1.setFillColor(ongSelColor);
  shOngConf1.setPosition(sf::Vector2f(0,0));

  circle.setRadius(3.f);
  circle1.setRadius(3.f);
  circle.setPosition(sf::Vector2f(117, 79));
  circle1.setPosition(sf::Vector2f(279, 79));
  circle2.setRadius(3.f);
  circle3.setRadius(3.f);
  circle2.setPosition(sf::Vector2f(118, 114));
  circle3.setPosition(sf::Vector2f(280, 114));
  circle4.setRadius(3.f);
  circle5.setRadius(3.f);
  circle4.setPosition(sf::Vector2f(122, 225));
  circle5.setPosition(sf::Vector2f(284, 225));

  adr << std::fixed << fGui<<"/"<<"Arial.ttf";
  font.loadFromFile(adr.str());
  adr.clear();
  adr.str("");
  sf::Texture ImgConf1;
  adr << std::fixed << fGui<<"/conf1.png";
  ImgConf1.loadFromFile(adr.str());
  sf::Sprite panConf1(ImgConf1);
  panConf1.setPosition(sf::Vector2f(0, 24));
  adr.clear();
  adr.str("");
  

  sf::Texture ImgConf5;
  adr << std::fixed << fGui<<"/bAnnuler.png";
  ImgConf5.loadFromFile(adr.str());
  sf::Sprite annuler(ImgConf5);
  annuler.setPosition(sf::Vector2f(272, 320));
  adr.clear();
  adr.str("");
  sf::Texture ImgConf6;
  adr << std::fixed << fGui<<"/bValider.png";
  ImgConf6.loadFromFile(adr.str());
  sf::Sprite valider(ImgConf6);
  valider.setPosition(sf::Vector2f(340, 320));
  adr.clear();
  adr.str("");
 
  
  winParam.create(sf::VideoMode(415,360), titreWinParam);
  sf::RectangleShape menuBar(sf::Vector2f( winParamWidth,ParamBarHeight));
  
  winCurseur.setSize(sf::Vector2f(2,12));
  winCurseur.setFillColor(sf::Color(0,0,0,255));
  flagCurseur=0;
  portT.setFont(font);
  portT.setCharacterSize(fSize);
  portT.setFillColor(fColor);
  portT.setPosition(174-portT.getLocalBounds().width-2,258);
  serveurT.setFont(font);
  serveurT.setCharacterSize(fSize);
  serveurT.setFillColor(fColor);
  serveurT.setPosition(380-serveurT.getLocalBounds().width-2,258);
  
  nText.setFont(font);
  nText.setCharacterSize(fSize);
  nText.setPosition(sf::Vector2f(134, 58));
  nText.setFillColor(fColor);
  nEditeur.setFont(font);
  nEditeur.setCharacterSize(fSize);
  nEditeur.setFillColor(fColor);
  nEditeur.setPosition(350-nEditeur.getLocalBounds().width-2,146);
  nNavigateur.setFont(font);
  nNavigateur.setCharacterSize(fSize);
  nNavigateur.setFillColor(fColor);
  nNavigateur.setPosition(350-nNavigateur.getLocalBounds().width-2,180);
  oscPortT.setFont(font);
  oscPortT.setCharacterSize(fSize);
  oscPortT.setFillColor(fColor);
  oscPortT.setPosition(174-oscPortT.getLocalBounds().width-2,292);
  labelNavigateur.setFont(font);
  labelNavigateur.setString("Navigateur");
  labelNavigateur.setCharacterSize(fSize);
  labelNavigateur.setFillColor(fColor);
  labelNavigateur.setPosition(46,184);
  labelOsc.setFont(font);
  labelOsc.setString("OSC Port");
  labelOsc.setCharacterSize(fSize);
  labelOsc.setFillColor(fColor);
  labelOsc.setPosition(48,292);
  labelXmit.setFont(font);
  labelXmit.setString("xmit");
  labelXmit.setCharacterSize(fSize);
  labelXmit.setFillColor(fColor);
  labelXmit.setPosition(218,292);
  xmitT.setFont(font);
  xmitT.setString("0");
  xmit=0;
  xmitT.setCharacterSize(fSize);
  xmitT.setFillColor(fColor);
  xmitT.setPosition(312-xmitT.getLocalBounds().width-2,292);
  
  while (winParam.isOpen()) {                             // Événements
        sf::Event event;
        while (winParam.pollEvent(event)){                // Gestion des évènements de la fenêtre principale
    	       	switch (event.type){
		        case sf::Event::Closed:            // Fermeture de la fenêtre
			        onClose();
			break;
			case sf::Event::TextEntered:
           			newText1(event);
			break;
            	        case sf::Event::MouseButtonPressed:
			  	onClick(event);
                	break;
            	        case sf::Event::MouseMoved:
			        onMouseMove(event);
                	break;
        				  					
		default:                            // on ne traite pas les autres types d'évènements
                	break;
  	       	}            
        
        }
        // Clear screen
	winParam.setActive(true);
	winParam.pushGLStates();
   winParam.clear(sf::Color(19,37,53));
   
  
	winParam.draw(shOngConf1);
	winParam.draw(ongConf1);
	winParam.draw(panConf1);

   winParam.draw(nEditeur);
   winParam.draw(portT); 	
   winParam.draw(serveurT);
   
   winParam.draw(nNavigateur);
   winParam.draw(oscPortT);
   winParam.draw(labelXmit);
   winParam.draw(xmitT);
   
   winParam.draw(annuler);
   winParam.draw(valider);
   
   if(Lang=="Fr"){
   	circle.setFillColor(sf::Color(88, 142, 181));
   	circle1.setFillColor(sf::Color(255, 255, 255));
   }else{
   	circle.setFillColor(sf::Color(255, 255, 255));
   	circle1.setFillColor(sf::Color(88, 142, 181));
   }
   winParam.draw(circle);
   winParam.draw(circle1);
   if(Theme=="base"){
   	circle2.setFillColor(sf::Color(88, 142, 181));
   	circle3.setFillColor(sf::Color(255, 255, 255));
   }else{
   	circle2.setFillColor(sf::Color(255, 255, 255));
   	circle3.setFillColor(sf::Color(88, 142, 181));
   }
   if(daw=="Ardour"){
   	circle4.setFillColor(sf::Color(88, 142, 181));
   	circle5.setFillColor(sf::Color(255, 255, 255));
   }else{
   	circle4.setFillColor(sf::Color(255, 255, 255));
   	circle5.setFillColor(sf::Color(88, 142, 181));
   }
   winParam.draw(circle4);
   winParam.draw(circle5);
   
   if(flagCurseur==1){
		if(clockCurseur.getElapsedTime()>sf::seconds(0.8f)){
			winParam.draw(winCurseur);
			if(clockCurseur.getElapsedTime()>sf::seconds(1.6f)){
				clockCurseur.restart();
			}
		}
	}
   
	winParam.display();
	winParam.popGLStates();
	winParam.setActive(false);
   }
   return txt;
}
void Parametres::onClose(){
  txt="";
  winParam.close();
}
void Parametres::valider(){
  txt="ok";
  if(xmit>2){
  	xmit=2;
  }
  if(xmit<0){
  	xmit=0;
  }
  saveParametres();
  winParam.close();
}

void Parametres::onMouseMove(sf::Event e){
   std::cout << "mouse x: " << e.mouseMove.x << std::endl;
   std::cout << "mouse y: " << e.mouseMove.y << std::endl;
  
}
void Parametres::onClick(sf::Event e){
   if (e.mouseButton.button == sf::Mouse::Left){
      //std::cout << "the left button was pressed" << std::endl;
      //std::cout << "mouse x: " << e.mouseButton.x << std::endl;
      //std::cout << "mouse y: " << e.mouseButton.y << std::endl;
   }
  if(e.mouseButton.x>114 && e.mouseButton.x<127 && e.mouseButton.y>74 && e.mouseButton.y<96){
    Lang="Fr"; 
  }
  /*
  if(e.mouseButton.x>276 && e.mouseButton.x<289 && e.mouseButton.y>74 && e.mouseButton.y<96){
    Lang="En";
  }
  */
  if(e.mouseButton.x>114 && e.mouseButton.x<127  && e.mouseButton.y>108 && e.mouseButton.y<130){
    Theme="base";
  }
  /*
  if(e.mouseButton.x>276 && e.mouseButton.x<289  && e.mouseButton.y>108 && e.mouseButton.y<130){
    Theme="Dark";
  }
  */
  if(e.mouseButton.x>114 && e.mouseButton.x<132  && e.mouseButton.y>224 && e.mouseButton.y<234){
    daw="Ardour";
  }
  if(e.mouseButton.x>280 && e.mouseButton.x<294  && e.mouseButton.y>224 && e.mouseButton.y<234){
    daw="Reaper";
  }
  if(e.mouseButton.x>115 && e.mouseButton.x<352 && e.mouseButton.y>145 && e.mouseButton.y<170){
    Editeur="";
    txt="";
    defText=1;
    flagTxt=1;
    flagCurseur=1;
    winCurseur.setPosition(348,150);
  }
  if(e.mouseButton.x>115 && e.mouseButton.x<352 && e.mouseButton.y>180 && e.mouseButton.y<203){
    nNavigateur.setString("");
    txt="";
    defText=4;
    flagTxt=1;
    flagCurseur=1;
    winCurseur.setPosition(348,185);
  }
  if(e.mouseButton.x>116 && e.mouseButton.x<160 && e.mouseButton.y>255 && e.mouseButton.y<280){
    portT.setString("");
    txt="";
    defText=2;
    flagTxt=1;
    flagCurseur=1;
    winCurseur.setPosition(174,261);
  }
  if(e.mouseButton.x>276 && e.mouseButton.x<352 && e.mouseButton.y>255 && e.mouseButton.y<280){
    serveurT.setString("");
    txt="";
    defText=3;
    flagTxt=1;
    flagCurseur=1;
    winCurseur.setPosition(382,261);
  }
  if(e.mouseButton.x>116 && e.mouseButton.x<160 && e.mouseButton.y>290 && e.mouseButton.y<312){
    oscPortT.setString("");
    txt="";
    defText=5;
    flagTxt=1;
    flagCurseur=1;
    winCurseur.setPosition(174,294);
  }
  if(e.mouseButton.x>276 && e.mouseButton.x<316 && e.mouseButton.y>290 && e.mouseButton.y<312){
    xmitT.setString("");
    txt="";
    defText=6;
    flagTxt=1;
    flagCurseur=1;
    winCurseur.setPosition(314,294);
  }
  if( e.mouseButton.y>322 && e.mouseButton.y<350){
	  if(e.mouseButton.x>271 && e.mouseButton.x<328){
	    onClose();
	  }
	  if(e.mouseButton.x>341 && e.mouseButton.x<391){
	    valider();
	  }
  }
}

void Parametres::newText1(sf::Event e){
     int key=e.key.code;
     if (e.text.unicode < 128){
		switch (key){
	     case 8:
	         if(flagTxt==1){
	       		switch (defText){
		       		case 1:
			     			Editeur=txt;
			     			nEditeur.setString(txt);
			     			nEditeur.setPosition(350-nEditeur.getLocalBounds().width-2,146);
			     			 
			     			break;
			     		case 2:
			     			port=stoi(txt);
			     			portT.setString(txt);
			     			portT.setPosition(174-portT.getLocalBounds().width-2,258);
			     			break;
			     		case 3:
			     			serveur=txt;
			     			serveurT.setString(txt);
			     			serveurT.setPosition(380-serveurT.getLocalBounds().width-2,258);
			     			break;
			     		case 4:
			     			Navigateur=txt;
			     			nNavigateur.setString(txt);
			     			nNavigateur.setPosition(350-nNavigateur.getLocalBounds().width-2,180);
			     			break;
			     		case 5:
			     			oscPort=stoi(txt);
			     			oscPortT.setString(txt);
			     			oscPortT.setPosition(174-oscPortT.getLocalBounds().width-2,292);
			     			break;
			     		case 6:
			     			xmit=stoi(txt);
			     			xmitT.setString(txt);
			     			xmitT.setPosition(312-xmitT.getLocalBounds().width-2,292);
			     			break;	
			     	}
	       	}
	 	  break;
	     case 13:
	     		if(flagTxt==1){
	     			switch (defText){
		       		case 1:
			     			Editeur=txt;
			     			nEditeur.setString(txt);
			     			nEditeur.setPosition(350-nEditeur.getLocalBounds().width-2,146);
			     			 
			     			break;
			     		case 2:
			     			port=stoi(txt);
			     			portT.setString(txt);
			     			portT.setPosition(174-portT.getLocalBounds().width-2,258);
			     			break;
			     		case 3:
			     			serveur=txt;
			     			serveurT.setString(txt);
			     			serveurT.setPosition(380-serveurT.getLocalBounds().width-2,258);
			     			break;
			     		case 4:
			     			Navigateur=txt;
			     			nNavigateur.setString(txt);
			     			nNavigateur.setPosition(350-nNavigateur.getLocalBounds().width-2,180);
			     			break;
			     		case 5:
			     			oscPort=stoi(txt);
			     			oscPortT.setString(txt);
			     			oscPortT.setPosition(174-oscPortT.getLocalBounds().width-2,292);
			     			break;
			     		case 6:
			     			xmit=stoi(txt);
			     			xmitT.setString(txt);
			     			xmitT.setPosition(312-xmitT.getLocalBounds().width-2,292);
			     			break;	
			     	}
	     		}
		  break;
	     default:
			txt=txt+static_cast<char>(e.text.unicode);
			if(flagTxt==1){
	     		 switch (defText){
		       		case 1:
			     			Editeur=txt;
			     			nEditeur.setString(txt);
			     			nEditeur.setPosition(350-nEditeur.getLocalBounds().width-2,146);
			     			winParam.draw(nEditeur);
			     			break;
			     		case 2:
			     			portT.setString(txt);
			     			port=stoi(txt);
			     			portT.setPosition(174-portT.getLocalBounds().width-2,258);
			     			break;
			     		case 3:
			     			serveur=txt;
			     			serveurT.setString(txt);
			     			serveurT.setPosition(380-serveurT.getLocalBounds().width-2,258);
			     			break;
			     		case 4:
			     			Navigateur=txt;
			     			nNavigateur.setString(txt);
			     			nNavigateur.setPosition(350-nNavigateur.getLocalBounds().width-2,180);
			     			break;
			     		case 5:
			     			oscPort=stoi(txt);
			     			oscPortT.setString(txt);
			     			oscPortT.setPosition(174-oscPortT.getLocalBounds().width-2,292);
			     			break;
			     		case 6:
			     			xmit=stoi(txt);
			     			xmitT.setString(txt);
			     			xmitT.setPosition(312-xmitT.getLocalBounds().width-2,292);
			     			break;
			 	 }
	  		}
		break;
    	}
    }
}
void Parametres::saveParametres(){
	bool alerteFlag=0;
	string nameFile=dossierUser+"/parametres.conf";
	ofstream fichier(nameFile, ios::out | ios::trunc);
	if(fichier){  // si l'ouverture a réussi
	  fichier<<"Thème="<<Theme<<endl;
	  fichier<<"Lang="<< Lang<<endl;
	  fichier<<"dossierConfig="<<dossierConfig<<endl;
	  string s=nEditeur.getString();
	  fichier<<"Editeur="<<s<<endl;
	  fichier<<"Navigateur="<<Navigateur<<endl;
	  fichier<<"Daw="<<daw<<endl;
	  fichier<<"port="<<port<<endl;
	  fichier<<"serveur="<<serveur<<endl;
	  fichier<<"OSC="<<oscPort<<endl;
	  fichier.close(); 
	}else{  // sinon
     cerr << "Erreur à l'ouverture !" << endl;
	}
}
string Parametres::getDaw(){
	return daw;
}
string Parametres::getNavigateur(){
	return Navigateur;
}
string Parametres::getEditeur(){
	return Editeur;
}
std::string Parametres::getServeur(){
	return serveur;
}
int Parametres::getOsc(){
	return oscPort;
}
int Parametres::getPort(){
	return port;
}
int Parametres::getXmit(){
	return xmit;
}
