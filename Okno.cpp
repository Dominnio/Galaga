#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <list>
#include <cstddef>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <sstream>

#include "Samolot.h"
#include "Przeciwnik.h"
#include "Przeciwnik_strzelajacy.h"
#include "Przeciwnik_uciekajacy.h"
#include "Okno.h"
#include "Zderzenie.h"
#include "Przeszkoda.h"
#include "Pocisk.h"
#include "Pocisk_naprowadzany.h"
#include "Wyjatek_zapisu.h"



Okno::Okno(){ // załadowanie okna aplikacji, grafik, dźwięków, kształtów, tekstów, etc.
    okno_aplikacji.create(sf::VideoMode( 600, 700, 32 ), "GALAGA" );
    okno_aplikacji.setFramerateLimit(60);

    tekstura_tla.loadFromFile( "tlo_1.png" );
    obrazek_tla.setTexture( tekstura_tla);
    tekstura_tla_2.loadFromFile( "tlo_2.png" );
    obrazek_tla_2.setTexture( tekstura_tla_2);

    buffer_pocisku.loadFromFile("dzwiek_strzalu.wav");
    dzwiek_pocisku.setBuffer(buffer_pocisku);

    czcionka.loadFromFile("TrueNorthTexturesTwo3D-Bold.ttf");

    text_wyniku.setFont(czcionka);
    text_wyniku.setCharacterSize(20);
    text_wyniku.setString("Punkty:");

    text_zasad.setFont(czcionka);
    text_zasad.setString("Sterowanie samolotem : strzalki\nPojedynczy strzal : Spacja\nPocisk naprowadzany : Shift + Spacja\nWiazka pociskow : Ctrl + Spcaja\nZapis gry : S\nPauza : P\n\nUnikaj przeszkod i niszcz przeciwnikow.\n\nPowrot (P)");
    text_zasad.setCharacterSize(20);
    text_zasad.setPosition(75,80);

    text_pauzy.setFont(czcionka);
    text_pauzy.setString("   Wcisnij 'P', aby kontynuowac.");
    text_pauzy.setPosition(5,okno_aplikacji.getSize().y/2);

    text_statystyk.setFont(czcionka);
    text_statystyk.setCharacterSize(20);
    text_statystyk.setPosition(75,80);

    text_menu.setFont(czcionka);
    text_menu.setString("      Menu\nNowa gra (N)\nWczytaj gre (W)\nRekordy (R)\nZasady (Z)\nWyjsce (Esc)");
    text_menu.setPosition(okno_aplikacji.getSize().x/2-100,okno_aplikacji.getSize().y/4);

    text_punktow.setFont(czcionka);
    text_punktow.setCharacterSize(20);
    text_punktow.setPosition(text_punktow.getCharacterSize()*5,0);

    text_wygranej.setFont(czcionka);
    text_wygranej.setPosition(okno_aplikacji.getSize().x/2 - 150,okno_aplikacji.getSize().y/4);
    text_wygranej.setString("PRZESZEDLES LEVEL!\n  Statystyki (S)\n  Nowa gra (N)\n  Menu (M)\n");

    text_przegranej.setFont(czcionka);
    text_przegranej.setPosition(okno_aplikacji.getSize().x/2 - 120,okno_aplikacji.getSize().y/4);
    text_przegranej.setString("   PRZEGRANA!\nStatystyki (S)\nNowa gra (N)\nMenu (M)\n");

    linia.setSize(sf::Vector2f(okno_aplikacji.getSize().x, 25));
    linia.setPosition(0,0);
    linia.setFillColor(sf::Color::Blue);

    linia_biala.setSize(sf::Vector2f(okno_aplikacji.getSize().x, 1));
    linia_biala.setPosition(0,25);
    linia_biala.setFillColor(sf::Color::White);
    srand( time( NULL ) );
}

Okno::~Okno(){
    //dtor
}

void Okno::nowaGra(Samolot &samolot) // metoda zawierająca pętlę główną gry, rozpoczęcię tej pętli rozpoczyna nową rozgrywkę
{
    zegar.restart();
    zegar_2.restart();
    zegar_3.restart();
    elapsed=zegar.getElapsedTime();
    elapsed_2=zegar.getElapsedTime();
    elapsed_2=zegar.getElapsedTime();
    elapsed_pause_1=zegar.getElapsedTime();
    elapsed_pause_2=zegar.getElapsedTime();

    while (okno_aplikacji.isOpen()){
        policz_wynik(samolot);
        generuj_obiekty();
        obsluguj_klawisze(samolot);
        poruszaj_obiekty(samolot);
        if(zderzenie.pocisk_przeszkoda_przeciwnik(listaPociskow,listaPrzeciwnikow,listaPrzeszkod,tekstura_pocisku,samolot)==1){
            przegrana(samolot);
        }
        wynik(samolot);
        okno_aplikacji.display();
        okno_aplikacji.clear( sf::Color::Black );
        if(samolot.punkty>=10){
            wygrana(samolot);
        }
        std::cout.flush();
    }
}

void Okno::obsluguj_klawisze(Samolot &samolot){
     while( okno_aplikacji.pollEvent( zdarzenie ) ) // obsługa zdarzeń, czyli akcji jakie może wykonać użytkownik (wyjście, pauza, ruchy, strzał)
    {
        if( zdarzenie.type == sf::Event::Closed ) {
             okno_aplikacji.close();
          }
        if( zdarzenie.type == sf::Event::KeyPressed && zdarzenie.key.code == sf::Keyboard::Escape ) {
             okno_aplikacji.close();
        }
        if( zdarzenie.type == sf::Event::KeyPressed && zdarzenie.key.code == sf::Keyboard::S ) {
             zapis.zapisz_obiekty(listaPrzeciwnikow,listaPrzeszkod,samolot);
        }
        if( zdarzenie.type == sf::Event::KeyPressed && zdarzenie.key.code == sf::Keyboard::P ) {
            elapsed_pause_1 += zegar.getElapsedTime();
            elapsed_pause_2 += zegar_2.getElapsedTime();
            przerwa(samolot);
            zegar.restart();
            zegar_2.restart();
        }
        if( zdarzenie.type == sf::Event::KeyPressed && zdarzenie.key.code == sf::Keyboard::Left ) left=1;
        if( zdarzenie.type == sf::Event::KeyPressed && zdarzenie.key.code == sf::Keyboard::Up ) up=1;
        if( zdarzenie.type == sf::Event::KeyPressed && zdarzenie.key.code == sf::Keyboard::Down ) down=1;
        if( zdarzenie.type == sf::Event::KeyPressed && zdarzenie.key.code == sf::Keyboard::Right ) right=1;
        if( zdarzenie.type == sf::Event::KeyReleased && zdarzenie.key.code == sf::Keyboard::Left ) left=0;
        if( zdarzenie.type == sf::Event::KeyReleased && zdarzenie.key.code == sf::Keyboard::Up ) up=0;
        if( zdarzenie.type == sf::Event::KeyReleased && zdarzenie.key.code == sf::Keyboard::Down ) down=0;
        if( zdarzenie.type == sf::Event::KeyReleased && zdarzenie.key.code == sf::Keyboard::Right ) right=0;
        if( zdarzenie.type == sf::Event::KeyPressed && zdarzenie.key.code == sf::Keyboard::Space) space=1;
        if( zdarzenie.type == sf::Event::KeyReleased && zdarzenie.key.code == sf::Keyboard::Space ) space=0;
        if( zdarzenie.type == sf::Event::KeyPressed && zdarzenie.key.code == sf::Keyboard::LShift) lShift=1;
        if( zdarzenie.type == sf::Event::KeyReleased && zdarzenie.key.code == sf::Keyboard::LShift ) lShift=0;
        if( zdarzenie.type == sf::Event::KeyPressed && zdarzenie.key.code == sf::Keyboard::LControl) lControl=1;
        if( zdarzenie.type == sf::Event::KeyReleased && zdarzenie.key.code == sf::Keyboard::LControl ) lControl=0;
    }
    if(space==1){
        samolot.strzelaj(this);
    }
    if(up==1){
          if(samolot.getY()<=30){
             }
                 else{
                 samolot.poruszDoPrzodu();
            }
    }
    if(down==1){
        if(samolot.getY()>=okno_aplikacji.getSize().y-samolot.wysokosc){
            }
                else{
                 samolot.poruszDoTylu();
            }
    }
    if(right==1){
        if(samolot.getX()>=(okno_aplikacji.getSize().x-samolot.szerokosc)){
            }
            else{
                samolot.poruszWPrawo();
            }
    }
    if(left==1){
        if(samolot.getX()<=0){
            }
                else{
                 samolot.poruszWLewo();
            }
    }
}

//tutaj rozpoczyna się czesc odpowiedzialna za mechnizmy modelujace grą, np. dodawnaie przeciników, poruszanie przedmiotów, liczenie wyniku



void Okno::zeruj_ustawienia(){
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

void Okno::generuj_obiekty(){
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
            try{
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
            catch(const std::bad_alloc &)
            {
                std::cout<<"Brak pamieci, nie utworzono obiektu!";
                //throw Wyjatek_zapisu();
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
            try{
                listaPrzeszkod.push_back(new Przeszkoda(b,0));
            }
            catch(const std::bad_alloc &)
            {
                std::cout<<"Brak pamieci, nie utworzono obiektu!";
            }
         }

}

void Okno::poruszaj_obiekty(Samolot &samolot){
        int a=0;
        x=x+2;
        y=y+2;
        obrazek_tla.setPosition(0,x);
        obrazek_tla_2.setPosition(0,y);
        if(x>=700 && y<0) x=0; else if(x>=700) x=-700;
        if(y>=700 && x<0) y=0; else if(y>=700) y=-700;
        okno_aplikacji.draw(obrazek_tla);
        okno_aplikacji.draw(obrazek_tla_2);
        wyswietlSamolot(samolot);
        for(std::list<Pocisk*>::iterator iter=listaPociskow.begin(); iter != listaPociskow.end();){
            a++;
            if((*iter)->getY() <= 30){
                delete *iter;
                iter=listaPociskow.erase(iter);
                continue;
            }
            else{
                wyswietlPocisk(**iter);
                (*iter)->porusz(listaPrzeciwnikow,a%4);
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
                if(samolot.punkty>0) {samolot.punkty_stracone+=0.1;}
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

void Okno::policz_wynik(Samolot &samolot){
    if(samolot.ilosc_pociskow==0) {samolot.punkty=0;}
    else {samolot.punkty = 0.5 - samolot.punkty_stracone + samolot.zestrzelonych_przeciwnikow/samolot.ilosc_pociskow * samolot.zestrzelonych_przeciwnikow;}
}

// tutaj rozpoczyna się czesc odpowiedzialna za wyswietlanie odpowiednich grafik w oknie w danej sekcji gry (menu, zasady, rekordy)

void Okno::wyswietlPrzeszkode(Przeszkoda &przeszkoda){
    przeszkoda.obrazek_przeszkody.setPosition(przeszkoda.getX(),przeszkoda.getY());
    okno_aplikacji.draw(przeszkoda.obrazek_przeszkody);
}
void Okno::wyswietlSamolot(Samolot &samolot){
    samolot.obrazek_samolotu.setPosition(samolot.getX(), samolot.getY());
    okno_aplikacji.draw(samolot.obrazek_samolotu);
}
void Okno::wyswietlPocisk(Pocisk &pocisk){
    pocisk.obrazek_pocisku.setPosition(pocisk.getX(),pocisk.getY());
    okno_aplikacji.draw(pocisk.obrazek_pocisku);
}
void Okno::wyswietlPrzeciwnika(Przeciwnik &przeciwnik){
    przeciwnik.obrazek_przeciwnika.setPosition(przeciwnik.getX(), przeciwnik.getY());
    okno_aplikacji.draw(przeciwnik.obrazek_przeciwnika);
}

void Okno::wynik(Samolot &samolot){
    napis.str("");
    napis.clear();
    napis << samolot.punkty;
    napis_2=napis.str();
    text_punktow.setString(napis_2);
    okno_aplikacji.draw(linia);
    okno_aplikacji.draw(linia_biala);
    okno_aplikacji.draw(text_wyniku);
    okno_aplikacji.draw(text_punktow);
}

void Okno::przerwa(Samolot &samolot){
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
            if( !(zdarzenie.type == sf::Event::KeyPressed && zdarzenie.key.code == sf::Keyboard::P) ){
                okno_aplikacji.clear( sf::Color::Black);
                okno_aplikacji.draw(text_pauzy);
            }
            if( zdarzenie.type == sf::Event::KeyPressed && zdarzenie.key.code == sf::Keyboard::P ) {
                 return;
            }

        }
        okno_aplikacji.display();
    }
}

void Okno::zasady(Samolot &samolot){
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
            if( zdarzenie.type == sf::Event::KeyPressed && zdarzenie.key.code == sf::Keyboard::P ) {
                menu(samolot);
            }
        }
        okno_aplikacji.clear( sf::Color::Black  );
        okno_aplikacji.draw(text_zasad);
        okno_aplikacji.display();
    }

}

int Okno::menu(Samolot &samolot){
    zeruj_ustawienia();
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
            if( zdarzenie.type == sf::Event::KeyPressed && zdarzenie.key.code == sf::Keyboard::N ) {
                zeruj_ustawienia();
                samolot.ustaw_pozycje(okno_aplikacji.getSize().x/2 -(samolot.szerokosc)/(2), okno_aplikacji.getSize().y-samolot.wysokosc); //stworzenie samolotu
                nowaGra(samolot);
            }
            if( zdarzenie.type == sf::Event::KeyPressed && zdarzenie.key.code == sf::Keyboard::Z ) {
                zasady(samolot);
            }
            if( zdarzenie.type == sf::Event::KeyPressed && zdarzenie.key.code == sf::Keyboard::R ) {
                zapis.wczytaj_rekordy(okno_aplikacji);
            }
            if( zdarzenie.type == sf::Event::KeyPressed && zdarzenie.key.code == sf::Keyboard::W ) {
                zeruj_ustawienia();
                try{
                    if (zapis.wczytaj(listaPrzeciwnikow,listaPrzeszkod,samolot,okno_aplikacji)==1){
                        nowaGra(samolot);
                    }
                }
                catch (Wyjatek_zapisu &)
                    std::cout<<"Blad\n";
                }
            }
        }
        okno_aplikacji.clear( sf::Color::Black );
        okno_aplikacji.draw(text_menu);
        okno_aplikacji.display();
    }
    return 0;
}

void Okno::statystyki(Samolot &samolot){
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
            if( zdarzenie.type == sf::Event::KeyPressed && zdarzenie.key.code == sf::Keyboard::P ) {
                return;
            }
        }
        okno_aplikacji.clear( sf::Color::Black );
        napis.str("");
        napis.clear();
        if(samolot.ilosc_pociskow ==0 || samolot.zestrzelonych_przeciwnikow==0 ){
            napis << "Zestrzelonych przeciwnikow : " << samolot.zestrzelonych_przeciwnikow <<"\n" << "Liczba strzalow : " << samolot.ilosc_strzalow << "\nUzytej amunicji : " << samolot.ilosc_pociskow << "\n" << "Skutecznosc : " << "0" << " %";
            napis<<"\nPunkty : ";
            samolot.punkty=0;
            napis<< samolot.punkty;
        }
        else{
            napis << "Zestrzelonych przeciwnikow : " << samolot.zestrzelonych_przeciwnikow <<"\n" << "Liczba strzalow : " << samolot.ilosc_strzalow << "\nUzytej amunicji : " << samolot.ilosc_pociskow<< "\n" << "Skutecznosc : " << 100*samolot.zestrzelonych_przeciwnikow/samolot.ilosc_pociskow << " %";
            napis<<"\nPunkty : ";
            samolot.punkty=0.5+samolot.zestrzelonych_przeciwnikow/samolot.ilosc_pociskow*samolot.zestrzelonych_przeciwnikow-samolot.punkty_stracone;
            if(samolot.punkty < 0) samolot.punkty=0;
            napis<< samolot.punkty;
            }
        napis << "\n\nPowrot (P)";
        napis_2=napis.str();
        text_statystyk.setString(napis_2);
        okno_aplikacji.draw(text_statystyk);

        okno_aplikacji.display();
    }
}
void Okno::wygrana(Samolot &samolot){
    if(zapis.zapisz_wynik(samolot.punkty)==1){
        text_przegranej.setString("NOWY REKORD !!!\nStatystyki (S)\nNowa gra (N)\nMenu (M)\n");
    }
    //zeruj_ustawienia(samolot);
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
            if( zdarzenie.type == sf::Event::KeyPressed && zdarzenie.key.code == sf::Keyboard::S ) {
                statystyki(samolot);
            }
            if( zdarzenie.type == sf::Event::KeyPressed && zdarzenie.key.code == sf::Keyboard::N ) {
                zeruj_ustawienia();
                samolot.ustaw_pozycje(okno_aplikacji.getSize().x/2 -(samolot.szerokosc)/(2), okno_aplikacji.getSize().y-samolot.wysokosc); //stworzenie samolotu
                nowaGra(samolot);
            }
            if( zdarzenie.type == sf::Event::KeyPressed && zdarzenie.key.code == sf::Keyboard::M ) {
                menu(samolot);
            }
        }
        okno_aplikacji.clear( sf::Color::Green  );
        okno_aplikacji.draw(text_wygranej);
        okno_aplikacji.display();
    }
}



void Okno::przegrana(Samolot &samolot){
    if(zapis.zapisz_wynik(samolot.punkty)==1){
        text_przegranej.setString("NOWY REKORD !!!\nStatystyki (S)\nNowa gra (N)\nMenu (M)\n");
    }
    //zeruj_ustawienia(samolot);
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
            if( zdarzenie.type == sf::Event::KeyPressed && zdarzenie.key.code == sf::Keyboard::S ) {
                statystyki(samolot);
            }
            if( zdarzenie.type == sf::Event::KeyPressed && zdarzenie.key.code == sf::Keyboard::N ) {
                zeruj_ustawienia();
                samolot.ustaw_pozycje(okno_aplikacji.getSize().x/2 -(samolot.szerokosc)/(2), okno_aplikacji.getSize().y-samolot.wysokosc); //stworzenie samolotu
                nowaGra(samolot);
            }
            if( zdarzenie.type == sf::Event::KeyPressed && zdarzenie.key.code == sf::Keyboard::M ) {
                menu(samolot);
            }
        }
        okno_aplikacji.clear( sf::Color::Red  );
        okno_aplikacji.draw(text_przegranej);
        okno_aplikacji.display();
    }
}

