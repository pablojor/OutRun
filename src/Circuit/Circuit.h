#pragma once
#include <vector>
#include <stdint.h>
class Segment;
class RenderCommand;
class RenderThread;
class Car;

class Circuit {
private:
	std::vector<Segment*> _segments;
	void* _buffer;
	uint32_t _numSegments;
	int _iniSeg, _iniCarSeg;

public:
	~Circuit();

	void init(Car* c);

	//reads file and creates all segments
	void loadFile(const char* filepath);

	//add values to the segment
	void createSegment(void* buffer, int sum);

	// renders 300 segments checking if segment to render is not off limits in height
	void render(RenderThread* thread, RenderCommand* comando);

	void update(Car* c, int zOffset);

	// ========== GETTERS ==========
	uint32_t getNumSegments();
	std::vector<Segment*>& getSegments();
};