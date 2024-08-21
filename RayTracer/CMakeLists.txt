cmake_minimum_required(VERSION 3.20)

project("RayTracer")
add_executable("RayTracer" "main.cpp"  "vec3.h" "color.h" "ray.h" "hittable.h" "sphere.h" "hittable_list.h")