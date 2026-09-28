#include <cassert>
#include <cmath>
#include <iostream>
#include <string>

// Include core trait headers
#include "aion/math/generic_math.hpp"
#include "aion/string/string_utils.hpp"
#include "aion/path/path_utils.hpp"

// Include subsystem deprecation headers
#include "aion/rendering/render_math_utils.hpp"
#include "aion/physics/physics_math_helpers.hpp"
#include "aion/ui/ui_string_helpers.hpp"
#include "aion/io/path_utils.hpp"

#define TEST_ASSERT(condition, message) \
    do { \
        if (!(condition)) { \
            std::cerr << "Assertion failed: " << message << " at line " << __LINE__ << std::endl; \
            return false; \
        } \
    } while(0)

static bool TestMathTraitsAndRenderingWrappers()
{
    // Test Clamp
    float val = 15.0f;
    float clampedCore = Aion::Math::Clamp(val, 0.0f, 10.0f);
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
    float clampedRender = Aion::Rendering::RenderClamp(val, 0.0f, 10.0f);
#pragma GCC diagnostic pop
    TEST_ASSERT(clampedCore == 10.0f, "Clamp core value");
    TEST_ASSERT(clampedCore == clampedRender, "RenderClamp matches Clamp");

    // Test Lerp float
    float lerpCore = Aion::Math::Lerp(0.0f, 100.0f, 0.25f);
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
    float lerpRender = Aion::Rendering::RenderLerp(0.0f, 100.0f, 0.25f);
#pragma GCC diagnostic pop
    TEST_ASSERT(lerpCore == 25.0f, "Lerp core float");
    TEST_ASSERT(lerpCore == lerpRender, "RenderLerp matches Lerp");

    // Test Lerp Vector3
    Aion::Vector3 v1(0.0f, 10.0f, 20.0f);
    Aion::Vector3 v2(10.0f, 30.0f, 50.0f);
    Aion::Vector3 vLerpCore = Aion::Math::Lerp(v1, v2, 0.5f);
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
    Aion::Vector3 vLerpRender = Aion::Rendering::RenderLerp(v1, v2, 0.5f);
#pragma GCC diagnostic pop
    TEST_ASSERT(vLerpCore == Aion::Vector3(5.0f, 20.0f, 35.0f), "Vector3 Lerp core");
    TEST_ASSERT(vLerpCore == vLerpRender, "RenderLerp Vector3 matches Lerp");

    // Test Matrix Transformations
    Aion::Vector3 trans(1.0f, 2.0f, 3.0f);
    Aion::Matrix4 mTransCore = Aion::Math::Translate(trans);
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
    Aion::Matrix4 mTransRender = Aion::Rendering::RenderTranslate(trans);
#pragma GCC diagnostic pop
    TEST_ASSERT(mTransCore[3].x == mTransRender[3].x && mTransCore[3].y == mTransRender[3].y && mTransCore[3].z == mTransRender[3].z, "RenderTranslate matches Translate");

    return true;
}

static bool TestPhysicsWrappers()
{
    Aion::Vector3 p1(0.0f, 0.0f, 0.0f);
    Aion::Vector3 p2(10.0f, 20.0f, 30.0f);
    Aion::Vector3 lerpCore = Aion::Math::Lerp(p1, p2, 0.5f);

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
    Aion::Vector3 lerpPhysics = Aion::Physics::PhysicsVector3Lerp(p1, p2, 0.5f);
    float scalarLerpPhysics = Aion::Physics::PhysicsLerp(0.0f, 100.0f, 0.75f);
    float clampPhysics = Aion::Physics::PhysicsClamp(-5.0f, 0.0f, 10.0f);
#pragma GCC diagnostic pop

    TEST_ASSERT(lerpCore == lerpPhysics, "PhysicsVector3Lerp matches Lerp core");
    TEST_ASSERT(scalarLerpPhysics == 75.0f, "PhysicsLerp scalar core");
    TEST_ASSERT(clampPhysics == 0.0f, "PhysicsClamp core");

    return true;
}

static bool TestStringTraitsAndUIWrappers()
{
    std::string formattedCore = Aion::String::Format("Score: %d, Name: %s", 100, "Aion");

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
    std::string formattedUI = Aion::UI::UIFormatString("Score: %d, Name: %s", 100, "Aion");
#pragma GCC diagnostic pop

    std::string formattedMacro = UI_FORMAT_STRING("Score: %d, Name: %s", 100, "Aion");
    std::string stringFormatMacro = UI_STRING_FORMAT("Value: %d", 42);
    std::string toStringMacro = UI_TO_STRING(12345);

    TEST_ASSERT(formattedCore == "Score: 100, Name: Aion", "Format core");
    TEST_ASSERT(formattedCore == formattedUI, "UIFormatString matches Format core");
    TEST_ASSERT(formattedCore == formattedMacro, "UI_FORMAT_STRING macro matches Format core");
    TEST_ASSERT(stringFormatMacro == "Value: 42", "UI_STRING_FORMAT macro");
    TEST_ASSERT(toStringMacro == "12345", "UI_TO_STRING macro");

    TEST_ASSERT(Aion::String::Trim("  hello world  ") == "hello world", "Trim");
    TEST_ASSERT(Aion::String::ToLower("AION Engine") == "aion engine", "ToLower");
    TEST_ASSERT(Aion::String::ToUpper("aion engine") == "AION ENGINE", "ToUpper");

    return true;
}

static bool TestPathTraitsAndIOWrappers()
{
    std::string rawPath = "assets\\\\models\\/DamagedHelmet.glb";
    std::string normCore = Aion::Path::Normalize(rawPath);

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
    std::string normIO = Aion::IO::NormalizePath(rawPath);
    std::string extIO = Aion::IO::GetPathExtension(rawPath);
    std::string nameIO = Aion::IO::GetPathFileName(rawPath);
    std::string combIO = Aion::IO::CombinePaths("assets/models", "DamagedHelmet.glb");
#pragma GCC diagnostic pop

    TEST_ASSERT(normCore == "assets/models/DamagedHelmet.glb", "Path Normalize core");
    TEST_ASSERT(normCore == normIO, "NormalizePath IO wrapper matches core");
    TEST_ASSERT(extIO == ".glb", "GetPathExtension");
    TEST_ASSERT(nameIO == "DamagedHelmet.glb", "GetPathFileName");
    TEST_ASSERT(combIO == "assets/models/DamagedHelmet.glb", "CombinePaths");

    return true;
}

int main()
{
    std::cout << "Running Aion Template Traits & Deprecation Wrapper Unit Tests..." << std::endl;

    if (!TestMathTraitsAndRenderingWrappers()) {
        std::cerr << "TestMathTraitsAndRenderingWrappers failed!" << std::endl;
        return 1;
    }
    if (!TestPhysicsWrappers()) {
        std::cerr << "TestPhysicsWrappers failed!" << std::endl;
        return 1;
    }
    if (!TestStringTraitsAndUIWrappers()) {
        std::cerr << "TestStringTraitsAndUIWrappers failed!" << std::endl;
        return 1;
    }
    if (!TestPathTraitsAndIOWrappers()) {
        std::cerr << "TestPathTraitsAndIOWrappers failed!" << std::endl;
        return 1;
    }

    std::cout << "All Aion trait and wrapper tests passed successfully!" << std::endl;
    return 0;
}
