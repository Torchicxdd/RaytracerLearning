#ifndef COLOR_H
#define COLOR_H

#include "interval.h"
#include "vec3.h"

using Color = Vec3;

void Write_color(std::ostream& out, const Color& pixel_color) {
	auto r = pixel_color.X();
	auto g = pixel_color.Y();
	auto b = pixel_color.Z();

	// Translate the [0,1] component values to the byte range [0,255]
	static const Interval intensity(0.000, 0.999);
	int rbyte = int(256 * intensity.Clamp(r));
	int gbyte = int(256 * intensity.Clamp(g));
	int bbyte = int(256 * intensity.Clamp(b));

	// Write out the pixel color components
	out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}

#endif