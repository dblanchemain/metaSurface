#include <SFML/Graphics.hpp>
#include <libgen.h>
#include <sstream>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <ctgmath>
#include <string>
#include <cstring>
#include <boost/filesystem.hpp>
#include <vector>
#include <errno.h>


#include "configuration.h"
#include "selectFile.h"
#include "parametres.h"
#include "menu.h"
#include "surfaceSelect.h"

using namespace std;



Configuration::Configuration(string dossierInstall, string perso){
  std::stringstream adr;
  string Home=perso;
  string ds="/metaSurface4/parametres.conf";
  fichierParametres=Home+ds;
  adr.clear();
  adr.str("");
  dossierUser=Home+"/metaSurface4";
  dossierConfig=dossierInstall;
  adr << std::fixed <<dossierConfig<< "/gui";
  appGui=adr.str();
  adr.clear();
  adr.str("");
   
  ifstream fichier(fichierParametres, ios::in);
  string contenu;
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
       if(pf[0]=="Thème"){
		  	  Theme=pf[1];
			  adr << std::fixed  <<dossierConfig<<"/Themes/"<< Theme;
			  fichierTheme=adr.str();
			  adr.clear();
			  adr.str("");
       }
       if(pf[0]=="Lang"){
			  Lang=pf[1];
			  adr << std::fixed <<dossierConfig << "/Lang/" << Lang;
			  fichierLang=adr.str();
			  adr.clear();
			  adr.str("");
			  adr << std::fixed <<dossierConfig << "/Lang/divers." << Lang;
			  diversLang=adr.str();
			  adr.clear();
			  adr.str("");
       }
       if(pf[0]=="Editeur"){
	  		editeur=pf[1];
       }
       if(pf[0]=="Navigateur"){
	  		navigateur=pf[1];
       }
       if(pf[0]=="Player"){
	  		padPlayer=pf[1];
       }
       if(pf[0]=="Daw"){
	  		daw=pf[1];
       }
       if(pf[0]=="port"){
	  		port=stoi(pf[1]);
       }
       if(pf[0]=="OSC"){
	  		osc=stoi(pf[1]);
       }
       if(pf[0]=="serveur"){
	  		serveur=pf[1];
       }
     }
     fichier.close();		
  }else{  // sinon
       cerr << "Erreur à l'ouverture Préférences!" << endl;
  }
  std::cout << "parametres : " << fichierParametres<<std::endl;
  std::cout << "Theme: " << fichierTheme<<std::endl;
  std::cout << "Lang : " << Lang<<std::endl;
  std::cout << "Player : " << padPlayer<<std::endl;
  adr << std::fixed << appGui <<"/"<<Theme;
  appGui=adr.str();
  adr.clear();
  adr.str("");
  std::cout << "GUI" << appGui<<std::endl;
  
  //newInfo.setInfo(appGui);
  //surfaceN.setGui(appGui);
}
void Configuration::initLang(string lg){
	std::stringstream adr;
	std::cout << "Lang divers: " <<lg<<std::endl;
	ifstream fichierLang(diversLang.c_str(), ios::in); 
   string contenu="";
   sf::String sfstr;
   string pf[2];
   int i=0;
   if(fichierLang){  
     while(getline(fichierLang, contenu)){
			char * cstr = new char [contenu.length()+1];
			std::strcpy (cstr, contenu.c_str());
			char * p = std::strtok (cstr,"=");
			i=0;
			while (p!=0){
				pf[i]=p;
	 	    	i++;
		    	p = std::strtok(NULL,"=");
			}
			if(pf[0]=="labelNameInstrument"){
		  	//sfstr = sf::String::fromUtf8(pf[1].begin(), pf[1].end());
		   labelNameInstrument=pf[1];
			}
			
			if(pf[0]=="labelNbchannels"){
		  	sfstr = sf::String::fromUtf8(pf[1].begin(), pf[1].end());
		   labelNbchannels=sfstr;
			}
			if(pf[0]=="labelNfile"){
		   	labelFile = sf::String::fromUtf8(pf[1].begin(), pf[1].end());
			}
			if(pf[0]=="labelDaw"){
		  		labelDaw = sf::String::fromUtf8(pf[1].begin(), pf[1].end());
			}
			if(pf[0]=="labelMixerGain"){
		  		labelMixerGain = sf::String::fromUtf8(pf[1].begin(), pf[1].end());
			}
			if(pf[0]=="labelDimMixer"){
		  		labelDimMixer = sf::String::fromUtf8(pf[1].begin(), pf[1].end());
			}		
			if(pf[0]=="labelGainMin"){
		  		labelGainMin = sf::String::fromUtf8(pf[1].begin(), pf[1].end());
			}
			if(pf[0]=="labelGainMax"){
		  		labelGainMax = sf::String::fromUtf8(pf[1].begin(), pf[1].end());
			}
			if(pf[0]=="labelCanaux"){
		  		labelCanaux = sf::String::fromUtf8(pf[1].begin(), pf[1].end());
			}
			if(pf[0]=="labelDuree"){
		  		labelDuree = sf::String::fromUtf8(pf[1].begin(), pf[1].end());
			}
			
      }
      fichierLang.close();
    }else{  // sinon
		cerr << "Erreur à l'ouverture du fichier Lang!" << endl;
		
        std::cout << "could not open file : " <<lg<< " : " << strerror(errno) << std::endl;
        
    }
}
void Configuration::initTheme(){
  ifstream fichier(fichierTheme, ios::in); 
  string contenu;
  string pf[2];
  int i=0;
  
  stringstream adr;
  adr << std::fixed << appGui<<"/"<<"Arial.ttf";
  font.loadFromFile(adr.str());
  adr.clear();
  adr.str("");
 
  //appShapWindow();
  
  
  
}
Configuration::~Configuration(){
}
string Configuration::getDossierConfig(){
	return dossierConfig;
}
string Configuration::getFichierTheme(){
	return fichierTheme;
}
string Configuration::getAppGui(){
	return appGui;
}
string Configuration::getDiversLang(){
	return diversLang;
}
string Configuration::getEditeur(){
	return editeur;
}
string Configuration::getNavigateur(){
	return navigateur;
}
string Configuration::getLang(){
	return Lang;
}
string Configuration::getTheme(){
	return Theme;
}

string Configuration::getLabelFile(){
	return labelFile;
}
string Configuration::getDossierUser(){
	return dossierUser;
}
string Configuration::getDaw(){
	return daw;
}
int Configuration::getPort(){
	return port;
}
int Configuration::getOSC(){
	return osc;
}
string Configuration::getServeur(){
	return serveur;
}
string Configuration::getLabelDaw(){
	return labelDaw;
}
string Configuration::getLabelRi(){
	return labelRi;
}
string Configuration::getLabelMixerGain(){
	return labelMixerGain;
}
string Configuration::getLabelDimMixer(){
	return labelDimMixer;
}
string Configuration::getLabelGainMin(){
	return labelGainMin;
}
string Configuration::getLabelGainMax(){
	return labelGainMax;
}
string Configuration::getLabelCanaux(){
	return labelCanaux;
}
string Configuration::getLabelDuree(){
	return labelDuree;
}
sf::Color Configuration::getAppBackGround(){
	return AppBackGround;
}
float Configuration::getWindowAppWidth(){
	return windowAppWidth;
}
float Configuration::getWindowAppHeight(){
	return windowAppHeight;
}
float Configuration::getMenuBarHeight(){
	return menuBarHeight;
}
float Configuration::getSlideHeight(){
	return slideHeight;
}
sf::Color Configuration::getSlideBkgColor(){
	return slideBkgColor;
}
sf::Color Configuration::getSlideMColor(){
	return slideMColor;
}
sf::Color Configuration::getSlideOutlineColor(){
	return slideOutlineColor;
}
int Configuration::getSlideOutline(){
	return slideOutline;
}
float Configuration::getBkgSurfaceWidth(){
	return bkgSurfaceWidth;
}
float Configuration::getBkgSurfaceHeight(){
	return bkgSurfaceHeight;
}
float Configuration::getWorkspaceSurfaceWidth(){
	return workspaceSurfaceWidth;
}
float Configuration::getWorkspaceSurfaceHeight(){
	return workspaceSurfaceHeight;
}
float Configuration::getWorkspaceSurfaceTop(){
	return workspaceSurfaceTop;
}
float Configuration::getWorkspaceSurfaceLeft(){
	return workspaceSurfaceLeft;
}
int Configuration::getWorkspaceSurfaceOutline(){
	return workspaceSurfaceOutline;
}
sf::Color Configuration::getWorkspaceSurfaceOutColor(){
	return workspaceSurfaceOutColor;
}
void Configuration::setNavigateur(string nav){
	navigateur=nav;
}
void Configuration::setEditeur(std::string edit){
	editeur=edit;
}
void  Configuration::setPort(int pt){
	port=pt;
}
void Configuration::setServeur(string serv){
	serveur=serv;
}
void Configuration::setOsc(int oscP){
	osc=osc;
}