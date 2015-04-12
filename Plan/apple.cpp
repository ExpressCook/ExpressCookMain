#include "apple.h"

Apple::Apple():AbstractFood()
{
    loadForce = 50;
    defaultThick = 13;
}

int Apple::getType()
{
    return 1;
}

QString Apple::getName()
{
    return "apple";
}
