#ifndef VEC3_H
#define VEC3_H

class Vec3 {
	public:
		double e[3];

		Vec3() : e{ 0,0,0 } {}
		Vec3(double e0, double e1, double e2) : e{ e0, e1, e2 } {}

		double X() const { return e[0]; }
		double Y() const { return e[1]; }
		double Z() const { return e[2]; }

		Vec3 operator-() const { return Vec3(-e[0], -e[1], -e[2]); }
		double operator[](int i) const { return e[i]; }
		double& operator[](int i) { return e[i]; }

		Vec3& operator+=(const Vec3& v) {
			e[0] += v.e[0];
			e[1] += v.e[1];
			e[2] += v.e[2];
			return *this;
		}

		Vec3& operator*=(double t) {
			e[0] *= t;
			e[1] *= t;
			e[2] *= t;
			return *this;
		}

		Vec3& operator/=(double t) {
			return *this *= 1 / t;
		}

		double Length() const {
			return std::sqrt(Length_squared());
		}

		double Length_squared() const {
			return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
		}

		bool Near_zero() const {
			// Return true if the vector is close to zero in all dimensions
			auto s = 1e-8;
			return (std::fabs(e[0]) < s) && (std::fabs(e[1]) < s) && (std::fabs(e[2]) < s);
		}

		static Vec3 Random() {
			return Vec3(Random_double(), Random_double(), Random_double());
		}

		static Vec3 Random(Interval minMax) {
			return Vec3(Random_double(minMax.min, minMax.max), Random_double(minMax.min, minMax.max), Random_double(minMax.min, minMax.max));
		}
};

// Point3 is just an alias for Vec3, but useful for geometric clarity in the code
using Point3 = Vec3;


// Vector Utility Functions

inline std::ostream& operator<<(std::ostream& out, const Vec3& v) {
	return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

inline Vec3 operator+(const Vec3& u, const Vec3& v) {
	return Vec3(u.X() + v.X(), u.Y() + v.Y(), u.Z() + v.Z());
}

inline Vec3 operator-(const Vec3& u, const Vec3& v) {
	return Vec3(u.X() - v.X(), u.Y() - v.Y(), u.Z() - v.Z());
}

inline Vec3 operator*(const Vec3& u, const Vec3& v) {
	return Vec3(u.X() * v.X(), u.Y() * v.Y(), u.Z() * v.Z());
}

inline Vec3 operator*(double t, const Vec3& v) {
	return Vec3(t*v.X(), t*v.Y(), t*v.Z());
}

inline Vec3 operator*(const Vec3& v, double t) {
	return t * v;
}

inline Vec3 operator/(const Vec3& v, double t) {
	return (1/t) * v;
}

inline double Dot(const Vec3& u, const Vec3& v) {
	return u.X() * v.X()
		+ u.Y() * v.Y()
		+ u.Z() * v.Z();
}

inline Vec3 Cross(const Vec3& u, const Vec3& v) {
	return Vec3(u.Y() * v.Z() - u.Z() * v.Y(),
				u.Z() * v.X() - u.X() * v.Z(),
				u.X() * v.Y() - u.Y() * v.X());
}

inline Vec3 Unit_vector(const Vec3& v) {
	return v / v.Length();
}

inline Vec3 Random_Unit_Vector() {
	while (true) {
		auto p = Vec3::Random(Interval(-1, 1));
		auto lengthSquared = p.Length_squared();
		// Float-point abstraction leak if random vector is small enough near the center of unit circle
		if (1e-160 < lengthSquared && lengthSquared <= 1) {
			return p / sqrt(lengthSquared);
		}
	}
}

inline Vec3 Random_On_Hemisphere(const Vec3& normal) {
	Vec3 on_unit_sphere = Random_Unit_Vector();
	if (Dot(on_unit_sphere, normal) > 0.0) { 
		return on_unit_sphere; // In the same hemisphere as the normal
	}
	else {
		return -on_unit_sphere;
	}
}

inline Vec3 Reflect(const Vec3& v, const Vec3& n) {
	return v - 2*Dot(v, n)*n;
}

#endif