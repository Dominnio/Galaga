#ifndef OKNO_H
#define OKNO_H
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Samolot.h"
#include "Przeciwnik.h"
#include "Okno.h"
#include "Zderzenie.h"
#include "Przeszkoda.h"
#include "Pocisk.h"
#include "Zapis.h"

#include <iostream>
#include <list>
#include <sstream>



class Okno
{
    public:
        sf::RenderWindow okno_aplikacji;
        Samolot samolot;
        void nowaGra(Samolot &samolot);
        int menu(Samolot &samolot);
        bool lControl=0;
        bool lShift=0;
        sf::Time elapsed_3;
        sf::Clock zegar_3;
        sf::Time t3 = sf::milliseconds(150);
        std::list<Pocisk*> listaPociskow;
        sf::Sound dzwiek_pocisku;
        Okno();
        virtual ~Okno();
    protected:
    private:

        void wynik(Samolot &samolot);                           // wyświetla wynik i potrzebną otoczkę (np. linię oddzielającą wynik od pola gry)
      /*
      */
        void policz_wynik(Samolot &samolot);                    // liczy wynik
        void przerwa(Samolot &samolot);                         // obsługuje pauzę podczas rozgrywki (wyświetla odpowiedni tekst i "czeka na akcję")
        void wygrana(Samolot &samolot);                         // obsługuje wygraną (wyświetla odpowiedni tekst i "czeka na akcję")
        void przegrana(Samolot &samolot);                       // obsługuje przegraną ---------------------||----------------------
        void zeruj_ustawienia();                                // zeruje ustawienia przed nową grą
        void statystyki(Samolot &samolot);                      // wyświetla statystyki
        void zasady(Samolot &samolot);                          // wyświetla zasady
        void obsluguj_klawisze(Samolot &samolot);               // funkcja sprawdza czy użytkonik coś wcisnął podczas rozgrywki
        void wyswietlSamolot(Samolot &samolot);                 // poniżej funkcje odpowiedzialne za wyświetlenie jednej, odpowiedniej, grafiki
        void wyswietlPocisk(Pocisk &pocisk);
        void wyswietlPrzeszkode(Przeszkoda &przeszkoda);
        void wyswietlPrzeciwnika(Przeciwnik &przeciwnik);
        void poruszaj_obiekty(Samolot &samolot);                //porusza wszystkim co powinno się poruszyć (łącznie z tłem)
        void generuj_obiekty();                                 //generuje nowych przeciwników i przeszkody co odpowiedni czas

        sf::Event zdarzenie;

        sf::SoundBuffer buffer_pocisku;

        sf::Sprite obrazek_pocisku;
        sf::Texture tekstura_pocisku;

        sf::Sprite obrazek_tla;
        sf::Sprite obrazek_tla_2;
        sf::Texture tekstura_tla;
        sf::Texture tekstura_tla_2;

        sf::Font czcionka;

        sf::Text text_wyniku;
        sf::Text text_pauzy;
        sf::Text text_zasad;
        sf::Text text_menu;
        sf::Text text_przegranej;
        sf::Text text_punktow;
        sf::Text text_statystyk;
        sf::Text text_wygranej;

        sf::Clock zegar;
        sf::Clock zegar_2;
        sf::Time elapsed;
        sf::Time elapsed_2;

        sf::Time elapsed_pause_1 = sf::seconds(0);
        sf::Time elapsed_pause_2 = sf::seconds(0);
        sf::Time t1 = sf::milliseconds(900);
        sf::Time t2 = sf::milliseconds(1500);

        std::ostringstream napis;
        std::string napis_2;
        std::list<Przeciwnik*> listaPrzeciwnikow;
        std::list<Przeszkoda*> listaPrzeszkod;

        sf::RectangleShape linia;
        sf::RectangleShape linia_biala;

        Zderzenie zderzenie;
        Zapis zapis;

        bool up=0;
        bool down=0;
        bool right=0;
        bool left=0;
        bool space=0;;
        bool a=0;
        bool g=0;
        bool l=0;

        double x=0,y=-700;
};

#endif // OKNO_H
