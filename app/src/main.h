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

class Entity
{
    public:
        Entity(unsigned int i) :index(i){}

        unsigned int index = 0;
        int componentIndexes[3] = {-1};
};

// --------------------------

class System
{
    public:
        bool hasComponentType(Component::Type type) const;
        void registerEntity(Entity* entity);
        void removeEntity(Entity* entity);

        // virtual void update() = 0;
        // virtual ~System();

    protected:
        const unsigned int componentTypes = 0;

    private:
        std::vector<Entity*> entities;
};

class System_1 : public System
{
    // public:
    //     void update();

    protected:
        const unsigned int componentTypes = Component::Mask::POSITION;
};

class System_2 : public System
{
    // public:
    //     void update();

    protected:
        const unsigned int componentTypes = Component::Mask::POSITION | Component::Mask::VISIBILITY;
};

// --------------------------

class EntitiesManager
{
    public:
        Entity* addEntity();

        void addComponentToEntity(Entity* entity, Component::Type componentType);
        void deleteComponentFromEntity(Entity* entity, Component::Type componentType);
        void deleteEntity(Entity* entity);

    private:
        System *systems[2]{
            new System_1(),
            new System_2()};

        std::vector<Entity> entities;

        std::vector<Component::Position> positionComponents;
        std::vector<Component::Life> lifeComponents;
        std::vector<Component::Visibility> visibilityComponents;

        unsigned int addPositionComponent();
        unsigned int addVisibilityComponent();
        unsigned int addLifeComponent();

        void deletePositionComponent(unsigned int index);
        void deleteVisibilityComponent(unsigned int index);
        void deleteLifeComponent(unsigned int index);

        void deleteComponent(Component::Type componentType, unsigned int index);
        void deleteAllComponentsFromEntity(Entity* entity);

        void registerEntity(Entity* entity, Component::Type componentType);
        void unregisterEntity(Entity* entity, Component::Type componentType);
};

// --------------------------

class Game
{
    public:
        Game() :entityManager{EntitiesManager()} {}

        void start();

    private:
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

