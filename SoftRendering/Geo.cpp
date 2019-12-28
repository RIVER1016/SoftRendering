#include "Geo.h"

void Geo::setDevice( Device dv )
{
	device = dv;
}

Cube::Cube( )
{
	Vector vc1( -2.f, -2.f, -2.f );
	Vector vc2( 2.f, -2.f, -2.f );
	Vector vc3( 2.f,2.f, -2.f );
	Vector vc4( -2.f, 2.f, -2.f );
	Vector vc5( -2.f, -2.f, 2.f );
	Vector vc6( 2.f, -2.f, 2.f );
	Vector vc7( 2.f, 2.f, 2.f );
	Vector vc8( -2.f, 2.f, 2.f );
	Vector c1( 0.f, 1.f, 0.f );
	Vector c2( 1.f, 0.f, 0.f );
	Vector c3( 0.f, 0.f, 1.f );
	Vector v0 = Vector( 0.f, 0.f, 0.f );
	Vertex vt1( vc1, c1, v0 );
	Vertex vt2( vc2, c2, v0 );
	Vertex vt3( vc3, c3, v0 );
	Vertex vt4( vc4, c1, v0 );
	Vertex vt5( vc5, c2, v0 );
	Vertex vt6( vc6, c3, v0 );
	Vertex vt7( vc7, c1, v0 );
	Vertex vt8( vc8, c2, v0 );
	v1 = vt1; v2 = vt2; v3 = vt3; v4 = vt4;
	v5 = vt5; v6 = vt6; v7 = vt7; v8 = vt8; 
}

Cube::Cube( Vertex vt1, Vertex vt2, Vertex vt3, Vertex vt4, Vertex vt5, Vertex vt6, Vertex vt7, Vertex vt8 )
{
	v1 = vt1;
	v2 = vt2;
	v3 = vt3;
	v4 = vt4;
	v5 = vt5;
	v6 = vt6;
	v7 = vt7;
	v8 = vt8;
}

void Cube::draw()
{
	device.draw3DRectangle( v4, v3, v2, v1 );
	device.draw3DRectangle( v5, v6, v7, v8 );
	device.draw3DRectangle( v1, v2, v6, v5 );
	device.draw3DRectangle( v1, v5, v8, v4 );
	device.draw3DRectangle( v4, v8, v7, v3 );
	device.draw3DRectangle( v3, v7, v6, v2 );
}

Sphere::Sphere( )
{
	radius = 1.0f;
}

Sphere::Sphere( float r )
{
	radius = r;
}

void Sphere::drawFlat( int n )
{
	Vector v1( radius, 0.f, 0.f );
	Vector v2( 0, -radius, 0.f );
	Vector v3( -radius, 0.f, 0.f );
	Vector v4( 0.f, radius, 0.f );
	Vector v5( 0.f, 0.f, radius );
	Vector v6( 0.f, 0.f, -radius );
	Vector n1( 1.f, 0.f, 0.f );
	Vector n2( 0, -1.f, 0.f );
	Vector n3( -1.f, 0.f, 0.f );
	Vector n4( 0.f, 1.f, 0.f );
	Vector n5( 0.f, 0.f, 1.f );
	Vector n6( 0.f, 0.f, -1.f );
	Vector c1( 1.f, 0.f, 0.f );
	Vector c2( 1.f, 0.f, 0.f );
	Vector c3( 1.f, 0.f, 0.f );
	Vector c4( 1.f, 0.f, 0.f );
	Vector c5( 1.f, 0.f, 0.f );
	Vector c6( 1.f, 0.f, 0.f );
	Vector ld( 0.f, 0.f, 1.f );
	Vector lc( 1.f, 1.f, 1.f );
	Vertex vt1( v1, c1, n1 );
	Vertex vt2( v2, c2, n2 );
	Vertex vt3( v3, c3, n3 );
	Vertex vt4( v4, c4, n4 );
	Vertex vt5( v5, c5, n5 );
	Vertex vt6( v6, c6, n6 );
	Triangle tri1( vt1, vt2, vt5 ), tri2( vt3, vt5, vt2 ),
		tri3( vt4, vt5, vt3 ), tri4( vt1, vt5 ,vt4 ),
		tri5( vt1, vt6, vt2 ), tri6( vt2, vt6, vt3 ), 
		tri7( vt3, vt6, vt4 ), tri8( vt4, vt6, vt1 );
	drawTriFlat( tri1, radius, n );
	drawTriFlat( tri2, radius, n );
	drawTriFlat( tri3, radius, n );
	drawTriFlat( tri4, radius, n );
	drawTriFlat( tri5, radius, n );
	drawTriFlat( tri6, radius, n );
	drawTriFlat( tri7, radius, n );
	drawTriFlat( tri8, radius, n );
}

void Sphere::drawGourand( int n )
{
	Vector v1( radius, 0.f, 0.f );
	Vector v2( 0, -radius, 0.f );
	Vector v3( -radius, 0.f, 0.f );
	Vector v4( 0.f, radius, 0.f );
	Vector v5( 0.f, 0.f, radius );
	Vector v6( 0.f, 0.f, -radius );
	Vector n1( 1.f, 0.f, 0.f );
	Vector n2( 0, -1.f, 0.f );
	Vector n3( -1.f, 0.f, 0.f );
	Vector n4( 0.f, 1.f, 0.f );
	Vector n5( 0.f, 0.f, 1.f );
	Vector n6( 0.f, 0.f, -1.f );
	Vector c1( 1.f, 0.f, 0.f );
	Vector c2( 1.f, 0.f, 0.f );
	Vector c3( 1.f, 0.f, 0.f );
	Vector c4( 1.f, 0.f, 0.f );
	Vector c5( 1.f, 0.f, 0.f );
	Vector c6( 1.f, 0.f, 0.f );
	Vector ld( 0.f, 0.f, 1.f );
	Vector lc( 1.f, 1.f, 1.f );
	Vertex vt1( v1, c1, n1 );
	Vertex vt2( v2, c2, n2 );
	Vertex vt3( v3, c3, n3 );
	Vertex vt4( v4, c4, n4 );
	Vertex vt5( v5, c5, n5 );
	Vertex vt6( v6, c6, n6 );
	Triangle tri1( vt1, vt2, vt5 ), tri2( vt3, vt5, vt2 ),
		tri3( vt4, vt5, vt3 ), tri4( vt1, vt5 ,vt4 ),
		tri5( vt1, vt6, vt2 ), tri6( vt2, vt6, vt3 ), 
		tri7( vt3, vt6, vt4 ), tri8( vt4, vt6, vt1 );
	drawTriGourand( tri1, radius, n );
	drawTriGourand( tri2, radius, n );
	drawTriGourand( tri3, radius, n );
	drawTriGourand( tri4, radius, n );
	drawTriGourand( tri5, radius, n );
	drawTriGourand( tri6, radius, n );
	drawTriGourand( tri7, radius, n );
	drawTriGourand( tri8, radius, n );
}

int Sphere::drawTriFlat( Triangle tri, float r, int n )
{
	Triangle *btri = new Triangle [4];
	btri = getBallTri( tri, r );
	if ( n == 1 )
	{
		btri = getBallTri( tri, r );
		for( int i = 0; i < 4; i ++ )
		{
			device.drawTriangle3DFlat( 1, btri[i] );
		}
		delete btri;
		return 0;
	}
	drawTriFlat( btri[0], r, n - 1 );
	drawTriFlat( btri[1], r, n - 1 );
	drawTriFlat( btri[2], r, n - 1 );
	drawTriFlat( btri[3], r, n - 1 );
	return 0;
}

int Sphere::drawTriGourand( Triangle tri, float r, int n )
{
	Triangle *btri = new Triangle [4];
	btri = getBallTri( tri, r );
	if ( n == 1 )
	{
		btri = getBallTri( tri, r );
		for( int i = 0; i < 4; i ++ )
		{
			device.draw3DFullTriangleLight( 1, btri[i] );
		}
		delete btri;
		return 0;
	}
	drawTriGourand( btri[0], r, n - 1 );
	drawTriGourand( btri[1], r, n - 1 );
	drawTriGourand( btri[2], r, n - 1 );
	drawTriGourand( btri[3], r, n - 1 );
	return 0;
}

Triangle* Sphere::getBallTri( Triangle tri, float r )
{
	Triangle *btri = new Triangle [4];
	Vector v4, v5, v6;
	Vector c4, c5, c6;
	Vector n4, n5, n6;
	v4 = tri.vertex1.position + ( tri.vertex3.position - tri.vertex1.position ) * 0.5;
	v4.normalize( );
	v4 = v4 * r;
	v5 = tri.vertex1.position + ( tri.vertex2.position - tri.vertex1.position ) * 0.5;
	v5.normalize( );
	v5 = v5 * r;
	v6 = tri.vertex2.position+ ( tri.vertex3.position - tri.vertex2.position ) * 0.5;
	v6.normalize( );
	v6 = v6 * r;
	c4 = ( tri.vertex1.color + tri.vertex3.color ) * 0.5;
	c5 = ( tri.vertex2.color + tri.vertex1.color ) * 0.5;
	c6 = ( tri.vertex2.color + tri.vertex3.color ) * 0.5;
	n4 = ( tri.vertex1.normal + tri.vertex3.normal ) * 0.5;
	n5 = ( tri.vertex2.normal + tri.vertex1.normal ) * 0.5;
	n6 = ( tri.vertex2.normal + tri.vertex3.normal ) * 0.5;
	Vertex vt4, vt5, vt6;
	vt4 = Vertex( v4, c4, n4 );
	vt5 = Vertex( v5, c5, n5 );
	vt6 = Vertex( v6, c6, n6 );
	btri[0] = Triangle( tri.vertex3, vt4, vt6 );
	btri[1] = Triangle( tri.vertex1, vt5, vt4 );
	btri[2] = Triangle( vt5, tri.vertex2, vt6 );
	btri[3] = Triangle( vt5, vt6, vt4 );
	return btri;
}