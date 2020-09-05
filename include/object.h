#pragma once
#include "ray.h"
#include "material.h"
#include <vector>

struct HitData
{
	Point3 p;
	vec3 normal;
	Material* mat_ptr;
	double t;
	double u;
    double v;
	bool front_face;

    inline void set_face_normal(const Ray& r, const vec3& outward_normal) 
    {
        front_face = dot(r.direction(), outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    }
};

class Object
{
public:
	Object();
	virtual ~Object() = 0;

	virtual bool hit(const Ray& i_ray, HitData* data, double t_min, double t_max) = 0;

};


class ObjectList : public Object
{
public:
	ObjectList();
	~ObjectList();

	virtual bool hit(const Ray& i_ray, HitData* data, double t_min, double t_max);

	void insert(Object* item);

private:
	std::vector<Object*> m_obj_vector;

};