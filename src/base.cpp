#include "base.h"

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/gtx/hash.hpp>
#include <map>
#include <unordered_map>

void AddBase(
    std::vector<glm::vec3> &points,
    std::vector<glm::ivec3> &triangles,
    const int w, const int h, const float z)
{
    const int w1 = w - 1;
    const int h1 = h - 1;

    std::map<int, float> x0s;
    std::map<int, float> x1s;
    std::map<int, float> y0s;
    std::map<int, float> y1s;
    std::unordered_map<glm::vec3, int> lookup;

    // find points along each edge
    for (int i = 0; i < points.size(); i++) {
        const auto &p = points[i];
        bool edge = false;
        if (p.x == 0) {
            x0s[p.y] = p.z;
            edge = true;
        } else if (p.x == w1) {
            x1s[p.y] = p.z;
            edge = true;
        }
        if (p.y == 0) {
            y0s[p.x] = p.z;
            edge = true;
        } else if (p.y == h1) {
            y1s[p.x] = p.z;
            edge = true;
        }
        if (edge) {
            lookup[p] = i;
        }
    }

    std::vector<std::pair<int, float>> sx0s(x0s.begin(), x0s.end());
    std::vector<std::pair<int, float>> sx1s(x1s.begin(), x1s.end());
    std::vector<std::pair<int, float>> sy0s(y0s.begin(), y0s.end());
    std::vector<std::pair<int, float>> sy1s(y1s.begin(), y1s.end());

    const auto pointIndex = [&lookup, &points](
        const float x, const float y, const float z)
    {
        const glm::vec3 point(x, y, z);
        if (lookup.find(point) == lookup.end()) {
            lookup[point] = points.size();
            points.push_back(point);
        }
        return lookup[point];
    };

    // compute base center point
    const int center = pointIndex(w * 0.5f, h * 0.5f, z);

    // edge x = 0
    for (int i = 1; i < sx0s.size(); i++) {
        const int y0 = sx0s[i-1].first;
        const int y1 = sx0s[i].first;
        const float z0 = sx0s[i-1].second;
        const float z1 = sx0s[i].second;
        const int p00 = pointIndex(0, y0, z);
        const int p01 = pointIndex(0, y0, z0);
        const int p10 = pointIndex(0, y1, z);
        const int p11 = pointIndex(0, y1, z1);
        triangles.emplace_back(p01, p10, p00);
        triangles.emplace_back(p01, p11, p10);
        triangles.emplace_back(center, p00, p10);
    }

    // edge x = w1
    for (int i = 1; i < sx1s.size(); i++) {
        const int y0 = sx1s[i-1].first;
        const int y1 = sx1s[i].first;
        const float z0 = sx1s[i-1].second;
        const float z1 = sx1s[i].second;
        const int p00 = pointIndex(w1, y0, z);
        const int p01 = pointIndex(w1, y0, z0);
        const int p10 = pointIndex(w1, y1, z);
        const int p11 = pointIndex(w1, y1, z1);
        triangles.emplace_back(p00, p10, p01);
        triangles.emplace_back(p10, p11, p01);
        triangles.emplace_back(center, p10, p00);
    }

    // edge y = 0
    for (int i = 1; i < sy0s.size(); i++) {
        const int x0 = sy0s[i-1].first;
        const int x1 = sy0s[i].first;
        const float z0 = sy0s[i-1].second;
        const float z1 = sy0s[i].second;
        const int p00 = pointIndex(x0, 0, z);
        const int p01 = pointIndex(x0, 0, z0);
        const int p10 = pointIndex(x1, 0, z);
        const int p11 = pointIndex(x1, 0, z1);
        triangles.emplace_back(p00, p10, p01);
        triangles.emplace_back(p10, p11, p01);
        triangles.emplace_back(center, p10, p00);
    }

    // edge y = h1
    for (int i = 1; i < sy1s.size(); i++) {
        const int x0 = sy1s[i-1].first;
        const int x1 = sy1s[i].first;
        const float z0 = sy1s[i-1].second;
        const float z1 = sy1s[i].second;
        const int p00 = pointIndex(x0, h1, z);
        const int p01 = pointIndex(x0, h1, z0);
        const int p10 = pointIndex(x1, h1, z);
        const int p11 = pointIndex(x1, h1, z1);
        triangles.emplace_back(p01, p10, p00);
        triangles.emplace_back(p01, p11, p10);
        triangles.emplace_back(center, p00, p10);
    }
}


void AddBase(
    const std::vector<glm::vec3> &points,
    const std::vector<glm::ivec3> &triangles,
    std::vector<glm::vec3> &oPts,
    std::vector<glm::ivec3> &oTris,
    const int w, const int h, const float z)
{
    const int w1 = w - 1;
    const int h1 = h - 1;

    std::map<int, float> x0s;
    std::map<int, float> x1s;
    std::map<int, float> y0s;
    std::map<int, float> y1s;
    std::unordered_map<glm::vec3, int> lookup;
    std::vector<std::pair<glm::vec3, int>> lkp;

    // find points along each edge
    for (int i = 0; i < points.size(); i++) {
        const auto &p = points[i];
        bool edge = false;
        if (p.x == 0) {
            x0s[p.y] = p.z;
            edge = true;
        } else if (p.x == w1) {
            x1s[p.y] = p.z;
            edge = true;
        }
        if (p.y == 0) {
            y0s[p.x] = p.z;
            edge = true;
        } else if (p.y == h1) {
            y1s[p.x] = p.z;
            edge = true;
        }
        if (edge) {
            lookup[p] = i;
            lkp.push_back(std::pair(p, i));
        }
    }

    std::vector<std::pair<int, float>> sx0s(x0s.begin(), x0s.end());
    std::vector<std::pair<int, float>> sx1s(x1s.begin(), x1s.end());
    std::vector<std::pair<int, float>> sy0s(y0s.begin(), y0s.end());
    std::vector<std::pair<int, float>> sy1s(y1s.begin(), y1s.end());

    const auto pointIndex = [&lookup, &points, &oPts, &lkp](
        const float x, const float y, const float z)
    {
        const glm::vec3 point(x, y, z);
        if (lookup.find(point) == lookup.end()) { // this means that the point was not found? 
            lookup[point] = points.size() + oPts.size(); // this is changing the last point on the lookup table
            lkp.push_back(std::pair(point, points.size() + oPts.size()));
            oPts.push_back(point);
        }
        return lookup[point];
    };

    // compute base center point
    const int center = pointIndex(w * 0.5f, h * 0.5f, z);

    // edge x = 0
    for (int i = 1; i < sx0s.size(); i++) {
        const int y0 = sx0s[i-1].first;
        const int y1 = sx0s[i].first;
        const float z0 = sx0s[i-1].second;
        const float z1 = sx0s[i].second;
        const int p00 = pointIndex(0, y0, z);
        const int p01 = pointIndex(0, y0, z0);
        const int p10 = pointIndex(0, y1, z);
        const int p11 = pointIndex(0, y1, z1);
        oTris.emplace_back(p01, p10, p00);
        oTris.emplace_back(p01, p11, p10);
        oTris.emplace_back(center, p00, p10);
    }

    // edge x = w1
    for (int i = 1; i < sx1s.size(); i++) {
        const int y0 = sx1s[i-1].first;
        const int y1 = sx1s[i].first;
        const float z0 = sx1s[i-1].second;
        const float z1 = sx1s[i].second;
        const int p00 = pointIndex(w1, y0, z);
        const int p01 = pointIndex(w1, y0, z0);
        const int p10 = pointIndex(w1, y1, z);
        const int p11 = pointIndex(w1, y1, z1);
        oTris.emplace_back(p00, p10, p01);
        oTris.emplace_back(p10, p11, p01);
        oTris.emplace_back(center, p10, p00);
    }

    // edge y = 0
    for (int i = 1; i < sy0s.size(); i++) {
        const int x0 = sy0s[i-1].first;
        const int x1 = sy0s[i].first;
        const float z0 = sy0s[i-1].second;
        const float z1 = sy0s[i].second;
        const int p00 = pointIndex(x0, 0, z);
        const int p01 = pointIndex(x0, 0, z0);
        const int p10 = pointIndex(x1, 0, z);
        const int p11 = pointIndex(x1, 0, z1);
        oTris.emplace_back(p00, p10, p01);
        oTris.emplace_back(p10, p11, p01);
        oTris.emplace_back(center, p10, p00);
    }

    // edge y = h1
    for (int i = 1; i < sy1s.size(); i++) {
        const int x0 = sy1s[i-1].first;
        const int x1 = sy1s[i].first;
        const float z0 = sy1s[i-1].second;
        const float z1 = sy1s[i].second;
        const int p00 = pointIndex(x0, h1, z);
        const int p01 = pointIndex(x0, h1, z0);
        const int p10 = pointIndex(x1, h1, z);
        const int p11 = pointIndex(x1, h1, z1);
        oTris.emplace_back(p01, p10, p00);
        oTris.emplace_back(p01, p11, p10);
        oTris.emplace_back(center, p00, p10);
    }

    std::sort(lkp.begin(), lkp.end(), 
    [](std::pair<glm::vec3, int>& a, std::pair<glm::vec3, int>& b){
        return a.second < b.second;
    });

    oPts.clear();
    int i = 0;
    for (auto item : lkp)
    {
        if (i < item.second)
        {
            for (auto& tri : oTris)
            {
                if (tri.x == item.second)
                    tri.x = i;
                if (tri.y == item.second)
                    tri.y = i;
                if (tri.z == item.second)
                    tri.z = i;
            }
        }
        oPts.push_back(item.first);
        i++;
    }
}
