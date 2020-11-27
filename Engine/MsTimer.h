#pragma once
class MSTimer
{
public:
	void Start();
	Uint32 Read();
	Uint32 Stop();

private:
	Uint32 time;
	bool activated = false;
};



