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

#include "../JuceLibraryCode/JuceHeader.h"

class CommunicationHandler
{
public:
    CommunicationHandler ();
    ~CommunicationHandler();
    
    void readSerial();
    std::vector<int> read();
    
    std::vector<int> parse(std::string valueStr);
    
    //==============================================================================
    
private:
    
};

#endif /* CommunicationHandler_h */
