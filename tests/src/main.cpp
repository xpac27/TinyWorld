#include <algorithm>
#include "lest.hpp"
#include "test_EntityManager.cpp"

int main( int argc, char * argv[] )
{
    return std::min(
        lest::run(test_EntityManager),
    1);
}
