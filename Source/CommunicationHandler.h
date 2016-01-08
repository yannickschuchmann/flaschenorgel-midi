//
//  CommunicationHandler.h
//  Flaschenorgel
//
//  Created by Yannick Schuchmann on 07.01.16.
//
//

#ifndef CommunicationHandler_h
#define CommunicationHandler_h

#include <stdio.h>

#include <iostream>

class CommunicationHandler
{
public:
    CommunicationHandler ();
    ~CommunicationHandler();
    
    void readSerial();
    std::string read();
    //==============================================================================
    
private:
    
};

#endif /* CommunicationHandler_h */
