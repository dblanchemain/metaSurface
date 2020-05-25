#ifndef DEF_SELECTFILE
#define DEF_SELECTFILE

#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdlib.h>
#include <string>

#include "info.h"

class selectFile{

 public :
  
  selectFile ();
  ~selectFile();

  void initSelector(std::string dossier);
  std::string  selector();
  void setSelectorDossier(std::string path);
  void setSelectorWidth(float w);
  void setSelectorHeight(float h);
  void setSelectorBarColor(sf::Color sBC);
  void setSelectorBkgColor(sf::Color sBkgC);
  void setSelectorPathColor(sf::Color pathC);
  void setSelectorFileColor(sf::Color fileC);
  void setSelectorLineColor(sf::Color lineC);
  void setSelectorSlider1Color(sf::Color slider1C);
  void setSelectorSlider2Color(sf::Color slider2C);
  void setSelectorSlider1thColor(sf::Color slider1thC);
  void setSelectorSlider2thColor(sf::Color slider2thC);
  void setSelectorFontColor(sf::Color sFC);
  void setSelectorFontSize(int sFS);
  void setSelectFontSize(int sFS);
  void setDirFontColor(sf::Color sFdC);
  void setFileFontColor(sf::Color sFfC);
  void setTitreSelector(sf::String sT);
  void setSelectorGui(sf::String gui);
  void setSelectorTheme(sf::String theme);
  void setSelectorLang(sf::String fLang);
  void setSelectorSimpleLecteur(std::string sfl);
  void setNText(std::string nt);
  
  std::string getGui() const;

  void newText(sf::Event e);
  void onClose();
  void onMouseWheel(sf::Event e);
  void onClick(sf::Event e);
  void onMouseUp(sf::Event e);
  void onMouseMove(sf::Event e);
  
 private :
 
	int createDir(std::string dir);
	int listDirs(std::string cdir);
	int readFiles();
	void listFiles();
 	void drawFiles();
	void drawDirs2();
	void drawFiles2();
  

  Info newInfo;
  std::string fGui;
  std::string fTheme;
  std::string dossier;
  sf::Text dossierPath;
  std::string fLang;
  std::string fichierLang;
 
  char simplePlayer[255];
  sf::RenderWindow winSelector;
  float winSelectorWidth;
  float winSelectorHeight;
  int menuBarHeight;
  std::string titreSelector;
  sf::RectangleShape selectBarH;
  sf::RectangleShape selectBarB;
  sf::RectangleShape selectDefPath;
  sf::RectangleShape selectFileS;
  sf::Texture selectFolder;
  sf::Texture selectBAnnuler;
  sf::Texture selectBValider;
  sf::Texture selectSpeakers;
  sf::Sprite selectNew;
  sf::Sprite selectAnnuler;
  sf::Sprite selectValider;

  sf::RectangleShape lineBloc;
  sf::RectangleShape lineBloch;
  sf::RectangleShape lineBloc2;
  sf::RectangleShape lineBloch2;
  
  sf::Font font;
  
  sf::Color selectorBarColor;
  sf::Color selectorBkgColor;
  sf::Color selectorFontColor;
  int selectFontSize;
  sf::Color dirFontColor;
  sf::Color fileFontColor;
  int selectorFontSize;
  
  sf::RectangleShape selectBkgSlider;
  sf::RectangleShape selectBkgSlider2;
  sf::RectangleShape selectMSlider;  
  sf::RectangleShape selectMSlider2;
  int buttonMouse;
  int lastPos1;
  int lastPos2;
  
  std::string txt;
  sf::Text nText;
  std::string newSelect;
  std::vector <std::string> vecDirs;
  std::vector <std::string> vecFs;
  sf::Text selectTextDir;
  int listDirsIndex;
  int listDirsIndex2;
  int listFilesIndex2;
  int selectType;
  sf::RectangleShape selectShap;
  
  sf::Sprite speaker;
  std::string rtf="";
};
#endif
