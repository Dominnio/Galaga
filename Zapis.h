#ifndef ZAPIS_H
#define ZAPIS_H
#include "Samolot.h"
#include "Przeciwnik.h"
#include "Przeszkoda.h"

#include <list>

class Zapis
{
    public:
        Zapis();
        virtual ~Zapis();
        int zapisz_wynik(int punkty);   //zapisuje tylko wynik (za każdą skończoną grą)
        void zapisz_obiekty(std::list<Przeciwnik*> &listaPrzeciwnikow, std::list<Przeszkoda*> &listaPrzeszkod,Samolot samolot);                                 //zapisuje grę po wciśnięciu S podczas rozgrywki
        int wczytaj(std::list<Przeciwnik*> &listaPrzeciwnikow, std::list<Przeszkoda*> &listaPrzeszkod,Samolot &samolot,sf::RenderWindow &okno_aplikacji);       //wczytuje grę
        void wczytaj_rekordy(sf::RenderWindow &okno_aplikacji);
    protected:
    private:
        sf::Font czcionka;
        sf::Text text_zapisu;
        sf::Text text_rekordow;
};

#endif // ZAPIS_H
