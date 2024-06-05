#include "Feedback.h"
#include <map>


Feedback::Feedback(StatusIndicator statusIndicator, Buzzer buzzer) 
    : statusIndicator(statusIndicator), buzzer(buzzer) {
    patterns[IDLE] = {IDLE, StatusIndicator::BLUE, 200, 2000, 500};
    patterns[ARMED] = {ARMED, StatusIndicator::GREEN, 200, 2000, 500};
    patterns[FAILURE] = {FAILURE, StatusIndicator::RED, 200, 200, 1000};
}

void Feedback::setStatus(Status newStatus) {
    currentStatus = newStatus;
    statusIndicator.flash(patterns[newStatus].color, patterns[newStatus].onDurationMs, patterns[newStatus].offDurationMs);
    buzzer.beep(patterns[newStatus].onDurationMs, patterns[newStatus].offDurationMs, patterns[newStatus].toneFrequency);
}

void Feedback::update() {
    statusIndicator.update();
    buzzer.update();
}

