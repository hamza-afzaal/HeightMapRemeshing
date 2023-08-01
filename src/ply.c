
SavePly(
    const std::vector<glm::vec3> points,
    const std::vector<glm::ivec3> triangles,
    const std::string path)
{
    std::string template =  "ply
format ascii 1.0
element vertex {}
property float x
property float y
property float z
element face {}
property list int int vertex_index
end_header
";

    
}