#ifndef POCISK_H
#define POCISK_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>
#include <list>

class Przeciwnik;

class Pocisk
{
    public:
        Pocisk();
        Pocisk(double x,double y);
        virtual void porusz(std::list<Przeciwnik*> listaPrzeciwnikow,int a);
        sf::Sprite obrazek_pocisku;
        sf::Texture tekstura_pocisku;
        double szerokosc;
        double wysokosc;
        double getX();
        double getY();
        virtual ~Pocisk();
    protected:
        double x;
        double y;
    private:
};

#endif // POCISK_H
