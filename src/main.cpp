#include "Renderer/Renderer.h"
#include "Platform/Platform.h"
#include "Input/Input.h"
#include "Camera.h"
#include "Car.h"
#include "RenderThread.h"
#include "RenderCommand.h"
#include "Circuit/Circuit.h"
#include "Circuit/Segment.h"

#include <iostream>
int main(int argc, char* args[])
{
	// Initialize resources
	int yOffset = 1000 - (600 / 2);
	int zOffset = -800;
	Platform::Init();
	Renderer::Init(true, 1280, 720);
	Input::Init();
	Camera::Init(Vector3(0, yOffset, zOffset), Renderer::GetWidth(), Renderer::GetHeight(), 100, 1200);

	Circuit circuit;
	circuit.loadFile("recursos/circuits/circuit.bin");

	 //Load ferrari images
	Image* image = Renderer::CreateImage("recursos/sprites/ferrari.rgba");
	Image* imageHill = Renderer::CreateImage("recursos/sprites/ferrariUpHill.rgba");

	Car car(image, imageHill, Vector3(0,0,230), 1000, 500);
	circuit.init(&car);

	//Initialize render thread
	RenderThread renderThread;
	renderThread.start();

	//Commands
	RenderCommand comandoClear;
	comandoClear.type = RenderCommandType::CLEAR;
	comandoClear.clearInfo.color = 0x007ECEFF;

	RenderCommand comandoTrapece;
	comandoTrapece.type = RenderCommandType::DRAWTRAPECE;

	RenderCommand comandoSprite;
	comandoSprite.type = RenderCommandType::DRAWSPRITE;

	RenderCommand comandoPresent;
	comandoPresent.type = RenderCommandType::PRESENT;

	// Main loop
	double lastFrameTime = Platform::Get_Time();

	double time = 0;
	double frames = 0;
	while (Platform::Tick())
	{

	//	//---------------- INPUT ---------------//
		std::vector<Event> events = Input::Get_Events();
		int size = events.size();
		for (int i = 0; i < size; i++)
			car.handleInput(events[i]);
		

	//	//---------------- UPDATE ---------------//
		 //Calculate deltaTime
		double currentTime = Platform::Get_Time();
		double delta = currentTime - lastFrameTime;
		lastFrameTime = currentTime;

		 //Update car
		car.update(delta);
		
		circuit.update(&car, zOffset);

		 //Update camera position
		Vector3 carPos = car.getPosition();
		Camera::setPosition(Vector3(carPos.getX(), carPos.getY() + yOffset, carPos.getZ() + zOffset));

		//---------------- RENDER ---------------//

		 //Enqueue Renderer::Clear() command
		renderThread.enqueueCommand(comandoClear);

		//Render circuit
		circuit.render(&renderThread, &comandoTrapece);

		 //Enqueue Renderer::DrawImage() command
		car.render(&comandoSprite);
		renderThread.enqueueCommand(comandoSprite);
		
		 //Enqueue Renderer::Present() command
		renderThread.enqueueCommand(comandoPresent);

		while (renderThread.pendingFrames() > 3);

		//---------------- FPS ---------------//
		time += delta;
		frames++;
		if (time > 10)
		{
			printf("%f FPS\n", frames / time);
			time = 0;
			frames = 0;
		}
	}

	 //Cleanup before closing application
	renderThread.stop();

	delete image;
	delete imageHill;

	Renderer::Release();
	Platform::Release();
	//Input::Release();

	return 0;
}