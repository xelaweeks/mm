#ifndef LIBC_MATH_H
#define LIBC_MATH_H

#define F_PI 3.14159265358979323846f
#define F_SQRT2 1.41421356237309504880f
#define F_SQRT1_2 0.70710678118654752440f /* 1/sqrt(2) */

#define MAXFLOAT 3.40282347e+38f
#define SHT_MAX 32767.0f
#define SHT_MINV (1.0f / SHT_MAX)

float fabsf(float f);
#pragma intrinsic(fabsf)
#ifdef __GNUC__
#define fabsf(f) __builtin_fabsf((float)(f))
#endif

double sqrt(double d);
#pragma intrinsic(sqrt)

float fmodf(float dividend, float divisor);

#endif
