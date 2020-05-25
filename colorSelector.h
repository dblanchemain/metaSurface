#ifndef DEF_COLORSELECTOR
#define DEF_COLORSELECTOR

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
#include <stdlib.h>
#include <string>


class colorSelector{

	private :
   
   std::string gui;
   sf::RenderWindow winSelector;
   sf::Texture colorHsv;
   sf::Sprite disqueHsv;
	float cv=M_PI/180;
	float teinte;
	unsigned char couleur;
	float saturation;
	float valeur;
	unsigned char rouge;
	unsigned char vert;
	unsigned char bleu;
	unsigned char rougeP;
	unsigned char vertP;
	unsigned char bleuP;
	int defOpacity;
	bool defReturn;
	sf::Color shapeSelColor[12];
	sf::CircleShape selTriangle;
	sf::Color selColorReturn;
	float selTriangleX;
	float selTriangleY;
	float s0x;
	float s0y;
	float s1x;
	float s1y;
	float s2x;
	float s2y;
	sf::VertexArray triangle;
	sf::VertexArray opacity;
	sf::Text colorTeinteValue;
	sf::Text colorSaturationValue;
	sf::Text colorValeurValue;
	sf::Text colorRougeValue;
	sf::Text colorVertValue;
	sf::Text colorBleuValue;
	sf::Text selectColorHex;
	sf::Text selectOpacity;
	
	sf::Font font;
	sf::RectangleShape shapeColorActu;
	sf::RectangleShape shapeColorPast;
	int paveSelect;
	sf::RectangleShape shapeColorSel[12];
	sf::RectangleShape shapeOpacity;

	public :
	
	colorSelector();
  ~colorSelector();

	void RGBtoHSV( const unsigned char src_r, const unsigned char src_g, const unsigned char src_b);
	sf::Color HSVtoRGB(float H, float S, float V);
	int colorSelectorOpen();
	bool drawColorSelector(std::string gui);
	void onClickSelColor(sf::Event e);
	void onColorUp();
	void defColorHSV();
	void defColorRGB();
	void defColorString();
	void reInit();
	void colorSelReturn();
	void colorSelectorClose();
	sf::Color colorSelect();
	sf::Color defComplementaire(float t, float s, float v);
	void onMouseMoveSelectColor(sf::Event e);
   int inPolygone(sf::Vector2f p);
   int isLeft(const sf::Vector2f &p0,const sf::Vector2f &p1,const sf::Vector2f &point);
};
#endif
