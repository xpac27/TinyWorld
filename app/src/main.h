#include <vector>

// TODO use const where it should be used

// --------------------------

namespace Component
{
    enum Type { position, life, visibility };
    enum Mask
    {
        POSITION   = 1 << 0,
        LIFE       = 1 << 1,
        VISIBILITY = 1 << 2
    };

    struct Position
    {
        float x = 0.0;
        float y = 0.0;
    };

    struct Life
    {
        unsigned int amount = 100;
    };

    struct Visibility
    {
        bool active = true;
    };
}

// --------------------------

struct Entity
{
    unsigned int componentIndexes[3] = {0};
};

class EntitiesManager
{
    public:
        unsigned int addEntity();
        // void deleteEntity(unsigned int entityIndex);
        void addComponentToEntity(unsigned int entityIndex, Component::Type componentType);
        // void removeComponentFromEntity(unsigned int entityIndex, Component::Type componentType);

    private:
        unsigned int totalEntities = 0;
        // unsigned int totalComponents[3] = {0};

        std::vector<Entity> entities;

        std::vector<Component::Position> positionComponents;
        std::vector<Component::Life> lifeComponents;
        std::vector<Component::Visibility> visibilityComponents;
};



// --------------------------

// class System
// {
//     public:
//         unsigned int componentTypes = 0;
//
//     protected:
//         unsigned int entities[20] {0};
//         unsigned int totalEntities = 0;
// };
//
// class System_1 : public System
// {
//     public:
//         unsigned int componentTypes = Component::Mask::POSITION;
// };
//
// class System_2 : public System
// {
//     public:
//         unsigned int componentTypes = Component::Mask::POSITION | Component::Mask::VISIBILITY;
// };

// --------------------------

class Game
{
    public:
        Game() :
            // systems{new System_1(), new System_2()}, 
            entityManager{EntitiesManager()} {}

        void start();

    private:
        // System *systems[2];
        EntitiesManager entityManager;
};

// --------------------------

// class ComponentsManager
// {
//     protected:
//         Component::None components[5];
//         int totalComponents = 0;
// };
//
// class PositionComponentsManager : public ComponentsManager
// {
//     protected:
//         Component::Position components[5];
//         int totalComponents = 0;
// };
//
// class LifeComponentsManager : public ComponentsManager
// {
//     protected:
//         Component::Life components[5];
//         int totalComponents = 0;
// };
//
// class VisibilityComponentsManager : public ComponentsManager
// {
//     protected:
//         Component::Visibility components[5];
//         int totalComponents = 0;
// };

