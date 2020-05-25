#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <ctgmath>
#include <string>
#include <cstring>

#include "omni.h"

using namespace std;

Omni::Omni(){
  
}

Omni::~Omni(){
}
void Omni::setEtat(bool e){
	etat=e;
}
void Omni::setDirectionParam(float x, float y){
	directionParam.x=x;
	directionParam.y=y;
}
void Omni::setDirectionParamX(float x){
	directionParam.x=x;
}
void Omni::setDirectionParamY(float y){
	directionParam.y=y;
}
void Omni::setDirection(float x, float y){
	direction.x=x;
	direction.y=y;
}
void Omni::setDirectionX(float x){
	direction.x=x;
}
void Omni::setDirectionY(float y){
	direction.y=y;
}
void Omni::setComptimeD(float t){
	comptimeD=t;
}
void Omni::setComptime(float t){
	comptime=t;
}
void Omni::setExplose(int ex){
	explose=ex;
}
void Omni::setDureeVie(int dv){
	dureeVie=dv;
}
void Omni::initComptime(){
	comptime=comptimeD;
}
int Omni::getExplose(){
	return explose;
}
int Omni::getDureeVie(){
	return dureeVie;
}
bool Omni::getEtat(){
	return etat;
}
float  Omni::getDirectionParamX(){
	return directionParam.x;
}
float  Omni::getDirectionParamY(){
	return directionParam.y;
}
float  Omni::getDirectionX(){
	return direction.x;
}
float  Omni::getDirectionY(){
	return direction.y;
}
float  Omni::getComptime(){
	return comptime;
}