#include <iostream>
#include <glm/glm.hpp>
using namespace glm;


int main()
{
    //3차원 상의 평면과 직선의 교점
    //평면 상의 한 점 p0과 평면의 법선벡터 n, 직선상의 두 점 p1, p2의 각 원소
    //출력은 평면과 직선의 교점의 x y z 좌표값
    float p0x, p0y, p0z, nx, ny, nz, p1x, p1y, p1z, p2x, p2y, p2z;
    std::cin >> p0x >> p0y >> p0z >> nx >> ny >> nz >> p1x >> p1y >> p1z >> p2x >> p2y >> p2z;
    vec3 p0(p0x, p0y, p0z);
    vec3 p1(p1x, p1y, p1z);
    vec3 p2(p2x, p2y, p2z);
    vec3 n(nx, ny, nz);
    n = normalize(n);
    vec3 L = p2 - p1;
    float a = dot(p0 - p1, n) / dot(L, n);
    vec3 p = p1 + (a * L);
    printf("X : %f, Y : %f, Z : %f", p.x, p.y, p.z);
}