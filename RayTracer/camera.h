#ifndef CAMERA_H
#define CAMERA_H

#include "hittable.h"
#include "material.h"

class Camera {
	public:
        // Image
        double  aspect_ratio = 1.0; // Ratio of image width over height
        int     image_width = 100; // Rendered image width in pixel count
        int     samples_per_pixel = 10; // Count of random samples for each pixel
        int     max_depth = 10; // Max number of ray bounces into scene

        void Render(const Hittable& world) {
            Initialize();

            // Goes through every pixel and determines its colour
            std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

            for (int j = 0; j < image_height; j++) {
                std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
                for (int i = 0; i < image_width; i++) {
                    Color pixel_color(0, 0, 0);
                    for (int sample = 0; sample < samples_per_pixel; sample++) {
                        Ray r = Get_Ray(i, j);
                        pixel_color += Ray_Color(r, max_depth, world);
                    }
                    Write_color(std::cout, pixel_color * pixel_samples_scale);
                }
            }

            std::clog << "\rDone.                 \n";
        }

	private:
        int image_height;           // Rendered image height
        double pixel_samples_scale; // Colour scale factor for a sum of pixel samples;
        Point3 center;              // Camera center
        Point3 pixel00_loc;         // Location of pixel 0,0
        Vec3 pixel_delta_u;         // Offset to pixel to the right
        Vec3 pixel_delta_v;         // Offset to pixel below


        void Initialize() {
            // Calculate the image height, and ensure that it's at least 1
            image_height = int(image_width / aspect_ratio);
            image_height = (image_height < 1) ? 1 : image_height;

            pixel_samples_scale = 1.0 / samples_per_pixel;

            center = Point3(0, 0, 0);

            // Determine viewport dimensions
            auto focal_length = 1.0;
            auto viewport_height = 2.0;
            auto viewport_width = viewport_height * (double(image_width) / image_height);

            // Calculate the vectors across the horizontal and down the vertical viewport edges
            auto viewport_u = Vec3(viewport_width, 0, 0);
            auto viewport_v = Vec3(0, -viewport_height, 0);

            // Calculate the horizontal and vertical delta vectors from pixel to pixel
            pixel_delta_u = viewport_u / image_width;
            pixel_delta_v = viewport_v / image_height;

            // Calculate the location of the upper left pixel
            auto viewport_upper_left =
                center - Vec3(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2;
            pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
        }

        Ray Get_Ray(int i, int j) const {
            // Construct a camera ray originating from the origin and directed at randomly sampled
            // point around the pixel location i, j

            Vec3 offset = Sample_Square();
            Vec3 pixel_sample = pixel00_loc
                + ((i + offset.X()) * pixel_delta_u)
                + ((j + offset.Y()) * pixel_delta_v);

            auto ray_origin = center;
            auto ray_direction = pixel_sample - ray_origin;

            return Ray(ray_origin, ray_direction);
        }

        Vec3 Sample_Square() const {
            // Returns the vector to a random point in the [-.5, -.5] - [+.5, +.5] unit square
            return Vec3(Random_double() - 0.5, Random_double() - 0.5, 0);
        }

        // Checks to see if ray hits an object and returns colour
        Color Ray_Color(const Ray& r, int depth, const Hittable& world) const {
            // If we've exceeded the ray bounce limit, no more light is gathered.
            if (depth <= 0) {
                return Color(0, 0, 0);
            }

            HitRecord rec;

            if (world.Hit(r, Interval(0.001, infinity), rec)) {
                Ray scattered;
                Color attenuation;
                if (rec.mat->Scatter(r, rec, attenuation, scattered)) {
                    return attenuation * Ray_Color(scattered, depth - 1, world);
                }
                return Color(0,0,0);
            }

            // Returns color between white and blue (the sky because it didn't hit)
            Vec3 unit_direction = Unit_vector(r.Direction());
            auto a = 0.5 * (unit_direction.Y() + 1.0);
            return (1.0 - a) * Color(1.0, 1.0, 1.0) + a * Color(0.5, 0.7, 1.0);
        }
};


#endif
