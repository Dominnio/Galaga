#ifndef ZDERZENIE_H
#define ZDERZENIE_H
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include<Pocisk.h>
#include<Przeciwnik.h>
#include<Przeszkoda.h>
#include<Samolot.h>
#include <list>
#include <cstddef>
#include <iostream>

class Zderzenie
{
    public:
        Zderzenie();
        Zderzenie(double x,double y);
        virtual ~Zderzenie();
        int kolizja(double x1,double x2,double y1,double y2,double a,double b);
        int pocisk_przeszkoda_przeciwnik(std::list<Pocisk*> &listaPociskow,std::list<Przeciwnik*> &listaPrzeciwnikow,std::list<Przeszkoda*> &listaPrzeszkod, sf::Texture tekstura_pocisku, Samolot &samolot);       //sprawdza czy nastąpiła kolizja pomiędzy obiektami
        double getX();
        double getY();

    protected:
    private:
        sf::SoundBuffer buffer_zniszczenia;
        sf::Sound dzwiek_zniszczenia;
        double x;
        double y;
};

#endif // ZDERZENIE_H
