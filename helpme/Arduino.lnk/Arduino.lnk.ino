#include <MIDI.h>

// Simple tutorial on how to receive and send MIDI messages.
// Here, when receiving any message on channel 4, the Arduino
// will blink a led and play back a note for 1 second.

MIDI_CREATE_DEFAULT_INSTANCE();

int sw1=2;
int sw2=3;
int sw3=4;
int sw4=5;
int sw5=6;
int sw6=7;
int sw7=8;
int sw8=9;
int sw9=10;
int sw10=11;
int sw11=12;
int sw12=13;

int j=0;
int i=0;
int k=0;
int l=0;
int m=0;
int n=0;
int o=0;
int p=0;
int q=0;
int r=0;
int s=0;
int t=0;



void setup()
{
    MIDI.begin(1);                      // Launch MIDI and listen to channel 4
    pinMode(sw1, INPUT_PULLUP);
    pinMode(sw2, INPUT_PULLUP);
    pinMode(sw3, INPUT_PULLUP);
    pinMode(sw4, INPUT_PULLUP);
    pinMode(sw5, INPUT_PULLUP);
    pinMode(sw6, INPUT_PULLUP);
    pinMode(sw7, INPUT_PULLUP);
    pinMode(sw8, INPUT_PULLUP);
    pinMode(sw9, INPUT_PULLUP);
    pinMode(sw10, INPUT_PULLUP);
    pinMode(sw11, INPUT_PULLUP);
    pinMode(sw12, INPUT_PULLUP);
}

void loop()
{
  if (digitalRead(sw1)==LOW && j==0)
    {
        MIDI.sendNoteOn(24, 100, 1);
        j=1;
    }
    else if (digitalRead(sw1)==HIGH && j==1)
    {
         MIDI.sendNoteOff(24, 0, 1);
         j=0;
    }


      if (digitalRead(sw2)==LOW && i==0)
    {
        MIDI.sendNoteOn(25, 100, 1);
        i=1;
    }
    else if (digitalRead(sw2)==HIGH && i==1)
    {
         MIDI.sendNoteOff(25, 0, 1);
         i=0;
    }

     if (digitalRead(sw3)==LOW && k==0)
    {
        MIDI.sendNoteOn(26, 100, 1);
        k=1;
    }
    else if (digitalRead(sw3)==HIGH && k==1)
    {
         MIDI.sendNoteOff(26, 0, 1);
         k=0;
    }

     if (digitalRead(sw4)==LOW && l==0)
    {
        MIDI.sendNoteOn(27, 100, 1);
        l=1;
    }
    else if (digitalRead(sw4)==HIGH && l==1)
    {
         MIDI.sendNoteOff(27, 0, 1);
         l=0;
    }

     if (digitalRead(sw5)==LOW && m==0)
    {
        MIDI.sendNoteOn(28, 100, 1);
        m=1;
    }
    else if (digitalRead(sw5)==HIGH && m==1)
    {
         MIDI.sendNoteOff(28, 0, 1);
         m=0;
    }

     if (digitalRead(sw6)==LOW && n==0)
    {
        MIDI.sendNoteOn(29, 100, 1);
        n=1;
    }
    else if (digitalRead(sw6)==HIGH && n==1)
    {
         MIDI.sendNoteOff(29, 0, 1);
         n=0;
    }

     if (digitalRead(sw7)==LOW && o==0)
    {
        MIDI.sendNoteOn(30, 100, 1);
        o=1;
    }
    else if (digitalRead(sw7)==HIGH && o==1)
    {
         MIDI.sendNoteOff(30, 0, 1);
         o=0;
    }

     if (digitalRead(sw8)==LOW && p==0)
    {
        MIDI.sendNoteOn(31, 100, 1);
        p=1;
    }
    else if (digitalRead(sw8)==HIGH && p==1)
    {
         MIDI.sendNoteOff(31, 0, 1);
         p=0;
    }

     if (digitalRead(sw9)==LOW && q==0)
    {
        MIDI.sendNoteOn(32, 100, 1);
        q=1;
    }
    else if (digitalRead(sw9)==HIGH && q==1)
    {
         MIDI.sendNoteOff(32, 0, 1);
         q=0;
    }

     if (digitalRead(sw10)==LOW && r==0)
    {
        MIDI.sendNoteOn(33, 100, 1);
        r=1;
    }
    else if (digitalRead(sw10)==HIGH && r==1)
    {
         MIDI.sendNoteOff(33, 0, 1);
         r=0;
    }

     if (digitalRead(sw11)==LOW && s==0)
    {
        MIDI.sendNoteOn(34, 100, 1);
        s=1;
    }
    else if (digitalRead(sw11)==HIGH && s==1)
    {
         MIDI.sendNoteOff(34, 0, 1);
         s=0;
    }

     if (digitalRead(sw12)==LOW && t==0)
    {
        MIDI.sendNoteOn(35, 100, 1);
        t=1;
    }
    else if (digitalRead(sw12)==HIGH && t==1)
    {
         MIDI.sendNoteOff(35, 0, 1);
         t=0;
    }


   
}
