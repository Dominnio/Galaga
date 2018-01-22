#include "Komunikacja.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <Okno.h>
#include<iostream>

Komunikacja::Komunikacja()
{
    //ctor
}

Komunikacja::~Komunikacja()
{
    //dtor
}

void Komunikacja::wynik(sf::RenderWindow &okno_aplikacji){
    sf::Font font;
    font.loadFromFile("arial.ttf");

    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(20);
    text.setString("Wynik:");

    sf::RectangleShape line(sf::Vector2f(okno_aplikacji.getSize().x, 1));
    line.setPosition(0,25);

    okno_aplikacji.draw(text);
    okno_aplikacji.draw(line);
}


void Komunikacja::przerwa(sf::RenderWindow &okno_aplikacji){

    sf::Text text;
    sf::Font font;
    font.loadFromFile("arial.ttf");
    text.setFont(font);
    text.setString("Wcisnij 'P', aby kontynuowac.");
    text.setPosition(0,okno_aplikacji.getSize().y/2);
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
                okno_aplikacji.clear( sf::Color::Blue );
                okno_aplikacji.draw(text);
            }
            if( zdarzenie.type == sf::Event::KeyPressed && zdarzenie.key.code == sf::Keyboard::P ) {
                 return;
            }

        }
        okno_aplikacji.display();
    }

}

void Komunikacja::menu(){

}

void Komunikacja::przegrana(){

}
