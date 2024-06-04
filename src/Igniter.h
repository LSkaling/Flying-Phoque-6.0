#ifndef IGNITER_H
#define IGNITER_H

class Igniter {
    public:
        Igniter(int igniterPin, int sensePin);
        void arm();
        void disarm();
        void fire();
        bool isArmed();
        bool isFiring();
        bool igniterCheck();
        int readSensePin();
        void reset();

    private:
        int igniterPin;
        int sensePin;
        bool armed;
        bool firing;

};

#endif