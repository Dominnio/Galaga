#ifndef POCISK_NAPROWADZANY_H
#define POCISK_NAPROWADZANY_H

#include <Pocisk.h>


class Pocisk_naprowadzany : public Pocisk
{
    public:
        Pocisk_naprowadzany();
        Pocisk_naprowadzany(double x,double y);
        void porusz(std::list<Przeciwnik*> listaPrzeciwnikow, int a);   //porusza pociskiem, tak aby nadlatywał do najbliższego przeciwnika
        virtual ~Pocisk_naprowadzany();
    protected:
    private:
};

#endif // POCISK_NAPROWADZANY_H
