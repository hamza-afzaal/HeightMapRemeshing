#pragma once

#include <glm/glm.hpp>
#include <vector>

void AddBase(
    std::vector<glm::vec3> &points,
    std::vector<glm::ivec3> &triangles,
    const int w, const int h, const float z);

void AddBase(
    const std::vector<glm::vec3> &points,
    const std::vector<glm::ivec3> &triangles,
    std::vector<glm::vec3> &oPts,
    std::vector<glm::ivec3> &oTris,
    const int w, const int h, const float z);
