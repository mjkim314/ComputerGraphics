#include <iostream>
#include <glm/glm.hpp>
using namespace glm;

int main()
{
    //콘솔로 부터 세 벡터( a, b, c)의 각 원소(ax ay az bx by bz cx cy cz)을 입력 받습니다. 
    // 이때, 각각은 실수형이고, space로 구분되어 있습니다.
    // 평행육면체의 부피를 콘솔에 출력합니다.
    float ax, ay, az, bx, by, bz, cx, cy, cz;
    std::cin >> ax >> ay >> az >> bx >> by >> bz >> cx >> cy >> cz;
    vec3 a(ax, ay, az);
    vec3 b(bx, by, bz);
    vec3 c(cx, cy, cz);
    float A = dot(cross(a, b), c);
    A = abs(A);
    printf("%f", A);
}