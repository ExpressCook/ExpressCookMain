#include "potato.h"

Potato::Potato():AbstractFood()
{
    loadForce = 70;
    defaultThick = 10;
}

int Potato::getType()
{
    return 0;
}

QString Potato::getName()
{
    return "potato";
}
