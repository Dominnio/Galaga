#ifndef PRZECIWNIK_UCIEKAJACY_H
#define PRZECIWNIK_UCIEKAJACY_H

#include <Przeciwnik.h>
#include <Przeszkoda.h>

class Przeciwnik_uciekajacy : public Przeciwnik
{
    public:
        Przeciwnik_uciekajacy();
        Przeciwnik_uciekajacy(double x,double y);
        virtual ~Przeciwnik_uciekajacy();
        void porusz(std::list<Pocisk*> listaPociskow,std::list<Przeszkoda*> listaPrzeszkod);    // porusza przeciwnikem tak aby uciekał przed nadlatującym pociskiem
    protected:
    private:
};

#endif // PRZECIWNIK_UCIEKAJACY_H
