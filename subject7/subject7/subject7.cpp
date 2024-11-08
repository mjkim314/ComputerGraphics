#include <iostream>
#include <glm/glm.hpp>
using namespace glm;

int main(){
	float a, b, c, d, e, f;
	std::cin >> a >> b >> c >> d >> e >> f;
	vec3 v1(a, b, c), v2(d, e, f);
	float cos_theta = dot(normalize(v1), normalize(v2));
	float radian = acos(cos_theta);
	float degree = degrees(radian);
	printf("%f", degree);
}
