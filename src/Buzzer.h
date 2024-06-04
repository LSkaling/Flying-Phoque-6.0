#ifndef BUZZER_H
#define BUZZER_H

class Buzzer {
  public:
    Buzzer(int pin);
    void slowBeep();
    void fastBeep();
    void longBeep();
    void beep(int onDurationMs, int offDurationMs, int tone);
    void noBeep();
    void update();

  private:
    int pin;
    int onDurationMs;
    int offDurationMs;
    int toneFrequency;

};

#endif