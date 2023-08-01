#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <string>

void SavePly(
    const std::vector<glm::vec3> points,
    const std::vector<glm::ivec3> triangles,
    const std::string path
);