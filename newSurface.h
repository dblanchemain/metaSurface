#ifndef DEF_NEWSURFACE
#define DEF_NEWSURFACE

#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>


#include "selectFile.h"
#include "info.h"
#include "colorSelector.h"

class newSurface{


	private :
	
	std::string appGui;
	std::string Theme;
	std::string dossierConfig;
	std::string userConfig;
	
	float windowAppWidth;
   float windowAppHeight;
   float menuBarHeight;
   float nscale;
   bool surfaceEtat;
   bool surfaceSave;

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
   
   colorSelector newColor;
   sf::RenderWindow surface;
   sf::RenderTexture bkgSurface;
   sf::RectangleShape workspaceSurface;
   sf::RenderTexture navBkgSurface;
   sf::RectangleShape navWorkspaceSurface;
   sf::RectangleShape navSurface;
   sf::Sprite palette;
   sf::Sprite barPalette;
   sf::Texture selectAnB;
   sf::Texture selectAnB2;
   
   struct barycentre{
    bool etat;
    float cx;
    float cy;
    int dim;
    sf::Vector2f point[17];
    float distanceMax;
    sf::ConvexShape nconvex;
    std::string fileSound;
    std::string path;
    int canaux;
    float duree;
    bool daw;
    int track;
    float dimMixer;
    float gainMin;
    float gainMax;
    bool fx;
    bool curseurEtat;
    int curseurType;
    float curseurX;
    float curseurY;
    std::string listfx;
   };
   float temporisationMin;
   float temporisationMax;
   float vieMin;
   float vieMax;
   float exploseMax;
   
   sf::RectangleShape lineCurseurX;
   sf::RectangleShape lineCurseurY;
   barycentre tabBarycentres[64];
   sf::RectangleShape tabShapeBarycentres[64];
   sf::RectangleShape tabShapePoint[16];
   sf::Color bkgcouleur;
   sf::Color borderColor;
   int thickness;
   int nbc;
   int paveSelect;
   int barycentreID;
   int pointSelect;
   bool pointSelectFlag;
   int nbPave;
   std::string nameBkgFile;
   std::string pathBkgFile;
   std::string nameDestFile;
   std::string pathDestFile;
   sf::Vector2f bkgSurfaceSize;
   sf::RectangleShape shapeLineColor;
   sf::RectangleShape shapeBarycentreColor;
   sf::RectangleShape shapePointColor;
   
   bool barySelectFlag;
   int barycentreActif;
   bool paveSelectFlag;
   sf::Text surfaceTname;
   sf::Text surfaceTbkg;
   sf::Text surfaceTnbpave;
   sf::Text surfaceTw;
   sf::Text surfaceTh;
   sf::Text barycentreTcx;
   sf::Text barycentreTcy;
   sf::Text thicknessT;
   sf::Text nbcT;
   float defPosX;
   float defPosY;
   
   sf::Text test1;
   sf::Text test2;
   sf::Text test3;
   sf::Text test4;
   sf::Text test5;
   sf::Text test6;
   sf::Text test7;
   
   sf::Texture selectST;
   sf::Sprite defSurface;
   sf::Sprite defSurface2;
   float surfaceX;
   float surfaceY;
   float workSizeX;
   float workSizeY;
   float lastAppWidth;
   float lastAppHeight;

   
   selectFile fileSelector;
   
   public :
	
	newSurface(std::string config, std::string gui, std::string theme, std::string user);
  ~newSurface();
  
	bool drawSurface();
	void onResized(sf::Event e);
	void onClickSurface(sf::Event e);
   void onMouseMoveSurface(sf::Event e);
   void onMouseButtonUpSurface(sf::Event e);
   void mouseWheel(sf::Event e);
   void newSurfaceText(sf::Event e);
   void setSlideHeight();
   void saveSurface();
   void openSurface();
   void defBkgImage(std::string path, std::string nameFile);

	void defEllipse(float cx, float cy, float rdx, float rdy);
	int inPolygone(barycentre &shape, sf::Vector2f point);
	int isLeft(const sf::Vector2f &p0,const sf::Vector2f &p1,const sf::Vector2f &point);
	
	float distanceCentre(float cx, float cy, float x, float y);
	
	sf::Vector2f normaliseMouseXY(float x, float y);
	void newPolygone(sf::Event e,int nbc);
	void deletePolygone();
	void selectPolygone(float x, float y);
	void saveImage();
	void defParametre();
	void loadBkgImage();
	std::string surfaceDefPath();
	std::string surfaceDefFile();

};

#endif