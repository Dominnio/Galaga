#ifndef POCISK_PRZECIWNIKA_H
#define POCISK_PRZECIWNIKA_H

#include <Pocisk.h>


class Pocisk_przeciwnika : public Pocisk
{
    public:
        Pocisk_przeciwnika();
        virtual ~Pocisk_przeciwnika();
        Pocisk_przeciwnika(double x,double y);
        void porusz(std::list<Przeciwnik*> listaPrzeciwnikow, int a);       //porusza pociskiem w dół
    protected:
    private:
};

#endif // POCISK_PRZECIWNIKA_H
