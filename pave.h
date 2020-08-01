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
#ifndef DEF_PAVE
#define DEF_PAVE

#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdlib.h>
#include <string>

#include "configuration.h"

class Pave{

 public :
  
  Pave();
 
  ~Pave();
   
  void setPath(std::string p);
  void setPathD(std::string p);
  void setFile(std::string f);
  void setFileD(std::string p);
  void setPaveDim(float d);
  void setFlagMulticanaux(bool f);
  void setFlagMulticanauxD(bool f);
  void setMixgain(bool m);
  void setDimMixer(float r);
  void setDimMixerD(float r);
  void setX(int x);
  void setY(int y);
  void setGainMin(float g);
  void setGainMinD(float g);
  void setGainMax(float g);
  void setGainMaxD(float g);
  void setGain(float g);
  void setFlagDaw(int d);
  void setFlagDawD(int d);
  void setDgGain(bool dt);
  void setFx(bool f);
  void setFxD(bool f);
  void setMode(int m);
  void setCurseurT(int ct);
  void setCurseurTD(int ct);
  void setCurseurX(float curx);
  void setCurseurY(float curY);
  void setCurseurEtat(bool cure);
  void setTrack(int tk);
  void setTrackD(int tk);
  void setDistanceMax(float dt);
  void setPoint(int id,sf::Vector2f dc);
  
  void defautPave();
  void defPave();
  
  void setExplose(int ex);  
  
  void setNbCanaux(int nb);
  void setDuree(float d);
  
	
  std::string getPath();
  std::string getFile(); 
  int getTrack();
  int getFlagDaw();  
  float getCx();
  float getCy();
  int getDim();
  bool getFlagMulticanaux();
  bool getFlagMulticanauxD();
  float getDimMixer();
  bool getMixgain();
  float getGainMin();
  float getGainMax();
  float getGain();
  float getSpeed();
  float getMode();
  bool getDgGain();
  bool getFx();
  sf::Vector2f getPoint(int id);
  float getDistanceMax();
  
  int getCurseurT();
  float getCurseurX();
  float getCurseurY();
  bool getCurseurEtat();
  sf::Sprite getCurseur();
  int getNbCanaux();
  float getDuree();
  int getExplose(); 
  
  int getFlagDawD();
  float getDimMixerD();
  float getGainMinD();
  float getGainMaxD();
 
  float gain;
  /*
  bool compresRatioB=0;
  float compresIntRatioMin=1.0;
  float compresIntRatioMax=20.0;
  float compresIntRatioScale=1.0;
  bool compresRatioMode=0;
  bool compresThresB=0;
  float compresIntThresMin=-100.0;
  float compresIntThresMax=10.0;
  float compresIntThresScale=1.0;
  bool compresThresMode=0;
  bool compresTimeB=0;
  float compresIntTimeMin=1.0;
  float compresIntTimeMax=1000.0;
  float compresIntTimeScale=1.0;
  bool compresTimeMode=0;
  bool compresReleaseB=0;
  float compresIntReleaseMin=1.0;
  float compresIntReleaseMax=1000.0;
  float compresIntReleaseScale=1.0;
  bool compresReleaseMode=0;
  bool compresGainB=0;
  float compresIntGainMin=-96.0;
  float compresIntGainMax=96.0;
  float compresIntGainScale=1.0;
  bool compresGainMode=0;
  
  bool compresDRatioB=0;
  float compresDIntRatioMin=1.0;
  float compresDIntRatioMax=20.0;
  float compresDIntRatioScale=1.0;
  bool compresDRatioMode=0;
  bool compresDThresB=0;
  float compresDIntThresMin=-100.0;
  float compresDIntThresMax=10.0;
  float compresDIntThresScale=1.0;
  bool compresDThresMode=0;
  bool compresDTimeB=0;
  float compresDIntTimeMin=1.0;
  float compresDIntTimeMax=1000.0;
  float compresDIntTimeScale=1.0;
  bool compresDTimeMode=0;
  bool compresDReleaseB=0;
  float compresDIntReleaseMin=1.0;
  float compresDIntReleaseMax=1000.0;
  float compresDIntReleaseScale=1.0;
  bool compresDReleaseMode=0;
  bool compresDGainB=0;
  float compresDIntGainMin=-96.0;
  float compresDIntGainMax=96.0;
  float compresDIntGainScale=1.0;
  bool compresDGainMode=0;
  
  
  bool  delayDelB=0;
  float delayIntDelayMin=0;
  float delayIntDelayMax=5000;
  float delayIntDelayScale=1;
  bool  delayDelayMode=0;
  bool  delayFbkB=0;
  float delayIntFbkMin=0;
  float delayIntFbkMax=100;
  float delayIntFbkScale=1;
  bool  delayFbkMode=0;
  bool  delayInterpolB=0;
  float delayIntInterpolMin=10;
  float delayIntInterpolMax=100;
  float delayIntInterpolScale=1;
  bool  delayInterpolMode=0;
  
  bool  delayDDelB=0;
  float delayDDelMin=0;
  float delayDDelMax=5000;
  float delayDDelScale=1;
  bool  delayDDelMode=0;
  bool  delayDFbkB=0;
  float delayDFbkMin=0;
  float delayDFbkMax=100;
  float delayDFbkScale=1;
  bool  delayDFbkMode=0;
  bool  delayDInterpolB=0;
  float delayDInterpolMin=10;
  float delayDInterpolMax=100;
  float delayDInterpolScale=1;
  bool  delayDInterpolMode=0;
  
  bool  distortionDriveB=0;
  float distortionIntDriveMin=0;
  float distortionIntDriveMax=1;
  float distortionIntDriveScale=1;
  bool  distortionDriveMode=0;

  float distortionOffsetB=0;
  float distortionIntOffsetMin=0;
  float distortionIntOffsetMax=1;
  float distortionIntOffsetScale=1;
  bool  distortionOffsetMode=0;
  
  bool  distortionDDriveB=0;
  float distortionDDriveMin=0;
  float distortionDDriveMax=1;
  float distortionDDriveScale=1;
  bool  distortionDDriveMode=0;
  bool  distortionDOffsetB=0;
  float distortionDOffsetMin=0;
  float distortionDOffsetMax=1;
  float distortionDOffsetScale=1;
  bool  distortionDOffsetMode=0;

  bool  granulatorDecalB=0;
  float granulatorDecalMin=0;
  float granulatorDecalMax=1;
  float granulatorDecalScale=1;
  bool  granulatorDecalMode=0; 
  bool  granulatorFbkB=0;
  float granulatorFbkMin=0;
  float granulatorFbkMax=2;
  float granulatorFbkScale=1;
  bool  granulatorFbkMode=0; 
  bool  granulatorPopuB=0;
  float granulatorPopuMin=0;
  float granulatorPopuMax=1;
  float granulatorPopuScale=1;
  bool  granulatorPopuMode=0;  
  bool  granulatorSpeedB=0;
  float granulatorSpeedMin=0.125;
  float granulatorSpeedMax=4;
  float granulatorSpeedScale=1;
  bool  granulatorSpeedMode=0;
  bool  granulatorSizeB=0;
  float granulatorSizeMin=4;
  float granulatorSizeMax=200;
  float granulatorSizeScale=1;
  bool  granulatorSizeMode=0;
  
  bool  granulatorDDecalB=0;
  float granulatorDDecalMin=0;// 0.001
  float granulatorDDecalMax=1;
  float granulatorDDecalScale=1;
  bool  granulatorDDecalMode=0; 
  bool  granulatorDFbkB=0;  //0.001
  float granulatorDFbkMin=0;
  float granulatorDFbkMax=2;
  float granulatorDFbkScale=1;
  bool  granulatorDFbkMode=0; 
  bool  granulatorDPopuB=0; //0.001
  float granulatorDPopuMin=0;
  float granulatorDPopuMax=1;
  float granulatorDPopuScale=1;
  bool  granulatorDPopuMode=0;  
  bool  granulatorDSpeedB=0;
  float granulatorDSpeedMin=0.125;
  float granulatorDSpeedMax=4;
  float granulatorDSpeedScale=1;
  bool  granulatorDSpeedMode=0;
  bool  granulatorDSizeB=0;
  float granulatorDSizeMin=4;
  float granulatorDSizeMax=200;//0.001
  float granulatorDSizeScale=1;
  bool  granulatorDSizeMode=0;
  
  bool  filtersHpfB=0;
  float filtersHpfMin=20;
  float filtersHpfMax=20000;
  float filtersHpfScale=1;
  bool  filtersHpfMode=0; 
  bool  filtersLpfB=0;
  float filtersLpfMin=20;
  float filtersLpfMax=20000;
  float filtersLpfScale=1;
  bool  filtersLpfMode=0; 
  
  bool  filtersDHpfB=0;
  float filtersDHpfMin=20;
  float filtersDHpfMax=20000;
  float filtersDHpfScale=1;
  bool  filtersDHpfMode=0; 
  bool  filtersDLpfB=0; 
  float filtersDLpfMin=20;
  float filtersDLpfMax=20000;
  float filtersDLpfScale=1;
  bool  filtersDLpfMode=0;
  
  bool  flangerSpeedB=0;
  float flangerSpeedMin=0;
  float flangerSpeedMax=10;
  float flangerSpeedScale=1;
  bool  flangerSpeedMode=0; 
  bool  flangerDepthB=0;
  float flangerDepthMin=0;
  float flangerDepthMax=1;
  float flangerDepthScale=1;
  bool  flangerDepthMode=0; 
  bool  flangerFbkB=0;
  float flangerFbkMin=-0.999;
  float flangerFbkMax=0.999;
  float flangerFbkScale=1;
  bool  flangerFbkMode=0;  
  bool  flangerDelayB=0;
  float flangerDelayMin=0;
  float flangerDelayMax=20;
  float flangerDelayScale=1;
  bool  flangerDelayMode=0;
  bool  flangerOffsetB=0;
  float flangerOffsetMin=0;
  float flangerOffsetMax=20;
  float flangerOffsetScale=1;
  bool  flangerOffsetMode=0;
  bool  flangerLevelB=0;
  float flangerLevelMin=-60;
  float flangerLevelMax=10;
  float flangerLevelScale=1;
  bool  flangerLevelMode=0;
  
  bool  flangerDSpeedB=0;
  float flangerDSpeedMin=0;
  float flangerDSpeedMax=10;
  float flangerDSpeedScale=1;
  bool  flangerDSpeedMode=0; 
  bool  flangerDDepthB=0;
  float flangerDDepthMin=0;
  float flangerDDepthMax=1;
  float flangerDDepthScale=1;
  bool  flangerDDepthMode=0; 
  bool  flangerDFbkB=0;
  float flangerDFbkMin=-0.999;
  float flangerDFbkMax=0.999;
  float flangerDFbkScale=1;
  bool  flangerDFbkMode=0;  
  bool  flangerDDelayB=0;
  float flangerDDelayMin=0;
  float flangerDDelayMax=20;
  float flangerDDelayScale=1;
  bool  flangerDDelayMode=0;
  bool  flangerDOffsetB=0;
  float flangerDOffsetMin=0;
  float flangerDOffsetMax=20;
  float flangerDOffsetScale=1;
  bool  flangerDOffsetMode=0;
  bool  flangerDLevelB=0;
  float flangerDLevelMin=-60;
  float flangerDLevelMax=10;
  float flangerDLevelScale=1;
  bool  flangerDLevelMode=0;
  
  bool  freeverbDampB=0;
  float freeverbDampMin=0;
  float freeverbDampMax=1;
  float freeverbDampScale=1;
  bool  freeverbDampMode=0; 
  bool  freeverbRoomB=0;
  float freeverbRoomMin=0;
  float freeverbRoomMax=1;
  float freeverbRoomScale=1;
  bool  freeverbRoomMode=0; 
  bool  freeverbStereoB=0;
  float freeverbStereoMin=0;
  float freeverbStereoMax=1;
  float freeverbStereoScale=1;
  bool  freeverbStereoMode=0;
  bool  freeverbWetB=0;
  float freeverbWetMin=0;
  float freeverbWetMax=1;
  float freeverbWetScale=1;
  bool  freeverbWetMode=0;
  
  bool  freeverbDDampB=0;
  float freeverbDDampMin=0;
  float freeverbDDampMax=1;
  float freeverbDDampScale=1;
  bool  freeverbDDampMode=0; 
  bool  freeverbDRoomB=0;
  float freeverbDRoomMin=0;
  float freeverbDRoomMax=1;
  float freeverbDRoomScale=1;
  bool  freeverbDRoomMode=0; 
  bool  freeverbDStereoB=0;
  float freeverbDStereoMin=0;
  float freeverbDStereoMax=1;
  float freeverbDStereoScale=1;
  bool  freeverbDStereoMode=0;
  bool  freeverbDWetB=0;
  float freeverbDWetMin=0;
  float freeverbDWetMax=1;
  float freeverbDWetScale=1;
  bool  freeverbDWetMode=0;
  
  bool  moogFreqB=0;
  float moogFreqMin=1;
  float moogFreqMax=88;
  float moogFreqScale=1;
  bool  moogFreqMode=0;
  bool  moogResonanceB=0;
  float moogResonanceMin=0;
  float moogResonanceMax=1;
  float moogResonanceScale=1;
  bool  moogResonanceMode=0;
  bool  moogLevelB=0;
  float moogLevelMin=-60;
  float moogLevelMax=20;
  float moogLevelScale=1;
  bool  moogLevelMode=0;
  
  bool  moogDFreqB=0;
  float moogDFreqMin=1;
  float moogDFreqMax=88;
  float moogDFreqScale=1;
  bool  moogDFreqMode=0;
  bool  moogDResonanceB=0;
  float moogDResonanceMin=0;
  float moogDResonanceMax=1;
  float moogDResonanceScale=1;
  bool  moogDResonanceMode=0;
  bool  moogDLevelB=0;
  float moogDLevelMin=-60;
  float moogDLevelMax=20;
  float moogDLevelScale=1;
  bool  moogDLevelMode=0;
  
  bool  parametricEqLowBoostB=0;
  float parametricEqLowBoostMin=-40;
  float parametricEqLowBoostMax=40;
  float parametricEqLowBoostScale=1;
  bool  parametricEqLowBoostMode=0; 
  bool  parametricEqLowFreqB=0;
  float parametricEqLowFreqMin=1;
  float parametricEqLowFreqMax=5000;
  float parametricEqLowFreqScale=1;
  bool  parametricEqLowFreqMode=0; 
  bool  parametricEqPeakBoostB=0;
  float parametricEqPeakBoostMin=-40;
  float parametricEqPeakBoostMax=40;
  float parametricEqPeakBoostScale=1;
  bool  parametricEqPeakBoostMode=0;  
  bool  parametricEqPeakFreqB=0;
  float parametricEqPeakFreqMin=1;
  float parametricEqPeakFreqMax=100;
  float parametricEqPeakFreqScale=1;
  bool  parametricEqPeakFreqMode=0;
  bool  parametricEqPeakQB=0;
  float parametricEqPeakQMin=1;
  float parametricEqPeakQMax=1000;
  float parametricEqPeakQScale=1;
  bool  parametricEqPeakQMode=0;
  bool  parametricEqHighBoostB=0;
  float parametricEqHighBoostMin=-40;
  float parametricEqHighBoostMax=40;
  float parametricEqHighBoostScale=1;
  bool  parametricEqHighBoostMode=0; 
  bool  parametricEqHighFreqB=0;
  float parametricEqHighFreqMin=20;
  float parametricEqHighFreqMax=10000;
  float parametricEqHighFreqScale=1;
  bool  parametricEqHighFreqMode=0; 
  
  bool  parametricEqDLowBoostB=0;
  float parametricEqDLowBoostMin=-40;
  float parametricEqDLowBoostMax=40;
  float parametricEqDLowBoostScale=1;
  bool  parametricEqDLowBoostMode=0; 
  bool  parametricEqDLowFreqB=0;
  float parametricEqDLowFreqMin=1;
  float parametricEqDLowFreqMax=5000;
  float parametricEqDLowFreqScale=1;
  bool  parametricEqDLowFreqMode=0; 
  bool  parametricEqDPeakBoostB=0;
  float parametricEqDPeakBoostMin=-40;
  float parametricEqDPeakBoostMax=40;
  float parametricEqDPeakBoostScale=1;
  bool  parametricEqDPeakBoostMode=0;  
  bool  parametricEqDPeakFreqB=0;
  float parametricEqDPeakFreqMin=1;
  float parametricEqDPeakFreqMax=100;
  float parametricEqDPeakFreqScale=1;
  bool  parametricEqDPeakFreqMode=0;
  bool  parametricEqDPeakQB=0;
  float parametricEqDPeakQMin=1;
  float parametricEqDPeakQMax=1000;
  float parametricEqDPeakQScale=1;
  bool  parametricEqDPeakQMode=0;
  bool  parametricEqDHighBoostB=0;
  float parametricEqDHighBoostMin=-40;
  float parametricEqDHighBoostMax=40;
  float parametricEqDHighBoostScale=1;
  bool  parametricEqDHighBoostMode=0; 
  bool  parametricEqDHighFreqB=0;
  float parametricEqDHighFreqMin=20;
  float parametricEqDHighFreqMax=10000;
  float parametricEqDHighFreqScale=1;
  bool  parametricEqDHighFreqMode=0;   
  
  bool  phaserSpeedB=0;
  float phaserSpeedMin=0;
  float phaserSpeedMax=10;
  float phaserSpeedScale=1;
  bool  phaserSpeedMode=0;
  bool  phaserFbkB=0;
  float phaserFbkMin=-0.999;
  float phaserFbkMax=0.999;
  float phaserFbkScale=1;
  bool  phaserFbkMode=0; 
  bool  phaserLevelB=0;
  float phaserLevelMin=-60;
  float phaserLevelMax=10;
  float phaserLevelScale=1;
  bool  phaserLevelMode=0;  
  bool  phaserDepthB=0;
  float phaserDepthMin=0;
  float phaserDepthMax=1;
  float phaserDepthScale=1;
  bool  phaserDepthMode=0; 
  
  bool  phaserDSpeedB=0;
  float phaserDSpeedMin=0;
  float phaserDSpeedMax=10;
  float phaserDSpeedScale=1;
  bool  phaserDSpeedMode=0;
  bool  phaserDFbkB=0;
  float phaserDFbkMin=-0.999;
  float phaserDFbkMax=0.999;
  float phaserDFbkScale=1;
  bool  phaserDFbkMode=0; 
  bool  phaserDLevelB=0;
  float phaserDLevelMin=-60;
  float phaserDLevelMax=10;
  float phaserDLevelScale=1;
  bool  phaserDLevelMode=0;  
  bool  phaserDDepthB=0;
  float phaserDDepthMin=0;
  float phaserDDepthMax=1;
  float phaserDDepthScale=1;
  bool  phaserDDepthMode=0; 
  
  
  bool  ringModulatorDepthB=0;
  float ringModulatorDepthMin=0;
  float ringModulatorDepthMax=1;
  float ringModulatorDepthScale=1;
  bool  ringModulatorDepthMode=0; 
  bool  ringModulatorFrequencyB=0;
  float ringModulatorFrequencyMin=0.1;
  float ringModulatorFrequencyMax=1000;
  float ringModulatorFrequencyScale=1;
  bool  ringModulatorFrequencyMode=0; 
  
  bool  ringModulatorDDepthB=0;
  float ringModulatorDDepthMin=0;
  float ringModulatorDDepthMax=1;
  float ringModulatorDDepthScale=1;
  bool  ringModulatorDDepthMode=0; 
  bool  ringModulatorDFrequencyB=0; 
  float ringModulatorDFrequencyMin=0.1;
  float ringModulatorDFrequencyMax=1000;
  float ringModulatorDFrequencyScale=1;
  bool  ringModulatorDFrequencyMode=0; 
  
  bool  speedSpeedB=0;
  float speedSpeedMin=0.1;
  float speedSpeedMax=3;
  float speedSpeedScale=1;
  bool  speedSpeedMode=0; 
  
  bool  speedDSpeedB=0;
  float speedDSpeedMin=0.1;
  float speedDSpeedMax=3;
  float speedDSpeedScale=1;
  bool  speedDSpeedMode=0;
  */
  
  int rtfx=0;  
  int nbfx;
  int idfx[12]={0};
  std::string idNameFx[12]={""};
  struct pluginParam{
		bool etat;
		float min;
		float max;
		float scale;
		bool rev;
		bool mod;
	};
  std::vector<pluginParam> tabUsrPluginParam[12];
  int modeFx[12];
  bool fxcanal;
  bool fxSpectrum;
  
 private :
 
  
  std::string fileSound;
  std::string path;
  int dim;
  int canaux;
  float duree;
  int track;
  float cx;
  float cy;
  int flagDaw;
  bool flagMulticanaux;
  bool flagMulticanauxD;

  float dimMixer;
  bool mixgain;
  float gainMin;
  float gainMax;
  float speed;
  int readMode;
  bool dtgain;
  bool fx;
  sf::Vector2f point[17];
  float distanceMax;
  int explose=0;
  
  std::string fileSoundD="";
  std::string pathD="";
  int dimD;
  int canauxD;
  float dureeD;
  int trackD;
  float cxD;
  float cyD;
  int flagDawD;

  float dimMixerD;
  float gainMinD;
  float gainMaxD;
  float speedD;
  bool fxD;
  int curseurTypeD;
  
  sf::Sprite curseur;
  int curseurType=0;
  float curseurX;
  float curseurY;
  bool curseurE;
  

};
#endif
