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
#include <libgen.h>
#include <sstream>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <iomanip>
#include <ctgmath>
#include <string>
#include <cstring>
#include <boost/filesystem.hpp>
#include <vector>


#include "newSurface.h"
#include "selectFile.h"
#include "info.h"
#include "colorSelector.h"

using namespace std;

newSurface::newSurface(string config, string gui, string theme, string user){
/*
Theme="/home/dominique/Compile/CodeBlocks/createSurface/Themes/base";
dossierConfig="/home/dominique/Compile/CodeBlocks/createSurface";
appGui="/home/dominique/Compile/CodeBlocks/createSurface/gui/base";
*/
Theme=theme;
dossierConfig=config;
appGui=gui;
userConfig=user;
ifstream fichier(Theme, ios::in); 
  string contenu;
  float s1;
  int s2;
  string pf[2];
  int i=0;
  if(fichier){ 
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
       if(pf[0]=="windowAppWidth"){
	 		windowAppWidth=stof(pf[1]);
       }
        if(pf[0]=="windowAppHeight"){
	 		windowAppHeight=stof(pf[1]);
       }
       if(pf[0]=="AppBackGround"){
	 		AppBackGround=sf::Color(std::stoul(pf[1],nullptr,16));
       }
       if(pf[0]=="AppBackGroundMenuBar"){
         menuBar.setFillColor(sf::Color(std::stoul(pf[1],nullptr,16)));
       }
       if(pf[0]=="slideBkgColor"){
         surfaceSliderDroit.setFillColor(sf::Color(std::stoul(pf[1],nullptr,16)));
       }
       if(pf[0]=="slideMColor"){
         surfaceSliderMDroit.setFillColor(sf::Color(std::stoul(pf[1],nullptr,16)));
       }
       if(pf[0]=="slideHeight"){
         slideHeight=stof(pf[1]);
       }
       if(pf[0]=="slideOutline"){
         //slideOutline=stoi(pf[1]);
         surfaceSliderDroit.setOutlineThickness(stoi(pf[1]));
       }
       if(pf[0]=="slideOutlineColor"){
         surfaceSliderDroit.setOutlineColor(sf::Color(std::stoul(pf[1],nullptr,16)));
       }
       if(pf[0]=="menuBarHeight"){
         menuBarHeight=stof(pf[1]);
       }
       if(pf[0]=="bkgSurfaceWidth"){
         s2=stoi(pf[1]);
       }
       if(pf[0]=="bkgSurfaceHeight"){
         bkgSurface.create(s2, stoi(pf[1]));
         s2=0;
       }
       if(pf[0]=="workspaceSurfaceWidth"){
         s1=stof(pf[1]);
       }
       if(pf[0]=="workspaceSurfaceHeight"){
         workspaceSurface.setSize(sf::Vector2f(s1, stof(pf[1])));
       }
       if(pf[0]=="workspaceSurfaceTop"){
         s2=stof(pf[1]);
       }
       if(pf[0]=="workspaceSurfaceLeft"){
          workspaceSurface.setPosition(stof(pf[1]),s2);
       }
       if(pf[0]=="workspaceSurfaceOutline"){
          workspaceSurface.setOutlineThickness(stoi(pf[1]));
       }
       if(pf[0]=="workspaceSurfaceOutColor"){
         workspaceSurface.setOutlineColor(sf::Color(std::stoul(pf[1],nullptr,16)));
       }
       if(pf[0]=="navWorkspaceSizeX"){
         s1=stof(pf[1]);
       }
       if(pf[0]=="navWorkspaceSizeY"){
          navWorkspaceSurface.setSize(sf::Vector2f(s1,stof(pf[1])));
       }
       if(pf[0]=="navWorkspaceOutline"){
          navWorkspaceSurface.setOutlineThickness(stoi(pf[1]));
       }
       if(pf[0]=="navWorkspaceOutColor"){
          navWorkspaceSurface.setOutlineColor(sf::Color(std::stoul(pf[1],nullptr,16)));
       }
       if(pf[0]=="navWorkspacePosX"){
         s1=stof(pf[1]);
       }
       if(pf[0]=="navWorkspacePosY"){
        navWorkspaceSurface.setPosition(s1,stof(pf[1]));
       }
       if(pf[0]=="navSurfaceSizeX"){
        s1=stof(pf[1]);
       }
       if(pf[0]=="navSurfaceSizeY"){
        navSurface.setSize(sf::Vector2f(s1, stof(pf[1])));
       }
       if(pf[0]=="navSurfaceOutline"){
        navSurface.setOutlineThickness(stoi(pf[1]));
       }
       if(pf[0]=="navWorkspaceOutColor"){
          navSurface.setOutlineColor(sf::Color(std::stoul(pf[1],nullptr,16)));
       }
       if(pf[0]=="navSurfacePosX"){
        s1=stof(pf[1]);
       }
       if(pf[0]=="navSurfacePosY"){
        navSurface.setPosition(s1, stof(pf[1]));
       }
       
  		 if(pf[0]=="selectorWidth"){
        fileSelector.setSelectorWidth(stof(pf[1]));
       }
       if(pf[0]=="selectorHeight"){
        fileSelector.setSelectorHeight(stof(pf[1]));
       }
       if(pf[0]=="selectorBkgColor"){
       	sf::Color bkg=sf::Color(std::stoul(pf[1],nullptr,16));
         fileSelector.setSelectorBkgColor(bkg);
       }
       if(pf[0]=="selectorBarColor"){
       	sf::Color bc=sf::Color(std::stoul(pf[1],nullptr,16));
         fileSelector.setSelectorBarColor(bc);
       }
       if(pf[0]=="selectorPathColor"){
       	sf::Color bkg=sf::Color(std::stoul(pf[1],nullptr,16));
         fileSelector.setSelectorPathColor(bkg);
       }
       if(pf[0]=="selectorFileColor"){
       	sf::Color bc=sf::Color(std::stoul(pf[1],nullptr,16));
         fileSelector.setSelectorFileColor(bc);
       }
       if(pf[0]=="selectorLineBlocColor"){
       	sf::Color bc=sf::Color(std::stoul(pf[1],nullptr,16));
         fileSelector.setSelectorLineColor(bc);
       }
       if(pf[0]=="selectorSlider1Color"){
       	sf::Color bc=sf::Color(std::stoul(pf[1],nullptr,16));
         fileSelector.setSelectorSlider1Color(bc);
       }
       if(pf[0]=="selectorSlider2Color"){
       	sf::Color bc=sf::Color(std::stoul(pf[1],nullptr,16));
         fileSelector.setSelectorSlider2Color(bc);
       }
       if(pf[0]=="selectorSlider1ThColor"){
       	sf::Color bc=sf::Color(std::stoul(pf[1],nullptr,16));
         fileSelector.setSelectorSlider1thColor(bc);
       }
       if(pf[0]=="selectorSlider2ThColor"){
       	sf::Color bc=sf::Color(std::stoul(pf[1],nullptr,16));
         fileSelector.setSelectorSlider2thColor(bc);
       }
       if(pf[0]=="selectorFontColor"){
       	sf::Color fc=sf::Color(std::stoul(pf[1],nullptr,16));
         fileSelector.setSelectorFontColor(fc);
       }
       if(pf[0]=="selectorFontSize"){
         fileSelector.setSelectorFontSize(stoi(pf[1]));
       }
       if(pf[0]=="selectFontSize"){
         fileSelector.setSelectFontSize(stoi(pf[1]));
       }
       if(pf[0]=="dirFontColor"){
       	sf::Color dc=sf::Color(std::stoul(pf[1],nullptr,16));
         fileSelector.setDirFontColor(dc);
       }
       if(pf[0]=="fileFontColor"){
       	sf::Color fc=sf::Color(std::stoul(pf[1],nullptr,16));
         fileSelector.setFileFontColor(fc);
       }
       
     }		
  }else{  // sinon
       cerr << "Erreur à l'ouverture Theme!" << endl;
  }
  surfaceSave=0;
  stringstream adr;
  adr << std::fixed << appGui<<"/"<<"Arial.ttf";
  font.loadFromFile(adr.str());
  adr.clear();
  adr.str("");
  
  fileSelector.setSelectorGui(appGui);
  fileSelector.setTitreSelector("File selector");
  fileSelector.initSelector(getcwd(NULL,0));
  fileSelector.setSelectorLang(dossierConfig+"/Lang/divers.Fr");
  surfaceEtat=0;
  adr << std::fixed << appGui<<"/createSurfaceMenu.png";
  selectAnB.loadFromFile(adr.str());
  palette.setTexture(selectAnB);
  palette.setPosition(0,28);
  adr.clear();
  adr.str("");
  adr << std::fixed << appGui<<"/createSurfacePalette.png";
  selectAnB2.loadFromFile(adr.str());
  barPalette.setTexture(selectAnB2);
  barPalette.setPosition(20,0);
  adr.clear();
  adr.str("");
  
  surfaceSliderDroit.setSize(sf::Vector2f(slideHeight,windowAppHeight-menuBarHeight-slideHeight));
  surfaceSliderDroit.setPosition(windowAppWidth-slideHeight,menuBarHeight);
  surfaceSliderMDroit.setSize(sf::Vector2f(slideHeight-2, 233.f));
  surfaceSliderMDroit.setPosition(surfaceSliderDroit.getPosition().x+1,263);
  surfaceSliderBas.setFillColor(surfaceSliderDroit.getFillColor());
  surfaceSliderBas.setSize(sf::Vector2f(workspaceSurface.getSize().x, slideHeight));
  surfaceSliderBas.setPosition(workspaceSurface.getPosition().x,windowAppHeight-slideHeight);
  surfaceSliderMBas.setFillColor(surfaceSliderMDroit.getFillColor());
  surfaceSliderMBas.setSize(sf::Vector2f(233.f, slideHeight-2));
  surfaceSliderMBas.setPosition(433,surfaceSliderBas.getPosition().y+1);
  surfaceSliderMBas.setOutlineThickness(surfaceSliderDroit.getOutlineThickness());
  surfaceSliderMBas.setOutlineColor(sf::Color(surfaceSliderDroit.getOutlineColor()));
  
  bkgSurface.clear(AppBackGround);
  bkgSurface.setRepeated(false);
  std::cout << "surface position: " << workspaceSurface.getPosition().y<<std::endl;
  
  navBkgSurface.create(navWorkspaceSurface.getSize().x,navWorkspaceSurface.getSize().y);
  navBkgSurface.clear();
  navBkgSurface.setRepeated(false);
  navSurface.setFillColor(sf::Color(0,0,0,0));
  
  menuBar.setSize(sf::Vector2f( windowAppWidth,menuBarHeight));
  
  sf::ContextSettings settings;
  settings.antialiasingLevel = 8;
  surface.create(sf::VideoMode(920,754), "Surface",sf::Style::Default, settings);
  
  depNavSurface=0;
  slideMB=0;
  slideMD=0; 
  nscale=1;
  barycentreID=255;
  barySelectFlag=0;
  paveSelect=255;
  pointSelectFlag=0;
  pointSelect=255;
  nbc=3;
  thickness=1;
  nbPave=0;
  paveSelectFlag;
  
  barycentreTcx.setFont(font);
  barycentreTcx.setCharacterSize(13);
  barycentreTcx.setFillColor(sf::Color(0,0,0));
  barycentreTcy.setFont(font);
  barycentreTcy.setCharacterSize(13);
  barycentreTcy.setFillColor(sf::Color(0,0,0));
  thicknessT.setFont(font);
  thicknessT.setCharacterSize(13);
  thicknessT.setFillColor(sf::Color(0,0,0));
  thicknessT.setString(to_string(thickness));
  thicknessT.setPosition(146-thicknessT.getLocalBounds().width-4,414);
  nbcT.setFont(font);
  nbcT.setCharacterSize(13);
  nbcT.setFillColor(sf::Color(0,0,0));
  nbcT.setString(to_string(nbc));
  nbcT.setPosition(146-nbcT.getLocalBounds().width-4,445);
    
  surfaceTw.setFont(font);
  surfaceTw.setCharacterSize(13);
  surfaceTw.setFillColor(sf::Color(0,0,0));
  surfaceTh.setFont(font);
  surfaceTh.setCharacterSize(13);
  surfaceTh.setFillColor(sf::Color(0,0,0));
  surfaceTname.setFont(font);
  surfaceTname.setCharacterSize(13);
  surfaceTname.setFillColor(sf::Color(0,0,0));
  surfaceTbkg.setFont(font);
  surfaceTbkg.setCharacterSize(13);
  surfaceTbkg.setFillColor(sf::Color(0,0,0));
  
  surfaceTnbpave.setFont(font);
  surfaceTnbpave.setCharacterSize(13);
  surfaceTnbpave.setFillColor(sf::Color(0,0,0));
  
  test3.setFont(font);
  test3.setCharacterSize(13);
  test3.setFillColor(sf::Color(255,255,255));
  test3.setPosition(38,352);
  test3.setString(L"Vertex");
  test4.setFont(font);
  test4.setCharacterSize(13);
  test4.setFillColor(sf::Color(255,255,255));
  test4.setPosition(38,382);
  test4.setString("Centre");
  test5.setFont(font);
  test5.setCharacterSize(13);
  test5.setFillColor(sf::Color(255,255,255));
  test5.setPosition(40,250);
  test5.setString("Ri");
  test6.setFont(font);
  test6.setCharacterSize(13);
  test6.setFillColor(sf::Color(255,255,255));
  test6.setPosition(40,280);
  test6.setString("Re");
  test7.setFont(font);
  test7.setCharacterSize(13);
  test7.setFillColor(sf::Color(255,255,255));
  test7.setPosition(40,310);
  test7.setString("Ro");
  
  lineCurseurX.setSize(sf::Vector2f(2,700));
  lineCurseurX.setFillColor(sf::Color(255,0,0));
  lineCurseurY.setSize(sf::Vector2f(700,2));
  lineCurseurY.setFillColor(sf::Color(255,0,0));
  
  shapeLineColor.setFillColor(sf::Color(0,0,0));
  shapeLineColor.setSize(sf::Vector2f(58,16));
  shapeLineColor.setPosition(105,321);
  shapeBarycentreColor.setFillColor(sf::Color(0,0,0));
  shapeBarycentreColor.setSize(sf::Vector2f(58,16));
  shapeBarycentreColor.setPosition(105,381);
  shapePointColor.setFillColor(sf::Color(0,0,0));
  shapePointColor.setSize(sf::Vector2f(58,16));
  shapePointColor.setPosition(105,352);
  
  for(int i=0;i<64;i++){
	  tabShapeBarycentres[i].setSize(sf::Vector2f(6,6));
	  tabShapeBarycentres[i].setFillColor(sf::Color(0,255,0));
  }
  for(int i=0;i<64;i++){
		tabBarycentres[i].etat=0;
		tabBarycentres[i].cx=0;
		tabBarycentres[i].cy=0;
  }
  for(int i=0;i<16;i++){
	  tabShapePoint[i].setSize(sf::Vector2f(8,8));
	  tabShapePoint[i].setFillColor(sf::Color(0,0,255));
  }
  
  defSurface.setTextureRect(sf::IntRect(0, 0, 1045, 700));
  adr << std::fixed << userConfig<<"/surfacesBkg/path5020-24.png";
  std::cout << "getDossierConfig: " << adr.str()<<std::endl;
  selectST.loadFromFile(adr.str());
  defSurface.setTexture(selectST);
  adr.clear();
  adr.str("");
  defSurface.setPosition(sf::Vector2f(527.5,700));
  defSurface.setScale(1,1);
  surfaceX=700;
  surfaceY=700;
  workspaceSurface.setTextureRect(sf::IntRect(surfaceX, surfaceY, 700,700));
  bkgSurface.clear(AppBackGround);
  bkgSurface.draw(defSurface); 
  bkgSurface.display();
  
  defSurface2.setTexture(bkgSurface.getTexture());
  defSurface2.setScale(0.071f,0.071f);
  defSurface2.setPosition(sf::Vector2f(0,0));
  navBkgSurface.draw(defSurface2);
  navBkgSurface.display();
  navWorkspaceSurface.setTextureRect(sf::IntRect(0, 0, 150, 150));
  navWorkspaceSurface.setTexture(&navBkgSurface.getTexture(),false);
}

newSurface::~newSurface(){
}


//*************************************************************************************************** 
bool newSurface::drawSurface(){
	 
  while (surface.isOpen()) {
      sf::Event eventSurface;
      
      while (surface.pollEvent(eventSurface)){
      	switch (eventSurface.type){
	   		case sf::Event::Closed:
		          {
			        surface.close();
			       }
			       break;
		     case sf::Event::Resized:
         	    onResized(eventSurface);
             	 break;
           case sf::Event::MouseWheelScrolled:
		 			 mouseWheel(eventSurface);
             	 break;
           case sf::Event::MouseButtonPressed:
		  			 onClickSurface(eventSurface);
             	 break;
           case sf::Event::MouseButtonReleased:
        			 onMouseButtonUpSurface(eventSurface);
             	 break;
           case sf::Event::MouseMoved:
		          onMouseMoveSurface(eventSurface);
             	 break;
     				  					
	        default: 
             	 break;
  	      }            
     }

  		surface.setActive(true);
		surface.pushGLStates();
		surface.clear(AppBackGround);
		bkgSurface.clear(AppBackGround);
		bkgSurface.draw(defSurface); 

		surface.draw(surfaceSliderDroit);
	   surface.draw(surfaceSliderMDroit);
	   surface.draw(surfaceSliderBas);
	   surface.draw(surfaceSliderMBas);
	   surface.draw(menuBar);
	   surface.draw(barPalette);
	   surface.draw(palette);

	   surface.draw(barycentreTcx);
	   surface.draw(barycentreTcy);
	   surface.draw(thicknessT);
	   surface.draw(nbcT);
	  
	   surface.draw(surfaceTw);
	   surface.draw(surfaceTh);
	   surface.draw(surfaceTname);
	   surface.draw(surfaceTbkg);
	   surface.draw(surfaceTnbpave);
	   
	   surface.draw(navWorkspaceSurface);
		surface.draw(navSurface);
		surface.draw(shapeLineColor);
		surface.draw(shapeBarycentreColor);
		surface.draw(shapePointColor);
		
	   for(int i=0;i<64;i++){
	   	if(tabBarycentres[i].etat==1){
		  		tabShapeBarycentres[i].setPosition(defSurface.getPosition().x+tabBarycentres[i].cx*nscale,defSurface.getPosition().y+tabBarycentres[i].cy*nscale);
   			bkgSurface.draw(tabShapeBarycentres[i]);
		  	}
  		}

		for(int j=0;j<64;j++){
			if(tabBarycentres[j].etat==1){
				for(unsigned short i=0;i<tabBarycentres[j].nconvex.getPointCount();i++){
					float x1=defSurface.getPosition().x+tabBarycentres[j].point[i].x*nscale;
					float y1=defSurface.getPosition().y+tabBarycentres[j].point[i].y*nscale;
					tabBarycentres[j].nconvex.setPoint(i,sf::Vector2f(x1,y1));
				}
				bkgSurface.draw(tabBarycentres[j].nconvex);
			}
		}

		if(paveSelect!=255){
			for(unsigned short i=0;i<tabBarycentres[paveSelect].dim;i++){
				float x1=defSurface.getPosition().x+tabBarycentres[paveSelect].point[i].x*nscale;
				float y1=defSurface.getPosition().y+tabBarycentres[paveSelect].point[i].y*nscale;
				tabShapePoint[i].setPosition(x1,y1);
				bkgSurface.draw(tabShapePoint[i]);
			}
		}
	
		bkgSurface.display();
		workspaceSurface.setTexture(&bkgSurface.getTexture(),false);
		surface.draw(workspaceSurface);
		
		
		surface.display();
		surface.popGLStates();
		surface.setActive(false);
  }
  return surfaceSave;
}
void newSurface::onResized(sf::Event e){
   sf::FloatRect visibleArea(0, 0, e.size.width, e.size.height);
   surface.setView(sf::View(visibleArea));
	workSizeX=e.size.width-220;
	workSizeY=e.size.height-48;
	workspaceSurface.setSize(sf::Vector2f(workSizeX,workSizeY));
	int wx=workspaceSurface.getTextureRect().top;
   int wy=workspaceSurface.getTextureRect().left;
   workspaceSurface.setTextureRect(sf::IntRect(wx, wy, workSizeX, workSizeY));
   
   
   std::cout << "workSizeX: " << workSizeX <<"  workSizeY "<< workSizeY<< std::endl;
   menuBar.setSize(sf::Vector2f(e.size.width,28));
   surfaceSliderDroit.setPosition(e.size.width-18,28);
   surfaceSliderDroit.setSize(sf::Vector2f(18,e.size.height-48));
   wy=surfaceSliderMDroit.getPosition().y;
   surfaceSliderMDroit.setPosition(e.size.width-17,wy);
   surfaceSliderBas.setPosition(200,e.size.height-18);
   surfaceSliderMBas.setPosition(surfaceSliderMBas.getPosition().x,e.size.height-18);
   surfaceSliderBas.setSize(sf::Vector2f(e.size.width-218,18));
   wx=(surfaceSliderBas.getSize().x/2100)*surfaceSliderBas.getSize().x;
   surfaceSliderMBas.setSize(sf::Vector2f(wx,16));
   wy=(surfaceSliderDroit.getSize().y/2100)*surfaceSliderDroit.getSize().y;
   surfaceSliderMDroit.setSize(sf::Vector2f(16,wy));

	float workXScale=150*(workSizeX/2100);
   float workYScale=150*(workSizeY/2100);
   navSurface.setSize(sf::Vector2f(workXScale, workYScale));
   lastAppWidth=e.size.width;
   lastAppHeight=e.size.height;
}
void newSurface::onMouseButtonUpSurface(sf::Event e){
	depNavSurface=0;
	slideMB=0;
	slideMD=0;
	barySelectFlag=0;
	pointSelectFlag=0;
	barycentreID=255;
	paveSelectFlag=0;
}
void newSurface::onClickSurface(sf::Event e){
   std::cout << "the left button was pressed" << std::endl;
   std::cout << "mouse x: " << e.mouseButton.x << std::endl;
   std::cout << "mouse y: " << e.mouseButton.y << std::endl;
   stringstream adr;
   if(e.mouseButton.x>navSurface.getPosition().x && e.mouseButton.x<navSurface.getPosition().x + navSurface.getSize().x && e.mouseButton.y>navSurface.getPosition().y && e.mouseButton.y<navSurface.getPosition().y + navSurface.getSize().y){
   	depNavSurface=1;
   	depNavX=navSurface.getPosition().x-e.mouseButton.x;
   	depNavY=navSurface.getPosition().y-e.mouseButton.y;
   }
   if(e.mouseButton.x>lastAppWidth-18 && e.mouseButton.x<lastAppWidth  && e.mouseButton.y>surfaceSliderMDroit.getPosition().y&& e.mouseButton.y<surfaceSliderMDroit.getPosition().y+surfaceSliderMDroit.getSize().y){
   	slideMD=1;
   	slideMB=0;
   	depNavSurface=0;
   	slideMdY=e.mouseButton.y;
   }
   if(e.mouseButton.x>surfaceSliderMBas.getPosition().x && e.mouseButton.x<surfaceSliderMBas.getPosition().x+surfaceSliderMBas.getSize().x  && e.mouseButton.y>lastAppHeight-48 && e.mouseButton.y<lastAppHeight){
   	slideMD=0;
   	slideMB=1;
   	depNavSurface=0;
   	slideMbX=e.mouseButton.x;
   }
   if(e.mouseButton.x>28 && e.mouseButton.x<50 && e.mouseButton.y>6 && e.mouseButton.y<24){
   	paveSelect=255;
   	for(int i=0;i<64;i++){
   		if(tabBarycentres[i].etat==1){
   			tabShapeBarycentres[i].setFillColor(sf::Color(0,0,0,0));
   		}
   	}
   }
   if(e.mouseButton.x>56 && e.mouseButton.x<78 && e.mouseButton.y>6 && e.mouseButton.y<24){
   	for(int i=0;i<64;i++){
   		if(tabBarycentres[i].etat==1){
   			tabShapeBarycentres[i].setFillColor(sf::Color(0,255,0,255));
   		}
   	}
   }
   if(e.mouseButton.x>126 && e.mouseButton.x<152 && e.mouseButton.y>6 && e.mouseButton.y<24){
   	saveImage();
   }
   if(e.mouseButton.x>workspaceSurface.getPosition().x && e.mouseButton.x<workspaceSurface.getPosition().x+workspaceSurface.getSize().x  && e.mouseButton.y>workspaceSurface.getPosition().y && e.mouseButton.y<workspaceSurface.getPosition().y+workspaceSurface.getSize().y){
		sf::Vector2f ncoord=normaliseMouseXY(e.mouseButton.x, e.mouseButton.y);
   	
   	for(int i=0;i<64;i++){
   		if(tabBarycentres[i].etat==1){
				int rt=inPolygone(tabBarycentres[i], sf::Vector2f(e.mouseButton.x,e.mouseButton.y));
				
				if(rt>0){
					std::cout << "surface : " << i<<std::endl;
						pointSelectFlag=0;
						barycentreID=i;
						paveSelect=i;
						barySelectFlag=0;
						defParametre();
						paveSelectFlag=1;
						nbc=tabBarycentres[i].dim;
						nbcT.setString(to_string(nbc));
						break;
				}
			}
		}
		
		for(int i=0;i<64;i++){
			if(tabBarycentres[i].etat==1 && ncoord.x/nscale>(tabBarycentres[i].cx-12) && ncoord.x/nscale<(tabBarycentres[i].cx+12) && ncoord.y/nscale>(tabBarycentres[i].cy-12) && ncoord.y/nscale<(tabBarycentres[i].cy+12)){
				barySelectFlag=1;
				paveSelectFlag=0;
				pointSelect=255;
				pointSelectFlag=0;
				barycentreID=i;
				paveSelect=i;
			   defParametre();
			   break;
			}
		}
		
		if(paveSelect!=255){
			for(unsigned short i=0;i<tabBarycentres[paveSelect].dim;i++){
				float x1=tabBarycentres[paveSelect].point[i].x;
				float y1=tabBarycentres[paveSelect].point[i].y;
				if(ncoord.x/nscale>x1-12 && ncoord.x/nscale<x1+12 && ncoord.y/nscale>y1-12 && ncoord.y/nscale<y1+12){
					barycentreID=paveSelect;
					pointSelectFlag=1;
					pointSelect=i;
					barySelectFlag=0;
					break;
				}
			}
		}

		if(barycentreID==255){
		  	newPolygone(e,nbc);
		   defParametre();	
   	}
   }

   if(e.mouseButton.x>94 && e.mouseButton.x<112  && e.mouseButton.y>6 && e.mouseButton.y<22){
   	if(paveSelect!=255){
   		stringstream adr;
	   	tabBarycentres[paveSelect].etat=0;
	   	paveSelect=255;
	   	nbPave--;
	   	adr << std::fixed<< std::setprecision(0)<<nbPave;
		   surfaceTnbpave.setString(adr.str());
			surfaceTnbpave.setPosition(162-surfaceTnbpave.getLocalBounds().width-2,290);
   	}
   }
   if(e.mouseButton.x>36 && e.mouseButton.x<164  && e.mouseButton.y>142 && e.mouseButton.y<170){
   	loadBkgImage();
   }
   if(e.mouseButton.x>149 && e.mouseButton.x<164  && e.mouseButton.y>412 && e.mouseButton.y<422){
   	int v=thickness;
   	v++;
   	if(v>4){
   		v=4;
   	}
   	thickness=v;
   	thicknessT.setString(to_string(v));
   	thicknessT.setPosition(146-thicknessT.getLocalBounds().width-2,414);
   }
   if(e.mouseButton.x>149 && e.mouseButton.x<164  && e.mouseButton.y>422 && e.mouseButton.y<432){
   	int v=thickness;
   	v--;
   	if(v<1){
   		v=1;
   	}
   	thickness=v;
   	thicknessT.setString(to_string(v));
   	thicknessT.setPosition(146-thicknessT.getLocalBounds().width-2,414);
   }
   if(e.mouseButton.x>149 && e.mouseButton.x<164  && e.mouseButton.y>444 && e.mouseButton.y<454){
   	int v=nbc;
   	v++;
   	if(v>16){
   		v=16;
   	}
   	nbc=v;
   	nbcT.setString(to_string(v));
   	nbcT.setPosition(146-nbcT.getLocalBounds().width-4,445);
   }
   if(e.mouseButton.x>146 && e.mouseButton.x<164  && e.mouseButton.y>454 && e.mouseButton.y<464){
   	int v=nbc;
   	v--;
   	if(v<3){
   		v=3;
   	}
   	nbc=v;
   	nbcT.setString(to_string(v));
   	nbcT.setPosition(146-nbcT.getLocalBounds().width-4,445);
   }
    if(e.mouseButton.x>102 && e.mouseButton.x<162  && e.mouseButton.y>322 && e.mouseButton.y<340){
    	bool rt=newColor.drawColorSelector(appGui);
    	if(rt==1){
	    	shapeLineColor.setFillColor(newColor.colorSelect());
	    	for(int i=0;i<64;i++){
	    		tabBarycentres[i].nconvex.setOutlineColor(newColor.colorSelect());
	    	}
    	}
    }
    if(e.mouseButton.x>102 && e.mouseButton.x<162  && e.mouseButton.y>382 && e.mouseButton.y<400){
    	bool rt=newColor.drawColorSelector(appGui);
    	if(rt==1){
    		shapeBarycentreColor.setFillColor(newColor.colorSelect());
	    	for(int i=0;i<64;i++){
	 		   tabShapeBarycentres[i].setFillColor(newColor.colorSelect());
  			}
    	}
    }
    if(e.mouseButton.x>102 && e.mouseButton.x<162  && e.mouseButton.y>352 && e.mouseButton.y<370){
    	bool rt=newColor.drawColorSelector(appGui);
    	if(rt==1){
    		shapePointColor.setFillColor(newColor.colorSelect());
	    	for(int i=0;i<16;i++){
	  			tabShapePoint[i].setFillColor(newColor.colorSelect());
  			}
    	}
    }
    if(e.mouseButton.x>164 && e.mouseButton.x<184  && e.mouseButton.y>6 && e.mouseButton.y<26){
    	saveSurface();
    }
    if(e.mouseButton.x>154 && e.mouseButton.x<176  && e.mouseButton.y>72 && e.mouseButton.y<90){
    	openSurface();
    }
}
void newSurface::onMouseMoveSurface(sf::Event e){
   std::cout << "mouse x: " << e.mouseMove.x << std::endl;
   std::cout << "mouse y: " << e.mouseMove.y << std::endl;
   int ndpx=0;
   int ndpy=0;
   float lpx;
	float lpy;
	float mx;
	float my;

   if (depNavSurface==1 && e.mouseMove.x > navWorkspaceSurface.getPosition().x && e.mouseMove.x<navWorkspaceSurface.getSize().x+navWorkspaceSurface.getPosition().x && e.mouseMove.y > navWorkspaceSurface.getPosition().y && e.mouseMove.y<navWorkspaceSurface.getPosition().y+navWorkspaceSurface.getSize().y ){
   	ndpx= e.mouseMove.x+depNavX;
   	ndpy= e.mouseMove.y+depNavY;
   	if(ndpx+navSurface.getSize().x>navWorkspaceSurface.getSize().x+navWorkspaceSurface.getPosition().x){
   		ndpx=(navWorkspaceSurface.getPosition().x+navWorkspaceSurface.getSize().x)-navSurface.getSize().x;
   	}
   	if(ndpy+navSurface.getSize().y>navWorkspaceSurface.getSize().y+navWorkspaceSurface.getPosition().y){
   		ndpy=(navWorkspaceSurface.getPosition().y+navWorkspaceSurface.getSize().y)-navSurface.getSize().y;
   	}
   	if(ndpx<navWorkspaceSurface.getPosition().x){
   		ndpx=navWorkspaceSurface.getPosition().x;
   	}
   	if(ndpy<navWorkspaceSurface.getPosition().y){
   		ndpy=navWorkspaceSurface.getPosition().y;
   	}
   	int wx=workspaceSurface.getTextureRect().width;
   	int wy=workspaceSurface.getTextureRect().height;
   	navSurface.setPosition(sf::Vector2f(ndpx,ndpy));
   	int rtx=workspaceSurface.getSize().x/navSurface.getSize().x;
      int rty=workspaceSurface.getSize().y/navSurface.getSize().y;
   	workspaceSurface.setTextureRect(sf::IntRect((ndpx-navWorkspaceSurface.getPosition().x)*rtx, (ndpy-navWorkspaceSurface.getPosition().y)*rty, wx,wy));
   }
   if (slideMD==1 && e.mouseMove.x > lastAppWidth-slideHeight && e.mouseMove.x<lastAppWidth && e.mouseMove.y > surfaceSliderMDroit.getPosition().y && e.mouseMove.y<surfaceSliderMDroit.getPosition().y+surfaceSliderMDroit.getSize().y){ 
      	
     int nposy=surfaceSliderMDroit.getPosition().y+(e.mouseMove.y-slideMdY);
     if(nposy<surfaceSliderDroit.getPosition().y+1){
   		nposy=surfaceSliderDroit.getPosition().y+1;
     }
     if(nposy+surfaceSliderMDroit.getSize().y>surfaceSliderDroit.getSize().y+menuBarHeight){
   		nposy=surfaceSliderDroit.getSize().y-surfaceSliderMDroit.getSize().y+menuBarHeight;
     }
     surfaceSliderMDroit.setPosition(surfaceSliderMDroit.getPosition().x,nposy);
     nposy=nposy-menuBarHeight;
     navSurface.setPosition(sf::Vector2f(navSurface.getPosition().x,(nposy*(navWorkspaceSurface.getSize().y/workspaceSurface.getSize().y))+navWorkspaceSurface.getPosition().y));//navSurface.getSize().y/workspaceSurface.geSize().y=0.21    bkgSurface.getSize().y/navSurface.getSize().y=14
     int wx=workspaceSurface.getTextureRect().width;
     int wy=workspaceSurface.getTextureRect().height;
     int rtx=workspaceSurface.getSize().x/navSurface.getSize().x;
     int rty=workspaceSurface.getSize().y/navSurface.getSize().y;
     workspaceSurface.setTextureRect(sf::IntRect((navSurface.getPosition().x-navWorkspaceSurface.getPosition().x)*rtx, ((nposy*(navWorkspaceSurface.getSize().y/workspaceSurface.getSize().y))*rty), wx,wy));
     slideMdY=e.mouseMove.y; 
   }
   if (slideMB==1 && e.mouseMove.x > surfaceSliderMBas.getPosition().x && e.mouseMove.x<surfaceSliderMBas.getPosition().x+surfaceSliderMBas.getSize().x && e.mouseMove.y > lastAppHeight-slideHeight-menuBarHeight && e.mouseMove.y<lastAppHeight ){   	
     int nposx=surfaceSliderMBas.getPosition().x+(e.mouseMove.x-slideMbX);
     if(nposx<surfaceSliderBas.getPosition().x+1){
   		nposx=surfaceSliderBas.getPosition().x+1;
     }
     if(nposx+surfaceSliderMBas.getSize().x>surfaceSliderBas.getSize().x+workspaceSurface.getPosition().x){
   		nposx=surfaceSliderBas.getSize().x-surfaceSliderMBas.getSize().x+workspaceSurface.getPosition().x;
     }
     surfaceSliderMBas.setPosition(nposx,surfaceSliderMBas.getPosition().y);
     navSurface.setPosition(sf::Vector2f(((nposx-workspaceSurface.getPosition().x)*(navWorkspaceSurface.getSize().x/workspaceSurface.getSize().x))+navWorkspaceSurface.getPosition().x,navSurface.getPosition().y));
     int wx=workspaceSurface.getTextureRect().width;
     int wy=workspaceSurface.getTextureRect().height;
     int rtx=workspaceSurface.getSize().x/navSurface.getSize().x;
     int rty=workspaceSurface.getSize().y/navSurface.getSize().y;
     workspaceSurface.setTextureRect(sf::IntRect(((nposx-workspaceSurface.getPosition().x)*(navWorkspaceSurface.getSize().x/workspaceSurface.getSize().x))*rtx,(navSurface.getPosition().y-navWorkspaceSurface.getPosition().y)*rty, wx,wy));
     slideMbX=e.mouseMove.x; 
   }
   if(paveSelectFlag==1 && paveSelect!=255){
   	sf::Vector2f ncoord=normaliseMouseXY(e.mouseMove.x-3, e.mouseMove.y-3);
		lpx=(ncoord.x/nscale)-tabBarycentres[paveSelect].cx;
		lpy=(ncoord.y/nscale)-tabBarycentres[paveSelect].cy;
		tabBarycentres[paveSelect].cx=ncoord.x/nscale;
		tabBarycentres[paveSelect].cy=ncoord.y/nscale;
		for(int i=0;i<tabBarycentres[paveSelect].dim;i++){
			tabBarycentres[paveSelect].point[i].x=tabBarycentres[paveSelect].point[i].x+lpx;
			tabBarycentres[paveSelect].point[i].y=tabBarycentres[paveSelect].point[i].y+lpy;
		}
   }
   if(barySelectFlag==1 && paveSelect!=255){
		sf::Vector2f ncoord=normaliseMouseXY(e.mouseMove.x-3, e.mouseMove.y-3);
		lpx=(ncoord.x/nscale)-tabBarycentres[paveSelect].cx;
		lpy=(ncoord.y/nscale)-tabBarycentres[paveSelect].cy;
		tabBarycentres[paveSelect].cx=ncoord.x/nscale;
		tabBarycentres[paveSelect].cy=ncoord.y/nscale;
		defParametre();
   }
   if(pointSelectFlag==1 && paveSelect!=255){ 	
		stringstream adr;
		sf::Vector2f ncoord=normaliseMouseXY(e.mouseMove.x-3, e.mouseMove.y-3);
		tabBarycentres[paveSelect].point[pointSelect].x=ncoord.x/nscale;
		tabBarycentres[paveSelect].point[pointSelect].y=ncoord.y/nscale;
   }
}
void newSurface::mouseWheel(sf::Event e){
  if (e.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel){
	if(e.mouseWheelScroll.delta==1){
		nscale=nscale-0.01;
		if(nscale<-2){
		 	nscale=2;
		} 	
	}else{
		nscale=nscale+0.01;
		if(nscale>2){
		 	nscale=2;
		} 	
	}
	float dtx=defSurface.getTextureRect().width;
	float dty=defSurface.getTextureRect().height; 
	defSurface.setScale(nscale,nscale);
   surfaceX=(bkgSurface.getSize().x-(dtx*nscale))/2;
   surfaceY=(bkgSurface.getSize().y-(dty*nscale))/2;
   	
	defSurface.setPosition(sf::Vector2f(surfaceX,surfaceY));
	bkgSurface.clear(AppBackGround);
	bkgSurface.draw(defSurface);
	bkgSurface.display();
	
	defSurface2.setTexture(bkgSurface.getTexture());
	defSurface2.setScale(0.071f,0.071f);
	defSurface2.setPosition(sf::Vector2f(0,0));
	navBkgSurface.draw(defSurface2);
	navBkgSurface.display();
	 std::cout << "scale : "<<nscale  << std::endl;
  }
}

void newSurface::loadBkgImage(){
	string path=userConfig;
	char * cstr = new char [userConfig.length()+1];
   std::strcpy (cstr, userConfig.c_str());
   int ncwd=chdir(cstr);
	string nameFile;
	stringstream adr;

	nameFile=fileSelector.selector();
	path=getcwd(NULL,0);
	defBkgImage(path,nameFile);

}
void newSurface::defBkgImage(string path, string nameFile){
	stringstream adr;
	if(nameFile!=""){
		adr << std::fixed << path<<"/"<<nameFile;
	   std::cout << "getDossierConfig: " << adr.str()<<std::endl;
	   selectST.loadFromFile(adr.str());
	   adr.clear();
		adr.str("");
		sf::Vector2u nimage=selectST.getSize();
	   float px=(2100-nimage.x)/2;
	   float py=(2100-nimage.y)/2;
	   defSurface.setTextureRect(sf::IntRect(0, 0, nimage.x, nimage.y));
	   defSurface.setTexture(selectST);
	   defSurface.setPosition(px,py);
	   bkgSurface.clear(AppBackGround);
		bkgSurface.draw(defSurface);
	   defSurface2.setTexture(bkgSurface.getTexture());
	   defSurface2.setScale(0.071f,0.071f);
	   defSurface2.setPosition(sf::Vector2f(0,0));
	   navBkgSurface.draw(defSurface2);
	   
		adr << std::fixed<< std::setprecision(2)<<nimage.x;
		surfaceTw.setString(adr.str());
		surfaceTw.setPosition(162-surfaceTw.getLocalBounds().width-2,182);
		adr.clear();
		adr.str("");
		adr << std::fixed<< std::setprecision(2)<<nimage.y;
		surfaceTh.setString(adr.str());
		surfaceTh.setPosition(162-surfaceTh.getLocalBounds().width-2,214);
		adr.clear();
		adr.str("");	
		nameBkgFile=nameFile;
		pathBkgFile=path;
		string s=nameFile.substr(0,nameFile.length()-4);
		surfaceTname.setString(s);
		surfaceTname.setPosition(148-surfaceTname.getLocalBounds().width-2,72);
		surfaceTbkg.setString(nameFile);
		surfaceTbkg.setPosition(164-surfaceTbkg.getLocalBounds().width-2,146);
		nameFile="";
		bkgSurfaceSize=sf::Vector2f(nimage.x,nimage.y);
	
	}
}
void newSurface::saveImage(){
	int rs=paveSelect;
	paveSelect=255;
	string nameFile=fileSelector.selector();
	string path=getcwd(NULL,0);
	
	if(nameFile!=""){
		bkgSurface.getTexture().copyToImage().saveToFile(path+"/"+nameFile);
		std::cout << "save: " << path+"/"+nameFile<< " nameFile "<<nameFile<<std::endl;
	}
	paveSelect=rs;
}
int newSurface::inPolygone(barycentre &shape, sf::Vector2f p){
	int nbc=shape.dim;
	sf::Vector2f s1,s2;
	int    wn = 0;    // the  winding number counter
   
	sf::Vector2f ncoord=normaliseMouseXY(p.x, p.y);
	p.x=ncoord.x/nscale;
	p.y=ncoord.y/nscale;
				
   shape.point[nbc]=shape.point[0];
    for (int i = 0; i<nbc; i++) {   // edge from V[i] to  V[i+1]
    	  s1=shape.point[i];
    	  s2=shape.point[i+1];
		  if(s1.y<=p.y){
		  	 if(s2.y>p.y){
		  	 	if(isLeft(s1,s2,p)>0){
		  	 		++wn;
		  	 	}
		  	 }
		  }else{
		  	 if(s2.y<=p.y){
		  	 	if(isLeft(s1,s2,p)<0){
		  	 		--wn;
		  	 	}
		  	 }
		  }
		   std::cout << "le point appartient : "<<p.x<<" , "<<p.y<<" , "<<shape.point[i].x<<" , "<<shape.point[i].y<< "  "<<wn<< std::endl;	 
    }
	return wn;
	
}
int newSurface::isLeft(const sf::Vector2f &p0,const sf::Vector2f &p1,const sf::Vector2f &point){
    return ((p1.x - p0.x) * (point.y - p0.y) -
            (point.x - p0.x) * (p1.y - p0.y));
}
void newSurface::newPolygone(sf::Event e,int nbc){
	float radius_x=80;
	float radius_y=60;
	float PI=3.14159265359;
   stringstream adr;
	paveSelect=255;
	for(int i=0;i<64;i++){
		if(tabBarycentres[i].etat==0){
			paveSelect=i;
			tabBarycentres[i].etat=1;
			break;
		}
	}
	
	if(paveSelect!=255){
	   tabBarycentres[paveSelect].dim=nbc;
	   tabBarycentres[paveSelect].nconvex.setPointCount(nbc);
	   tabBarycentres[paveSelect].nconvex.setFillColor(sf::Color(255,0,0,0));
		tabBarycentres[paveSelect].nconvex.setOutlineThickness(thickness);
		tabBarycentres[paveSelect].nconvex.setOutlineColor(sf::Color(shapeLineColor.getFillColor()));

		sf::Vector2f ncoord=normaliseMouseXY(e.mouseButton.x, e.mouseButton.y);
		
		tabBarycentres[paveSelect].cx=ncoord.x/nscale;
		tabBarycentres[paveSelect].cy=ncoord.y/nscale;
		
		for(unsigned short i=0;i<nbc;i++){
		 float rad=(360/nbc*i)/(360/PI/2);
	    float x=(cos(rad)*radius_x)+tabBarycentres[paveSelect].cx;
	    float y=(sin(rad)*radius_y)+tabBarycentres[paveSelect].cy;
	    tabBarycentres[paveSelect].nconvex.setPoint(i,sf::Vector2f(x,y));
	    std::cout << "point convex : "<<x<<" , "<<y<<" , "<<tabBarycentres[paveSelect].nconvex.getPoint(i).x<<" , "<<tabBarycentres[paveSelect].nconvex.getPoint(i).y<< std::endl;	
	    tabBarycentres[paveSelect].point[i]=sf::Vector2f(x,y);
		}
		nbPave++;
		adr << std::fixed<< std::setprecision(0)<<nbPave;
		surfaceTnbpave.setString(adr.str());
		surfaceTnbpave.setPosition(162-surfaceTnbpave.getLocalBounds().width-2,290);
		tabBarycentres[paveSelect].fileSound="";
   	tabBarycentres[paveSelect].path="";
   	tabBarycentres[paveSelect].canaux=0;
    	tabBarycentres[paveSelect].duree=0;
    	tabBarycentres[paveSelect].daw=0;
    	tabBarycentres[paveSelect].track=0;
      tabBarycentres[paveSelect].dimMixer=1.0;
    	tabBarycentres[paveSelect].gainMin=0;
    	tabBarycentres[paveSelect].gainMax=2;
    	tabBarycentres[paveSelect].fx=0;
    	tabBarycentres[paveSelect].curseurEtat=0;
    	tabBarycentres[paveSelect].curseurType=0;
      tabBarycentres[paveSelect].curseurX=0;
    	tabBarycentres[paveSelect].curseurY=0;
    	tabBarycentres[paveSelect].listfx="";
	}
}
sf::Vector2f newSurface::normaliseMouseXY(float x, float y){
	float lpx;
	float lpy;
	float mx;
	float my;
	if(defSurface.getPosition().x>workspaceSurface.getTextureRect().left){
			lpx=(defSurface.getPosition().x-workspaceSurface.getTextureRect().left);
			mx=(x-200)-lpx;
	 }else{
		   lpx=(workspaceSurface.getTextureRect().left-defSurface.getPosition().x);
			mx=(x-200)+lpx;
	 }
	 if(defSurface.getPosition().y>workspaceSurface.getTextureRect().top){
			lpy=(defSurface.getPosition().y-workspaceSurface.getTextureRect().top);
			my=y-lpy-workspaceSurface.getPosition().y;
	 }else{
		   lpy=(workspaceSurface.getTextureRect().top-defSurface.getPosition().y);
			my=y+lpy-workspaceSurface.getPosition().y;
	 }
	 return sf::Vector2f(mx,my);
}
void newSurface::defParametre(){
	stringstream adr;
	adr << std::fixed<< std::setprecision(2)<<tabBarycentres[paveSelect].cx;
	barycentreTcx.setString(adr.str());
	barycentreTcx.setPosition(150-barycentreTcx.getLocalBounds().width-2,514);
	adr.clear();
	adr.str("");
	adr << std::fixed<< std::setprecision(2)<<tabBarycentres[paveSelect].cy;
	barycentreTcy.setString(adr.str());
	barycentreTcy.setPosition(150-barycentreTcy.getLocalBounds().width-2,544);
	adr.clear();
	adr.str("");
}
float newSurface::distanceCentre(float cx, float cy, float x, float y){
	float dt=sqrt(pow(cx-x,2)+pow(cy-y,2));
	return dt;
}
void newSurface::saveSurface(){
	string path=userConfig;
	char * cstr = new char [userConfig.length()+1];
   std::strcpy (cstr, userConfig.c_str());
   int ncwd=chdir(cstr);
	string nameFile;
	ostringstream ss;
	string s;
	float distance=0;
	nameFile=fileSelector.selector();
	path=getcwd(NULL,0);
   s=nameFile.substr(0,nameFile.length()-4);
   nameDestFile=nameFile;
   pathDestFile=path;
	surfaceTname.setString(s);
	surfaceTname.setPosition(148-surfaceTname.getLocalBounds().width-2,106);
	if(nameFile!=""){
		nameFile=path+"/"+nameFile;
		std::cout << "path: " << path<< "file :"<<nameFile<< std::endl;

		ofstream fichier(nameFile, ios::out | ios::trunc);	
	   if(fichier){
	   	s=surfaceTname.getString();
	   	fichier<<"padName="<<s<< endl;
	   	fichier<<"type="<<nbPave<< endl;
	   	
	   	fichier<<"nameBkgFile="<<nameBkgFile<< endl;
	   	fichier<<"pathBkgFile="<<pathBkgFile<< endl;
	   	fichier<<"surfaceWidth="<<bkgSurfaceSize.x<< endl;
	   	fichier<<"surfaceHeight="<<bkgSurfaceSize.y<< endl;
	   	sf::Uint32 bkgc = shapeLineColor.getFillColor().toInteger();
	   	fichier<<"editLineColor="<<std::hex <<bkgc << endl;
	   	fichier<<"editLineThickness="<<thickness << endl;
	   	bkgc = shapeBarycentreColor.getFillColor().toInteger();
	   	fichier<<"barycentreColor="<<bkgc << endl;
	   	bkgc = shapePointColor.getFillColor().toInteger();
	   	fichier<<"pointColor="<<bkgc << endl;
	   	
	   	if(surfaceEtat==1){
		   	fichier<<"temporisationMin="<<std::dec <<temporisationMin<< endl;
		   	fichier<<"temporisationMax="<<temporisationMax<< endl;
		   	fichier<<"vieMin="<<vieMin<<endl;
	   		fichier<<"vieMax="<<vieMax<<endl;
	   		fichier<<"exploseMax="<<exploseMax<<endl;
	   	}else{
	   		fichier<<"temporisationMin="<<std::dec <<5<< endl;
		   	fichier<<"temporisationMax="<<20<< endl;
		   	fichier<<"vieMin="<<10000<<endl;
	   		fichier<<"vieMax="<<300000<<endl;
	   		fichier<<"exploseMax="<<10<<endl;
	   	}
	   	
	   	for(int i=0;i<nbPave;i++){
	   		fichier<<"pad="<<i<< endl;
	   		fichier<<"dim="<<tabBarycentres[i].dim<<endl;
	   		fichier<<"fileSound="<<tabBarycentres[i].fileSound<<endl;
	   		fichier<<"path="<<tabBarycentres[i].path<<endl;
	   		fichier<<"canaux="<<tabBarycentres[i].canaux<<endl;
	   		fichier<<"daw="<<tabBarycentres[i].daw<<endl;
	   		fichier<<"duree"<<tabBarycentres[i].duree<<endl;
	    		fichier<<"track="<<tabBarycentres[i].track<<endl;
	    		fichier<<"Cx="<<tabBarycentres[i].cx<< endl;
	   		fichier<<"Cy="<<tabBarycentres[i].cy<< endl;
	    		fichier<<"dimMixer="<<tabBarycentres[i].dimMixer<<endl;
	      	fichier<<"gainMin="<<tabBarycentres[i].gainMin<<endl;
	    		fichier<<"gainMax="<<tabBarycentres[i].gainMax<<endl;
	    		fichier<<"fx="<<tabBarycentres[i].fx<<endl;
	    		fichier<<"curseurEtat="<<tabBarycentres[i].curseurEtat<<endl;
	    		fichier<<"curseurType="<<tabBarycentres[i].curseurType<<endl;
	      	fichier<<"curseurX="<<tabBarycentres[i].curseurX<<endl;
	    		fichier<<"curseurY="<<tabBarycentres[i].curseurY<<endl;
	    		fichier<<"listfx="<<tabBarycentres[i].listfx<<endl;
	    		tabBarycentres[i].distanceMax=0;
	   		for(int j=0;j<tabBarycentres[i].dim;j++){
	   			fichier<<"px="<<tabBarycentres[i].point[j].x<< endl;
	   			fichier<<"py="<<tabBarycentres[i].point[j].y<< endl;
	   			distance=distanceCentre(tabBarycentres[i].cx, tabBarycentres[i].cy, tabBarycentres[i].point[j].x, tabBarycentres[i].point[j].y);
	   			if(distance>tabBarycentres[i].distanceMax){
	   				tabBarycentres[i].distanceMax=distance;
	   			}
	   		}
	   		fichier<<"distanceMax="<<tabBarycentres[i].distanceMax<<endl;
	   	}
	   	
	   	fichier.close();
	   	surfaceSave=1;
		}else{  // sinon
	     cerr << "Erreur à l'ouverture du fichier!" << endl;
	     surfaceSave=0;
		} 
	}
}
void newSurface::openSurface(){
	string path=userConfig;
	char * cstr = new char [userConfig.length()+1];
   std::strcpy (cstr, userConfig.c_str());
   int ncwd=chdir(cstr);
	string nameFile;
	ostringstream ss;
	string s;
	int pad=0;
	int pt=0;
	int ip=0;
	string contenu;
   string pf[2];
   int i=0;
	nameFile=fileSelector.selector();
	path=getcwd(NULL,0);
	s=nameFile.substr(0,nameFile.length()-4);
	surfaceTname.setString(s);
	surfaceTname.setPosition(148-surfaceTname.getLocalBounds().width-2,106);
	
	if(nameFile.substr(nameFile.length()-3,nameFile.length())=="msf"){
		nameFile=path+"/"+nameFile;
		std::cout << "path: " << path<< "file :"<<nameFile<< std::endl;
		ifstream fichier(nameFile, ios::in);
		if(fichier){  // si l'ouverture a réussi   
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
	  			if(pf[0]=="padName"){
					surfaceTname.setString(pf[1]);
					surfaceTname.setPosition(148-surfaceTname.getLocalBounds().width-2,74);
	  			}
	  			if(pf[0]=="type"){
	  				nbPave=stoi(pf[1]);
					surfaceTnbpave.setString(to_string(nbPave));
					surfaceTnbpave.setPosition(162-surfaceTnbpave.getLocalBounds().width-2,290);
	  			}
	  			if(pf[0]=="nameBkgFile"){
	  				nameBkgFile=pf[1];
					surfaceTbkg.setString(nameBkgFile);
					surfaceTbkg.setPosition(164-surfaceTbkg.getLocalBounds().width-2,146);
	  			}
	  			if(pf[0]=="pathBkgFile"){
	  				pathBkgFile=pf[1];
	  				defBkgImage(pathBkgFile, nameBkgFile);
	  			}
	  			if(pf[0]=="surfaceWidth"){
	  				bkgSurfaceSize.x=stof(pf[1]);
	  			}
	  			if(pf[0]=="surfaceHeight"){
	  				bkgSurfaceSize.y=stof(pf[1]);
	  			}
	  			if(pf[0]=="editLineColor"){
	  				shapeLineColor.setFillColor(sf::Color(std::stoul(pf[1],nullptr,16)));
	  			}
	  			if(pf[0]=="editLineThickness"){
	  				thickness=stoi(pf[1]);
	  				thicknessT.setString(to_string(thickness));
						thicknessT.setPosition(146-thicknessT.getLocalBounds().width-2,414);
	  			}
	  			if(pf[0]=="barycentreColor"){
	  				shapeBarycentreColor.setFillColor(sf::Color(std::stoul(pf[1],nullptr,16)));
	  				for(int i=0;i<64;i++){
	 		   		tabShapeBarycentres[i].setFillColor(shapeBarycentreColor.getFillColor());
  					}
	  			}
	  			if(pf[0]=="pointColor"){
	  				shapePointColor.setFillColor(sf::Color(std::stoul(pf[1],nullptr,16)));
	  				for(int i=0;i<16;i++){
	  					tabShapePoint[i].setFillColor(shapePointColor.getFillColor());
  					}
	  			}
	  			if(pf[0]=="temporisationMin"){
	  				temporisationMin=stof(pf[1]);
	  			}
	  			if(pf[0]=="temporisationMax"){
	  				temporisationMax=stof(pf[1]);
	  			}
	  			if(pf[0]=="vieMin"){
	  				vieMin=stof(pf[1]);
	  			}
	  			if(pf[0]=="vieMax"){
	  				vieMax=stof(pf[1]);
	  			}
	  			if(pf[0]=="exploseMax"){
	  				exploseMax=stof(pf[1]);
	  			}
	  			if(pf[0]=="pad"){
	  				pad=stoi(pf[1]);
	  				tabBarycentres[pad].nconvex.setFillColor(sf::Color(0,0,0,0));
					tabBarycentres[pad].nconvex.setOutlineThickness(thickness);
					tabBarycentres[pad].nconvex.setOutlineColor(sf::Color(shapeLineColor.getFillColor()));
	  				tabBarycentres[pad].etat=1;
	  				pt=0;
	  			}
	  			if(pf[0]=="dim"){
	  				tabBarycentres[pad].dim=stoi(pf[1]);
	  				tabBarycentres[pad].nconvex.setPointCount(tabBarycentres[pad].dim);
	  				pf[1]="";
	  			}
	  			if(pf[0]=="fileSound"){
	  				tabBarycentres[pad].fileSound=pf[1];
	  			}
	  			if(pf[0]=="path"){
	  				tabBarycentres[pad].path=pf[1];
	  			}
	  			if(pf[0]=="canaux"){
	  				tabBarycentres[pad].canaux=stoi(pf[1]);
	  			}
	  			if(pf[0]=="duree"){
	  				tabBarycentres[pad].duree=stof(pf[1]);
	  			}
	  			if(pf[0]=="daw"){
	  				if(stoi(pf[1])==0){
	  					tabBarycentres[pad].daw=0;
	  				}else{
	  					tabBarycentres[pad].daw=1;
	  				}
	  			}
				if(pf[0]=="track"){
	  				tabBarycentres[pad].track=stoi(pf[1]);
	  			}
	  			if(pf[0]=="Cx"){
	  				tabBarycentres[pad].cx=stof(pf[1]);
	  			}
	  			if(pf[0]=="Cy"){
	  				tabBarycentres[pad].cy=stof(pf[1]);
	  			}
	  			if(pf[0]=="dimMixer"){
	  				tabBarycentres[pad].dimMixer=stof(pf[1]);
	  			}
	  			if(pf[0]=="gainMin"){
	  				tabBarycentres[pad].gainMin=stof(pf[1]);
	  			}
	  			if(pf[0]=="gainMax"){
	  				tabBarycentres[pad].gainMax=stof(pf[1]);
	  			}
	  			if(pf[0]=="fx"){
	  				if(stoi(pf[1])==0){
	  					tabBarycentres[pad].fx=0;
	  				}else{
	  					tabBarycentres[pad].fx=1;
	  				}
	  			}
				if(pf[0]=="curseurEtat"){
	  				if(stoi(pf[1])==0){
	  					tabBarycentres[pad].curseurEtat=0;
	  				}else{
	  					tabBarycentres[pad].curseurEtat=1;
	  				}
	  			}
	  			if(pf[0]=="curseurType"){
	  				tabBarycentres[pad].curseurType=stoi(pf[1]);
	  			}
	  			if(pf[0]=="curseurX"){
	  				tabBarycentres[pad].curseurX=stof(pf[1]);
	  			}
	  			if(pf[0]=="curseurY"){
	  				tabBarycentres[pad].curseurY=stof(pf[1]);
	  				pf[1]="";
	  			}
	  			if(pf[0]=="listfx"){
	  				tabBarycentres[pad].listfx=pf[1];
	  			}
	  			if(pf[0]=="px"){
	  				tabBarycentres[pad].point[pt].x=stof(pf[1]);
	  			}
	  			if(pf[0]=="py"){
	  				tabBarycentres[pad].point[pt].y=stof(pf[1]);
	  				pt++;
	  			}
	  		}
	  		tabBarycentres[pad].nconvex.setFillColor(sf::Color(0,0,0,0));
			tabBarycentres[pad].nconvex.setOutlineThickness(thickness);
			tabBarycentres[pad].nconvex.setOutlineColor(sf::Color(shapeLineColor.getFillColor()));
		  		std::cout << "fichier chargé" << std::endl;
	  	}else{  // sinon
	     cerr << "Erreur à l'ouverture du fichier!" << endl;
		} 	
	}
}
string newSurface::surfaceDefPath(){
	return pathDestFile;
}
string newSurface::surfaceDefFile(){
	return nameDestFile;
}
