#pragma once
#include "math.h"
#include "Device.h"

class GridBuffer
{
public:
	void init( Device* device, const Vector& origin, const float& side, const int& width, const int& height );
	void setUp( const float& up );
	void draw( );
	void setRandomUp( );
	void setCircleUp( );

private:
	int width;
	int height;
	float side;
	Vector** gridBuffer;
	Device* device;
};
