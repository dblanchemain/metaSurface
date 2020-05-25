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

void Pave::defautCompression(){
	compresRatioB=compresDRatioB;
   compresIntRatioMin=compresDIntRatioMin;
   compresIntRatioMax=compresDIntRatioMax;
   compresIntRatioScale=compresDIntRatioScale;
   compresRatioMode=compresDRatioMode;
   compresThresB=compresDThresB;
   compresIntThresMin=compresDIntThresMin;
   compresIntThresMax=compresDIntThresMax;
   compresIntThresScale=compresDIntThresScale;
   compresThresMode=compresDThresMode;
   compresTimeB=compresTimeB;
   compresIntTimeMin=compresDIntTimeMin;
   compresIntTimeMax=compresDIntTimeMax;
   compresIntTimeScale=compresDIntTimeScale;
   compresTimeMode=compresDTimeMode;
   compresReleaseB=compresDReleaseB;
   compresIntReleaseMin=compresDIntReleaseMin;
   compresIntReleaseMax=compresDIntReleaseMax;
   compresIntReleaseScale=compresDIntReleaseScale;
   compresReleaseMode=compresDReleaseMode;
   compresGainB=compresDGainB;
   compresIntGainMin=compresDIntGainMin;
   compresIntGainMax=compresDIntGainMax;
   compresIntGainScale=compresDIntGainScale;
   compresGainMode=compresDGainMode;
}
void Pave::defautDelay(){
	delayDelB=delayDDelB;
   delayIntDelayMin=delayDDelMin;
   delayIntDelayMax=delayDDelMax;
   delayIntDelayScale=delayDDelScale;
   delayDelayMode=delayDDelMode;
   delayFbkB=delayDFbkB;
   delayIntFbkMin=delayDFbkMin;
   delayIntFbkMax=delayDFbkMax;
   delayIntFbkScale=delayDFbkScale;
   delayFbkMode=delayDFbkMode;
   delayInterpolB=delayInterpolB;
   delayIntInterpolMin=delayDInterpolMin;
   delayIntInterpolMax=delayDInterpolMax;
   delayIntInterpolScale=delayDInterpolScale;
   delayInterpolMode=delayDInterpolMode;
}
void Pave::defautDistortion(){
	distortionDriveB=distortionDDriveB;
   distortionIntDriveMin=distortionDDriveMin;
   distortionIntDriveMax=distortionDDriveMax;
   distortionIntDriveScale=distortionDDriveScale;
   distortionDriveMode=distortionDDriveMode;
   distortionOffsetB=distortionDOffsetB;
   distortionIntOffsetMin=distortionDOffsetMin;
   distortionIntOffsetMax=distortionDOffsetMax;
   distortionIntOffsetScale=distortionDOffsetScale;
   distortionOffsetMode=distortionDOffsetMode;
}
void Pave::defautFlanger(){
	flangerSpeedB=flangerDSpeedB;
   flangerSpeedMin=flangerDSpeedMin;
   flangerSpeedMax=flangerDSpeedMax;
   flangerSpeedScale=flangerDSpeedScale;
   flangerSpeedMode=flangerDSpeedMode;
   flangerDepthB=flangerDDepthB;
   flangerDepthMin=flangerDDepthMin;
   flangerDepthMax=flangerDDepthMax;
   flangerDepthScale=flangerDDepthScale;
   flangerDepthMode=flangerDDepthMode;
   flangerFbkB=flangerDFbkB;
   flangerFbkMin=flangerDFbkMin;
   flangerFbkMax=flangerDFbkMax;
   flangerFbkScale=flangerDFbkScale;
   flangerFbkMode=flangerDFbkMode;
   flangerDelayB=flangerDDelayB;
   flangerDelayMin=flangerDDelayMin;
   flangerDelayMax=flangerDDelayMax;
   flangerDelayScale=flangerDDelayScale;
   flangerDelayMode=flangerDDelayMode;
   flangerOffsetB=flangerDOffsetB;
   flangerOffsetMin=flangerDOffsetMin;
   flangerOffsetMax=flangerDOffsetMax;
   flangerOffsetScale=flangerDOffsetScale;
   flangerOffsetMode=flangerDOffsetMode;
   flangerLevelB=flangerDLevelB;
   flangerLevelMin=flangerDLevelMin;
   flangerLevelMax=flangerDLevelMax;
   flangerLevelScale=flangerDLevelScale;
   flangerLevelMode=flangerDLevelMode;
}
void Pave::defautFreeverb(){
	freeverbDampB=freeverbDDampB;
   freeverbDampMin=freeverbDDampMin;
   freeverbDampMax=freeverbDDampMax;
   freeverbDampScale=freeverbDDampScale;
   freeverbDampMode=freeverbDDampMode;
   freeverbRoomB=freeverbDRoomB;
   freeverbRoomMin=freeverbDRoomMin;
   freeverbRoomMax=freeverbDRoomMax;
   freeverbRoomScale=freeverbDRoomScale;
   freeverbRoomMode=freeverbDRoomMode;
   freeverbStereoB=freeverbDStereoB;
   freeverbStereoMin=freeverbDStereoMin;
   freeverbStereoMax=freeverbDStereoMax;
   freeverbStereoScale=freeverbDStereoScale;
   freeverbStereoMode=freeverbDStereoMode;
   freeverbWetB=freeverbDWetB;
   freeverbWetMin=freeverbDWetMin;
   freeverbWetMax=freeverbDWetMax;
   freeverbWetScale=freeverbDWetScale;
   freeverbWetMode=freeverbDWetMode;
}
void Pave::defautGranulator(){
	granulatorDecalB=granulatorDDecalB;
   granulatorDecalMin=granulatorDDecalMin;
   granulatorDecalMax=granulatorDDecalMax;
   granulatorDecalScale=granulatorDDecalScale;
   granulatorDecalMode=granulatorDDecalMode;
   granulatorFbkB=granulatorDFbkB;
   granulatorFbkMin=granulatorDFbkMin;
   granulatorFbkMax=granulatorDFbkMax;
   granulatorFbkScale=granulatorDFbkScale;
   granulatorFbkMode=granulatorDFbkMode;
   granulatorPopuB=granulatorDPopuB;
   granulatorPopuMin=granulatorDPopuMin;
   granulatorPopuMax=granulatorDPopuMax;
   granulatorPopuScale=granulatorDPopuScale;
   granulatorPopuMode=granulatorDPopuMode;
   granulatorSpeedB=granulatorDSpeedB;
   granulatorSpeedMin=granulatorDSpeedMin;
   granulatorSpeedMax=granulatorDSpeedMax;
   granulatorSpeedScale=granulatorDSpeedScale;
   granulatorSpeedMode=granulatorDSpeedMode;
   granulatorSizeB=granulatorDSizeB;
   granulatorSizeMin=granulatorDSizeMin;
   granulatorSizeMax=granulatorDSizeMax;
   granulatorSizeScale=granulatorDSizeScale;
   granulatorSizeMode=granulatorDSizeMode;
}
void Pave::defautFilters(){
	filtersHpfB=filtersDHpfB;
   filtersHpfMin=filtersDHpfMin;
   filtersHpfMax=filtersDHpfMax;
   filtersHpfScale=filtersDHpfScale;
   filtersHpfMode=filtersDHpfMode;
   filtersLpfB=filtersDLpfB;
   filtersLpfMin=filtersDLpfMin;
   filtersLpfMax=filtersDLpfMax;
   filtersLpfScale=filtersDLpfScale;
   filtersLpfMode=filtersDLpfMode;
}
void Pave::defautMoog(){
	moogFreqB=moogDFreqB;
   moogFreqMin=moogDFreqMin;
   moogFreqMax=moogDFreqMax;
   moogFreqScale=moogDFreqScale;
   moogFreqMode=moogDFreqMode;
   moogResonanceB=moogDResonanceB;
   moogResonanceMin=moogDResonanceMin;
   moogResonanceMax=moogDResonanceMax;
   moogResonanceScale=moogDResonanceScale;
   moogResonanceMode=moogDResonanceMode;
   moogLevelB=moogLevelB;
   moogLevelMin=moogDLevelMin;
   moogLevelMax=moogDLevelMax;
   moogLevelScale=moogDLevelScale;
   moogLevelMode=moogDLevelMode;
}
void Pave::defautParametricEq(){
	parametricEqLowBoostB=parametricEqDLowBoostB;
   parametricEqLowBoostMin=parametricEqDLowBoostMin;
   parametricEqLowBoostMax=parametricEqDLowBoostMax;
   parametricEqLowBoostScale=parametricEqDLowBoostScale;
   parametricEqLowBoostMode=parametricEqDLowBoostMode;
   parametricEqLowFreqB=parametricEqDLowFreqB;
   parametricEqLowFreqMin=parametricEqDLowFreqMin;
   parametricEqLowFreqMax=parametricEqDLowFreqMax;
   parametricEqLowFreqScale=parametricEqDLowFreqScale;
   parametricEqLowFreqMode=parametricEqDLowFreqMode;
   parametricEqPeakBoostB=parametricEqDPeakBoostB;
   parametricEqPeakBoostMin=parametricEqDPeakBoostMin;
   parametricEqPeakBoostMax=parametricEqDPeakBoostMax;
   parametricEqPeakBoostScale=parametricEqDPeakBoostScale;
   parametricEqPeakBoostMode=parametricEqDPeakBoostMode;
   parametricEqPeakFreqB=parametricEqDPeakFreqB;
   parametricEqPeakFreqMin=parametricEqDPeakFreqMin;
   parametricEqPeakFreqMax=parametricEqDPeakFreqMax;
   parametricEqPeakFreqScale=parametricEqDPeakFreqScale;
   parametricEqPeakFreqMode=parametricEqDPeakFreqMode;
   parametricEqPeakQB=parametricEqDPeakQB;
   parametricEqPeakQMin=parametricEqDPeakQMin;
   parametricEqPeakQMax=parametricEqDPeakQMax;
   parametricEqPeakQScale=parametricEqDPeakQScale;
   parametricEqPeakQMode=parametricEqDPeakQMode;
   parametricEqHighBoostB=parametricEqDHighBoostB;
   parametricEqHighBoostMin=parametricEqDHighBoostMin;
   parametricEqHighBoostMax=parametricEqDHighBoostMax;
   parametricEqHighBoostScale=parametricEqDHighBoostScale;
   parametricEqHighBoostMode=parametricEqDHighBoostMode;
   parametricEqHighFreqB=parametricEqDHighFreqB;
   parametricEqHighFreqMin=parametricEqDHighFreqMin;
   parametricEqHighFreqMax=parametricEqDHighFreqMax;
   parametricEqHighFreqScale=parametricEqDHighFreqScale;
   parametricEqHighFreqMode=parametricEqDHighFreqMode;
}
void Pave::defautPhaser(){
	phaserSpeedB=phaserDSpeedB;
   phaserSpeedMin=phaserDSpeedMin;
   phaserSpeedMax=phaserDSpeedMax;
   phaserSpeedScale=phaserDSpeedScale;
   phaserSpeedMode=phaserDSpeedMode;
   phaserFbkB=phaserDFbkB;
   phaserFbkMin=phaserDFbkMin;
   phaserFbkMax=phaserDFbkMax;
   phaserFbkScale=phaserDFbkScale;
   phaserFbkMode=phaserDFbkMode;
   phaserLevelB=phaserDLevelB;
   phaserLevelMin=phaserDLevelMin;
   phaserLevelMax=phaserDLevelMax;
   phaserLevelScale=phaserDLevelScale;
   phaserLevelMode=phaserDLevelMode;
   phaserDepthB=phaserDDepthB;
   phaserDepthMin=phaserDDepthMin;
   phaserDepthMax=phaserDDepthMax;
   phaserDepthScale=phaserDDepthScale;
   phaserDepthMode=phaserDDepthMode;
}
void Pave::defautRingModulator(){
	ringModulatorDepthB=ringModulatorDDepthB;
   ringModulatorDepthMin=ringModulatorDDepthMin;
   ringModulatorDepthMax=ringModulatorDDepthMax;
   ringModulatorDepthScale=ringModulatorDDepthScale;
   ringModulatorDepthMode=ringModulatorDDepthMode;
   ringModulatorFrequencyB=ringModulatorDFrequencyB;
   ringModulatorFrequencyMin=ringModulatorDFrequencyMin;
   ringModulatorFrequencyMax=ringModulatorDFrequencyMax;
   ringModulatorFrequencyScale=ringModulatorDFrequencyScale;
   ringModulatorFrequencyMode=ringModulatorDFrequencyMode;
}
void Pave::defautSpeed(){
	speedSpeedB=speedDSpeedB;
   speedSpeedMin=speedDSpeedMin;
   speedSpeedMax=speedDSpeedMax;
   speedSpeedScale=speedDSpeedScale;
   speedSpeedMode=speedDSpeedMode;
}
