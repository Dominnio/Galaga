#include "Pocisk.h"
#include <iostream>
#include "Przeciwnik.h"
#include <list>
#include <cmath>

Pocisk::Pocisk()
{
    //std::cout<<"stworzono pocisk" <<std::endl;
}

Pocisk::Pocisk(double x,double y)
{
    //std::cout<<"stworzono pocisk" <<std::endl;
    tekstura_pocisku.loadFromFile( "pocisk_01.png" );
    obrazek_pocisku.setTexture( tekstura_pocisku );
    szerokosc=tekstura_pocisku.getSize().x;
    wysokosc=tekstura_pocisku.getSize().y;
    this->x=x;
    this->y=y;

}

Pocisk::~ Pocisk()
{
    // std::cout<<"usunieto pocisk" <<std::endl;
    //dtor
}

void Pocisk::porusz(std::list<Przeciwnik*> listaPrzeciwnikow, int a){
    y=y-15;
}

double Pocisk::getX(){
    return x;
}

double Pocisk::getY(){
    return y;
}

