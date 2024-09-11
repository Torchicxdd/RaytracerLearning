#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"

class Sphere : public Hittable {
	public:
		Sphere(const Point3& center, double radius) : center(center), radius(std::fmax(0, radius)) {}

		bool Hit(const Ray& r, Interval ray_t, HitRecord& rec) const override {
			Vec3 oc = center - r.Origin();
			auto a = r.Direction().Length_squared();
			auto h = Dot(r.Direction(), oc);
			auto c = oc.Length_squared() - radius * radius;

			auto discriminant = h * h - a * c;
			if (discriminant < 0) {
				return false;
			}
			
			auto sqrtd = std::sqrt(discriminant);

			// Find the nearest root that lies in the acceptable range
			auto root = (h - sqrtd) / a;
			if (!ray_t.Surrounds(root)) {
				root = (h + sqrtd) / a;
				if (!ray_t.Surrounds(root)) {
					return false;
				}
			}

			rec.t = root;
			rec.point = r.At(rec.t);
			Vec3 outward_normal = (rec.point - center) / radius;
			rec.Set_face_normal(r, outward_normal);

			return true;
		}

	private:
		Point3 center;
		double radius;
};

#endif