#pragma once

/*
** RPI Game Architecture Engine
**
** Portions adapted from:
** Viper Engine - Copyright (C) 2016 Velan Studios - All Rights Reserved
**
** This file is distributed under the MIT License. See LICENSE.txt.
**
** Based on: "Parallelizing the Naughty Dog Engine Using Fibers", Christian Gyrling
*/

#include <cstdint>

/*
** Job entry point.
*/
typedef void(*ga_job_function_t)(void* data);

/*
** Defines a job.
*/
struct ga_job_decl_t
{
	ga_job_function_t _entry;
	void* _data;

	int32_t* _pending_count;
};

/*
** Job system functionality.
*/
class ga_job
{
public:
	static void startup(
		uint32_t hardware_thread_mask,
		int queue_size,
		int fiber_count);

	static void shutdown();

	static void run(ga_job_decl_t* decls, int decl_count, int32_t* counter);

	static void wait(int32_t* counter);

private:
	static void* _impl;
};
