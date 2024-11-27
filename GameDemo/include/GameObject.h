#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Component.h"

class GameObject
{
    public:
        GameObject();
        virtual ~GameObject();

        void AddComponent(Component* comp);
        void RemoveComponent(Component* comp);

    protected:

    private:
        //std::unordered_set<Component*> mComponents;
};

#endif // GAMEOBJECT_H
