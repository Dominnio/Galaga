#include "Przeciwnik_strzelajacy.h"
#include "Pocisk_przeciwnika.h"

#include <iostream>
#include <Przeszkoda.h>


Przeciwnik_strzelajacy::Przeciwnik_strzelajacy()
{
    //ctor
}

Przeciwnik_strzelajacy::~Przeciwnik_strzelajacy()
{
    //dtor
}

Przeciwnik_strzelajacy::Przeciwnik_strzelajacy(double x,double y)
{
    tekstura_przeciwnika.loadFromFile( "przeciwnik_02.png" );
    obrazek_przeciwnika.setTexture( tekstura_przeciwnika );
    //obrazek_przeciwnika.setScale(0.5,0.5);
    szerokosc=tekstura_przeciwnika.getSize().x;
    wysokosc=tekstura_przeciwnika.getSize().y;
    this->x=x;
    this->y=y;
    zegar.restart();
}

void Przeciwnik_strzelajacy::strzelaj(std::list<Pocisk*> &listaPociskow){
    elapsed=zegar.getElapsedTime();
    if(elapsed > t1){
        listaPociskow.push_front(new Pocisk_przeciwnika(x+szerokosc/2-10,y+wysokosc+5));
        zegar.restart();
        elapsed=sf::seconds(0);
    }
}
