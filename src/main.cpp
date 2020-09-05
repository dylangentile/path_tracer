#include "pt_util.h"
#include "render.h"
#include "sphere.h"
#include "material.h"
#include <cstdio>
#include <chrono>





int main(void)
{
	seed_random();
	/*FILE* fd = fopen("image1.bmp", "w");
	if(fd == nullptr)
		return 1;

	uint8_t picture[12]{
		0xFF, 0,	 0,
		0,	  0xFF,	 0,
		0,	  0,	 0xFF,
		0,	  0,	 0		

	};


	stbi_write_bmp_to_func(&stbi_write_callback, fd, 2, 2, OUTPUT_FORMAT_STBI_RGB, picture);


	fclose(fd);*/

	const int32_t width =  1920;
	const int32_t height = 1080;
	const uint32_t spp = 1000;
	const uint8_t thread_count = 64;
	const double aspect_ratio = double(width)/double(height);
	const Point3 lookfrom = Point3(-2.0,1.8,-2);
	const Point3 lookat = Point3(0,0,-1);
	const double aperture = 0.001;

	Camera cam(lookfrom, lookat, vec3(0,1,0), 60, aspect_ratio, aperture,
		(lookfrom - lookat).length());

	Matte white_matte(Color(0.5, 0.5, 0.5));
	DiffuseLight blue_light(Color(0.0, 0.0, 1.0));
	DiffuseLight red_light(Color(1.0, 0.0, 0.0));
	DiffuseLight green_light(Color(0.0, 1.0, 0.0));
	Metal gold_material(Color(0.8, 0.6, 0.2), 0.0);
	Dielectric glass_mat(.9);

	Sphere center_sphere(Point3(0.0, 0.0, -1.0), 0.5, &white_matte);
	Sphere left_light(Point3(-1.0, 0.0, -1.0), 0.5, &gold_material);
	Sphere right_light(Point3(1.0, 0.0, -1.0), 0.5, &red_light);
	Sphere ground_sphere(Point3(0.0, -100.5, -1.0), 100.0, &white_matte);
	Sphere back_light(Point3(0.0, 0.0, -2.0), 0.5, &blue_light);
	Sphere front_light(Point3(0.0, 0.0, 0.0), 0.5, &green_light);
	//Sphere light_sphere

	ObjectList obj_list;
	obj_list.insert(&center_sphere);
	obj_list.insert(&ground_sphere);
	obj_list.insert(&left_light);
	obj_list.insert(&right_light);
	obj_list.insert(&back_light);
	obj_list.insert(&front_light);

	Scene the_scene;
	the_scene.obj = &obj_list;
	the_scene.bg_color = Color(0,0,0);//Color(0.70, 0.80, 1.00);
	the_scene.cam = &cam;
	the_scene.use_skybox = false;
	

	FrameRenderer renderer(&the_scene, width, height, spp, thread_count);



	std::chrono::high_resolution_clock::time_point timer_begin 
					= std::chrono::high_resolution_clock::now();

	renderer.render("result_image.bmp");

	std::chrono::high_resolution_clock::time_point timer_end
					= std::chrono::high_resolution_clock::now();

	uint64_t the_duration = std::chrono::duration_cast<std::chrono::milliseconds>
							(timer_end - timer_begin).count();
	
	FILE* fd = fopen("benchmark.log", "a");
	fprintf(fd, "%lld ms  w=%d h=%d spp=%u tc=%u\n", the_duration, width, height, spp, thread_count);
	fclose(fd);

	return 0;
}



