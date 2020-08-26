#ifndef VECTOR_MATH_HPP
#define VECTOR_MATH_HPP

class vec3 {
public:
	float x, y, z;
	vec3();
	vec3(float x, float y, float z);
};

class vec4 {
public:
	float x, y, z, w;
};

class mat4 {
public:
	float data[16];
	mat4();
	float& operator [](unsigned idx);
	mat4 operator *(mat4& o);
	static mat4 identity();
	static mat4 perspective(float fov, float aspect, float near, float far);
};

#endif
