#include "ray.h"

Ray::Ray(){}
Ray::Ray(Point3 origin, vec3 dir) : m_origin(origin), m_dir(dir) {}
Ray::~Ray() {}


Point3
Ray::origin() const
{
	return m_origin;
}

vec3
Ray::direction() const
{
	return m_dir;
}

Point3
Ray::at(double t) const
{
	return m_origin + (m_dir * t);
}