#include "RenderCommand.h"
#include <glad/glad.h>

namespace Aion
{

    RenderState RenderCommand::s_CurrentState{};
    bool RenderCommand::s_Initialized = false;

    static GLenum DepthFuncToGL(DepthFunc func)
    {
        switch (func)
        {
        case DepthFunc::Never:
            return GL_NEVER;
        case DepthFunc::Less:
            return GL_LESS;
        case DepthFunc::Equal:
            return GL_EQUAL;
        case DepthFunc::LEqual:
            return GL_LEQUAL;
        case DepthFunc::Greater:
            return GL_GREATER;
        case DepthFunc::NotEqual:
            return GL_NOTEQUAL;
        case DepthFunc::GEqual:
            return GL_GEQUAL;
        case DepthFunc::Always:
            return GL_ALWAYS;
        }
        return GL_LEQUAL;
    }

    static GLenum BlendFactorToGL(BlendFactor factor)
    {
        switch (factor)
        {
        case BlendFactor::Zero:
            return GL_ZERO;
        case BlendFactor::One:
            return GL_ONE;
        case BlendFactor::SrcColor:
            return GL_SRC_COLOR;
        case BlendFactor::OneMinusSrcColor:
            return GL_ONE_MINUS_SRC_COLOR;
        case BlendFactor::SrcAlpha:
            return GL_SRC_ALPHA;
        case BlendFactor::OneMinusSrcAlpha:
            return GL_ONE_MINUS_SRC_ALPHA;
        case BlendFactor::DstAlpha:
            return GL_DST_ALPHA;
        case BlendFactor::OneMinusDstAlpha:
            return GL_ONE_MINUS_DST_ALPHA;
        }
        return GL_ONE;
    }

    void RenderCommand::Init()
    {
        glEnable(GL_DEPTH_TEST);
        glDepthMask(GL_TRUE);
        glDepthFunc(GL_LEQUAL);

        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);

        glDisable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        s_Initialized = true;
    }

    void RenderCommand::ApplyState(const RenderState& state)
    {
        if (!s_Initialized)
            Init();

        if (state.DepthTest != s_CurrentState.DepthTest)
        {
            state.DepthTest ? glEnable(GL_DEPTH_TEST) : glDisable(GL_DEPTH_TEST);
            s_CurrentState.DepthTest = state.DepthTest;
        }

        if (state.DepthWrite != s_CurrentState.DepthWrite)
        {
            glDepthMask(state.DepthWrite ? GL_TRUE : GL_FALSE);
            s_CurrentState.DepthWrite = state.DepthWrite;
        }

        if (state.DepthFunction != s_CurrentState.DepthFunction)
        {
            glDepthFunc(DepthFuncToGL(state.DepthFunction));
            s_CurrentState.DepthFunction = state.DepthFunction;
        }

        if (state.CullingMode != s_CurrentState.CullingMode)
        {
            if (state.CullingMode == CullMode::None)
            {
                glDisable(GL_CULL_FACE);
            }
            else
            {
                glEnable(GL_CULL_FACE);
                if (state.CullingMode == CullMode::Front)
                    glCullFace(GL_FRONT);
                else if (state.CullingMode == CullMode::Back)
                    glCullFace(GL_BACK);
                else if (state.CullingMode == CullMode::FrontAndBack)
                    glCullFace(GL_FRONT_AND_BACK);
            }
            s_CurrentState.CullingMode = state.CullingMode;
        }

        if (state.BlendEnable != s_CurrentState.BlendEnable)
        {
            state.BlendEnable ? glEnable(GL_BLEND) : glDisable(GL_BLEND);
            s_CurrentState.BlendEnable = state.BlendEnable;
        }

        if (state.SrcBlend != s_CurrentState.SrcBlend || state.DstBlend != s_CurrentState.DstBlend)
        {
            glBlendFunc(BlendFactorToGL(state.SrcBlend), BlendFactorToGL(state.DstBlend));
            s_CurrentState.SrcBlend = state.SrcBlend;
            s_CurrentState.DstBlend = state.DstBlend;
        }
    }

} // namespace Aion