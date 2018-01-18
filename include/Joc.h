#ifndef JOC_H
#define JOC_H
#include "PilaCartes.h"
#include "Tauler.h"
#include "Carta.h"
#include "HardwareInterface.h"

class Joc
{
    public:
        Joc(int llavor, HI::HITexture c[]);
        //Pre: -- //Post: Printeja
        void mostrar(const point2D&);
        //Pre: -- //Post: Intenta realitzar un moviment en el joc
        void Accio(Posicio_Carta, Posicio_Carta, bool&);
		void Processar_origen(Posicio_Carta origen);
		void Netejar_Buffer();
		Posicio_Carta Localitzar_Carta(point2D t)const;
		
		bool a_guanyada; //Estalvia un getter

    private:
        //METODES PRIVATS
        //MODIFICADORS
        //Pre: Baralla amb almenys 28 cartes //Post: Posa les cartes que no cabien al tauler a la pila de la m�
        void emplenar_ma(Baralla);
        //Pre: -- //Post: Posa a la columna col del tauler la carta car. Retorna cert si es mou amb �xit
        bool PosarAlTauler(Carta car, int col);
        //Pre: -- //Post: Retorna cert si s'ha guanyat la partida
        bool Partida_Guanyada();
        //Pre: -- //Post: Posa la carta car a la pila corresponent i retorna cert si ha sigut possible
		bool PosarALaPila(Carta car);
		int Triar_Opcio(Posicio_Carta origen, Posicio_Carta desti);
		void NumCartesColumna(int, int &, int &)const;

        //ATRIBUTS:
        int a_opcio;
        PilaCartes a_ma, a_descartades, a_pals[4];
        Tauler a_tauler;
};

#endif // JOC_H