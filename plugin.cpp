#include <SFML/Graphics.hpp>
#include <sstream>
#include <iostream>
#include <fstream>
#include <dirent.h>
#include <stdlib.h>
#include <iomanip>
#include <ctgmath>
#include <string>
#include <cstring>
#include <boost/filesystem.hpp>
#include <vector>
#include <map>

#include "plugin.h"

using namespace std;

Plugin::Plugin(){
  winPluginWidth=400;
  winPluginHeight=314;
  pluginBarHeight=36;
  editMode=0;
  winPluginCurseur.setSize(sf::Vector2f(2,12));
  winPluginCurseur.setFillColor(sf::Color(0,0,0,255));
  flagPluginCurseur=0;
  idparam=0;
  numid=0;
  
  systemPlugin();
  
  nameFx.setFont(font);
  nameFx.setCharacterSize(13);
  nameFx.setFillColor(sf::Color(0, 0, 0));
  fonctionFx.setFont(font);
  fonctionFx.setCharacterSize(13);
  fonctionFx.setFillColor(sf::Color(0, 0, 0));
  fonctionFx.setPosition(8,18);
  numparam.setFont(font);
  numparam.setCharacterSize(13);
  numparam.setFillColor(sf::Color(0, 0, 0));
  numparam.setPosition(8,18);
  refid.setFont(font);
  refid.setCharacterSize(16);
  refid.setFillColor(sf::Color(0, 0, 0));
  refid.setPosition(38,196);
  id.setFont(font);
  id.setCharacterSize(13);
  id.setFillColor(sf::Color(0, 0, 0));
  id.setPosition(8,18);
  param.setFont(font);
  param.setCharacterSize(13);
  param.setFillColor(sf::Color(0, 0, 0));
  param.setPosition(8,18);
  min.setFont(font);
  min.setCharacterSize(13);
  min.setFillColor(sf::Color(0, 0, 0));
  min.setPosition(8,18);
  max.setFont(font);
  max.setCharacterSize(13);
  max.setFillColor(sf::Color(0, 0, 0));
  max.setPosition(8,18);
  adresse.setFont(font);
  adresse.setCharacterSize(13);
  adresse.setFillColor(sf::Color(0, 0, 0));
  adresse.setPosition(8,18);
  
  winSelectCurseur.setSize(sf::Vector2f(110,24));
  winSelectCurseur.setFillColor(sf::Color(100,100,100));
  winSelectCurseur.setPosition(6,8);
  shapeEditSlider.setSize(sf::Vector2f(18, 350));
  shapeEditSlider.setFillColor(sf::Color(190,190,190));
  shapeEditSlider.setOutlineThickness(1.f);
  shapeEditSlider.setOutlineColor(sf::Color(255,255,255));
  shapeEditSlider.setPosition(sf::Vector2f(190,10));
  shapeEditMSlider.setSize(sf::Vector2f(16, 30));
  shapeEditMSlider.setFillColor(sf::Color(150,150,150));
  shapeEditMSlider.setOutlineThickness(1.f);
  shapeEditMSlider.setOutlineColor(sf::Color(200,200,200));
  shapeEditMSlider.setPosition(sf::Vector2f(191,11));
  listEditIndex=0;
}

Plugin::~Plugin(){
}

void Plugin::setPlugin(string Theme, string gui, string uConfig, string edit, string nav){
   stringstream adr;
	adr << std::fixed <<gui;
   pluginGui=adr.str();
   adr.clear();
   adr.str("");
   userConfig=uConfig;
   adr << std::fixed << pluginGui<<"/"<<"Arial.ttf";
   font.loadFromFile(adr.str());
   adr.clear();
   adr.str("");
   navigateur=nav;
  
   adr << std::fixed << pluginGui<<"/fondPlugin.png";
   selectF1.loadFromFile(adr.str());
	adr.clear();
   adr.str("");
   adr << std::fixed << pluginGui<< "/bNoSelect.png";
   bNoSelect.loadFromFile(adr.str());
   adr.clear();
   adr.str("");
   adr << std::fixed << pluginGui<< "/bselect.png";
   bselect.loadFromFile(adr.str());
   adr.clear();
   adr.str("");
   adr << std::fixed << pluginGui<< "/faustide.png";
   idet.loadFromFile(adr.str());
   adr.clear();
   adr.str("");
   daw.setTexture(bNoSelect);
   daw.setPosition(68,20);
   fondPlugin.setTexture(selectF1);
   fondPlugin.setPosition(sf::Vector2f(0, 0));
   faustIde.setTexture(idet);
   faustIde.setPosition(sf::Vector2f(326, 94));
   
   editeur=edit;
   ifstream fichier(Theme, ios::in); 
   string contenu;
   float s1;
   int s2;
   string pf[2];
   int i=0;
   if(fichier){ 
     while(getline(fichier, contenu)){
       char * cstr = new char [contenu.length()+1];
       std::strcpy (cstr, contenu.c_str());
       char * p = std::strtok (cstr,"=");
       i=0;
       while (p!=0){
 	     pf[i]=p;
 	     i++;
	     p = std::strtok(NULL," ");
       }
       if(pf[0]=="pluginTxtSize"){
         pluginTxtSize=stoi(pf[1]);
       }
       if(pf[0]=="pluginTxtFillColor"){
         pluginTxtFillColor=sf::Color(std::stoul(pf[1],nullptr,16));
       }
       if(pf[0]=="pluginBkgColor"){
         pluginBkgColor=sf::Color(std::stoul(pf[1],nullptr,16));
       }
     }		
  }else{  // sinon
       cerr << "Erreur à l'ouverture Theme!" << endl;
  }
}

bool Plugin::drawPlugin(bool edit,int ext, string titreWPlugin){
  editMode=edit;
  titreWinPlugin=titreWPlugin;
  rtf=0;
  if(editMode==0){
 	 tabnparam.clear();
  }
  externe=ext;
  if(externe==2){
  	daw.setTexture(bselect);
  }else{
  	daw.setTexture(bNoSelect);
  }
  daw.setPosition(68,20);

  
  if(editMode==0){
	  nameFx.setString("");
	  fonctionFx.setString("");
	  id.setString("");
	  param.setString("");
	  min.setString("");
	  max.setString("");
	  adresse.setString("");
  }

  winPlugin.create(sf::VideoMode(winPluginWidth, winPluginHeight), titreWinPlugin);
  sf::RectangleShape menuBar(sf::Vector2f( winPluginWidth,pluginBarHeight));
  
  
  while (winPlugin.isOpen()) {                             // Événements
	sf::Event event;
	while (winPlugin.pollEvent(event)){                // Gestion des évènements de la fenêtre principale
		switch (event.type){
			case sf::Event::Closed:            // Fermeture de la fenêtre
				onClose();
				break;
			case sf::Event::MouseButtonPressed:
				onClick(event);
				break;
			case sf::Event::MouseMoved:
				onMouseMove(event);
				break;
        	case sf::Event::TextEntered:
     			newPluginText(event);
				break;			  					
			default:                            // on ne traite pas les autres types d'évènements
				break;
		}            
        
	}
        // Clear screen
	winPlugin.setActive(true);
	winPlugin.pushGLStates();
	winPlugin.clear(pluginBkgColor);
	winPlugin.draw(fondPlugin);
	winPlugin.draw(daw);
   winPlugin.draw(nameFx);
   winPlugin.draw(fonctionFx);
   refid.setString(to_string(numid));
   winPlugin.draw(refid);
   winPlugin.draw(id);
   winPlugin.draw(param);
   winPlugin.draw(min);
   winPlugin.draw(max);
   winPlugin.draw(adresse);
   winPlugin.draw(faustIde);
 
   if(flagPluginCurseur==1){
		if(clockPluginCurseur.getElapsedTime()>sf::seconds(0.8f)){
			winPlugin.draw(winPluginCurseur);
			if(clockPluginCurseur.getElapsedTime()>sf::seconds(1.6f)){
				clockPluginCurseur.restart();
			}
		}
	}
			
	winPlugin.display();
	winPlugin.popGLStates();
	winPlugin.setActive(false);
  }
  return rtf;
}
void Plugin::onClose(){
  rtf=0;
  winPlugin.close();
}
void Plugin::systemPlugin(){
	plugin defPlugin;
  defPlugin={0,"","","",0,{}};
  tabPlugin.push_back(defPlugin);
  defPlugin={0,"Compression","compressor","",5,{}};
  defPlugin.param={{0,"Ratio",1.0,20.0,"COMPRESSOR/0x00/Compression_Control/Ratio"},{1,"Threshold",-100,10.0,"COMPRESSOR/0x00/Compression_Control/Threshold"},{2,"Time",1.0,1000,"COMPRESSOR/0x00/Compression_Response/Attack"},{3,"Release",1.0,1000,"COMPRESSOR/0x00/Compression_Response/Release"},{4,"Gain",-96,96,"COMPRESSOR/Makeup_Gain"}};
  tabPlugin.push_back(defPlugin);
  defPlugin={0,"Delay","delay","",3,{}};
  defPlugin.param={{0,"Delay",0.0,5000,"DELAY/0x00/delay"},{1,"Feedback",0,100,"DELAY/0x00/feedback"},{2,"Interpolation",10,100,"DELAY/0x00/interpolation"}};
  tabPlugin.push_back(defPlugin);
  defPlugin={0,"Distortion","dm.cubicnl_demo","",2,{}};
  defPlugin.param={{0,"Drive",0.0,1.0,"CUBIC_NONLINEARITY_cubicnl/Drive"},{1,"Offset",0.0,1.0,"CUBIC_NONLINEARITY_cubicnl/Offset"}};
  tabPlugin.push_back(defPlugin);
  defPlugin={0,"Flanger","flangerMono","",6,{}};
  defPlugin.param={{0,"Speed",0.0,10.0,"FLANGER/0x00/Speed"},{1,"Depth",0,1.0,"FLANGER/0x00/Depth"},{2,"Feedback",-1.0,1.0,"FLANGER/0x00/Feedback"},{3,"Delay",0.0,20.0,"FLANGER/Delay_Controls/Flange_Delay"},{4,"Offset",0.0,20.0,"FLANGER/Delay_Controls/Delay_Offset"},{5,"Level",-60,10,"FLANGER/0x00/Flanger_Output_Level"}};
  tabPlugin.push_back(defPlugin);
  defPlugin={0,"Freeverb","freeverb","",4,{}};
  defPlugin.param={{0,"Damp",0.0,1.0,"Freeverb/0x00/Damp"},{1,"Room",0.0,1.0,"Freeverb/0x00/RoomSize"},{2,"Stereo",0.0,1.0,"Freeverb/0x00/Stereo_Spread"},{3,"Wet",0.0,1.0,"Freeverb/Wet"}};
  tabPlugin.push_back(defPlugin);
  defPlugin={0,"Granulator","granulator","",5,{}};
  defPlugin.param={{0,"Decal",1.0,1.0,"GRANULATOR/0x00/decal"},{1,"Feedback",0.0,2.0,"GRANULATOR/0x00/feedback"},{2,"Population",0.0,1.0,"GRANULATOR/0x00/population"},{3,"Speed",1.0,4.0,"GRANULATOR/0x00/speed"},{4,"Size",4.0,200.0,"GRANULATOR/0x00/taille"}};
  tabPlugin.push_back(defPlugin);
  defPlugin={0,"HPF/LPF","filters","",2,{}};
  defPlugin.param={{0,"HPF",20.0,20000.0,"FILTERS/0x00/HPF_Freq"},{1,"LPF",20.0,20000.0,"FILTERS/0x00/LPF_Freq"}};
  tabPlugin.push_back(defPlugin);
  defPlugin={0,"Mixer","mixer","",0,{}};
  tabPlugin.push_back(defPlugin);
  defPlugin={0,"Moog_VCF","moog_vcf","",3,{}};
  defPlugin.param={{0,"Frequency",1.0,88.0,"MOOG_VCF__Voltage_Controlled_Filter_/Corner_Frequency"},{1,"Resonance",0,1.0,"MOOG_VCF__Voltage_Controlled_Filter_/Corner_Resonance"},{2,"Level",-60,20,"MOOG_VCF__Voltage_Controlled_Filter_/VCF_Output_Level"}};
  tabPlugin.push_back(defPlugin);
  defPlugin={0,"ParametricEQ","parametric_eq","",7,{}};
  defPlugin.param={{0,"Low Boost",-40.0,40.0,"PARAMETRIC_EQ_SECTIONS/CTRL/Low_Shelf/Low_Boost_Cut"},{1,"Low Freq.",1.0,5000.0,"PARAMETRIC_EQ_SECTIONS/CTRL/Low_Shelf/Transition_Frequency"},{2,"Peak Boost",-40.0,40.0,"PARAMETRIC_EQ_SECTIONS/CTRL/Peaking_Equalizer/Peak_Boost_Cut"},{3,"Peak Freq.",0.0,100.0,"PARAMETRIC_EQ_SECTIONS/CTRL/Peaking_Equalizer/Peak_Frequency"},{4,"Peak Q",1.0,1000.0,"PARAMETRIC_EQ_SECTIONS/CTRL/Peaking_Equalizer/Peak_Q"},{5,"High Boost",-40,40,"PARAMETRIC_EQ_SECTIONS/CTRL/High_Shelf/High_Boost_Cut"},{6,"High Freq",20,10000,"PARAMETRIC_EQ_SECTIONS/CTRL/High_Shelf/Transition_Frequency"}};
  tabPlugin.push_back(defPlugin);
  defPlugin={0,"Phaser","phaserMono","",4,{}};
  defPlugin.param={{0,"Speed",0.0,10.0,"PHASER/0x00/Speed"},{1,"Feedback",-1.0,1.0,"PHASER/0x00/Feedback_Gain"},{2,"Output Level",-60.0,10.0,"PHASER/0x00/Phaser_Output_Level"},{3,"Notch_Depth",0.0,1.0,"PHASER/0x00/Notch_Depth__Intensity_"}};
  tabPlugin.push_back(defPlugin);
  defPlugin={0,"RingModulator","ringModulator","",2,{}};
  defPlugin.param={{0,"Depth",0.0,1.0,"RING_MODULATOR/0x00/depth"},{1,"Frequency",0.0,1000.0,"RING_MODULATOR/0x00/frequency"}};
  tabPlugin.push_back(defPlugin);
  defPlugin={0,"Speed","Speed","",1,{}};
  defPlugin.param={{0,"Speed",-1.0,3.0,"Player/Param/speed_"}};
  tabPlugin.push_back(defPlugin);
  defPlugin={0,"SpectrumAnalyser","spectral_level","",0,{}};
  tabPlugin.push_back(defPlugin);
}
void Plugin::onMouseMove(sf::Event e){
   std::cout << "mouse x: " << e.mouseMove.x << std::endl;
   std::cout << "mouse y: " << e.mouseMove.y << std::endl;
   
}
void Plugin::onClick(sf::Event e){
   if (e.mouseButton.button == sf::Mouse::Left){
      std::cout << "the left button was pressed" << std::endl;
      std::cout << "mouse x: " << e.mouseButton.x << std::endl;
      std::cout << "mouse y: " << e.mouseButton.y << std::endl;
   }
   if(e.mouseButton.x>70 && e.mouseButton.x<82 && e.mouseButton.y>24 && e.mouseButton.y<36){
   	if(externe==0){
   		externe=1;
   		daw.setTexture(bselect);
   	}else{
   		externe=0;
   		daw.setTexture(bNoSelect);
   	}
   }
   if(e.mouseButton.x>326 && e.mouseButton.x<346 && e.mouseButton.y>48 && e.mouseButton.y<70){
   	newCodePlugin();
   }
   if(e.mouseButton.x>326 && e.mouseButton.x<346 && e.mouseButton.y>94 && e.mouseButton.y<126){
   	newFaustIde();
   }
   if(e.mouseButton.x>70 && e.mouseButton.x<306 && e.mouseButton.y>56 && e.mouseButton.y<80){
   	textDef=1;
   	apptxt="";
   	flagPluginCurseur=1;
   	winPluginCurseur.setPosition(304,62);
   }
   if(e.mouseButton.x>70 && e.mouseButton.x<306 && e.mouseButton.y>100 && e.mouseButton.y<122){
   	textDef=2;
   	apptxt="";
   	flagPluginCurseur=1;
   	winPluginCurseur.setPosition(304,104);
   }
   if(e.mouseButton.x>70 && e.mouseButton.x<114 && e.mouseButton.y>190 && e.mouseButton.y<210){
   	textDef=3;
   	apptxt="";
   	flagPluginCurseur=1;
   	winPluginCurseur.setPosition(110,194);
   }
   if(e.mouseButton.x>122 && e.mouseButton.x<200 && e.mouseButton.y>190 && e.mouseButton.y<210){
   	textDef=4;
   	apptxt="";
   	flagPluginCurseur=1;
   	winPluginCurseur.setPosition(198,194);
   }
   if(e.mouseButton.x>210 && e.mouseButton.x<272 && e.mouseButton.y>190 && e.mouseButton.y<210){
   	textDef=5;
   	apptxt="";
   	flagPluginCurseur=1;
   	winPluginCurseur.setPosition(268,194);
   }
   if(e.mouseButton.x>280 && e.mouseButton.x<342 && e.mouseButton.y>190 && e.mouseButton.y<210){
   	textDef=6;
   	apptxt="";
   	flagPluginCurseur=1;
   	winPluginCurseur.setPosition(338,194);
   }
   if(e.mouseButton.x>70 && e.mouseButton.x<342 && e.mouseButton.y>218 && e.mouseButton.y<240){
   	textDef=7;
   	apptxt="";
   	flagPluginCurseur=1;
   	winPluginCurseur.setPosition(338,222);
   }
   if(e.mouseButton.x>356 && e.mouseButton.x<372 && e.mouseButton.y>194 && e.mouseButton.y<210){
   	gesIndex(-1);
   }
   if(e.mouseButton.x>356 && e.mouseButton.x<372 && e.mouseButton.y>216 && e.mouseButton.y<228){
   	gesIndex(1);
   }
   if(e.mouseButton.x>356 && e.mouseButton.x<372 && e.mouseButton.y>166 && e.mouseButton.y<182){
   	addParamPlugin();
   }
   if(e.mouseButton.x>36 && e.mouseButton.x<54 && e.mouseButton.y>166 && e.mouseButton.y<188){
   	delParamPlugin();
   }
   if(e.mouseButton.x>260 && e.mouseButton.x<312 && e.mouseButton.y>280 && e.mouseButton.y<307){
     rtf=0;
     winPlugin.close();
   }
    if(e.mouseButton.x>320 && e.mouseButton.x<366 && e.mouseButton.y>280 && e.mouseButton.y<307){
     rtf=1;
     if(nameFx.getString()!=""){
	     validerNewPlugin();
     }
     winPlugin.close();
   }
   
}
void Plugin::gesIndex(int index){
	stringstream adr;
	int n=numid+index;
	if(n>=0 && n<idparam){
		numid=numid+index;
		id.setString(to_string(tabnparam[numid].id));
		id.setPosition(110-id.getLocalBounds().width-2,192);
		param.setString(tabnparam[numid].nom);
		param.setPosition(198-param.getLocalBounds().width-2,192);
		string s=param.getString();
		std::cout << "index : "<<numid<<"tabnparam[numid].nom"<<tabnparam[numid].nom<<" name "<<s<< std::endl;
		adr << std::fixed<< std::setprecision(2)<<tabnparam[numid].min;
		min.setString(adr.str());
		min.setPosition(268-min.getLocalBounds().width-2,192);
		adr.clear();
		adr.str("");
		adr << std::fixed<< std::setprecision(2)<<tabnparam[numid].max;
		max.setString(adr.str());
		max.setPosition(338-max.getLocalBounds().width-2,192);
		adr.clear();
		adr.str("");
		adresse.setString(tabnparam[numid].adr);
		adresse.setPosition(338-adresse.getLocalBounds().width-2,220);
	}

	if(n==idparam){
		id.setString("");
		param.setString("");
		min.setString("");
		max.setString("");
		adresse.setString("");
		numid=idparam;
	}
}
void Plugin::deletePlugin(string nm){
	std::map<string,int>::iterator it;
	int id=listPlugin.find(nm)->second;
	tabPlugin.erase(tabPlugin.begin()+id);
	for(int i=0; i<tabPlugin.size(); i++){
    std::cout <<  " plugin name "<<tabPlugin[i].nomFx<< " id " <<i <<'\n';
	}
	listPlugin.clear();
	for(int i=0;i<tabPlugin.size();i++){
   	listPlugin.insert (std::pair<string, int>(tabPlugin[i].nomFx,i));
   }
	for (it=listPlugin.begin(); it!=listPlugin.end(); ++it){
    std::cout << it->first << " => " << it->second << " plugin name "<<tabPlugin[it->second].nomFx<<'\n';
	}
  	defListPlugin();
  	writeUsrPlugin();	
}
void Plugin::nettoyerPlugin(){
	tabPlugin.clear();
	systemPlugin();
	listPlugin.clear();
	string s="";
	for(int i=0;i<tabPlugin.size();i++){
   	listPlugin.insert (std::pair<string, int>(tabPlugin[i].nomFx,i));
   }
   defListPlugin();
  	string path=userConfig+"/Plugins";
	string file=path+"/usrPlugins";
	ofstream fichier(file, ios::out | ios::trunc);	
   if(fichier){
   	fichier<<s<< endl;
   	 fichier.close();
	}else{  // sinon
   cerr << "Erreur à l'ouverture du fichier!" << endl;
   }
}
void Plugin::newCodePlugin(){
	string nameFile;
	string command;
	if(nameFx.getString()==""){
		std::cout << "Vous devez définir le nom de ce plugin!"<< std::endl;
	}else{
		int rt=1;
		nameFile=userConfig+"/Plugins/"+nameFx.getString()+".lib";
		if(!boost::filesystem::exists(nameFile)){
			nameFile=userConfig+"/Plugins/"+"nplug.lib";
		}
		command=editeur+"  "+nameFile+" -f faust-mode -geometry 110x40 &";
		rt=system(const_cast<char*>(command.c_str()));
		if(rt!=1){
			std::cout << "rt " << rt << std::endl;
		}
	}
}
void Plugin::newFaustIde(){
	string nameFile;
	string command;
	if(nameFx.getString()==""){
		std::cout << "Vous devez définir le nom de ce plugin!"<< std::endl;
	}else{
		int rt=1;
		nameFile=userConfig+"/Plugins/"+nameFx.getString()+".lib";
		if(!boost::filesystem::exists(nameFile)){
			nameFile=userConfig+"/Plugins/"+"nplug.lib";
		}
		command=navigateur+" https://faustide.grame.fr &";
		rt=system(const_cast<char*>(command.c_str()));
		if(rt!=1){
			std::cout << "rt " << rt << std::endl;
		}
	}
}
void Plugin::newPluginText(sf::Event e){
   int key=e.key.code;
   stringstream adr;
   if (e.text.unicode < 128){
		if(key==8){
	      apptxt=apptxt.substr(0,apptxt.length()-1);
	 	}else{
			apptxt=apptxt+static_cast<char>(e.text.unicode);
		}
		switch (textDef){
       		case 1:
       			if(editMode==0){
	       			nameFx.setString(apptxt);
	       			nameFx.setPosition(304-nameFx.getLocalBounds().width-2,60);
       			}
       			break;
       		case 2:
       			fonctionFx.setString(apptxt);
       			fonctionFx.setPosition(304-fonctionFx.getLocalBounds().width-2,102);
       			break;
       		case 3:
       			id.setString(apptxt);
       			id.setPosition(110-id.getLocalBounds().width-2,192);
       			break;
       		case 4:
       			param.setString(apptxt);
       			param.setPosition(198-param.getLocalBounds().width-2,192);
       			break;
       		case 5:
       			min.setString(apptxt);
       			min.setPosition(268-min.getLocalBounds().width-2,192);
       			break;
       		case 6:
       			max.setString(apptxt);
       			max.setPosition(338-max.getLocalBounds().width-2,192);
       			break;
       		case 7:
       			adresse.setString(apptxt);
       			adresse.setPosition(338-adresse.getLocalBounds().width-2,220);
       			break;
       		default:
       			break;
	   }
   }
   adr.clear();
  	adr.str(""); 
}
void Plugin::addParamPlugin(){
	parametre nparam;
	stringstream adr;
	string s;
	s=id.getString();
	nparam.id=stoi(s);
	nparam.nom=param.getString();
	s=min.getString();
	nparam.min=stof(s);
	s=max.getString();
	nparam.max=stof(s);
	nparam.adr=adresse.getString();
	tabnparam.push_back(nparam);
	std::cout << "idParam: "<<idparam<< "   "<<s<<"nparam"<<tabnparam[idparam].nom  << std::endl;
	idparam++;
	id.setString("");
	param.setString("");
	min.setString("");
	max.setString("");
	adresse.setString("");
	numid=idparam;
}
void Plugin::delParamPlugin(){
	tabnparam.erase(tabnparam.begin()+numid);
	stringstream adr;
	string s;
	idparam=tabnparam.size();
	numid=0;
	if(editMode==1){
	   gesIndex(0);
	}else{
		string nplug=nameFx.getString();
		deletePlugin(nplug);
		nameFx.setString(nplug);
 	   writeListPlugin();
 	   defListPlugin();
	}
}
void Plugin::readListPlugin(){
  std::cout << "userConfig: " << userConfig << std::endl;
  string path=userConfig+"/Plugins";
  string file=path+"/usrPlugins";
  plugin defPlugin;
  ifstream fichier(file, ios::in); 
  string contenu;
  parametre pr;
  float s1;
  int s2;
  string pf[2];
  string pf2[7];
  vector<string> pf3;
  vector<string> pf4;
  int i=0;
  if(fichier){ 
     while(getline(fichier, contenu)){
       char * cstr = new char [contenu.length()+1];
       std::strcpy (cstr, contenu.c_str());
       char * p = std::strtok (cstr,"=");
       i=0;
       while (p!=0){
 	     pf[i]=p;
 	     i++;
	     p = std::strtok(NULL," ");
       }
       if(pf[0]=="plugin"){
       	int j=0;
       	char * cstr2 = new char [pf[1].length()+1];
       	std::strcpy (cstr2, pf[1].c_str());
       	char * p2 = std::strtok (cstr2,",");
       	while (p2!=0){
 	     		pf2[j]=p2;
 	     		j++;
	     		p2 = std::strtok(NULL,",");
      	}
      	defPlugin.type=stoi(pf2[0]);
      	defPlugin.nomFx=pf2[1];
      	defPlugin.fx=pf2[2];
      	defPlugin.path=pf2[3];
      	defPlugin.nbpar=stoi(pf2[4]);
       }
       
       if(pf[0]=="param"){
      	std::cout << "pf1 "<<pf[1]  << std::endl;
      	pf3=explode(pf[1], ';');
      	for(int m=0;m<pf3.size();m++){
      		std::cout << "size "<<pf3.size()<<"param pf3: "<<pf3[m]  << std::endl;
      	}
      	for(int m=0;m<pf3.size();m++){
      		pf4=explode(pf3[m], ',');
      		pr.id=stoi(pf4[0]);
 	     		pr.nom=pf4[1];
 	     		pr.min=stof(pf4[2]);
 	     		pr.max=stof(pf4[3]);
 	     		pr.adr=pf4[4];
 	     		defPlugin.param.push_back(pr);
      	}
			pf3.clear();
			pf4.clear();
			
       }
       if(pf[0]=="end"){
       	tabPlugin.push_back(defPlugin);
       	defPlugin.param.clear();
       }

     }
     fichier.close();
   }else{  // sinon
      cerr << "Erreur à l'ouverture du fichier!" << endl;
	} 
   listPlugin.clear(); 
   for(int i=0;i<tabPlugin.size();i++){
   	listPlugin.insert(std::pair<string, int>(tabPlugin[i].nomFx,i));
   }
   std::map<string,int>::iterator it;
   for (it=listPlugin.begin(); it!=listPlugin.end(); ++it){
    std::cout << it->first << " => " << it->second << " plugin name "<<tabPlugin[it->second].nomFx<<'\n';
	}

}
const vector<string> Plugin::explode(const string& s, const char& c){
	string buff{""};
	vector<string> v;
	
	for(auto n:s)
	{
		if(n != c) buff+=n; else
		if(n == c && buff != "") { v.push_back(buff); buff = ""; }
	}
	if(buff != "") v.push_back(buff);
	
	return v;
}
std::map<std::string, int>& Plugin::getListPlugin(){
	return listPlugin;
}
std::vector<Plugin::plugin>& Plugin::getTabPlugin(){
	return tabPlugin;
}
void Plugin::afficheListPlugin(){
	for(std::map<string, int>::iterator it=listPlugin.begin(); it!=listPlugin.end(); ++it){
     	std::cout << it->first <<" , " <<it->second<< std::endl;
   }
}
void Plugin::validerNewPlugin(){
	if(editMode==0){
		writeListPlugin();
	}else{
		string nplug=nameFx.getString();
		deletePlugin(nplug);
		nameFx.setString(nplug);
 	   writeListPlugin();
 	   defListPlugin();
	}
}
void Plugin::writeListPlugin(){
	string path=userConfig+"/Plugins";
	string file=path+"/usrPlugins";
	string s;
	parametre pr;
	stringstream adr;
	ofstream fichier(file, ios::out | ios::app);	
	plugin defPlugin;
   if(fichier){
   	string np="plugin="+to_string(externe)+","+nameFx.getString()+","+fonctionFx.getString()+","+path+","+to_string(idparam);
   	fichier<<np<< endl;
   	for(int i=0;i<idparam;i++){
   		adr<<tabnparam[i].id<<","<<tabnparam[i].nom<<","<<tabnparam[i].min<<","<<tabnparam[i].max<<","<<tabnparam[i].adr;
   		s=s+adr.str()+";";
   		adr.clear();
			adr.str("");
   	}
   	s=s.substr(0,s.length()-1);
   	fichier<<"param="<<s<< endl;  
   	fichier<<"end=" << endl;
   fichier.close();
   if(externe==1){
   	defPlugin.type=2;
   }else{
   	defPlugin.type=1;
   }
	defPlugin.nomFx=nameFx.getString();
	defPlugin.fx=fonctionFx.getString();
	defPlugin.path=path;
	defPlugin.nbpar=idparam;
	for(int i=0;i<idparam;i++){
		defPlugin.param.push_back(tabnparam[i]);
	}
	
	tabPlugin.push_back(defPlugin);
	listPlugin.clear();
	for(int i=0;i<tabPlugin.size();i++){
   	listPlugin.insert (std::pair<string, int>(tabPlugin[i].nomFx,i));
   }
    fichier.close();
	}else{  // sinon
      cerr << "Erreur à l'ouverture du fichier!" << endl;
	} 	
}
void Plugin::writeUsrPlugin(){
	string path=userConfig+"/Plugins";
	string file=path+"/usrPlugins";
	string s;
	string s2;
	stringstream adr;
	ofstream fichier(file,  ios::out | ios::trunc);
	std::map<string, int>::iterator it = listPlugin.begin();
	string rs;
	int i=0;
   if(fichier){
   	while (it!=listPlugin.end()){
   		i=it->second;
	  		if(tabPlugin[i].type>0){
	   		s="plugin="+to_string(tabPlugin[i].type)+","+tabPlugin[i].nomFx+","+tabPlugin[i].fx+","+tabPlugin[i].path+","+to_string(tabPlugin[i].nbpar);
	   		fichier<<s<< endl;
	   		s2="";
	   		for(int j=0;j<tabPlugin[i].nbpar;j++){
		   		adr<<tabPlugin[i].param[j].id<<","<<tabPlugin[i].param[j].nom<<","<<tabPlugin[i].param[j].min<<","<<tabPlugin[i].param[j].max<<","<<tabPlugin[i].param[j].adr;
		   		s2=s2+adr.str()+";";
		   		adr.clear();
					adr.str("");
	   		}
	   		s2=s2.substr(0,s2.length()-1);
	   		fichier<<"param="<<s2<< endl;  
	   		fichier<<"end=" << endl;
	  		}
	  		std::cout << it->first << " => " << it->second << " plugin name "<<tabPlugin[it->second].nomFx<<'\n';
	  		std::cout << "s " << s<< " s2 "<<s2<<'\n';
	  		it++;
   	}
   	
   	 fichier.close();
	}else{  // sinon
   cerr << "Erreur à l'ouverture du fichier!" << endl;
   }
   /*
   if(winEditPlugin.isOpen()){
	   winEditPlugin.close();
	}
	*/
} 

// ***************************************************************************************************************
//                                   Edit plugin
// ***************************************************************************************************************

bool Plugin::editListPlugin(string titreWPlugin){
  titreWinPlugin="Edit Plugin";
  rtf=0;
  tabnparam.clear();
  stringstream adr;
    
  sf::Texture edit;
  adr << std::fixed << pluginGui<<"/text-editor2.png";
  edit.loadFromFile(adr.str());
  sf::Sprite editor(edit);
  adr.clear();
  adr.str("");
  sf::Texture trashF;
  adr << std::fixed << pluginGui<< "/trashF2.png";
  trashF.loadFromFile(adr.str());
  sf::Sprite trash(trashF);
  adr.clear();
  adr.str("");
  sf::Texture bvide;
  adr << std::fixed << pluginGui<< "/bvide.png";
  bvide.loadFromFile(adr.str());
  sf::Sprite bfermer(bvide);
  bfermer.setPosition(130,366);
  adr.clear();
  adr.str("");
  
  sf::Text fermerT;
  fermerT.setFont(font);
  fermerT.setCharacterSize(13);
  fermerT.setFillColor(sf::Color(0, 0, 0));
  fermerT.setPosition(137,373);
  fermerT.setString("Fermer");

  //readListPlugin();
  if(listPlugin.size()<15){
  	asize=listPlugin.size();
  }else{
  	asize=15;
  }
  
  std::map<string, int>::iterator it = listPlugin.begin();
  it++;
  int lid=0;
  
  for(int i=0;i<15;i++){
  	  plugName[i].setFont(font);
  	  plugName[i].setCharacterSize(13);
  	  plugName[i].setFillColor(sf::Color(0, 0, 0));
  	  plugName[i].setPosition(8,12+(i*24));
  	  plugName[i].setString("");
  }
  defListPlugin();
  wheight=404;
  wWidth=220;

  winEditPlugin.create(sf::VideoMode(wWidth, wheight), titreWinPlugin);
  
  
  while (winEditPlugin.isOpen()) {                             // Événements
	sf::Event Editevent;
	while (winEditPlugin.pollEvent(Editevent)){                // Gestion des évènements de la fenêtre principale
		switch (Editevent.type){
			case sf::Event::Closed:            // Fermeture de la fenêtre
				winEditPlugin.close();
				break;
			case sf::Event::MouseButtonPressed:
				editOnClick(Editevent);
				break;
			case sf::Event::MouseMoved:
				editMouseMove(Editevent);
				break;
				
			case sf::Event::MouseButtonReleased:
				onMouseUpWinEdit(Editevent);
				break;
			case sf::Event::MouseWheelScrolled:
		      mouseEditWheel(Editevent);
	         break;			  					
			default:                            // on ne traite pas les autres types d'évènements
				break;
		}            
        
	}
        // Clear screen
	winEditPlugin.setActive(true);
	winEditPlugin.pushGLStates();
	winEditPlugin.clear(sf::Color(224,224,224));
	winEditPlugin.draw(winSelectCurseur);
	for(int i=0;i<nbplug;i++){
		plugName[i].setFillColor(sf::Color(0,0,0));
		plugName[selectId].setFillColor(sf::Color(255,255,255));
		winEditPlugin.draw(plugName[i]);
		editor.setPosition(120,12+(i*24));
		winEditPlugin.draw(editor);
		trash.setPosition(150,12+(i*24));
		winEditPlugin.draw(trash);
	}
	winEditPlugin.draw(bfermer);
	winEditPlugin.draw(fermerT);
	winEditPlugin.draw(shapeEditSlider);
	winEditPlugin.draw(shapeEditMSlider);
   /*
   if(flagPluginCurseur==1){
		if(clockPluginCurseur.getElapsedTime()>sf::seconds(0.8f)){
			winPlugin.draw(winPluginCurseur);
			if(clockPluginCurseur.getElapsedTime()>sf::seconds(1.6f)){
				clockPluginCurseur.restart();
			}
		}
	}
	*/	
		
	winEditPlugin.display();
	winEditPlugin.popGLStates();
	winEditPlugin.setActive(false);
  }
  return rtf;
  
}
void Plugin::editOnClose(){
	
}
void Plugin::editOnClick(sf::Event e){
	if(e.mouseButton.x>shapeEditMSlider.getPosition().x && e.mouseButton.x<shapeEditMSlider.getPosition().x+shapeEditMSlider.getSize().x && e.mouseButton.y>shapeEditMSlider.getPosition().y && e.mouseButton.y<shapeEditMSlider.getPosition().y+shapeEditMSlider.getSize().y){
   	flagEditMSlider=1;
   	FxMdY=e.mouseButton.y;
   }
   if(e.mouseButton.x>120 && e.mouseButton.x<138 && e.mouseButton.y>14 && e.mouseButton.y<366){
   	int Id=((e.mouseButton.y-8)/24);
   	string s=plugName[Id].getString();
   	int plugId=listPlugin.find(s)->second;
   	std::cout << " edit Id "<<Id<<" listEditIndex "<<listEditIndex<<" name: " << s<<" plugId "<<plugId << std::endl;
   	for(int i=0; i<tabPlugin.size(); i++){
    std::cout <<  " plugin name "<<tabPlugin[i].nomFx<< " id " <<i <<'\n';
	}
   	modifPlugin(plugId);
   }
   if(e.mouseButton.x>150 && e.mouseButton.x<168 && e.mouseButton.y>14 && e.mouseButton.y<366){
   	int Id=((e.mouseButton.y-8)/24);
   	string s=plugName[Id].getString();
   	int plugId=listPlugin.find(s)->second;
   	deletePlugin(s);
   	std::cout << " delete Id "<<Id<<" listEditIndex "<<listEditIndex<<" name: " << s<<" plugId "<<plugId << std::endl;
   }
	if(e.mouseButton.x>130 && e.mouseButton.x<168 && e.mouseButton.y>370 && e.mouseButton.y<396){
		winEditPlugin.close();
	}
}
void Plugin::editMouseMove(sf::Event e){
	std::cout << "mouse x: " << e.mouseMove.x << std::endl;
   std::cout << "mouse y: " << e.mouseMove.y << std::endl;
    if(e.mouseMove.x>6 && e.mouseMove.x<180 && e.mouseMove.y>10 && e.mouseMove.y<wheight-50){
    	selectId=(e.mouseMove.y-8)/24;
    	if(selectId>14){
    		selectId=14;
    	}
    	if(selectId<nbplug){
    		winSelectCurseur.setPosition(winSelectCurseur.getPosition().x,8+(selectId*24));
    	}
    }
    if (flagEditMSlider==1 && e.mouseMove.x > shapeEditMSlider.getPosition().x && e.mouseMove.x<shapeEditMSlider.getPosition().x+shapeEditMSlider.getSize().x && e.mouseMove.y > shapeEditMSlider.getPosition().y && e.mouseMove.y<shapeEditMSlider.getPosition().y+shapeEditMSlider.getSize().y){ 
     int nposy=shapeEditMSlider.getPosition().y+(e.mouseMove.y-FxMdY);
     if(e.mouseMove.y<FxMdY){
     	listEditIndex=listEditIndex-1;
     	if(listEditIndex<1){
     		listEditIndex=0;
     	}
     }else{
     	listEditIndex=listEditIndex+1;
     	if(listEditIndex>listPlugin.size()-15){
     		listEditIndex=listPlugin.size()-15;
     	}
     }
     if(nposy<shapeEditSlider.getPosition().y+1){
   		nposy=shapeEditSlider.getPosition().y+1;
     }
     if(nposy+shapeEditMSlider.getSize().y>shapeEditSlider.getPosition().y+shapeEditSlider.getSize().y){
   		nposy=(shapeEditSlider.getPosition().y+shapeEditSlider.getSize().y)-shapeEditMSlider.getSize().y;
     }
     shapeEditMSlider.setPosition(shapeEditMSlider.getPosition().x,nposy);
     FxMdY=e.mouseMove.y; 
     defListPlugin();
  }
}
void Plugin::onMouseUpWinEdit(sf::Event e){
	flagEditMSlider=0;
}
void Plugin::mouseEditWheel(sf::Event e){
  int nposy;
  if(e.mouseWheelScroll.x>8 && e.mouseWheelScroll.x<212 && e.mouseWheelScroll.y>6 && 370){
	  if (e.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel){
		if(e.mouseWheelScroll.delta==1){
			listEditIndex=listEditIndex-1;
			if(listEditIndex<1){
			 	listEditIndex=0;
			 	nposy=0;
			}else{
				nposy=-1;
			} 	
		}else{
			listEditIndex=listEditIndex+1;
			if(listEditIndex>listPlugin.size()-15){
			 	listEditIndex=listPlugin.size()-15;
			 	nposy=0;
			}else{
				nposy=1;
			}
		}
		defListPlugin();
	  }
	  shapeEditMSlider.setPosition(shapeEditMSlider.getPosition().x,shapeEditMSlider.getPosition().y+nposy);
  }
}
void Plugin::defListPlugin(){
  	std::map<string, int>::iterator it = listPlugin.begin();
  	it++;
   for(int k=0;k<listEditIndex;k++){
  	  	it++;
  	}
  	int k=0;
  	int max=listPlugin.size()-listEditIndex;
  	int nb;
  	if(max<15){
  		nb=max;
  	}else{
  		nb=15;
  	}
  	for(int i=0;i<15;i++){
  		plugName[i].setString("");
  	}
  	while (it!=listPlugin.end() && k<nb){
  		if(tabPlugin[it->second].type>0){
  			std::cout <<" tabPlugin[it->second].type "<<tabPlugin[it->second].type<< std::endl;
	  		plugName[k].setString(it->first);
	  		k++;
  		}
  		it++;
   }
   nbplug=k;
   nb=shapeEditSlider.getSize().y-listPlugin.size()+15;
   if(nb>10){
   	shapeEditMSlider.setSize(sf::Vector2f(shapeEditMSlider.getSize().x,nb));
   }
}

void Plugin::modifPlugin(int pid){
	stringstream adr;
	nameFx.setString(tabPlugin[pid].nomFx);
	std::cout <<  " plugin type "<<tabPlugin[pid].type<<'\n';
	if(tabPlugin[pid].type==2){
			externe=1;
   		daw.setTexture(bselect);
   }else{
   		externe=tabPlugin[pid].type;
   		daw.setTexture(bNoSelect);
   }
	nameFx.setPosition(304-nameFx.getLocalBounds().width-2,60);
	fonctionFx.setString(tabPlugin[pid].fx);
	fonctionFx.setPosition(304-fonctionFx.getLocalBounds().width-2,102);
	parametre pr;
	id.setString("");
	param.setString("");
	min.setString("");
	max.setString("");
	adresse.setString("");
	tabnparam.clear();

	
	for(int i=0;i<tabPlugin[pid].nbpar;i++){
		pr.id=tabPlugin[pid].param[i].id;
		pr.nom=tabPlugin[pid].param[i].nom;
		pr.min=tabPlugin[pid].param[i].min;
		pr.max=tabPlugin[pid].param[i].max;
		pr.adr=tabPlugin[pid].param[i].adr;
		tabnparam.push_back(pr);
	}
	
	idparam=tabnparam.size();
	numid=0;
	gesIndex(0);
	drawPlugin(1,externe,"Modif plugin");
	
}