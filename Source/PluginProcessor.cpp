/*
  ==============================================================================

    This file was auto-generated by the Introjucer!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
FlaschenorgelAudioProcessor::FlaschenorgelAudioProcessor()
{
    stateChanged = true;
    startTimer(5000);
}

FlaschenorgelAudioProcessor::~FlaschenorgelAudioProcessor()
{
}

//==============================================================================
const String FlaschenorgelAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool FlaschenorgelAudioProcessor::acceptsMidi() const
{
    return false;
}

bool FlaschenorgelAudioProcessor::producesMidi() const
{
    return true;
}

bool FlaschenorgelAudioProcessor::silenceInProducesSilenceOut() const
{
    return false;
}

double FlaschenorgelAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int FlaschenorgelAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int FlaschenorgelAudioProcessor::getCurrentProgram()
{
    return 0;
}

void FlaschenorgelAudioProcessor::setCurrentProgram (int index)
{
}

const String FlaschenorgelAudioProcessor::getProgramName (int index)
{
    return String();
}

void FlaschenorgelAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void FlaschenorgelAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void FlaschenorgelAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

void FlaschenorgelAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    
    // clearing audiochannels to avoid garbage.
    // framework required
    for (int i = getNumInputChannels(); i < getNumOutputChannels(); ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    for (int channel = 0; channel < getNumInputChannels(); ++channel)
    {
        float* channelData = buffer.getWritePointer (channel);
    }
    
    if (stateChanged) {
        /* doesn't play multiple notes.. just the last one
         * for now we have to do a sad workaround and play just the average note ;(
        sendNote(pressureToNote(350), 1, midiMessages);
        sendNote(pressureToNote(700), 2, midiMessages);
        sendNote(pressureToNote(950), 3, midiMessages);
         */
        int notes[3];
        notes[0] = pressureToNote(350);
        notes[1] = pressureToNote(750);
        notes[2] = pressureToNote(920);
        
        sendNote(getAverageNoteNumber(notes, 3), 1, midiMessages);
        stateChanged = false;
    }
}

int FlaschenorgelAudioProcessor::getAverageNoteNumber(int notes[], int notesLength)
{
    // notesLength parameter is just for keep it simple.
    // For more info take a look at sizeof of arrays passed to functions and becoming pointer
    int noteNumber;
    int noteSum = 0;
    int validNotes = 0;
    for (int i = 0; i < notesLength; i++) {
        if (notes[i] > 0) { // if valid note
            validNotes++;
            noteSum += notes[i];
        }
    }
    
    if (validNotes > 0) {
        noteNumber = noteSum / validNotes;
    } else {
        noteNumber = 0;
    }
    
    return noteNumber;
}

void FlaschenorgelAudioProcessor::sendNote (int noteNumber, int channel, MidiBuffer& midiMessages)
{
    MidiMessage msg;
    uint8 vel = 127;

    int lastNoteNumber = lastNoteNumbersForChannel[channel - 1];
    
    if (noteNumber == 0) {
        if (lastNoteNumber > 0) {
            msg = MidiMessage::noteOff(channel, lastNoteNumber, vel);
            midiMessages.addEvent(msg, midiMessages.getLastEventTime());
        }
        
        return;
    }

    msg = MidiMessage::noteOff(channel, noteNumber, vel);
    midiMessages.addEvent(msg, midiMessages.getLastEventTime());
    
    msg = MidiMessage::noteOn(channel, noteNumber, vel);
    midiMessages.addEvent(msg, midiMessages.getLastEventTime());

    lastNoteNumbersForChannel[channel - 1] = noteNumber;
    
    std::cout << noteNumber;
    std::cout << MidiMessage::getMidiNoteName(msg.getNoteNumber(), true, true, 1);
    std::cout << "\n";
}

int FlaschenorgelAudioProcessor::pressureToNote(int pressure)
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

void FlaschenorgelAudioProcessor::timerCallback()
{
    stateChanged = true;
}

//==============================================================================
bool FlaschenorgelAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* FlaschenorgelAudioProcessor::createEditor()
{
    return new FlaschenorgelAudioProcessorEditor (*this);
}

//==============================================================================
void FlaschenorgelAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void FlaschenorgelAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new FlaschenorgelAudioProcessor();
}
