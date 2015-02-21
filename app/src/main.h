#include <vector>
#include <climits>
#include <iostream>
#include <assert.h>

#define mask(n) ((1) << (n))

// --------------------------

// CRT Patern Object Register
template <class B>
struct Component
{
    static unsigned int typeIndex;
    static std::vector<B> list;
};
template <class B>
unsigned int Component<B>::typeIndex = UINT_MAX;
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

// --------------------------

class System
{
    public:
        System(unsigned int mask) :componentTypes(mask) {}

        void registerEntity(unsigned int entity);
        void unregisterEntity(unsigned int entity);

        bool useComponent(unsigned int mask) const;

        template<typename T>
            bool useComponent() const;

    protected:
        unsigned int componentTypes;

    private:
        std::vector<unsigned int> entities;
};

class System_1 : public System
{
    public:
        System_1() :System(
                mask(Component<Position>::typeIndex)) {}
};

class System_2 : public System
{
    public:
        System_2() :System(
                mask(Component<Position>::typeIndex) | 
                mask(Component<Life>::typeIndex)) {}
};

class EntitiesManager
{
    public:
        unsigned int addEntity();
        unsigned int getEntityCount() const;

        void resetEntity(unsigned int entity);

        template<typename T>
            void registerComponent();
        template<typename T>
            void registerSystem();
        template<typename T>
            void delComponent(unsigned int entity);
        template<typename T>
            bool hasComponent(unsigned int entity) const;
        template<typename T>
            T* addComponent(unsigned int entity);
        template<typename T>
            T* getComponent(unsigned int entity) const;

    private:
        unsigned int entityCount = 0;
        unsigned int componentTypeCount = 0;

        std::vector<System> systems;
        std::vector<std::vector<unsigned int>> entitiesComponentsIndex;
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

