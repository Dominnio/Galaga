#ifndef PRZECIWNIK_STRZELAJACY_H
#define PRZECIWNIK_STRZELAJACY_H

#include <Przeciwnik.h>


class Przeciwnik_strzelajacy : public Przeciwnik
{
    public:
        Przeciwnik_strzelajacy();
        Przeciwnik_strzelajacy(double x,double y);
        void strzelaj(std::list<Pocisk*> &listaPociskow);
        virtual ~Przeciwnik_strzelajacy();
        sf::Clock zegar;
        sf::Time elapsed;
        sf::Time t1 = sf::milliseconds(500);
    protected:
    private:
};

#endif // PRZECIWNIK_STRZELAJACY_H
