#include "render.h"
#include "stb_image_write.h"

#include <thread>
#include <memory>

#include <cstdlib>
#include <cstdio>


void stbi_write_callback(void* context, void* data, int size)
{
	fwrite(data, 1, size,(FILE*)context);
}

FrameRenderer::FrameRenderer(Scene* scene_, uint16_t width, uint16_t height, uint32_t spp, uint8_t thread_max) 
	: m_scene(scene_), m_width(width), m_height(height), m_spp(spp), m_thread_max(thread_max)
{
	m_data = (uint8_t*)malloc(COLOR_SIZE*m_width*m_height);
	assert(m_data != nullptr && "malloc returned nullptr!");
}


FrameRenderer::~FrameRenderer(){}

void
FrameRenderer::set_current_pixel(uint8_t* image_data, Color col)
{
	double scale = 1.0 / m_spp;
	image_data[0] = static_cast<uint8_t>(256 * clamp(std::sqrt(col.x() * scale), 0.0, 0.99999));
	image_data[1] = static_cast<uint8_t>(256 * clamp(std::sqrt(col.y() * scale), 0.0, 0.99999));
	image_data[2] = static_cast<uint8_t>(256 * clamp(std::sqrt(col.z() * scale), 0.0, 0.99999));
}

Color
FrameRenderer::get_ray_color(const Ray& r, int depth)
{
	HitData h_data;

	if(depth <= 0)
		return Color(0.0,0.0,0.0);

	if(!m_scene->obj->hit(r, &h_data, 0.001, pt_infinity))
	{
		if(m_scene->use_skybox)
		{
			vec3 unit_direction = unit_vector(r.direction());
		    auto t = 0.5*(unit_direction.y() + 1.0);
		    return (1.0-t)*Color(1.0, 1.0, 1.0) + t*Color(0.5, 0.7, 1.0);
		}
		else
		{
			return m_scene->bg_color;
		}
	}

	Ray scattered;
	Color attenuation;
	Color emitted = h_data.mat_ptr->emitted(h_data.u, h_data.v, h_data.p);

	if(!h_data.mat_ptr->scatter(r, h_data, &attenuation, &scattered))
		return emitted;


	return emitted + (attenuation * get_ray_color(scattered, depth-1));
}



void
FrameRenderer::render_loop()
{
	while(true)
	{
		this->m_manager.job_mutex.lock();
		
		JobOrder job = this->m_manager.job_queue.front();
		
		if(job.img_ptr == nullptr)
		{
			this->m_manager.job_mutex.unlock();
			break;
		}
		
		this->m_manager.job_queue.pop();
		this->m_manager.job_mutex.unlock();

		

		int j = job.j;

		for(int i = 0; i < m_width; i++)
		{
			Color pixel_color(0,0,0);
			for(int s = 0; s < m_spp; s++)
			{
				double u = (i + random_double()) / (this->m_width-1);
				double v = (j + random_double()) / (this->m_height-1);
				Ray r = this->m_scene->cam->get_ray(u, v);
				pixel_color += this->get_ray_color(r, max_depth);
			}
			this->set_current_pixel(job.img_ptr, pixel_color);
			job.img_ptr += COLOR_SIZE;
		}

		line_count++;
	}

}

/*
struct PixelJob
{
	int j;
	int i;
	uint8_t* loc;

};

class PixelRenderer
{
	PixelRenderer(FrameRenderer* fr) : mfr(fr) {}
	~PixelRenderer(){}

	friend class FrameRenderer;

	void render_pixel();

	FrameRenderer* mfr;

	std::queue<PixelJob> job_queue;
	std::mutex job_mutex;

};

void
PixelRenderer::render_pixel()
{
	while(true)
	{
		job_mutex.lock();
		while(job_queue.empty())
		{
			//if(leader) return;

			std::this_thread::yield();
		}

		PixelJob pixel_job = job_queue.front();
		if(pixel_job.loc == nullptr)
		{
			job_mutex.unlock();
			break;
		}

		job_queue.pop();
		job_mutex.unlock();

		Color pixel_color(0,0,0);
		for(int s = 0; s < mfr->m_spp; s++)
		{
			double u = (pixel_job.i + random_double()) / (mfr->m_width-1);
			double v = (pixel_job.j + random_double()) / (mfr->m_height-1);
			Ray r = mfr->m_scene->cam->get_ray(u, v);
			pixel_color += mfr->get_ray_color(r, mfr->max_depth);
		}
		mfr->set_current_pixel(pixel_job.loc, pixel_color);
		mfr->line_count++;

	}
}


void
FrameRenderer::render_loop()
{
	using std::thread;

	PixelRenderer pix(this);
	std::vector<thread*> thread_vector;

	for(int i = 0; i < 3; i++)
		thread_vector.push_back(new thread(&PixelRenderer::render_pixel, &pix));



	while(true)
	{
		this->m_manager.job_mutex.lock();
		while(this->m_manager.job_queue.empty())
			std::this_thread::yield();

		JobOrder job = this->m_manager.job_queue.front();

		
		if(job.img_ptr == nullptr)
		{
			this->m_manager.job_mutex.unlock();
			break;
		}
		
		this->m_manager.job_queue.pop();
		this->m_manager.job_mutex.unlock();

		

		int j = job.j;

		for(int i = 0; i < m_width; i++)
		{
			PixelJob pixel_job;
			pixel_job.i = i;
			pixel_job.j = j;
			pixel_job.loc = job.img_ptr;
			pix.job_queue.push(pixel_job);
			job.img_ptr += COLOR_SIZE;
		}

		//pix.render_pixel(true);

		//line_count++;
	}

	for(thread* t : thread_vector)
	{
		t->join();
		delete t;
	}

}



*/


/*

uint8_t* image_data = m_data;
for(int j = m_height - 1; j >= 0; j--)
{
	for(int i = 0; i < m_width; i++)
	{
		Color pixel_color(0,0,0);
		for(int s = 0; s < m_spp; s++)
		{
			double u = (i + random_double()) / (m_width-1);
			double v = (j + random_double()) / (m_height-1);
			Ray r = m_scene->cam->get_ray(u, v);
			pixel_color += get_ray_color(r, max_depth);
		}
		set_current_pixel(image_data, pixel_color);
		image_data += COLOR_SIZE;
	}
}

*/
#include <chrono>

void
FrameRenderer::render(const char* dest)
{	
	using namespace std::chrono_literals;
	using std::thread;

	int row = 0;
	for(int j = m_height - 1; j >= 0; j--)
	{
		JobOrder job;
		job.j = j;
		job.img_ptr = m_data + (m_width*COLOR_SIZE*row);
		m_manager.job_queue.push(job);
		row++;
	}

	JobOrder stop_job;
	stop_job.j = 0;
	stop_job.img_ptr = nullptr;
	m_manager.job_queue.push(stop_job);

	std::vector< thread* > thread_vector;

	for(int i = 0; i < m_thread_max; i++)
		thread_vector.push_back(new thread(&FrameRenderer::render_loop, this));
	
	fprintf(stderr, "\n");
	while(line_count < m_height)
	{
		int current = line_count;
		fprintf(stderr, "\r%d/%d", current, m_height);
		std::this_thread::sleep_for(1s);
	}

	fprintf(stderr, "\rDONE!\n");
	
	for(thread* t : thread_vector)
	{
		t->join();
		delete t;
	}

	FILE* fd = fopen(dest, "w");
	if(fd == nullptr)
		fprintf(stderr, "Cannot open file: %s\n", dest);
	stbi_write_bmp_to_func(&stbi_write_callback, fd, m_width, m_height, 
		OUTPUT_FORMAT_STBI_RGB, m_data);


}