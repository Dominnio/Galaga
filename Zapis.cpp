#include "Zapis.h"

#include <cstddef>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <ostream>


#include "Samolot.h"
#include "Przeciwnik.h"
#include "Przeciwnik_strzelajacy.h"
#include "Przeciwnik_uciekajacy.h"
#include "Przeszkoda.h"
#include "Okno.h"
#include "Wyjatek_zapisu.h"



Zapis::Zapis()
{
    czcionka.loadFromFile("TrueNorthTexturesTwo3D-Bold.ttf");
    text_zapisu.setFont(czcionka);
    czcionka.loadFromFile("TrueNorthTexturesTwo3D-Bold.ttf");
    text_rekordow.setFont(czcionka);
    //ctor
}

Zapis::~Zapis()
{
    //dtor
}

int Zapis::zapisz_wynik(int punkty){
    std::fstream plik;
    int punkty_razem;
    double rekord;
    double x;

    try{
        plik.open( "wyniki_rekordy", std::ios::app | std::ios::in);
        if( plik.good() != true ){
            throw 0;
        }
    }
    catch(...){
        std::cout<<"Nie udalo sie zapisac rekordu";
        plik.close();
    }

    plik>>punkty_razem;
    plik>>rekord;
    plik.close();
    punkty_razem += punkty;

    try{
        plik.open( "wyniki_rekordy", std::ios::trunc | std::ios::out);
        if( plik.good() != true ){
            throw 0;
        }
    }
    catch(...){
        std::cout<<"Nie udalo sie zapisac rekordu";
        plik.close();
    }

    plik << punkty_razem;
    plik << "\n";
    if (punkty > rekord){
        plik<<punkty;
        x=1;
    }
    else{
        plik<<rekord;
        x=0;
    }
    plik.close();
    return x;
}

void Zapis::wczytaj_rekordy(sf::RenderWindow &okno_aplikacji){
    std::fstream plik;

    try{
        plik.open( "wyniki_rekordy", std::ios::in);
        if( plik.is_open() != true ){
            throw 0;
        }
    }
    catch(...){
        std::cout<<"Nie udalo sie wczytac rekordu\n";
        plik.close();
        return;
    }

    std::string dane_1;
    std::string dane_2;
    std::string napis_wyjsciowy;
    while(plik.fail()!=true){
        getline( plik, dane_1 );
        getline( plik, dane_2 );
        napis_wyjsciowy = "Razem zdobytych punktow : " + dane_1;
        getline( plik, dane_2 );
        napis_wyjsciowy = napis_wyjsciowy + "\nNajlepszy wynik : " + dane_2;
    }
    plik.close();
    napis_wyjsciowy = "Rekordy :\n" + napis_wyjsciowy + "\n\nPowrot (P)";
    text_rekordow.setString(napis_wyjsciowy);
    text_rekordow.setCharacterSize(20);
    text_rekordow.setPosition(75,80);
    while(okno_aplikacji.isOpen()){
    sf::Event zdarzenie;
        while( okno_aplikacji.pollEvent( zdarzenie ) )
        {
            if( zdarzenie.type == sf::Event::Closed ) {
                 okno_aplikacji.close();
            }
            if( zdarzenie.type == sf::Event::KeyPressed && zdarzenie.key.code == sf::Keyboard::Escape ) {
                 okno_aplikacji.close();
            }
            if( zdarzenie.type == sf::Event::KeyPressed && zdarzenie.key.code == sf::Keyboard::P) {
                 return;
            }
        }
        okno_aplikacji.clear( sf::Color::Black);
        okno_aplikacji.draw(text_rekordow);
        okno_aplikacji.display();
    }
    plik.close();
}

void Zapis::zapisz_obiekty(std::list<Przeciwnik*> &listaPrzeciwnikow, std::list<Przeszkoda*> &listaPrzeszkod,Samolot samolot){
    time_t czas;
    struct tm * data;
    char bufor[ 20 ];
    time( & czas ); // ile sekund uplynelo od 1 stycznia 1970 roku (wynik zapisuje w czas)
    data = localtime( & czas ); // przelicza czas na postac struktury tm i zapisuje do data
    strftime( bufor, 20, "%d/%m/%Y %H:%M:%S", data ); // ustawia bufor
    std::fstream plik;

    try{
        plik.open( "zapisane_gry", std::ios::out | std::ios::trunc );
        if( plik.is_open() != true ){
            throw 0;
        }
    }
    catch(...){
        std::cout<<"Nie udalo sie zapisac gry\n";
        plik.close();
        return;
    }
    // zapisuje do pliku tekstowego wszystkie dane z gry (położenia obiektów, punkty, etc), wszystko w określonym porządku
    plik << "#";
    plik << bufor;
    plik << "#\n\n";
    plik<<samolot.getX();
    plik<<"\t";
    plik<<samolot.getY();
    plik<<"\n";
    plik << samolot.punkty;
    plik << "\n";
    plik << samolot.zestrzelonych_przeciwnikow;
    plik << "\n";
    plik << samolot.ilosc_pociskow;
    plik << "\n";
    plik << samolot.punkty_stracone;
    plik << "\n";
    plik << samolot.ilosc_strzalow;
    plik << "\n";
    for(std::list<Przeciwnik*>::iterator iter=listaPrzeciwnikow.begin(); iter != listaPrzeciwnikow.end(); iter++){
        plik<<(*iter)->getX();
        plik<<"\t";
        plik<<(*iter)->getY();
        plik<<"\t";
        plik<<(*iter)->szerokosc;
        plik<<"\n";
    }
    plik<<"-1\n";
    for(std::list<Przeszkoda*>::iterator iter=listaPrzeszkod.begin(); iter != listaPrzeszkod.end(); iter++){
        plik<<(*iter)->getX();
        plik<<"\t";
        plik<<(*iter)->getY();
        plik<<"\t";
        plik<<(*iter)->szerokosc;
        plik<<"\n";
    }
    plik<<"-2\n";
    plik<<"\n\n";
    plik.close();
}

int Zapis::wczytaj(std::list<Przeciwnik*> &listaPrzeciwnikow, std::list<Przeszkoda*> &listaPrzeszkod,Samolot &samolot,sf::RenderWindow &okno_aplikacji){
    double x,y,z;
    std::fstream plik;
    try{
        plik.open( "zapisane_gryy", std::ios::in);
        if( plik.is_open() != true ){
            throw 0;
        }
    }
    catch(...){
        plik.close();
        throw Wyjatek_zapisu();
    }
    std::string dane;
    std::string napis_wyjsciowy;
    //wczytanie kiedy została zapisana
    while(plik.fail()!=true){
        getline( plik, dane );
        if(dane[0]=='#'){
            napis_wyjsciowy=napis_wyjsciowy+dane;
            napis_wyjsciowy=napis_wyjsciowy+"\n";
        }
    }
    plik.close();
    napis_wyjsciowy = "Zapisane gry :\n" + napis_wyjsciowy + "\nPowrot (P)";
    text_zapisu.setString(napis_wyjsciowy);
    text_zapisu.setCharacterSize(20);
    text_zapisu.setPosition(75,80);
    while(okno_aplikacji.isOpen()){
    sf::Event zdarzenie;
        while( okno_aplikacji.pollEvent( zdarzenie ) )
        {
            if( zdarzenie.type == sf::Event::Closed ) {
                 okno_aplikacji.close();
            }
            if( zdarzenie.type == sf::Event::KeyPressed && zdarzenie.key.code == sf::Keyboard::Escape ) {
                 okno_aplikacji.close();
            }
            if( zdarzenie.type == sf::Event::KeyPressed && zdarzenie.key.code == sf::Keyboard::P) {
                 return 0;
            }
            if( zdarzenie.type == sf::Event::KeyPressed && zdarzenie.key.code == sf::Keyboard::Num1) {
                plik.open( "zapisane_gry", std::ios::in);
                getline( plik, dane );
                plik>>x;
                plik>>y;
                samolot.ustaw_pozycje(x,y);
                plik>>samolot.punkty;
                plik>>samolot.zestrzelonych_przeciwnikow;
                plik>>samolot.ilosc_pociskow;
                plik>>samolot.punkty_stracone;
                plik>>samolot.ilosc_strzalow;
                plik>>x;
                while(x!=-1){
                    plik>>y;
                    plik>>z;
                    if(z==45) listaPrzeciwnikow.push_back(new Przeciwnik(x,y));
                    if(z==46) listaPrzeciwnikow.push_back(new Przeciwnik_strzelajacy(x,y));
                    if(z==44) listaPrzeciwnikow.push_back(new Przeciwnik_uciekajacy(x,y));
                    plik>>x;
                }
                plik>>x;
                while(x!=-2){
                    plik>>y;
                    plik>>z;
                    if(z==45) z=2;
                    if(z==90) z=1;
                    if(z==100) z=0;
                    listaPrzeszkod.push_back(new Przeszkoda(x,y,z));
                    plik>>x;
                }
                plik.close();
                return 1;
            }
        }
        okno_aplikacji.clear( sf::Color::Black);
        okno_aplikacji.draw(text_zapisu);
        okno_aplikacji.display();
    }
    plik.close();
    return 0;
}
