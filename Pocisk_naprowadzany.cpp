#include "Pocisk_naprowadzany.h"
#include <iostream>
#include "Przeciwnik.h"
#include "Pocisk.h"
#include <list>
#include <cmath>

Pocisk_naprowadzany::Pocisk_naprowadzany()
{
    //ctor
}

Pocisk_naprowadzany::~Pocisk_naprowadzany()
{
    //dtor
}

Pocisk_naprowadzany::Pocisk_naprowadzany(double x,double y) {
    tekstura_pocisku.loadFromFile( "pocisk_02.png" );
    obrazek_pocisku.setTexture( tekstura_pocisku );
    szerokosc=tekstura_pocisku.getSize().x;
    wysokosc=tekstura_pocisku.getSize().y;
    this->x=x;
    this->y=y;
}


void Pocisk_naprowadzany::porusz(std::list<Przeciwnik*> listaPrzeciwnikow, int c){
    y=y-9;
    double a=100000,b=0;
    int i=1;
    std::list<Przeciwnik*>::iterator najblizszy;
    if(listaPrzeciwnikow.empty()==true){
    }else{
        for(std::list<Przeciwnik*>::iterator iter=listaPrzeciwnikow.begin(); iter != listaPrzeciwnikow.end();iter++,i++){
            b=sqrt((((*iter)->getX()+(*iter)->szerokosc/2-x+szerokosc/2)*((*iter)->getX()+(*iter)->szerokosc/2-x+szerokosc/2))+(((*iter)->getY()+(*iter)->wysokosc/2-y-wysokosc)*((*iter)->getY()+(*iter)->wysokosc/2-y-wysokosc)));
            if( b < a){
                a=b;
                najblizszy=iter;
            }
        }
        a=(*najblizszy)->getX()+(*najblizszy)->szerokosc/2;
        if(a>x+szerokosc/2){
            x=x+5;
        }else{
            x=x-5;
        }
    }
}
