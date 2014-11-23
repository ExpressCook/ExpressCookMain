#ifndef MOTORSERIAL_H
#define MOTORSERIAL_H

#include "serialib.h"
#include <QtCore>

using namespace std;

class MotorSerial
{

public:
    MotorSerial();
    ~MotorSerial();

    bool init();

    /*!
     * \brief move the arm in x direction to absolute position
     * \param position
     */
    bool moveXTo(int position);

    /*!
     * \brief move the arm in x direction with relative position
     * \param position
     */
    bool moveXBy(int position);

    /*!
     * \brief move the arm in y direction to absolute position
     * \param position
     */
    bool moveYTo(int position);

    /*!
     * \brief move the arm in y direction with relative position
     * \param position
     */
    bool moveYBy(int position);

    /*!
     * \brief rotate the arm with speed
     * \param speed
     */
    bool rotateWith(int speed);

    /*!
     * \brief move the arm down to absolute position
     * \param position
     */
    bool moveDownTo(int position);

    /*!
     * \brief set the gantry into origin position
     */
    bool goToOrigin();

    int getXPos();

    int getYPos();

    int getRSpeed();

    int getLPos();

private:
    serialib serial;
    QString endMark;

    int _xPos;
    int _yPos;
    int _rSpeed;
    int _lPos;

    char _buffer[128];

    void updateState();

    bool toBool(int value);
    const char *toChar(QString string);
};

#endif // MOTORSERIAL_H
