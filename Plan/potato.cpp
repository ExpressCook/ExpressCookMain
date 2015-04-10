#include "potato.h"

Potato::Potato():AbstractFood()
{
    loadForce = 70;
    defaultThick = 20;
}

int Potato::getType()
{
    return 0;
}

QString Potato::getName()
{
    return "potato";
}
