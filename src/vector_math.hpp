#ifndef VECTOR_MATH_HPP
#define VECTOR_MATH_HPP

class vec3 {
public:
	float x, y, z;
	vec3();
	vec3(float x, float y, float z);
	vec3(const vec3& o){ x = o.x; y = o.y; z = o.z; }
};

class vec4 {
public:
	float x, y, z, w;
	vec4();
	vec4(float x, float y, float z, float w);
	vec4(const vec4& o){ x = o.x; y = o.y; z = o.z; w = o.w; }
	float& operator [](unsigned idx);
};

class mat4 {
public:
	float data[16];
	mat4();
	float& operator [](unsigned idx);
	mat4& operator *(mat4& o);
	vec4  operator *(vec4& o);
	mat4& scale(float x, float y, float z);
	mat4& translate(float x, float y, float z);
	static mat4 identity();
	static mat4 invert(mat4& m);
	static mat4 lookAt(vec3 eye, vec3 center, vec3 up);
	static mat4 perspective(float fov, float aspect, float near, float far);
};

#endif
