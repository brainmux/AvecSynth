#include <MIDI.h>
#include <AvecSynth.h>

#define BUF_LEN(x) (sizeof((x))/sizeof((x)[0]))

static struct avec_sample buf[32] = {};

void setup()
{
  AvecSynth.begin();
  AvecSynth.Record(buf, BUF_LEN(buf));
}

void loop()
{
  unsigned long wait = millis();
  while (millis() - wait < 1000);
  AvecSynth.Play(buf, BUF_LEN(buf));
}
