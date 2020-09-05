#pragma once
#include "object.h"


class Sphere : public Object
{
public:
	Sphere(Point3 location, double radius, Material* mat);
	virtual ~Sphere();


	virtual bool hit(const Ray& i_ray, HitData* data, double t_min, double t_max);
public:
	const Point3 m_location;
	const double m_radius;
	Material* const m_mat;
};