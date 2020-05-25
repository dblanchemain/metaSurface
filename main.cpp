#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdlib.h>
#include <iomanip>
#include <locale>
#include <sstream>
#include <ctgmath>
#include <string>


#include "configuration.h"
#include "metaSurface.h"

using namespace std;


int main (int argc, char* argv[]){
  
  Configuration nwConf(argv[1],argv[2]);
  nwConf.initLang(nwConf.getDiversLang());
  //nwApp.appPreferences();
  //nwConf.initTheme();
  std::cout << "Theme: " << nwConf.getFichierTheme()<<std::endl;
  std::cout << "Lang: " << nwConf.getDiversLang()<<std::endl;
  metaSurface nwSurface(&nwConf);
  //metaSurface.initSurface(&nwConf);
  
  nwSurface.drawSurface();
  
  //nwApp.appWindow();


  
  
  
      
    
  
  return EXIT_SUCCESS;
  
}

	
