#include "lest.hpp"

using namespace std;

const lest::test test_EntityManager[] =
{
    CASE( "Empty string has length zero" )
    {
        EXPECT( 0 == string(  ).length() );
        EXPECT( 0 == string("").length() );
    },
};
