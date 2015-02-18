/*
 * Base class for all kinds of food
 * Store information like height and width
 */

#ifndef ABSTRACTFOOD_H
#define ABSTRACTFOOD_H

class AbstractFood
{
public:
    AbstractFood();
    virtual int getType()=0;

    int width;
    int length;
    int height;
    int centerX;
    int centerY;
};

#endif // FOOD_H
