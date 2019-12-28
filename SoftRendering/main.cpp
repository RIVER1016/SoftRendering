#include "Screen.h"
#include "Device.h"
#include <tchar.h>
#include <stdio.h>
#include "Grid.h"
#include "Geo.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

Screen* screen = NULL;
Device* device = NULL;
Transform* transform = NULL;
Light* light = NULL;
GridBuffer* gridBuffer = NULL;

void DrawPoint( )
{
	Vector v1 = Vector( 50.f, 50.f, 0.f );
	Vector c1 = Vector( 1.f, 0.f, 0.f );
	device->drawPoint( v1, c1 );
}

void DrawLine( )
{
	Vector v1 = Vector( 10.f, 10.f, 0.f );
	Vector c1 = Vector( 1.f, 0.f, 0.f );

	Vector v2 = Vector( 60.f, 360.f, 0.f );
	Vector c2 = Vector( 0.f, 1.f, 0.f );

	Vector normal = v1 % v2;
	normal.normalize( );

	Vertex vertex1 = Vertex( v1, c1, normal );
	Vertex vertex2 = Vertex( v2, c2, normal );
	device->drawLine( vertex1, vertex2 );
}

void DrawLine3D( )
{
	Vector v1 = Vector( -1.f, 0.f, 0.f );
	Vector c1 = Vector( 1.f, 0.f, 0.f );

	Vector v2 = Vector( 1.f, 0.f, 0.f );
	Vector c2 = Vector( 0.f, 1.f, 0.f );

	Vector normal = v1 % v2;
	normal.normalize( );

	Vertex vertex1 = Vertex( v1, c1, normal );
	Vertex vertex2 = Vertex( v2, c2, normal );
	device-> drawLine3D( vertex1, vertex2 );
}

void DrawTriangleLine3D( )
{
	Vector v1 = Vector( -1.f, 0.f, 0.f );
	Vector c1 = Vector( 1.f, 0.f, 0.f );

	Vector v2 = Vector( 1.f, 0.f, 0.f );
	Vector c2 = Vector( 0.f, 1.f, 0.f );

	Vector v3 = Vector( 0.f, 1.f, 0.f );
	Vector c3 = Vector( 0.f, 0.f, 1.f );

	Vector normal = ( v3 - v1 ) % ( v2 - v1 );
	normal.normalize( );
	Vertex vertex1 = Vertex( v1, c1, normal );
	Vertex vertex2 = Vertex( v2, c2, normal );
	Vertex vertex3 = Vertex( v3, c3, normal );
	device->drawLine3D( vertex1, vertex2 );
	device->drawLine3D( vertex1, vertex3 );
	device->drawLine3D( vertex3, vertex2 );
}

void DrawTraingle3D2( const int & changeShader )
{

	Vector v1 = Vector( 0.f, 0.f, -1.f );
	Vector c1 = Vector( 1.f, 0.f, 0.f );

	Vector v2 = Vector( 2.f, 0.f, -1.f );
	Vector c2 = Vector( 0.f, 1.f, 0.f );

	Vector v3 = Vector( 1.f, 1.f, -1.f );
	Vector c3 = Vector( 0.f, 0.f, 1.f );

	Vector normal = ( v3 - v1 ) % ( v2 - v1 );
	normal.normalize( );
	Vertex vertex1 = Vertex( v1, c1, normal );
	Vertex vertex2 = Vertex( v2, c2, normal );
	Vertex vertex3 = Vertex( v3, c3, normal );
	Triangle tr = Triangle( vertex1, vertex2, vertex3 );
	device->drawTriangle3D( changeShader, tr );
}

void DrawTraingle3D( const int & changeShader )
{

	Vector v1 = Vector( -1.f, 0.f, 0.f );
	Vector c1 = Vector( 1.f, 0.f, 0.f );

	Vector v2 = Vector( 1.f, 0.f, 0.f );
	Vector c2 = Vector( 0.f, 1.f, 0.f );

	Vector v3 = Vector( 0.f, 1.f, 0.f );
	Vector c3 = Vector( 0.f, 0.f, 1.f );

	Vector normal = ( v3 - v1 ) % ( v2 - v1 );
	normal.normalize( );
	Vertex vertex1 = Vertex( v1, c1, normal );
	Vertex vertex2 = Vertex( v2, c2, normal );
	Vertex vertex3 = Vertex( v3, c3, normal );
	Triangle tr = Triangle( vertex1, vertex2, vertex3 );
	device->drawTriangle3D( changeShader, tr );
}

void draw3DCube( )
{
	Cube cube;
	cube.setDevice( *device );
	cube.draw( );
}

void drawFlatBall( float r )
{
	Sphere ball( r );
	ball.setDevice( *device );
	ball.drawFlat( 3 );
}

void drawGourandBall( float r )
{
	Sphere ball( r );
	ball.setDevice( *device );
	ball.drawGourand( 3 );
}

void Walk( float x, float y, float z, float ar, float br, float cr )
{
	Camera camera = transform->getCamera( );
	camera.walk( x, y, z );
	camera.pitch( ar );
	camera.yaw( br );
	camera.roll( cr );
	transform->setCamera( camera );
	transform->setView( );
}

void SetWorld( const float& theta )
{
	Vector translate = Vector( 0.f, 0.f, 0.f, 1.f );
	Vector rotate = Vector( 0.f, 1.f, 0.f, 1.f );
	transform->setWorld( translate, rotate, theta );
	transform->update( );
}

#define VK_A 0x41
#define VK_D 0x44
#define VK_W 0x57
#define VK_S 0x53
#define VK_J 0x4A
#define VK_K 0x4B
#define VK_M 0x4D
#define VK_N 0x4E

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE prevInstance, PSTR cmdLine, int showCmd )
{

	screen = new Screen( );
	int ret = screen->init( WINDOW_WIDTH, WINDOW_HEIGHT, _T( "SoftRendering" ) );
	if ( ret < 0 )
	{
		printf( "screen init failed(%d)!\n", ret );
		exit( ret );
	}
	Vector position = Vector( 0.f, 0.f, 5.f );
	Vector right = Vector( -1.f, 0.f, 0.f );
	Vector up = Vector( 0.f, 1.f, 0.f );
	Vector look = Vector( 0.f, 0.f, -1.f );
	Camera camera;
	camera.init( position, right, look, up );
	transform = new Transform( );
	transform->init( WINDOW_WIDTH, WINDOW_HEIGHT, camera );
	uint32* wfb = ( uint32* )( screen->getFrameBuffer( ) );

	//light = new Light( Vector( 1.f, 1.f, 1.f ), Vector( 0.f, -0.3f, 1.f ), Vector( 2.f, 2.f, 2.f ), 10.f );
	light = new Light( Vector( 1.f, 1.f, 1.f ), Vector( 0.f, 0.3f, -1.f ), Vector( 2.f, 2.f, 2.f ), 10.f );
	device = new Device( );
	device->init( WINDOW_WIDTH, WINDOW_HEIGHT, wfb, transform, light );

	gridBuffer = new GridBuffer( );
	Vector originBottom = Vector( -3.f, 0.f, -2.f );
	gridBuffer->init( device, originBottom, 2.f, 20, 10 );
	gridBuffer->setRandomUp( );

	float theta = 0.f;
	float dist = 0.f;
	float an1 = 0.f;
	float an2 = 0.f;
	float an3 = 0.f;
	float rightControl = 0.f;
	float upControl = 0.f;
	int fillTriangle = 0;	// 改变光渲染效果
	//int diffuse = 1;	// 改变光渲染效果
	//int blinnPhong = 2;
	//int materialShader = 3;
	//int phong = 4;
	//int blendPhong = 5;
	while ( !screen->isExit( ) )
	{
		device->clear( );
		screen->dispatch( );
		Walk( rightControl, upControl, dist, an1, an2, an3 );
		an1 = an2 = an3 = rightControl = upControl =  dist = 0.f;
		theta += 0.05f;
		SetWorld( theta );
		if ( screen->isKeyPressed( VK_A ) )
			rightControl += 0.01f;
		if ( screen->isKeyPressed( VK_D ) )
			rightControl -= 0.01f;
		if ( screen->isKeyPressed( VK_W ) )
			dist -= 0.01f;
		if ( screen->isKeyPressed( VK_S ) )
			dist += 0.01f;
		if ( screen->isKeyPressed( VK_J ) )	// 上天
			upControl += 0.01f;
		if ( screen->isKeyPressed( VK_K ) )	// 入地
			upControl -= 0.01f;

		if ( screen->isKeyPressed( VK_LEFT ) )	// 向左看
			an2 += 0.001f;
		if ( screen->isKeyPressed( VK_RIGHT ) )	// 向右看
			an2 -= 0.001f;
		if ( screen->isKeyPressed( VK_UP ) )	// 抬头
			an1 -= 0.001f;
		if ( screen->isKeyPressed( VK_DOWN ) )	// 低头
			an1 += 0.001f;
		if ( screen->isKeyPressed( VK_M ) )
			an3 += 0.001f;
		if ( screen->isKeyPressed( VK_N ) )
			an3 -= 0.001f;

		//gridBuffer->draw( );
		//DrawPoint( );
		//DrawLine( );
		//DrawLine3D( );
		//DrawTriangleLine3D( );
		//DrawTraingle3D( fillTriangle );
		//DrawTraingle3D2( fillTriangle );
		//DrawTraingle3D( phong );
		//DrawTraingle3D( blinnPhong );
		//DrawTraingle3D( diffuse );
		//DrawTraingle3D( materialShader );
		//DrawTraingle3D( blendPhong );
		//draw3DCube( );
		//drawFlatBall( 2.0 );
		drawGourandBall( 2.0 );

		screen->dispatch( );
		screen->update( );
		Sleep( 1 );
	}

	screen->close( );

	delete screen;
	delete device;
	delete transform;
	delete light;
	delete gridBuffer;

	return 0;
}
