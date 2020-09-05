#pragma once
#include "pt_util.h"



//taken from raytracing in a weekend. In the future I'll probably just drop in eigen

class vec3
{
public:
	vec3();
	vec3(double, double, double);
	~vec3();

	double x() const;
	double y() const;
	double z() const;

	vec3 operator-() const;
	double  operator[](int i) const;
	double& operator[](int i);

	vec3& operator+=(const vec3& v);
	vec3& operator*=(const double t);
	vec3& operator/=(const double t);

	double length() const;
	double length_squared() const;

	inline static vec3 random() 
	{
		return vec3(random_double(), random_double(), random_double());
	}

	inline static vec3 random(double min, double max) 
	{
		return vec3(random_double(min,max), random_double(min,max), random_double(min,max));
	}


public:
	double m_array[3];

};

inline vec3 operator+(const vec3 &u, const vec3 &v) 
{
	return vec3(u.m_array[0] + v.m_array[0], u.m_array[1] + v.m_array[1], u.m_array[2] + v.m_array[2]);
}

inline vec3 operator-(const vec3 &u, const vec3 &v) 
{
	return vec3(u.m_array[0] - v.m_array[0], u.m_array[1] - v.m_array[1], u.m_array[2] - v.m_array[2]);
}

inline vec3 operator*(const vec3 &u, const vec3 &v) {

	return vec3(u.m_array[0] * v.m_array[0], u.m_array[1] * v.m_array[1], u.m_array[2] * v.m_array[2]);
}

inline vec3 operator*(double t, const vec3 &v) 
{
	return vec3(t*v.m_array[0], t*v.m_array[1], t*v.m_array[2]);
}

inline vec3 operator*(const vec3 &v, double t) 
{
	return t * v;
}

inline vec3 operator/(vec3 v, double t) 
{
	return (1/t) * v;
}

inline double dot(const vec3 &u, const vec3 &v) 
{
	return u.m_array[0] * v.m_array[0]
		 + u.m_array[1] * v.m_array[1]
		 + u.m_array[2] * v.m_array[2];
}

inline vec3 cross(const vec3 &u, const vec3 &v) 
{
	return vec3(u.m_array[1] * v.m_array[2] - u.m_array[2] * v.m_array[1],
				u.m_array[2] * v.m_array[0] - u.m_array[0] * v.m_array[2],
				u.m_array[0] * v.m_array[1] - u.m_array[1] * v.m_array[0]);
}

inline vec3 unit_vector(vec3 v) 
{
	return v / v.length();
}

vec3 random_in_unit_sphere();
vec3 random_unit_vector();
vec3 random_in_unit_disk();
vec3 random_in_hemisphere(const vec3& normal);
vec3 reflect(const vec3& v, const vec3& n);
vec3 refract(const vec3& uv, const vec3& n, double etai_over_etat);


using Color  = vec3;
using Point3 = vec3;


