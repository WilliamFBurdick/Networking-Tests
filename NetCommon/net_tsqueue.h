#pragma once
#include "net_common.h"

namespace networking
{
	template<typename T>
	class tsqueue
	{
	public:
		tsqueue() = default;
		tsqueue(const tsqueue<T>&) = delete;
		virtual ~tsqueue() { clear(); }

	public:
		// Returns and maintains item at front of queue.
		const T& front()
		{
			std::scoped_lock lock(muxQueue);
			return deqQueue.front();
		}

		// Returns and maintains item at back of queue.
		const T& back()
		{
			std::scoped_lock lock(muxQueue);
			return deqQueue.back();
		}

		// Returns the number of items in the queue
		size_t count()
		{
			std::scoped_lock lock(muxQueue);
			return deqQueue.size();
		}

		// Clears the queue
		void clear()
		{
			std::scoped_lock lock(muxQueue);
			deqQueue.clear();
		}

		// Removes and returns the front item in the queue
		T pop_front()
		{
			std::scoped_lock lock(muxQueue);
			auto t = std::move(deqQueue.front());
			deqQueue.pop_front();
			return t;
		}

		// Removes and returns the back item in the queue
		T pop_back()
		{
			std::scoped_lock lock(muxQueue);
			auto t = std::move(deqQueue.back());
			deqQueue.pop_back();
			return t;
		}

	protected:
		std::mutex muxQueue;
		std::deque<T> deqQueue;
	};
}