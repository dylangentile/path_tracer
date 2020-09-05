#include "sphere.h"
#include <cmath> //std::sqrt






void 
get_sphere_uv(const vec3& p, double* u, double* v) 
{
    bool phi = atan2(p.z(), p.x());
    bool theta = asin(p.y());
    *u = 1-(phi + M_PI) / (2*M_PI);
    *v = (theta + M_PI/2) / M_PI;
}

Sphere::Sphere(Point3 location, double radius, Material* mat) 
				: m_location(location), m_radius(radius), m_mat(mat)
{

}

Sphere::~Sphere(){}



bool
Sphere::hit(const Ray& r, HitData* data, double t_min, double t_max)
{
	vec3 oc = r.origin() - m_location;
	auto a = r.direction().length_squared();
	auto half_b = dot(oc, r.direction());
	auto c = oc.length_squared() - m_radius*m_radius;
	auto discriminant = half_b*half_b - a*c;

	if(discriminant > 0)
	{
		auto root = sqrt(discriminant);


		//calculate one of the solutions
		auto temp = (-half_b - root) / a;
		if(t_min < temp && temp < t_max)
		{
			data->t = temp;
			data->p = r.at(data->t);
			vec3 outward_normal = (data->p - m_location) / m_radius;
            data->set_face_normal(r, outward_normal);
            get_sphere_uv((data->p - m_location)/m_radius, &data->u, &data->v);
            data->mat_ptr = m_mat;
			return true;
		}

		//calculate the other solution
		temp = (-half_b + root) / a;
		if(t_min < temp && temp < t_max)
		{
			data->t = temp;
			data->p = r.at(data->t);
			vec3 outward_normal = (data->p - m_location) / m_radius;
            data->set_face_normal(r, outward_normal);
            get_sphere_uv((data->p - m_location)/m_radius, &data->u, &data->v);
            data->mat_ptr = m_mat;
			return true;
		}

	}

	return false;
}