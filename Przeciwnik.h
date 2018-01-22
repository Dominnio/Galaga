#ifndef PRZECIWNIK_H
#define PRZECIWNIK_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>
#include <list>
#include <Przeszkoda.h>

class Pocisk;

class Przeciwnik
{
    public:
        Przeciwnik();
        Przeciwnik(double x,double y);
        virtual void strzelaj(std::list<Pocisk*> &listaPociskow);       // tworzy nowy pocisk przeciwnika
        double wysokosc;
        double szerokosc;
        sf::Sprite obrazek_przeciwnika;
        sf::Texture tekstura_przeciwnika;
        virtual void porusz(std::list<Pocisk*> listaPociskow,std::list<Przeszkoda*> listaPrzeszkod);        // porsuza przecwnikime (odpowiednio dla każdego typu)
        double getX();
        double getY();
        virtual ~Przeciwnik();
    protected:
        double x;
        double y;
    private:
};

#endif // PRZECIWNIK_H
