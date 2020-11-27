#pragma once

class USTimer
{
public:
	void Start();
	Uint32 Read();
	Uint32 Stop();

private:
	Uint32 microseconds;
	double frequency;
	bool activated = false;
};



