#include "material.h"
#include "object.h"

Material::Material()
{

}

Material::~Material(){}

Color 
Material::emitted(double u, double v, const Point3& p) const
{
	return Color(0.0, 0.0, 0.0); //by default materials don't emit light
}

Lambertian::Lambertian(const Color& a) : m_albedo(a) {}
Lambertian::~Lambertian(){}

bool 
Lambertian::scatter(const Ray& i_ray, const HitData& data, Color* attenuation, Ray* scattered) const
{
	vec3 scatter_direction = data.normal + random_unit_vector();
	*scattered = Ray(data.p, scatter_direction);
	*attenuation = m_albedo;
	return true;
}


Metal::Metal(const Color& a, double fuzz) : m_albedo(a), m_fuzz(fuzz < 1 ? fuzz : 1){}
Metal::~Metal(){}

bool
Metal::scatter(const Ray& i_ray, const HitData& data, Color* attenuation, Ray* scattered) const
{
	vec3 reflected = reflect(unit_vector(i_ray.direction()), data.normal);
	*scattered = Ray(data.p, reflected + m_fuzz*random_in_unit_sphere());
	*attenuation = m_albedo;
	return dot(scattered->direction(), data.normal) > 0;
}


Dielectric::Dielectric(double ri) : m_ref_idx(ri) {}
Dielectric::~Dielectric(){}

double schlick(double cosine, double ref_idx) {
	auto r0 = (1-ref_idx) / (1+ref_idx);
	r0 = r0*r0;
	return r0 + (1-r0)*pow((1 - cosine),5);
}

bool
Dielectric::scatter(const Ray& i_ray, const HitData& data, Color* attenuation, Ray* scattered) const
{
	*attenuation = Color(1.0, 1.0, 1.0);
	double etai_over_etat = data.front_face ? (1.0 / m_ref_idx) : m_ref_idx;

	vec3 unit_direction = unit_vector(i_ray.direction());

	double cos_theta = fmin(dot(-unit_direction, data.normal), 1.0);
	double sin_theta = std::sqrt(1.0 - cos_theta*cos_theta);
	if (etai_over_etat * sin_theta > 1.0 ) {
		vec3 reflected = reflect(unit_direction, data.normal);
		*scattered = Ray(data.p, reflected);
		return true;
	}

	double reflect_prob = schlick(cos_theta, etai_over_etat);
	if (random_double() < reflect_prob)
	{
		vec3 reflected = reflect(unit_direction, data.normal);
		*scattered = Ray(data.p, reflected);
		return true;
	}


	vec3 refracted = refract(unit_direction, data.normal, etai_over_etat);
	*scattered = Ray(data.p, refracted);
	return true;
}


DiffuseLight::DiffuseLight(const Color& a) : m_color(a) {}
DiffuseLight::~DiffuseLight(){}

bool
DiffuseLight::scatter(const Ray&, const HitData&, Color*, Ray*) const
{
	return false;
}

Color 
DiffuseLight::emitted(double, double, const Point3&) const
{
	return m_color;
}