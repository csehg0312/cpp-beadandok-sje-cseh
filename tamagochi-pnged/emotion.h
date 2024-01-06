#ifndef EMOTION_H
#define EMOTION_H

#include <QPixmap>

enum Emotion {
    Happy,
    Sad,
    Blushing
};

class EmotionHandle {
private:
    Emotion currentEmotion;



public:
    EmotionHandle();
    void setEmotion(Emotion newEmotion);
    Emotion getEmotion() const;
    void expressEmotion();
};

#endif // EMOTION_H
