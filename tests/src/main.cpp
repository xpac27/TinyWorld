// #include <algorithm>
#include "hamlest.hpp"
// #include "test_EntityManager.cpp"
// #define CASE( name ) lest_CASE( specification(), name )

lest::tests & specification()
{
    static lest::tests tests;
    return tests;
}

int main( int argc, char * argv[] )
{
    return lest::run( specification(), argc, argv /*, std::cout */ );

    // return std::min(
    //     lest::run(test_EntityManager, argc, argv),
    // 1);
}
