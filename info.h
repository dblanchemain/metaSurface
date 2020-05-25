#ifndef DEF_INFO
#define DEF_INFO

#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdlib.h>
#include <string>


class Info{

 public :
  
  Info();
  ~Info();
  
  void setInfo(std::string Theme, std::string gui);
  void setTxt(int i, sf::String txt);
  bool drawInfo(int ftype, std::string titreWDialog);
  void setInfoTxtSize(int size);
  void setInfoTxtFillColor(sf::Color color);
  void setInfoBkgColor(sf::Color color);
  void setTxtPosX(int i, int k);
  void setTxtPosY(int i, int k);

  void onClose();
  void onEventResized(sf::Event);
  void mouseWheel(sf::Event);
  void onKeyPressed(sf::Event e);
  void onClick(sf::Event e);
  void onMouseUp(sf::Event e);
  void onMouseMove(sf::Event e);
  

 private :
  
  int winInfoWidth;
  int winInfoHeight;
  int infoBarHeight;
  int type;
  std::string infoGui;
  std::string fTheme;
  std::string Theme;
  sf::RenderWindow winInfo;
  sf::Font font;
  std::string titreWinInfo;

  sf::Text infoTxt[2];  
  int infoTxtSize;
  sf::Color infoTxtFillColor;
  sf::Color infoBkgColor;

  
  bool  rtf=0;
};
#endif
