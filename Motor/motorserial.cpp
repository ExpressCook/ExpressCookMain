#include "motorserial.h"
#define DEVICE_PORT "/dev/ttyO1"

MotorSerial::MotorSerial():endMark("!")
{
}

MotorSerial::~MotorSerial()
{
    serial.Close();
}

bool MotorSerial::init()
{
    int ret = serial.Open(DEVICE_PORT,SERIAL_RATE);
    return toBool(ret);
}

bool MotorSerial::moveTo(int xPos, int yPos)
{
    bool r1 = moveXTo(xPos);
    bool r2 = moveYTo(yPos);
    return r1&&r2;
}

void MotorSerial::bMoveTo(int xPos, int yPos)
{
    xPos = checkXpos(xPos);
    yPos = checkYpos(yPos);
    moveTo(xPos,yPos);
    while(getXPos()!=xPos || getYPos()!=yPos){}
}

bool MotorSerial::moveXTo(int position)
{
    QString command = "xa"+QString::number(position)+endMark;
    int ret = serial.WriteString(toChar(command));
    return toBool(ret);
}

void MotorSerial::bMoveXTo(int position)
{
    position = checkXpos(position);
    moveXTo(position);
    while(getXPos()!=position){}
}

bool MotorSerial::moveXBy(int position)
{
    int finalPos = getXPos()+position;
    return moveXTo(finalPos);
}

void MotorSerial::bMoveXBy(int position)
{
    int finalPos = getXPos()+position;
    bMoveXTo(finalPos);
}

bool MotorSerial::moveYTo(int position)
{
    QString command = "ya"+QString::number(position)+endMark;
    int ret = serial.WriteString(toChar(command));
    return toBool(ret);
}

void MotorSerial::bMoveYTo(int position)
{
    position = checkYpos(position);
    moveYTo(position);
    while(getYPos()!=position){}
}

bool MotorSerial::moveYBy(int position)
{
    int finalPos = getYPos()+position;
    return moveYTo(finalPos);
}

void MotorSerial::bMoveYBy(int position)
{
    int finalPos = getYPos()+position;
    bMoveYTo(finalPos);
}

bool MotorSerial::rotateWith(int speed)
{
    QString command = "rc"+QString::number(speed)+endMark;
    int ret = serial.WriteString(toChar(command));
    return toBool(ret);
}

bool MotorSerial::moveDownTo(int position)
{
    QString command = "lp"+QString::number(position)+endMark;
    int ret = serial.WriteString(toChar(command));
    return toBool(ret);
}

void MotorSerial::bMoveDownTo(int position)
{
    position = checkLpos(position);
    moveDownTo(position);
    //the tolerance should be smaller
    while(abs(position-getLPos())>=2){}
}

bool MotorSerial::moveDownBy(int position)
{
    return moveDownTo(getLPos()+position);
}

void MotorSerial::bMoveDownBy(int position)
{
    bMoveDownTo(getLPos()+position);
}

bool MotorSerial::moveDownTillHit(int strength)
{
    QString command = "lh"+QString::number(strength)+endMark;
    int ret = serial.WriteString(toChar(command));
    return toBool(ret);
}

void MotorSerial::bMoveDownTillHit(int strength)
{
    moveDownTillHit(strength);

    int lastPos,nowPos;
    do
    {
        QThread::msleep(30);
        lastPos = nowPos;
        nowPos = getLPos();
    }
    while(lastPos!=nowPos);
}

bool MotorSerial::goToOrigin()
{
    //the function block until it reach the origin point
    int ret = serial.WriteString("gc");
    QString state="";
    do
    {
        serial.ReadString(_buffer,'\n',128,1000);
        state = QString::fromUtf8(_buffer);
    }
    while(state.compare("c")==0);
    return toBool(ret);
}

void MotorSerial::moveAwayForCamera()
{
    int xSafe = 1200;
    int ySafe = 700;

    if(getXPos()<xSafe && getYPos()<ySafe)
        bMoveTo(xSafe, ySafe);
    else if(getXPos()<xSafe)
        bMoveXTo(xSafe);
    else if(getYPos()<ySafe)
        bMoveYTo(ySafe);
}

int MotorSerial::getXPos()
{
    updateState();
    return _xPos;
}

int MotorSerial::getYPos()
{
    updateState();
    return _yPos;
}

int MotorSerial::getRSpeed()
{
    updateState();
    return _rSpeed;
}

int MotorSerial::getLPos()
{
    updateState();
    return _lPos;
}

int MotorSerial::getRevLPos()
{
    return RANGE_L_MAX - getLPos();
}

int MotorSerial::getPeelDis()
{
    updateState();
    return _peelPos;
}

void MotorSerial::updateState()
{
    char a;
    do
    {
        serial.ReadChar(&a,100);
    }
    while(a!='*');

    serial.ReadString(_buffer,'\n',128,1000);

    QString state = QString::fromUtf8(_buffer);
    QStringList states = state.split("!");

    _xPos = states.at(0).toInt();
    _yPos = states.at(1).toInt();
    _rSpeed = states.at(2).toInt();
    _lPos = states.at(3).toInt();
    _peelPos = states.at(4).toInt();
}

int MotorSerial::checkXpos(int xpos)
{
   return constrain(xpos,0,RANGE_X);
}

int MotorSerial::checkYpos(int ypos)
{
   return constrain(ypos,0,RANGE_Y);
}

int MotorSerial::checkLpos(int lpos)
{
    return constrain(lpos,RANGE_L_MIN,RANGE_L_MAX);
}

int MotorSerial::constrain(int value, int min, int max)
{
    if(value<min)
        value = min;

    if(value>max)
        value = max;

    return value;
}

bool MotorSerial::toBool(int value)
{
    if(value==1)
        return true;
    else
        return false;
}

const char *MotorSerial::toChar(QString string)
{
    QByteArray ba = string.toLocal8Bit();
    return ba.constData();
}
