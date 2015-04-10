#ifndef APPLE_H
#define APPLE_H

#include<abstractfood.h>
class Apple: public AbstractFood
{
public:
    Apple();
    int getType();
    QString getName();
};

#endif // APPLE_H
