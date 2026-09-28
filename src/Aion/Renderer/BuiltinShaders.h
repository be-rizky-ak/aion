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
            uniform sampler2D u_EmissiveTexture;
            uniform vec4 u_BaseColor;
            uniform vec3 u_EmissiveFactor;
            uniform float u_AlphaCutoff;
            uniform int u_AlphaMode;

            out vec4 FragColor;

            void main()
            {
                vec4 texColor = texture(u_BaseColorTexture, v_UV) * u_BaseColor;

                if (u_AlphaMode == 1 && texColor.a < u_AlphaCutoff) {
                    discard;
                }

                vec3 emissive = texture(u_EmissiveTexture, v_UV).rgb * u_EmissiveFactor;
                vec3 finalColor = texColor.rgb + emissive;

                FragColor = vec4(finalColor, texColor.a);
            }
        )";

    } // namespace Shaders
} // namespace Aion