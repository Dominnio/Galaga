#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <list>
#include <iostream>
#include "Samolot.h"
#include "Pocisk_naprowadzany.h"
#include "Pocisk_skrecajacy.h"

#include "Okno.h"

Samolot::Samolot()
{
    x=0;
    y=0;
    tekstura_samolotu.loadFromFile( "samolot_gracza.png" );
    obrazek_samolotu.setTexture( tekstura_samolotu );
    //obrazek_samolotu.setScale(0.15,0.15);
    szerokosc=tekstura_samolotu.getSize().x;
    wysokosc=tekstura_samolotu.getSize().y;
    this->x=300-szerokosc/2;
    this->y=700-wysokosc;
}

Samolot::Samolot(double x,double y){
    //std::cout<<"stworzono samolot" <<std::endl;
    tekstura_samolotu.loadFromFile( "samolot_gracza.png" );
    obrazek_samolotu.setTexture( tekstura_samolotu );
    //obrazek_samolotu.setScale(0.15,0.15);
    szerokosc=tekstura_samolotu.getSize().x;
    wysokosc=tekstura_samolotu.getSize().y;
    this->x=300-szerokosc/2;
    this->y=700-wysokosc;
}
void Samolot::ustaw_pozycje(double x,double y){
    this->x=x;
    this->y=y;
}

Samolot::~Samolot()
{
    //dtor
}

void Samolot::strzelaj(Okno *okno){
    try{
        if(okno->lShift==0){
            if(okno->lControl==0){
                okno->elapsed_3=okno->zegar_3.getElapsedTime();
                    if(okno->elapsed_3 < okno->t3){
                        ;
                    } else{
                        okno->zegar_3.restart();
                        //dzwiek_pocisku.play();
                        ilosc_strzalow++;
                        ilosc_pociskow++;
                        okno->listaPociskow.push_front(new Pocisk(getX() +((szerokosc)/(2))-10,getY()-40));
                    }
            }else{
                okno->elapsed_3=okno->zegar_3.getElapsedTime();
                    if(okno->elapsed_3 < okno->t3){
                        ;
                    } else{
                        okno->zegar_3.restart();
                        //dzwiek_pocisku.play();
                        ilosc_pociskow+=3;
                        ilosc_strzalow++;
                        okno->listaPociskow.push_front(new Pocisk_skrecajacy(getX() +((szerokosc)/(2))-10,getY()-40));
                        okno->listaPociskow.push_front(new Pocisk_skrecajacy(getX() +((szerokosc)/(2))-10,getY()-40));
                        okno->listaPociskow.push_front(new Pocisk_skrecajacy(getX() +((szerokosc)/(2))-10,getY()-40));
                    }
            }
        }else{
        okno->elapsed_3=okno->zegar_3.getElapsedTime();
            if(okno->elapsed_3 < okno->t3){
                ;
            } else{
                okno->zegar_3.restart();
                //okno->dzwiek_pocisku.play();
                ilosc_strzalow++;
                ilosc_pociskow+=3;
                okno->listaPociskow.push_front(new Pocisk_naprowadzany(getX() +((szerokosc)/(2))-10,getY()-40));
            }
        }
    }
    catch(const std::bad_alloc &)
    {
        std::cout<<"Brak pamieci, nie utworzono obiektu!";
    }
}

void Samolot::poruszWLewo()
{
    x=x-7.5;
}

void Samolot::poruszWPrawo()
{
    x=x+7.5;

}
void Samolot::poruszDoPrzodu()
{
    y = y - 7.5;
}

void Samolot::poruszDoTylu()
{
    y = y + 7.5;
}

double Samolot::getX() const {
    return x;
}

double Samolot::getY()  const{
    return y;
}

