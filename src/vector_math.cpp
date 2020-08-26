#include "vector_math.hpp"
#include <cmath>

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

mat4 mat4::operator *(mat4& o){
	mat4 res;
	for(int r=0; r<4; r++)
		for(int c=0; c<4; c++)
			for(int n=0; c<4; n++)
				res[r*4+c] += this->data[r*4+n] * o[n*4+c];
	return res;
}

mat4 mat4::identity(){
	mat4 ret;
	for(int i=0; i<4; i++)
		for(int j=0; j<4; j++) {
			if(i != j) continue;
			ret[i*4+j] = 1.0;
		}
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
