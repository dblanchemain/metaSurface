/* MetaSurface  .
 *
 * This is the main function for the MetaSurface.
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
#include <iomanip>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>

#include <ctgmath>
#include <string>
#include <cstring>
#include <boost/filesystem.hpp>
#include <vector>
#include <thread>

#include <lo/lo.h>
#include <lo/lo_cpp.h>

#include "faust/audio/jack-dsp.h"
#include "faust/dsp/llvm-dsp.h"
#include "faust/dsp/interpreter-dsp.h"
#include "faust/dsp/dsp-adapter.h"
#include "faust/dsp/proxy-dsp.h"
#include "faust/dsp/poly-dsp.h"
#include "faust/gui/meta.h"
#include "faust/gui/FUI.h"
#include "faust/gui/GTKUI.h"
#include "faust/gui/MidiUI.h"
#include "faust/gui/OSCUI.h"
#include "faust/gui/OSCControler.h"
#include "faust/gui/SoundUI.h"
#include "faust/misc.h"

#include "metaSurface.h"
#include "configuration.h"
#include "selectFile.h"
#include "parametres.h"
#include "info.h"
#include "menu.h"
#include "surfaceSelect.h"
#include "pave.h"
#include "omni.h"
#include "plugin.h"
#include "contraintesFx.h"
#include "apropos.h"

using namespace std;

list<GUI*> GUI::fGuiList;
ztimedmap GUI::gTimedZoneMap;

metaSurface::metaSurface(Configuration *def){
ref=def;
string Theme=def->getFichierTheme();
userConfig=def->getDossierUser();
ifstream fichier(def->getFichierTheme(), ios::in); 
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
         s2=stoi(pf[1]);
       }
       if(pf[0]=="workspaceSurfaceLeft"){
          workspaceSurface.setPosition(stoi(pf[1]),s2);
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
       if(pf[0]=="menu1BkgColor"){
         defMenu.setMenu1BkgColor(sf::Color(std::stoul(pf[1],nullptr,16)));
       }
       if(pf[0]=="bkgWindowColor"){
         //bkgWindowColor=sf::Color(std::stoul(pf[1],nullptr,16));
       }
       if(pf[0]=="menu1bBkgColor"){
         defMenu.setMenu1bBkgColor(sf::Color(std::stoul(pf[1],nullptr,16)));
       }
       if(pf[0]=="itemShapBkgColor"){
         defMenu.setItemShapBkgColor(sf::Color(std::stoul(pf[1],nullptr,16)));
       }
       if(pf[0]=="itemFontColor"){
         defMenu.setItemFontColor(sf::Color(std::stoul(pf[1],nullptr,16)));
       }
       if(pf[0]=="itemShapFontColor"){
         defMenu.setItemShapFontColor(sf::Color(std::stoul(pf[1],nullptr,16)));
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
       /*
       if(pf[0]=="dialogFontColor"){
         newDialog.setFontColor(sf::Color(std::stoul(pf[1],nullptr,16)));
       }
       if(pf[0]=="dialogFontSize"){
         newDialog.setFontSize(stoi(pf[1]));
       }
       
       if(pf[0]=="paramOngSelectColor"){
         paramOngSelectColor=sf::Color(std::stoul(pf[1],nullptr,16));
       }
       if(pf[0]=="paramOngColor"){
         paramOngColor=sf::Color(std::stoul(pf[1],nullptr,16));
       }
       if(pf[0]=="paramFontColorOng"){
         paramFontColorOng=sf::Color(std::stoul(pf[1],nullptr,16));
       }
       if(pf[0]=="paramFontSizeOng"){
         paramFontSizeOng=stoi(pf[1]);
       }
       
       if(pf[0]=="infoTxtSize"){
         newInfo.setInfoTxtSize(stoi(pf[1]));
       }
       if(pf[0]=="infoTxtFillColor"){
         newInfo.setInfoTxtFillColor(sf::Color(std::stoul(pf[1],nullptr,16)));
       }
       */
      
     }
     fichier.close();	
  }else{  // sinon
       cerr << "Erreur à l'ouverture init surface Theme!" << endl;
  }
  selectPad=0;
  padActif=0;
  surfaceMode=0;
  flagSurfaceCurseur=0;
  flagPaveCurseur=0;
  exploseMax=10;
  omniSelectFlag=0;
  typeMove=0;
  fx=0;
  shapFxEdit=0;
  fxcanal=0;
  rtfx=0;
  ctrlFX=1;
  ctrlOsc=1; // 0 osc Plugin 1 Ardour 2 Reaper
  indexList=0;
  modeDsp=0;
  newInfo.setInfo(def->getFichierTheme(),def->getAppGui());
  newApropos.setApropos(def->getDossierConfig(),def->getFichierTheme(),def->getAppGui(),def->getDiversLang());
  newPlugin.setPlugin(def->getFichierTheme(),def->getAppGui(),userConfig, ref->getEditeur(),ref->getNavigateur());
  fileSelector.setSelectorGui(def->getAppGui());
  fileSelector.setSelectorTheme(def->getFichierTheme());
  fileSelector.setTitreSelector("File selector");
  fileSelector.setSelectorLang(def->getDiversLang());
  
  stringstream adr;
  adr << std::fixed << def->getAppGui()<<"/"<<"Arial.ttf";
  font.loadFromFile(adr.str());
  adr.clear();
  adr.str("");
 
  //appShapWindow();
  
  defMenu.setGui(def->getAppGui());
  adr << std::fixed << def->getDossierConfig() <<"/Lang/" << "menu.fr";
  defMenu.setFichierMenu(adr.str());
  defMenu.initMenu();
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
  
  surfaceCurseur.setSize(sf::Vector2f(2,12));
  surfaceCurseur.setFillColor(sf::Color(0,0,0,255));
  surfaceCurseur.setPosition(132,98);
  winPaveCurseur.setSize(sf::Vector2f(2,12));
  winPaveCurseur.setFillColor(sf::Color(0,0,0,255));
  winPaveCurseur.setPosition(132,98);
  
  surface.create(sf::VideoMode(920,754), "Surface");
  
  depNavSurface=0;
  slideMB=0;
  slideMD=0; 
  nscale=1;
  
  tempoTMin.setFont(font);
  tempoTMin.setCharacterSize(13);
  tempoTMin.setFillColor(sf::Color(0, 0, 0));
  tempoTMin.setString("5");
  tempoTMin.setPosition(84-tempoTMin.getLocalBounds().width-6,410);
  tempoTMax.setFont(font);
  tempoTMax.setCharacterSize(13);
  tempoTMax.setFillColor(sf::Color(0, 0, 0));
  tempoTMax.setString("20");
  tempoTMax.setPosition(134-tempoTMax.getLocalBounds().width-6,410);
  temporisationMin=5;
  temporisationMax=20;
  exploseTMax.setFont(font);
  exploseTMax.setCharacterSize(13);
  exploseTMax.setFillColor(sf::Color(0, 0, 0));
  exploseTMax.setString("10");
  exploseTMax.setPosition(136-exploseTMax.getLocalBounds().width-6,96);
  exploseMax=10;
  dureevieTMin.setFont(font);
  dureevieTMin.setCharacterSize(13);
  dureevieTMin.setFillColor(sf::Color(0, 0, 0));
  dureevieTMin.setString("10000");
  dureevieTMin.setPosition(90-dureevieTMin.getLocalBounds().width-4,352);
  dureevieTMax.setFont(font);
  dureevieTMax.setCharacterSize(13);
  dureevieTMax.setFillColor(sf::Color(0, 0, 0));
  dureevieTMax.setString("300000");
  dureevieTMax.setPosition(164-dureevieTMax.getLocalBounds().width-4,352);
  vieMin=10000;
  vieMax=300000;
  
  omniSurface=0;
  omniRamdom=1;
  
  
  adr << std::fixed << def->getAppGui()<<"/g7002.png";
  curType[0].loadFromFile(adr.str());
  curType[0].setSmooth(true);
  adr.clear();
  adr.str("");
  adr << std::fixed << def->getAppGui()<<"/g4813.png";
  curType[1].loadFromFile(adr.str());
  curType[0].setSmooth(true);
  adr.clear();
  adr.str("");
  adr << std::fixed << def->getAppGui()<<"/g7012.png";
  curType[2].loadFromFile(adr.str());
  curType[0].setSmooth(true);
  adr.clear();
  adr.str("");
  adr << std::fixed << def->getAppGui()<<"/g7022.png";
  curType[3].loadFromFile(adr.str());
  curType[0].setSmooth(true);
  adr.clear();
  adr.str("");
  adr << std::fixed << def->getAppGui()<<"/g7010.png";
  curType[4].loadFromFile(adr.str());
  curType[0].setSmooth(true);
  adr.clear();
  adr.str("");
  adr << std::fixed << def->getAppGui()<<"/g7004.png";
  curType[5].loadFromFile(adr.str());
  curType[0].setSmooth(true);
  adr.clear();
  adr.str("");
  adr << std::fixed << def->getAppGui()<<"/g7017.png";
  curType[6].loadFromFile(adr.str());
  curType[0].setSmooth(true);
  adr.clear();
  adr.str("");
  adr << std::fixed << def->getAppGui()<<"/g7016.png";
  curType[7].loadFromFile(adr.str());
  curType[0].setSmooth(true);
  adr.clear();
  adr.str("");
  adr << std::fixed << def->getAppGui()<<"/g4794.png";
  curType[8].loadFromFile(adr.str());
  curType[0].setSmooth(true);
  adr.clear();
  adr.str("");
  adr << std::fixed << def->getAppGui()<<"/g7013.png";
  curType[9].loadFromFile(adr.str());
  curType[0].setSmooth(true);
  adr.clear();
  adr.str("");
  adr << std::fixed << def->getAppGui()<<"/g4894c.png";
  curType[10].loadFromFile(adr.str());
  curType[0].setSmooth(true);
  adr.clear();
  adr.str("");
  adr << std::fixed << def->getAppGui()<<"/g7009.png";
  curType[11].loadFromFile(adr.str());
  curType[0].setSmooth(true);
  adr.clear();
  adr.str("");
  adr << std::fixed << def->getAppGui()<<"/g7006.png";
  curType[12].loadFromFile(adr.str());
  curType[0].setSmooth(true);
  adr.clear();
  adr.str("");
  adr << std::fixed << def->getAppGui()<<"/g7019.png";
  curType[13].loadFromFile(adr.str());
  curType[0].setSmooth(true);
  adr.clear();
  adr.str("");
  adr << std::fixed << def->getAppGui()<<"/g7018.png";
  curType[14].loadFromFile(adr.str());
  curType[0].setSmooth(true);
  adr.clear();
  adr.str("");
  adr << std::fixed << def->getAppGui()<<"/g7014.png";
  curType[15].loadFromFile(adr.str());
  curType[0].setSmooth(true);
  adr.clear();
  adr.str("");
  adr << std::fixed << def->getAppGui()<<"/g6928.png";
  curType[16].loadFromFile(adr.str());
  curType[0].setSmooth(true);
  adr.clear();
  adr.str("");
  adr << std::fixed << def->getAppGui()<<"/g7003.png";
  curType[17].loadFromFile(adr.str());
  curType[0].setSmooth(true);
  adr.clear();
  adr.str("");
  adr << std::fixed << def->getAppGui()<<"/g5074.png";
  curType[18].loadFromFile(adr.str());
  curType[0].setSmooth(true);
  adr.clear();
  adr.str("");
  adr << std::fixed << def->getAppGui()<<"/g7011.png";
  curType[19].loadFromFile(adr.str());
  curType[0].setSmooth(true);
  adr.clear();
  adr.str("");
  adr << std::fixed << def->getAppGui()<<"/g7007.png";
  curType[20].loadFromFile(adr.str());
  curType[0].setSmooth(true);
  adr.clear();
  adr.str("");
  adr << std::fixed << def->getAppGui()<<"/g7023.png";
  curType[21].loadFromFile(adr.str());
  curType[0].setSmooth(true);
  adr.clear();
  adr.str("");
  adr << std::fixed << def->getAppGui()<<"/g7021.png";
  curType[22].loadFromFile(adr.str());
  curType[0].setSmooth(true);
  adr.clear();
  adr.str("");
  adr << std::fixed << def->getAppGui()<<"/g5074.png";
  curType[23].loadFromFile(adr.str());
  curType[0].setSmooth(true);
  adr.clear();
  adr.str("");
  adr << std::fixed << def->getAppGui()<<"/g7005.png";
  curType[24].loadFromFile(adr.str());
  curType[0].setSmooth(true);
  adr.clear();
  adr.str("");
  adr << std::fixed << def->getAppGui()<<"/g5100.png";
  curType[25].loadFromFile(adr.str());
  curType[0].setSmooth(true);
  adr.clear();
  adr.str("");
  adr << std::fixed << def->getAppGui()<<"/g4906.png";
  curType[26].loadFromFile(adr.str());
  curType[0].setSmooth(true);
  adr.clear();
  adr.str("");
  adr << std::fixed << def->getAppGui()<<"/g7001.png";
  curType[27].loadFromFile(adr.str());
  curType[0].setSmooth(true);
  adr.clear();
  adr.str("");
  adr << std::fixed << def->getAppGui()<<"/g7000.png";
  curType[28].loadFromFile(adr.str());
  curType[0].setSmooth(true);
  adr.clear();
  adr.str("");
  adr << std::fixed << def->getAppGui()<<"/g7020.png";
  curType[29].loadFromFile(adr.str());
  curType[0].setSmooth(true);
  adr.clear();
  adr.str("");
  adr << std::fixed << def->getAppGui()<<"/g4971.png";
  curType[30].loadFromFile(adr.str());
  curType[0].setSmooth(true);
  adr.clear();
  adr.str("");
  adr << std::fixed << def->getAppGui()<<"/g7024.png";
  curType[31].loadFromFile(adr.str());
  curType[0].setSmooth(true);
  adr.clear();
  adr.str("");
  
  
  adr << std::fixed << def->getAppGui()<<"/objetColor.png";
  selectCurT.loadFromFile(adr.str());
  selectCurType.setTexture(selectCurT);
  selectCurType.setPosition(0,0);
  adr.clear();
  adr.str("");
  
  adr << std::fixed << def->getAppGui()<<"/anneau1.png";
  selectAn.loadFromFile(adr.str());
  adr.clear();
  adr.str("");
  
  adr << std::fixed << def->getAppGui()<<"/surfaceMenu.png";
  std::cout << "gui: " << adr.str()<<std::endl;
  selectAnB.loadFromFile(adr.str());
  palette.setTexture(selectAnB);
  palette.setPosition(0,30);
  adr.clear();
  adr.str("");
  
  adr << std::fixed << def->getAppGui()<<"/fsliderb.png";
  selectAnSlb.loadFromFile(adr.str());
  boutonSl1b.setTexture(selectAnSlb);
  boutonSl1b.setPosition(57,326);
  boutonSl2b.setTexture(selectAnSlb);
  boutonSl2b.setPosition(127,152);
  adr.clear();
  adr.str("");
  
  
  adr << std::fixed << def->getAppGui()<<"/fondPave.png";
  selectFp.loadFromFile(adr.str());
  bkgWinPave.setTexture(selectFp);
  adr.clear();
  adr.str("");
  adr << std::fixed << def->getAppGui()<<"/bNoSelect.png";
  bNoSelect.loadFromFile(adr.str());
  fxSelect.setTexture(bNoSelect);
  fxSelect.setPosition(260,168);
  defSelectDaw.setTexture(bNoSelect);
  defSelectDaw.setPosition(114,66);
  adr.clear();
  adr.str("");
  adr << std::fixed << def->getAppGui()<<"/bselect.png";
  bselect.loadFromFile(adr.str());
  adr.clear();
  adr.str("");
  defSelectGain.setTexture(bselect);
  defSelectGain.setPosition(114,172);
  
  defMulti.setTexture(bNoSelect);
  defMulti.setPosition(114,99);
  
  bOmniSurface.setPosition(77,543);
  bOmniSurface.setTexture(bNoSelect);
  bOmniRamdom.setPosition(155,543);
  bOmniRamdom.setTexture(bselect);
  
  adr << std::fixed << def->getAppGui()<<"/fondFx.png";
  selectF1.loadFromFile(adr.str());
  adr.clear();
  adr.str("");
  fondFx.setTexture(selectF1);
  fondFx.setPosition(sf::Vector2f(0, 0));
  labelFile.setString(def->getLabelFile());
  labelFile.setFont(font);
  labelFile.setCharacterSize(13);
  labelFile.setFillColor(sf::Color(0, 0, 0));
  labelFile.setPosition(8,18);
  labelDaw.setString(def->getLabelDaw());
  labelDaw.setFont(font);
  labelDaw.setCharacterSize(13);
  labelDaw.setFillColor(sf::Color(0, 0, 0));
  labelDaw.setPosition(8,65);
  labelRi.setString(def->getLabelRi());
  labelRi.setFont(font);
  labelRi.setCharacterSize(13);
  labelRi.setFillColor(sf::Color(0, 0, 0));
  labelRi.setPosition(8,100);
  labelMulti.setString("Multi");
  labelMulti.setFont(font);
  labelMulti.setCharacterSize(13);
  labelMulti.setFillColor(sf::Color(0, 0, 0));
  labelMulti.setPosition(8,100);
  labelMixerGain.setString(def->getLabelMixerGain());
  labelMixerGain.setFont(font);
  labelMixerGain.setCharacterSize(13);
  labelMixerGain.setFillColor(sf::Color(0, 0, 0));
  labelMixerGain.setPosition(8,170);
  labelDimMixer.setString(def->getLabelDimMixer());
  labelDimMixer.setFont(font);
  labelDimMixer.setCharacterSize(13);
  labelDimMixer.setFillColor(sf::Color(0, 0, 0));
  labelDimMixer.setPosition(8,135);
  labelGainMin.setString(def->getLabelGainMin());
  labelGainMin.setFont(font);
  labelGainMin.setCharacterSize(13);
  labelGainMin.setFillColor(sf::Color(0, 0, 0));
  labelGainMin.setPosition(8,205);
  labelGainMax.setString(def->getLabelGainMax());
  labelGainMax.setFont(font);
  labelGainMax.setCharacterSize(13);
  labelGainMax.setFillColor(sf::Color(0, 0, 0));
  labelGainMax.setPosition(8,240);
  labelCanaux.setString(def->getLabelCanaux());
  labelCanaux.setFont(font);
  labelCanaux.setCharacterSize(13);
  labelCanaux.setFillColor(sf::Color(0, 0, 0));
  labelCanaux.setPosition(192,65);
  labelDuree.setString(def->getLabelDuree());
  labelDuree.setFont(font);
  labelDuree.setCharacterSize(13);
  labelDuree.setFillColor(sf::Color(0, 0, 0));
  labelDuree.setPosition(192,100);
  labelTrack.setString("Track");
  labelTrack.setFont(font);
  labelTrack.setCharacterSize(13);
  labelTrack.setFillColor(sf::Color(0, 0, 0));
  labelTrack.setPosition(192,135);
  labeldFx.setString("FX");
  labeldFx.setFont(font);
  labeldFx.setCharacterSize(13);
  labeldFx.setFillColor(sf::Color(0, 0, 0));
  labeldFx.setPosition(192,168);
  labelType.setString("Type");
  labelType.setFont(font);
  labelType.setCharacterSize(13);
  labelType.setFillColor(sf::Color(0, 0, 0));
  labelType.setPosition(192,242);
  
  paramFile.setFont(font);
  paramFile.setCharacterSize(13);
  paramFile.setFillColor(sf::Color(0, 0, 0));
  paramDaw.setFont(font);
  paramDaw.setCharacterSize(13);
  paramDaw.setFillColor(sf::Color(0, 0, 0));
  paramRi.setFont(font);
  paramRi.setCharacterSize(13);
  paramRi.setFillColor(sf::Color(0, 0, 0));

  paramDimMixer.setFont(font);
  paramDimMixer.setCharacterSize(13);
  paramDimMixer.setFillColor(sf::Color(0, 0, 0));
  paramGainMin.setFont(font);
  paramGainMin.setCharacterSize(13);
  paramGainMin.setFillColor(sf::Color(0, 0, 0));
  paramGainMax.setFont(font);
  paramGainMax.setCharacterSize(13);
  paramGainMax.setFillColor(sf::Color(0, 0, 0));
  paramCanaux.setFont(font);
  paramCanaux.setCharacterSize(13);
  paramCanaux.setFillColor(sf::Color(0, 0, 0));
  paramDuree.setFont(font);
  paramDuree.setCharacterSize(13);
  paramDuree.setFillColor(sf::Color(0, 0, 0));
  paramTrack.setFont(font);
  paramTrack.setCharacterSize(13);
  paramTrack.setFillColor(sf::Color(0, 0, 0));
  
  shapeFxSel.setSize(sf::Vector2f(142, 300));
  shapeFxSel.setFillColor(sf::Color(19,37,53));
  shapeFxSel.setOutlineThickness(1.f);
  shapeFxSel.setOutlineColor(sf::Color(0, 0, 0));
  selectShapFxSel.setSize(sf::Vector2f(114, 20));
  selectShapFxSel.setFillColor(sf::Color(224,224,224));
  selectShapFxSel.setPosition(sf::Vector2f(38,34));
  shapeFxSlider.setSize(sf::Vector2f(18, 296));
  shapeFxSlider.setFillColor(sf::Color(190,190,190));
  shapeFxSlider.setOutlineThickness(1.f);
  shapeFxSlider.setOutlineColor(sf::Color(255,255,255));
  shapeFxSlider.setPosition(sf::Vector2f(160,34));
  shapeFxMSlider.setSize(sf::Vector2f(16, 30));
  shapeFxMSlider.setFillColor(sf::Color(150,150,150));
  shapeFxMSlider.setOutlineThickness(1.f);
  shapeFxMSlider.setOutlineColor(sf::Color(200,200,200));
  shapeFxMSlider.setPosition(sf::Vector2f(161,34));
  
  fxLabel.setFont(font);
  fxLabel.setCharacterSize(13);
  fxLabel.setFillColor(sf::Color(0,0,0));
  fxLabel.setPosition(sf::Vector2f(80,414));
  fxLabel.setString("Canal");
  fxLabelSp.setFont(font);
  fxLabelSp.setCharacterSize(13);
  fxLabelSp.setFillColor(sf::Color(0,0,0));
  fxLabelSp.setPosition(sf::Vector2f(160,414));
  fxLabelSp.setString("Spectrum");
  fxcanalB.setPosition(sf::Vector2f(128,414));
  fxcanalB.setTexture(bNoSelect);
  fxcanalSpect.setPosition(sf::Vector2f(230,414));
  fxcanalSpect.setTexture(bNoSelect);
  for(int i=0;i<15;i++){
  	labelFx[i].setFont(font);
  	labelFx[i].setCharacterSize(13);
   labelFx[i].setFillColor(sf::Color(255, 255, 255));
  }
  labelFx[0].setString("");
  labelFx[1].setString("Compression");
  labelFx[2].setString("Delay");
  labelFx[3].setString("Distortion");
  labelFx[4].setString("Flanger");
  labelFx[5].setString("Freeverb");
  labelFx[6].setString("Granulator");
  labelFx[7].setString("HPF/LPF");
  labelFx[8].setString("Mixer");
  labelFx[9].setString("Moog_VCF");
  labelFx[10].setString("ParametricEQ");
  labelFx[11].setString("Phaser");
  labelFx[12].setString("RingModulator");
  labelFx[13].setString("Speed");
  labelFx[14].setString("SpectrumAnalyser");
  
  funcFx[0]="";
  funcFx[1]="compressor";
  funcFx[2]="delay";
  funcFx[3]="dm.cubicnl_demo";
  funcFx[4]="flangerMono";
  funcFx[5]="freeverb";
  funcFx[6]="granulator";
  funcFx[7]="filters";
  funcFx[8]="mixer";
  funcFx[9]="moog_vcf";
  funcFx[10]="parametric_eq";
  funcFx[11]="phaserMono";
  funcFx[12]="ringModulator";
  funcFx[13]="Speed";
  funcFx[14]="spectral_level";
  
  
  for(int i=0;i<12;i++){
  	txtFx[i].setFont(font);
  	txtFx[i].setCharacterSize(13);
   txtFx[i].setFillColor(sf::Color(0,0,0));
   txtFx[i].setString("");
   txtFx[i].setPosition(60,14+(i*33.4));
  }
  newPlugin.readListPlugin();
  

}

metaSurface::~metaSurface(){
}


//*************************************************************************************************** 
void metaSurface::drawSurface(){  
  while (surface.isOpen()) {
      sf::Event eventSurface;
      sf::Event eventWinPave;
      sf::Event eventType;
      sf::Event eventWinFx;
      while (surface.pollEvent(eventSurface)){
      	switch (eventSurface.type){
	   		case sf::Event::Closed:
		          {
		           char commandeSf[255];
		           snprintf(commandeSf, 255, "%s", "killall -9 midiPlayer");
		           int pdSf=system(commandeSf);
			        surface.close();
			       }
			       break;
		     case sf::Event::Resized:
         	    onResized(eventSurface);
             	 break;
           case sf::Event::MouseWheelScrolled:
		 			 mouseWheel(eventSurface);
             	 break;
           case sf::Event::KeyPressed:
		          //onKeyPressed2(event2);
					 break;
           case sf::Event::TextEntered:
        			 //newDefText2(event2);
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
     while (winPave.pollEvent(eventWinPave)){ 
    	      switch (eventWinPave.type){
		        case sf::Event::Closed:
		        		bkgSurface.clear(AppBackGround);
	  					bkgSurface.draw(defSurface);
			       	winPave.close();
			     		break;
	       	  case sf::Event::TextEntered:
	     			   newPaveText(eventWinPave);
					   break;
	        	  case sf::Event::MouseButtonPressed:
		  			   onClickWinPave(eventWinPave);
	          	   break;
	        	  case sf::Event::MouseButtonReleased:
	     			   onMouseUpWinPave(eventWinPave);
	          	   break;
	           case sf::Event::MouseMoved:
		            onMouseMoveWinPave(eventWinPave);
	          	   break;
        				  					
		        default: 
                	break;
  	      	 }            
     }
     while (selectType.pollEvent(eventType)){ 
 	      switch (eventType.type){
	        case sf::Event::Closed:
		       	 selectType.close();
		    		 break;
           case sf::Event::MouseButtonPressed:
		  			 onClickType(eventType);
             	 break;
     				  					
	        default: 
             	 break;
  	      }            
     }
     while (winFX.pollEvent(eventWinFx)){ 
    	      switch (eventWinFx.type){
		        case sf::Event::Closed:
			       	winFX.close();
			     		break;
	        	  case sf::Event::MouseButtonPressed:
		  			   onClickWinFx(eventWinFx);
	          	   break;
	        	  case sf::Event::MouseButtonReleased:
	     			   onMouseUpWinFx(eventWinFx);
	          	   break;
	           case sf::Event::MouseMoved:
		            onMouseMoveWinFx(eventWinFx);
	          	   break;
	           case sf::Event::MouseWheelScrolled:
		            mouseFxWheel(eventWinFx);
	          	   break;				
		        default: 
                	break;
  	      	 }            
     }
     
  		surface.setActive(true);
		surface.pushGLStates();
		surface.clear(AppBackGround);

		surface.draw(surfaceSliderDroit);
	   surface.draw(surfaceSliderMDroit);
	   surface.draw(surfaceSliderBas);
	   surface.draw(surfaceSliderMBas);
	   surface.draw(palette);
	   surface.draw(tempoTMin);
      surface.draw(tempoTMax);
      surface.draw(exploseTMax);
      surface.draw(dureevieTMin);
      surface.draw(dureevieTMax);
      surface.draw(bOmniSurface);
      surface.draw(bOmniRamdom);
	   surface.draw(boutonSl1b);
      surface.draw(boutonSl2b);
	   surface.draw(menuBar);
	   
	   
	   
		
		bkgSurface.clear(AppBackGround);
	   bkgSurface.draw(defSurface);
		for(int i=0;i<surfaceTypeDef;i++){
			if(tabPave[i].getCurseurEtat()==1){
				int curt=tabPave[i].getCurseurT(); 
				curs.setTexture(curType[curt]);
   			curs.setPosition(defSurface.getPosition().x+tabPave[i].getCurseurX()*nscale,defSurface.getPosition().y+tabPave[i].getCurseurY()*nscale);
   			curs.setScale(tabPave[i].getDimMixer(),tabPave[i].getDimMixer());
   			bkgSurface.draw(curs);
   			
			}
		}
		
		if(omniRamdom==0){
			for(int i=0;i<exploseMax;i++){
				if(tabOmni[i].getEtat()==1){
					//tabOmni[i].anneau.setPosition(tabOmni[i].anneau.getPosition().x*nscale,tabOmni[i].anneau.getPosition().y*nscale);
					bkgSurface.draw(tabOmni[i].anneau);
				}
			}
		}else{
			for(int i=0;i<exploseMax;i++){
				if(tabOmni[i].getEtat()==1){
					surfaceCollision(i);
				}
			}
			for(int i=0;i<exploseMax;i++){
				if(tabOmni[i].getEtat()==1){
					moveAnneau(i);
					bkgSurface.draw(tabOmni[i].anneau);
				}
			}
		}
		surface.draw(navWorkspaceSurface);
		surface.draw(navSurface);
		workspaceSurface.setTexture(&bkgSurface.getTexture(),false);
		surface.draw(workspaceSurface);
	   if(flagSurfaceCurseur==1){
			if(clockCurseur.getElapsedTime()>sf::seconds(0.8f)){
				surface.draw(surfaceCurseur);
				if(clockCurseur.getElapsedTime()>sf::seconds(1.6f)){
					clockCurseur.restart();
				}
			}
		}
		defMenu.appDrawMenu(&surface);
		surface.display();
		surface.popGLStates();
		surface.setActive(false);
	 
  
	  if(winPave.isOpen()) {
			winPave.setActive(true);
			winPave.pushGLStates();
	   	winPave.clear(AppBackGround);
		   	
		   winPave.draw(bkgWinPave);
			winPave.draw(labelFile);
			winPave.draw(labelDaw);
			winPave.draw(labelMulti);
			winPave.draw(labelDimMixer);
			winPave.draw(labelMixerGain);
			winPave.draw(labelGainMin);
			winPave.draw(labelGainMax);
			winPave.draw(labelCanaux);
			winPave.draw(labelDuree);
			winPave.draw(labelTrack);
			winPave.draw(labeldFx);
			winPave.draw(labelType);
			winPave.draw(fxSelect);
			winPave.draw(defSelectDaw);
			winPave.draw(defMulti);
			winPave.draw(defSelectGain);
			winPave.draw(paramFile);
			winPave.draw(paramDimMixer);
			winPave.draw(paramGainMin);
			winPave.draw(paramGainMax);
			winPave.draw(paramCanaux);
			winPave.draw(paramDuree);
			winPave.draw(paramTrack);
		   	
			int curt=tabPave[selectPad-1].getCurseurT(); 
			curs.setTexture(curType[curt]);
	   	curs.setPosition(256,238);
	   	curs.setScale(tabPave[selectPad-1].getDimMixer(),tabPave[selectPad-1].getDimMixer());
	   	winPave.draw(curs);
	   	
	   	if(flagPaveCurseur==1){
				if(clockCurseur.getElapsedTime()>sf::seconds(0.8f)){
					winPave.draw(winPaveCurseur);
					if(clockCurseur.getElapsedTime()>sf::seconds(1.6f)){
						clockCurseur.restart();
					}
				}
			}
	   	
	   	winPave.display();
			winPave.popGLStates();
			winPave.setActive(false);
	  }
	  if(selectType.isOpen()) {
	  		selectType.setActive(true);
			selectType.pushGLStates();
	   	selectType.clear(AppBackGround);

			selectType.draw(selectCurType);	   	
	   	
	   	selectType.display();
			selectType.popGLStates();
			selectType.setActive(false);
	  	}
	  if(winFX.isOpen()) {
			winFX.setActive(true);
			winFX.pushGLStates();
			winFX.draw(fondFx);
		
			
			if(shapFxEdit==1){
				winFX.draw(shapeFxSel);
				winFX.draw(selectShapFxSel);
				winFX.draw(shapeFxSlider);
				winFX.draw(shapeFxMSlider);
				for(int i=0;i<15;i++){
					labelFx[i].setFillColor(sf::Color(255, 255, 255));
					labelFx[rtfx].setFillColor(sf::Color(0,0,0));
			  		winFX.draw(labelFx[i]);
				}
			}

			if(shapFxEdit==0){
				txtFx[0].setPosition(60,14);
				txtFx[1].setPosition(60,47);
				for(int i=0;i<12;i++){
					  	winFX.draw(txtFx[i]);
				}
		   }
		   winFX.draw(fxLabel);
		   winFX.draw(fxcanalB);
		   winFX.draw(fxLabelSp);
		   winFX.draw(fxcanalSpect);

			winFX.display();
			winFX.popGLStates();
			winFX.setActive(false);
			
	  }
	}
}
void metaSurface::onResized(sf::Event e){
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
void metaSurface::onMouseButtonUpSurface(sf::Event e){
	depNavSurface=0;
	padActif=0;
	slideMB=0;
	slideMD=0;
	mvBoutonSl1b=0;
	mvBoutonSl2b=0;
	omniSelectFlag=0;
}
void metaSurface::onClickSurface(sf::Event e){
   std::cout << "the left button was pressed" << std::endl;
   std::cout << "mouse x: " << e.mouseButton.x << std::endl;
   std::cout << "mouse y: " << e.mouseButton.y << std::endl;
   int v=0; // variable de travail
   float dt=0.0;
   //*********************************************************************************************************************
   //													gestion navigateur
   //*********************************************************************************************************************
   if(e.mouseButton.x>navSurface.getPosition().x && e.mouseButton.x<navSurface.getPosition().x + navSurface.getSize().x && e.mouseButton.y>navSurface.getPosition().y && e.mouseButton.y<navSurface.getPosition().y + navSurface.getSize().y){
   	depNavSurface=1;
   	depNavX=navSurface.getPosition().x-e.mouseButton.x;
   	depNavY=navSurface.getPosition().y-e.mouseButton.y;
   }
   //*********************************************************************************************************************
   //													gestion scrollbar
   //*********************************************************************************************************************
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
   //*********************************************************************************************************************
   //													gestion menu
   //*********************************************************************************************************************
   if(e.mouseButton.x>0 && e.mouseButton.x<800 && e.mouseButton.y>0 && e.mouseButton.y<36){
     if(e.mouseButton.x>6 && e.mouseButton.x<32 && e.mouseButton.y>6 && e.mouseButton.y<30){ // menu principal
		defMenu.setSelectM1(1);
		defMenu.setSelectM2(0);
		defMenu.setSelectM3(0);
		defMenu.setSelectM4(0);
		defMenu.setSelectBarMenu(1);
     }
     if(e.mouseButton.x>54 && e.mouseButton.x<104 && e.mouseButton.y>6 && e.mouseButton.y<30){
		defMenu.setSelectM1(0);
		defMenu.setSelectM2(1);
		defMenu.setSelectM3(0);
		defMenu.setSelectM4(0);
		defMenu.setSelectBarMenu(1);
     }
     if(e.mouseButton.x>110 && e.mouseButton.x<164 && e.mouseButton.y>6 && e.mouseButton.y<30){
		defMenu.setSelectM1(0);
		defMenu.setSelectM2(0);
		defMenu.setSelectM3(1);
		defMenu.setSelectM4(0);
		defMenu.setSelectBarMenu(1);
     }
     if(e.mouseButton.x>170 && e.mouseButton.x<220 && e.mouseButton.y>6 && e.mouseButton.y<30){
		defMenu.setSelectM1(0);
		defMenu.setSelectM2(0);
		defMenu.setSelectM3(0);
		defMenu.setSelectM4(1);
		defMenu.setSelectBarMenu(1);
     }
   }
   if(defMenu.getSelectM1()==1 && e.mouseButton.x>6 && e.mouseButton.x<116 && e.mouseButton.y>36 && e.mouseButton.y<200){
     if(defMenu.getSelectM1()==1 && e.mouseButton.x>6 && e.mouseButton.x<116 && e.mouseButton.y>36 && e.mouseButton.y<64){
       menuSession();
     }
     if(defMenu.getSelectM1()==1 && e.mouseButton.x>6 && e.mouseButton.x<116 && e.mouseButton.y>64 && e.mouseButton.y<92){
       menuOpen();
     }
     if(defMenu.getSelectM1()==1 && e.mouseButton.x>6 && e.mouseButton.x<116 && e.mouseButton.y>92 && e.mouseButton.y<120){
       menuSave();
     }
     if(defMenu.getSelectM1()==1 && e.mouseButton.x>6 && e.mouseButton.x<116 && e.mouseButton.y>118 && e.mouseButton.y<150){
       menuComment();
     }
     if(defMenu.getSelectM1()==1 && e.mouseButton.x>6 && e.mouseButton.x<116 && e.mouseButton.y>150 && e.mouseButton.y<178){
       onClose();
     }
   }
   
   if(defMenu.getSelectM2()==1 && e.mouseButton.x>44 && e.mouseButton.x<160 && e.mouseButton.y>36 && e.mouseButton.y<274){
     if(e.mouseButton.x>44 && e.mouseButton.x<160 && e.mouseButton.y>36 && e.mouseButton.y<64){
     	 delCurseur(); 
     }
     if(e.mouseButton.x>44 && e.mouseButton.x<160 && e.mouseButton.y>64 && e.mouseButton.y<92){
       delGrpCurseur();
     }
     if(e.mouseButton.x>44 && e.mouseButton.x<160 && e.mouseButton.y>92 && e.mouseButton.y<120){
       delAllCurseur();
     }
     if(e.mouseButton.x>44 && e.mouseButton.x<160 && e.mouseButton.y>144 && e.mouseButton.y<172){
       menuPreferences();
     }
   }
   if(defMenu.getSelectM3()==1 && e.mouseButton.x>120 && e.mouseButton.x<170 && e.mouseButton.y>36 && e.mouseButton.y<274){
     if(e.mouseButton.x>120 && e.mouseButton.x<170 && e.mouseButton.y>36 && e.mouseButton.y<64){
     	 menuPlugin(); 
     }
     if(e.mouseButton.x>120 && e.mouseButton.x<170 && e.mouseButton.y>64 && e.mouseButton.y<92){
       editPlugin();
     }
     if(e.mouseButton.x>120 && e.mouseButton.x<170 && e.mouseButton.y>92 && e.mouseButton.y<120){
       eraseUsrPlugin();
     }
   }
   if(defMenu.getSelectM4()==1 && e.mouseButton.x>170 && e.mouseButton.x<220 && e.mouseButton.y>36 && e.mouseButton.y<274){
     if(e.mouseButton.x>170 && e.mouseButton.x<220 && e.mouseButton.y>36 && e.mouseButton.y<64){
       manuel();
     }
     if(e.mouseButton.x>170 && e.mouseButton.x<220 && e.mouseButton.y>64 && e.mouseButton.y<92){
       faust();
     }
     if(e.mouseButton.x>170 && e.mouseButton.x<220 && e.mouseButton.y>92 && e.mouseButton.y<120){
       apropos();
     }
   }
   //*********************************************************************************************************************
   //													séléction d'un pavé
   //*********************************************************************************************************************
   if(e.mouseButton.x>workspaceSurface.getPosition().x && e.mouseButton.x<workspaceSurface.getPosition().x+workspaceSurface.getSize().x  && e.mouseButton.y>workspaceSurface.getPosition().y && e.mouseButton.y<workspaceSurface.getPosition().y+workspaceSurface.getSize().y){
		int vret=0;
		if(e.mouseButton.button == sf::Mouse::Right){
   		vret=locatePoint(e.mouseButton.x, e.mouseButton.y,1);
   	}else{
   		vret=locatePoint(e.mouseButton.x, e.mouseButton.y,0);
   		if(omniSelectFlag==0 && vret!=0){
	   		tabPave[selectPad-1].setCurseurEtat(1);
	   		float lpx;
				float lpy;
				float mx;
	   		float my;
				if(defSurface.getPosition().x>workspaceSurface.getTextureRect().left){
					lpx=(defSurface.getPosition().x-workspaceSurface.getTextureRect().left);
					mx=(e.mouseButton.x-workspaceSurface.getPosition().x-(12*tabPave[selectPad-1].getDimMixer()))-lpx;
				}else{
				   lpx=(workspaceSurface.getTextureRect().left-defSurface.getPosition().x);
					mx=(e.mouseButton.x-workspaceSurface.getPosition().x-(12*tabPave[selectPad-1].getDimMixer()))+lpx;
				}
				if(defSurface.getPosition().y>workspaceSurface.getTextureRect().top){
					lpy=(defSurface.getPosition().y-workspaceSurface.getTextureRect().top);
					my=(e.mouseButton.y-(12*tabPave[selectPad-1].getDimMixer()))-lpy-workspaceSurface.getPosition().y;
				}else{
				   lpy=(workspaceSurface.getTextureRect().top-defSurface.getPosition().y);
					my=(e.mouseButton.y-(12*tabPave[selectPad-1].getDimMixer()))+lpy-workspaceSurface.getPosition().y;
				}
	   		tabPave[selectPad-1].setCurseurX(mx/nscale);
	   		tabPave[selectPad-1].setCurseurY(my/nscale);
	   		padActif=selectPad;
	   		updateCurseurPave(padActif-1);
	   		std::cout << "selectPad: " <<selectPad << std::endl;
   			std::cout << "tabPave[selectPad-1].getDimMixer()"<<tabPave[selectPad-1].getDimMixer()<<" mx: " <<(e.mouseButton.x-200-12)*nscale<< std::endl;
   		}
   	}
   }
   //*********************************************************************************************************************
   //													suppression
   //*********************************************************************************************************************
	if(e.mouseButton.x>118 && e.mouseButton.x<134 && e.mouseButton.y>442 && e.mouseButton.y<468){
   	delAnneau();
   }
   if(e.mouseButton.x>140 && e.mouseButton.x<160  && e.mouseButton.y>442 && e.mouseButton.y<468){
   	delAllAnneau();
   }
   if(e.mouseButton.x>44 && e.mouseButton.x<64  && e.mouseButton.y>446 && e.mouseButton.y<468){
   	delCurseur();
   }
   if(e.mouseButton.x>68 && e.mouseButton.x<88  && e.mouseButton.y>446 && e.mouseButton.y<468){
   	delGrpCurseur();
   }
   if(e.mouseButton.x>92 && e.mouseButton.x<112  && e.mouseButton.y>446 && e.mouseButton.y<468){
   	delAllCurseur();
   }
   //*********************************************************************************************************************
   //													temporisation
   //*********************************************************************************************************************
   if(e.mouseButton.x>84 && e.mouseButton.x<98  && e.mouseButton.y>408 && e.mouseButton.y<420){
   	v=temporisationMin;
   	v++;
   	if(v>temporisationMax-1){
   		v=temporisationMax-1;
   	}
   	temporisationMin=v;
   	tempoTMin.setString(to_string(v));
   	tempoTMin.setPosition(84-tempoTMin.getLocalBounds().width-6,410);
   	std::cout <<" ex : "<<temporisationMin<< std::endl;
   }
   if(e.mouseButton.x>84 && e.mouseButton.x<98  && e.mouseButton.y>420 && e.mouseButton.y<430){
   	v=temporisationMin;
   	v--;
   	if(v<1){
   		v=1;
   	}
   	temporisationMin=v;
   	tempoTMin.setString(to_string(v));
   	tempoTMin.setPosition(84-tempoTMin.getLocalBounds().width-6,410);
   }
   if(e.mouseButton.x>134 && e.mouseButton.x<148  && e.mouseButton.y>408 && e.mouseButton.y<420){
   	v=temporisationMax;
   	v++;
   	if(v>40){
   		v=40;
   	}
   	temporisationMax=v;
   	tempoTMax.setString(to_string(v));
   	tempoTMax.setPosition(134-tempoTMax.getLocalBounds().width-6,410);
   }
   if(e.mouseButton.x>134 && e.mouseButton.x<148  && e.mouseButton.y>420 && e.mouseButton.y<430){
   	v=temporisationMax;
   	v--;
   	if(v<temporisationMin+1){
   		v=temporisationMin+1;
   	}
   	temporisationMax=v;
   	tempoTMax.setString(to_string(v));
   	tempoTMax.setPosition(134-tempoTMax.getLocalBounds().width-6,410);
   }
   //*********************************************************************************************************************
   //													Explode
   //*********************************************************************************************************************
   if(e.mouseButton.x>139 && e.mouseButton.x<154  && e.mouseButton.y>96 && e.mouseButton.y<106){
   	v=exploseMax;
   	v++;
   	if(v>40){
   		v=40;
   	}
   	exploseMax=v;
   	exploseTMax.setString(to_string(v));
   	exploseTMax.setPosition(136-exploseTMax.getLocalBounds().width-6,98);
   }
   if(e.mouseButton.x>139 && e.mouseButton.x<154  && e.mouseButton.y>106 && e.mouseButton.y<118){
   	v=exploseMax;
   	v--;
   	if(v<1){
   		v=1;
   	}
   	exploseMax=v;
   	exploseTMax.setString(to_string(v));
   	exploseTMax.setPosition(136-exploseTMax.getLocalBounds().width-6,98);
   }
   //*********************************************************************************************************************
   //													Sliders Durée de vie
   //*********************************************************************************************************************
   
   if(e.mouseButton.x>boutonSl1b.getPosition().x && e.mouseButton.x< boutonSl1b.getPosition().x+11 && e.mouseButton.y>boutonSl1b.getPosition().y && e.mouseButton.y<boutonSl1b.getPosition().y+11){
   	mvBoutonSl1b=1;
   	slideMdY=e.mouseButton.y;
   }
   if(e.mouseButton.x>boutonSl2b.getPosition().x && e.mouseButton.x< boutonSl2b.getPosition().x+11 && e.mouseButton.y>boutonSl2b.getPosition().y && e.mouseButton.y<boutonSl2b.getPosition().y+11){
   	mvBoutonSl2b=1;
   	slideMdY=e.mouseButton.y;
   }
   //*********************************************************************************************************************
   //													Surface mode
   //*********************************************************************************************************************
   if(e.mouseButton.x>78 && e.mouseButton.x<92 && e.mouseButton.y>544 && e.mouseButton.y<558){
   	if(omniSurface==0){
    	 omniSurface=1;
    	 bOmniSurface.setTexture(bselect);
    	}else{
    	 omniSurface=0;
    	 bOmniSurface.setTexture(bNoSelect);
    	}
   }
   if(e.mouseButton.x>154 && e.mouseButton.x<172 && e.mouseButton.y>544 && e.mouseButton.y<558){
   	if(omniRamdom==0){
    	 omniRamdom=1;
    	 bOmniRamdom.setTexture(bselect);
    	}else{
    	 omniRamdom=0;
    	 bOmniRamdom.setTexture(bNoSelect);
    	}
   }
   //*********************************************************************************************************************
   //													Type de déplacement
   //*********************************************************************************************************************
   if(e.mouseButton.x>56 && e.mouseButton.x<76  && e.mouseButton.y>58 && e.mouseButton.y<76){
   	typeMove=0;
   }
   if(e.mouseButton.x>89 && e.mouseButton.x<110  && e.mouseButton.y>58 && e.mouseButton.y<76){
   	typeMove=1;
   }
   if(e.mouseButton.x>124 && e.mouseButton.x<144  && e.mouseButton.y>58 && e.mouseButton.y<76){
   	typeMove=2;
   }
   //*********************************************************************************************************************
   //													New Omni
   //*********************************************************************************************************************
   if(e.mouseButton.x>114 && e.mouseButton.x<134  && e.mouseButton.y>486 && e.mouseButton.y<510){
   	int lX=defSurface.getPosition().x+rand_a_b(10, 600);
	   int lY=defSurface.getPosition().y+rand_a_b(10, 600);
   	newOmni(lX,lY);
   }
   if(e.mouseButton.x>66 && e.mouseButton.x<90 && e.mouseButton.y>486 && e.mouseButton.y<510){
   	genDSP(to_string(ref->getOSC()),to_string(newParametres.getXmit()));
   }
}
void metaSurface::onMouseMoveSurface(sf::Event e){
   std::cout << "mouse x: " << e.mouseMove.x << std::endl;
   std::cout << "mouse y: " << e.mouseMove.y << std::endl;
   int ndpx=0;
   int ndpy=0;
   float lpx;
	float lpy;
	float mx;
	float my;
	float dt=0.0;
   //*********************************************************************************************************************
   //													gestion du Menu
   //*********************************************************************************************************************
   if(e.mouseMove.x>0 && e.mouseMove.x<windowAppWidth && e.mouseMove.y>0 && e.mouseMove.y<400){
     if(defMenu.getSelectBarMenu()==1 && e.mouseMove.x>6 && e.mouseMove.x<52){ // menu principal
		 defMenu.setSelectM1(1);
		 defMenu.setSelectM2(0);
     }
     if(defMenu.getSelectM1()==1 && (e.mouseMove.x>116 || e.mouseMove.y>200)){
		 defMenu.setSelectM1(0);
		 defMenu.setSelectM2(0);
		 defMenu.setSelectBarMenu(0);
     }
     if(defMenu.getSelectM1()==1 && e.mouseMove.x>0 && e.mouseMove.x<116 && e.mouseMove.y>36 &&  e.mouseMove.y<200){
       defMenu.setSelectM1I((int)(e.mouseMove.y-36)/30);
     }
     if(defMenu.getSelectBarMenu()==1 && e.mouseMove.x>70 && e.mouseMove.x<140){ // menu principal
		 defMenu.setSelectM1(0);
		 defMenu.setSelectM2(1);
     }
     if(defMenu.getSelectM2()==1 && (e.mouseMove.x<56 || e.mouseMove.x>110  ||  e.mouseMove.y>172)){
		 defMenu.setSelectM2(0);
       defMenu.setSelectBarMenu(0);
     }
     if(defMenu.getSelectM2()==1 && e.mouseMove.x>56 && e.mouseMove.x<110 && e.mouseMove.y>36 &&  e.mouseMove.y<172){
       defMenu.setSelectM2I((int)(e.mouseMove.y-36)/30);
     }
     if(defMenu.getSelectM3()==1 && (e.mouseMove.x<110 || e.mouseMove.x>164  ||  e.mouseMove.y>172)){
		 defMenu.setSelectM3(0);
       defMenu.setSelectBarMenu(0);
     }
     if(defMenu.getSelectM3()==1 && e.mouseMove.x>112 && e.mouseMove.x<164 && e.mouseMove.y>36 &&  e.mouseMove.y<172){
       defMenu.setSelectM3I((int)(e.mouseMove.y-36)/30);
     }
     if(defMenu.getSelectM4()==1 && (e.mouseMove.x<170 || e.mouseMove.x>220  ||  e.mouseMove.y>172)){
		 defMenu.setSelectM4(0);
       defMenu.setSelectBarMenu(0);
     }
     if(defMenu.getSelectM4()==1 && e.mouseMove.x>170 && e.mouseMove.x<220 && e.mouseMove.y>36 &&  e.mouseMove.y<172){
       defMenu.setSelectM4I((int)(e.mouseMove.y-36)/30);
     }
   }
   //*********************************************************************************************************************
   //													gestion navigateur
   //*********************************************************************************************************************
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
   //*********************************************************************************************************************
   //													gestion scrollbar
   //*********************************************************************************************************************
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
   //*********************************************************************************************************************
   //													gestion sliders
   //*********************************************************************************************************************
   if(mvBoutonSl1b==1 && e.mouseMove.x > 50 && e.mouseMove.x<78 && e.mouseMove.y> 152 && e.mouseMove.y<332){
     int nposy=boutonSl1b.getPosition().y+(e.mouseMove.y-slideMdY);
     if(nposy<152){
   		nposy=152;
     }
     if(nposy>328){
   		nposy=328;
     }
     boutonSl1b.setPosition(boutonSl1b.getPosition().x,nposy);
     dt=520.231*(328-nposy);
     vieMin=(int)dt+10000;
     if(vieMin<10000){
     	vieMin=10000;
     }
     if(vieMin>vieMax){
     	vieMin=vieMax-1;
     }
	  dureevieTMin.setString(to_string(vieMin));
	  dureevieTMin.setPosition(90-dureevieTMin.getLocalBounds().width-4,352);
     slideMdY=e.mouseMove.y; 
     std::cout << "slider y: " << nposy << std::endl;
   }
   if(mvBoutonSl2b==1 && e.mouseMove.x > 120 && e.mouseMove.x<146 && e.mouseMove.y> 152 && e.mouseMove.y<330){
     int nposy=boutonSl2b.getPosition().y+(e.mouseMove.y-slideMdY);
     if(nposy<152){
   		nposy=152;
     }
     if(nposy>330){
   		nposy=330;
     }
     boutonSl2b.setPosition(boutonSl2b.getPosition().x,nposy);
     dt=1250*(330-nposy);
     vieMax=(int)dt+100000;
     if(vieMax<vieMin){
     	vieMin=vieMin+1;
     }
     if(vieMax>300000){
     	vieMax=300000;
     }
	  dureevieTMax.setString(to_string(vieMax));
	  dureevieTMax.setPosition(164-dureevieTMax.getLocalBounds().width-4,352);
     slideMdY=e.mouseMove.y; 
   }
	//*********************************************************************************************************************
   //													gestion déplacement mixer et omni
   //*********************************************************************************************************************   
   if(omniSelectFlag==1){
   	float sx=tabOmni[omniSelect].anneau.getPosition().x;
		float sy=tabOmni[omniSelect].anneau.getPosition().y;
		if(defSurface.getPosition().x>=workspaceSurface.getTextureRect().left){
			lpx=(defSurface.getPosition().x-workspaceSurface.getTextureRect().left);
			mx=(e.mouseMove.x-212)-lpx+defSurface.getPosition().x;
		}else{
		   lpx=(workspaceSurface.getTextureRect().left-defSurface.getPosition().x);
			mx=(e.mouseMove.x-212)+lpx+defSurface.getPosition().x;
		}
		if(defSurface.getPosition().y>=workspaceSurface.getTextureRect().top){
			lpy=(defSurface.getPosition().y-workspaceSurface.getTextureRect().top);
			my=(e.mouseMove.y-12)-lpy-workspaceSurface.getPosition().y+defSurface.getPosition().y;
		}else{
		   lpy=(workspaceSurface.getTextureRect().top-defSurface.getPosition().y);
			my=(e.mouseMove.y-12)+lpy-workspaceSurface.getPosition().y+defSurface.getPosition().y;
		}   	
		tabOmni[omniSelect].anneau.setPosition(sf::Vector2f(mx,my));
		if(typeMove==1){
			lpx=mx-sx;
			lpy=my-sy;
			for(int i;i<exploseMax;i++){
				if(i!=omniSelect){
					mx=tabOmni[i].anneau.getPosition().x+lpx;
					my=tabOmni[i].anneau.getPosition().y+lpy;
					tabOmni[i].anneau.setPosition(sf::Vector2f(mx,my));
				}
			}
		}
		updateGainPave();
   }else{
	   if ( padActif!=0 ){
	   	
			float sx=tabPave[selectPad-1].getCurseurX();
			float sy=tabPave[selectPad-1].getCurseurY();
			if(defSurface.getPosition().x>workspaceSurface.getTextureRect().left){
				lpx=(defSurface.getPosition().x-workspaceSurface.getTextureRect().left);
				mx=(e.mouseMove.x-workspaceSurface.getPosition().x-(12*tabPave[selectPad-1].getDimMixer()))-lpx;
			}else{
			   lpx=(workspaceSurface.getTextureRect().left-defSurface.getPosition().x);
				mx=(e.mouseMove.x-workspaceSurface.getPosition().x-(12*tabPave[selectPad-1].getDimMixer()))+lpx;
			}
			if(defSurface.getPosition().y>workspaceSurface.getTextureRect().top){
				lpy=(defSurface.getPosition().y-workspaceSurface.getTextureRect().top);
				my=(e.mouseMove.y-(12*tabPave[selectPad-1].getDimMixer()))-lpy-workspaceSurface.getPosition().y;
			}else{
			   lpy=(workspaceSurface.getTextureRect().top-defSurface.getPosition().y);
				my=(e.mouseMove.y-(12*tabPave[selectPad-1].getDimMixer()))+lpy-workspaceSurface.getPosition().y;
			}
	   	int rtp=inPolygone(1,tabPave[selectPad-1], sf::Vector2f(e.mouseMove.x,e.mouseMove.y));
	   	if(rtp>0){
	   		tabPave[selectPad-1].setCurseurX(mx/nscale);
	   		tabPave[selectPad-1].setCurseurY(my/nscale);
	   		if(typeMove==1){
	   			lpx=tabPave[selectPad-1].getCurseurX()-sx;
	   			lpy=tabPave[selectPad-1].getCurseurY()-sy;
	   			for(int i;i<surfaceTypeDef;i++){
	   				if(i!=selectPad-1 && tabPave[selectPad-1].getCurseurT()==tabPave[i].getCurseurT() && tabPave[selectPad-1].getCurseurEtat()==1){
	   					mx=tabPave[i].getCurseurX()+lpx;
	   					my=tabPave[i].getCurseurY()+lpy;
	   					rtp=inPolygone(0,tabPave[i], sf::Vector2f(mx*nscale,my*nscale));
	   					if(rtp>0){
	   						tabPave[i].setCurseurX(mx);
	   						tabPave[i].setCurseurY(my);
	   						updateCurseurPave(i);
	   					}
	   				}
	   			}
	   		}
	   		if(typeMove==2){
	   			lpx=tabPave[selectPad-1].getCurseurX()-sx;
	   			lpy=tabPave[selectPad-1].getCurseurY()-sy;
	   			for(int i;i<surfaceTypeDef;i++){
	   				if(i!=selectPad-1 && tabPave[selectPad-1].getCurseurEtat()==1){
	   					mx=tabPave[i].getCurseurX()+lpx;
	   					my=tabPave[i].getCurseurY()+lpy;
	   					rtp=inPolygone(0,tabPave[i], sf::Vector2f(mx*nscale,my*nscale));
	   					if(rtp>0){
	   						tabPave[i].setCurseurX(mx);
	   						tabPave[i].setCurseurY(my);
	   						updateCurseurPave(i);
	   					}
	   				}
	   			}
	   		}
	   		updateCurseurPave(selectPad-1);
	   	}
	   }
   }
}
void metaSurface::mouseWheel(sf::Event e){
  int dx;
  int dy;
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
	float dtx=defSurface.getTextureRect().width;;
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
void metaSurface::onClose(){
  surface.close();
}
void metaSurface::menuOpen(){
  openSurface();
}
void metaSurface::menuSave(){
  saveSurface(0);
}
void metaSurface::menuComment(){
  system(const_cast<char*>(ref->getEditeur().c_str()));
}
void metaSurface::menuPlugin(){
	bool rt=newPlugin.drawPlugin(0,0,"Plugin");
}
void metaSurface::editPlugin(){
	bool rt=newPlugin.editListPlugin("Plugin");
	typeMove=0;
}
void metaSurface::eraseUsrPlugin(){
	//bool rt=newPlugin.eraseUsrPlugin(5, "Plugin");
	newPlugin.nettoyerPlugin();
}
void metaSurface::menuPreferences(){
  string rt=newParametres.drawParametres(ref->getDossierConfig(),ref->getAppGui(),ref->getFichierTheme(),ref->getDossierUser());
  if(rt=="ok"){
  	ref->setDaw(newParametres.getDaw());
  	ref->setEditeur(newParametres.getEditeur());
  	ref->setNavigateur(newParametres.getNavigateur());
  	ref->setPort(newParametres.getPort());
  	ref->setServeur(newParametres.getServeur());
  	ref->setOsc(newParametres.getOsc());
  	std::cout <<"navigateur "<<ref->getNavigateur()<< std::endl;
  }
}
void metaSurface::menuSession(){
	string s=ref->getDossierConfig();
	char * cstr = new char [s.length()+1];
   std::strcpy (cstr, s.c_str());
   int ncwd=chdir(cstr);
	int type=surfaceN.drawSurface(ref->getDossierConfig(),ref->getAppGui(),ref->getFichierTheme(),ref->getDossierUser());
  	string nameFile=surfaceN.selectReturnPath()+"/"+surfaceN.selectReturnFile();
  	std::cout <<"appGui "<<ref->getAppGui()<<" nameFile "<<nameFile<< std::endl;
  	chargeSurface(nameFile);
}
void metaSurface::manuel(){
	string nn=ref->getNavigateur();
	string cmd=nn+" http://blanchemain.info/Documents/Programmation/index.php?page=metaSurface &";
   char* dest = new char[cmd.length() + 1];
   std::copy(cmd.begin(), cmd.end(), dest);
   system(dest);
}
void metaSurface::faust(){
	string nn=ref->getNavigateur();
	string cmd=nn+" https://faust.grame.fr/ &";
   char* dest = new char[cmd.length() + 1];
   std::copy(cmd.begin(), cmd.end(), dest);
   system(dest);
}
void metaSurface::apropos(){
	std::cout <<"a propos "<< std::endl;
	//bool rt=newPlugin.editPlugin(5, "Plugin");
	newApropos.drawApropos(ref->getDossierConfig(),ref->getAppGui(),ref->getFichierTheme(),ref->getDiversLang(),ref->getNavigateur());
}
// ********************************************************************************************************************************
//																gestion du gain
// ********************************************************************************************************************************
void metaSurface::updateCurseurPave(int pv){
	std::cout <<" pv "<<pv<<" tabPave[pv].getCurseurEtat "<<tabPave[pv].getCurseurEtat() << std::endl;
	if(tabPave[pv].getCurseurEtat()==1){
		float rt=distanceCentre(tabPave[pv].getCx(), tabPave[pv].getCy(),tabPave[pv].getCurseurX()+(12*tabPave[selectPad-1].getDimMixer()), tabPave[pv].getCurseurY()+(12*tabPave[selectPad-1].getDimMixer()));
		float base=(tabPave[pv].getGainMax()-tabPave[pv].getGainMin())/tabPave[pv].getDistanceMax();
		float gain=tabPave[pv].getGainMax()-(base*rt);
		tabPave[pv].gain=gain;
		defGain(pv,gain);
		updatePlugins(pv, rt);
		stringstream adr;
	   string obj3;
	   float pvk;
	   pvk=tabPave[pv].gain;
	  	adr << std::fixed<< std::setprecision(2)<<pvk;
	  	obj3=adr.str();
		adr.clear();
	  	adr.str("");
		std::cout <<"distanceMax"<<tabPave[pv].getDistanceMax() <<" base "<< base <<" distance"<<rt<<"getCx"<<tabPave[pv].getCx()<<"getCy"<<tabPave[pv].getCy()<<"getCurseurX"<<tabPave[pv].getCurseurX()<<"getCurseurY"<<tabPave[pv].getCurseurY()<<" gain : " << obj3<< std::endl;
	}
}
void metaSurface::defGain(int pad, float gain){
	if(ref->getDaw()=="Ardour"){
		ctrlOsc=1;
	}else{
		ctrlOsc=2;
	}
	if(tabPave[pad].getMixgain()==1){
		string portArdour=to_string(ref->getPort());
		string cmArdour="/strip/plugin/parameter";
		string portReaper=to_string(ref->getPort());
		string cmReaper;
		string cm;
		string destination=ref->getServeur();
		string portOsc=to_string(ref->getOSC());
		string spv;
		string spad;
		lo::Address a(destination, portOsc);
		if(tabPave[pad].getFlagDaw()==0){
			switch(modeDsp){
				case 0:
					if(pad<10){
						spad="0"+to_string(pad)+"/0x00/Player/Param/gain_";
					}else{
						spad=to_string(pad)+"/0x00/Player/Param/gain";
					}
					cm="/padPlayer/Pad/p"+spad+to_string(pad);
					break;
				case 1:
					cm="/padPlayer/0x00/0x00/Player/0x00/0x00/gain";
					break;
				case 2:
					cm="/padPlayer/0x00/0x00/0x00/Player/0x00/0x00/gain";
			}
			a.send(cm, "f",gain);
			std::cout <<"osc Loop "<<portOsc<<" "<<cm<<" f "<<gain<< std::endl;
		}else if(ctrlOsc==1){
			/*
			if(tabPave[pad].getFile()!=""){
				if(pad<10){
					spad="0"+to_string(pad)+"/0x00/Player/Param/gain_";
				}else{
					spad=to_string(pad)+"/0x00/Player/Param/gain";
				}
				cm="/padPlayer/Pad/p"+spad+to_string(pad);
			}
			a.send(cm, "f",gain);
			*/
			lo::Address a(destination, portArdour);
			gain=gain/tabPave[pad].getGainMax();
			string cm="/strip/fader if "+to_string(tabPave[pad].getTrack())+" "+to_string(gain);
	 		a.send("/strip/fader", "if",tabPave[pad].getTrack(),gain);
			std::cout <<"osc Ardour "<<" f "<<cm<< std::endl;
	 			}else{
	 				lo::Address a(destination, portReaper);
	  			 	cmReaper="/track/"+to_string(tabPave[pad].getTrack())+"/volume";
	  			 	a.send(cmReaper, "f", gain/tabPave[pad].getGainMax());
	  			 	std::cout <<"osc Reaper "<< cmReaper<<" f "<<gain/tabPave[pad].getGainMax()<< std::endl;
	 			}
	} 
}
void metaSurface::updateGainPave(){
	float rt,rtp,base,gain,gain2;
	int nb=0;
	gain=0;
	float dl=0;
	float ec;
	
	if(omniSurface==0){
		for(int pv=0;pv<surfaceTypeDef;pv++){
			if(tabPave[pv].getCurseurEtat()==1){
				float g1=tabPave[pv].gain;
				base=(tabPave[pv].getGainMax()-tabPave[pv].getGainMin())/(tabPave[pv].getDistanceMax()*nscale);
				for(int i=0;i<exploseMax;i++){
					rtp=inPolygone(0,tabPave[pv], sf::Vector2f(tabOmni[i].anneau.getPosition().x+12-defSurface.getPosition().x,tabOmni[i].anneau.getPosition().y+12-defSurface.getPosition().y));
					if(rtp>0){
						if(tabOmni[i].getEtat()==1){
								rt=distanceCentre(tabPave[pv].getCx()*nscale, tabPave[pv].getCy()*nscale,(tabOmni[i].anneau.getPosition().x+12)-defSurface.getPosition().x, (tabOmni[i].anneau.getPosition().y+12)-defSurface.getPosition().y);
								gain=gain+(tabPave[pv].getGainMax()-(base*rt));
								nb++;
						}
					}
				}
				if(nb>0){
					gain=gain/nb;
					dl=(tabPave[pv].getGainMax()-tabPave[pv].gain);
					ec=tabPave[pv].getGainMax()-tabPave[pv].getGainMin();
					gain2=g1+(dl*(gain/ec));
					if(gain2>tabPave[pv].getGainMax()){
						gain2=tabPave[pv].getGainMax();
					}
					defGain(pv, gain2);
					gain=0;
					gain2=0;
				}
			}
			nb=0;
		}
	}else{
		for(int pv=0;pv<surfaceTypeDef;pv++){
			base=(tabPave[pv].getGainMax()-tabPave[pv].getGainMin())/(tabPave[pv].getDistanceMax()*nscale);
			for(int i=0;i<exploseMax;i++){
				rtp=inPolygone(0,tabPave[pv], sf::Vector2f(tabOmni[i].anneau.getPosition().x+12-defSurface.getPosition().x,tabOmni[i].anneau.getPosition().y+12-defSurface.getPosition().y));
				if(rtp>0){
					if(tabOmni[i].getEtat()==1){
						rt=distanceCentre(tabPave[pv].getCx()*nscale, tabPave[pv].getCy()*nscale,(tabOmni[i].anneau.getPosition().x+12)-defSurface.getPosition().x, (tabOmni[i].anneau.getPosition().y+12)-defSurface.getPosition().y);
						if(rt<(tabPave[pv].getDistanceMax()*nscale)){
							gain=gain+(tabPave[pv].getGainMax()-(base*rt));
							nb++;
						}
					}
				}
			}
			if(nb>0){
				gain=gain/nb;
				if(gain>tabPave[pv].getGainMax()){
				gain=tabPave[pv].getGainMax();
				}
				if(gain<0){
					gain=0;
				}
				defGain(pv, gain);
					gain=0;
					nb=0;
			}
			
		}
	}
}
void metaSurface::defPlugins(string &ms, float param){
	
	
}
void metaSurface::updatePlugins(int pv, float rt){
	float param;
	string baseAdr;
	string daw=ref->getDaw();
	string destination=ref->getServeur();
	string portOsc=to_string(ref->getOSC());
	string portArdour=to_string(ref->getPort());
	string cmArdour="/strip/plugin/parameter";
	string portReaper=to_string(ref->getPort());
	string cmReaper;
	string cm;
	string spv;
	stringstream adr;
	if(ref->getDaw()=="Ardour"){
		ctrlOsc=1;
	}else{
		ctrlOsc=2;
	}
	lo::Address a(destination, portOsc);
	if(pv<10){
		spv="0"+to_string(pv);
	}else{
		spv=to_string(pv);
	}
	
	if(tabPave[pv].getFx()==1){
		std::map<string, int> ls=newPlugin.getListPlugin();
  		std::vector<Plugin::plugin> tabPlug=newPlugin.getTabPlugin();
  		int idnbfx=ls.find(tabPave[pv].idNameFx[0])->second;
  		ContraintesFx ctrlFx(ref);
  		
		for(int i=0;i<12;i++){
			
			if(tabPave[pv].idNameFx[i]!=""){
				std::cout << "selectPad: " << selectPad-1<< "plugin: " << i<< "name: " << tabPave[pv].idNameFx[i]<< std::endl;
				idnbfx=ls.find(tabPave[pv].idNameFx[i])->second;
				std::cout << " tabPlugin nom: " << tabPlug[idnbfx].nomFx<< "  DistanceMax: " << tabPave[pv].getDistanceMax()<< std::endl;
			
				for(int j=0;j<tabPlug[idnbfx].nbpar;j++){
					if(tabPave[pv].tabUsrPluginParam[i][j].etat==1){
						param=((tabPave[pv].tabUsrPluginParam[i][j].max-tabPave[pv].tabUsrPluginParam[i][j].min)/tabPave[pv].getDistanceMax())*tabPave[pv].tabUsrPluginParam[i][j].scale;
						if(tabPave[pv].tabUsrPluginParam[i][j].rev==0){
							param=tabPave[pv].tabUsrPluginParam[i][j].max-(param*rt);
							if(tabPave[pv].tabUsrPluginParam[i][j].mod==1){
								param=param*(log10(tabPave[pv].getDistanceMax()/rt));
							}
						}else{
							param=(param*rt)+tabPave[pv].tabUsrPluginParam[i][j].min;
							if(tabPave[pv].tabUsrPluginParam[i][j].mod==1){
								param=param/(log10(tabPave[pv].getDistanceMax()/rt));
							}
						}
						if(param>tabPave[pv].tabUsrPluginParam[i][j].max){
							param=tabPave[pv].tabUsrPluginParam[i][j].max;
						}
						if(param<tabPave[pv].tabUsrPluginParam[i][j].min){
							param=tabPave[pv].tabUsrPluginParam[i][j].min;
						}
						if(tabPave[pv].getFlagDaw()==0){
			        	   		lo::Address a(destination, portOsc);
		       	 				switch(modeDsp){
										case 0:
											baseAdr="/padPlayer/Pad/p"+spv+"/0x00/0x00/"+tabPlug[idnbfx].param[j].adr;
											if(tabPave[pv].idNameFx[i]=="Speed"){
												baseAdr="/padPlayer/Pad/p"+spv+"/0x00/Player/Param/speed";
												if(pv<10){
													baseAdr=baseAdr+"_"+to_string(pv);
												}else{
													baseAdr=baseAdr+to_string(pv);
												}
												std::cout <<" nom "<<tabPave[pv].idNameFx[i]<<" speed ok "<<baseAdr<< std::endl;
											}
											a.send(baseAdr, "f",param);
											break;
										case 1:
											baseAdr="/padPlayer/0x00/0x00/0x00/0x00/"+tabPlug[idnbfx].param[j].adr;
											a.send(baseAdr, "f",param);
											break;
										case 2:
											for(int k=0;k<tabPave[pv].getNbCanaux();k++){
												baseAdr="/padPlayer/0x00/c_"+to_string(k)+"/0x00/"+tabPlug[idnbfx].param[j].adr;
												a.send(baseAdr, "f",param);
											}
									}
				        	  	   
				        	  	   std::cout <<"osc "<<baseAdr<<" f "<<param<< std::endl;

		    		 		}else if(ctrlOsc==1) {
		  			 				lo::Address a(destination, portArdour);
	 								int np=i+1;
	 								cm=cmArdour+" iiif "+to_string(tabPave[pv].getTrack())+" "+to_string(np)+" "+to_string(tabPlug[idnbfx].param[j].id+1);
/*
	 								float param2=((tabPave[pv].tabUsrPluginParam[i][j].max-tabPave[pv].tabUsrPluginParam[i][j].min)/tabPave[pv].getDistanceMax())*tabPave[pv].tabUsrPluginParam[i][j].scale;
									if(tabPave[pv].tabUsrPluginParam[i][j].rev==0){
										param2=(tabPave[pv].tabUsrPluginParam[i][j].max-(param2*rt))*(log10(130/rt));
									}else{
										param2=(param2*rt)+tabPave[pv].tabUsrPluginParam[i][j].min;
									}
									*/
						 			a.send(cmArdour, "iiif",tabPave[pv].getTrack(),np,tabPlug[idnbfx].param[j].id+1,param);
						 			}else{
						 				lo::Address a(destination, portReaper);
			  			 				int np=i+1;
			  			 				cmReaper="/track/"+to_string(tabPave[pv].getTrack())+"/fx/"+to_string(np)+"/fxparam/"+to_string(tabPlug[idnbfx].param[j].id+1)+"/value";
										float nbase;										
										if(tabPlug[idnbfx].type!=2){									
											nbase=1/((tabPave[pv].tabUsrPluginParam[i][j].max-tabPave[pv].tabUsrPluginParam[i][j].min)*tabPave[pv].tabUsrPluginParam[i][j].scale);
											if(tabPave[pv].tabUsrPluginParam[i][j].min<0){
												param=param-tabPave[pv].tabUsrPluginParam[i][j].min;
											}
											param=nbase*param;
										}
			  			 				a.send(cmReaper, "f", param);
			  			 				std::cout << " tabPlugin nom: " << tabPlug[idnbfx].nomFx<< "  cm: " << cmReaper<< " param= " <<param<<" base "<<nbase<< std::endl;
						 			}
						//std::cout << " tabPlugin nom: " << tabPlug[idnbfx].nomFx<< "  cm: " << cmReaper<< " param= " <<param<<" rt "<<rt<< std::endl;
					}
				}
			}
		}
	}
}
// ********************************************************************************************************************************
//																Suppression
// ********************************************************************************************************************************
void metaSurface::delAnneau(){
	for(int i=0;i<20;i++){
		if(tabOmni[i].getEtat()==1){
			tabOmni[i].setEtat(0);
			break;
		}
	}
}
void metaSurface::delAllAnneau(){
	for(int i=0;i<20;i++){
		tabOmni[i].setEtat(0);
	}
}
void metaSurface::delCurseur(){
		tabPave[selectPad-1].setCurseurEtat(0);
		defGain(selectPad-1, 0);
		std::cout <<" padActif : "<<selectPad<< std::endl;
}
void metaSurface::delGrpCurseur(){
	 int grp=tabPave[selectPad-1].getCurseurT();
	 for(int i=0;i<surfaceTypeDef;i++){
	 	if(tabPave[i].getCurseurEtat()==1 && tabPave[i].getCurseurT()==grp){
			tabPave[i].setCurseurEtat(0);
			defGain(i, 0);
		}
	 }
}
void metaSurface::delAllCurseur(){
	 for(int i=0;i<surfaceTypeDef;i++){
		tabPave[i].setCurseurEtat(0);
		defGain(i, 0);
	 }
}
// ********************************************************************************************************************************
//																gestion des Omni
// ********************************************************************************************************************************
void  metaSurface::newOmni(int lX, int lY){
	for(int i=0;i<exploseMax;i++){
		if(tabOmni[i].getEtat()==0){
			tabOmni[i].setEtat(1);
			tabOmni[i].anneau.setTexture(selectAn);
  			tabOmni[i].anneau.setPosition(lX,lY);
  			tabOmni[i].setDirectionX(1);
  			tabOmni[i].setDirectionY(1);
  			tabOmni[i].setDirectionParamX(rand_a_b(1, 4));
  			tabOmni[i].setDirectionParamY(rand_a_b(1, 10));
  			tabOmni[i].setComptimeD(rand_a_b(temporisationMin, temporisationMax));
  			tabOmni[i].setDureeVie(rand_a_b(vieMin, vieMax));
  			tabOmni[i].setExplose(rand_a_b(1, 4));
  			tabOmni[i].initComptime();
  			break;
		}
	}
}
void metaSurface::surfaceCollision(int mobil){
	bool exp;
	for(int i=0;i<surfaceTypeDef;i++){
		if(tabOmni[mobil].getDureeVie()>0){
			tabOmni[mobil].setDureeVie(tabOmni[mobil].getDureeVie()-1);
		}else{
			tabOmni[mobil].setEtat(0);
		}
		if(tabPave[i].getCurseurEtat()==1){
			exp=collision(12, tabOmni[mobil].anneau.getPosition().x, tabOmni[mobil].anneau.getPosition().y, tabPave[i].getDimMixer(), defSurface.getPosition().x+tabPave[i].getCurseurX()*nscale, defSurface.getPosition().y+tabPave[i].getCurseurY()*nscale);
      	if(exp==1 && tabOmni[mobil].getExplose()>0){
      		newOmni(tabOmni[mobil].anneau.getPosition().x,tabOmni[mobil].anneau.getPosition().y);
      		tabPave[i].setExplose(tabPave[i].getExplose()-1);
      		if(tabPave[i].getExplose()<0){
      			tabPave[i].setExplose(0);
      		}
      		tabOmni[mobil].setExplose(tabOmni[mobil].getExplose()-1);
      		if(tabOmni[mobil].getExplose()<0){
      			tabOmni[mobil].setExplose(0);
      		}
      		break;
      	}
		}
	}
}
bool metaSurface::collision(float r1, float x1, float y1, float r2, float x2, float y2){
	float dt=distanceCentre(x1, y1, x2, y2);
	bool cl;
	if(dt<r1+r2){
		cl=1;
	}else{
		cl=0;
	}
	return cl;
}
void metaSurface::moveAnneau(int mobil){
	float dtwx=surfaceN.getSwidth()*nscale;
	float dtwy=surfaceN.getSheight()*nscale; 
	float anneauPosX;
	float anneauPosY;
	float param;
	float ct=tabOmni[mobil].getComptime();
	if(omniRamdom==1){
		if(ct==0){
			anneauPosX=tabOmni[mobil].anneau.getPosition().x+(tabOmni[mobil].directionParam.x*tabOmni[mobil].direction.x);
			anneauPosY=tabOmni[mobil].anneau.getPosition().y+(tabOmni[mobil].directionParam.y*tabOmni[mobil].direction.y);
			if(anneauPosX<defSurface.getPosition().x){
				anneauPosX=defSurface.getPosition().x;
				tabOmni[mobil].setDirectionX(1);
				param=rand_a_b(1, 7);
				tabOmni[mobil].setDirectionParamX(param);
			}
			if(anneauPosX>defSurface.getPosition().x+dtwx-24){
				anneauPosX=defSurface.getPosition().x+dtwx-24;
				tabOmni[mobil].setDirectionX(-1);
				param=rand_a_b(1, 7);
				tabOmni[mobil].setDirectionParamX(param);
			}
			if(anneauPosY<defSurface.getPosition().y){
				anneauPosY=defSurface.getPosition().y;
				tabOmni[mobil].setDirectionY(1);
				param=rand_a_b(1, 7);
				tabOmni[mobil].setDirectionParamY(param);
			}
			if(anneauPosY>defSurface.getPosition().y+dtwy-24){
				anneauPosY=defSurface.getPosition().y+dtwy-24;
				tabOmni[mobil].setDirectionY(-1);
				param=rand_a_b(1, 7);
				tabOmni[mobil].setDirectionParamY(param);
			}
			tabOmni[mobil].anneau.setPosition(anneauPosX,anneauPosY);
			tabOmni[mobil].initComptime();
		}else{
			ct--;
			tabOmni[mobil].setComptime(ct);
		}
		updateGainPave();
	}
}
// ********************************************************************************************************************************
//																gestion des fichiers
// ********************************************************************************************************************************
void metaSurface::saveSurface(bool t){
	string s=userConfig+"/Pad";
	char * cstr = new char [s.length()+1];
   std::strcpy (cstr, s.c_str());
   int ncwd=chdir(cstr);
	string nameFile;
	string wfile;
	int nbcanaux=8;
	string dfx;
	string path=getcwd(NULL,0);
	std::ostringstream ss;
	
	fileSelector.initSelector(path);
	nameFile=fileSelector.selector();
	path=getcwd(NULL,0);
	wfile=path+"/"+nameFile;
	
	std::cout << "path: " << path<< "file :"<<nameFile<< std::endl;
	
	ofstream fichier(wfile, ios::out | ios::trunc);	
	
   if(fichier){
   	fichier<<"padName="<<nameFile<< endl;
   	fichier<<"type="<<surfaceTypeDef<< endl;
   	
   	fichier<<"nameBkgFile="<<nameBkgFile<< endl;
   	fichier<<"pathBkgFile="<<pathBkgFile<< endl;
   	fichier<<"surfaceWidth="<<surfaceN.getSwidth()<< endl;
   	fichier<<"surfaceHeight="<<surfaceN.getSheight()<< endl;
   	fichier<<"editLineColor="<<editLineColor<< endl;
   	fichier<<"editLineThickness="<<thickness << endl;
   	fichier<<"barycentreColor="<<barycentreColor << endl;
   	fichier<<"pointColor="<<pointColor << endl;
   	
   	
   	fichier<<"temporisationMin="<<temporisationMin<< endl;
		fichier<<"temporisationMax="<<temporisationMax<< endl;
		fichier<<"vieMin="<<vieMin<< endl;
		fichier<<"vieMax="<<vieMax<< endl;
		fichier<<"exploseMax="<<exploseMax<< endl;
   	for(int i=0; i<surfaceTypeDef;i++){
   		dfx="";
   		fichier<<"pad="<<i<< endl;
   		fichier<<"dim="<<tabPave[i].getDim()<< endl;
   		fichier<<"fileSound="<<tabPave[i].getFile()<< endl;
   		fichier<<"path="<<tabPave[i].getPath()<< endl;
   		fichier<<"canaux="<<tabPave[i].getNbCanaux()<< endl;
   		fichier<<"daw="<<tabPave[i].getFlagDaw()<< endl;
   		fichier<<"multi="<<tabPave[i].getFlagMulticanaux()<< endl;
   		fichier<<"duree="<<tabPave[i].getDuree()<< endl;
   		fichier<<"track="<<tabPave[i].getTrack()<< endl;
   		fichier<<"Cx="<<tabPave[i].getCx()<< endl;
   		fichier<<"Cy="<<tabPave[i].getCy()<< endl;

   		fichier<<"dimMixer="<<tabPave[i].getDimMixer()<< endl;
   		fichier<<"gainMin="<<tabPave[i].getGainMin()<< endl;
   		fichier<<"gainMax="<<tabPave[i].getGainMax()<< endl;
   		fichier<<"fx="<<tabPave[i].getFx()<< endl;
   		fichier<<"curseurEtat="<<tabPave[i].getCurseurEtat()<< endl;
   		fichier<<"curseurX="<<tabPave[i].getCurseurX()<< endl;
   		fichier<<"curseurY="<<tabPave[i].getCurseurY()<< endl;
   		if(tabPave[i].getFx()==1){
   			std::map<string, int> ls=newPlugin.getListPlugin();
  				std::vector<Plugin::plugin> tabPlug=newPlugin.getTabPlugin();
  				int idnbfx;
	   		for(int j=0;j<12;j++){
	   			if(tabPave[i].idNameFx[j]!=""){
	   				idnbfx=ls.find(tabPave[i].idNameFx[j])->second;
	   				dfx=dfx+tabPlug[idnbfx].nomFx+"(";
	   				for(int k=0;k<tabPlug[idnbfx].nbpar;k++){
	   					dfx=dfx+to_string(tabPave[i].tabUsrPluginParam[j][k].etat)+",";
	   					ss <<tabPave[i].tabUsrPluginParam[j][k].min;
	   					dfx=dfx+ss.str()+",";
	   					ss.clear();
	  						ss.str("");
	  						ss <<tabPave[i].tabUsrPluginParam[j][k].max;
	   					dfx=dfx+ss.str()+",";
	   					ss.clear();
	  						ss.str("");
	  						ss <<tabPave[i].tabUsrPluginParam[j][k].scale;
	   					dfx=dfx+ss.str()+",";
	   					ss.clear();
	  						ss.str("");
	  						ss <<tabPave[i].tabUsrPluginParam[j][k].rev;
	   					dfx=dfx+ss.str()+",";
	   					ss.clear();
	  						ss.str("");
	  					}
	  					dfx=dfx.substr(0,dfx.length()-1);
	  					dfx=dfx+");";
	  				}	
	  			}
	  			dfx=dfx.substr(0,dfx.length()-1);
	   		
   		}
   		fichier<<"listfx="<<dfx<< endl;
   		for(int k=0;k<tabPave[i].getDim();k++){
   			fichier<<"px="<<tabPave[i].getPoint(k).x<< endl;
   			fichier<<"py="<<tabPave[i].getPoint(k).y<< endl;
   		}
   		fichier<<"distanceMax="<<tabPave[i].getDistanceMax()<< endl;
   	}
   	
   fichier.close();
   char commande[255];
	string rcFile=".padPlayer-rc";
	char * cstr = new char [rcFile.length()+1];
	std::strcpy (cstr, rcFile.c_str());
	char* home = getenv("HOME");
	char orig[255];
	snprintf(orig, 255, "%s/%s", home,cstr);
	nameFile=nameFile.substr(0,nameFile.length()-4);
	wfile=path+"/."+nameFile+"-rc";
	char * dest = new char [wfile.length()+1];
	std::strcpy (dest, wfile.c_str());
	snprintf(commande, 255, "%s %s %s ", "cp",orig,dest);
	int pd=system(commande);
	}else{  // sinon
     cerr << "Erreur à l'ouverture du fichier!" << endl;
	} 
	
}
const vector<string> metaSurface::explode(const string& s, const char& c){
	string buff{""};
	vector<string> v;
	
	for(auto n:s)
	{
		if(n != c) buff+=n; else
		if(n == c && buff != "") { v.push_back(buff); buff = ""; }
	}
	if(buff != "") v.push_back(buff);
	
	return v;
}
void metaSurface::openSurface(){
	string s=userConfig+"/Pad";
	char * cstr = new char [s.length()+1];
   std::strcpy (cstr, s.c_str());
   int ncwd=chdir(cstr);
	string nameFile;
	fileSelector.initSelector(getcwd(NULL,0));
	nameFile=fileSelector.selector();
	std::cout <<"path "<<fileSelector.getPath()<<" nameFile "<< nameFile<< std::endl;
	chargeSurface(nameFile);
	
	char commande[255];
	string destFile=".padPlayer-rc";
	char * cs = new char [destFile.length()+1];
	std::strcpy (cs, destFile.c_str());
	char* home = getenv("HOME");
	char dest[255];
	snprintf(dest, 255, "%s/%s", home,cs);
	
	nameFile=nameFile.substr(0,nameFile.length()-4);
	string wfile=fileSelector.getPath()+"/."+nameFile+"-rc";
	char * orig = new char [wfile.length()+1];
	std::strcpy (orig, wfile.c_str());
	snprintf(commande, 255, "%s %s %s ", "cp",orig,dest);
	std::cout <<"commande "<<commande<< std::endl;
	int pd=system(commande);
}
void metaSurface::chargeSurface(string nameFile){	
   string path=getcwd(NULL,0);
   std::cout <<"path "<<getcwd(NULL,0)<<" nameFile "<< nameFile<< std::endl;
   ifstream fichier(nameFile, ios::in);
   string contenu;
	string pf[2];
	string ss1;
	string ss2;
	vector<string> sv;
	vector<string> sp;
	int pt;
	float c1;
	int pad;
	Pave::pluginParam mp;
	int i=0;
   string sparam[12];
  
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
	  			padName=pf[1];
	  			pf[1]="";
  			}
  			if(pf[0]=="type"){
	  			surfaceTypeDef=stoi(pf[1]);
	  			pf[1]="";
  			}
  			
  			if(pf[0]=="nameBkgFile"){
	  			nameBkgFile=pf[1];
	  			pf[1]="";
  			}
  			
  			if(pf[0]=="pathBkgFile"){
	  			pathBkgFile=userConfig+"/surfacesBkg";
	  			pf[1]="";
  			}
  			if(pf[0]=="surfaceWidth"){
	  			surfaceN.setSwidth(stoi(pf[1]));
	  			pf[1]="";
  			}
  			if(pf[0]=="surfaceHeight"){
	  			surfaceN.setSheight(stoi(pf[1]));
	  			pf[1]="";
  			}
  			
  			if(pf[0]=="editLineColor"){
  				editLineColor=pf[1];
  			}
  			if(pf[0]=="editLineThickness"){
  				thickness=stoi(pf[1]);
  			}
  			if(pf[0]=="barycentreColor"){
  				barycentreColor=pf[1];
  			}
  			if(pf[0]=="pointColor"){
  				pointColor==pf[1];
  			}
  			
  			if(pf[0]=="temporisationMin"){
	  			temporisationMin=stoi(pf[1]);
	  			pf[1]="";
  			}
  			if(pf[0]=="temporisationMax"){
	  			temporisationMax=stoi(pf[1]);
	  			pf[1]="";
  			}
  			if(pf[0]=="vieMin"){
	  			vieMin=stoi(pf[1]);
	  			pf[1]="";
  			}
  			if(pf[0]=="vieMax"){
	  			vieMax=stoi(pf[1]);
	  			pf[1]="";
  			}
  			if(pf[0]=="exploseMax"){
	  			exploseMax=stoi(pf[1]);
	  			pf[1]="";
  			}
  			
  			if(pf[0]=="pad"){
	  			pad=stoi(pf[1]);
	  			pt=0;
	  			pf[1]="";
	  		}
	  		if(pf[0]=="dim"){
	  			tabPave[pad].setPaveDim(stoi(pf[1]));
	  			pf[1]="";
	  		}
  			if(pf[0]=="fileSound"){
	  			tabPave[pad].setFile(pf[1]);
	  			pf[1]="";
	  		}
	  		if(pf[0]=="path"){
	  			tabPave[pad].setPath(pf[1]);
	  			pf[1]="";
	  		}
	  		if(pf[0]=="canaux"){
	  			tabPave[pad].setNbCanaux(stoi(pf[1]));
	  			pf[1]="";
	  		}
	  		if(pf[0]=="daw"){
	  			if(pf[1]=="0"){
	  				tabPave[pad].setFlagDawD(0);
	  				defSelectDaw.setTexture(bNoSelect);
	  			}else{
	  				tabPave[pad].setFlagDawD(1);
	  				defSelectDaw.setTexture(bselect);
	  			}
	  			tabPave[pad].setFlagDaw(tabPave[pad].getFlagDawD());
	  			pf[1]="";
	  		}
	  		if(pf[0]=="multi"){
	  			if(pf[1]=="0"){
	  				tabPave[pad].setFlagMulticanauxD(0);
	  				defMulti.setTexture(bNoSelect);
	  			}else{
	  				tabPave[pad].setFlagMulticanauxD(1);
	  				defMulti.setTexture(bselect);
	  			}
	  			tabPave[pad].setFlagMulticanaux(tabPave[pad].getFlagMulticanauxD());
	  			pf[1]="";
	  		}
	  		if(pf[0]=="duree"){
	  			tabPave[pad].setDuree(stof(pf[1]));
	  			pf[1]="";
	  		}
	  		if(pf[0]=="track"){
	  			tabPave[pad].setTrack(stoi(pf[1]));
	  			tabPave[pad].setTrackD(stoi(pf[1]));
	  			pf[1]="";
	  		}
	  		if(pf[0]=="Cx"){
	  			tabPave[pad].setX(stof(pf[1]));
	  			pf[1]="";
	  		}
	  		if(pf[0]=="Cy"){
	  			tabPave[pad].setY(stof(pf[1]));
	  			pf[1]="";
	  		}
	  		if(pf[0]=="dimMixer"){
	  			tabPave[pad].setDimMixer(stof(pf[1]));
	  			tabPave[pad].setDimMixerD(stof(pf[1]));
	  			pf[1]="";
	  		}
	  		if(pf[0]=="gainMin"){
	  			tabPave[pad].setGainMin(stof(pf[1]));
	  			tabPave[pad].setGainMinD(stof(pf[1]));
	  			pf[1]="";
	  		}
	  		if(pf[0]=="gainMax"){
	  			tabPave[pad].setGainMax(stof(pf[1]));
	  			tabPave[pad].setGainMaxD(stof(pf[1]));
	  			pf[1]="";
	  		}
	  		
	  		if(pf[0]=="fx"){
	  			if(pf[1]=="0"){
	  				tabPave[pad].setFx(0);
	  			}else{
	  				tabPave[pad].setFx(1);
	  			}
	  			tabPave[pad].setFxD(tabPave[pad].getFx());
	  			pf[1]="";
	  		}
	  		if(pf[0]=="curseurEtat"){
	  			if(pf[1]=="0"){
	  				tabPave[pad].setCurseurEtat(0);
	  			}else{
	  				tabPave[pad].setCurseurEtat(1);
	  			}
	  			pf[1]="";
	  		}
	  		if(pf[0]=="curseurType"){
	  			tabPave[pad].setCurseurT(stoi(pf[1]));
	  			tabPave[pad].setCurseurTD(stoi(pf[1]));
	  			pf[1]="";
	  		}
	  		if(pf[0]=="curseurX"){
	  			tabPave[pad].setCurseurX(stof(pf[1]));
	  			pf[1]="";
	  		}
	  		if(pf[0]=="curseurY"){
	  			tabPave[pad].setCurseurY(stof(pf[1]));
	  			pf[1]="";
	  		}
	  		
	  		if(pf[0]=="listfx"){
	  			if(pf[1]!=""){
		  			string rfx=pf[1];
		  			sv=explode(pf[1], ';');
		  			for(int k=0;k<sv.size();k++){
		  				std::size_t pos = sv[k].find("(");
		  				ss1=sv[k].substr (0,pos);
		  				tabPave[pad].idNameFx[k]=ss1;
		  				ss2=sv[k].substr (pos+1,sv[k].length()-(pos+2));
						sp=explode(ss2, ',');
						for(int m=0;m<sp.size();m=m+5){
							mp.etat=stoi(sp[m+0]);
							mp.min=stof(sp[m+1]);
							mp.max=stof(sp[m+2]);
							mp.scale=stof(sp[m+3]);
							mp.rev=stoi(sp[m+4]);
							tabPave[pad].tabUsrPluginParam[k].push_back(mp);
						}
						ss1="";
						ss2="";
						sp.clear();
					}
				}
  					
	  		}	
  			if(pf[0]=="px"){
  				c1=stof(pf[1]);
  				pf[1]="";
  			}
  			if(pf[0]=="py"){
  				tabPave[pad].setPoint(pt,sf::Vector2f(c1,stof(pf[1])));
  				pf[1]="";
  				pt++;
  			}
  			if(pf[0]=="distanceMax"){
  			tabPave[pad].setDistanceMax(stof(pf[1]));
  			pf[1]="";
  			}
	  			
	  	}
	  	fichier.close();	
  	}else{  // sinon
     cerr << "Erreur à l'ouverture du fichier!" << endl;
	} 	
	
	std::cout << "fichier chargé" << std::endl;
	//sf::Vector2f vc;
	
	sessionCreateSurface(1)	;
	
}
void metaSurface::sessionCreateSurface(int id){
	stringstream adr;
	nscale=1;
	surface.setSize(sf::Vector2u(920,754));
	defSurface.setTextureRect(sf::IntRect(0, 0, surfaceN.getSwidth(), surfaceN.getSheight()));
	adr << std::fixed <<pathBkgFile<<"/"<<nameBkgFile;
	selectST.loadFromFile(adr.str());
	defSurface.setTexture(selectST);
	adr.clear();
  	adr.str("");
  	float posx=(2100-surfaceN.getSwidth())/2;
  	float posy=(2100-surfaceN.getSheight())/2;
	defSurface.setPosition(sf::Vector2f(posx,posy));
	defSurface.setScale(nscale,nscale);
	bkgSurface.clear(AppBackGround);
	bkgSurface.draw(defSurface);    
	bkgSurface.display();
	surfaceX=700;
	surfaceY=700;
	workspaceSurface.setTextureRect(sf::IntRect(surfaceX, surfaceY, 700,700));
	workspaceSurface.setTexture(&bkgSurface.getTexture(),false);
         
	defSurface2.setTexture(bkgSurface.getTexture());
	defSurface2.setScale(0.071f,0.071f);
	defSurface2.setPosition(sf::Vector2f(0,0));
	navBkgSurface.draw(defSurface2);
	navBkgSurface.display();
	navWorkspaceSurface.setTextureRect(sf::IntRect(0, 0, 150, 150));
	navWorkspaceSurface.setTexture(&navBkgSurface.getTexture(),false);	
	for(int i=0;i<surfaceTypeDef;i++){
	  	updateCurseurPave(i);
	}
	  			
}
int metaSurface::inPolygone(bool mode,Pave &shape, sf::Vector2f p){
	int nbc=shape.getDim();
	sf::Vector2f s1,s2;
	int    wn = 0;    // the  winding number counter
   if(mode==1){
	sf::Vector2f ncoord=normaliseMouseXY(p.x, p.y);
	p.x=ncoord.x;
	p.y=ncoord.y;
	}
	p.x=p.x/nscale;
	p.y=p.y/nscale;			
   shape.setPoint(nbc,shape.getPoint(0));
    for (int i = 0; i<nbc; i++) {   // edge from V[i] to  V[i+1]
    	  s1=shape.getPoint(i);
    	  s2=shape.getPoint(i+1);
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
		   //std::cout << "le point appartient : "<<p.x<<" , "<<p.y<<" , "<<shape.getPoint(i).x<<" , "<<shape.getPoint(i).y<< "  "<<wn<< std::endl;	 
    }
    
	return wn;
	
}
int metaSurface::isLeft(const sf::Vector2f &p0,const sf::Vector2f &p1,const sf::Vector2f &point){
    return ((p1.x - p0.x) * (point.y - p0.y) -
            (point.x - p0.x) * (p1.y - p0.y));
}
sf::Vector2f metaSurface::normaliseMouseXY(float x, float y){
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
// ********************************************************************************************************************************
//																gestion des pavés 
// ********************************************************************************************************************************

int metaSurface::locatePoint(int x, int y,bool mode){
	float lpx=workspaceSurface.getTextureRect().left+(x-200);
	float lpy=workspaceSurface.getTextureRect().top+y-28;
	selectPad=0;
	surfaceMode=mode;
	for(int i=0;i<exploseMax;i++){
		
		if(tabOmni[i].getEtat()==1 && x+workspaceSurface.getTextureRect().left-200>tabOmni[i].anneau.getPosition().x && x+workspaceSurface.getTextureRect().left-200<tabOmni[i].anneau.getPosition().x+24 && y+workspaceSurface.getTextureRect().top-30>tabOmni[i].anneau.getPosition().y && y+workspaceSurface.getTextureRect().top-30<tabOmni[i].anneau.getPosition().y+24){
			omniSelectFlag=1;
			omniSelect=i;
			std::cout <<" anneau : "<<i<< std::endl;
			if(tabOmni[i].getEtat()==1){
		std::cout <<" etat : "<<tabOmni[i].getEtat()<<"   "<< tabOmni[i].anneau.getPosition().x<<"  "<<tabOmni[i].anneau.getPosition().y<< " x : "<<x+workspaceSurface.getTextureRect().left-200<<" y: " <<y+workspaceSurface.getTextureRect().top-30<< std::endl;
		}
			break;
		}
		if(tabOmni[i].getEtat()==1){
		std::cout <<" etat : "<<tabOmni[i].getEtat()<<"   "<< tabOmni[i].anneau.getPosition().x<<"  "<<tabOmni[i].anneau.getPosition().y<< " x : "<<x+workspaceSurface.getTextureRect().left-200<<" y: " <<y+workspaceSurface.getTextureRect().top-30<< std::endl;
		}
   }
   if(omniSelectFlag==0){
		if(lpx<defSurface.getPosition().x || lpx>defSurface.getPosition().x+(surfaceN.getSwidth()*nscale) || lpy<defSurface.getPosition().y || lpy>defSurface.getPosition().y+(surfaceN.getSheight()*nscale)){
			selectPad=0;
		}else{
			for(int i=0;i<surfaceTypeDef;i++){
				int rtp=inPolygone(1,tabPave[i], sf::Vector2f(x,y));
				if(rtp>0){
					std::cout <<" pave inPolygone : "<<i<< std::endl;
					selectPad=i+1;
					padActif=selectPad;
					break;
				}
			}
					
		}	
	}
	if(surfaceMode==1){
		initTPave();
  		winPave.create(sf::VideoMode(308,336), "Pave");
	}
		
	return selectPad;
}
float metaSurface::distanceCentre(float cx, float cy, float x, float y){
	float dt=sqrt(pow(cx-x,2)+pow(cy-y,2));
	return dt;
}
int metaSurface::rand_a_b(int a, int b){
	 //srand(time(NULL));
    return rand()%(b-a) +a;
}


void metaSurface::onClickWinPave(sf::Event e){
	std::cout << "the left button was pressed" << std::endl;
   std::cout << "mouse x: " << e.mouseButton.x << std::endl;
   std::cout << "mouse y: " << e.mouseButton.y << std::endl;
   stringstream adr;
   if(e.mouseButton.x>64 && e.mouseButton.x<214 && e.mouseButton.y>11 && e.mouseButton.y<41){
   	string path=getcwd(NULL,0);
   	//string s=userConfig+"/sounds";
   	string s=path;
	   //char * cstr = new char [s.length()+1];
      //std::strcpy (cstr, s.c_str());
      //int ncwd=chdir(cstr);
   	SF_INFO sfinfo;
		fileSelector.initSelector(s);
		string rtf2=fileSelector.selector();
		path=getcwd(NULL,0);
		tabPave[selectPad-1].setPath(path);
		tabPave[selectPad-1].setFile(rtf2);
		paramFile.setString(rtf2);
		paramFile.setPosition(262-paramFile.getLocalBounds().width-4,18);
		std::cout << "path: " << tabPave[selectPad-1].getPath()<< "file :"<<tabPave[selectPad-1].getFile()<< std::endl;
		string sFileName=tabPave[selectPad-1].getPath()+"/"+tabPave[selectPad-1].getFile();
      const char *dpath=sFileName.c_str();
      SNDFILE* sndfile=sf_open(dpath, SFM_READ, &sfinfo) ;
      sf_close(sndfile) ;
      cout <<path <<" canaux : " << sfinfo.channels<<" Sample rate = "<< sfinfo.samplerate<<" frames : "<<sfinfo.frames<< endl;
      tabPave[selectPad-1].setNbCanaux(sfinfo.channels);
      float nb=(float)sfinfo.frames/sfinfo.samplerate;
      tabPave[selectPad-1].setDuree(nb);
      paramCanaux.setString(to_string(tabPave[selectPad-1].getNbCanaux()));
      paramCanaux.setPosition(296-paramCanaux.getLocalBounds().width-4,65);
      stringstream adr;
  	   adr << std::fixed<< std::setprecision(2)<<tabPave[selectPad-1].getDuree();
      paramDuree.setString(adr.str());
      paramDuree.setPosition(296-paramDuree.getLocalBounds().width-4,100);
      
   }
   
   if(e.mouseButton.x>114 && e.mouseButton.x<130 && e.mouseButton.y>70 && e.mouseButton.y<82){
	 	bool p=tabPave[selectPad-1].getFlagDaw();
	   if(p==1){
	   	tabPave[selectPad-1].setFlagDaw(0);
	   	defSelectDaw.setTexture(bNoSelect);
	   }else{
	   	tabPave[selectPad-1].setFlagDaw(1);
	   	defSelectDaw.setTexture(bselect);
	   }
	 }

   if(e.mouseButton.x>112 && e.mouseButton.x<170  && e.mouseButton.y>126 && e.mouseButton.y<156){
   	paveChampIndex=1;
   	apptxt="";
   	winPaveCurseur.setPosition(170,138);
	 	flagPaveCurseur=1;
	 	clockCurseur.restart();
   }
   if(e.mouseButton.x>112 && e.mouseButton.x<170  && e.mouseButton.y>204 && e.mouseButton.y<224){
   	paveChampIndex=2;
   	apptxt="";
   	winPaveCurseur.setPosition(170,207);
	 	flagPaveCurseur=1;
	 	clockCurseur.restart();
   }
   if(e.mouseButton.x>112 && e.mouseButton.x<170  && e.mouseButton.y>240 && e.mouseButton.y<260){
   	paveChampIndex=3;
   	apptxt="";
   	winPaveCurseur.setPosition(170,242);
	 	flagPaveCurseur=1;
	 	clockCurseur.restart();
   }
   if(e.mouseButton.x>174 && e.mouseButton.x<188 && e.mouseButton.y>135 && e.mouseButton.y<145){
   	float dp=tabPave[selectPad-1].getDimMixer();
   	dp=dp+0.1;
   	if(dp>1.0){
   		dp=1.0;
   	}
   	tabPave[selectPad-1].setDimMixer(dp);
   	adr << std::fixed<< std::setprecision(1)<<dp;
   	paramDimMixer.setString(adr.str());
   	paramDimMixer.setPosition(170-paramDimMixer.getLocalBounds().width-2,135);
   	adr.clear();
		adr.str("");
   }
   if(e.mouseButton.x>174 && e.mouseButton.x<188 && e.mouseButton.y>145 && e.mouseButton.y<155){
   	float dp=tabPave[selectPad-1].getDimMixer();
   	dp=dp-0.1;
   	if(dp<0.1){
   		dp=0.1;
   	}
   	tabPave[selectPad-1].setDimMixer(dp);
   	adr << std::fixed<< std::setprecision(1)<<dp;
   	paramDimMixer.setString(adr.str());
   	paramDimMixer.setPosition(170-paramDimMixer.getLocalBounds().width-2,135);
   	adr.clear();
		adr.str("");
   }
   if(e.mouseButton.x>174 && e.mouseButton.x<188 && e.mouseButton.y>204 && e.mouseButton.y<214){
   	float dp=tabPave[selectPad-1].getGainMin();
   	dp=dp+0.1;
   	if(dp>tabPave[selectPad-1].getGainMax()){
   		dp=tabPave[selectPad-1].getGainMax()-0.1;
   	}
   	tabPave[selectPad-1].setGainMin(dp);
   	adr << std::fixed<< std::setprecision(2)<<dp;
   	paramGainMin.setString(adr.str());
   	paramGainMin.setPosition(170-paramGainMin.getLocalBounds().width-2,205);
   	adr.clear();
		adr.str("");
   }
   if(e.mouseButton.x>174 && e.mouseButton.x<188 && e.mouseButton.y>214 && e.mouseButton.y<224){
   	float dp=tabPave[selectPad-1].getGainMin();
   	dp=dp-0.1;
   	if(dp<0.1){
   		dp=0.1;
   	}
   	tabPave[selectPad-1].setGainMin(dp);
   	adr << std::fixed<< std::setprecision(2)<<dp;
   	paramGainMin.setString(adr.str());
   	paramGainMin.setPosition(170-paramGainMin.getLocalBounds().width-2,205);
   	adr.clear();
		adr.str("");
   }
   if(e.mouseButton.x>174 && e.mouseButton.x<188 && e.mouseButton.y>240 && e.mouseButton.y<250){
   	float dp=tabPave[selectPad-1].getGainMax();
   	dp=dp+0.1;
   	if(dp>2.0){
   		dp=2.0;
   	}
   	tabPave[selectPad-1].setGainMax(dp);
   	adr << std::fixed<< std::setprecision(2)<<dp;
   	paramGainMax.setString(adr.str());
   	paramGainMax.setPosition(170-paramGainMax.getLocalBounds().width-2,240);
   	adr.clear();
		adr.str("");
   }
   if(e.mouseButton.x>174 && e.mouseButton.x<188 && e.mouseButton.y>250 && e.mouseButton.y<260){
   	float dp=tabPave[selectPad-1].getGainMax();
   	dp=dp-0.1;
   	if(dp<tabPave[selectPad-1].getGainMin() ){
   		dp=tabPave[selectPad-1].getGainMin()+0.1;
   	}
   	tabPave[selectPad-1].setGainMax(dp);
   	adr << std::fixed<< std::setprecision(2)<<dp;
   	paramGainMax.setString(adr.str());
   	paramGainMax.setPosition(170-paramGainMax.getLocalBounds().width-2,240);
   	adr.clear();
		adr.str("");
   }
   if(e.mouseButton.x>252 && e.mouseButton.x<280 && e.mouseButton.y>136 && e.mouseButton.y<156){
   	paveChampIndex=5;
   	winPaveCurseur.setPosition(277,139);
	 	flagPaveCurseur=1;
	 	apptxt="";
	 	paramTrack.setString("");
	 	clockCurseur.restart();
   }
   if(e.mouseButton.x>282 && e.mouseButton.x<294 && e.mouseButton.y>136 && e.mouseButton.y<146){
   	string s=paramTrack.getString();
   	int tk=stoi(s);
   	tk=tk+1;
   	if(tk>64){
   		tk=64;
   	}
   	tabPave[selectPad-1].setTrack(tk);
   	paramTrack.setString(to_string(tk));
   }
   if(e.mouseButton.x>282 && e.mouseButton.x<294 && e.mouseButton.y>146 && e.mouseButton.y<156){
   	string s=paramTrack.getString();
   	int tk=stoi(s);
   	tk=tk-1;
   	if(tk<0){
   		tk=0;
   	}
   	tabPave[selectPad-1].setTrack(tk);
   	paramTrack.setString(to_string(tk));
   }
   if(e.mouseButton.x>260 && e.mouseButton.x<274 && e.mouseButton.y>170 && e.mouseButton.y<185){
	 	bool p=tabPave[selectPad-1].getFx();
	   if(p==1){
	   	tabPave[selectPad-1].setFx(0);
	   	fxSelect.setTexture(bNoSelect);
	   }else{
	   	tabPave[selectPad-1].setFx(1);
	   	fxSelect.setTexture(bselect);
	   }
	 }
	if(tabPave[selectPad-1].getFx()==1 && e.mouseButton.x>252 && e.mouseButton.x<285 && e.mouseButton.y>194 && e.mouseButton.y<225){
		initTPaveFx();
		if(tabPave[selectPad-1].fxcanal==1){
    	 fxcanalB.setTexture(bselect);
   	}else{
    	 fxcanalB.setTexture(bNoSelect);
    	}
	 	winFX.create(sf::VideoMode(270, 480), "FX");
	}
	if(e.mouseButton.x>256 && e.mouseButton.x<280 && e.mouseButton.y>238 && e.mouseButton.y<262){
	 	selectType.create(sf::VideoMode(474,128), "Type");
	}
	if(e.mouseButton.x>24 && e.mouseButton.x<80 && e.mouseButton.y>296 && e.mouseButton.y<325){
	 	defTPave();
	}
	if(e.mouseButton.x>185 && e.mouseButton.x<241 && e.mouseButton.y>296 && e.mouseButton.y<325){
	 	surfaceMode=0;
	 	winPave.close();
	}
	if(e.mouseButton.x>246 && e.mouseButton.x<295 && e.mouseButton.y>296 && e.mouseButton.y<325){
	 	surfaceMode=0;
	 	paveValider();
	  	winPave.close();
	}
	if(e.mouseButton.x>278 && e.mouseButton.x<296 && e.mouseButton.y>8 && e.mouseButton.y<28){
	 	testFileDSP("");
	}
	if(e.mouseButton.x>278 && e.mouseButton.x<296 && e.mouseButton.y>32 && e.mouseButton.y<52){
   	tabPave[selectPad-1].setFile("");
   	paramFile.setString("");
   	tabPave[selectPad-1].setNbCanaux(0);
   	paramCanaux.setString("0");
      paramCanaux.setPosition(296-paramCanaux.getLocalBounds().width-4,65);
      tabPave[selectPad-1].setDuree(0);
      paramDuree.setString("0");
      paramDuree.setPosition(296-paramDuree.getLocalBounds().width-4,100);
   }
	if(e.mouseButton.x>114 && e.mouseButton.x<130 && e.mouseButton.y>172 && e.mouseButton.y<188){
	 	if(tabPave[selectPad-1].getMixgain()==1){
	 		tabPave[selectPad-1].setMixgain(0);
	 		defSelectGain.setTexture(bNoSelect);
	 	}else{
	 		tabPave[selectPad-1].setMixgain(1);
	 		defSelectGain.setTexture(bselect);
	 	}
	}
	if(e.mouseButton.x>116 && e.mouseButton.x<130 && e.mouseButton.y>104 && e.mouseButton.y<116){
	 	if(tabPave[selectPad-1].getFlagMulticanaux()==1){
	 		tabPave[selectPad-1].setFlagMulticanaux(0);
	 		defMulti.setTexture(bNoSelect);
	 	}else{
	 		tabPave[selectPad-1].setFlagMulticanaux(1);
	 		defMulti.setTexture(bselect);
	 	}
	}
}
void metaSurface::onMouseMoveWinPave(sf::Event e){
	std::cout << "mouse x: " << e.mouseMove.x << std::endl;
   std::cout << "mouse y: " << e.mouseMove.y << std::endl;
   string ds;
   stringstream adr;
   newInfo.setInfoTxtSize(13);
   newInfo.setInfoTxtFillColor(sf::Color(0,0,0,255));
	if(flagTxt==1 && e.mouseMove.x>122 && e.mouseMove.x<354 && e.mouseMove.y>60 && e.mouseMove.y<262){
   	int dy=(e.mouseButton.y-64)/32.6;
   	if(dy!=paveChampIndex){
   		switch (paveChampIndex){
	       		case 1:
	       			ds=paramDimMixer.getString();
		   			if(stof(ds)<0 || stof(ds)>30){
		   				std::cout << "erreur " << std::endl;
		   				newInfo.setTxt(1,"0 < Ro < 40");
		   				bool rt=newInfo.drawInfo(5, "Alerte");
		   				flagTxt=0;
		  					adr << std::fixed<< std::setprecision(2)<<tabPave[selectPad-1].getDimMixer();
		   			}else{
		   				adr << std::fixed<< std::setprecision(2)<<stof(ds);
		   			}
		   			paramDimMixer.setString(adr.str());
		   			adr.clear();
		  				adr.str("");
						paramDimMixer.setPosition(174-paramDimMixer.getLocalBounds().width-2,135);
	       			break;
	       		case 2:
	       			ds=paramGainMin.getString();
		   			if(stof(ds)<0 || stof(ds)>1){
		   				std::cout << "erreur " << std::endl;
		   				newInfo.setTxt(1,"0 < Gain min < 1");
		   				bool rt=newInfo.drawInfo(5, "Alerte");
		   				flagTxt=0;
		  					adr << std::fixed<< std::setprecision(2)<<tabPave[selectPad-1].getGainMin();
		   			}else{
		   				adr << std::fixed<< std::setprecision(2)<<stof(ds);
		   			}
		   			paramGainMin.setString(adr.str());
		   			adr.clear();
		  				adr.str("");
						paramGainMin.setPosition(174-paramGainMin.getLocalBounds().width-2,205);
	       			break;
	       		case 3:
	       			ds=paramGainMax.getString();
		   			if(stof(ds)<0 || stof(ds)>2){
		   				std::cout << "erreur " << std::endl;
		   				newInfo.setTxt(1,"1 < Gain Max < 2");
		   				bool rt=newInfo.drawInfo(5, "Alerte");
		   				flagTxt=0;
		  					adr << std::fixed<< std::setprecision(2)<<tabPave[selectPad-1].getGainMax();
		   			}else{
		   				adr << std::fixed<< std::setprecision(2)<<stof(ds);
		   			}
		   			paramGainMax.setString(adr.str());
		   			adr.clear();
		  				adr.str("");
						paramGainMax.setPosition(174-paramGainMax.getLocalBounds().width-2,240);
	       			break;
	       		case 5:
	       			ds=paramTrack.getString();
		   			if(stof(ds)<0 || stof(ds)>64){
		   				std::cout << "erreur " << std::endl;
		   				newInfo.setTxt(1,"1 < Track < 64");
		   				bool rt=newInfo.drawInfo(0, "Alerte");
		   				flagTxt=0;
		  					adr << std::fixed<< std::setprecision(0)<<tabPave[selectPad-1].getTrack();
		   			}else{
		   				adr << std::fixed<< std::setprecision(0)<<stof(ds);
		   			}
		   			paramTrack.setString(adr.str());
		   			adr.clear();
		  				adr.str("");
						paramTrack.setPosition(276-paramTrack.getLocalBounds().width-2,136);
	       		default:
	       		break;
	      }
	   }
	}
}
void metaSurface::onMouseUpWinPave(sf::Event e){
}

void metaSurface::onClickType(sf::Event e){
   std::cout << "the left button was pressed" << std::endl;
   std::cout << "mouse x4: " << e.mouseButton.x << std::endl;
   std::cout << "mouse y4: " << e.mouseButton.y << std::endl;
   int h=e.mouseButton.x/60;
   int v=e.mouseButton.y/32;
   tabPave[selectPad-1].setCurseurT((v*8)+h);
}

void metaSurface::initTPave(){
	 stringstream adr;
	 float s;
	 paramFile.setString(tabPave[selectPad-1].getFile());
	 paramFile.setPosition(262-paramFile.getLocalBounds().width-4,18);
	 if(tabPave[selectPad-1].getFlagDaw()==0){
	 	defSelectDaw.setTexture(bNoSelect);
	 }else{
	 	defSelectDaw.setTexture(bselect);
	 }
	 adr << std::fixed<< std::setprecision(2)<<tabPave[selectPad-1].getDimMixer();
	 paramDimMixer.setString(adr.str());
	 paramDimMixer.setPosition(170- paramDimMixer.getLocalBounds().width-2,135);
	 adr.clear();
	 adr.str("");
	 adr << std::fixed<< std::setprecision(2)<<tabPave[selectPad-1].getGainMin();
	 paramGainMin.setString(adr.str());
	 paramGainMin.setPosition(172- paramGainMin.getLocalBounds().width-2,205);
	 adr.clear();
	 adr.str("");
	 adr << std::fixed<< std::setprecision(2)<<tabPave[selectPad-1].getGainMax();
	 paramGainMax.setString(adr.str());
	 paramGainMax.setPosition(172- paramGainMax.getLocalBounds().width-2,240);
	 adr.clear();
	 adr.str("");
	 paramTrack.setString(to_string(tabPave[selectPad-1].getTrack()));
	 paramTrack.setPosition(276- paramTrack.getLocalBounds().width-2,136);
	 adr << std::fixed<< std::setprecision(2)<<tabPave[selectPad-1].getDuree();
	 paramCanaux.setString(adr.str());
	 paramCanaux.setPosition(294- paramCanaux.getLocalBounds().width-2,100);
	 adr.clear();
	 adr.str("");
	 paramDuree.setString(to_string(tabPave[selectPad-1].getNbCanaux()));
	 paramDuree.setPosition(294- paramDuree.getLocalBounds().width-2,64);
	 if(tabPave[selectPad-1].getFlagMulticanaux()==0){
	 	defMulti.setTexture(bNoSelect);
	 }else{
	 	defMulti.setTexture(bselect);
	 }
	 if(tabPave[selectPad-1].getMixgain()==0){
	 	defSelectGain.setTexture(bNoSelect);
	 }else{
	 	defSelectGain.setTexture(bselect);
	 }
	 if(tabPave[selectPad-1].getFx()==0){
	 	fxSelect.setTexture(bNoSelect);
	 }else{
	 	fxSelect.setTexture(bselect);
	 }
}
void metaSurface::defTPave(){
	 stringstream adr;
	 float s;
	 paramFile.setString("");
	 tabPave[selectPad].setFlagDaw(0);
	 defSelectDaw.setTexture(bNoSelect);
	 adr << std::fixed<< std::setprecision(2)<<tabPave[selectPad-1].getDimMixerD();
	 paramDimMixer.setString(adr.str());
	 paramDimMixer.setPosition(170- paramDimMixer.getLocalBounds().width-2,135);
	 adr.clear();
	 adr.str("");
	 tabPave[selectPad].setMixgain(1);
	 defSelectGain.setTexture(bselect);
	 adr << std::fixed<< std::setprecision(2)<<tabPave[selectPad-1].getGainMinD();
	 paramGainMin.setString(adr.str());
	 paramGainMin.setPosition(172- paramGainMin.getLocalBounds().width-2,205);
	 adr.clear();
	 adr.str("");
	 adr << std::fixed<< std::setprecision(2)<<tabPave[selectPad-1].getGainMaxD();
	 paramGainMax.setString(adr.str());
	 paramGainMax.setPosition(172- paramGainMax.getLocalBounds().width-2,240);
	 adr.clear();
	 adr.str("");
	 paramCanaux.setString("");
	 paramDuree.setString("");
	 paramTrack.setString("0");
	 tabPave[selectPad].setFx(0);
	 fxSelect.setTexture(bNoSelect);
}
void metaSurface::paveValider(){
	string s;
	s=paramDimMixer.getString();
	tabPave[selectPad-1].setDimMixer(stof(s));
	s=paramGainMin.getString();
	tabPave[selectPad-1].setGainMin(stof(s));
	s=paramGainMax.getString();
	tabPave[selectPad-1].setGainMax(stof(s));
	s=paramTrack.getString();
	tabPave[selectPad-1].setTrack(stoi(s));
}
void metaSurface::newPaveText(sf::Event e){
   int key=e.key.code;
   stringstream adr;
   if (e.text.unicode < 128){
		if(key==8){
	      apptxt=apptxt.substr(0,apptxt.length()-1);
	 	}else{
			apptxt=apptxt+static_cast<char>(e.text.unicode);
			flagTxt=1;
		}
		switch (paveChampIndex){
       		case 1:
       			adr << std::fixed<< std::setprecision(2)<<apptxt;
       			paramDimMixer.setString(adr.str());
       			paramDimMixer.setPosition(170-paramDimMixer.getLocalBounds().width-2,135);
       			break;
       		case 2:
       			adr << std::fixed<< std::setprecision(2)<<apptxt;
       			paramGainMin.setString(adr.str());
       			paramGainMin.setPosition(172-paramGainMin.getLocalBounds().width-2,205);
       			break;
       		case 3:
       			adr << std::fixed<< std::setprecision(2)<<apptxt;
       			paramGainMax.setString(adr.str());
       			paramGainMax.setPosition(172-paramGainMax.getLocalBounds().width-2,240);
       			break;
       		case 5:
       			adr << std::fixed<< std::setprecision(1)<<apptxt;
       			paramTrack.setString(adr.str());
       			paramTrack.setPosition(276-paramTrack.getLocalBounds().width-2,136);
       			break;
       		default:
       			break;
	    }
	    
   }
   adr.clear();
  	adr.str(""); 
}
// ********************************************************************************************************************************
//																gestion FX
// ********************************************************************************************************************************
void metaSurface::defListPlugin(){
	std::map<string, int> ls=newPlugin.getListPlugin();
  	std::map<string, int>::iterator it = ls.begin();
   for(int k=0;k<indexList;k++){
  	  	it++;
  	}
  	int k=0;
  	int max=ls.size()-indexList;
  	int nb;
  	if(max<15){
  		nb=max;
  	}else{
  		nb=15;
  	}
  	for(int i=0;i<15;i++){
  		labelFx[i].setString("");
  	}
  	while (k<nb){
	  		std::cout <<" ls.size() "<<ls.size()<< " nb "<<nb<<"  "<< it->first <<" , " <<it->second<< std::endl;
	  		labelFx[k].setString(it->first);
	  		k++;
	  		it++;
   }
   nb=shapeFxSlider.getSize().y-ls.size()+15;
   if(nb>10){
   	shapeFxMSlider.setSize(sf::Vector2f(shapeFxMSlider.getSize().x,nb));
   }
}
void metaSurface::mouseFxWheel(sf::Event e){
  std::map<string, int> ls=newPlugin.getListPlugin();
  int nposy;
  if(e.mouseWheelScroll.x>shapeFxSel.getPosition().x && e.mouseWheelScroll.x<shapeFxSel.getPosition().x+shapeFxSel.getSize().x && e.mouseWheelScroll.y>shapeFxSel.getPosition().y&& e.mouseWheelScroll.y<shapeFxSel.getPosition().x+shapeFxSel.getSize().y){
	  if (e.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel){
		if(e.mouseWheelScroll.delta==1){
			indexList=indexList-1;
			if(indexList<1){
			 	indexList=0;
			 	nposy=0;
			}else{
				nposy=-1;
			} 	
		}else{
			indexList=indexList+1;
			if(indexList>ls.size()-15){
			 	indexList=ls.size()-15;
			 	nposy=0;
			}else{
				nposy=1;
			}
		}
		defListPlugin();
	  }
	  shapeFxMSlider.setPosition(shapeFxMSlider.getPosition().x,shapeFxMSlider.getPosition().y+nposy);
  }
}
void metaSurface::onClickWinFx(sf::Event e){
	std::cout << "the left button was pressed" << std::endl;
   std::cout << "mouse x: " << e.mouseButton.x << std::endl;
   std::cout << "mouse y: " << e.mouseButton.y << std::endl;
   if(e.mouseButton.x>180 && e.mouseButton.x<194 && e.mouseButton.y>12 && e.mouseButton.y<402){
   	chaineFxSelect=e.mouseButton.y/34;
   	std::cout << "shapFxEdit1: " << shapFxEdit<< std::endl;
   	if(shapFxEdit==0){
		  shapeFxSel.setPosition(sf::Vector2f(38, 32));
		  for(int i=0;i<15;i++){
		  	labelFx[i].setPosition(42,34+(i*20));
		  }
		  shapFxEdit=1;
		  defListPlugin();
		}
   }
   if(shapFxEdit==1 && e.mouseButton.x>38 && e.mouseButton.x<154 && e.mouseButton.y>35 && e.mouseButton.y<334){
   	 std::map<string, int> ls=newPlugin.getListPlugin();
  		 std::vector<Plugin::plugin> tabPlug=newPlugin.getTabPlugin();
  		 int idnbfx=ls.find(labelFx[rtfx].getString())->second;
   	 txtFx[chaineFxSelect].setString(labelFx[rtfx].getString());
   	 std::cout << "chaineFxSelect: " << chaineFxSelect<<"rtfx"<<rtfx<< std::endl;
   	 tabPave[selectPad-1].idfx[chaineFxSelect]=rtfx;
   	 tabPave[selectPad-1].idNameFx[chaineFxSelect]=txtFx[chaineFxSelect].getString();
   	 if(tabPlug[idnbfx].nbpar>0){
	   	 tabPave[selectPad-1].tabUsrPluginParam[chaineFxSelect].clear();
	   	 Pave::pluginParam pvparplug;
	   	 pvparplug.etat=0;
			 pvparplug.scale=1;
			 pvparplug.rev=0;
			 for(int i=0;i<tabPlug[idnbfx].nbpar;i++){
			 	pvparplug.min=tabPlug[idnbfx].param[i].min;
			 	pvparplug.max=tabPlug[idnbfx].param[i].max;
			 	pvparplug.mod=tabPlug[idnbfx].param[i].mod;
			 	tabPave[selectPad-1].tabUsrPluginParam[chaineFxSelect].push_back(pvparplug);
			 	std::cout <<"min "<<tabPave[selectPad-1].tabUsrPluginParam[chaineFxSelect][i].min<< std::endl;
			 }
			 std::cout <<"name "<<tabPlug[idnbfx].nomFx <<" tabPlug[idnbfx].nbpar "<<tabPlug[idnbfx].nbpar<< " size: " <<  tabPave[selectPad-1].tabUsrPluginParam[chaineFxSelect][0].etat<< std::endl;
			 std::cout <<"nom "<<tabPave[selectPad-1].idNameFx[chaineFxSelect]<< std::endl;
		 }   	 
   	 shapFxEdit=0;
   }
   if(shapFxEdit==1 && e.mouseButton.x>shapeFxMSlider.getPosition().x && e.mouseButton.x<shapeFxMSlider.getPosition().x+shapeFxMSlider.getSize().x && e.mouseButton.y>shapeFxMSlider.getPosition().y && e.mouseButton.y<shapeFxMSlider.getPosition().y+shapeFxMSlider.getSize().y){
   	flagFxMSlider=1;
   	FxMdY=e.mouseButton.y;
   }
   if(e.mouseButton.x>204 && e.mouseButton.x<228 && e.mouseButton.y>12 && e.mouseButton.y<402){
   	int plugin=(e.mouseButton.y-12)/33;
   	std::cout << "selectPad: " << selectPad-1<< "plugin: " << plugin<< std::endl;
   	std::map<string, int> ls=newPlugin.getListPlugin();
  		std::vector<Plugin::plugin> tabPlug=newPlugin.getTabPlugin();
  		int idnbfx=ls.find(tabPave[selectPad-1].idNameFx[plugin])->second;
  		ContraintesFx ctrlFx(ref);
  		std::cout << "selectPad: " << selectPad-1<< "plugin: " << plugin<< " name: " << tabPave[selectPad-1].idNameFx[plugin]<<" tabPlug.size "<<tabPlug[idnbfx].nbpar<< std::endl;
  		if(tabPlug[idnbfx].nbpar>0){
   		ctrlFx.drawContraintesFx(newPlugin,idnbfx,&tabPave[selectPad-1], plugin,newPlugin.getEditMode());
   		newPlugin.setEditMode(0);
   		std::cout << "selectPad: " << selectPad-1<< "plugin: " << plugin<< "name: " << tabPave[selectPad-1].idNameFx[plugin]<< std::endl;
   		for(int i=0;i<tabPlug[idnbfx].nbpar;i++){
   		std::cout << "tabPave[selectPad-1].tabPluginParam[plugin].etat"<<tabPave[selectPad-1].tabUsrPluginParam[plugin][i].etat<< std::endl;
   		}
   	//winPlugin[idfx[plugin]].create(sf::VideoMode(270, 310), txtFx[idfx].getString());
   	}
   }
   if(e.mouseButton.x>24 && e.mouseButton.x<44 && e.mouseButton.y>414 && e.mouseButton.y<434){
     testFxDSP("");
   }
   if(e.mouseButton.x>130 && e.mouseButton.x<145 && e.mouseButton.y>417 && e.mouseButton.y<432){
   	if(tabPave[selectPad-1].fxcanal==0){
    	 tabPave[selectPad-1].fxcanal=1;
    	 fxcanalB.setTexture(bselect);
    	}else{
    	 tabPave[selectPad-1].fxcanal=0;
    	 fxcanalB.setTexture(bNoSelect);
    	}
   }
   if(e.mouseButton.x>232 && e.mouseButton.x<245 && e.mouseButton.y>417 && e.mouseButton.y<432){
   	if(tabPave[selectPad-1].fxSpectrum==0){
    	 tabPave[selectPad-1].fxSpectrum=1;
    	 fxcanalSpect.setTexture(bselect);
    	}else{
    	 tabPave[selectPad-1].fxSpectrum=0;
    	 fxcanalSpect.setTexture(bNoSelect);
    	}
   }
   if(e.mouseButton.x>199 && e.mouseButton.x<249 && e.mouseButton.y>444 && e.mouseButton.y<472){
     tabPave[selectPad-1].rtfx=0;
     winFX.close();
   }
   if(e.mouseButton.x>19 && e.mouseButton.x<50 && e.mouseButton.y>444 && e.mouseButton.y<472){
     for(int i=0;i<12;i++){
     		tabPave[selectPad-1].idfx[i]=0;
     		txtFx[i].setString("");
     }
   }
   if(e.mouseButton.x>54 && e.mouseButton.x<110 && e.mouseButton.y>444 && e.mouseButton.y<472){
     for(int k=0;k<surfaceTypeDef;k++){
	     for(int i=0;i<12;i++){
	     	if(k!=selectPad-1){
	     		tabPave[k].idfx[i]=tabPave[selectPad-1].idfx[i];
	     	}
	     }
	     tabPave[k].setFx(1);
     }
   }
}
void metaSurface::onMouseMoveWinFx(sf::Event e){
	std::cout << "mouse x: " << e.mouseMove.x << std::endl;
   std::cout << "mouse y: " << e.mouseMove.y << std::endl;
   if(shapFxEdit==1 && e.mouseMove.x>38 && e.mouseMove.x<160 && e.mouseMove.y>35 && e.mouseMove.y<334){
   	int id=(e.mouseMove.y-32)/20;
   	 std::cout << "id: " << id << std::endl;
   	rtfx=id;
   	float y=(id*20)+32;
   	selectShapFxSel.setPosition(sf::Vector2f(38, y));
  }
  if(e.mouseMove.x<38 || e.mouseMove.x>242 || e.mouseMove.y<10 || e.mouseMove.y>400){
   	shapFxEdit=0;
  }
  if (flagFxMSlider==1 && e.mouseMove.x > shapeFxMSlider.getPosition().x && e.mouseMove.x<shapeFxMSlider.getPosition().x+shapeFxMSlider.getSize().x && e.mouseMove.y > shapeFxMSlider.getPosition().y && e.mouseMove.y<shapeFxMSlider.getPosition().y+shapeFxMSlider.getSize().y){ 
     std::map<string, int> ls=newPlugin.getListPlugin();	
     int nposy=shapeFxMSlider.getPosition().y+(e.mouseMove.y-FxMdY);
     if(e.mouseMove.y<FxMdY){
     	indexList=indexList-1;
     	if(indexList<1){
     		indexList=0;
     	}
     }else{
     	indexList=indexList+1;
     	if(indexList>ls.size()-15){
     		indexList=ls.size()-15;
     	}
     }
     if(nposy<shapeFxSlider.getPosition().y+1){
   		nposy=shapeFxSlider.getPosition().y+1;
     }
     if(nposy+shapeFxMSlider.getSize().y>shapeFxSlider.getPosition().y+shapeFxSlider.getSize().y){
   		nposy=(shapeFxSlider.getPosition().y+shapeFxSlider.getSize().y)-shapeFxMSlider.getSize().y;
     }
     shapeFxMSlider.setPosition(shapeFxMSlider.getPosition().x,nposy);
     FxMdY=e.mouseMove.y; 
     defListPlugin();
  }
}
void metaSurface::onMouseUpWinFx(sf::Event e){
	flagFxMSlider=0;
}
void metaSurface::initTPaveFx(){
	for(int i=0;i<12;i++){
		txtFx[i].setString(tabPave[selectPad-1].idNameFx[i]);
	}
}


// ********************************************************************************************************************************
//																Faust DSP
// ********************************************************************************************************************************
bool metaSurface::testFileDSP(string st1){
  SF_INFO sfinfo;
  string sFileName=tabPave[selectPad-1].getPath()+"/"+tabPave[selectPad-1].getFile();
  const char *path=sFileName.c_str();

  SNDFILE* sndfile=sf_open(path, SFM_READ, &sfinfo) ;
  sf_close(sndfile) ;
  cout <<path <<" canaux : " << sfinfo.channels<<" Sample rate = "<< sfinfo.samplerate<<" frames : "<<sfinfo.frames<< endl;
  string nameFile="simplePlayer.dsp";
  if(sfinfo.channels>1){
  string prog;
  prog=prog+"import(\""+ref->getDossierConfig()+"/faust/stdfaust.lib\");";
  prog=prog+"import(\""+ref->getDossierConfig()+"/faust/soundfiles2.lib\");";
  prog=prog+"ds=soundfile(\"[url:{\'"+path+"\'}]\","+to_string(sfinfo.channels)+");";
  prog=prog+"vmeter(x)= attach(x, envelop(x) : vbargraph(\"[2][unit:dB]\", -70, +5));";
  prog=prog+"envelop = abs : max ~ -(1.0/ma.SR) : max(ba.db2linear(-70)) : ba.linear2db;";
  prog=prog+"sample1 = so.sound(ds, 0);";
  prog=prog+"gain = vslider(\"[0]gain\",0.1,0,2,0.01) : si.smoo;";
  prog=prog+"gate = button(\"[1]gate\");";
  prog=prog+"gdec(x) = hgroup(\"Player\",x);";
  prog=prog+"tdec(x) = gdec(vgroup(\"[1]\",x));";
  prog=prog+"lect(x) = gdec(hgroup(\"[2]\",x));";
  prog=prog+"lgain=tdec(gain);";
  prog=prog+"lgate=tdec(gate);";
  prog=prog+"lmet=lect(par(j,"+to_string(sfinfo.channels)+",hgroup(\"c%2j\",vmeter)));";
  prog=prog+"smp1 = display_progress(sample1.play_progress(lgain,lgate)):lmet;";
  prog=prog+"process = smp1;";
  cout <<path <<" prog : " << prog<< endl;
  createDSP(prog, st1);
  }
}

void metaSurface::createDSP(std::string localDsp, string st1){
  char name[256];
  char nameAudio[256];
  char rcfilename[256];
  char* home = getenv("HOME");
  string s = "padPlayer.dsp";
  char filename[s.length() + 1];
  strcpy(filename, s.c_str());
  snprintf(name, 255, "%s","Padplayer");
  //snprintf(nameAudio, 255, "%s", basename(path);
  snprintf(rcfilename, 255, "%s/.%s-rc", home, name);
  std::cout << "name : " << name<<"filename "<<filename<<"rcfilename "<<rcfilename<< std::endl;
  
  bool is_osc;
  if(st1=="-osc"){
    is_osc = 1;
  }else{
  	 is_osc = 0;
  }
    
  dsp_factory* factory = nullptr;
  dsp* DSP = nullptr;
  MidiUI* midiinterface = nullptr;
  jackaudio_midi audio;
  GUI* oscinterface = nullptr;
  string error_msg;
    
  cout << "Libfaust version : " << getCLibFaustVersion () << endl;
  
  factory = createDSPFactoryFromString(filename,localDsp, 0,NULL, "", error_msg, -1);
  if (!factory) {
     cerr << "Cannot create factory : " << error_msg;
     exit(EXIT_FAILURE);
  }
  std::cout << "Factory : " << factory<< std::endl;
  cout << "getCompileOptions " << factory->getCompileOptions() << endl;
  
  DSP = factory->createDSPInstance();
  if (!DSP) {
     cerr << "Cannot create instance "<< endl;
     exit(EXIT_FAILURE);
  }
  GUI* interface = new GTKUI(filename,0,NULL);
  DSP->buildUserInterface(interface);
  FUI* finterface = new FUI();
  DSP->buildUserInterface(finterface);
  SoundUI* soundinterface = new SoundUI();
  DSP->buildUserInterface(soundinterface);
  
  if (is_osc) {
  	 int argc1=5;
  	 char* argv1[64];
  	 argv1[0]=filename;
  	 argv1[1]=(char*)"-xmit";
  	 argv1[2]=(char*)"0";
  	 //cout <<argv1[0]<<argv1[1] << " : " << argv1[2]<< endl;
  	 argv1[3]=(char*)"-port";
  	 string s=to_string(ref->getOSC());
  	 argv1[4]=(char*)s.c_str();//"5540"
  	 cout << "osc " << argv1[4] << endl;
    oscinterface = new OSCUI(filename,argc1,argv1);
    DSP->buildUserInterface(oscinterface);
  }

  if (!audio.init(basename(filename), DSP)) {
     cout << "audio.init : " << 0<< endl;
  }
  finterface->recallState(rcfilename);
  audio.start();

  if (is_osc) {
  		oscinterface->run();
  }
  
  interface->run();
  
  audio.stop();
  
  finterface->saveState(rcfilename);
  
  delete DSP;
  delete interface;
  delete finterface;
  delete oscinterface;
  delete soundinterface;
  
  deleteDSPFactory(static_cast<llvm_dsp_factory*>(factory));

}
void metaSurface::testFxDSP(string st1){
  int nbcanaux=tabPave[selectPad-1].getNbCanaux();
  string sFileName=tabPave[selectPad-1].getPath()+"/"+tabPave[selectPad-1].getFile();
  const char *path=sFileName.c_str();
  int nbfx=0;
  if(tabPave[selectPad-1].fxcanal==0){
  	modeDsp=1;
  }else{
  	modeDsp=2;
  }
  for(int i=0;i<12;i++){
  	if(tabPave[selectPad-1].idNameFx[i]!=""){
  		nbfx++;
  	}
  }
  int nbctrl=0;
  int idnbfx;
  map<string,string> lstPlugins;
  std::map<string, int> ls=newPlugin.getListPlugin();
  std::vector<Plugin::plugin> tabPlug=newPlugin.getTabPlugin();
  
  for(int i=0;i<12;i++){
  		int idnbfx=ls.find(tabPave[selectPad-1].idNameFx[i])->second;
  		if(tabPave[selectPad-1].idNameFx[i]!="" && tabPlug[idnbfx].type==1){
  			 cout <<" plugin : " << tabPave[selectPad-1].idNameFx[i]<<" type : "<<tabPlug[idnbfx].type<< endl;
  			 lstPlugins.insert(std::pair<string, string>(tabPave[selectPad-1].idNameFx[i],tabPlug[idnbfx].fx));
  		}	
  }
  if(nbcanaux>1 && nbfx>0){
	  string prog;
	  
	  prog=prog+"import(\""+ref->getDossierConfig()+"/faust/stdfaust.lib\");\n";
	  prog=prog+"import(\""+ref->getDossierConfig()+"/faust/soundfiles2.lib\");\n";
	  prog=prog+"import(\""+ref->getDossierConfig()+"/faust/metaSurfaceFaust.lib\");\n";
	  std::map<string, string>::iterator it;
	  for(it=lstPlugins.begin();it!=lstPlugins.end();it++){
	  		 prog=prog+"import(\""+ref->getDossierUser()+"/Plugins/"+it->first+".lib\");\n";
	  }
	  
	  prog=prog+"ds=soundfile(\"[url:{\'"+path+"\'}]\","+to_string(nbcanaux)+");\n";
	  prog=prog+"vmeter(i,x)= attach(x, envelop(x) : vbargraph(\"%2i[2][unit:dB]\", -70, +5));\n";
	  prog=prog+"envelop = abs : max ~ -(1.0/ma.SR) : max(ba.db2linear(-70)) : ba.linear2db;\n";
	  prog=prog+"sample1 = so.sound(ds, 0);\n";
	  prog=prog+"sgain = vslider(\"[0]gain\",0.1,0,2,0.01) : si.smoo;\n";
	  prog=prog+"sspeed=vslider(\"[1]speed\",1.0,0.1,3,0.01) : si.smoo;\n";
	  prog=prog+"lect2(x)=hgroup(\"\",x);\n";
	  prog=prog+"lect3(x)=hgroup(\"FX\",x);\n";
	  prog=prog+"tdec(x)=lect2(hgroup(\"[1]\",x));\n";
	  prog=prog+"lect(x)=lect2(hgroup(\"[2]\",x));\n";
	  prog=prog+"lgain=tdec(sgain);\n";
	  prog=prog+"lspeed=tdec(sspeed);\n";

	  prog=prog+"lmet=lect(par(j,"+to_string(nbcanaux)+",hgroup(\"\",vmeter(j))));\n";  
	  
	  int k=0;
	  int di=0;
	  if(tabPave[selectPad-1].fxcanal==0){
		  if(nbfx<4){
		  	 prog=prog+"base=hgroup(\" \",hgroup(\"[0] \",vgroup(\"[0] Player\",display_progress(sample1.loop_speed_level_progress(lspeed,lgain)):lmet):hgroup(\"[2]\",par(j,"+to_string(nbcanaux)+",";
		  	 for(int i=0;i<12;i++){
		  	 	if(tabPave[selectPad-1].idNameFx[i]!="" && tabPave[selectPad-1].idNameFx[i]!="Speed"){
		  	 		if(tabPave[selectPad-1].idNameFx[i]=="Mixer"){
		  	 			prog=prog+"hgroup(\"["+to_string(i)+"]MIXER\",mixer(j)):";
		  	 		}else{
		  	 			idnbfx=ls.find(tabPave[selectPad-1].idNameFx[i])->second;
						prog=prog+"hgroup(\"["+to_string(i)+"]\","+tabPlug[idnbfx].fx+"):";
		  	 		}
		  	 	}
		  	 }
		  	 prog=prog.substr(0,prog.length()-1);
		  	 prog=prog+"))));\n";
		  	 prog=prog+"smp1 = vgroup(\"\",base);\n";
		  }
		  if(nbfx>3 && nbfx<9){
		  	 prog=prog+"base=hgroup(\" \",hgroup(\"[0] v0\",vgroup(\"[0] Player\",display_progress(sample1.loop_speed_level_progress(lspeed,lgain)):lmet):hgroup(\"[2]\",par(j,"+to_string(nbcanaux)+",";
		  	 
		  	 for(int i=0;i<12;i++){
		  	 	if(k<3 && tabPave[selectPad-1].idNameFx[i]!="" && tabPave[selectPad-1].idNameFx[i]!="Speed"){
		  	 		if(tabPave[selectPad-1].idNameFx[i]=="Mixer"){
		  	 			prog=prog+"hgroup(\"["+to_string(k)+"]MIXER\",mixer(j)):";
		  	 		}else{
		  	 			idnbfx=ls.find(tabPave[selectPad-1].idNameFx[i])->second;
						prog=prog+"hgroup(\"["+to_string(i)+"]\","+tabPlug[idnbfx].fx+"):";
		  	 		}
		  	 		k++;
		  	 		di=i;
		  	 	}
		  	 }
		  	 k++;
		  	 prog=prog.substr(0,prog.length()-1);
		  	 prog=prog+"))));\n";
		  	 prog=prog+"bl1 = hgroup(\"[1]\",par(j,"+to_string(nbcanaux)+",";
		  	 for(int i=di+1;i<12;i++){
		  	 	if(k<9 && tabPave[selectPad-1].idNameFx[i]!="" && tabPave[selectPad-1].idNameFx[i]!="Speed"){
		  	 		if(tabPave[selectPad-1].idNameFx[i]=="Mixer"){
		  	 			prog=prog+"hgroup(\"["+to_string(k)+"]MIXER\",mixer(j)):";
		  	 		}else{
		  	 			idnbfx=ls.find(tabPave[selectPad-1].idNameFx[i])->second;
						prog=prog+"hgroup(\"["+to_string(i)+"]\","+tabPlug[idnbfx].fx+"):";
		  	 		}
		  	 		k++;
		  	 	}
		  	 }
		  	 prog=prog.substr(0,prog.length()-1);
		  	 prog=prog+"));\n";
		  	 prog=prog+"fx=vgroup(\"FX\",bl1);\n";
		  	 prog=prog+"smp1=vgroup(\"[0]\",base):vgroup(\"[1]\",fx);\n";
		  }
		  if(nbfx>8 && nbfx<13){
		  	 prog=prog+"base=hgroup(\" \",hgroup(\"[0] v0\",vgroup(\"[0] Player\",display_progress(sample1.loop_speed_level_progress(lspeed,lgain)):lmet):hgroup(\"[2]\",par(j,"+to_string(nbcanaux)+",";
		  	 int k=0;
		  	 int di=0;
		  	 for(int i=0;i<12;i++){
		  	 	if(k<3 && tabPave[selectPad-1].idNameFx[i]!="" && tabPave[selectPad-1].idNameFx[i]!="Speed"){
		  	 		if(tabPave[selectPad-1].idNameFx[i]=="Mixer"){
		  	 			prog=prog+"hgroup(\"["+to_string(k)+"]MIXER\",mixer(j)):";
		  	 		}else{
		  	 			idnbfx=ls.find(tabPave[selectPad-1].idNameFx[i])->second;
						prog=prog+"hgroup(\"["+to_string(i)+"]\","+tabPlug[idnbfx].fx+"):";
		  	 		}
		  	 		k++;
		  	 		di=i;
		  	 	}
		  	 }
		  	 k++;
		  	 prog=prog.substr(0,prog.length()-1);
		  	 prog=prog+"))));\n";
		  	 prog=prog+"bl1 = hgroup(\"[1]\",par(j,"+to_string(nbcanaux)+",";
		  	 for(int i=di+1;i<12;i++){
		  	 	if(k>3 && k<9 && tabPave[selectPad-1].idNameFx[i]!="" && tabPave[selectPad-1].idNameFx[i]!="Speed"){
		  	 		if(tabPave[selectPad-1].idNameFx[i]=="Mixer"){
		  	 			prog=prog+"hgroup(\"["+to_string(k)+"]MIXER\",mixer(j)):";
		  	 		}else{
		  	 			idnbfx=ls.find(tabPave[selectPad-1].idNameFx[i])->second;
						prog=prog+"hgroup(\"["+to_string(i)+"]\","+tabPlug[idnbfx].fx+"):";
		  	 		}
		  	 		k++;
		  	 		di=i;
		  	 	}
		  	 }
		  	 prog=prog.substr(0,prog.length()-1);
		  	 prog=prog+"));\n";
		  	 k++;
			 prog=prog+"bl2 = hgroup(\"[2]\",par(j,"+to_string(nbcanaux)+","; 
			 for(int i=di+1;i<12;i++){
		  	 	if(k>8 && k<14 && tabPave[selectPad-1].idNameFx[i]!="" && tabPave[selectPad-1].idNameFx[i]!="Speed"){
		  	 		if(tabPave[selectPad-1].idNameFx[i]=="Mixer"){
		  	 			prog=prog+"hgroup(\"["+to_string(k)+"]MIXER\",mixer(j)):";
		  	 		}else{
		  	 			idnbfx=ls.find(tabPave[selectPad-1].idNameFx[i])->second;
						prog=prog+"hgroup(\"["+to_string(i)+"]\","+tabPlug[idnbfx].fx+"):";
		  	 		}
		  	 		k++;
		  	 	}
		  	 }
		  	 prog=prog.substr(0,prog.length()-1);
		  	 prog=prog+"));\n";	 
		  	 
		  	 prog=prog+"fx=vgroup(\"FX\",bl1:bl2);\n";
		  	 prog=prog+"smp1=vgroup(\"[0]\",base):vgroup(\"[1]\",fx);\n";
		  }
		  prog=prog+"process = smp1;\n";
	  }else{
	  		//prog=prog+"base=hgroup(\" \",hgroup(\"[0]\",vgroup(\"[0] Player\",display_progress(sample1.loop_speed_level_progress(lspeed,lgain)):lmet):hgroup(\"[2]\",par(j,"+to_string(nbcanaux)+",hgroup(\"[3]MIXER\",mixer(j)):hgroup(\"[4]\",spectral_level)))));\n";
	  		prog=prog+"base=hgroup(\" \",hgroup(\"[0]\",vgroup(\"[0] Player\",display_progress(sample1.loop_speed_level_progress(lspeed,lgain)):lmet):hgroup(\"[2]\",par(j,"+to_string(nbcanaux)+",hgroup(\"[3]MIXER\",mixer(j))";
	  		if(tabPave[selectPad-1].fxSpectrum==1){
	  			prog=prog+":hgroup(\"[4]\",spectral_level)";
	  		}
	  		prog=prog+"))));\n";
	  		prog=prog+"bl1 = par(j,"+to_string(nbcanaux)+",hgroup(\"c%2j\","; 
	  		for(int i=0;i<12;i++){
		  	 	if(k<5 && tabPave[selectPad-1].idNameFx[i]!="" && tabPave[selectPad-1].idNameFx[i]!="Mixer"  && tabPave[selectPad-1].idNameFx[i]!="Speed" && tabPave[selectPad-1].idNameFx[i]!="SpectrumAnalyser"){
		  	 		idnbfx=ls.find(tabPave[selectPad-1].idNameFx[i])->second;
					prog=prog+"hgroup(\"["+to_string(i)+"]\","+tabPlug[idnbfx].fx+"):";
		  	 		k++;
		  	 		di=i;
		  	 	}
		  	 }
		  	 prog=prog.substr(0,prog.length()-1);
		  	 prog=prog+"));\n";
		  	 k++;
		  	 if(nbfx>5){
			  	 prog=prog+"bl2 = par(j,"+to_string(nbcanaux)+",hgroup(\"c%2j\","; 
				 for(int i=di+1;i<12;i++){
			  	 	if(k>4 && k<14 && tabPave[selectPad-1].idNameFx[i]!="" && tabPave[selectPad-1].idNameFx[i]!="Mixer"  && tabPave[selectPad-1].idNameFx[i]!="Speed" && tabPave[selectPad-1].idNameFx[i]!="SpectrumAnalyser"){
			  	 		if(k<10){
			  	 			idnbfx=ls.find(tabPave[selectPad-1].idNameFx[i])->second;
							prog=prog+"hgroup(\"[0"+to_string(i)+"]\","+tabPlug[idnbfx].fx+"):";
			  	 		}else{
			  	 			idnbfx=ls.find(tabPave[selectPad-1].idNameFx[i])->second;
							prog=prog+"hgroup(\"["+to_string(i)+"]\","+tabPlug[idnbfx].fx+"):";
			  	 		}
			  	 		k++;
			  	 	}
			  	 }
			  	 prog=prog.substr(0,prog.length()-1);
		  	 	 prog=prog+"));\n";
		  	 }
		  	 	 
		  	 prog=prog+"smp1=vgroup(\"[0]\",base):tgroup(\"[1]\", bl1)";
		  	 if(nbfx>5){
		  	    prog=prog+": tgroup(\"[2]\",bl2)";
		  	 }
		  	 prog=prog+";\n";
		  	 prog=prog+"process = smp1;\n";
	  }  
	  cout <<" canaux : " << nbcanaux<<" nbfx : "<<nbfx<<" path : " << path<< endl;
	  cout <<" dsp : " << prog<< endl;
	  
	  std::thread t(&metaSurface::createDSP,this,prog,"-osc");
	  t.detach();
	  /*
	  string player=ref->getDossierConfig()+"/padPlayer" ;
		char commande[255];
		string nameFile="padPlayer.dsp";
	   string cdir=ref->getDossierConfig();
	   char * cstr = new char [cdir.length()+1];
  	   std::strcpy (cstr, cdir.c_str());
  	   int ncwd=chdir(cstr); 
	   ofstream fichier(nameFile, ios::out | ios::trunc);	
	   if(fichier){
	   	fichier<<prog<<endl;
	   	fichier.close();
	   }else{  // sinon
    	 cerr << "Erreur à l'ouverture du fichier!" << endl;
		} 
		string port=to_string(ref->getOSC());
		string mitx=to_string(newParametres.getXmit());
		char* ns = new char [nameFile.length()+1];
		std::strcpy (ns, nameFile.c_str());
		char* pl = new char [player.length()+1];
		std::strcpy (pl, player.c_str());
		char* nosc = new char [port.length()+1];
		std::strcpy (nosc, port.c_str());
		char* nmit = new char [mitx.length()+1];
		std::strcpy (nmit, mitx.c_str());
		snprintf(commande, 255, "%s %s %s %s %s %s/%s &", pl,"-osc",nosc,"-xmit",nmit,getcwd(NULL,0), ns);
		std::cout << "player dsp: " << commande << std::endl;
		int pd=system(commande);
		*/
   }
}

void metaSurface::genDSP(string port, string mitx){
	cout <<" osc meta: " << port<< endl;
	modeDsp=0;
	int nbcanaux=8;
	int nbsorties=8;
	string prog;
	string nfx;
	int nbCanauxMax=0;
	int dfpart=0;
	string nameFile="padPlayer.dsp";
	string path=getcwd(NULL,0);
	
	for(int k=0;k<surfaceTypeDef;k++){
		tabPave[k].nbfx=0;
		if(tabPave[k].getNbCanaux()>nbCanauxMax){
			nbCanauxMax=tabPave[k].getNbCanaux();
		}
		for(int i=0;i<12;i++){
			if(tabPave[k].idNameFx[i]!=""){
				tabPave[k].nbfx++;
			}
		}
	}
	nbcanaux=nbCanauxMax;
	nbsorties=nbcanaux;
	std::map<string, int> ls=newPlugin.getListPlugin();
	std::vector<Plugin::plugin> tabPlug=newPlugin.getTabPlugin();
	int nbctrl=0;
	int idnbfx;
   map<string,string> lstPlugins;
   for(int j=0;j<surfaceTypeDef;j++){
	   for(int i=0;i<12;i++){
	  		int idnbfx=ls.find(tabPave[j].idNameFx[i])->second;
	  		if(tabPave[j].idNameFx[i]!="" && tabPlug[idnbfx].type==1){
	  			 cout <<" plugin : " << tabPave[j].idNameFx[i]<<" type : "<<tabPlug[idnbfx].type<< endl;
	  			 lstPlugins.insert(std::pair<string, string>(tabPave[j].idNameFx[i],tabPlug[idnbfx].fx));
	  		}	
	   }	
   }
   
   prog=prog+"import(\"stdfaust.lib\");";
	prog=prog+"import(\""+ref->getDossierConfig()+"/faust/soundfiles.lib\");";
	prog=prog+"import(\""+ref->getDossierConfig()+"/faust/metaSurfaceFaust.lib\");";
	std::map<string, string>::iterator it;
  	for(it=lstPlugins.begin();it!=lstPlugins.end();it++){
  		 prog=prog+"import(\""+ref->getDossierUser()+"/Plugins/"+it->first+".lib\");\n";
 	}
	   
	nfx="ds=soundfile(\"[url:{";
	for(int i=0;i<surfaceTypeDef;i++){
	   if(tabPave[i].getFile()==""){
	   	nfx=nfx+"\'"+ref->getDossierConfig()+"/sound/vide.wav\';";
	   }else{
	   	nfx=nfx+"\'"+tabPave[i].getPath()+"/"+tabPave[i].getFile()+"\';";
	   }
	}
	nfx=nfx.substr(0,nfx.length()-1);
	nfx=nfx+"}]\","+to_string(nbcanaux)+");\n";
	prog=prog+nfx;
	prog=prog+"vmeter(i,x)= attach(x, envelop(x) : vbargraph(\"%2i[unit:dB]\", -70, +5));";
	prog=prog+"envelop = abs : max ~ -(1.0/ma.SR) : max(ba.db2linear(-70)) : ba.linear2db;";
	prog=prog+"sample(x) = so.sound(ds, x);";
	prog=prog+"sgain(i) = vslider(\"[0]gain%2i\",0.1,0,2,0.01) : si.smoo;";
	prog=prog+"ingain(i) = vslider(\"[0]gain%2i\",0.1,0,2,0.01) : si.smoo;";
	prog=prog+"sspeed(i)=vslider(\"[1]speed%2i\",1.0,0,2,0.01) : si.smoo;";
	prog=prog+"lect2(x)=hgroup(\"Player\",x);";
	
	prog=prog+"tdec(x)=lect2(hgroup(\"[0]Param\",x));";
	prog=prog+"lect(x)=lect2(hgroup(\"[1]Meter\",x));";
	
	prog=prog+"lgain(i)=tdec(sgain(i));";
	prog=prog+"lgainp(i)=tdec(ingain(i));";
	prog=prog+"lspeed(i)=tdec(sspeed(i));";
	if(nbsorties==0){
		prog=prog+"lmet=lect(vmeter(1));";
		nbcanaux=1;
	}else{
		prog=prog+"lmet=lect(par(j,"+to_string(nbsorties)+",vmeter(j)));";
	}   
	prog=prog+"base=tgroup(\"Pad\",";
   for(int k=0;k<surfaceTypeDef;k++){
   	int nbc;
  	      if(tabPave[k].getFile()==""){
			nbc=2;
	   }else{
	  		nbc=tabPave[k].getNbCanaux();
	   }
   	dfpart=0;
      nfx="";
		   if(tabPave[k].nbfx<=5){ 	
			   	prog=prog+"hgroup(\"p";
      			if(k<10){
      				prog=prog+"0";
      			}
      			if(tabPave[k].getFile()==""){
			   	prog=prog+to_string(k)+"\",hgroup(\"[0]\",_:*(lgainp("+to_string(k)+"))<:lmet";  
					}else{
						prog=prog+to_string(k)+"\",hgroup(\"[0]\",sample("+to_string(k)+").loop_speed_level(lspeed("+to_string(k)+"),lgain("+to_string(k)+")):lmet";  
					}						   	
			   	if(tabPave[k].nbfx==1 && tabPave[k].idNameFx[0]=="Speed"){
      				nbctrl=0;
				   }else{
				   	nbctrl=tabPave[k].nbfx;
				   }		      					      
			      if(nbctrl>0){
			      	prog=prog+":par(j,"+to_string(nbcanaux)+",";
			      }
			  	   for(int i=0;i<12;i++){
			  	   	idnbfx=ls.find(tabPave[k].idNameFx[i])->second;
			  	   	if(tabPlug[idnbfx].type<2){
				  	 	  if(tabPave[k].idNameFx[i]!="" && tabPave[k].idNameFx[i]!="Speed"){
				  	 		  if(tabPave[k].idNameFx[i]=="Mixer"){
				  	 			  nfx=nfx+"hgroup(\"["+to_string(i)+"]MIXER\",mixer(j)):";
				  	 			  dfpart++;
				  	 		  }else{
				  	 		  	  idnbfx=ls.find(tabPave[k].idNameFx[i])->second;
				  	 			  nfx=nfx+"hgroup(\"["+to_string(i)+"]\","+tabPlug[idnbfx].fx+"):";
				  	 			  dfpart++;
				  	 		  }
				  	 	  }
				  	 	}
			  	   }
			  	   if(nfx.length()>0){
			  	   	nfx=nfx.substr(0,nfx.length()-1);
			  	   	prog=prog+nfx+")";
			  	   }
				  	if(tabPave[k].getFlagMulticanaux()==0){
				  	  prog=prog+"):>_),\n";
			  	   }else{
			  	     prog=prog+"):>";
			  	     
			  	     for(int c=0;c<nbsorties;c++){	
			  	    	 prog=prog+"_,";
			  	     }
			  	     prog=prog.substr(0,prog.length()-1);
			  	     prog=prog+"),\n";
			  	   }
			  
	  	   }else{
	  	   	dfpart=0;
	  	   	prog=prog+"vgroup(\"p";
   			if(k<10){
   				prog=prog+"0";
   			}
		   	if(tabPave[k].getFile()==""){
			   	prog=prog+to_string(k)+"\",hgroup(\"[0]\",_:*(lgainp("+to_string(k)+"))<:lmet";  
				}else{
					prog=prog+to_string(k)+"\",hgroup(\"[0]\",sample("+to_string(k)+").loop_speed_level(lspeed("+to_string(k)+"),lgain("+to_string(k)+")):lmet";  
				}	
	      	nfx="";
				if(tabPave[k].nbfx>0){
				   prog=prog+":par(j,"+to_string(nbcanaux)+",";
				}		
		  	   for(int i=0;i<12;i++){
		  	   	if(dfpart<=4){
		  	   	  idnbfx=ls.find(tabPave[k].idNameFx[i])->second;
			  	     if(tabPlug[idnbfx].type<2){
				  	 	  if(tabPave[k].idNameFx[i]!="" && tabPave[k].idNameFx[i]!="Speed"){
				  	 		  if(tabPave[k].idNameFx[i]=="Mixer"){
				  	 			  nfx=nfx+"hgroup(\"["+to_string(i)+"]MIXER\",mixer(j)):";
				  	 		  }else{
				  	 		  	  idnbfx=ls.find(tabPave[k].idNameFx[i])->second;
					  	 		  nfx=nfx+"hgroup(\"["+to_string(i)+"]\","+tabPlug[idnbfx].fx+"):";
				  	 		  }
				  	 		  
				  	 	  }
				  	 }
			  	 	  dfpart++;
			  	 	}
		  	   }
		  	   nfx=nfx.substr(0,nfx.length()-1);
		  	   prog=prog+nfx;
		  	   nfx="";
		  	   if(tabPave[k].nbfx>5 && tabPave[k].idNameFx[5]=="Speed"){
      			nbctrl=0;
				}else{
				  	nbctrl=tabPave[k].nbfx;
				}
				if(nbctrl>0){
	  	   	prog=prog+")):hgroup(\"[1]\",par(j,"+to_string(nbcanaux)+",";
	  	   	}
				for(int i=dfpart;i<12;i++){
					idnbfx=ls.find(tabPave[k].idNameFx[i])->second;
			  	   if(tabPlug[idnbfx].type<2){
		  	   		if(tabPave[k].idNameFx[i]!="" && tabPave[k].idNameFx[i]!="Speed"){
			  	 		  if(tabPave[k].idNameFx[i]=="Mixer"){
			  	 			  nfx=nfx+"hgroup(\"["+to_string(i)+"]MIXER\",mixer(j)):";
			  	 		  }else{
			  	 			  idnbfx=ls.find(tabPave[k].idNameFx[i])->second;
					  	 	  nfx=nfx+"hgroup(\"["+to_string(i)+"]\","+tabPlug[idnbfx].fx+"):";
			  	 		  }
			  	 		  
			  	 	   }
			  	 	}
		  	   }
		  	   if(nfx.length()>0){
		  	   nfx=nfx.substr(0,nfx.length()-1);
		  	   prog=prog+nfx;
		  	   }

		  	   if(tabPave[k].getFlagMulticanaux()==0){
			  	 	prog=prog+")):>_),\n";
		  	    }else{
		  	    	prog=prog+"):";
		  	    	
		  	     for(int c=0;c<nbsorties;c++){	
		  	    	 prog=prog+"_,";
		  	     }
		  	    	prog=prog.substr(0,prog.length()-1);
		  	    	prog=prog+")),\n";
		  	    }
		  	   
		  	   //prog=prog+")):>_),\n";
	  	   }
	  	
	  	}
  	   prog=prog.substr(0,prog.length()-2);
  	   prog=prog+");";
  	   
  	   prog=prog+"smp1=vgroup(\"[0]\",base);";
  	   	   
			
		prog=prog+"process = smp1;";
		
	std::cout << "prog : " << prog << std::endl;
	std::thread t(&metaSurface::createDSP,this,prog,"-osc");
	t.detach();	
}
