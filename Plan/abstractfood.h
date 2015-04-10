/*
 * Base class for all kinds of food
 * Store information like height and width
 */

#ifndef ABSTRACTFOOD_H
#define ABSTRACTFOOD_H
#include<qstring.h>

class AbstractFood
{
public:
    AbstractFood();
    virtual int getType()=0;
    virtual QString getName()=0;

    static int parseType(const QString &str);

    int width;
    int length;
    int height;
    int centerX;
    int centerY;

    int loadForce;
    int defaultThick;

    bool isPeeled;
    bool isSliced;
};

#endif // FOOD_H
