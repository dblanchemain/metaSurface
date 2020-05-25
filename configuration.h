#ifndef DEF_CONFIGURATION
#define DEF_CONFIGURATION

#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>

#include "selectFile.h"

#include "menu.h"
#include "surfaceSelect.h"


class Configuration{

	public :
	
	Configuration(std::string dossierInstall, std::string perso);
  ~Configuration();
  
   void initLang(std::string lg);
   void initTheme();
   
	std::string getDossierConfig();   
   std::string getFichierTheme();
   std::string getAppGui();
   std::string getEditeur();
   std::string getNavigateur();
   std::string getDiversLang();
   std::string getDossierUser();
   float getWindowAppWidth();
   float getWindowAppHeight();
   float getMenuBarHeight();
   float getSlideHeight();
   
   sf::Color getAppBackGround();
   sf::Color getSlideBkgColor();
   sf::Color getSlideMColor();
   sf::Color getSlideOutlineColor();
   int getSlideOutline();
   
   float getBkgSurfaceWidth();
   float getBkgSurfaceHeight();
	float getWorkspaceSurfaceWidth();
	float getWorkspaceSurfaceHeight();
	float getWorkspaceSurfaceTop();
	float getWorkspaceSurfaceLeft();
	int getWorkspaceSurfaceOutline();
	sf::Color getWorkspaceSurfaceOutColor();
	
	std::string getLabelFile();
	std::string getLabelDaw();
	std::string getLabelRi();
	std::string getLabelMixerGain();
	std::string getLabelDimMixer();
	std::string getLabelGainMin();
	std::string getLabelGainMax();
	std::string getLabelCanaux();
	std::string getLabelDuree();
	std::string getDaw();
	std::string getLang();
	std::string getTheme();
	int getPort();
	int getOSC();
	std::string getServeur();
	
	void setNavigateur(std::string nav);
	void setEditeur(std::string edit);
	void setPort(int pt);
	void setServeur(std::string serv);
	void setOsc(int oscP);

	private :

//************************************************************************
//                           paramètres de base
//************************************************************************ 	
	std::string dossierConfig;
	std::string fichierParametres;
	std::string appGui;
	std::string Theme;
	std::string fichierTheme;
	std::string Lang;
	std::string fichierLang;
	std::string diversLang;
	std::string editeur;
	std::string navigateur;
	std::string padPlayer;
	std::string dossierUser;
	std::string daw;
	int port;
	int osc;
	std::string serveur;
	
//************************************************************************
//                           paramètres Langue
//************************************************************************	
	std::string titreSelector;
	std::string labelNameInstrument;
	std::string labelNbchannels;
	sf::Text plabel[15];
	std::string labelFile;
	std::string labelDaw;
	std::string labelRi;
	std::string labelMixerGain;
	std::string labelDimMixer;
	std::string labelGainMin;
	std::string labelGainMax;
	std::string labelCanaux;
	std::string labelDuree;
	sf::Text labelNfile;
	
//************************************************************************
//                           paramètres Macro Objets
//************************************************************************
	

	surfaceSelect surfaceN;
	
//************************************************************************
//                           paramètres Interface
//************************************************************************	
	float windowAppWidth;
   float windowAppHeight;
   float menuBarHeight;
   float slideHeight;
   int slideOutline;
   
   sf::Color slideBkgColor;
   sf::Color slideMColor;
   sf::Color slideOutlineColor;
   sf::Color AppBackGround;
   sf::Color AppBackGroundMenuBar;
   sf::Color bkgWindowColor;
	sf::Font font;
	
	float bkgSurfaceWidth;
	float bkgSurfaceHeight;
	float workspaceSurfaceWidth;
	float workspaceSurfaceHeight;
	float workspaceSurfaceTop;
	float workspaceSurfaceLeft;
	int workspaceSurfaceOutline;
	sf::Color workspaceSurfaceOutColor;
};

#endif