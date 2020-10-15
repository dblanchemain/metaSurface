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

	
