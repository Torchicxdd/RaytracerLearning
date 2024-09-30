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

#endif
