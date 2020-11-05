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

#include "selectFile.h"
#include "info.h"

using namespace std;

selectFile::selectFile(){
}

selectFile::~selectFile(){
}
void selectFile::setSelectorDossier(string path){
	dossier=path;
}
void selectFile::setSelectorWidth(float w){
	winSelectorWidth=w;
}
void selectFile::setSelectorHeight(float h){
	winSelectorHeight=h;
}
void selectFile::setSelectorBarColor(sf::Color sBC){
	selectorBarColor=sBC;
}
void selectFile::setSelectorBkgColor(sf::Color sBkgC){
	selectorBkgColor=sBkgC;
}
void selectFile::setSelectorPathColor(sf::Color pathC){
	selectDefPath.setFillColor(sf::Color(pathC));
}
void selectFile::setSelectorFileColor(sf::Color fileC){
	selectFileS.setFillColor(sf::Color(fileC));
}
void selectFile::setSelectorLineColor(sf::Color lineC){
	lineBloc.setFillColor(sf::Color(lineC));
	lineBloch.setFillColor(sf::Color(lineC));
	lineBloc2.setFillColor(sf::Color(lineC));
	lineBloch2.setFillColor(sf::Color(lineC));
}
void selectFile::setSelectorSlider1Color(sf::Color slider1C){
	selectMSlider.setFillColor(sf::Color(slider1C));
}
void selectFile::setSelectorSlider2Color(sf::Color slider2C){
	selectMSlider2.setFillColor(sf::Color(slider2C));
}
void selectFile::setSelectorSlider1thColor(sf::Color slider1thC){
	selectMSlider.setOutlineColor(sf::Color(slider1thC));
}
void selectFile::setSelectorSlider2thColor(sf::Color slider2thC){
	selectMSlider2.setOutlineColor(sf::Color(slider2thC));
}
void selectFile::setSelectorFontColor(sf::Color sFC){
	selectorFontColor=sFC;
}
void selectFile::setSelectorFontSize(int sFS){
	selectorFontSize=sFS;
}
void selectFile::setSelectFontSize(int sFS){
	selectFontSize=sFS;
}
void selectFile::setDirFontColor(sf::Color sFdC){
	dirFontColor=sFdC;
}
void selectFile::setFileFontColor(sf::Color sFfC){
	fileFontColor=sFfC;
}
void selectFile::setTitreSelector(sf::String sT){
	titreSelector=sT;
}
void selectFile::setSelectorGui(sf::String gui){
	fGui=gui;
}
void selectFile::setSelectorTheme(sf::String theme){
	fTheme=theme;
}
void selectFile::setSelectorLang(sf::String fLang){
	fichierLang=fLang;
}
void selectFile::setSelectorSimpleLecteur(std::string sfl){
	strcpy(simplePlayer,sfl.c_str());
}
void selectFile::setNText(string nt){
	nText.setString(nt);
}
std::string selectFile::getGui() const{
	return fGui;
}


void selectFile::initSelector(string fdir){
  std::stringstream adr;
  adr << std::fixed << fGui<<"/Arial.ttf";
  font.loadFromFile(adr.str());
  adr.clear();
  adr.str("");
  winSelector.setTitle(titreSelector);
  nText.setString("");
  dossier=fdir;
  dossierPath.setString(dossier);
  listDirs(dossier);
  readFiles();
  newInfo.setInfo(fTheme,fGui);
  newInfo.setInfoTxtSize(13);
  newInfo.setInfoTxtFillColor(sf::Color(0,0,0,255));

  selectBarH.setSize(sf::Vector2f(winSelectorWidth, 36));
  selectBarH.setFillColor(selectorBarColor);
  selectBarH.setPosition(sf::Vector2f(0,0));
  selectDefPath.setSize(sf::Vector2f(430, 24)); // Path
  selectDefPath.setPosition(sf::Vector2f(38,6));
  selectBarB.setSize(sf::Vector2f(winSelectorWidth, 36)); 
  selectBarB.setFillColor(sf::Color(selectorBarColor));
  selectBarB.setPosition(sf::Vector2f(0,400));
  selectFileS.setSize(sf::Vector2f(300, 24));   // Fichier
  selectFileS.setPosition(sf::Vector2f(48, 406));
  
  selectShap.setSize(sf::Vector2f(172, 18));
  selectShap.setFillColor(selectorBarColor);
  selectShap.setPosition(sf::Vector2f(2, 40));
  
  selectBkgSlider.setSize(sf::Vector2f(20, 364));
  selectBkgSlider.setFillColor(selectorBarColor);
  selectBkgSlider.setPosition(sf::Vector2f(182,36));
  lineBloc.setSize(sf::Vector2f(2,364));
  lineBloc.setPosition(sf::Vector2f(180,36));
  lineBloch.setSize(sf::Vector2f(22,2));
  lineBloch.setPosition(sf::Vector2f(180,36));
  
  selectBkgSlider2.setSize(sf::Vector2f(18, 364));
  selectBkgSlider2.setFillColor(selectorBarColor);
  selectBkgSlider2.setPosition(sf::Vector2f(482,36));
  lineBloc2.setSize(sf::Vector2f(2,364));
  lineBloc2.setPosition(sf::Vector2f(480,36));
  lineBloch2.setSize(sf::Vector2f(22,2));
  lineBloch2.setPosition(sf::Vector2f(480,36));
  
  selectMSlider.setPosition(sf::Vector2f(184,38));
  selectMSlider.setOutlineThickness(1.f);
  selectMSlider2.setPosition(sf::Vector2f(484,38));
  selectMSlider2.setOutlineThickness(1.f);

  adr << std::fixed << fGui<<"/folder-new.png";
  selectFolder.loadFromFile(adr.str());
  selectNew.setTexture(selectFolder);
  selectNew.setPosition(sf::Vector2f(10, 406));
  adr.clear();
  adr.str("");
  adr << std::fixed << fGui<<"/bAnnuler.png";
  selectBAnnuler.loadFromFile(adr.str());
  selectAnnuler.setTexture(selectBAnnuler);
  selectAnnuler.setPosition(sf::Vector2f(360, 402));
  adr.clear();
  adr.str("");
  adr << std::fixed << fGui<<"/bValider.png";
  selectBValider.loadFromFile(adr.str());
  selectValider.setTexture(selectBValider);
  selectValider.setPosition(sf::Vector2f(420, 402));
  adr.clear();
  adr.str("");
  adr << std::fixed << fGui<<"/audio-speakers.png";
  selectSpeakers.loadFromFile(adr.str());
  speaker.setTexture(selectSpeakers);
  adr.clear();
  adr.str("");

  dossierPath.setFont(font);
  dossierPath.setString("");
  dossierPath.setCharacterSize(selectorFontSize);
  dossierPath.setPosition(sf::Vector2f(60, 8));
  dossierPath.setFillColor(selectorFontColor);
  nText.setFont(font);
  nText.setCharacterSize(selectorFontSize);
  nText.setPosition(sf::Vector2f(60, 408));
  nText.setFillColor(selectorFontColor);

  selectTextDir.setFont(font);	
  selectTextDir.setCharacterSize(selectFontSize);
  selectTextDir.setFillColor(dirFontColor);
  listDirsIndex=0;
  listDirsIndex2=0;
  listFilesIndex2=0;
  buttonMouse=0;
  flagSelectorCurseur=0;
  selectorCurseur.setSize(sf::Vector2f(2,12));
  selectorCurseur.setFillColor(sf::Color(0,0,0,255));
  selectorCurseur.setPosition(56,412);
  std::cout << "width fileSelector"<<winSelectorWidth << std::endl;
}

string selectFile::selector(){							

  winSelector.create(sf::VideoMode(winSelectorWidth, winSelectorHeight), titreSelector, sf::Style::Titlebar|sf::Style::Close);
  listDirs(getcwd(NULL,0));
  readFiles();
  while (winSelector.isOpen()) {                                       // Événements
        sf::Event event;
        while (winSelector.pollEvent(event)){                         // Gestion des évènements de la fenêtre principale
    	       switch (event.type){
		       case sf::Event::Closed:                        // Fermeture de la fenêtre
			        onClose();
				     winSelector.close();
					  break;
             case sf::Event::TextEntered:
           			newText(event);
			         break;
             case sf::Event::MouseButtonPressed:
			  	      onClick(event);
                	break;
             case sf::Event::MouseWheelScrolled:
			 			onMouseWheel(event);
                	break;
             case sf::Event::MouseButtonReleased:
           			onMouseUp(event);
                	break;
             case sf::Event::MouseMoved:
			         onMouseMove(event);
                	break;
        				  					
		       default:                                      // on ne traite pas les autres types d'évènements
             break;
  	       	}            
        
        }
        // Clear screen
	winSelector.setActive(true);
	winSelector.pushGLStates();
   winSelector.clear(selectorBkgColor);

	winSelector.draw(selectBarH);
	winSelector.draw(selectDefPath);
   winSelector.draw(selectBarB);
	winSelector.draw(selectFileS);
	
	winSelector.draw(dossierPath);
	winSelector.draw(selectNew);
	
   winSelector.draw(selectAnnuler);
	winSelector.draw(selectValider);
	winSelector.draw(nText);
	winSelector.draw(selectShap);
	winSelector.draw(selectBkgSlider);
	winSelector.draw(lineBloc);
	winSelector.draw(lineBloch);
	winSelector.draw(selectBkgSlider2);
	winSelector.draw(lineBloc2);
	winSelector.draw(lineBloch2);
	winSelector.draw(selectMSlider);
	winSelector.draw(selectMSlider2);

	drawDirs2();
	drawFiles();
   if(flagSelectorCurseur==1){
		if(clockCurseur.getElapsedTime()>sf::seconds(0.8f)){
			winSelector.draw(selectorCurseur);
			if(clockCurseur.getElapsedTime()>sf::seconds(1.6f)){
				clockCurseur.restart();
			}
		}
	}     
	
   winSelector.display();
	winSelector.popGLStates();
	winSelector.setActive(false);
    }
  return rtf;
}
void selectFile::onClose(){
  if(nText.getString()!=""){
  	rtf=nText.getString();
  }else{
   rtf="";
  }
}

void selectFile::onMouseWheel(sf::Event e){
	int nposy;
	int dt;
	if (e.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel && e.mouseWheelScroll.x>8 && e.mouseWheelScroll.x<142 && e.mouseWheelScroll.y>40 && e.mouseWheelScroll.y< 400){
		 if(e.mouseWheelScroll.delta==1){
		 	nposy=selectMSlider.getPosition().y-1;
		 	if(nposy<selectBkgSlider.getPosition().y+2){
		 		nposy=selectBkgSlider.getPosition().y+2;
		 		listDirsIndex2=listDirsIndex2=0;
		 	}else{
		 		listDirsIndex2=listDirsIndex2-1;
		 		selectMSlider.setPosition(sf::Vector2f(selectMSlider.getPosition().x,nposy));
		 	}
		 }else{
		 	nposy=selectMSlider.getPosition().y+1;
		 	if(nposy+selectMSlider.getSize().y>selectBkgSlider.getPosition().y+selectBkgSlider.getSize().y){
		 	   nposy=selectBkgSlider.getPosition().y+selectBkgSlider.getSize().y;
		 	}else{
		 		selectMSlider.setPosition(sf::Vector2f(selectMSlider.getPosition().x,nposy));
		 		listDirsIndex2=listDirsIndex2+1;
		 	}
		 }
	}
	if (e.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel && e.mouseWheelScroll.x>204 && e.mouseWheelScroll.x<500 && e.mouseWheelScroll.y>40 && e.mouseWheelScroll.y<400){
		 if(e.mouseWheelScroll.delta==1){
		 	nposy=selectMSlider2.getPosition().y-1;
		 	if(nposy<selectBkgSlider2.getPosition().y+2){
		 		nposy=selectBkgSlider2.getPosition().y+2;
		 		listFilesIndex2=listFilesIndex2=0;
		 	}else{
		 		listFilesIndex2=listFilesIndex2-1;
		 		selectMSlider2.setPosition(sf::Vector2f(selectMSlider2.getPosition().x,nposy));
		 	}
		 }else{
		 	nposy=selectMSlider2.getPosition().y+1;
		 	if(nposy+selectMSlider2.getSize().y>selectBkgSlider2.getPosition().y+selectBkgSlider2.getSize().y){
		 	   nposy=selectBkgSlider2.getPosition().y+selectBkgSlider2.getSize().y;
		 	}else{
		 		selectMSlider2.setPosition(sf::Vector2f(selectMSlider2.getPosition().x,nposy));
		 		listFilesIndex2=listFilesIndex2+1;
		 	}
		 }
	}
	
}
void selectFile::onMouseMove(sf::Event e){
   std::cout << "mouse x: " << e.mouseMove.x << std::endl;
   std::cout << "mouse y: " << e.mouseMove.y << std::endl;
   if(e.mouseMove.x>0 && e.mouseMove.x<180 && e.mouseMove.y>36 && e.mouseMove.y<380){
   int cy=(((e.mouseMove.y-40)/18)*18)+40;
   selectShap.setSize(sf::Vector2f(172, 18));
   selectShap.setPosition(sf::Vector2f(4, cy));
   }
   if(e.mouseMove.x>200 && e.mouseMove.x<winSelectorWidth && e.mouseMove.y>36 && e.mouseMove.y<380){
   int cy=(((e.mouseMove.y-40)/18)*18)+40;
   selectShap.setSize(sf::Vector2f(272, 18));
   selectShap.setPosition(sf::Vector2f(204, cy));
   }
   if(buttonMouse==1 && e.mouseMove.x>selectMSlider.getPosition().x && e.mouseMove.x<selectMSlider.getPosition().x+14 && e.mouseMove.y>selectMSlider.getPosition().y && e.mouseMove.y<selectMSlider.getPosition().y+selectMSlider.getSize().y){
     int nposy=selectMSlider.getPosition().y+(e.mouseMove.y-lastPos1);
     if(nposy<selectBkgSlider.getPosition().y+2){
   		nposy=selectBkgSlider.getPosition().y+2;
     }
     if(nposy+selectMSlider.getSize().y>34+selectBkgSlider.getSize().y){
   		nposy=selectBkgSlider.getSize().y-selectMSlider.getSize().y+34;
     }
     selectMSlider.setPosition(selectMSlider.getPosition().x,nposy);
     listDirsIndex2=(int)nposy-38;
     drawDirs2();
     lastPos1=e.mouseMove.y;   
   }
   if(buttonMouse==1 && e.mouseMove.x>selectMSlider2.getPosition().x && e.mouseMove.x<selectMSlider2.getPosition().x+14 && e.mouseMove.y>selectMSlider2.getPosition().y && e.mouseMove.y<selectMSlider2.getPosition().y+selectMSlider2.getSize().y){
     int nposy=selectMSlider2.getPosition().y+(e.mouseMove.y-lastPos2);
     if(nposy<selectBkgSlider2.getPosition().y+2){
   		nposy=selectBkgSlider2.getPosition().y+2;
     }
     if(nposy+selectMSlider2.getSize().y>34+selectBkgSlider2.getSize().y){
   		nposy=selectBkgSlider2.getSize().y-selectMSlider2.getSize().y+34;
     }
     selectMSlider2.setPosition(selectMSlider2.getPosition().x,nposy);
     listFilesIndex2=(int)nposy-38;
     drawFiles();
     lastPos2=e.mouseMove.y;   
   }
}
void selectFile::onClick(sf::Event e){
   stringstream adr;
   if (e.mouseButton.button == sf::Mouse::Left){
      std::cout << "the left button was pressed" << std::endl;
      std::cout << "mouse x: " << e.mouseButton.x << std::endl;
      std::cout << "mouse y: " << e.mouseButton.y << std::endl;
   }
   if(e.mouseButton.x>0 && e.mouseButton.x<178 && e.mouseButton.y>36 && e.mouseButton.y<380){
     int id=((e.mouseButton.y-40)/18)+listDirsIndex2;
     if(id<vecDirs.size()){
     	selectType=0;
     	adr << std::fixed <<getcwd(NULL,0) <<"/"<<vecDirs[id];
    	dossierPath.setString(adr.str());
    	listDirs(adr.str());
     	readFiles();
     	std::cout << "index dir: " <<vecDirs[id]<< "path :"<<adr.str()<<"listDirIndex "<<listDirsIndex2 << std::endl;
    	adr.clear();
    	adr.str("");
     }
   }
   if(e.mouseButton.x>200 && e.mouseButton.x<winSelectorWidth && e.mouseButton.y>36 && e.mouseButton.y<400){
     int id=((e.mouseButton.y-40)/18)+listFilesIndex2;
     if(id<vecFs.size()){
     	nText.setString(vecFs[id]);
    	rtf=vecFs[id];
     	newSelect=vecFs[id];
     	selectType=1;
     }else{
	nText.setString("");
	rtf="";
	newSelect="";
     }
   }
   if(e.mouseButton.x>362 && e.mouseButton.x<418 && e.mouseButton.y>406 && e.mouseButton.y<432){
     rtf="";
     winSelector.close();
   }
   if(e.mouseButton.x>422 && e.mouseButton.x<470 && e.mouseButton.y>406 && e.mouseButton.y<432){
   	if(nText.getString()!=""){
   		rtf=nText.getString();
   	}
      winSelector.close();
   }
   if(e.mouseButton.x>50 && e.mouseButton.x<348 && e.mouseButton.y>408 && e.mouseButton.y<432){
     flagSelectorCurseur=1;
  	  selectorCurseur.setPosition(56,412);
   }
   if(e.mouseButton.x>10 && e.mouseButton.x<34 && e.mouseButton.y>406 && e.mouseButton.y<430){
     createDir(txt);
   }
   if(e.mouseButton.x>selectMSlider.getPosition().x && e.mouseButton.x<selectMSlider.getPosition().x+14 && e.mouseButton.y>selectMSlider.getPosition().y && e.mouseButton.y<selectMSlider.getPosition().y+selectMSlider.getSize().y){
     buttonMouse=1;
     lastPos1=e.mouseButton.y;
   }
   if(e.mouseButton.x>selectMSlider2.getPosition().x && e.mouseButton.x<selectMSlider2.getPosition().x+14 && e.mouseButton.y>selectMSlider2.getPosition().y && e.mouseButton.y<selectMSlider2.getPosition().y+selectMSlider2.getSize().y){
     buttonMouse=1;
     lastPos2=e.mouseButton.y;
   }
}
void selectFile::onMouseUp(sf::Event e){
	buttonMouse=0;
}

void selectFile::newText(sf::Event e){
	int key=e.key.code;
	int rtn=0;
	int ph;
	if (e.text.unicode < 128){
		switch (key){
	     case 8:
	       	txt=txt.substr(0,txt.length()-1);
	       	nText.setString(txt);
	       	ph=nText.getLocalBounds().width+62;
				selectorCurseur.setPosition(ph,411);
	 			break;
	     default:
				txt=txt+static_cast<char>(e.text.unicode);
				nText.setString(txt);
				ph=nText.getLocalBounds().width+62;
				selectorCurseur.setPosition(ph,411);
				break;
		}
	}
}

int selectFile::createDir(string dir){
  int rt=0;
	if(dir.size()>0){
    if(boost::filesystem::create_directory(dir)) {
      std::cout << "Success" << "\n";
      int rd=listDirs(".");
    }else{
		rt=1;
		newInfo.setTxt(0,"Attention");
      newInfo.setTxtPosY(0, 30);
      newInfo.setTxt(1,L"Le dossier n'a pas pu être créé.");
      newInfo.setTxtPosY(1, 60);
      bool rt=newInfo.drawInfo(0, "Alerte");
    }
	}
	nText.setString("");
	txt="";
	return rt;
}

int selectFile::listDirs(string cdir){
  char * cstr = new char [cdir.length()+1];
  std::strcpy (cstr, cdir.c_str());
  int ncwd=chdir(cstr);
  listDirsIndex2=0;
  listFilesIndex2=0;
  nText.setString("");
  vecDirs.clear();
  DIR * rep = opendir(getcwd(NULL,0));
  if (rep != NULL){
     struct dirent * ent;
     string dname;
     while ((ent = readdir(rep)) != NULL){
         dname=ent->d_name;
         if(boost::filesystem::is_directory(dname) && dname!="."){
           vecDirs.push_back (dname);
         }
     }
  }
  std::sort (vecDirs.begin(), vecDirs.end());
  closedir(rep);
  if(vecDirs.size()<20){
   	selectMSlider.setSize(sf::Vector2f(14, 360));
  }else{
   	int nbs=360-(vecDirs.size()-19);
   	selectMSlider.setSize(sf::Vector2f(14, nbs));
  }
  selectMSlider.setPosition(selectMSlider.getPosition().x,selectBkgSlider.getPosition().y+2);
  drawDirs2();
  return 0;
}

void selectFile::drawDirs2(){
    int maxf;
    string vs;
    sf::String vs2;
    int bf=listDirsIndex2;
    
    if(bf+19>vecDirs.size()){
		maxf=vecDirs.size();
    }else{
		maxf=bf+19;
    }
    
    int j=0;
    int i=bf;
    dossierPath.setString(getcwd(NULL,0));
    while(i<maxf){
      vs=vecDirs[i].substr(0,20);
    	if(vs.length()<vecDirs[i].size()){
    	  vs=vs+"...";
    	}
   vs2 = sf::String::fromUtf8(vs.begin(), vs.end());
	selectTextDir.setString(vs2);
	selectTextDir.setPosition(sf::Vector2f(8, 40+(j*18)));
	selectTextDir.setFillColor(dirFontColor);
	winSelector.draw(selectTextDir);
	j++;
	i++;
   }
}

int selectFile::readFiles(){
    DIR * rep = opendir(getcwd(NULL,0));
    vecFs.clear();
    int i=0;
    if (rep != NULL){
        struct dirent * ent;
        string vname;
        while ((ent = readdir(rep)) != NULL){
          vname=ent->d_name;
          if(boost::filesystem::is_regular_file(vname) && vname.substr(vname.length()-1,1)!="~" ){
            vecFs.push_back (vname);
            i++;
          }
        }
     std::sort (vecFs.begin(), vecFs.end());
     closedir(rep);
    }
    if(vecFs.size()<20){
   	selectMSlider2.setSize(sf::Vector2f(14, 360));
    }else{
   	int nbs=360-(vecFs.size()-19);
   	selectMSlider2.setSize(sf::Vector2f(14, nbs));
    }
    selectMSlider2.setPosition(selectMSlider2.getPosition().x,selectBkgSlider2.getPosition().y+2);  
    return 0;
}
void selectFile::drawFiles(){
	int maxf=19;
	string vs;
	sf::String vs2;
	int bf=listFilesIndex2;
	if(bf+19>vecFs.size()){
	  maxf=vecFs.size();
	}else{
	maxf=bf+19;
	}
	int j=0;
	int i=bf;
	while(i<maxf){
		vs=vecFs[i].substr(0,30);
		vs2 = sf::String::fromUtf8(vs.begin(), vs.end());
		selectTextDir.setString(vs2);
	   selectTextDir.setPosition(sf::Vector2f(234, 40+(j*18)));
		selectTextDir.setFillColor(fileFontColor);
		if(vecFs[i].length()>5){
			string extension=vecFs[i].substr(vecFs[i].length()-4,4);
			string extension2=vecFs[i].substr(vecFs[i].length()-5,5);
			if(extension2==".flac" || extension2==".aiff" || extension==".wav" || extension==".ogg"){
			  speaker.setPosition(sf::Vector2f(210, 40+(j*18)));
			  winSelector.draw(speaker);
			}
		}
		winSelector.draw(selectTextDir);
		j++;
		i++;
	}
}
string selectFile::getPath(){
	return dossierPath.getString();
}
