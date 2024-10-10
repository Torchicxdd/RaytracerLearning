#ifndef MATERIAL_H
#define MATERIAL_H

#include "hittable.h"

class Material {
	public:
		virtual ~Material() = default;

		virtual bool Scatter(
			const Ray& ray_in, const HitRecord& rec, Color& attenuation, Ray& scattered
		) const {
			return false;
		}
};

class Lambertian : public Material {
	public:
		Lambertian(const Color& albedo) : albedo(albedo) {}

		bool Scatter(const Ray& ray_in, const HitRecord& rec, Color& attenuation, Ray& scattered)
		const override {
			auto scatter_direction = rec.normal + Random_Unit_Vector();

			if (scatter_direction.Near_zero()) {
				scatter_direction = rec.normal;
			}

			scattered = Ray(rec.point, scatter_direction);
			attenuation = albedo;
			return true;
		}

	private:
		Color albedo;
};

class Metal : public Material {
	public:
		Metal(const Color& albedo) : albedo(albedo) {}

		bool Scatter(const Ray& ray_in, const HitRecord& rec, Color& attenuation, Ray& scattered)
		const override {
			Vec3 reflected = Reflect(ray_in.Direction(), rec.normal);
			scattered = Ray(rec.point, reflected);
			attenuation = albedo;
			return true;
		}

	private:
		Color albedo;
};

#endif
