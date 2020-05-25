#include <SFML/Graphics.hpp>
#include <sstream>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <dirent.h>
#include <stdlib.h>
#include <ctgmath>
#include <string>
#include <cstring>
#include <boost/filesystem.hpp>

#include "pave.h"
#include "info.h"
#include "contraintesFx.h"
#include "plugin.h"

using namespace std;

ContraintesFx::ContraintesFx(Configuration *def){ 
  //appGui=gui;
  stringstream adr;
  adr << std::fixed << def->getAppGui()<<"/"<<"Arial.ttf";
  font.loadFromFile(adr.str());
  adr.clear();
  adr.str("");
  adr << std::fixed << def->getAppGui() << "/fondFx3.png";
  fond.loadFromFile(adr.str());
  fondContraintesFx.setTexture(fond);
  adr.clear();
  adr.str("");
  adr << std::fixed << def->getAppGui() << "/bNoSelect.png";
  bNoSelect.loadFromFile(adr.str());
  adr.clear();
  adr.str("");
  adr << std::fixed << def->getAppGui() << "/bselect.png";
  bselect.loadFromFile(adr.str());
  adr.clear();
  adr.str("");
  adr << std::fixed << def->getAppGui() << "/bAnnuler.png";
  bannul.loadFromFile(adr.str());
  annuler.setTexture(bannul);
  adr.clear();
  adr.str("");
  adr << std::fixed << def->getAppGui() << "/bValider.png";
  bvalid.loadFromFile(adr.str());
  valider.setTexture(bvalid);
  adr.clear();
  adr.str("");
  adr << std::fixed << def->getAppGui() << "/bdefautb.png";
  bdefautb.loadFromFile(adr.str());
  defaut.setTexture(bdefautb);
  adr.clear();
  adr.str("");
  adr << std::fixed << def->getAppGui() << "/bglobal.png";
  bglobal.loadFromFile(adr.str());
  global.setTexture(bglobal);
  
  adr.clear();
  adr.str("");
  winContraintesFxCurseur.setSize(sf::Vector2f(2,12));
  winContraintesFxCurseur.setFillColor(sf::Color(0,0,0,255));
  flagContraintesFxCurseur=0;
  
}

ContraintesFx::~ContraintesFx(){
}
bool ContraintesFx::drawContraintesFx(Plugin& newPlug, int id, Pave *pv, int plug){
	ls=newPlug.getListPlugin();
  	tabPlug=newPlug.getTabPlugin();
  	idPlugin=id;
  	npv=pv;
  	
  	usrParam defParam;
  	for(int i=0;i<tabPlug[id].nbpar;i++){
  		defParam.etat=0;
  		defParam.min.setFont(font);
 		defParam.min.setCharacterSize(13);
 		defParam.min.setFillColor(sf::Color(0,0,0));
 		defParam.max.setFont(font);
 		defParam.max.setCharacterSize(13);
 		defParam.max.setFillColor(sf::Color(0,0,0));
 		defParam.scale.setFont(font);
 		defParam.scale.setCharacterSize(13);
 		defParam.scale.setFillColor(sf::Color(0,0,0));
 		defParam.rev=0;
 		tabParam.push_back(defParam);
  	}
  	initContraintesFx(pv,plug);
	rtf=0;
  	float winHeight=58+(28*tabPlug[id].nbpar)+60;
  	float bheight;
  	sf::RectangleShape shapePluginContraintes(sf::Vector2f(374,54+(28*tabPlug[id].nbpar)));
  	shapePluginContraintes.setFillColor(sf::Color(0,0,0,0));
   shapePluginContraintes.setOutlineThickness(1.f);
   shapePluginContraintes.setOutlineColor(sf::Color(180,180,180));
   shapePluginContraintes.setPosition(sf::Vector2f(8,12));
  	sf::Text nomPlugin;
  	string s=" "+tabPlug[id].nomFx+" ";
  	nomPlugin.setString(s);
  	nomPlugin.setPosition(24,2);
  	nomPlugin.setFont(font);
 	nomPlugin.setCharacterSize(13);
 	nomPlugin.setFillColor(sf::Color(0,0,0));
 	sf::RectangleShape shapePluginBkg(sf::Vector2f(nomPlugin.getLocalBounds().width,nomPlugin.getLocalBounds().height));
 	shapePluginBkg.setFillColor(sf::Color(224,224,224));
 	shapePluginBkg.setPosition(24,2);
   

	sf::Text labelMin;
	labelMin.setString("Min");
	labelMin.setFont(font);
 	labelMin.setCharacterSize(13);
 	labelMin.setFillColor(sf::Color(0,0,0));
 	labelMin.setPosition(156,25);
	sf::Text labelMax;
	labelMax.setString("Max");
	labelMax.setFont(font);
 	labelMax.setCharacterSize(13);
 	labelMax.setFillColor(sf::Color(0,0,0));
 	labelMax.setPosition(224,25);
	sf::Text labelScale;
	labelScale.setString("Scale");
	labelScale.setFont(font);
 	labelScale.setCharacterSize(13);
 	labelScale.setFillColor(sf::Color(0,0,0));
 	labelScale.setPosition(278,25);
 	sf::Text labelRev;
	labelRev.setString("Rev.");
	labelRev.setFont(font);
 	labelRev.setCharacterSize(13);
 	labelRev.setFillColor(sf::Color(0,0,0));
 	labelRev.setPosition(328,25);
   
   bheight=60+(28*tabPlug[id].nbpar)+14;
   annuler.setPosition(248,bheight);
   valider.setPosition(312,bheight);
   defaut.setPosition(18,bheight);
   global.setPosition(80,bheight);
  	
  	winContraintesFx.create(sf::VideoMode(390, winHeight), tabPlug[id].nomFx);
  	
	std::cout << "tabPlug " << tabPlug[id].nbpar <<" param "<<tabPlug[id].param[0].nom<< std::endl;
	
	stringstream adr;
	while (winContraintesFx.isOpen()) { 
        sf::Event eventContraintesFx;
        while (winContraintesFx.pollEvent(eventContraintesFx)){
    	     switch (eventContraintesFx.type){
		         case sf::Event::Closed:
		         	rtf=1;
			         winContraintesFx.close();
						break;
            	case sf::Event::MouseButtonPressed:
			      	onClickContraintesFx(eventContraintesFx,pv, plug);
                	break;
            	case sf::Event::MouseMoved:
			         onMouseMoveContraintesFx(eventContraintesFx,pv,plug);
                	break;
               case sf::Event::TextEntered:
           			newContraintesFxText(eventContraintesFx,plug);
						break;
        				  					
		         default: 
                	break;
  	       	}            
        }
			winContraintesFx.setActive(true);
			winContraintesFx.pushGLStates();
			winContraintesFx.clear(sf::Color(224,224,224));
			winContraintesFx.draw(shapePluginContraintes);
			winContraintesFx.draw(shapePluginBkg);
			winContraintesFx.draw(nomPlugin);
			
			winContraintesFx.draw(labelMin);
			winContraintesFx.draw(labelMax);
			winContraintesFx.draw(labelScale);
			winContraintesFx.draw(labelRev);
			
			for(int i=0;i<tabPlug[id].nbpar;i++){
				labelsPlugin.setString(tabPlug[id].param[i].nom);
				labelsPlugin.setPosition(30,50+(i*30));
				labelsPlugin.setFont(font);
			 	labelsPlugin.setCharacterSize(13);
			 	labelsPlugin.setFillColor(sf::Color(0,0,0));
			 	if(tabParam[i].etat==0){
	   			tabParam[i].state.setTexture(bNoSelect);
	   		}else{
	   			tabParam[i].state.setTexture(bselect);
	   		}
				tabParam[i].state.setPosition(110,50+(i*30));
				minPlugin.setPosition(140,48+(i*30));
				minPlugin.setSize(sf::Vector2f(60,20));
				maxPlugin.setPosition(140+68,48+(i*30));
				maxPlugin.setSize(sf::Vector2f(60,20));
				scalePlugin.setPosition(140+136,48+(i*30));
				scalePlugin.setSize(sf::Vector2f(40,20));
				if(tabParam[i].rev==0){
	   			tabParam[i].direction.setTexture(bNoSelect);
	   		}else{
	   			tabParam[i].direction.setTexture(bselect);
	   		}
				tabParam[i].direction.setPosition(140+190,50+(i*30));
	
				winContraintesFx.draw(labelsPlugin);
				winContraintesFx.draw(tabParam[i].state);
				winContraintesFx.draw(minPlugin);
				tabParam[i].min.setPosition(196-tabParam[i].min.getLocalBounds().width-2,50+(i*30));
				winContraintesFx.draw(tabParam[i].min);
				winContraintesFx.draw(maxPlugin);
				tabParam[i].max.setPosition(196+68-tabParam[i].max.getLocalBounds().width-2,50+(i*30));
				winContraintesFx.draw(tabParam[i].max);
				winContraintesFx.draw(scalePlugin);
				tabParam[i].scale.setPosition(312-tabParam[i].scale.getLocalBounds().width-2,50+(i*30));
				winContraintesFx.draw(tabParam[i].scale);
				winContraintesFx.draw(tabParam[i].direction);
			}			
			
			winContraintesFx.draw(defaut);
			winContraintesFx.draw(global);
			winContraintesFx.draw(annuler);
			winContraintesFx.draw(valider);
			
			if(flagContraintesFxCurseur==1){
				if(clockContraintesFxCurseur.getElapsedTime()>sf::seconds(0.8f)){
					winContraintesFx.draw(winContraintesFxCurseur);
					if(clockContraintesFxCurseur.getElapsedTime()>sf::seconds(1.6f)){
						clockContraintesFxCurseur.restart();
					}
				}
			}
			
			winContraintesFx.display();
			winContraintesFx.popGLStates();
			winContraintesFx.setActive(false);
			
	}
   return rtf;
   
}

//************************************************************************************************************
//								
//************************************************************************************************************
void ContraintesFx::initContraintesFx(Pave *pv, int plugin){
	stringstream adr;
	for(int i=0;i<tabPlug[idPlugin].nbpar;i++){
		tabParam[i].etat=pv->tabUsrPluginParam[plugin][i].etat;
		adr << std::fixed<< std::setprecision(2)<<pv->tabUsrPluginParam[plugin][i].min;
		tabParam[i].min.setString(adr.str());
		adr.clear();
		adr.str("");
		adr << std::fixed<< std::setprecision(2)<<pv->tabUsrPluginParam[plugin][i].max;
		tabParam[i].max.setString(adr.str());
		adr.clear();
		adr.str("");
		adr << std::fixed<< std::setprecision(2)<<pv->tabUsrPluginParam[plugin][i].scale;
		tabParam[i].scale.setString(adr.str());
		adr.clear();
		adr.str("");
		tabParam[i].rev=pv->tabUsrPluginParam[plugin][i].rev;
	}
}
void ContraintesFx::defautContraintesFxInt(Pave *pv, int plugin){
	stringstream adr;
	int idnbfx=ls.find(tabPlug[idPlugin].nomFx)->second;
	std::cout << "plugin: " << plugin <<"tabPlug[idPlugin].nomFx"<<tabPlug[idPlugin].nomFx<<" idnbfx "<<idnbfx<< std::endl;
	for(int i=0;i<tabPlug[idPlugin].nbpar;i++){
		tabParam[i].etat=0;
		adr << std::fixed<< std::setprecision(2)<<tabPlug[idnbfx].param[i].min;
		tabParam[i].min.setString(adr.str());
		adr.clear();
		adr.str("");
		adr << std::fixed<< std::setprecision(2)<<tabPlug[idnbfx].param[i].max;
		tabParam[i].max.setString(adr.str());
		adr.clear();
		adr.str("");
		tabParam[i].scale.setString("1.00");
		tabParam[i].rev=0;
		std::cout << "param[i].min: " << tabPlug[idnbfx].param[i].min <<"param[i].max"<<tabPlug[idnbfx].param[i].max<< std::endl;
	}
}
void ContraintesFx::onMouseMoveContraintesFx(sf::Event e,Pave *pv, int plugin){
  //std::cout << "mouse x: " << e.mouseMove.x << std::endl;
  //std::cout << "mouse y: " << e.mouseMove.y << std::endl;
  if(e.mouseMove.x<112 || e.mouseMove.x>346 || e.mouseMove.y<50 || e.mouseMove.y>50+(28*tabParam.size())){
  	validerParam(pv,plugin);
  }
}
void ContraintesFx::onClickContraintesFx(sf::Event e,Pave *pv, int plugin){
   if (e.mouseButton.button == sf::Mouse::Left){
      std::cout << "the left button was pressed" << std::endl;
      std::cout << "mouse x: " << e.mouseButton.x << std::endl;
      std::cout << "mouse y: " << e.mouseButton.y << std::endl;
   }
   int id;
   if(e.mouseButton.x>112 && e.mouseButton.x<126 &&e.mouseButton.y>54 && e.mouseButton.y<54+(28*tabParam.size())){
   	id=(e.mouseButton.y-54)/28;
   	if(tabParam[id].etat==0){
   		tabParam[id].etat=1;
   	}else{
   		tabParam[id].etat=0;
   	}
   	std::cout << "id: " << id <<"tabParam[id].etat"<<tabParam[id].etat<< std::endl;
   }
   if(e.mouseButton.x>142 && e.mouseButton.x<200 &&e.mouseButton.y>50 && e.mouseButton.y<50+(30*tabParam.size())){
   	id=(e.mouseButton.y-50)/30;
   	textDef=id;
   	textRand=0;
   	tabParam[id].min.setString("");
   	apptxt="";
   	flagTxt=1;
   	flagContraintesFxCurseur=1;
   	winContraintesFxCurseur.setPosition(196,52+(id*30));
   }
   if(e.mouseButton.x>208 && e.mouseButton.x<268 &&e.mouseButton.y>50 && e.mouseButton.y<50+(30*tabParam.size())){
   	id=(e.mouseButton.y-50)/30;
   	textDef=id;
   	textRand=1;
   	tabParam[id].max.setString("");
   	apptxt="";
   	flagTxt=1;
   	flagContraintesFxCurseur=1;
   	winContraintesFxCurseur.setPosition(264,52+(id*30));
   }
   if(e.mouseButton.x>276 && e.mouseButton.x<316 &&e.mouseButton.y>50 && e.mouseButton.y<50+(30*tabParam.size())){
   	id=(e.mouseButton.y-50)/30;
   	textDef=id;
   	textRand=2;
   	tabParam[id].scale.setString("");
   	apptxt="";
   	flagTxt=1;
   	flagContraintesFxCurseur=1;
   	winContraintesFxCurseur.setPosition(312,52+(id*30));
   }
   if(e.mouseButton.x>332 && e.mouseButton.x<346 &&e.mouseButton.y>54 && e.mouseButton.y<54+(28*tabParam.size())){
   	id=(e.mouseButton.y-54)/28;
   	if(tabParam[id].rev==0){
   		tabParam[id].rev=1;
   	}else{
   		tabParam[id].rev=0;
   	}
   	std::cout << "id: " << id <<"tabParam[id].etat"<<tabParam[id].etat<< std::endl;
   }
   
   if(e.mouseButton.x>20 && e.mouseButton.x<75 && e.mouseButton.y>50+(28*tabParam.size()) && e.mouseButton.y<100+(28*tabParam.size())){
   	defautContraintesFxInt(pv,plugin);
   }
   if(e.mouseButton.x>250 && e.mouseButton.x<306 && e.mouseButton.y>50+(28*tabParam.size()) && e.mouseButton.y<100+(28*tabParam.size())){
   	winContraintesFx.close();
   }
   if(e.mouseButton.x>312 && e.mouseButton.x<360 && e.mouseButton.y>50+(28*tabParam.size()) && e.mouseButton.y<100+(28*tabParam.size())){
   	validerParam(pv, plugin);
   	winContraintesFx.close();
   }
}
void ContraintesFx::validerParam(Pave *pv,int plugin){
	stringstream adr;
	float fs;
	string s;
  	int idnbfx=ls.find(tabPlug[idPlugin].nomFx)->second;
  	std::cout << "nom " << tabPlug[idPlugin].nomFx<< std::endl;
	for(int i=0;i<tabParam.size();i++){
  		pv->tabUsrPluginParam[plugin][i].etat=tabParam[i].etat;
  		
  		s=tabParam[i].min.getString();
  		fs=stof(s);
  		if(fs<tabPlug[idnbfx].param[i].min || fs>tabPlug[idnbfx].param[i].max){
  			fs=tabPlug[idnbfx].param[i].min;
  		}
  		adr << std::fixed<< std::setprecision(2)<<fs;
		tabParam[i].min.setString(adr.str());
		s=adr.str();
		adr.clear();
		adr.str("");
  		pv->tabUsrPluginParam[plugin][i].min=stof(s);
  		
  		s=tabParam[i].max.getString();
  		fs=stof(s);
  		std::cout << "max " << tabPlug[idnbfx].param[i].max<< std::endl;
  		if(fs<pv->tabUsrPluginParam[plugin][i].min || fs>tabPlug[idnbfx].param[i].max){
  			fs=tabPlug[idnbfx].param[i].max;
  		}
  		adr << std::fixed<< std::setprecision(2)<<fs;
		tabParam[i].max.setString(adr.str());
		s=adr.str();
		adr.clear();
		adr.str("");
  		pv->tabUsrPluginParam[plugin][i].max=stof(s);
  		
  		string s=tabParam[i].scale.getString();
  		fs=stof(s);
  		if(fs<0 || fs>2){
  			fs=1;
  		}
  		adr << std::fixed<< std::setprecision(2)<<fs;
		tabParam[i].scale.setString(adr.str());
		s=adr.str();
		adr.clear();
		adr.str("");
  		pv->tabUsrPluginParam[plugin][i].scale=stof(s);
  		
  		pv->tabUsrPluginParam[plugin][i].rev=tabParam[i].rev;
  		
	}
}
void ContraintesFx::newContraintesFxText(sf::Event e, int plugin){
   int key=e.key.code;
   stringstream adr;
   int idnbfx=ls.find(tabPlug[idPlugin].nomFx)->second;
   float posv=(20-distortionTIntDriveMin.getLocalBounds().height)/2;
   if (e.text.unicode < 128){
		if(key==8){
	       	apptxt=apptxt.substr(0,apptxt.length()-1);
	       	
	 	}else{
		apptxt=apptxt+static_cast<char>(e.text.unicode);
		flagTxt=1;
      }
      switch (textRand){
    		case 0:
				 tabParam[textDef].min.setString(apptxt);
     			 break;
     		case 1:
     			 tabParam[textDef].max.setString(apptxt);
     			 break;
     		case 2:
     			 tabParam[textDef].scale.setString(apptxt);
     			 break;
     		default:
    			break;
	   }
      
   }
}
void ContraintesFx::contraintesFxValider(Pave *pv){
	/*
  string s;
  s=distortionTIntDriveMin.getString();
  pv->distortionIntDriveMin=stof(s);
  s=distortionTIntDriveMax.getString();
  pv->distortionIntDriveMax=stof(s);
  s=distortionTIntDriveScale.getString();
  pv->distortionIntDriveScale=stof(s);
  s=distortionTIntOffsetMin.getString();
  pv->distortionIntOffsetMin=stof(s);
  s=distortionTIntOffsetMax.getString();
  pv->distortionIntOffsetMax=stof(s);
  s=distortionTIntOffsetScale.getString();
  pv->distortionIntOffsetScale=stof(s);
  */
}
void ContraintesFx::defautContraintesFxInt(Pave *pv){
	/*
	stringstream adr;
  	adr << std::fixed<< std::setprecision(1)<<pv->distortionIntDriveMin;
   distortionTIntDriveMin.setString(adr.str());
   float posv=(20-distortionTIntDriveMin.getLocalBounds().height)/2;
   distortionTIntDriveMin.setPosition(178-distortionTIntDriveMin.getLocalBounds().width-2,58+posv-3);
  	adr.clear();
  	adr.str("");
   adr << std::fixed<< std::setprecision(1)<<pv->distortionIntDriveMax;
   distortionTIntDriveMax.setString(adr.str());
   distortionTIntDriveMax.setPosition(248-distortionTIntDriveMax.getLocalBounds().width-2,58+posv-3);
   adr.clear();
  	adr.str("");
   adr << std::fixed<< std::setprecision(2)<<pv->distortionIntDriveScale;
   distortionTIntDriveScale.setString(adr.str());
   distortionTIntDriveScale.setPosition(290-distortionTIntDriveScale.getLocalBounds().width-2,58+posv-3);
   adr.clear();
  	adr.str("");
   adr << std::fixed<< std::setprecision(1)<<pv->distortionIntOffsetMin;
   distortionTIntOffsetMin.setString(adr.str());
   distortionTIntOffsetMin.setPosition(178-distortionTIntOffsetMin.getLocalBounds().width-2,85+posv-3);
   adr.clear();
  	adr.str("");
   adr << std::fixed<< std::setprecision(1)<<pv->distortionIntOffsetMax;
   distortionTIntOffsetMax.setString(adr.str());
   distortionTIntOffsetMax.setPosition(248-distortionTIntOffsetMax.getLocalBounds().width-2,85+posv-3);
   adr.clear();
  	adr.str("");
   adr << std::fixed<< std::setprecision(2)<<pv->distortionIntOffsetScale;
   distortionTIntOffsetScale.setString(adr.str());
   distortionTIntOffsetScale.setPosition(290-distortionTIntOffsetScale.getLocalBounds().width-2,85+posv-3);
   adr.clear();
  	adr.str("");
  	*/
}