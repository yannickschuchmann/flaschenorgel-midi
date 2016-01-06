//
//  FlaschenorgelItem.cpp
//  Flaschenorgel
//
//  Created by Yannick Schuchmann on 06.01.16.
//
//

#include "FlaschenorgelItem.h"

FlaschenorgelItem::FlaschenorgelItem ()
{
    pressure = 0;
}

void FlaschenorgelItem::setPressure(int _pressure) {
    pressure = _pressure;
}

int FlaschenorgelItem::getPressure()
{
    return pressure;
}

int FlaschenorgelItem::getNoteNumber()
{
    int noteNumber = 0;
    int deltaNoteNumber;
    int deltaPressure = pressure - TARA; // mute on "tara"
    if (deltaPressure > 0) {
        deltaNoteNumber = round((deltaPressure - DELTARANGE) / (DELTARANGE / NOTENUMBERRANGE));
        std::cout << deltaNoteNumber;
        noteNumber = NOTENUMBERCENTER + deltaNoteNumber;
    }
    return noteNumber;
}

FlaschenorgelItem::~FlaschenorgelItem()
{
}

