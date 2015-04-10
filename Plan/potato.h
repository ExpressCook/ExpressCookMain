#ifndef POTATO_H
#define POTATO_H

#include<abstractfood.h>
class Potato : public AbstractFood
{
public:
    Potato();
    int getType();
    QString getName();
};

#endif // POTATO_H
