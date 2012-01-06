
#ifndef AVECSYNTH_H__
#define AVECSYNTH_H__

#include <../MIDI/MIDI.h>
#include <stdlib.h>

struct avec_sample
{
  unsigned long delay_ms;
  kMIDIType     type;
  byte          channel;
  byte          data1;
  byte          data2;
};

class CAvecSynth
{
  public:
  CAvecSynth();
  virtual ~CAvecSynth();

  void    begin(const byte inChannel=1);
  void    Record(struct avec_sample* buf, size_t nsamples, byte Channel = 1);
  void    Play(const struct avec_sample* buf, size_t nsamples, byte Channel = 1);
};

extern CAvecSynth AvecSynth;

#endif // AVECSYNTH_H__

