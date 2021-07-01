#pragma once
#include "RenderCommand.h"
#include "ConcurrentQueue.h"

#include <thread>
#include <atomic>

class RenderThread
{
private:
	std::atomic_int numPresents;
	std::atomic_bool exit;
	std::thread* th;
	
	moodycamel::ConcurrentQueue<RenderCommand> concurrentQueue;

	// Thread main loop
	void renderThread();

	// Picks the first command in the queue an processes it
	void processCommand();

public:
	// Create thread and start main loop
	void start();

	// Stop main loop, wait for father to end and destroy
	void stop();

	// Add a command to the queue to be processed
	void enqueueCommand(RenderCommand command);

	// Return number of pending frames
	int pendingFrames();

};

