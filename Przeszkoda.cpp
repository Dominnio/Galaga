#include "Przeszkoda.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Okno.h"

#include <cstdlib>
#include <ctime>

Przeszkoda::Przeszkoda()
{

}

Przeszkoda::~Przeszkoda()
{
    //std::cout<<"usunieto przeszkode" <<std::endl;
    //dtor
}

Przeszkoda::Przeszkoda(double x, double y, double z)
{
    //std::cout<<"stworzono przeszkode-------------------------------------------------------------" <<std::endl;
    if(z==-1){
        z=rand()%4;
    }
    else{
        ;
    }
    if(z==0){
        tekstura_przeszkody.loadFromFile( "przeszkoda_01.png" );
        obrazek_przeszkody.setTexture( tekstura_przeszkody );
        obrazek_przeszkody.setScale(0.5,0.5);
        szerokosc=tekstura_przeszkody.getSize().x*0.5;
        wysokosc=tekstura_przeszkody.getSize().y*0.5;
    }
    if(z==1){
        tekstura_przeszkody.loadFromFile( "przeszkoda_02.png" );
        obrazek_przeszkody.setTexture( tekstura_przeszkody );
        obrazek_przeszkody.setScale(0.5,0.5);
        szerokosc=tekstura_przeszkody.getSize().x*0.5;
        wysokosc=tekstura_przeszkody.getSize().y*0.5;
    }
    if(z==2 || z==3){
        tekstura_przeszkody.loadFromFile( "przeszkoda_03.png" );
        obrazek_przeszkody.setTexture( tekstura_przeszkody );
        obrazek_przeszkody.setScale(0.25,0.25);
        szerokosc=tekstura_przeszkody.getSize().x*0.25;
        wysokosc=tekstura_przeszkody.getSize().y*0.25;
    }
    this->x=x;
    this->y=y;

}

void Przeszkoda::porusz(){
    y=y+3;
}

double Przeszkoda::getX(){
    return x;
}

double Przeszkoda::getY(){
    return y;
}
