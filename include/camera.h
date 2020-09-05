#pragma once
#include "pt_util.h"
#include "vec3.h"
#include "ray.h"

class Camera
{
public:
	Camera(	Point3 lookfrom,
			Point3 lookat,
			vec3   vup,
			double vfov, // vertical field-of-view in degrees
			double aspect_ratio,
			double aperture,
			double focus_dist);
	~Camera();


	Ray get_ray(double s, double t) const;
public:
	vec3 u, v, w;
	Point3 origin;
	Point3 lower_left_corner;
	vec3 horizontal;
	vec3 vertical;
	double lens_radius;
};