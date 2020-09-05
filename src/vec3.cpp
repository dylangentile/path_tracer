#include "vec3.h"


vec3::vec3() : m_array{0,0,0} {}
vec3::vec3(double x_, double y_, double z_) : m_array{x_, y_, z_} {}
vec3::~vec3(){}

double 
vec3::x() const
{
	return m_array[0];
}

double 
vec3::y() const
{
	return m_array[1];
}

double 
vec3::z() const
{
	return m_array[2];
}

vec3 
vec3::operator-() const
{
	return vec3(-m_array[0], -m_array[1], -m_array[2]);
}

double  
vec3::operator[](int i) const
{
	return m_array[i];
}

double& 
vec3::operator[](int i)
{
	return m_array[i];
}

vec3& 
vec3::operator+=(const vec3 &v) 
{
	m_array[0] += v.m_array[0];
	m_array[1] += v.m_array[1];
	m_array[2] += v.m_array[2];
	return *this;
}

vec3& 
vec3::operator*=(const double t) 
{
	m_array[0] *= t;
	m_array[1] *= t;
	m_array[2] *= t;
	return *this;
}

vec3& 
vec3::operator/=(const double t) 
{
	return *this *= 1/t;
}

double
vec3::length() const
{
	return std::sqrt(length_squared()); //pythagorean theorem
}

double
vec3::length_squared() const
{
	return (m_array[0] * m_array[0]) + (m_array[1] * m_array[1]) + (m_array[2] * m_array[2]);
}




vec3 random_in_unit_sphere() 
{
	while (true) 
	{
		auto p = vec3::random(-1,1);
		if (p.length_squared() >= 1) continue;
		return p;
	}
}

vec3 
random_unit_vector() 
{
	auto a = random_double(0, 2*M_PI);
	auto z = random_double(-1, 1);
	auto r = sqrt(1 - z*z);
	return vec3(r*cos(a), r*sin(a), z);
}

vec3 
random_in_hemisphere(const vec3& normal) 
{
	vec3 in_unit_sphere = random_in_unit_sphere();
	if (dot(in_unit_sphere, normal) > 0.0) // In the same hemisphere as the normal
		return in_unit_sphere;
	else
		return -in_unit_sphere;
}

vec3 
reflect(const vec3& v, const vec3& n) 
{
	return v - 2*dot(v,n)*n;
}

vec3 
refract(const vec3& uv, const vec3& n, double etai_over_etat) 
{
	auto cos_theta = dot(-uv, n);
	vec3 r_out_perp =  etai_over_etat * (uv + cos_theta*n);
	vec3 r_out_parallel = -sqrt(fabs(1.0 - r_out_perp.length_squared())) * n;
	return r_out_perp + r_out_parallel;
}

vec3 
random_in_unit_disk() 
{
	while (true) 
	{
		auto p = vec3(random_double(-1,1), random_double(-1,1), 0);
		if (p.length_squared() >= 1) continue;
		return p;
	}
}












