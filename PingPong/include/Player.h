#include <string>

#ifndef PLAYER_H
#define PLAYER_H

class Player
{
    public:
        Player();
        virtual ~Player();
        void setNextPlayer(Player* next) {
            m_pNext = next;
        }

    protected:

    private:
        //string m_Name;
        Player* m_pNext; // point to next player in a list
};

#endif // PLAYER_H
