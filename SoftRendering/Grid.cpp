#pragma once
#include "Grid.h"
#include <windows.h>
#include <math.h>
#define PI 3.1415926f
void GridBuffer::init( Device* d, const Vector& origin, const float& s, const int& w, const int& h )
{
	device = d;
	width = w + 1;
	height = h + 1;
	side = s;
	Vector** gb;
	gb = new Vector *[width];
	for ( int j = 0; j < width; j ++ )
	{
		gb[j] = new Vector [height];
	}
	for ( int i = 0; i < width; i ++ )
	{
		for ( int j = 0; j < height; j ++ )
		{
			Vector g = origin + Vector( i * side, 0.f, j * side );
			gb[i][j] = g;
		}
	}
	gridBuffer = gb;
}

void GridBuffer::setUp( const float& u )
{
	for ( int i = 0; i < width; i ++ )
	{
		for ( int j = 0; j < height; j ++ )
		{
			gridBuffer[i][j].y = u;
		}
	}
}

void GridBuffer::draw( )
{
	for ( int i = 0; i < width - 1; i ++ )
	{
		for( int j = 0; j < height; j ++ )
		{
			Vector bottom = gridBuffer[i][j];
			Vector bottomL = gridBuffer[i + 1][j];
			Vector top = gridBuffer[i + 1][j + 1];
			Vector topR = gridBuffer[i][j + 1];

			Vector green = Vector( 0.f, 1.f, 0.f );
			Vertex p1 = Vertex( bottom, green, Vector( ) );
			Vertex p2 = Vertex( bottomL, green, Vector( ) );
			Vertex p3 = Vertex( topR, green, Vector( ) );
			Vertex p4 = Vertex( top, green, Vector( ) );
			device->drawLine3D( p1, p2 );
			device->drawLine3D( p2, p4 );
			device->drawLine3D( p1, p3 );
			device->drawLine3D( p3, p4 );
		}
	}
}

void GridBuffer::setCircleUp( )
{
	float r = 1.f;
	for ( int i = 0; i < width; i ++ )
	{
		r = 0.f;
		for ( int j = 0; j < height; j ++ )
		{
			float div = ( float )j / ( float )height;
			float y = 2.f * sin( div * PI );
			gridBuffer[i][j].y = y;
		}
	}
}

void GridBuffer::setRandomUp( )
{
	for ( int i = 0; i < width; i ++ )
	{
		for ( int j = 0; j < height; j ++ )
		{
			int y = rand( ) % 3;
			gridBuffer[i][j].y = ( float )y;
		}
	}
}
