#pragma once

/*
** RPI Game Architecture Engine
**
** Portions adapted from:
** Viper Engine - Copyright (C) 2016 Velan Studios - All Rights Reserved
**
** This file is distributed under the MIT License. See LICENSE.txt.
*/

/*
** Thread-safe queue.
** https://www.research.ibm.com/people/m/michael/podc-1996.pdf
*/
#include <mutex>
#include <list>
class ga_queue
{
private:
	std::mutex H_Lock, T_LOCK;
	std::list<void*> queue;
public:
	ga_queue(int node_count);
	~ga_queue();

	void push(void* data);
	bool pop(void** data);

	int get_count() const;
};
