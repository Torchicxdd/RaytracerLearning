#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "hittable.h"

#include <vector>

class Hittable_list : public Hittable {
	public:
		std::vector<shared_ptr<Hittable>> objects;

		Hittable_list() {}
		Hittable_list(shared_ptr<Hittable> object) { Add(object); }

		void Clear() { objects.clear(); }

		void Add(shared_ptr<Hittable> object) {
			objects.push_back(object);
		}

		bool Hit(const Ray& r, Interval ray_t, HitRecord& rec) const override {
			HitRecord temp_rec;
			bool hit_anything = false;
			auto closest_so_far = ray_t.max;
			
			// Hittable Hit method
			for (const auto& object : objects) {
				if (object->Hit(r, Interval(ray_t.min, closest_so_far), temp_rec)) {
					hit_anything = true;
					closest_so_far = temp_rec.t;
					rec = temp_rec;
				}
			}

			return hit_anything;
		}
};

#endif 
