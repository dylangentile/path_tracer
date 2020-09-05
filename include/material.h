#pragma once
#include "ray.h"

struct HitData; //don't include object.h in here. They're recursive includes


class Material
{
public:
	Material();
	virtual ~Material() = 0;

	virtual bool scatter(const Ray& i_ray, const HitData& data, 
						 Color* attenuation, Ray* scattered) const = 0;

	virtual Color emitted(double u, double v, const Point3& p) const;

};

class Lambertian : public Material
{
public:
	Lambertian(const Color& a);
	~Lambertian();

	virtual bool scatter(const Ray&, const HitData&, Color*, Ray*) const;


public:
	Color m_albedo;
};

using Matte = Lambertian;


class Metal : public Material
{
public:
	Metal(const Color& a, double fuzz);
	~Metal();

	virtual bool scatter(const Ray&, const HitData&, Color*, Ray*) const;

public:
	Color m_albedo;
	double m_fuzz;
};

class Dielectric : public Material
{
public:
	Dielectric(double ri);
	~Dielectric();

	virtual bool scatter(const Ray&, const HitData&, Color*, Ray*) const;

public:
	double m_ref_idx; //refractive index (snell's law)

};


class DiffuseLight : public Material
{
public:
	DiffuseLight(const Color& a);
	~DiffuseLight();

	virtual bool scatter(const Ray&, const HitData&, Color*, Ray*) const;
	virtual Color emitted(double, double, const Point3&) const;

public:
	Color m_color;
};