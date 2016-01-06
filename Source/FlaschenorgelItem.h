//
//  FlaschenorgelItem.hpp
//  Flaschenorgel
//
//  Created by Yannick Schuchmann on 06.01.16.
//
//

#ifndef FlaschenorgelItem_h
#define FlaschenorgelItem_h

#include <stdio.h>

#include "../JuceLibraryCode/JuceHeader.h"

class FlaschenorgelItem
{
public:
    FlaschenorgelItem ();
    ~FlaschenorgelItem();
    
    int getNoteNumber();
    int getPressure();
    void setPressure(int pressure);
    
    const static int TARA = 300;
    const int DELTARANGE = 700 / 2;
    const int NOTENUMBERCENTER = 62;
    const int NOTENUMBERRANGE = 26;
    
    //==============================================================================
    
private:
    int pressure;
};

#endif /* FlaschenorgelItem_h */
