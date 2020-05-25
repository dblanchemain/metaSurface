#ifndef DEF_CONTRAINTESFX
#define DEF_CONTRAINTESFX

#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>

#include "pave.h"
#include "info.h"
#include "configuration.h"
#include "plugin.h"
/** Construction de l'application */

class ContraintesFx{

  private :
 	sf::RenderWindow winContraintesFx;
 	bool rtf;
 	std::string apptxt;
 	bool flagTxt;
 	int textRand;
 	int textDef;
 	Info newInfo;
	std::string appGui;
	sf::Texture fond;
	sf::Texture bNoSelect;
	sf::Texture bselect;
	sf::Texture bannul;
	sf::Texture bvalid;
	sf::Texture bdefautb;
	sf::Texture bglobal;
	sf::Sprite valider;
	sf::Sprite annuler;
	sf::Sprite defaut;
	sf::Sprite global;
	sf::Font font;
	sf::Sprite fondContraintesFx;
	sf::Sprite distortionDriveS;

	sf::Text labelsPlugin;
	sf::RectangleShape minPlugin;
	sf::RectangleShape maxPlugin;
	sf::RectangleShape scalePlugin;
	sf::Text minTPlugin;
	sf::Text maxTPlugin;
	sf::Text scaleTPlugin;
	sf::Text labelMin;
	sf::Text labelMax;
	sf::Text labelScale;
	
	struct usrParam{
		bool etat;
		sf::Sprite state;
		sf::Text min;
		sf::Text max;
		sf::Text scale;
		bool rev;
		sf::Sprite direction;
	};
	std::vector<usrParam> tabParam;
	
   sf::Text distortionTIntDriveMin;
   sf::Text distortionTIntDriveMax;
   sf::Text distortionTIntDriveScale;
   sf::CircleShape distortionTDriveM;
   sf::Sprite distortionOffsetS;
   sf::Text distortionTIntOffsetMin;
   sf::Text distortionTIntOffsetMax;
   sf::Text distortionTIntOffsetScale;
   sf::CircleShape distortionTOffsetM;
   
   sf::RectangleShape winContraintesFxCurseur;
	bool flagSurfaceCurseur;
	bool flagContraintesFxCurseur;
	sf::Clock clockContraintesFxCurseur;
	
	std::map<std::string, int> ls;
  	std::vector<Plugin::plugin> tabPlug;
  	Pave *npv;
  	int idPlugin;

	
public :	
	
	ContraintesFx(Configuration *def);
  ~ContraintesFx();
  bool drawContraintesFx(Plugin& newPlug,int id, Pave *pv, int plug);
  void initContraintesFx(Pave *pv, int plugin);
  
  void onMouseMoveContraintesFx(sf::Event e,Pave *pv, int plugin);
  void onClickContraintesFx(sf::Event e, Pave *pv, int plugin);
  void newContraintesFxText(sf::Event e, int plugin);
  void validerParam(Pave *pv,int plugin);
  void defautContraintesFxInt(Pave *pv, int plugin);
  void contraintesFxValider(Pave *pv);
  void defautContraintesFxInt(Pave *pv);


};

#endif