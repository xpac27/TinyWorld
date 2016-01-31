#include "Manifold.hpp"
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

using namespace std;

void generateTrianglesAdjacencyIndex(std::vector<glm::uvec3> &triangles, std::vector<unsigned int> &indexes)
{
    // Indexes' triangles
    vector<vector<glm::uvec3*>> indexesTriangles;

    // For each triangles
    for (auto& t : triangles) {
        // For each index of that triangles
        for (int i = 0; i < 3; ++i) {
            // Associate that triangle to that index
            if (indexesTriangles.size() <= t[i]) indexesTriangles.resize(t[i] + 1, vector<glm::uvec3*>({}));
            indexesTriangles[t[i]].push_back(&t);
        }
    }

    // For each triangles
    for (auto& t : triangles) {
        // For each index of that triangles
        for (int ti = 0; ti < 3; ti ++) {
            bool matched = false;
            // For each triangles sharing this index
            for (auto& n : indexesTriangles[t[ti]]) {
                if (matched) break;
                if (*n == t) continue;
                // For each of its edge
                for (int ni = 0; ni < 3; ni ++) {
                    unsigned int t1_A = t[ti];
                    unsigned int t1_B = t[(ti + 1) % 3];
                    unsigned int t2_A = (*n)[ni];
                    unsigned int t2_B = (*n)[(ni + 1) % 3];
                    if ((t1_A == t2_A && t1_B == t2_B) || (t1_A == t2_B && t1_B == t2_A)) {
                        indexes.push_back(t[ti]);
                        indexes.push_back((*n)[(ni + 2) % 3]);
                        matched = true;
                        break;
                    }
                }
            }
        }
    }
}
