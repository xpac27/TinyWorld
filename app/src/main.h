#include <vector>
#include <array>
#include <climits>

#define mask(n)     ((1) << (n))
#define as_int(e)   (int(e))
#define as_uint(e)  (unsigned(e))

// --------------------------

namespace Component
{
    enum class Type { position, life, visibility, COUNT };

    struct Position
    {
        // Position() :x(1.0), y(1.0) {}

        float x {0.0};
        float y {0.0};
    };

    struct Life
    {
        // Life() :amount(123) {}

        int amount {123};
    };

    struct Visibility
    {
        // Visibility() :active(true) {}

        bool active {true};
    };

    void debugPosition(Component::Position);
    void debugLife(Component::Life);
    void debugVisibility(Component::Visibility);
}

// --------------------------

class System
{
    public:
        bool useComponent(Component::Type componentType) const;

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
        const unsigned int componentTypes = mask(as_int(Component::Type::position));
};

class System_2 : public System
{
    // public:
    //     void update();

    protected:
        const unsigned int componentTypes = mask(as_int(Component::Type::position)) | mask(as_int(Component::Type::visibility));
};

// --------------------------

class EntitiesManager
{
    public:
        unsigned int addEntity();

        void addComponentToEntity(unsigned int entity, Component::Type componentType);
        void deleteComponentFromEntity(unsigned int entity, Component::Type componentType);
        void resetEntity(unsigned int entity);

        bool hasComponent(Component::Type componentType, unsigned int entity) const ;

        unsigned int getEntityCount() const;

        // TODO use template getComponent<Component::Type>()
        // we would have to avoid having component lists as member but instead have a components list of lists
        Component::Position getPositionComponent(unsigned int entity) const;
        Component::Life getLifeComponent(unsigned int entity) const;
        Component::Visibility getVisibilityComponent(unsigned int entity) const;

    private:
        System *systems[2]{
            new System_1(),
            new System_2()
        };

        unsigned int entityCount = 0;

        std::vector<std::array<unsigned int, as_int(Component::Type::COUNT)>> entitiesComponentsIndex;

        // replace by a list of lists array
        std::vector<Component::Position> positionComponents;
        std::vector<Component::Life> lifeComponents;
        std::vector<Component::Visibility> visibilityComponents;

        // TODO use template
        unsigned int addPositionComponent();
        unsigned int addVisibilityComponent();
        unsigned int addLifeComponent();

        template<Component::Type t> void registerComponent(unsigned int entity, unsigned int componentIndex);

        // TODO use template
        void deletePositionComponent(unsigned int index);
        void deleteVisibilityComponent(unsigned int index);
        void deleteLifeComponent(unsigned int index);

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

