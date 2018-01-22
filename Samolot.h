#ifndef SAMOLOT_H
#define SAMOLOT_H
#include "Pocisk.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Okno;

class Samolot
{
    public:
        void poruszWPrawo();
        void poruszWLewo();
        void poruszDoPrzodu();
        void poruszDoTylu();
        void ustaw_pozycje(double x,double y);      //ustawia początkową pozycję samolotu (przy wczytywaniu gry jest ona ta któ©a została zapisana)
        void strzelaj(Okno *okno);                  //tworzy nowy, odpowiedni pociek
        Samolot();
        Samolot(double x,double y);
        virtual ~Samolot();
        double getX() const;
        double getY() const;
        double zestrzelonych_przeciwnikow=0;
        double ilosc_pociskow=0;
        double ilosc_strzalow=0;
        int punkty=0;
        double punkty_stracone=0;
        double szerokosc;
        double wysokosc;

        sf::Sprite obrazek_samolotu;
        sf::Texture tekstura_samolotu;
        //Pocisk* wystrzelPocisk();
    protected:
    private:
        double x,y;
};

#endif // SAMOLOT_H
