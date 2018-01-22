#ifndef POCISK_SKRECAJACY_H
#define POCISK_SKRECAJACY_H

#include <Pocisk.h>

class Pocisk_skrecajacy : public Pocisk
{
    public:
        Pocisk_skrecajacy();
        Pocisk_skrecajacy(double x,double y);
        void porusz(std::list<Przeciwnik*> listaPrzeciwnikow,int a);        //porusza pociskiem w prawo, w lewo lub prosto w zależności od zmiennej a
        virtual ~Pocisk_skrecajacy();
    protected:
    private:
        int a=0;
};

#endif // POCISK_SKRECAJACY_H
