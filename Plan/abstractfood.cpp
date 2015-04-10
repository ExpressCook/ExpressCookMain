/*
 * Base class for all kinds of food
 * Store information like height and width
 */

#include "abstractfood.h"

AbstractFood::AbstractFood()
{
    width = 0;
    length = 0;
    centerX = 0;
    centerY = 0;

    isPeeled = false;
    isSliced = false;
}

int AbstractFood::parseType(const QString &str)
{
    if(str.compare("Apple")==0 || str.compare("apple")==0)
        return 1;

    if(str.compare("Potato")==0 || str.compare("potato")==0)
        return 0;
}
