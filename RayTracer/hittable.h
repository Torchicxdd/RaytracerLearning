#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"

class HitRecord {
	public:
		Point3 point;
		Vec3 normal;
		double t;
		bool front_face;

		void set_face_normal(const Ray& r, const Vec3& outward_normal) {
			front_face = dot(r.direction(), outward_normal) < 0;
			normal = front_face ? outward_normal : -outward_normal;
		}
};

class Hittable {
	public:
		virtual ~Hittable() = default;

		virtual bool hit(const Ray& r, double ray_tmin, double ray_tmax, HitRecord& rec) const = 0;
};

#endif
