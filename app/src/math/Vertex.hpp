#pragma once

struct Vertex
{
    GLfloat pos[3] {0.f, 0.f, 0.f};
    GLfloat tex[2] {0.f, 0.f};
    GLfloat nor[3] {0.f, 0.f, 1.f};
    GLfloat col[4] {1.f, 1.f, 1.f, 1.f};
    GLubyte pad[16];    // Pads the struct out to 64 bytes for performance increase
};
