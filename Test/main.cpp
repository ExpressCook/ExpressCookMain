#include <QCoreApplication>
#include <stdio.h>
#include <serialib.h>
#include <motorserial.h>
#include <visioninitialization.h>
#include <vision.h>
#include <unistd.h>

#define  DEVICE_PORT "/dev/ttyO1"

int testSerial();
void testSerialLib();
void testSerialLibBlock();
void testHit();
void testVision();

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    //testSerial();
    testSerialLib();
    //testSerialLibBlock();
    //testVision();
    //testHit();

    return a.exec();
}

int testSerial()
{
    serialib LS;                                                            // Object of the serialib class
    int Ret;                                                                // Used for return values
    char Buffer[128];

    // Open serial port
    Ret=LS.Open(DEVICE_PORT,9600);                                        // Open serial link at 115200 bauds
    if (Ret!=1) {                                                           // If an error occured...
        printf ("Error while opening port. Permission problem ?\n");        // ... display a message ...
        return Ret;                                                         // ... quit the application
    }
    printf ("Serial port opened successfully !\n");

    // Write the AT command on the serial port
    Ret=LS.WriteString("ro200!");                                             // Send the command on the serial port
    if (Ret!=1) {                                                           // If the writting operation failed ...
        printf ("Error while writing data\n");                              // ... display a message ...
        return Ret;                                                         // ... quit the application.
    }
    printf ("Write operation is successful \n");

    // Read a string from the serial device
    Ret=LS.ReadString(Buffer,'\n',128,5000);                                // Read a maximum of 128 characters with a timeout of 5 seconds
    // The final character of the string must be a line feed ('\n')
    if (Ret>0)                                                              // If a string has been read from, print the string
        printf ("String read from serial port : %s",Buffer);
    else
        printf ("TimeOut reached. No data received !\n");                   // If not, print a message.

    // Close the connection with the device
    LS.Close();

    return 0;
}

void testSerialLibBlock()
{
    MotorSerial motorControl;
    motorControl.init();

    motorControl.goToOrigin();

    motorControl.bMoveXTo(1000);
    motorControl.bMoveYTo(400);
    motorControl.bMoveDownTo(600);
    motorControl.bMoveDownTo(200);
    motorControl.bMoveTo(0,0);
}

void testSerialLib()
{
    MotorSerial motorControl;
    motorControl.init();

    motorControl.goToOrigin();

    for(int i=0; i<10; i++)
    {
        motorControl.moveXTo(1000);
        motorControl.moveYTo(500);
        motorControl.rotateWith(200);
        motorControl.moveDownTo(700);

        while(motorControl.getLPos()<600)
        {}

        motorControl.moveDownTo(100);
        motorControl.rotateWith(0);

        motorControl.moveXTo(100);
        motorControl.moveYTo(100);

        while(motorControl.getXPos()!=100
              && motorControl.getYPos()!=100
              && motorControl.getLPos()>150)
        {}
    }
}

void testHit()
{
    MotorSerial motor;
    motor.init();
    motor.goToOrigin();

    motor.bMoveDownTillHit();
    motor.bMoveTo(400,400);
    motor.goToOrigin();
}

void testVision()
{
    //VisionInitialization vsInit;protected variables in C++ functions
    //Vision vsOriginal;
    Vision vsNew;

    vsNew.imgCapture(0);
    usleep(10000000);
    vsNew.imgCapture(1);
    int num;
    num=vsNew.compute();
    cout<<"Number"<<num<<endl;
    CentrePoint point = vsNew.CalculateCentroid(0);
    //cout<<"Centroid Points are x:"<<point.x<<endl;
    //cout<<"Centroid Points are y:"<<point.y<<endl;
    //cout<<"......................"<<endl;

}
