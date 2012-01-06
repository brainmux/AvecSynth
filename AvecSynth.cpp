
#include "AvecSynth.h"

#if defined(ARDUINO) && ARDUINO >= 100
#include <Arduino.h>
#else
#include <wiring.h>
#endif

#include <string.h>

CAvecSynth AvecSynth;

CAvecSynth::CAvecSynth()
{
}

CAvecSynth::~CAvecSynth()
{
}

void CAvecSynth::begin(const byte inChannel)
{
  MIDI.begin(inChannel);
}

byte getInputChannel()
{
  return MIDI.getInputChannel();
}

void setInputChannel(const byte Channel)
{
  MIDI.setInputChannel(Channel);
}

void CAvecSynth::Record(struct avec_sample* Buffer, size_t NSamples, byte Channel)
{
  int  nread = 0;
  unsigned long start;
  while (nread < NSamples)
  {
    if (MIDI.read(Channel))
    {
      memset(&Buffer[nread], 0, sizeof(struct avec_sample));
      switch ((Buffer[nread].type = MIDI.getType()))
      {
        case NoteOn:
        case NoteOff:
        case ControlChange:
        case PitchBend:
        case AfterTouchPoly:
        case SongPosition:
          Buffer[nread].data2 = MIDI.getData2();
        case ProgramChange:
        case AfterTouchChannel:
        case TimeCodeQuarterFrame:
        case SongSelect:
          Buffer[nread].data1 = MIDI.getData1();
        case Start:
        case Continue:
        case Stop:
        case Clock:
        case ActiveSensing:
        case SystemReset:
        case TuneRequest:
            Buffer[nread].channel   = MIDI.getChannel();
            if (!nread)
            {
              Buffer[nread].delay_ms  = 0;
              start = millis();
            }
            else
              Buffer[nread].delay_ms  = millis() - start;
          break;
        default:
          continue;
      }
      nread++;
    }
  }
}

void CAvecSynth::Play(const struct avec_sample* Buffer, size_t NSamples, byte Channel)
{
  size_t                    nplay = 0;
  const struct avec_sample* play;
  unsigned long             start = millis();
  while (nplay < NSamples)
  {
    unsigned long wait = 0;
    play = &Buffer[nplay];
    while (millis() - start < play->delay_ms);
    MIDI.send(play->type, play->data1, play->data2, play->channel);
    nplay++;
  }   
}

