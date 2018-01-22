#ifndef KOMUNIKACJA_H
#define KOMUNIKACJA_H

#include <Okno.h>


class Komunikacja
{
    public:
        void wynik(sf::RenderWindow &okno_aplikacji);
        void przerwa(sf::RenderWindow &okno_aplikacji);
        void menu();
        void przegrana();
        Komunikacja();
        virtual ~Komunikacja();
    protected:
    private:
};

#endif // KOMUNIKACJA_H
