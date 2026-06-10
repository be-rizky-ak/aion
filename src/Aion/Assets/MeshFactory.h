#pragma once

#include "Mesh.h"

class Mesh;

class MeshFactory
{
  public:
    static Mesh* CreateCube();

    static Mesh* CreatePlane();

    static Mesh* CreateSphere();
};