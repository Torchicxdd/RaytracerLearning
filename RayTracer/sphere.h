#ifndef SPHERE.H
#define SPHERE.H

#include "hittable.h"
#include "vec3.h"

class Sphere : public Hittable {
	public:
		Sphere(const Point3& center, double radius) : center(center), radius(std::fmax(0, radius)) {}

		bool hit(const Ray& r, double ray_tmin, double ray_tmax, HitRecord& rec) const override {
			Vec3 oc = center - r.origin();
			auto a = r.direction().length_squared();
			auto h = dot(r.direction(), oc);
			auto c = oc.length_squared() - radius * radius;

			auto discriminant = h * h - a * c;
			if (discriminant < 0) {
				return false;
			}
			
			auto sqrtd = std::sqrt(discriminant);

			// Find the nearest root that lies in the acceptable range
			auto root = (h - sqrtd) / a;
			if (root <= ray_tmin || ray_tmax <= root) {
				root = (h + sqrtd) / a;
				if (root <= ray_tmin || ray_tmax <= root) {
					return false;
				}
			}

			rec.t = root;
			rec.point = r.at(rec.t);
			Vec3 outward_normal = (rec.point - center) / radius;
			rec.set_face_normal(r, outward_normal);

			return true;
		}

	private:
		Point3 center;
		double radius;
};

#endif