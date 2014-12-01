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
    int ret = serial.Open(DEVICE_PORT,19200);
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
    moveXTo(position);
    while(getXPos()!=position){}
}

bool MotorSerial::moveXBy(int position)
{
    QString command = "xr"+QString::number(position)+endMark;
    int ret = serial.WriteString(toChar(command));
    return toBool(ret);
}

void MotorSerial::bMoveXBy(int position)
{
    int finalPos = getXPos()+position;
    moveXBy(position);
    while(finalPos!=getXPos()){}
}

bool MotorSerial::moveYTo(int position)
{
    QString command = "ya"+QString::number(position)+endMark;
    int ret = serial.WriteString(toChar(command));
    return toBool(ret);
}

void MotorSerial::bMoveYTo(int position)
{
    moveYTo(position);
    while(getYPos()!=position){}
}

bool MotorSerial::moveYBy(int position)
{
    QString command = "yr"+QString::number(position)+endMark;
    int ret = serial.WriteString(toChar(command));
    return toBool(ret);
}

void MotorSerial::bMoveYBy(int position)
{
    int finalPos = getYPos()+position;
    moveYBy(position);
    while(finalPos!=getYPos()){}
}

bool MotorSerial::rotateWith(int speed)
{
    QString command = "ro"+QString::number(speed)+endMark;
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
    moveDownTo(position);
    while(abs(position-getLPos())>30){}
}

bool MotorSerial::goToOrigin()
{
    //the function should block until it reach the origin point
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
