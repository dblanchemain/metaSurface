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

#include "surfaceSelect.h"
#include "newSurface.h"

using namespace std;

surfaceSelect::surfaceSelect(){
  type=255;
}

surfaceSelect::~surfaceSelect(){
}
void surfaceSelect::setPath(string path){
	surfaceConfig=path;
}
void surfaceSelect::setGui(string gui){
	surfaceGui=gui;
}

int surfaceSelect::drawSurface(string path,string gui, string theme, string user){
  surfaceConfig=path;
  surfaceGui=gui;
  surfaceTheme=theme;
  userConfig=user;
  stringstream adr;
  sf::Texture selectS1;
  adr << std::fixed <<gui<<"/surfaceSelect.png";
  selectS1.loadFromFile(adr.str());
  sf::Sprite sf1(selectS1);
  sf1.setPosition(sf::Vector2f(0, 0));
  adr.clear();
  adr.str("");
  sf::Texture selectS2;
  adr << std::fixed <<gui<<"/bValider.png";
  selectS2.loadFromFile(adr.str());
  sf::Sprite bvalid(selectS2);
  bvalid.setPosition(sf::Vector2f(554, 632));
  adr.clear();
  adr.str("");
  sf::Texture selectS3;
  adr << std::fixed <<gui<<"/bAnnuler.png";
  selectS3.loadFromFile(adr.str());
  sf::Sprite bAnnul(selectS3);
  bAnnul.setPosition(sf::Vector2f(486, 632));
  adr.clear();
  adr.str("");
  adr << std::fixed << gui<<"/"<<"Arial.ttf";
  font.loadFromFile(adr.str());
  
  sf::Text test1;
  test1.setString("New");
  test1.setFont(font);
  test1.setFillColor(sf::Color(0,0,0));
  test1.setPosition(sf::Vector2f(524, 584));
  test1.setCharacterSize(13);
  
  
  selectShape.setFillColor(sf::Color(0, 0, 0, 0));
  selectShape.setOutlineColor(sf::Color(255, 0, 0));
  selectShape.setOutlineThickness(1.f);
  sf::Text st[12];
  st[0].setString("3x3 9");
  st[0].setPosition(sf::Vector2f(50, 150));
  st[1].setString("4x3 12");
  st[1].setPosition(sf::Vector2f(188, 150));
  st[2].setString("4x4 16");
  st[2].setPosition(sf::Vector2f(332, 150));
  st[3].setString("hexa 14");
  st[3].setPosition(sf::Vector2f(514, 150));
  st[4].setString("6x3 18");
  st[4].setPosition(sf::Vector2f(114, 320));
  st[5].setString("6x4 24");
  st[5].setPosition(sf::Vector2f(342, 320));
  st[6].setString("hexa 10");
  st[6].setPosition(sf::Vector2f(514, 320));
  st[7].setString("6x4 32");
  st[7].setPosition(sf::Vector2f(114, 496));
  st[8].setString("8x8 64");
  st[8].setPosition(sf::Vector2f(346, 496));
  st[9].setString("hexa 7");
  st[9].setPosition(sf::Vector2f(514, 496));
  st[10].setString("hyper 30");
  st[10].setPosition(sf::Vector2f(114, 672));
  st[11].setString("hyper 35");
  st[11].setPosition(sf::Vector2f(346, 672));
  for(int i=0;i<12;i++){
  	  st[i].setFont(font);
  	  st[i].setFillColor(sf::Color(255,255,255));
  	  st[i].setCharacterSize(13);
  }
  
  
  winSurface.create(sf::VideoMode(615, 700), "metaSurface");
  
  while (winSurface.isOpen()) {
        sf::Event event;
        while (winSurface.pollEvent(event)){
    	       switch (event.type){
		         case sf::Event::Closed:
			           onClose();
			 			  break;
            	case sf::Event::MouseButtonPressed:
			  			  onClick(event);
                	  break;
               case sf::Event::MouseMoved:
			  			  onMouseMove(event);
                	  break;
        				  					
		         default: 
                	  break;
  	       	}            
        
        }
		winSurface.setActive(true);
		winSurface.pushGLStates();
		winSurface.draw(sf1);
		
		for(int i=0;i<12;i++){
			winSurface.draw(st[i]);
		}
		if(surfaceS==1){
			winSurface.draw(selectShape);
		}

		winSurface.display();
		winSurface.popGLStates();
		winSurface.setActive(false);
   }
   return type;
}
void surfaceSelect::onClose(){
  type=255;
  winSurface.close();
}
void surfaceSelect::setSwidth(float sw){
  swidth=sw;
}
void surfaceSelect::setSheight(float sh){
  sheight=sh;
}
float surfaceSelect::getSwidth(){
  return swidth;
}
float surfaceSelect::getSheight(){
  return sheight;
}
string surfaceSelect::selectReturnPath(){
	return pathReturnFile;
}
string surfaceSelect::selectReturnFile(){
	return nameReturnFile;
} 
string surfaceSelect::getSUser(){
	return userConfig;
} 
void surfaceSelect::onMouseMove(sf::Event e){
   std::cout << "mouse x: " << e.mouseMove.x << std::endl;
   std::cout << "mouse y: " << e.mouseMove.y << std::endl;
  
}

void surfaceSelect::onClick(sf::Event e){
   if (e.mouseButton.button == sf::Mouse::Left){
/*
      std::cout << "the left button was pressed" << std::endl;
      std::cout << "mouse x: " << e.mouseButton.x << std::endl;
      std::cout << "mouse y: " << e.mouseButton.y << std::endl;
*/
   }
   if(e.mouseButton.x>9 && e.mouseButton.x<136 && e.mouseButton.y>9 && e.mouseButton.y<136){
     pathReturnFile=userConfig+"/surfaces";
	  nameReturnFile="meta9.msf";
   }
   if(e.mouseButton.x>148 && e.mouseButton.x<274 && e.mouseButton.y>24 && e.mouseButton.y<120){
     pathReturnFile=userConfig+"/surfaces";
	  nameReturnFile="meta12.msf";
   }
   if(e.mouseButton.x>286 && e.mouseButton.x<414 && e.mouseButton.y>9 && e.mouseButton.y<136){
     pathReturnFile=userConfig+"/surfaces";
	  nameReturnFile="meta16.msf";
   }
   if(e.mouseButton.x>476 && e.mouseButton.x<604 && e.mouseButton.y>9 && e.mouseButton.y<136){
     pathReturnFile=userConfig+"/surfaces";
	  nameReturnFile="meta14.msf";
   }
   if(e.mouseButton.x>9 && e.mouseButton.x<262 && e.mouseButton.y>178 && e.mouseButton.y<306){
     pathReturnFile=userConfig+"/surfaces";
	  nameReturnFile="meta18.msf";
   }
   if(e.mouseButton.x>276 && e.mouseButton.x<466 && e.mouseButton.y>178 && e.mouseButton.y<306){
     pathReturnFile=userConfig+"/surfaces";
	  nameReturnFile="meta24.msf";
   }
   if(e.mouseButton.x>482 && e.mouseButton.x<608 && e.mouseButton.y>182 && e.mouseButton.y<292){
     pathReturnFile=userConfig+"/surfaces";
	  nameReturnFile="meta10.msf";
   }
   if(e.mouseButton.x>9 && e.mouseButton.x<262 && e.mouseButton.y>352 && e.mouseButton.y<482){
     pathReturnFile=userConfig+"/surfaces";
	  nameReturnFile="meta32.msf";
   }
   if(e.mouseButton.x>306 && e.mouseButton.x<436 && e.mouseButton.y>352 && e.mouseButton.y<482){
     pathReturnFile=userConfig+"/surfaces";
	  nameReturnFile="meta64.msf";
   }
   if(e.mouseButton.x>480 && e.mouseButton.x<608 && e.mouseButton.y>352 && e.mouseButton.y<482){
     pathReturnFile=userConfig+"/surfaces";
	  nameReturnFile="meta7.msf";
   }
   if(e.mouseButton.x>73 && e.mouseButton.x<200 && e.mouseButton.y>536 && e.mouseButton.y<664){
     type=30;
     pathReturnFile=userConfig+"/surfaces";
	  nameReturnFile="meta30.msf";
   }
   if(e.mouseButton.x>306 && e.mouseButton.x<436 && e.mouseButton.y>536 && e.mouseButton.y<664){
     pathReturnFile=userConfig+"/surfaces";
	  nameReturnFile="meta35.msf";
   }
   if(e.mouseButton.x>485 && e.mouseButton.x<541 && e.mouseButton.y>603 && e.mouseButton.y<632){
     type=255;
     winSurface.close();
   }
   
   if(e.mouseButton.x>556 && e.mouseButton.x<604 && e.mouseButton.y>603 && e.mouseButton.y<632){
     type=0;
     winSurface.close();
   }
   if(e.mouseButton.x>520 && e.mouseButton.x<576 && e.mouseButton.y>550 && e.mouseButton.y<579){
     createSurface();
   }
   
}
void surfaceSelect::createSurface(){
	newSurface nwSurface(surfaceConfig,surfaceGui,surfaceTheme,userConfig);
	bool rt=nwSurface.drawSurface();
	if(rt==1){
		pathReturnFile=nwSurface.surfaceDefPath();
		nameReturnFile=nwSurface.surfaceDefFile();
		std::cout << " surfaceDefPath "  <<pathReturnFile<< " name "<<nameReturnFile<<std::endl;
	}else{
		std::cout << "surface non sauvegardée "<< std::endl;
		pathReturnFile=surfaceConfig+"/surfaces";
		nameReturnFile="meta9.msf";
		std::cout << " surfaceDefPath "  <<pathReturnFile<< " name "<<nameReturnFile<<std::endl;
	}
}

