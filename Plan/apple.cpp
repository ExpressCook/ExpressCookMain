#include "apple.h"

Apple::Apple():AbstractFood()
{
    loadForce = 50;
    defaultThick = 18;
}

int Apple::getType()
{
    return 1;
}

QString Apple::getName()
{
    return "apple";
}
