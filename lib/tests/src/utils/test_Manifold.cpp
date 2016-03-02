#include "catch.hpp"
#include "../../../src/utils/Manifold.hpp"
#include <glm/glm.hpp>

using namespace std;
using namespace glm;

namespace
{
    SCENARIO("Manifold util can generate triangles adjacency index") {

        vector<uvec3> triangles;
        vector<unsigned int> indexes;
        vector<unsigned int> expectedIndexes;

        GIVEN("a pyramid") {

            triangles.push_back(uvec3(0, 4, 1));
            triangles.push_back(uvec3(1, 4, 2));
            triangles.push_back(uvec3(2, 4, 3));
            triangles.push_back(uvec3(3, 4, 0));
            triangles.push_back(uvec3(0, 1, 2));
            triangles.push_back(uvec3(0, 2, 3));

            expectedIndexes = {
                0, 3, 4, 2, 1, 2,
                1, 0, 4, 3, 2, 0,
                2, 1, 4, 0, 3, 0,
                3, 2, 4, 1, 0, 2,
                0, 4, 1, 4, 2, 3,
                0, 1, 2, 4, 3, 4,
            };

            WHEN("generating triangles adjacency index") {

                generateTrianglesAdjacencyIndex(triangles, indexes);

                THEN("index values are correct") {

                    CHECK(indexes == expectedIndexes);
                }
            }
        }
    }
}
