#include <iostream>

// struct mat 
// {
// 	double mat[3][3];
// }

struct vec
{
	double x;
	double y;
	vec(double x, double y) : x(x), y(y) {}
};

vec operator+(const vec& v0, const vec& v1){
	return vec(v0.x + v1.x, v0.y + v1.y);
}

vec operator*(double s, const vec& v0) {
	return vec(v0.x*s, v0.y*s);}

vec operator*(double s[3][3], const vec& v0) {
	return vec(30, 30);
}

int main() {
	vec vec1(3,4);
	vec vec2(2,3);
	vec vec3 = vec1 + vec2;
	std::cout<< vec3.x << vec3.y;
}

