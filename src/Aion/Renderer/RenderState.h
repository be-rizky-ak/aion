#pragma once

namespace Aion
{

    enum class DepthFunc
    {
        Never,
        Less,
        Equal,
        LEqual,
        Greater,
        NotEqual,
        GEqual,
        Always
    };

    enum class CullMode
    {
        None,
        Front,
        Back,
        FrontAndBack
    };

    enum class BlendFactor
    {
        Zero,
        One,
        SrcColor,
        OneMinusSrcColor,
        SrcAlpha,
        OneMinusSrcAlpha,
        DstAlpha,
        OneMinusDstAlpha
    };

    struct RenderState
    {
        bool DepthTest = true;
        bool DepthWrite = true;
        DepthFunc DepthFunction = DepthFunc::LEqual;

        CullMode CullingMode = CullMode::Back;

        bool BlendEnable = false;
        BlendFactor SrcBlend = BlendFactor::SrcAlpha;
        BlendFactor DstBlend = BlendFactor::OneMinusSrcAlpha;
    };

} // namespace Aion