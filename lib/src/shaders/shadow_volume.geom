#version 330

layout(triangles_adjacency) in; // 6 vertice
layout (triangle_strip, max_vertices = 12) out;
/* layout (triangles) in; */
/* layout (line_strip, max_vertices = 6) out; */

uniform vec4 direct_light_direction;

vec3 GetNormal(int t1, int t2, int t3)
{
    vec3 a = vec3(gl_in[t1].gl_Position) - vec3(gl_in[t2].gl_Position);
    vec3 b = vec3(gl_in[t3].gl_Position) - vec3(gl_in[t2].gl_Position);
    return normalize(cross(a, b));
}

void GenerateLine(int index, vec3 normal)
{
    gl_Position = gl_in[index].gl_Position;
    EmitVertex();
    gl_Position = gl_in[index].gl_Position + vec4(normal, 0.0f) * 0.4f;
    EmitVertex();
    EndPrimitive();
}

void main()
{
    /* vec3 normal = GetNormal(0, 1, 2); */
    /* GenerateLine(0, normal); // First vertex normal */
    /* GenerateLine(1, normal); // Second vertex normal */
    /* GenerateLine(2, normal); // Third vertex normal */
    /*  */
    /* return; */
    vec3 ns[3];  // Normals
    vec3 d[3];   // Directions toward light
    vec4 v[4];  // Temporary vertices

    ns[0] = GetNormal(2, 0, 4);
    ns[0] = GetNormal(4, 2, 0);
    ns[0] = GetNormal(0, 4, 2);

    // Compute direction from vertices to light.
    d[0] = direct_light_direction.xyz;
    d[1] = direct_light_direction.xyz;
    d[2] = direct_light_direction.xyz;

    // Check if the main triangle faces the light.
    bool faces_light = !(dot(ns[0] ,d[0]) > 0 || dot(ns[1] , d[1]) > 0 || dot(ns[2] , d[2]) >0);
    if (!faces_light) {
        return;
    }

    // Loop over all edges and extrude if needed.
    for ( int i=0; i<3; i++ ) {
        // Compute indices of neighbor triangle.
        int v0 = i*2;
        int nb = (i*2+1);
        int v1 = (i*2+2) % 6;
        // Compute normals at vertices, the *exact*
        // same way as done above!
        ns[0] = cross(
                gl_in[nb].gl_Position.xyz-gl_in[v0].gl_Position.xyz,
                gl_in[v1].gl_Position.xyz-gl_in[v0].gl_Position.xyz);
        ns[1] = cross(
                gl_in[v1].gl_Position.xyz-gl_in[nb].gl_Position.xyz,
                gl_in[v0].gl_Position.xyz-gl_in[nb].gl_Position.xyz);
        ns[2] = cross(
                gl_in[v0].gl_Position.xyz-gl_in[v1].gl_Position.xyz,
                gl_in[nb].gl_Position.xyz-gl_in[v1].gl_Position.xyz);
        // Compute direction to light, again as above.
        d[0] = direct_light_direction.xyz;
        d[1] = direct_light_direction.xyz;
        d[2] = direct_light_direction.xyz;
        // Extrude the edge if it does not have a
        // neighbor, or if it's a possible silhouette.
        /* if (gl_in[nb].gl_Position.w < 1e-3 || */
        /*         ( faces_light != (dot(ns[0],d[0])>0 || */
        /*                           dot(ns[1],d[1])>0 || */
        /*                           dot(ns[2],d[2])>0) )) */
        /* { */
            // Make sure sides are oriented correctly.
            int i0 = faces_light ? v0 : v1;
            int i1 = faces_light ? v1 : v0;
            /*
            v[0] = gl_in[i0].gl_Position;
            v[1] = vec4(direct_light_direction*gl_in[i0].gl_Position);
            v[2] = gl_in[i1].gl_Position;
            v[3] = vec4(direct_light_direction*gl_in[i1].gl_Position);
            // Emit a quad as a triangle strip.
            gl_Position = v[0];
            EmitVertex();
            gl_Position = v[1];
            EmitVertex();
            gl_Position = v[2];
            EmitVertex();
            gl_Position = v[3];
            EmitVertex();
            EndPrimitive();
            */
            gl_Position = gl_in[v0].gl_Position;
            EmitVertex();
            gl_Position = gl_in[nb].gl_Position;
            EmitVertex();
            gl_Position = gl_in[v1].gl_Position;
            EmitVertex();
            EndPrimitive();
        /* } */
    }
}
