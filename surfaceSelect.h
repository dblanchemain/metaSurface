#ifndef DEF_SURFACESELECT
#define DEF_SURFACESELECT

#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdlib.h>
#include <string>

#include "newSurface.h"

class surfaceSelect{

 public :
  
  surfaceSelect();
  ~surfaceSelect();
  
  int drawSurface(std::string path,std::string gui, std::string theme,std::string user);
  void setPath(std::string path);
  void setGui(std::string gui);
  void setSwidth(float sw);
  void setSheight(float sh);
  float getSwidth();
  float getSheight();
  std::string getSUser();
  void onClose();
  
  void onClick(sf::Event e);
  void onMouseMove(sf::Event e);
  void createSurface();
  std::string selectReturnPath();
  std::string selectReturnFile();
  

 private :
  sf::RenderWindow winSurface;
  std::string surfaceConfig;
  std::string surfaceGui;
  std::string surfaceTheme;
  std::string userConfig;
  sf::Font font;
  int type;
  float swidth;
  float sheight;
  sf::RectangleShape selectShape;
  bool surfaceS=0;
  bool defNewSurface;
  std::string nameReturnFile;
  std::string pathReturnFile;
};
#endif
