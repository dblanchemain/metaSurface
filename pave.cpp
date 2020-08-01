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
#include <sstream>
#include <iostream>
#include <fstream>
#include <dirent.h>
#include <stdlib.h>
#include <ctgmath>
#include <string>
#include <cstring>
#include <boost/filesystem.hpp>

#include "pave.h"
#include "configuration.h"

using namespace std;

Pave::Pave(){
	mixgain=1;
}

Pave::~Pave(){
}

void Pave::defautPave(){
   fileSoundD="";
  	pathD="";	
	track=trackD;
	flagDawD=0;
	mixgain=1;
	cx=cxD;
	cy=cyD;
	dimMixer=dimMixerD;
	gainMin=gainMinD;
	gainMax=gainMaxD;
	gain=0;
	speed=1;
	canauxD=0;
   dureeD=0;
	readMode=0;
	fx=0;
	curseurType=curseurTypeD;
}


void Pave::setPath(string p){
	path=p;
}
void Pave::setPathD(string p){
	pathD=p;
}
void Pave::setFile(string f){
	fileSound=f;
}
void Pave::setFileD(string f){
	fileSoundD=f;
}
void Pave::setPaveDim(float d){
	dim=d;
}
void Pave::setFlagMulticanaux(bool f){
	flagMulticanaux=f;
}
void Pave::setFlagMulticanauxD(bool f){
	flagMulticanauxD=f;
}
void Pave::setDimMixer(float r){
	dimMixer=r;
}
void Pave::setDimMixerD(float r){
	dimMixerD=r;
}
void Pave::setX(int x){
	cx=x;
}
void Pave::setY(int y){
	cy=y;
}
void Pave::setGain(float g){
	gain=g;
}
void Pave::setMixgain(bool m){
	mixgain=m;
}
void Pave::setGainMin(float g){
	gainMin=g;
}
void Pave::setGainMinD(float g){
	gainMinD=g;
}
bool Pave::getFlagMulticanaux(){
	return flagMulticanaux;
}
bool Pave::getFlagMulticanauxD(){
	return flagMulticanauxD;
}
void Pave::setGainMax(float g){
	gainMax=g;
}
void Pave::setGainMaxD(float g){
	gainMaxD=g;
}
void Pave::setFlagDaw(int d){
	flagDaw=d;
}
void Pave::setFlagDawD(int d){
	flagDawD=d;
}
void Pave::setDgGain(bool dt){
	dtgain=dt;
}
void Pave::setFx(bool f){
	fx=f;
}
void Pave::setFxD(bool f){
	fxD=f;
}
void Pave::setMode(int m){
	readMode=m;
}
void Pave::setCurseurT(int ct){
	curseurType=ct;
}
void Pave::setCurseurTD(int ct){
	curseurTypeD=ct;
}
void Pave::setCurseurX(float curx){
	curseurX=curx;
}
void Pave::setCurseurY(float cury){
	curseurY=cury;
}
void Pave::setCurseurEtat(bool cure){
	curseurE=cure;
}

void Pave::setNbCanaux(int nb){
	canaux=nb;
}
void Pave::setDuree(float d){
	duree=d;
}
void Pave::setExplose(int ex){
	explose=ex;
}
void Pave::setTrack(int tk){
	track=tk;
}
void Pave::setTrackD(int tk){
	trackD=tk;
}
void Pave::setPoint(int id,sf::Vector2f dc){
	point[id]=dc;
}
void Pave::setDistanceMax(float dt){
	distanceMax=dt;
}

string Pave::getPath(){
	return path;
}
string Pave::getFile(){
	return fileSound;
}
int Pave::getDim(){
	return dim;
}
int Pave::getTrack(){
	return track;
}
int Pave::getFlagDaw(){
	return flagDaw;
}
float Pave::getCx(){
	return cx;
}
float Pave::getCy(){
	return cy;
}

float Pave::getDimMixer(){
	return dimMixer;
}
bool Pave::getMixgain(){
	return mixgain;
}
float Pave::getGainMin(){
	return gainMin;
}
float Pave::getGainMax(){
	return gainMax;
}
float Pave::getGain(){
	return gain;
}
float Pave::getSpeed(){
	return speed;
}
float Pave::getMode(){
	return readMode;
}
bool Pave::getDgGain(){
	return dtgain;
}
bool Pave::getFx(){
	return fx;
}
int Pave::getCurseurT(){
	return curseurType;
}
float Pave::getCurseurX(){
	return curseurX;
}
float Pave::getCurseurY(){
	return curseurY;
}
bool Pave::getCurseurEtat(){
	return curseurE;
}
sf::Vector2f Pave::getPoint(int id){
	return point[id];
}
float Pave::getDistanceMax(){
	return distanceMax;
}
sf::Sprite Pave::getCurseur(){
	return curseur;
}
int Pave::getNbCanaux(){
	return canaux;
}
float Pave::getDuree(){
	return duree;
}
int Pave::getExplose(){
	return explose;
}

int Pave::getFlagDawD(){
	return flagDawD;
}
float Pave::getDimMixerD(){
	return dimMixerD;
}
float Pave::getGainMinD(){
	return gainMinD;
}
float Pave::getGainMaxD(){
	return gainMaxD;
}
