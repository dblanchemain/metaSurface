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