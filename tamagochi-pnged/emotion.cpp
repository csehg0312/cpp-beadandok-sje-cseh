#include <iostream>
#include "QPixmap"

enum Emotion {
    Happy,
    Sad,
    Blushing
};

class EmotionHandle {
private:
    Emotion currentEmotion;




public:
    EmotionHandle() : currentEmotion(Happy) {}

    void setEmotion(Emotion newEmotion) {
        currentEmotion = newEmotion;
    }

    void expressEmotion() {
        switch (currentEmotion) {
        case Happy:
            std::cout << "Expressing happiness 😊" << std::endl;
            break;
        case Sad:
            std::cout << "Expressing sadness 😞" << std::endl;
            break;
        case Blushing:
            std::cout << "Expressing blushing ☺️" << std::endl;
            break;
        default:
            std::cout << "Unknown emotion" << std::endl;
        }
    }
};


