#include "vector_math.hpp"
#include <ostream>
#include <cmath>

#define EPSILON 0.000001f
#define hypot(a, b, c) (a*a + b*b + c*c)

/***********************************************/
/*                  VECTOR 3                   */
/***********************************************/

vec3::vec3(){
	this->x = 0.0f;
	this->y = 0.0f;
	this->z = 0.0f;
}

vec3::vec3(float x, float y, float z){
	this->x = x;
	this->y = y;
	this->z = z;
}

/***********************************************/
/*                  VECTOR 4                   */
/***********************************************/

vec4::vec4(){
	x = y = z = w = 0.0f;
}

vec4::vec4(float x, float y, float z, float w){
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

float& vec4::operator [](unsigned idx){
	switch(idx){
		case 0: return x;
		case 1: return y;
		case 2: return z;
		case 3: return w;
	}
	throw std::invalid_argument("Invalid index: %i");
}

/***********************************************/
/*                  MATRIX 3                   */
/***********************************************/


/***********************************************/
/*                  MATRIX 4                   */
/***********************************************/

mat4::mat4(){
	for(int i=0; i<16; i++) this->data[i] = 0.0f;
}

float& mat4::operator [](unsigned idx){
	return this->data[idx];
}

mat4& mat4::operator *(mat4& o){
	mat4 ret;
	for(int r=0; r<4; r++)
		for(int c=0; c<4; c++)
			for(int n=0; n<4; n++)
				ret[r*4+c] += this->data[r*4+n] * o[n*4+c];
	for(int i=0; i<16; i++) this->data[i] = ret[i];
	return *this;
}

vec4 mat4::operator *(vec4& o){
	vec4 ret;
	for(int i=0; i<4; i++)
		for(int j=0; j<4; j++)
			for(int n=0; n<4; n++) ret[j] += data[i*4+n] * o[n];
	return ret;
}

mat4& mat4::scale(float x, float y, float z){
	mat4 rhs;
	rhs[0] = x; rhs[5] = y; rhs[10] = z; rhs[15] = 1.0f;
	return (*this) * rhs;
}

mat4& mat4::translate(float x, float y, float z){
	data[12] = data[0] * x + data[4] * y + data[8 ] * z + data[12];
    data[13] = data[1] * x + data[5] * y + data[9 ] * z + data[13];
    data[14] = data[2] * x + data[6] * y + data[10] * z + data[14];
    data[15] = data[3] * x + data[7] * y + data[11] * z + data[15];
	return *this;
}

// STATIC METHODS

mat4 mat4::identity(){
	mat4 ret;
	for(int i=0; i<4; i++)
		for(int j=0; j<4; j++) {
			if(i != j) continue;
			ret[i*4+j] = 1.0f;
		}
	return ret;
}

mat4 mat4::invert(mat4& m){
	float b00 = m[0] * m[5] - m[1] * m[4];
	float b01 = m[0] * m[6] - m[2] * m[4];
	float b02 = m[0] * m[7] - m[3] * m[4];
	float b03 = m[1] * m[6] - m[2] * m[5];
	float b04 = m[1] * m[7] - m[3] * m[5];
	float b05 = m[2] * m[7] - m[3] * m[6];
	float b06 = m[8] * m[13] - m[9] * m[12];
	float b07 = m[8] * m[14] - m[10] * m[12];
	float b08 = m[8] * m[15] - m[11] * m[12];
	float b09 = m[9] * m[14] - m[10] * m[13];
	float b10 = m[9] * m[15] - m[11] * m[13];
	float b11 = m[10] * m[15] - m[11] * m[14];
	float det = b00 * b11 - b01 * b10 + b02 * b09 + b03 * b08 - b04 * b07 + b05 * b06;
	if (det == 0.0f) return mat4::identity();
	det = 1.0f / det;
	mat4 ret;
	ret[0] = (m[5] * b11 - m[6] * b10 + m[7] * b09) * det;
	ret[1] = (m[2] * b10 - m[1] * b11 - m[3] * b09) * det;
	ret[2] = (m[13] * b05 - m[14] * b04 + m[15] * b03) * det;
	ret[3] = (m[10] * b04 - m[9] * b05 - m[11] * b03) * det;
	ret[4] = (m[6] * b08 - m[4] * b11 - m[7] * b07) * det;
	ret[5] = (m[0] * b11 - m[2] * b08 + m[3] * b07) * det;
	ret[6] = (m[14] * b02 - m[12] * b05 - m[15] * b01) * det;
	ret[7] = (m[8] * b05 - m[10] * b02 + m[11] * b01) * det;
	ret[8] = (m[4] * b10 - m[5] * b08 + m[7] * b06) * det;
	ret[9] = (m[1] * b08 - m[0] * b10 - m[3] * b06) * det;
	ret[10] = (m[12] * b04 - m[13] * b02 + m[15] * b00) * det;
	ret[11] = (m[9] * b02 - m[8] * b04 - m[11] * b00) * det;
	ret[12] = (m[5] * b07 - m[4] * b09 - m[6] * b06) * det;
	ret[13] = (m[0] * b09 - m[1] * b07 + m[2] * b06) * det;
	ret[14] = (m[13] * b01 - m[12] * b03 - m[14] * b00) * det;
	ret[15] = (m[8] * b03 - m[9] * b01 + m[10] * b00) * det;
  	return ret;
}

mat4 mat4::lookAt(vec3 eye, vec3 center, vec3 up){
	if(std::abs(eye.x - center.x) < EPSILON &&
		std::abs(eye.y - center.y) < EPSILON &&
		std::abs(eye.z - center.z) < EPSILON) return mat4::identity();
	float z0 = eye.x - center.x;
	float z1 = eye.y - center.y;
	float z2 = eye.z - center.z;
	float len = 1 / hypot(z0, z1, z2);
	z0 *= len;
	z1 *= len;
	z2 *= len;
	float x0 = up.y * z2 - up.z * z1;
	float x1 = up.z * z0 - up.x * z2;
	float x2 = up.x * z1 - up.y * z0;
	len = hypot(x0, x1, x2);
	if(len == 0) x0 = x1 = x2 = 0;
	else {
		len = 1 / len;
		x0 *= len;
		x1 *= len;
		x2 *= len;
	}
	float y0 = z1 * x2 - z2 * x1;
	float y1 = z2 * x0 - z0 * x2;
	float y2 = z0 * x1 - z1 * x0;
	len = hypot(y0, y1, y2);
	if(!len) y0 = y1 = y2 = 0;
	else{
		len = 1 / len;
		y0 *= len;
		y1 *= len;
		y2 *= len;
	}
	mat4 ret;
	ret[0] = x0;
	ret[1] = y0;
	ret[2] = z0;
	ret[4] = x1;
	ret[5] = y1;
	ret[6] = z1;
	ret[8] = x2;
	ret[9] = y2;
	ret[10] = z2;
	ret[12] = -(x0 * eye.x + x1 * eye.y + x2 * eye.z);
	ret[13] = -(y0 * eye.x + y1 * eye.y + y2 * eye.z);
	ret[14] = -(z0 * eye.x + z1 * eye.y + z2 * eye.z);
	ret[15] = 1;
	return ret;
}

mat4 mat4::perspective(float fov, float aspect, float near, float far){
	float a = 1.0f / std::tan(fov/2);
	float b = a / aspect;
	float fsn = far-near, fan = far+near;
	float c = -fan/fsn;
	float d = -2*far*near/fsn;
	mat4 ret;
	ret[ 0] = a;
	ret[ 5] = b;
	ret[10] = c;
	ret[11] = d;
	ret[14] = -1;
	return ret;
}
