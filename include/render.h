#pragma once
#include "scene.h"
#include <queue>
#include <atomic>
#include <mutex>

struct JobOrder
{
	int j;
	uint8_t* img_ptr;
};

struct TManager
{
	std::queue<JobOrder> job_queue;
	std::mutex job_mutex;
};

class PixelRenderer;

class FrameRenderer
{
public:
	FrameRenderer(Scene* scene_, uint16_t width, uint16_t height, uint32_t spp, uint8_t thread_max);
	~FrameRenderer();


	void render(const char* dest);
	void render_loop();

private:
	void set_current_pixel(uint8_t*, Color);
	Color get_ray_color(const Ray& r, int depth);


private:
	Scene* const m_scene;
	const uint16_t m_width;
	const uint16_t m_height;
	const uint32_t m_spp; //samples per pixel
	const uint8_t m_thread_max;
	const int max_depth = 50;


	uint8_t* m_data;


	friend class PixelRenderer;
	TManager m_manager;
	std::atomic<int> line_count;

};



