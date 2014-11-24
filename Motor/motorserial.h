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
     * \brief move the arm in base x and y direction
     * \param xPos
     * \param yPos
     * \return
     */
    bool moveTo(int xPos, int yPos);
    void bMoveTo(int xPos, int yPos);

    /*!
     * \brief move the arm in x direction to absolute position
     * \param position
     */
    bool moveXTo(int position);
    void bMoveXTo(int position);

    /*!
     * \brief move the arm in x direction with relative position
     * \param position
     */
    bool moveXBy(int position);
    void bMoveXBy(int position);

    /*!
     * \brief move the arm in y direction to absolute position
     * \param position
     */
    bool moveYTo(int position);
    void bMoveYTo(int position);

    /*!
     * \brief move the arm in y direction with relative position
     * \param position
     */
    bool moveYBy(int position);
    void bMoveYBy(int position);

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
    void bMoveDownTo(int position);

    /*!
     * \brief set the gantry into origin position
     */
    bool goToOrigin();

    /*!
     * \brief move away the arm so it do not obscure the camera view
     */
    void moveAwayForCamera();

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
