#include <QCoreApplication>
#include <stdio.h>
#include <serialib.h>
#include <motorserial.h>
#include <vision.h>
#include <executor.h>
#include <apple.h>
#include <potato.h>
#include <unistd.h>

#define  DEVICE_PORT "/dev/ttyO1"

int testSerial();
void testSerialLib();
void testSerialLibBlock();
void testHit();
void testVision();
void testPeel();
void testSlice();
void testDist();

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    //testSerial();
    //testSerialLib();
    //testSerialLibBlock();
    //testVision();
    //testHit();
    //testPeel();
    testSlice();
    //testDist();

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

    motorControl.bMoveXTo(1700);
    motorControl.bMoveYTo(720);
    //motorControl.bMoveDownTo(600);
    //motorControl.bMoveDownTo(600);
    //motorControl.bMoveTo(0,0);
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

    motor.bMoveDownTillHit(50);
    motor.bMoveTo(400,400);
    motor.goToOrigin();
}

void testVision()
{
    Vision vsNew;
    vsNew.takePicture();
    vsNew.detect();
    vector<DetectionResults> &num = vsNew.getList();

    cout<<"List Size"<<num.size()<<endl;

    DetectionResults first = vsNew.getFirst(1);

    cout<<first.centroid.x<<"\t"<<first.centroid.y<<endl;

    /*for(int i=0;i<num.size();i++)
    {
        DetectionResults test=num.at(i);
        cout<<"Type of fruit "<<test.fruitType<<endl;
    }*/
    cout<<"......................"<<endl;
}

void testPeel()
{
    Executor& exe = Executor::getInstance();

    Apple apple,apple2;
    apple.height=380;
    apple.width = 100;
    apple.length = 100;

    exe.fakeLoad(apple2);
    exe.peel(apple);
}

void testSlice()
{
    Executor& exe = Executor::getInstance();

    Potato apple;
    apple.height=380;
    apple.width = 100;
    apple.length = 100;

    exe.fakeLoad(apple);
    exe.slice(apple);
}

void testDist()
{
    MotorSerial motor;
    motor.init();

    while(true)
        cout << "dist:" << motor.getPeelDis() << endl;
}
