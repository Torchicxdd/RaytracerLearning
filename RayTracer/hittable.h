#ifndef HITTABLE_H
#define HITTABLE_H

// We add this to tell the compiler that material is a class defined later
class material;

class HitRecord {
	public:
		Point3 point;
		Vec3 normal;
		shared_ptr<material> mat;
		double t;
		bool front_face;

		void Set_face_normal(const Ray& r, const Vec3& outward_normal) {
			front_face = Dot(r.Direction(), outward_normal) < 0;
			normal = front_face ? outward_normal : -outward_normal;
		}
};

class Hittable {
	public:
		virtual ~Hittable() = default;

		virtual bool Hit(const Ray& r, Interval ray_t, HitRecord& rec) const = 0;
};

#endif
