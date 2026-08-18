// ---------------------------------------------------------------------------------------
// quark_math.h - C99 single file math library for game development
// ---------------------------------------------------------------------------------------

/*
------------------------------------------------------------------------------------------
License Information
------------------------------------------------------------------------------------------

MIT License

Copyright (c) 2026 Lucas LaMarr

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

------------------------------------------------------------------------------------------
Using quark_math
------------------------------------------------------------------------------------------

quark_math has been compiled and checked with the following compilers
- MSVC (19.51.36252)
- GCC (16.1.0)

Just drag and drop quark_math.h into your project and start using it.
No extra installation or tooling required!

Because quark_math does not contain a dedicated quark_math.c implementation
file it must have a single translation unit to contain both the declarations
and definitions. This can be done quite easily by just writing the following
inside of your main entry point file.

#define QUARK_MATH_IMPLEMENTATION
#include "quark_math.h"

This just gives your main translation unit access to the entire quark_math.h
library and knows both the declaration signatures as well as the definitions.
Any other translation units that use the library can simply include the
header file like normal and does not need to have any additional macro added.
*/

#ifdef _WIN32

#ifndef QUARK_MATH_H
#define QUARK_MATH_H

#ifdef __cplusplus
extern "C" {
#endif

// ---------------------------------------------------------------------------------------
// Dependencies
// ---------------------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h> 

// ---------------------------------------------------------------------------------------
// Constants
// ---------------------------------------------------------------------------------------

#define QUARK_PI 3.14159265f // Universal ratio of a circles circumference to its diameter

// ---------------------------------------------------------------------------------------
// Structs
// ---------------------------------------------------------------------------------------

// Represents two related floats
typedef struct quark_vec2
{
	float x;
	float y;
} quark_vec2;

// Represents a rectangle in a 2D space
typedef struct quark_rect
{
	quark_vec2 position; // Starting horizontal and vertical position
	quark_vec2 size;     // Width and height
} quark_rect;


// ---------------------------------------------------------------------------------------
// Forward Declarations
// ---------------------------------------------------------------------------------------

extern float quark_min(float a, float b);                    // Returns the smaller of the two numbers
extern float quark_max(float a, float b);                    // Returns the larger of the two numbers
extern float quark_abs(float value);                         // Returns the absolute value of a number
extern float quark_pow(float value, int exponent);           // Returns a value multiplied by an exponent 
extern float quark_sqrt(float value);                        // Returns the estimated square root of a number (Newton's method)
extern float quark_floor(float value);                       // Returns rounded down value
extern float quark_ceil(float value);                        // Returns rounded up value
extern float quark_trunc(float value);                       // Returns number with fractional value removed
extern float quark_clamp(float value, float min, float max); // Returns clamped number between a min and max value
extern float quark_lerp(float start, float end, float time); // Returns value moving between two points over time
extern float quark_frac(float value);                        // Returns only the fractional part of a number
extern float quark_deg_to_rad(float deg);                    // Returns degrees converted to radians
extern float quark_rad_to_deg(float rad);                    // Returns radians converted to degrees
extern int quark_signed(float value);                        // Returns 1 if signed or 0 if unsigned

extern quark_vec2 quark_vec2_add(quark_vec2 a, quark_vec2 b);         // Returns the sum of two quark_vec2
extern quark_vec2 quark_vec2_subtract(quark_vec2 a, quark_vec2 b);    // Returns difference of two quark_vec2
extern quark_vec2 quark_vec2_mult(quark_vec2 a, quark_vec2 b);        // Returns product of two quark_vec2
extern quark_vec2 quark_vec2_mult_scalar(quark_vec2 a, float scalar); // Returns product of a quark_vec2 using scalar multiplication
extern quark_vec2 quark_vec2_div_scalar(quark_vec2 a, float scalar);  // Returns quotient of a quark_vec2 using scalar division
extern float quark_vec2_dot(quark_vec2 a, quark_vec2 b);              // Returns a value determined by how close two quark_vec2 are
extern float quark_vec2_magnitude(quark_vec2 vec);                    // Returns the length of a quark_vec2
extern float quark_vec2_distance(quark_vec2 a, quark_vec2 b);         // Returns the distance between between two quark_vec2
extern int quark_vec2_compare(quark_vec2 a, quark_vec2 b);            // Returns 1 if the two vectors are the same

#ifdef __cplusplus
}
#endif // extern "C"
#endif // QUARK_MATH_H


#ifdef QUARK_MATH_IMPLEMENTATION
#ifndef QUARK_MATH_IMPLEMENTATION_INCLUDED
#define QUARK_MATH_IMPLEMENTATION_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

// ---------------------------------------------------------------------------------------
// Definitions
// ---------------------------------------------------------------------------------------

float quark_min(float a, float b)
{
	return (a < b) ? a : b;
}

float quark_max(float a, float b)
{
	return (a > b) ? a : b;
}

float quark_abs(float value)
{
	return (value < 0.0f) ? -value : value;
}

float quark_pow(float value, int exponent)
{
	float result = 1.0f;

	if (exponent == 0)
	{
		return result;
	}

	int count = exponent;

	if (exponent < 0)
	{
		count = -exponent;
	}

	for (int i = 0; i < count; i++)
	{
		result *= value;
	}

	if (exponent < 0)
	{
		return 1.0f / result;
	}

	return result;
}

float quark_sqrt(float value)
{
	if (value <= 0.0f)
	{
		return 0.0f;
	}

	float estimate = value;

	for (int i = 0; i < 10; i++)
	{
		estimate = (estimate + value / estimate) / 2;
	}

	return estimate;
}

float quark_floor(float value)
{
	long long truncatedValue = (long long)value;

	if (value < (float)truncatedValue)
	{
		truncatedValue--;
	}

	return (float)truncatedValue;
}

float quark_ceil(float value)
{
	long long truncated = (long long)value;

	if (value > (float)truncated)
	{
		truncated++;
	}

	return (float)truncated;
}

float quark_trunc(float value)
{
	return (float)(long long)value;
}

float quark_clamp(float value, float min, float max)
{
	if (value < min)
	{
		return min;
	}

	else if (value > max)
	{
		return max;
	}

	return value;
}

float quark_lerp(float start, float end, float time)
{
	return start + (end - start) * time;
}

float quark_frac(float value)
{
	return value - quark_floor(value);
}

float quark_deg_to_rad(float deg)
{
	return deg * (QUARK_PI / 180.0f);
}

float quark_rad_to_deg(float rad)
{
	return rad * (180.0f / QUARK_PI);
}

int quark_signed(float value)
{
	return (value < 0.0f) ? 1 : 0;
}

quark_vec2 quark_vec2_add(quark_vec2 a, quark_vec2 b)
{
	quark_vec2 temp =
	{
		a.x + b.x,
		a.y + b.y
	};

	return temp;
}

quark_vec2 quark_vec2_subtract(quark_vec2 a, quark_vec2 b)
{
	quark_vec2 temp =
	{
		a.x - b.x,
		a.y - b.y
	};

	return temp;
}

quark_vec2 quark_vec2_mult(quark_vec2 a, quark_vec2 b)
{
	quark_vec2 temp =
	{
		a.x * b.x,
		a.y * b.y
	};

	return temp;
}

quark_vec2 quark_vec2_mult_scalar(quark_vec2 a, float scalar)
{
	quark_vec2 temp =
	{
		a.x * scalar,
		a.y * scalar
	};

	return temp;
}

quark_vec2 quark_vec2_div_scalar(quark_vec2 a, float scalar)
{
	if (scalar == 0.0f)
	{
		return a;
	}

	quark_vec2 temp =
	{
		a.x / scalar,
		a.y / scalar
	};

	return temp;
}

int quark_vec2_compare(quark_vec2 a, quark_vec2 b)
{
	return (a.x == b.x && a.y == b.y) ? 1 : 0;
}

float quark_vec2_dot(quark_vec2 a, quark_vec2 b)
{
	return (a.x * b.x) + (a.y * b.y);
}

float quark_vec2_magnitude(quark_vec2 vec)
{
	return quark_sqrt(quark_vec2_dot(vec, vec));
}

float quark_vec2_distance(quark_vec2 a, quark_vec2 b)
{
	quark_vec2 distance =
	{
		b.x - a.x,
		b.y - a.y
	};

	return quark_vec2_magnitude(distance);
}
#ifdef __cplusplus
}
#endif // extern "C"
#endif // QUARK_MATH_IMPLEMENTATION_INCLUDED 
#endif // QUARK_MATH_IMPLEMENTATION 

#endif