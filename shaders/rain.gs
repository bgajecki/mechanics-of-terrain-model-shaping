#version 460 core

layout (points) in;
layout (triangle_strip, max_vertices = 100) out;
//layout (line_strip, max_vertices = 2) out;

uniform mat4 mvp;

const double M_PI = 3.1415926535897932384626433832795;
const uint circleVertices = 10u;
const float scale = 0.01;
const float circlePiece = float(2.0 * M_PI) / float(circleVertices);

void main()
{
    vec4 circleCenterPosition, bottom, up;
    circleCenterPosition = gl_in[0].gl_Position + vec4(0.0, scale, 0.0, 0.0);
    bottom = gl_in[0].gl_Position;
    up = gl_in[0].gl_Position + vec4(0.0, scale * 4.0, 0.0, 0.0);

    float x, z, piece;
    for(uint i = 0; i <= circleVertices; i++)
    {

        if(i + 1 != circleVertices)
        {
            // Bottom
            gl_Position = mvp * bottom;
            EmitVertex();
            piece = circlePiece * i;
        
            z = sin(piece);
            x = cos(piece);

            gl_Position = mvp * (circleCenterPosition + (vec4(x, 0.0, z, 0.0) * scale));
            EmitVertex();

            piece = circlePiece * (i + 1);
        
            z = sin(piece);
            x = cos(piece);

            gl_Position = mvp * (circleCenterPosition + (vec4(x, 0.0, z, 0.0) * scale));
            EmitVertex();
            EndPrimitive();

            // Up
            gl_Position = mvp * up;
            EmitVertex();
            piece = circlePiece * i;
        
            z = cos(piece);
            x = sin(piece);

            gl_Position = mvp * (circleCenterPosition + (vec4(x, 0.0, z, 0.0) * scale));
            EmitVertex();

            piece = circlePiece * (i + 1);
        
            z = cos(piece);
            x = sin(piece);

            gl_Position = mvp * (circleCenterPosition + (vec4(x, 0.0, z, 0.0) * scale));
            EmitVertex();

            EndPrimitive();

        }
        else
        {
            // Bottom
            gl_Position = mvp * bottom;
            EmitVertex();
            piece = circlePiece * i;
        
            z = sin(piece);
            x = cos(piece);

            gl_Position = mvp * (circleCenterPosition + (vec4(x, 0.0, z, 0.0) * scale));
            EmitVertex();

            piece = 0;
        
            z = sin(piece);
            x = cos(piece);

            gl_Position = mvp * (circleCenterPosition + (vec4(x, 0.0, z, 0.0) * scale));
            EmitVertex();

            EndPrimitive();

            // Up
            gl_Position = mvp * up;
            EmitVertex();
            piece = circlePiece * i;
        
            z = cos(piece);
            x = sin(piece);

            gl_Position = mvp * (circleCenterPosition + (vec4(x, 0.0, z, 0.0) * scale));
            EmitVertex();

            piece = 0;
        
            z = cos(piece);
            x = sin(piece);

            gl_Position = mvp * (circleCenterPosition + (vec4(x, 0.0, z, 0.0) * scale));
            EmitVertex();

            EndPrimitive();
        }
    }
}