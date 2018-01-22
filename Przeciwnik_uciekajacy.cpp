#include "Przeciwnik_uciekajacy.h"
#include "Pocisk.h"

Przeciwnik_uciekajacy::Przeciwnik_uciekajacy()
{
    //ctor
}

Przeciwnik_uciekajacy::~Przeciwnik_uciekajacy()
{
    //dtor
}

Przeciwnik_uciekajacy::Przeciwnik_uciekajacy(double x,double y)
{
    tekstura_przeciwnika.loadFromFile( "przeciwnik_03.png" );
    obrazek_przeciwnika.setTexture( tekstura_przeciwnika );
    //obrazek_przeciwnika.setScale(0.5,0.5);
    szerokosc=tekstura_przeciwnika.getSize().x;
    wysokosc=tekstura_przeciwnika.getSize().y;
    this->x=x;
    this->y=y;
}

void Przeciwnik_uciekajacy::porusz(std::list<Pocisk*> listaPociskow,std::list<Przeszkoda*> listaPrzeszkod){
    y=y+4.5;
    if(x>0 && x<600-46){
        for(std::list<Pocisk*>::iterator iter=listaPociskow.begin(); iter != listaPociskow.end();iter++){
            if(!((*iter)->getY()>y+wysokosc)){
                while((*iter)->getX()+(*iter)->szerokosc>x && (*iter)->getX() < x + szerokosc){
                    if((*iter)->getX()>x+szerokosc/2-(*iter)->szerokosc/2){
                    x=x-0.2;
                    }else{
                    x=x+0.2;
                    }
                }
            }else{
                ;
            }
        }
    }
}
