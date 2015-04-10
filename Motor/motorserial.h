#ifndef MOTORSERIAL_H
#define MOTORSERIAL_H

#include "serialib.h"
#include <QtCore>
#include "motorparams.h"

using namespace std;

/*!
 * \brief sending serial command to the arduino motor controller
 * function ended with to means absolute position
 * function ended with by means relative position
 * function start with b means block function, only return when the manipulator reach its position
 */
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

    /*!
     * \brief the function return until the arm reach its position
     * \param xPos
     * \param yPos
     */
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
     * \brief move the arm down with relative position
     * \param position
     * \return
     */
    bool moveDownBy(int position);
    void bMoveDownBy(int position);

    /*!
     * \brief move the arm down till hit the fruit
     * \return
     */
    bool moveDownTillHit(int strength);
    void bMoveDownTillHit(int strength);

    /*!
     * \brief set the gantry into origin position
     */
    bool goToOrigin();

    /*!
     * \brief move away the arm so it do not obscure the camera view
     */
    void moveAwayForCamera();

    /*!
     * \brief return the x poistion of the gantry
     * \return
     */
    int getXPos();

    /*!
     * \brief return the y position of the gantry
     * \return
     */
    int getYPos();

    /*!
     * \brief return the rotation speed of the arm
     * \return
     */
    int getRSpeed();

    /*!
     * \brief return the depth of the arm
     * \return
     */
    int getLPos();
    int getRevLPos();

    /*!
     * \brief return the distance moved by the blade
     * \return
     */
    int getPeelDis();

private:
    serialib serial;
    const QString endMark;

    int _xPos;
    int _yPos;
    int _rSpeed;
    int _lPos;
    int _peelPos;

    char _buffer[128];

    void updateState();
    int checkXpos(int xpos);
    int checkYpos(int ypos);
    int checkLpos(int lpos);
    int constrain(int value, int min, int max);

    bool toBool(int value);
    const char *toChar(QString string);
};

#endif // MOTORSERIAL_H
