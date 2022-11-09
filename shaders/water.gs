#version 460 core

layout (points) in;
layout (triangle_strip, max_vertices = 256) out;
//layout (line_strip, max_vertices = 2) out;

const double M_PI = 3.1415926535897932384626433832795;
const float sectorCount = 8.0f;
const float stackCount = 5.0f;
const float radius = 0.005f;
const uint size = uint(sectorCount) * uint(stackCount) + 100u;

void main()
{
    float sectorStep = 2 * float(M_PI) / sectorCount;
    float stackStep = float(M_PI) / stackCount;
    float sectorAngle, stackAngle;

    float x, y, z, xy;
    vec4 vertices[size];
    uint counter = 0u;
    for(uint i = 0; i <= stackCount; ++i)
    {
        stackAngle = float(M_PI) / 2 - i * stackStep;        // starting from pi/2 to -pi/2
        xy = radius * cos(stackAngle);             // r * cos(u)
        z = radius * sin(stackAngle);              // r * sin(u)

        // add (sectorCount+1) vertices per stack
        // the first and last vertices have same position and normal, but different tex coords
        for(uint j = 0; j <= sectorCount; ++j)
        {
            sectorAngle = j * sectorStep;           // starting from 0 to 2pi

            x = xy * cos(sectorAngle);             // r * cos(u) * cos(v)
            y = xy * sin(sectorAngle);             // r * cos(u) * sin(v)

            // normalized vertex normal (nx, ny, nz)
            //nx = x * lengthinv;
            //ny = y * lengthinv;
            //nz = z * lengthinv;
            //normals.push_back(nx);
            //normals.push_back(ny);
            //normals.push_back(nz);

            // vertex tex coord (s, t) range between [0, 1]
            //s = (float)j / sectorCount;
            //t = (float)i / stackCount;
            //texCoords.push_back(s);
            //texCoords.push_back(t);

            vertices[counter] = gl_in[0].gl_Position + vec3(x, y, z);
            counter += 1u;
        }
    }
    uint k1, k2;
    for(uint i = 0; i < uint(stackCount); ++i)
    {
        k1 = i * (uint(sectorCount) + 1);     // beginning of current stack
        k2 = k1 + uint(sectorCount) + 1;      // beginning of next stack

        for(uint j = 0; j < uint(sectorCount); ++j, ++k1, ++k2)
        {
            // 2 triangles per sector excluding first and last stacks
            // k1 => k2 => k1+1
            if(i != 0)
            {
                gl_Position = vertices[k1];
                EmitVertex();
                gl_Position = vertices[k2];
                EmitVertex();
                gl_Position = vertices[k1 + 1];
                EmitVertex();
                //indices.push_back(k1);
                //indices.push_back(k2);
                //indices.push_back(k1 + 1);
            }

            // k1+1 => k2 => k2+1
            if(i != (uint(stackCount)-1))
            {
                gl_Position = vertices[k1 + 1];
                EmitVertex();
                gl_Position = vertices[k2];
                EmitVertex();
                gl_Position = vertices[k2 + 1];
                EmitVertex();
                //indices.push_back(k1 + 1);
                //indices.push_back(k2);
                //indices.push_back(k2 + 1);
            }

            // store indices for lines
            // vertical lines for all stacks, k1 => k2
            //lineIndices.push_back(k1);
            //lineIndices.push_back(k2);
            //if(i != 0)  // horizontal lines except 1st stack, k1 => k+1
            //{
            //    lineIndices.push_back(k1);
            //    lineIndices.push_back(k1 + 1);
            //}
        }
    }
    EndPrimitive();
/*
    gl_Position = gl_in[0].gl_Position;
    EmitVertex();
    gl_Position = gl_in[0].gl_Position - vec4(0.0, 0.05, 0.0, 0.0);
    EndPrimitive();
*/
}