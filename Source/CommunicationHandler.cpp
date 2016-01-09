//
//  CommunicationHandler.cpp
//  Flaschenorgel
//
//  Created by Yannick Schuchmann on 07.01.16.
//
//

#include "CommunicationHandler.h"

#include "SerialStream.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

CommunicationHandler::CommunicationHandler ()
{
    
}


CommunicationHandler::~CommunicationHandler ()
{
    
}


/* workaround
 * Reads arduino values from txt file which keeps updated by
 * Ruby script which is doing the part that seems too tricky for c++
 */
std::vector<int> CommunicationHandler::read()
{
    
    ifstream myReadFile;
    myReadFile.open("/Users/yannick/tmp_flaschenorgel.txt");
    char output[100];
    if (myReadFile.is_open()) {
        while (!myReadFile.eof()) {
            myReadFile >> output;
            cout << "Value: " << output << std::endl;
        }
    }
    myReadFile.close();
    
    
    return parse(output);
}

std::vector<int> CommunicationHandler::parse(std::string valueStr)
{
    std::vector<int> vect;
    std::stringstream ss(valueStr);
    
    int i;
    while (ss >> i)
    {
        vect.push_back(i);
        
        if (ss.peek() == '|')
            ss.ignore();
    }
    
    return vect;
}

void CommunicationHandler::readSerial()
{

    // sadly not working because of.. reasons
    // just freezing
    // known issue: http://stackoverflow.com/questions/4303995/libserial-open-freezes-in-my-c-program
    
    
    /*
    using namespace LibSerial;
    SerialStream serial_port ;
    
    serial_port.SetBaudRate(SerialStreamBuf::BAUD_9600);
    serial_port.SetCharSize(SerialStreamBuf::CHAR_SIZE_8);
    serial_port.SetFlowControl(SerialStreamBuf::FLOW_CONTROL_NONE);
    serial_port.SetNumOfStopBits(1);
    serial_port.SetParity(SerialStreamBuf::PARITY_NONE);
    serial_port.SetVTime(10);

    serial_port.Open("/dev/tty.usbmodem1411");
    
    if (serial_port.IsOpen() != false) {
        std::cout << "open?!";
    }
    
    while( serial_port.rdbuf()->in_avail() > 0  )
    {
        char next_byte;
        serial_port.get(next_byte);
        std::cerr << std::hex << static_cast<int>(next_byte) << " ";
        usleep(100) ;
    }
     */
    
}