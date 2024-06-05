#ifndef FEEDBACK
#define FEEDBACK

#include "StatusIndicator.h"
#include "Buzzer.h"
#include <map>

enum Status {
    IDLE,
    ARMED,
    FAILURE
};

struct FeedbackPattern {
    Status status;
    StatusIndicator::Color color;
    int onDurationMs;
    int offDurationMs;
    int toneFrequency;
};

class Feedback{
    public:
        Feedback(StatusIndicator statusIndicator, Buzzer buzzer);
        void setStatus(Status newStatus);
        void update();
    
    private:
        StatusIndicator statusIndicator;
        Buzzer buzzer;
        Status currentStatus;
        std::map<Status, FeedbackPattern> patterns;

        
};

#endif