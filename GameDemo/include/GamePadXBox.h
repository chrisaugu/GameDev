#ifndef GAMEPADXBOX_H
#define GAMEPADXBOX_H

#include <XInput.h>

class GamePadXBox
{
    public:
        GamePadXBox();
        virtual ~GamePadXBox();
        // GamePadState State;
        bool IsConnected() const;
        void Vibrate(float leftMotor, float rightMotor);
        void Update();

    protected:

    private:
        XINPUT_STATE state;
        // GamePadIndex playerIndex;
};

#endif // GAMEPADXBOX_H
