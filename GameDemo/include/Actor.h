#ifndef ACTOR_H
#define ACTOR_H

#include "vector"

#include "Vector2.h"

class Actor
{
    public:
        // Used to track state of actor
        enum State {
           EActive,
           EPaused,
           EDead
        };

        // Constructor/destructor
        Actor(class Game* game);
        virtual ~Actor();

        // Called every frame to update the actor
        // virtual void Update(float deltaTime);

        // called every frame to draw the actor
        // virtual void Draw();

        // Update function called from Game (not overridable)
        void Update(float deltaTime);
        // Called every frame to draw the Actor
        // void Draw();

        // Updates all the components attached to the actor (not overridable)
        void UpdateComponents(float deltaTime);

        // Any actor-specific update code (overridable)
        virtual void UpdateActor(float deltaTime);

        // Getters/setters // ... // Add/remove components
        void AddComponent(class Component* component);
        void RemoveComponent(class Component* component);

    private:
        // Actor's state
        State mState;

        // Transform
        Vector2 mPosition;  // Center position of actor
        float mScale;       // Uniforms scale of actor (1.0f for 100%)
        float mRotation;    // Rotation angle (in radians)

        // Components held by this actor
       std::vector<class Component*> mComponents;
        class Game* mGame;
        // The Actor class has several notable features. The state enum

};

#endif // ACTOR_H
