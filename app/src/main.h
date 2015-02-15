#include <vector>
#include <array>
#include <climits>

#define mask(n)  ((1) << (n))

// --------------------------

namespace Component
{
    enum Type { position, life, visibility };

    struct Position
    {
        float x = 1.0;
        float y = 1.0;
    };

    struct Life
    {
        int amount = 123;
    };

    struct Visibility
    {
        bool active = true;
    };

    // TODO use template debug<Component::Type>()
    void debugPosition(Component::Position);
    void debugLife(Component::Life);
    void debugVisibility(Component::Visibility);
}

// --------------------------

class System
{
    public:
        bool hasComponentType(Component::Type type) const;
        void registerEntity(unsigned int entity);
        void unregisterEntity(unsigned int entity);

        // virtual void update() = 0;
        // virtual ~System();

    protected:
        const unsigned int componentTypes = 0;

    private:
        std::vector<unsigned int> entities;
};

class System_1 : public System
{
    // public:
    //     void update();

    protected:
        const unsigned int componentTypes = mask(Component::Type::position);
};

class System_2 : public System
{
    // public:
    //     void update();

    protected:
        const unsigned int componentTypes = mask(Component::Type::position) | mask(Component::Type::visibility);
};

// --------------------------

class EntitiesManager
{
    public:
        unsigned int addEntity();

        void addComponentToEntity(unsigned int entity, Component::Type componentType);
        void deleteComponentFromEntity(unsigned int entity, Component::Type componentType);
        void deleteEntity(unsigned int entity);

        bool hasComponent(unsigned int entity, Component::Type componentType) const;

        unsigned int getEntityCount() const;

        // TODO use template getComponent<Component::Type>()
        Component::Position getPositionComponent(unsigned int entity) const;
        Component::Life getLifeComponent(unsigned int entity) const;
        Component::Visibility getVisibilityComponent(unsigned int entity) const;

    private:
        System *systems[2]{
            new System_1(),
            new System_2()
        };

        unsigned int entityCount = 0;

        std::vector<std::array<unsigned int, 3>> entitiesComponentsIndex;

        // TODO use template
        std::vector<Component::Position> positionComponents;
        std::vector<Component::Life> lifeComponents;
        std::vector<Component::Visibility> visibilityComponents;

        // TODO use template
        unsigned int addPositionComponent();
        unsigned int addVisibilityComponent();
        unsigned int addLifeComponent();

        // TODO use template
        void deletePositionComponent(unsigned int index);
        void deleteVisibilityComponent(unsigned int index);
        void deleteLifeComponent(unsigned int index);

        void deleteComponent(Component::Type componentType, unsigned int index);
        void deleteAllComponentsFromEntity(unsigned int entity);

        void registerEntity(unsigned int entity, Component::Type componentType);
        void unregisterEntity(unsigned int entity, Component::Type componentType);
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

