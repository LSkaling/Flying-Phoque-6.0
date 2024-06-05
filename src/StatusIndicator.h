#ifndef STATUS_INDICATOR_H
#define STATUS_INDICATOR_H

class StatusIndicator {
    public:
        StatusIndicator(int redPin, int greenPin, int bluePin);

        enum Color {
            RED,
            GREEN,
            BLUE,
            ORANGE,
            WHITE,
            OFF
        };

        Color currentColor;

        void flash(Color color, int onDurationMs, int offDurationMs);
        void solid(Color color);
        void off();
        void update();
        void setIntensity(float redIntensity, float greenIntensity, float blueIntensity);
    //    void setBrightness(int pin, int intensity); // 0-255

    private:
        int redPin;
        int greenPin;
        int bluePin;

        int redPower;
        int greenPower;
        int bluePower;

        int onDurationMs;
        int offDurationMs;

        float redIntensity;
        float greenIntensity;
        float blueIntensity;

        int MAX_INTENSITY; //TODO: How to set this to constant?
};

#endif