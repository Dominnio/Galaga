#include "Mechanizm.h"

Mechanizm::Mechanizm()
{
    //ctor
}

Mechanizm::~Mechanizm()
{
    //dtor
}


void Mechanizm::zeruj_ustawienia(Samolot &samolot){
    for(std::list<Pocisk*>::iterator iter=listaPociskow.begin(); iter != listaPociskow.end(); iter++){
        delete *iter;
    }
    for(std::list<Przeszkoda*>::iterator iter=listaPrzeszkod.begin(); iter != listaPrzeszkod.end(); iter++){
        delete *iter;
    }
    for(std::list<Przeciwnik*>::iterator iter=listaPrzeciwnikow.begin(); iter != listaPrzeciwnikow.end(); iter++){
        delete *iter;
    }
    listaPociskow.clear();
    listaPrzeszkod.clear();
    listaPrzeciwnikow.clear();
    left=0;
    right=0;
    up=0;
    down=0;
    space=0;
    lShift=0;
    lControl=0;
    elapsed = zegar.getElapsedTime();
    elapsed_2 = zegar.getElapsedTime();
    elapsed_3 = zegar.getElapsedTime();
    elapsed_pause_1 = zegar.getElapsedTime();
    elapsed_pause_2 = zegar.getElapsedTime();
    samolot.ilosc_pociskow=0;
    samolot.zestrzelonych_przeciwnikow=0;
    samolot.punkty=0;
    samolot.punkty_stracone=0;
    samolot.ilosc_strzalow=0;

}

void Mechanizm::generuj_obiekty(){
        double a=0,b=0,c=0;
        bool x=false;
        elapsed = zegar.getElapsedTime();
        elapsed_2 = zegar_2.getElapsedTime();

        if(elapsed + elapsed_pause_1 > t1 ){
            zegar.restart();
            elapsed_pause_1=sf::seconds(0);
            a=std::rand()%(okno_aplikacji.getSize().x-45);
            while(x!=true){
                x=true;
                for(std::list<Przeszkoda*>::iterator iter=listaPrzeszkod.begin(); iter != listaPrzeszkod.end();){
                    if((a < ((*iter)->getX()+(*iter)->szerokosc)) && (a > ((*iter)->getX()-45))){
                        a=std::rand()%(okno_aplikacji.getSize().x-45);
                        iter=listaPrzeszkod.begin();
                        continue;
                    }
                    iter++;
                }
                for(std::list<Przeciwnik*>::iterator iter=listaPrzeciwnikow.begin(); iter != listaPrzeciwnikow.end();){
                    if((a < ((*iter)->getX()+(*iter)->szerokosc)) && (a > ((*iter)->getX()-45))){
                        x=false;
                        a=std::rand()%(okno_aplikacji.getSize().x-45);
                        iter=listaPrzeciwnikow.begin();
                        continue;
                    }
                    iter++;
                }
            }
            c=rand()%3;
            if(c==0){
                listaPrzeciwnikow.push_back(new Przeciwnik_strzelajacy(a,0));
            }
            if(c==1){
                listaPrzeciwnikow.push_back(new Przeciwnik(a,0));
            }
            if(c==2){
                listaPrzeciwnikow.push_back(new Przeciwnik_uciekajacy(a,0));
            }
         }
         if(elapsed_2 + elapsed_pause_2 > t2){
            zegar_2.restart();
            elapsed_pause_2=sf::seconds(0);
            b=std::rand()%(okno_aplikacji.getSize().x-100);
            for(std::list<Przeciwnik*>::iterator iter=listaPrzeciwnikow.begin(); iter != listaPrzeciwnikow.end();){
                if((b<(*iter)->getX()+(*iter)->szerokosc) && (b>(*iter)->getX()-100)){
                    b=std::rand()%(okno_aplikacji.getSize().x-100);
                    iter=listaPrzeciwnikow.begin();
                    continue;
                }
                iter++;
            }
            listaPrzeszkod.push_back(new Przeszkoda(b,0));
         }

}

void Mechanizm::poruszaj_obiekty(Samolot &samolot){
        wyswietlSamolot(samolot); // wyświetlenie samolotu
        for(std::list<Pocisk*>::iterator iter=listaPociskow.begin(); iter != listaPociskow.end();){
            if((*iter)->getY() <= 30){
                delete *iter;
                iter=listaPociskow.erase(iter);
                continue;
            }
            else{
                wyswietlPocisk(**iter);
                (*iter)->porusz(listaPrzeciwnikow);
            }
            iter++;
        }
        for(std::list<Przeszkoda*>::iterator iter=listaPrzeszkod.begin(); iter != listaPrzeszkod.end();){
            if((*iter)->getY() >=samolot.getY()-(*iter)->wysokosc && (*iter)->getY() <=samolot.getY() + samolot.wysokosc && (*iter)->getX() >= samolot.getX() - (*iter)->szerokosc && (*iter)->getX()  <= samolot.getX() + samolot.szerokosc){
                przegrana(samolot);
            }
            if((*iter)->getY() > okno_aplikacji.getSize().y){
                delete *iter;
                iter=listaPrzeszkod.erase(iter);
                continue;
            }
            else{
                wyswietlPrzeszkode(**iter);
                (*iter)->porusz();
            }
            iter++;
        }
        for(std::list<Przeciwnik*>::iterator iter=listaPrzeciwnikow.begin(); iter != listaPrzeciwnikow.end();){
            if((*iter)->getY() >=samolot.getY()-(*iter)->wysokosc && (*iter)->getY() <=samolot.getY() + samolot.wysokosc && (*iter)->getX() >= samolot.getX() - (*iter)->szerokosc && (*iter)->getX()  <= samolot.getX() + samolot.szerokosc){
                przegrana(samolot);
            }
            if((*iter)->getY() > okno_aplikacji.getSize().y){
                delete *iter;
                iter=listaPrzeciwnikow.erase(iter);
                if(samolot.punkty>0) {samolot.punkty_stracone+=0.5;}
                continue;
            }
            else{
                (*iter)->strzelaj(listaPociskow);
                wyswietlPrzeciwnika(**iter);
                (*iter)->porusz(listaPociskow,listaPrzeszkod);
            }
            iter++;
        }
}

void Mechanizm::policz_wynik(Samolot &samolot){
    if(samolot.ilosc_pociskow==0) {samolot.punkty=0;}
    else {samolot.punkty = 0.5 - samolot.punkty_stracone + samolot.zestrzelonych_przeciwnikow/samolot.ilosc_pociskow * samolot.zestrzelonych_przeciwnikow;}
}
