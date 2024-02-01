#ifndef MATH_UTIL_H
#define MATH_UTIL_H



float max(float a, float b);
float min(float a, float b);

float rad(float angle);
float deg(float rad);

float dot_product(float *a, float *b);
void cross_product(float* result, const float* a, const float* b);

void subtract_vectors(float* result, const float* vector1, const float* vector2);
void add_scaled_vector(float* result, const float* vector, const float* scale_vector, float scalar);

float qi_sqrt(float number);

float calculate_diagonal(float a, float b);



/* max
return higher value*/
float max(float a, float b) 
{
    return (a > b) ? a : b;
}


/* min
return lower value*/
float min(float a, float b) 
{
    if (a < b) return a; else return b;
}

/* clamp
clamp x to the range [a, b] */
float clamp(float x, float a, float b) {
    if (x < a) return a;
    if (x > b) return b;
    return x;
}

  
/* rad
angle to radians*/

float rad(float angle)
{
	return M_PI / 180 * angle;
}

/* deg
radians to angle*/

float deg(float rad)
{
	return 180 / M_PI * rad;
}


/*dot
returns dot product*/
float dot_product(float* a, float* b) 
{
    return a[0] * b[0] + a[1] * b[1] + a[2] * b[2]; 
}


/* cross_product
calculates the cross product of two 3D vectors */
void cross_product(float* result, const float* a, const float* b) {
    result[0] = a[1] * b[2] - a[2] * b[1];
    result[1] = a[2] * b[0] - a[0] * b[2];
    result[2] = a[0] * b[1] - a[1] * b[0];
}


/* subtract_vectors
substracts vectors */
void subtract_vectors(float* result, const float* vector1, const float* vector2)
{
    result[0] = vector1[0] - vector2[0];
    result[1] = vector1[1] - vector2[1];
    result[2] = vector1[2] - vector2[2];
}


/* add_scaled_vector
adds a scaled vector given the scalar */
void add_scaled_vector(float* result, const float* vector, const float* scale_vector, float scalar)
{
    result[0] = vector[0] + scalar * scale_vector[0];
    result[1] = vector[1] + scalar * scale_vector[1];
    result[2] = vector[2] + scalar * scale_vector[2];
}


void divide_vector_by_float(float* vector, float divisor)
{
    if (divisor != 0.0f) { // Ensure the divisor is not zero to avoid division by zero
        vector[0] /= divisor;
        vector[1] /= divisor;
        vector[2] /= divisor;
    } else {
        // Handle the case of division by zero, for example, by setting all components to zero
        vector[0] = 0.0f;
        vector[1] = 0.0f;
        vector[2] = 0.0f;
    }
}


/*qi_sqrt
quick inverse square root*/
float qi_sqrt(float number){

	long i;
	float x2, y;
	const float threehalfs = 1.5F;

	x2 = number * 0.5F;
	y  = number;
	i  = * ( long * ) &y;
	i  = 0x5f3759df - ( i >> 1 ); 
	y  = * ( float * ) &i;
	y  = y * ( threehalfs - ( x2 * y * y ) );   // 1st iteration
//	y  = y * ( threehalfs - ( x2 * y * y ) );   // 2nd iteration, this can be removed

	return y;
}


/* calculate diagonal
 calculates diagonal of a rect triangle given its sides */

float calculate_diagonal(float a, float b){
    float diagonal = 1 / qi_sqrt(a * a + b * b);
    return diagonal;
}

#endif