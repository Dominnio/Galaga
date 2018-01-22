#ifndef PRZESZKODA_H
#define PRZESZKODA_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>



class Przeszkoda
{
    public:
        Przeszkoda();
        Przeszkoda(double x, double y,double z=-1);
        sf::Sprite obrazek_przeszkody;
        sf::Texture tekstura_przeszkody;
        double szerokosc;
        double wysokosc;
        void porusz();
        double getX();
        double getY();
        virtual ~Przeszkoda();
    protected:
    private:
        double x;
        double y;
        double pierwotny_x=-1;      //useless
};

#endif // PRZESZKODA_H
