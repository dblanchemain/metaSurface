#include <SFML/Graphics.hpp>
#include <libgen.h>
#include <sstream>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <iomanip>
#include <ctgmath>
#include <string>
#include <cstring>
#include <boost/filesystem.hpp>
#include <vector>


#include "colorSelector.h"
#define min_f(a, b, c)  (fminf(a, fminf(b, c)))
#define max_f(a, b, c) (fmaxf(a, fmaxf(b, c)))

using namespace std;

//*******************************************************************************************
//                                              Gui Color Selector
//*******************************************************************************************

colorSelector::colorSelector(){
reInit();

}
colorSelector::~colorSelector(){
	}
bool colorSelector::drawColorSelector(string gui){
stringstream adr;
adr << std::fixed << gui<<"/colorSel.png";
colorHsv.loadFromFile(adr.str());
adr.clear();
adr.str("");
colorHsv.setSmooth(true);
disqueHsv.setTexture(colorHsv);
disqueHsv.setPosition(sf::Vector2f(0, 0));
adr << std::fixed << gui<<"/Arial.ttf";
font.loadFromFile(adr.str());
adr.clear();
adr.str("");

colorTeinteValue.setFont(font);
colorTeinteValue.setCharacterSize(13);
colorTeinteValue.setFillColor(sf::Color(0,0,0));
adr << std::fixed<< std::setprecision(0)<<teinte;
colorTeinteValue.setString(adr.str());	
colorTeinteValue.setPosition(328-colorTeinteValue.getLocalBounds().width-2,40);
adr.clear();
adr.str("");
colorSaturationValue.setFont(font);	
colorSaturationValue.setCharacterSize(13);
colorSaturationValue.setFillColor(sf::Color(0,0,0));
adr << std::fixed<< std::setprecision(0)<<saturation*100;
colorSaturationValue.setString(adr.str());	
colorSaturationValue.setPosition(328-colorSaturationValue.getLocalBounds().width-2,66);
adr.clear();
adr.str("");
colorValeurValue.setFont(font);	
colorValeurValue.setCharacterSize(13);
colorValeurValue.setFillColor(sf::Color(0,0,0));
adr << std::fixed<< std::setprecision(0)<<valeur*100;
colorValeurValue.setString(adr.str());	
colorValeurValue.setPosition(328-colorValeurValue.getLocalBounds().width-2,92);
adr.clear();
adr.str("");
colorRougeValue.setFont(font);	
colorRougeValue.setString(to_string(rouge));
colorRougeValue.setCharacterSize(13);
colorRougeValue.setFillColor(sf::Color(0,0,0));
colorRougeValue.setPosition(462-colorRougeValue.getLocalBounds().width-2,40);
colorVertValue.setFont(font);	
colorVertValue.setString(to_string(vert));
colorVertValue.setCharacterSize(13);
colorVertValue.setFillColor(sf::Color(0,0,0));
colorVertValue.setPosition(462-colorVertValue.getLocalBounds().width-2,66);
colorBleuValue.setFont(font);	
colorBleuValue.setString(to_string(bleu));
colorBleuValue.setCharacterSize(13);
colorBleuValue.setFillColor(sf::Color(0,0,0));
colorBleuValue.setPosition(462-colorBleuValue.getLocalBounds().width-2,92);

selectColorHex.setFont(font);	
selectColorHex.setString("");
selectColorHex.setCharacterSize(13);
selectColorHex.setFillColor(sf::Color(0,0,0));
selectColorHex.setPosition(sf::Vector2f(420,126));

selectOpacity.setFont(font);	
selectOpacity.setString("255");
selectOpacity.setCharacterSize(13);
selectOpacity.setFillColor(sf::Color(0,0,0));
selectOpacity.setPosition(462-selectOpacity.getLocalBounds().width-2,160);

shapeSelColor[0]=sf::Color(255,255,255);
shapeSelColor[1]=sf::Color(255,255,255);
shapeSelColor[2]=sf::Color(255,255,255);
shapeSelColor[3]=sf::Color(255,255,255);
shapeSelColor[4]=sf::Color(255,255,255);
shapeSelColor[5]=sf::Color(255,255,255);
shapeSelColor[6]=sf::Color(255,255,255);
shapeSelColor[7]=sf::Color(255,255,255);
shapeSelColor[8]=sf::Color(255,255,255);
shapeSelColor[9]=sf::Color(255,255,255);
shapeSelColor[10]=sf::Color(255,255,255);
shapeSelColor[11]=sf::Color(255,255,255);

shapeColorSel[0].setSize(sf::Vector2f(20,15));
shapeColorSel[0].setPosition(sf::Vector2f(294,194));
shapeColorSel[1].setSize(sf::Vector2f(20,15));
shapeColorSel[1].setPosition(sf::Vector2f(326,194));
shapeColorSel[2].setSize(sf::Vector2f(20,15));
shapeColorSel[2].setPosition(sf::Vector2f(358,194));
shapeColorSel[3].setSize(sf::Vector2f(20,15));
shapeColorSel[3].setPosition(sf::Vector2f(392,194));
shapeColorSel[4].setSize(sf::Vector2f(20,15));
shapeColorSel[4].setPosition(sf::Vector2f(425,194));
shapeColorSel[5].setSize(sf::Vector2f(20,15));
shapeColorSel[5].setPosition(sf::Vector2f(457,194));
shapeColorSel[6].setSize(sf::Vector2f(20,15));
shapeColorSel[6].setPosition(sf::Vector2f(294,221));
shapeColorSel[7].setSize(sf::Vector2f(20,15));
shapeColorSel[7].setPosition(sf::Vector2f(326,221));
shapeColorSel[8].setSize(sf::Vector2f(20,15));
shapeColorSel[8].setPosition(sf::Vector2f(358,221));
shapeColorSel[9].setSize(sf::Vector2f(20,15));
shapeColorSel[9].setPosition(sf::Vector2f(391,221));
shapeColorSel[10].setSize(sf::Vector2f(20,15));
shapeColorSel[10].setPosition(sf::Vector2f(425,221));
shapeColorSel[11].setSize(sf::Vector2f(20,15));
shapeColorSel[11].setPosition(sf::Vector2f(458,221));

shapeColorActu.setSize(sf::Vector2f(60,17));
shapeColorActu.setPosition(sf::Vector2f(96,228));
shapeColorPast.setSize(sf::Vector2f(60,17));
shapeColorPast.setPosition(sf::Vector2f(96,264));

selTriangle.setFillColor(sf::Color(255, 255, 255,0));
selTriangle.setOutlineThickness(2.f);
selTriangle.setOutlineColor(sf::Color(125,125,125));


shapeOpacity.setSize(sf::Vector2f(2,18));
shapeOpacity.setPosition(sf::Vector2f(420,158));
shapeOpacity.setFillColor(sf::Color(defComplementaire(teinte, saturation, valeur)));


sf::ContextSettings settings;
settings.antialiasingLevel = 8;
winSelector.create(sf::VideoMode(500,300), "Sélecteur de couleur", sf::Style::Titlebar|sf::Style::Close, settings);

while (winSelector.isOpen()) {
        // Process events
        sf::Event eventSelectColor;
	while (winSelector.pollEvent(eventSelectColor)){ 
	 	 switch (eventSelectColor.type){
	  			case sf::Event::Closed:
	      		colorSelectorClose();
	      	break;
	      	case  sf::Event::TextEntered:	
				break;	
	      	case sf::Event::MouseButtonPressed:
	     			onClickSelColor(eventSelectColor);
	      	break;
	      	case sf::Event::MouseMoved:
	     			onMouseMoveSelectColor(eventSelectColor);
	      	break;
	      	case sf::Event::MouseButtonReleased:
	     			onColorUp();
	      	break;
	  				  					// on ne traite pas les autres types d'évènements
	  			default:
	      	break;
	  		  	 }            
	}
	winSelector.setActive(true);
   winSelector.pushGLStates();
   winSelector.clear(sf::Color(19,37,53));
   
   sf::RectangleShape shapeNo(sf::Vector2f(316,384));
	shapeNo.setFillColor(sf::Color(203,213,217));
	shapeNo.setPosition(sf::Vector2f(2,2));
	winSelector.draw(shapeNo); 
	winSelector.draw(disqueHsv);
											// on définit la position des sommets du triangle
	s0x=cos(-teinte*cv)*80;
	s0y=sin(-teinte*cv)*80;
	s1x=cos((120-teinte)*cv)*80;
	s1y=sin((120-teinte)*cv)*80;
	s2x=cos((240-teinte)*cv)*80;
	s2y=sin((240-teinte)*cv)*80;
	triangle[0].position = sf::Vector2f(110+s0x, 112+s0y);
	triangle[1].position = sf::Vector2f(110+s1x, 112+s1y);
	triangle[2].position = sf::Vector2f(110+s2x,112+s2y);

   // on définit la couleur des sommets du triangle
	
	triangle[0].color = sf::Color(rouge,vert,bleu);
	triangle[1].color = sf::Color::Black;
	triangle[2].color = sf::Color::White;
   winSelector.draw(triangle);
   
   winSelector.draw(colorTeinteValue);
   winSelector.draw(colorSaturationValue);
   winSelector.draw(colorValeurValue);

   winSelector.draw(colorRougeValue);
   winSelector.draw(colorVertValue);
   winSelector.draw(colorBleuValue);
   
   winSelector.draw(shapeColorActu);
   winSelector.draw(shapeColorPast);
   
   for(int i=0;i<12;i++){
   	winSelector.draw(shapeColorSel[i]);
   }
	
   winSelector.draw(selectColorHex);
   
   selTriangle.setOutlineColor(sf::Color(125,125,125));
   selTriangle.setPosition(sf::Vector2f(selTriangleX,selTriangleY));
   winSelector.draw(selTriangle);
   
   opacity[0].color = sf::Color(rouge,vert,bleu,0);
	opacity[1].color = sf::Color(rouge,vert,bleu,255);
	opacity[2].color = sf::Color(rouge,vert,bleu,255);
	opacity[3].color = sf::Color(rouge,vert,bleu,0);
	winSelector.draw(opacity);
	
	winSelector.draw(shapeOpacity);
	winSelector.draw(selectOpacity); 
   
	winSelector.display();
	winSelector.popGLStates();
	winSelector.setActive(false);

}
	return defReturn; 
} 


void colorSelector::onColorUp(){
	rougeP=rouge;
	vertP=vert;
	bleuP=bleu;
	string tdef,tdef2,tdef3,tdef4;
	stringstream ss1, ss2, ss3, ss4;
	ss1 << hex << (int)rouge;
	if(rouge<16){
		tdef = "0"+ss1.str();
	}else{
		tdef = ss1.str();
	}
	ss2 << hex << (int)vert;
	if(vert<16){
		tdef2 = "0"+ss2.str();
	}else{
		tdef2 = ss2.str();
	}
	ss3 << hex << (int)bleu;
   if(bleu<16){
		tdef3 = "0"+ss3.str();
	}else{
		tdef3 = ss3.str();
	}
	ss4 << hex << (int)defOpacity;
   if(defOpacity<16){
		tdef4 = "0"+ss4.str();
	}else{
		tdef4 = ss4.str();
	}
	selectColorHex.setString("#"+tdef+tdef2+tdef3+tdef4);
	selectColorHex.setPosition(478-selectColorHex.getLocalBounds().width-2,126);
}

void colorSelector::onClickSelColor(sf::Event e){
  float distanceCentre;
  if(e.mouseButton.x>166 && e.mouseButton.x<264 && e.mouseButton.y>262 && e.mouseButton.y<285){
		reInit();
  }
  if(e.mouseButton.x>272 && e.mouseButton.x<374 && e.mouseButton.y>262 && e.mouseButton.y<285){
		winSelector.close();
  }
  if(e.mouseButton.x>382 && e.mouseButton.x<482 && e.mouseButton.y>262 && e.mouseButton.y<285){
  		colorSelReturn();
  }
  if(e.mouseButton.x>32 && e.mouseButton.x<180 && e.mouseButton.y>36 && e.mouseButton.y<190){
  	 distanceCentre=sqrt(pow(e.mouseButton.x-110,2)+pow(e.mouseButton.y-113.5,2));
  	 if(distanceCentre<80){
  	 	int ret=inPolygone(sf::Vector2f(e.mouseButton.x,e.mouseButton.y));
		if(ret==1){
			shapeColorPast.setFillColor(sf::Color(rougeP,vertP,bleuP));
			selTriangleX=e.mouseButton.x;
			selTriangleY=e.mouseButton.y;
			defColorHSV();
		}
	 }
  }
  if(e.mouseButton.x>290 && e.mouseButton.x<482 && e.mouseButton.y>192 && e.mouseButton.y<242){
		paveSelect=(482-e.mouseButton.x)/32;
		paveSelect=11-((((242-e.mouseButton.y)/25)*6)+paveSelect);
		rouge=(int)shapeColorSel[paveSelect].getFillColor().r;
		vert=(int)shapeColorSel[paveSelect].getFillColor().g;
		bleu=(int)shapeColorSel[paveSelect].getFillColor().b;
		defColorRGB();
  }
  if(e.mouseButton.x>238 && e.mouseButton.x<264 && e.mouseButton.y>192 && e.mouseButton.y<214){
		shapeColorSel[paveSelect].setFillColor(shapeColorActu.getFillColor());
  }
  if(e.mouseButton.x>334 && e.mouseButton.x<346 && e.mouseButton.y>40 && e.mouseButton.y<50){
		teinte=teinte+1;
		if(teinte>360){
		 teinte=0;
		}
		defColorHSV();
	}
	if(e.mouseButton.x>334 && e.mouseButton.x<346 && e.mouseButton.y>50 && e.mouseButton.y<60){
		teinte=teinte-1;
		if(teinte<0){
		 teinte=360;
		}
		defColorHSV();
	}
	if(e.mouseButton.x>334 && e.mouseButton.x<346 && e.mouseButton.y>66 && e.mouseButton.y<76){
		saturation=saturation+0.01;
		if(saturation>1){
		 saturation=0;
		}
		defColorHSV();
	}
	if(e.mouseButton.x>334 && e.mouseButton.x<346 && e.mouseButton.y>76 && e.mouseButton.y<86){
		saturation=saturation-0.01;
		if(saturation<0){
		 saturation=1;
		}
		defColorHSV();
	}
	if(e.mouseButton.x>334 && e.mouseButton.x<346 && e.mouseButton.y>92 && e.mouseButton.y<102){
		valeur=valeur+0.01;
		if(valeur>1){
		 valeur=0;
		}
		defColorHSV();
	}
	if(e.mouseButton.x>334 && e.mouseButton.x<346 && e.mouseButton.y>102 && e.mouseButton.y<112){
		valeur=valeur-0.01;
		if(valeur<0){
		 valeur=1;
		}
		defColorHSV();
	}
	if(e.mouseButton.x>472 && e.mouseButton.x<486 && e.mouseButton.y>40 && e.mouseButton.y<50){
		rouge=rouge+1;
		if(rouge>255){
		 rouge=0;
		}
		colorRougeValue.setString(to_string(rouge));
		defColorRGB();
	}
	if(e.mouseButton.x>472 && e.mouseButton.x<486 && e.mouseButton.y>50 && e.mouseButton.y<60){
		rouge=rouge-1;
		if(rouge<1){
		 rouge=255;
		}
		colorRougeValue.setString(to_string(rouge));
		defColorRGB();
	}
	if(e.mouseButton.x>472 && e.mouseButton.x<486 && e.mouseButton.y>66 && e.mouseButton.y<76){
		vert=vert+1;
		if(vert>255){
		 vert=0;
		}
		colorVertValue.setString(to_string(vert));
		defColorRGB();
	}
	if(e.mouseButton.x>472 && e.mouseButton.x<486 && e.mouseButton.y>76 && e.mouseButton.y<86){
		vert=vert-1;
		if(vert<1){
		 vert=255;
		}
		colorVertValue.setString(to_string(vert));
		defColorRGB();
	}
	if(e.mouseButton.x>472 && e.mouseButton.x<486 && e.mouseButton.y>92 && e.mouseButton.y<102){
		bleu=bleu+1;
		if(bleu>255){
		 bleu=0;
		}
		colorBleuValue.setString(to_string(bleu));
		defColorRGB();
	}
	if(e.mouseButton.x>472 && e.mouseButton.x<486 && e.mouseButton.y>102 && e.mouseButton.y<112){
		bleu=bleu-1;
		if(bleu<1){
		 bleu=255;
		}
		colorBleuValue.setString(to_string(bleu));
		defColorRGB();
	}
	if(e.mouseButton.x>230 && e.mouseButton.x<420 && e.mouseButton.y>160 && e.mouseButton.y<180){
		stringstream adr;
		float nopacite=(e.mouseButton.x-232)*1.37;
		if(nopacite<1){
			nopacite=0;
		}
		if(nopacite>255){
			nopacite=255;
		}
		defOpacity=nopacite;
		
		shapeOpacity.setPosition(e.mouseMove.x,shapeOpacity.getPosition().y);
		adr << std::fixed<< std::setprecision(0)<<nopacite;
		selectOpacity.setString(adr.str());	
		adr.clear();
		adr.str("");
		selectOpacity.setPosition(462-selectOpacity.getLocalBounds().width-2,160);
	}
}
void colorSelector::onMouseMoveSelectColor(sf::Event e){
   float distanceCentre, distance2, distance3;
   float x,y;
  if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
  	distanceCentre=sqrt(pow(e.mouseMove.x-110,2)+pow(e.mouseMove.y-113.5,2));
   if(e.mouseMove.x>10 && e.mouseMove.x<210 && e.mouseMove.y>15 && e.mouseMove.y<212){
		if(distanceCentre>80 && distanceCentre<100){
			x=e.mouseMove.x-110;
			y=113.5-e.mouseMove.y;
			teinte=atan2(y,x);
			if(teinte>0){
				teinte=teinte*180/M_PI;
			}else{
				teinte=360+(teinte*180/M_PI);
			}
			sf::Color rt=HSVtoRGB(teinte, saturation, valeur);
			rouge = rt.r;
			vert = rt.g;
			bleu = rt.b;
			defColorString();
		}	
	}
	if(distanceCentre<80 ){
		int ret=inPolygone(sf::Vector2f(e.mouseMove.x,e.mouseMove.y));
		if(ret==1){
			x=110+cos((240-teinte)*cv)*80;
		   y=112+sin((240-teinte)*cv)*80;
		   distance2=sqrt(pow(e.mouseMove.x-x,2)+pow(e.mouseMove.y-y,2));
		   x=110+cos((120-teinte)*cv)*80;
		   y=112+sin((120-teinte)*cv)*80;
		   distance3=sqrt(pow(e.mouseMove.x-x,2)+pow(e.mouseMove.y-y,2));
		   if(saturation>=0 && saturation<=1 && valeur>=0 && valeur<=1 ){
		   	float nsaturation=distance2/133;
		   	float nvaleur=distance3/133;
		   	if(nsaturation>0.04 && nsaturation<0.98 && nvaleur>0.04 && nvaleur<0.98){
			   	selTriangleX=e.mouseMove.x;
					selTriangleY=e.mouseMove.y;
					selTriangle.setPosition(sf::Vector2f(selTriangleX,selTriangleY));
					saturation=nsaturation;
					valeur=nvaleur;
					defColorHSV();
				}
		   }
	  }
	}
	if(e.mouseMove.x>230 && e.mouseMove.x<420 && e.mouseMove.y>160 && e.mouseMove.y<180){
		stringstream adr;
		float nopacite=(e.mouseMove.x-232)*1.37;
		if(nopacite<1){
			nopacite=0;
		}
		if(nopacite>255){
			nopacite=255;
		}
		defOpacity=nopacite;
		shapeOpacity.setPosition(e.mouseMove.x,shapeOpacity.getPosition().y);
		shapeOpacity.setFillColor(defComplementaire(teinte, saturation, valeur));
		adr << std::fixed<< std::setprecision(0)<<nopacite;
		selectOpacity.setString(adr.str());	
		adr.clear();
		adr.str("");
		selectOpacity.setPosition(462-selectOpacity.getLocalBounds().width-2,160);
	}
  }
}
void colorSelector::defColorHSV(){
	sf::Color rt=HSVtoRGB(teinte, saturation, valeur);
	rouge = rt.r;
	vert = rt.g;
	bleu = rt.b;
	shapeColorActu.setFillColor(sf::Color(rouge,vert,bleu));
	defColorString();
}
void colorSelector::defColorRGB(){
	RGBtoHSV(rouge, vert, bleu);
	defColorString();
}
void colorSelector::defColorString(){
	colorTeinteValue.setString(to_string((int)teinte));
 	colorTeinteValue.setPosition(328-colorTeinteValue.getLocalBounds().width-2,40);
	int st=saturation*100;
	colorSaturationValue.setString(to_string((char)st));
	colorSaturationValue.setPosition(328-colorSaturationValue.getLocalBounds().width-2,66);
	st=valeur*100;
	colorValeurValue.setString(to_string((char)st));
	colorValeurValue.setPosition(328-colorValeurValue.getLocalBounds().width-2,90);
	colorRougeValue.setString(to_string(rouge));
	colorRougeValue.setPosition(462-colorRougeValue.getLocalBounds().width-2,40);
	colorVertValue.setString(to_string(vert));
	colorVertValue.setPosition(462-colorVertValue.getLocalBounds().width-2,66);
	colorBleuValue.setString(to_string(bleu));
	colorBleuValue.setPosition(462-colorBleuValue.getLocalBounds().width-2,90);
	shapeOpacity.setFillColor(sf::Color(defComplementaire(teinte, saturation, valeur)));
}
void colorSelector::colorSelectorClose(){
	defReturn=0;
	winSelector.close();
}
void colorSelector::colorSelReturn(){
	defReturn=1;
	winSelector.close();
}
sf::Color colorSelector::colorSelect(){
	return sf::Color(rouge,vert,bleu,(int)defOpacity);
}
void colorSelector::reInit(){
	teinte=0;
	couleur=0;
	saturation=1;
	valeur=1;
	rouge=0;
	vert=0;
	bleu=0;
	defOpacity=255;
	selectOpacity.setString("255");
	rougeP=255;
	vertP=255;
	bleuP=255;
	vertP=255;
	bleuP=255;
	for(int i=0;i<12;i++){
		shapeColorSel[i].setFillColor(sf::Color(255,255,255));
	}
	selTriangle.setRadius(2.f);
	triangle.setPrimitiveType(sf::Triangles);
	triangle.resize(3);
	opacity.setPrimitiveType(sf::Quads);
	opacity.resize(4);
	opacity[0].position = sf::Vector2f(230, 160);
	opacity[1].position = sf::Vector2f(420, 160);
	opacity[2].position = sf::Vector2f(420,175);
	opacity[3].position = sf::Vector2f(230,175);
	selTriangleX=180;
	selTriangleY=111;
	defColorString();
	shapeColorActu.setFillColor(sf::Color(255,255,255));
	shapeColorPast.setFillColor(sf::Color(255,255,255));
}
sf::Color colorSelector::defComplementaire(float t, float s, float v){
	int cteinte=t+180;
	int ns,nv;
	if(cteinte>360){
		cteinte=cteinte-360;
	}
	if(s>50){
		ns=s-50;
	}else{
		ns=s+50;
	}
	if(v>50){
		nv=s-50;
	}else{
		nv=s+50;
	}
	sf::Color complementaire=HSVtoRGB(cteinte, ns, nv);
	return sf::Color (complementaire.r,complementaire.g,complementaire.b,255);
}
void colorSelector::RGBtoHSV( const unsigned char src_r, const unsigned char src_g, const unsigned char src_b) {
 	 float r = src_r / 255.0f;
    float g = src_g / 255.0f;
    float b = src_b / 255.0f;

    float h, s, v; // h:0-360.0, s:0.0-1.0, v:0.0-1.0

    float max = max_f(r, g, b);
    float min = min_f(r, g, b);

    v = max;

    if (max == 0.0f) {
        s = 0;
        h = 0;
    }
    else if (max - min == 0.0f) {
        s = 0;
        h = 0;
    }
    else {
        s = (max - min) / max;

        if (max == r) {
            h = 60 * ((g - b) / (max - min)) + 0;
        }
        else if (max == g) {
            h = 60 * ((b - r) / (max - min)) + 120;
        }
        else {
            h = 60 * ((r - g) / (max - min)) + 240;
        }
    }

    if (h < 0) h += 360.0f;

    teinte = h;
    saturation = s;
	 valeur = v;
}

sf::Color colorSelector::HSVtoRGB(float H, float S, float V) {
	double C = S * V;
	double X = C * (1 - abs(fmod(H / 60.0, 2) - 1));
	double m = V - C;
	double Rs, Gs, Bs;

	if(H >= 0 && H < 60) {
		Rs = C;
		Gs = X;
		Bs = 0;	
	}
	if(H >= 60 && H < 120) {	
		Rs = X;
		Gs = C;
		Bs = 0;	
	}
	if(H >= 120 && H < 180) {
		Rs = 0;
		Gs = C;
		Bs = X;	
	}
	if(H >= 180 && H < 240) {
		Rs = 0;
		Gs = X;
		Bs = C;	
	}
	if(H >= 240 && H < 300) {
		Rs = X;
		Gs = 0;
		Bs = C;	
	}
	if(H >= 300 && H < 360){
		Rs = C;
		Gs = 0;
		Bs = X;
	}
	return sf::Color((Rs + m) * 255,(Gs + m) * 255,(Bs + m) * 255);
}

int colorSelector::inPolygone(sf::Vector2f p){
	int nbc=3;
	sf::Vector2f s1,s2;
	sf::Vector2f point[4];
	int    wn = 0;    // the  winding number counter

	point[0].x=s0x+110;
	point[0].y=s0y+112;
	point[1].x=s1x+110;
	point[1].y=s1y+112;
	point[2].x=s2x+110;
	point[2].y=s2y+112;
	point[3].x=s0x+110;
	point[3].y=s0y+112;			
    for (int i = 0; i<nbc; i++) {   // edge from V[i] to  V[i+1]
    	  s1=point[i];
    	  s2=point[i+1];
		  if(s1.y<=p.y){
		  	 if(s2.y>p.y){
		  	 	if(isLeft(s1,s2,p)>0){
		  	 		++wn;
		  	 	}
		  	 }
		  }else{
		  	 if(s2.y<=p.y){
		  	 	if(isLeft(s1,s2,p)<0){
		  	 		--wn;
		  	 	}
		  	 }
		  } 
    }
	return wn;
	
}
int colorSelector::isLeft(const sf::Vector2f &p0,const sf::Vector2f &p1,const sf::Vector2f &point){
    return ((p1.x - p0.x) * (point.y - p0.y) -
            (point.x - p0.x) * (p1.y - p0.y));
}