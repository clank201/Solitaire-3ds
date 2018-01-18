#include <iostream>
#include <string>
#include <sstream>
#include <random> //rng
#include <cstdlib>
#include "Baralla.h"
#include <cmath>
#include "Joc.h"
#include "Constants.h"
#include "HardwareInterface.h"
#include <time.h>

using namespace std;

void Carregar_Cartes(HI::HITexture c[]);

int main()
{	
	HI::systemInit();
	HI::setBackgroundColor(RGBA8(0x40, 0xFF, 0x40, 0xFF));
	srand(time(NULL));
	HI::consoleInit();
	
	HI::HITexture cartes[53]; //+1 pel darrera de la carta
	Carregar_Cartes(cartes);
	bool touchframeanterior=false, acciofeta=false;
	Joc joc(rand()%12345,cartes);
	Posicio_Carta origen, desti;
	point2D touch;
	int held, down;
			
	while (HardwareInterface::aptMainLoop()) {
		HI::updateHID();
		held = HI::getKeysHeld();
		down = HI::getKeysDown();
		if(!held)HI::sleepThread(100000000);
		if(held & HI::HI_KEY_START) break;
		if(down & HI::HI_KEY_B) joc=Joc(rand()%12345,cartes);
		if(!joc.a_guanyada){
			if (held & HI::HI_KEY_TOUCH){
				HI::updateTouch(touch);
				if(!touchframeanterior){
					origen=joc.Localitzar_Carta(touch);
					joc.Processar_origen(origen); //return bool per saber si hem agafat una carta correcte?
				}
			}
			else if(touchframeanterior){
				desti=joc.Localitzar_Carta(touch);
				joc.Accio(origen,desti,acciofeta);
				joc.Netejar_Buffer();			
			}
			touchframeanterior=held & HI::HI_KEY_TOUCH;

			HI::startFrame(HI::SCREEN_BOT);
			joc.mostrar(touch); 
			HI::endFrame();
			HI::swapBuffers();
		}
		else{
			cout<<"HAS GUANYAT ENJORAGUENA"<<endl;
			HI::sleepThread(10000000000);
			break;
		}
	}
	for(int i=0;i<53;i++)HI::freeTexture(cartes[i]);
	HI::consoleFini();
	HI::systemFini();
	return 0;
}

void Carregar_Cartes(HI::HITexture c[]){
	string ruta="gamedata/", extensio=".png", nom;
	for(int i=0;i<53;i++){
		stringstream ss;
		ss<<i+1;
		nom=ruta+ss.str()+extensio;
		cout<<"Carregant: "<<ss.str()+extensio<<endl;
		c[i]=HI::loadPngFile(nom.c_str());
	}
}