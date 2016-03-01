layout(triangles_adjacency) in; // 6 vertice
layout(triangle_strip, max_vertices = 12) out;

uniform mat4 view;
uniform mat4 projection;
uniform vec4 direct_light_direction;

vec3 GetNormal(int v1, int v2, int v3)
{
    vec3 a = gl_in[v1].gl_Position.xyz - gl_in[v2].gl_Position.xyz;
    vec3 b = gl_in[v3].gl_Position.xyz - gl_in[v2].gl_Position.xyz;
    return normalize(cross(a, b));
}

bool FacesLight(int v1, int v2, int v3, vec3 light_direction) {
    vec3 normal = GetNormal(v1, v2, v3);
    return !(dot(normal, light_direction) > 0.);
}

void main()
{
    // Get light direction
    vec4 d = direct_light_direction;

    // Skip if triangle doesn't face light
    if (!FacesLight(0, 2, 4, d.xyz)) {
        return;
    }

    // Loop over all edges
    for (int i = 0; i < 3; i ++) {
        // Compute indices of neighbor triangle.
        int v1 = (i * 2);
        int n0 = (i * 2 + 1);
        int v0 = (i * 2 + 2) % 6;
        // If facing light
        if (FacesLight(v0, n0, v1, d.xyz)) {
            // Extrude edge
            gl_Position = projection * view * gl_in[v0].gl_Position;
            EmitVertex();
            gl_Position = projection * view * direct_light_direction;
            EmitVertex();
            gl_Position = projection * view * gl_in[v1].gl_Position;
            EmitVertex();
            gl_Position = projection * view * direct_light_direction;
            EmitVertex();
            EndPrimitive();
        }
    }
}
