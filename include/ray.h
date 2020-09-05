#pragma once
#include "vec3.h"

class Ray
{
public:
	Ray();
	Ray(Point3 origin, vec3 dir);
	~Ray();

	Point3  origin() const;
	vec3 direction() const;

	Point3 at(double t) const;


public:
	Point3 m_origin;
	vec3 m_dir;


};