#include "Pocisk_skrecajacy.h"

Pocisk_skrecajacy::Pocisk_skrecajacy()
{
    //ctor
}

Pocisk_skrecajacy::~Pocisk_skrecajacy()
{
    //dtor
}

Pocisk_skrecajacy::Pocisk_skrecajacy(double x,double y)
{
    tekstura_pocisku.loadFromFile( "pocisk_01.png" );
    obrazek_pocisku.setTexture( tekstura_pocisku );
    szerokosc=tekstura_pocisku.getSize().x;
    wysokosc=tekstura_pocisku.getSize().y;
    this->x=x;
    this->y=y;

}


void Pocisk_skrecajacy::porusz(std::list<Przeciwnik*> listaPrzeciwnikow,int c){
    y=y-15;
    if(a==0){
        a=c;
    }
    if(a%4==1){
        x=x-5;
    }
    if(a%4==3){
        x=x+5;
    }
    if(a%4==2){
        ;
    }
}
