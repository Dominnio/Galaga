#include "Przeciwnik.h"
#include "Przeszkoda.h"

#include <Okno.h>
#include <iostream>
#include "Pocisk.h"

Przeciwnik::Przeciwnik()
{
    //ctor
}

Przeciwnik::Przeciwnik(double x,double y)
{
    //std::cout<<"stworzono przeciwnika" <<std::endl;
    tekstura_przeciwnika.loadFromFile( "przeciwnik_01.png" );
    obrazek_przeciwnika.setTexture( tekstura_przeciwnika );
    //obrazek_przeciwnika.setScale(0.5,0.5);
    szerokosc=tekstura_przeciwnika.getSize().x;
    wysokosc=tekstura_przeciwnika.getSize().y;
    this->x=x;
    this->y=y;

}

Przeciwnik::~Przeciwnik()
{
    //std::cout<<"usunieto przeciwnika" <<std::endl;
    //dtor
}

void Przeciwnik::porusz(std::list<Pocisk*> listaPociskow,std::list<Przeszkoda*> listaPrzeszkod){
    y=y+4.5;
}

double Przeciwnik::getX(){
    return x;
}

double Przeciwnik::getY(){
    return y;
}

void Przeciwnik::strzelaj(std::list<Pocisk*> &listaPociskow){
}

