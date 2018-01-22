#include "Pocisk_przeciwnika.h"

Pocisk_przeciwnika::Pocisk_przeciwnika()
{
    //ctor
}

Pocisk_przeciwnika::~Pocisk_przeciwnika()
{
    //dtor
}

Pocisk_przeciwnika::Pocisk_przeciwnika(double x,double y) {
    tekstura_pocisku.loadFromFile( "pocisk_03.png" );
    obrazek_pocisku.setTexture( tekstura_pocisku );
    szerokosc=tekstura_pocisku.getSize().x;
    wysokosc=tekstura_pocisku.getSize().y;
    this->x=x;
    this->y=y;
}

void Pocisk_przeciwnika::porusz(std::list<Przeciwnik*> listaPrzeciwnikow, int a){
    y=y+9;
}
