#include "RenderThread.h"
#include "Renderer/Renderer.h"

// Thread main loop
void RenderThread::renderThread()
{
	while (!exit)
		processCommand();

	while (numPresents > 0)
		processCommand();
}

// Picks the first command in the queue an processes it
void RenderThread::processCommand()
{
	RenderCommand command;
	if (concurrentQueue.try_dequeue(command))
	{
		// PRESENT Command
		if (command.type == RenderCommandType::PRESENT)
		{
			Renderer::Present();
			numPresents--;
		}

		// CLEAR Command
		else if (command.type == RenderCommandType::CLEAR)
			Renderer::Clear(command.clearInfo.color);
		
		// DRAWSPRITE Command
		else if (command.type == RenderCommandType::DRAWSPRITE)
			Renderer::DrawSprite(command.drawSpriteInfo.image, command.drawSpriteInfo.x1, command.drawSpriteInfo.y1, command.drawSpriteInfo.x2, command.drawSpriteInfo.y2,
				command.drawSpriteInfo.srcX1, command.drawSpriteInfo.srcY1, command.drawSpriteInfo.srcX2, command.drawSpriteInfo.srcY2);

		// DRAWIMAGE Command
		else if(command.type == RenderCommandType::DRAWIMAGE)
			Renderer::DrawImage(command.drawImageInfo.image, command.drawImageInfo.x1, command.drawImageInfo.y1, command.drawImageInfo.x2, command.drawImageInfo.y2);

		// DRAWTRAPECE Command
		else if (command.type == RenderCommandType::DRAWTRAPECE)
			Renderer::DrawTrapece(command.drawTrapeceInfo.x1, command.drawTrapeceInfo.y1, command.drawTrapeceInfo.w1, command.drawTrapeceInfo.x2, command.drawTrapeceInfo.y2, command.drawTrapeceInfo.w2,
				command.drawTrapeceInfo.color, command.drawTrapeceInfo.maxHeight);

		// DRAWHLINE Command
		else
			Renderer::DrawHLine(command.drawLineInfo.y, command.drawLineInfo.x1, command.drawLineInfo.x2, command.drawLineInfo.color);
	}
}

// Create thread and start main loop
void RenderThread::start()
{
	exit = false;
	numPresents = 0;
	th = new std::thread(&RenderThread::renderThread, this);
}

// Stop main loop, wait for father to end and destroy
void RenderThread::stop()
{
	exit = true;
	th->join();
	delete th;
}

// Add a command to the queue to be processed
void RenderThread::enqueueCommand(RenderCommand command)
{
	concurrentQueue.enqueue(command);
	if (command.type == RenderCommandType::PRESENT)
		numPresents++;
}

// Return number of pending frames
int RenderThread::pendingFrames()
{
	return numPresents;
}
