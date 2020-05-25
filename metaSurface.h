#ifndef DEF_METASURFACE
#define DEF_METASURFACE

#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>

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

class metaSurface{

	

	private :
	
//************************************************************************
//                           paramètres Interface surface
//************************************************************************	
	Configuration *ref;	
	
	std::string appGui;
	std::string Theme;
	float windowAppWidth;
   float windowAppHeight;
   float menuBarHeight;
   float nscale;
   
   surfaceSelect surfaceN;
   std::string userConfig;

	sf::Color AppBackGround;
	sf::Font font;
	
	sf::RectangleShape surfaceSliderDroit;
   sf::RectangleShape surfaceSliderMDroit;
   sf::RectangleShape surfaceSliderBas;
   sf::RectangleShape surfaceSliderMBas;
   sf::RectangleShape menuBar;
   
   float slideHeight;
   
	bool depNavSurface;
	int depNavX;
   int depNavY;
	bool slideMB;
	bool slideMD;
   float slideMdY;
   float slideMbX;   
   
   sf::RenderWindow surface;
   sf::RenderTexture bkgSurface;
   sf::RectangleShape workspaceSurface;
   sf::RenderTexture navBkgSurface;
   sf::RectangleShape navWorkspaceSurface;
   sf::RectangleShape navSurface;
   
   sf::Texture selectST;
   sf::Sprite defSurface;
   sf::Sprite defSurface2;
   float surfaceX;
   float surfaceY;
   float workSizeX;
   float workSizeY;
   float lastAppWidth;
   float lastAppHeight;
   
   sf::Texture selectAn;
   sf::Texture selectAnB;
   sf::Sprite palette;
   sf::Texture selectAnSlb;
   bool mvBoutonSl1b=0;
   sf::Sprite boutonSl1b;
   bool mvBoutonSl2b=0;
   sf::Sprite boutonSl2b;
   
	int surfaceMode;
	int typeMove;
	
	sf::RectangleShape surfaceCurseur;
	sf::RectangleShape winPaveCurseur;
	bool flagSurfaceCurseur;
	bool flagPaveCurseur;
	sf::Clock clockCurseur;
	
	std::string padName;
	std::string nameBkgFile;
	std::string pathBkgFile;
	bool ctrlFX;
	
	std::string editLineColor;
	int thickness;
	std::string barycentreColor;
	std::string pointColor;

//************************************************************************
//                           paramètres Macro Objets
//************************************************************************
	Menu defMenu;
	selectFile fileSelector; 
	Info newInfo;
	Plugin newPlugin;
	Parametres newParametres;
	Apropos newApropos;
	
//************************************************************************
//                           Paves
//************************************************************************
	
	int surfaceTypeDef;
	sf::CircleShape cercleInterne;
   sf::CircleShape cercleExterne;
   sf::RectangleShape centrePad;
	sf::Texture curType[32];
	sf::Sprite curs;
	Pave tabPave[64];
	int selectPad;
	int padActif;
	int ctrlOsc;
	
	sf::RenderWindow winPave;
	sf::RenderWindow selectType;
	sf::Texture selectCurT;
	sf::Sprite selectCurType;
	sf::Texture selectFp;
	sf::Sprite bkgWinPave;	
	sf::Text labelFile;
   sf::Text labelDaw;
   sf::Text labelMulti;
   sf::Text labelRi;
   sf::Text labelDimMixer;
   sf::Text labelMixerGain;
   sf::Text labelGainMin;
   sf::Text labelGainMax;
   sf::Text labelCanaux;
   sf::Text labelDuree;
   sf::Text labelTrack;
   sf::Text labeldFx;
   sf::Text labelType;
   sf::Text paramFile;
   sf::Text paramDaw;
   sf::Text paramRi;
   sf::Text paramDimMixer;
   sf::Text paramGainMin;
   sf::Text paramGainMax;
   sf::Text paramCanaux;
   sf::Text paramDuree;
   sf::Text paramTrack;
   sf::Text paramdFx;
   sf::Text paramType;
   sf::Sprite fxSelect;
   sf::Sprite defSelectDaw;
   sf::Sprite defSelectGain;
   sf::Sprite defMulti;
   sf::Texture bNoSelect;
   sf::Texture bselect;

   bool fx;
   int paveChampIndex;
   bool flagTxt;
   std::string apptxt;
   int modeDsp;
   
   int temporisationMin;
   int temporisationMax;
   sf::Text tempoTMin;
   sf::Text tempoTMax;
   sf::Text exploseTMax;
   sf::Text dureevieTMin;
   sf::Text dureevieTMax;
   int vieMin;
   int vieMax;
   bool omniSurface;
   bool omniRamdom;
   sf::Sprite bOmniSurface;
   sf::Sprite bOmniRamdom;

//************************************************************************
//                          Fx
//************************************************************************	
  sf::RenderWindow winFX;
  sf::Texture selectF1;
  sf::Sprite fondFx;
  bool shapFxEdit;
  sf::RectangleShape shapeFxSel;
  sf::RectangleShape selectShapFxSel;
  sf::RectangleShape  shapeFxSlider;
  sf::RectangleShape shapeFxMSlider;
  bool flagFxMSlider;
  float FxMdY;
  sf::Text labelFx[15];
  sf::Text labelArdourFx[15];
  sf::Text txtFx[12];
  std::string funcFx[15];
  sf::Text fxLabel;
  sf::Text fxLabelSp;
  sf::Sprite fxcanalB;
  sf::Sprite fxcanalSpect;
  bool fxcanal;
  bool fxSpectrum;
  int rtfx;
  int chaineFxSelect;
  int indexList;
//************************************************************************
//                           Omni
//************************************************************************	
	Omni tabOmni[40];
	bool omniSelectFlag;
	int omniSelect;
	int exploseMax;
	
//************************************************************************
//                           A propos
//************************************************************************	
  sf::RenderWindow winApropos;
  sf::Texture apro;
  sf::Sprite spApropos;

public :
	
	metaSurface(Configuration *def);
  ~metaSurface();
  
	void initSurface(Configuration *def);
	void drawSurface();
	void onResized(sf::Event e);
	void onClickSurface(sf::Event e);
   void onMouseMoveSurface(sf::Event e);
   void onMouseButtonUpSurface(sf::Event e);
   void mouseWheel(sf::Event e);

	void menuSession();
	void sessionCreateSurface(int id);
	void menuOpen();
	void menuSave();
	void menuComment();
	void menuPlugin();
	void editPlugin();
	void eraseUsrPlugin();
	void menuPreferences();
	void manuel();
	void faust();
	void apropos();
	void onClose();
   
   void setSlideHeight();

	float distanceCentre(float cx, float cy, float x, float y);
	int rand_a_b(int a, int b);
	int locatePoint(int x, int y,bool mode);
	
	int inPolygone(bool mode, Pave &shape, sf::Vector2f point);
	int isLeft(const sf::Vector2f &p0,const sf::Vector2f &p1,const sf::Vector2f &point);
	sf::Vector2f normaliseMouseXY(float x, float y);
	
	void delCurseur();
   void delGrpCurseur();
   void delAllCurseur();
	void delAnneau();
   void delAllAnneau();
   
   void surfaceCollision(int mobil);
   bool collision(float r1, float x1, float y1, float r2, float x2, float y2);
   void moveAnneau(int mobil);

	void onClickWinPave(sf::Event e);
	void onMouseMoveWinPave(sf::Event e);
	void onMouseUpWinPave(sf::Event e);
	void newPaveText(sf::Event e);
	void paveValider();
	
	void updateGainPave();
	void updateCurseurPave(int pv);
   void defGain(int pad, float gain);
   void updatePlugins(int pv, float rt);
   void defPlugins(std::string &ms, float param);
	const std::vector<std::string> explode(const std::string& s, const char& c);

	void saveSurface(bool t);
	void openSurface();
	void chargeSurface(std::string nameFile);
	
	void initTPave();
	void defTPave();
	
	void onClickType(sf::Event e);
	
	void onClickWinFx(sf::Event e);
	void onMouseMoveWinFx(sf::Event e);
	void onMouseUpWinFx(sf::Event e);
	void mouseFxWheel(sf::Event e);
	void initTPaveFx();
	void defListPlugin();
	
	void  newOmni(int lX, int lY);
	
	bool testFileDSP(std::string st1);
	bool createDSP(std::string localDsp, std::string st1);
	bool testFxDSP(std::string st1);
	void genDSP(std::string port, std::string x);
	
	void onClickApropos(sf::Event e);
	
};
#endif