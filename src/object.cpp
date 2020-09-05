#include "object.h"


Object::Object(){}
Object::~Object(){}

ObjectList::ObjectList(){}
ObjectList::~ObjectList(){}

bool 
ObjectList::hit(const Ray& i_ray, HitData* data, double t_min, double t_max)
{
	HitData temp_data;
	bool hit_anything = false;
	double closest_hit = t_max;

	for(auto obj : m_obj_vector)
	{
		if(obj->hit(i_ray, &temp_data, t_min, closest_hit))
		{
			hit_anything = true;
			closest_hit = temp_data.t;
			*data = temp_data;
		}
	}

	return hit_anything;
}

void
ObjectList::insert(Object* item)
{
	m_obj_vector.push_back(item);
}