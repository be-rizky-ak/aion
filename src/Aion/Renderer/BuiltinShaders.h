#pragma once

namespace Aion
{

    namespace Shaders
    {

        inline const char* StandardVertex = R"(
            #version 330 core

            layout(location=0) in vec3 aPos;
            layout(location=1) in vec3 aNormal;
            layout(location=2) in vec2 aUV;

            uniform mat4 u_MVP;

            out vec2 v_UV;

            void main()
            {
                v_UV = aUV;
                gl_Position = u_MVP * vec4(aPos, 1.0);
            }
        )";

        inline const char* StandardFragment = R"(
            #version 330 core

            in vec2 v_UV;

            uniform sampler2D u_BaseColorTexture;
            uniform vec4 u_BaseColor;

            out vec4 FragColor;

            void main()
            {
                vec4 tex = texture(u_BaseColorTexture, v_UV);
                FragColor = tex * u_BaseColor;
            }
        )";

    } // namespace Shaders
} // namespace Aion