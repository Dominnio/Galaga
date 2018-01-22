#include "Zderzenie.h"
#include <Okno.h>

Zderzenie::Zderzenie()
{
    buffer_zniszczenia.loadFromFile("dzwiek_zestrzelenia.wav");
    dzwiek_zniszczenia.setBuffer(buffer_zniszczenia);
    //ctor
}

Zderzenie::Zderzenie(double x,double y)
{
    this->x=x;
    this->y=y;

}

Zderzenie::~Zderzenie()
{
    //dtor
}

double Zderzenie::getX(){
    return x;
}

double Zderzenie::getY(){
    return y;
}
int Zderzenie::kolizja(double x1,double x2,double y1,double y2,double a,double b){
    if(a>x1 && a<x2 && b>y1 && b<y2){
        return 1;
    }
    return 0;
}

int Zderzenie::pocisk_przeszkoda_przeciwnik(std::list<Pocisk*> &listaPociskow, std::list<Przeciwnik*> &listaPrzeciwnikow, std::list<Przeszkoda*> &listaPrzeszkod, sf::Texture tekstura_pocisku,Samolot &samolot){
        bool x=false;

        for(std::list<Pocisk*>::iterator iter=listaPociskow.begin(); iter != listaPociskow.end();iter++){
            if((*iter)->getX()<=samolot.getX()+samolot.szerokosc && (*iter)->getX()>=samolot.getX()-(*iter)->szerokosc  && (*iter)->getY()<=samolot.getY()+samolot.wysokosc && (*iter)->getY()>=samolot.getY()-(*iter)->wysokosc){
                return 1;
            }
        }
        for(std::list<Pocisk*>::iterator iter=listaPociskow.begin(); iter != listaPociskow.end();){
            for(std::list<Przeciwnik*>::iterator iterr=listaPrzeciwnikow.begin(); iterr != listaPrzeciwnikow.end();){
                if((*iter)->getX()<=(*iterr)->getX()+(*iterr)->szerokosc && (*iter)->getX()>=(*iterr)->getX()-(*iter)->szerokosc  && (*iter)->getY()<=(*iterr)->getY()+(*iterr)->wysokosc && (*iter)->getY()>=(*iterr)->getY()-(*iter)->wysokosc){
                    x=true;
                    delete *iter;
                    delete *iterr;
                    iter=listaPociskow.erase(iter);
                    iterr=listaPrzeciwnikow.erase(iterr);
                    //iter=listaPociskow.begin();
                    //iterr=listaPrzeciwnikow.begin();
                    //dzwiek_zniszczenia.play();
                    samolot.zestrzelonych_przeciwnikow++;
                }
                if(x==true){
                    break;
                }
                else{
                    iterr++;
                }
            }
            if(x==true){
                x=false;
                ;
            }
            else{
                iter++;
            }
        }
        //samolot->collide(withWhat);
        for(std::list<Pocisk*>::iterator iter=listaPociskow.begin(); iter != listaPociskow.end();){
            for(std::list<Przeszkoda*>::iterator iterr=listaPrzeszkod.begin(); iterr != listaPrzeszkod.end();){
                if((*iter)->getX()<=(*iterr)->getX()+(*iterr)->szerokosc && (*iter)->getX()>=(*iterr)->getX()-(*iter)->szerokosc  && (*iter)->getY()<=(*iterr)->getY()+(*iterr)->wysokosc && (*iter)->getY()>=(*iterr)->getY()-(*iter)->wysokosc){
                    x=true;
                    delete *iter;
                    iter=listaPociskow.erase(iter);
                    //iter=listaPociskow.begin();
                }
                if(x==true){
                    break;
                }
                else{
                    iterr++;
                }
            }
            if(x==true){
                x=false;
                ;
            }
            else{
                iter++;
            }
         }
    return 0;
}
