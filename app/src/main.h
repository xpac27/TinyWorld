#include <vector>
#include <array>
#include <climits>
#include <iostream>
#include <assert.h>

#define mask(n)     ((1) << (n))

// --------------------------

class System
{
    public:
        // bool useComponent(Component::Type componentType) const;

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
        // const unsigned int componentTypes = mask(as_int(Component::Type::position));
};

class System_2 : public System
{
    // public:
    //     void update();

    protected:
        // const unsigned int componentTypes = mask(as_int(Component::Type::position)) | mask(as_int(Component::Type::visibility));
};

// --------------------------

template <class B>
struct Component
{
    static unsigned int index;
    static std::vector<B> list;
};
template <class B>
unsigned int Component<B>::index = UINT_MAX;
template <class B>
std::vector<B> Component<B>::list = std::vector<B>();

struct Position : Component<Position>
{
    float x {0.0};
    float y {0.0};
};

struct Life : Component<Life>
{
    int amount {123};
};

struct Visibility : Component<Visibility>
{
    bool active {true};
};

template <class T>
void print(const T* p);
std::ostream& operator <<(std::ostream& os, const Position* p);
std::ostream& operator <<(std::ostream& os, const Life* p);
std::ostream& operator <<(std::ostream& os, const Visibility* p);

class EntitiesManager
{
    public:
        unsigned int addEntity();
        unsigned int getEntityCount() const;

        template<typename T>
            void registerComponent();
        template<typename T>
            bool hasComponent(unsigned int entity) const;
        template<typename T>
            T* addComponent(unsigned int entity);
        template<typename T>
            T* getComponent(unsigned int entity);

        // template<typename T>
        //     void delComponent(unsigned int entity);
        //     void delComponent(unsigned int entity, Component::Type componentType);
        //     void delComponent(unsigned int entity, Component::Base *component);

        // void reset(unsigned int entity);

    private:
        unsigned int entityCount = 0;
        unsigned int componentTypeCount = 0;

        std::vector<std::vector<unsigned int>> entitiesComponentsIndex;

        System *systems[2]{
            new System_1(),
            new System_2()
        };
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

