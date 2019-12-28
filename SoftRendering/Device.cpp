#pragma once
#include "Device.h"
#include <Windows.h>

void Device::init( const int& w, const int& h, uint32* fb, Transform* ts, Light* li )
{
	width = w;
	height = h;

	// fb 为窗口显示缓存
	framebuffer = ( uint32** )malloc( h * sizeof( uint32* ) );
	for ( int y = 0; y < h; y ++ )
	{
		framebuffer[y] = fb + y * w;
	}
	zbuffer = ( float* )malloc( w * h * sizeof( float ) );
	memset( zbuffer, 0, w * h * sizeof( float ) );
	transform = ts;
	light = li;
}

void Device::drawPoint( const Vector& v, const Vector& c )
{
	int x = ( int )v.x;
	int y = ( int )v.y;

	if ( x >= width || x < 0 ) return;
	if ( y >= height || y < 0 ) return;
	if ( zbuffer[y * width + x] < v.z ) return;

	int fcolor = 0;
	int r = ( int )( c.x * 255 );
	int g = ( int )( c.y * 255 );
	int b = ( int )( c.z * 255 );

	fcolor = ( r << 16 ) | ( g << 8 ) | b;
	framebuffer[y][x] = fcolor;
	zbuffer[y * width + x] = v.z;
}

void Device::drawLine( const Vertex& vertex1, const Vertex& vertex2 )
{
	Vertex ver1 = vertex1;
	Vertex ver2 = vertex2;

	Vector vTemp, cTemp;
	float sx = ver1.position.x;
	float ex = ver2.position.x;
	float sy = ver1.position.y;
	float ey = ver2.position.y;

	float deltaX = ex - sx;
	float deltaY = ey - sy;
	float k;

	if ( deltaX == 0 )
		k = 1.f;
	else
		k = deltaY / deltaX;

	if ( k < 0 )
	{
		k = k * -1;
	}

	if ( k < 1 )
	{
		if( deltaX < 0 )
		{
			Vertex temp;
			temp = ver1;
			ver1 = ver2;
			ver2 = temp;
		}

		sx = ver1.position.x;
		ex = ver2.position.x;
		vTemp = ver2.position - ver1.position;
		cTemp = ver2.color - ver1.color;

		for ( float x = sx; x < ex; x ++ )
		{
			float gradient = ( x - sx ) / ( float )( ex - sx );

			Vector newV, newC;
			newV = ver1.position + vTemp * gradient;
			newC = ver1.color + cTemp * gradient;
			drawPoint( newV, newC );
		}
	}
	else
	{
		if( deltaY < 0 )
		{
			Vertex temp;
			temp = ver1;
			ver1 = ver2;
			ver2 = temp;
		}

		sy = ver1.position.y;
		ey = ver2.position.y;
		vTemp = ver2.position - ver1.position;
		cTemp = ver2.color - ver1.color;

		for ( float y = sy; y < ey; y ++ )
		{
			float gradient = ( y - sy ) / ( float )( ey - sy );

			Vector newV, newC;
			newV = ver1.position + vTemp * gradient;
			newC = ver1.color + cTemp * gradient;
			drawPoint( newV, newC );
		}
	}
}

void Device::drawLine3D( const Vertex& vertex1, const Vertex& vertex2 )
{
	Matrix wvp = transform->getWVP( );
	Vector pos1 =  vertex1.position * wvp;
	Vector pos2 =  vertex2.position * wvp;

	if ( pos1.w < 0 )
		return;
	if ( pos2.w < 0 )
		return;

	Vector v1 = transform->homogenize( pos1 );
	Vector v2 = transform->homogenize( pos2 );

	Vector c1 = vertex1.color;
	Vector c2 = vertex2.color;

	Vertex ver1 = vertex1;
	Vertex ver2 = vertex2;
	ver1.position = v1;
	ver2.position = v2;
	if ( v1.x < 0 || v1.x > width || v1.y < 0 || v1.y > height )
	{
		if ( v2.x < 0 || v2.x > width || v2.y < 0 || v2.y > height )
		{
			return;
		}
		else
		{
			// TODO: v1不在屏幕里v2在
			Vector vTemp = v1 - v2;
			float gradientY1 = ( 0.f - v2.y ) / ( v1.y - v2.y );
			float gradientY2 = ( height - v2.y ) / ( v1.y - v2.y );
			float gradientX1 = ( 0.f - v2.x ) / ( v1.x - v2.x );
			float gradientX2 = ( width - v2.x ) / ( v1.x - v2.x );
			if ( gradientY1 > 0 )
			{
				Vector newV = v2 + vTemp * gradientY1;
				if ( newV.x >= 0.f && newV.x <= width )
				{
					ver1.position = newV;
					drawLine( ver1, ver2 );
				}
			}
			if ( gradientY2 > 0 )
			{
				Vector newV = v2 + vTemp * gradientY2;
				if ( newV.x >= 0.f && newV.x <= width )
				{
					ver1.position = newV;
					drawLine( ver1, ver2 );
				}
			}
			if ( gradientX1 > 0 )
			{
				Vector newV = v2 + vTemp * gradientX1;
				if ( newV.y >= 0.f && newV.y <= height )
				{
					ver1.position = newV;
					drawLine( ver1, ver2 );
				}
			}
			if ( gradientX2 > 0 )
			{
				Vector newV = v2 + vTemp * gradientX2;
				if ( newV.y >= 0.f && newV.y <= height )
				{
					ver1.position = newV;
					drawLine( ver1, ver2 );
				}
			}
		}
	}
	else
	{
		if ( v2.x < 0 || v2.x > width || v2.y < 0 || v2.y > height )
		{
			// TODO: v1在屏幕里v2不在
			Vector vTemp = v2 - v1;
			float gradientY1 = ( 0.f - v1.y ) / ( v2.y - v1.y );
			float gradientY2 = ( height - v1.y ) / ( v2.y - v1.y );
			float gradientX1 = ( 0.f - v1.x ) / ( v2.x - v1.x );
			float gradientX2 = ( width - v1.x ) / ( v2.x - v1.x );
			if ( gradientY1 > 0 )
			{
				Vector newV = v1 + vTemp * gradientY1;
				if ( newV.x >= 0.f && newV.x <= width )
				{
					ver2.position = newV;
					drawLine( ver1, ver2 );
				}
			}
			if ( gradientY2 > 0 )
			{
				Vector newV = v1 + vTemp * gradientY2;
				if ( newV.x >= 0.f && newV.x <= width )
				{
					ver2.position = newV;
					drawLine( ver1, ver2 );
				}
			}
			if ( gradientX1 > 0 )
			{
				Vector newV = v1 + vTemp * gradientX1;
				if ( newV.y >= 0.f && newV.y <= height )
				{
					ver2.position = newV;
					drawLine( ver1, ver2 );
				}
			}
			if ( gradientX2 > 0 )
			{
				Vector newV = v1 + vTemp * gradientX2;
				if ( newV.y >= 0.f && newV.y <= height )
				{
					ver2.position = newV;
					drawLine( ver1, ver2 );
				}
			}
		}
		else
			drawLine( ver1, ver2 );
	}
}

void Device::fillTopFlatTriangle( const int& changeShader, const Vertex& vertex1, const Vertex& vertex2, const Vertex& vertex3 )
{
	Vector p1 = vertex1.position;
	Vector p2 = vertex2.position;
	Vector p3 = vertex3.position;

	Vector c1 = vertex1.color;
	Vector c2 = vertex2.color;
	Vector c3 = vertex3.color;

	Vector wp1 = vertex1.worldpos;
	Vector wp2 = vertex2.worldpos;
	Vector wp3 = vertex3.worldpos;

	Vector vTemp1 = p3 - p2;
	Vector vTemp2 = p3 - p1;

	Vector cTemp1 = c3 - c2;
	Vector cTemp2 = c3 - c1;

	Vector nTemp1 = vertex3.normal - vertex2.normal;
	Vector nTemp2 = vertex3.normal - vertex1.normal;

	Vector wTemp1 = wp3 - wp2;
	Vector wTemp2 = wp3 - wp1;

	for ( float y = p2.y; y <= (int)p3.y; y ++ )
	{
		// compute gradient
		float gradientY;
		if ( p3.y == p2.y )
			gradientY = 1.f;
		else
			gradientY = ( y - p2.y ) / ( float )( p3.y - p2.y );

		// start & end vertex
		Vertex st, ed;
		st.position = p2 + vTemp1 * gradientY;
		st.color = c2 + cTemp1 * gradientY;
		st.normal = vertex2.normal + nTemp1 * gradientY;
		st.worldpos = wp2 + wTemp1 * gradientY;

		ed.position = p1 + vTemp2 * gradientY;
		ed.color = c1 + cTemp2 * gradientY;
		ed.normal = vertex1.normal + nTemp1 * gradientY;
		ed.worldpos = wp1 + wTemp2 * gradientY;

		Vector vTemp = ed.position - st.position;
		Vector cTemp = ed.color - st.color;

		int se = ( int )st.position.x;
		int ex = ( int )ed.position.x;

		for ( int x = se; x <= ex; x ++ )
		{
			float gradientX = ( x - se ) / ( float )( ex - se );
			if ( gradientX >= 0 )
			{
				Vector newV, newC;
				newV.z = st.position.z + vTemp.z * gradientX;
				newV.x = ( float )x;
				newV.y = ( float )y;
				newC = st.color + cTemp * gradientX;

				// add light affect
				Vertex newVertex;
				newVertex.position = newV;
				newVertex.color = newC;
				newVertex.normal = st.normal + ( ed.normal - st.normal ) * gradientX;
				newVertex.worldpos = st.worldpos + ( ed.worldpos - st.worldpos ) * gradientX;

				// add light affect
				switch( changeShader )
				{
				case 0: break;	// fill triangle
				case 1: 
					{
						// add diffuse
						newC = newC.mul( light->diffuse( newVertex ) );
						break;
					}
				case 2: 
					{
						// blinn-phong reflect
						newC = light->blinnPhongSpecularReflection( newVertex, transform );
						break;
					}
				case 3: 
					{
						// material shader
						newC = newC.mul( light->diffuse( newVertex ) );
						newC = newC + light->blinnPhongSpecularReflection( newVertex, transform );
						break;
					}
				case 4: 
					{
						// phong reflect
						newC = light->phongSpecularReflection( newVertex, transform );
						break;
					}
				case 5: 
					{
						// blend shader
						newC = newC.mul( light->diffuse( newVertex ) );
						newC = newC + light->phongSpecularReflection( newVertex, transform );
						break;
					}
				}

				// make sure r,g,b during [0, 1]
				newC.x = saturate( newC.x );
				newC.y = saturate( newC.y );
				newC.z = saturate( newC.z );

				// draw point by  position & color
				drawPoint( newV, newVertex.normal );
			}
		}
	}
}

void Device::fillBottomFlatTriangle( const int& changeShader, const Vertex& vertex1, const Vertex& vertex2, const Vertex& vertex3 )
{
	Vector p1 = vertex1.position;
	Vector p2 = vertex2.position;
	Vector p3 = vertex3.position;

	Vector c1 = vertex1.color;
	Vector c2 = vertex2.color;
	Vector c3 = vertex3.color;

	Vector wp1 = vertex1.worldpos;
	Vector wp2 = vertex2.worldpos;
	Vector wp3 = vertex3.worldpos;

	Vector vTemp1 = p2 - p1;
	Vector vTemp2 = p3 - p1;

	Vector cTemp1 = c2 - c1;
	Vector cTemp2 = c3 - c1;

	Vector wTemp1 = wp2 - wp1;
	Vector wTemp2 = wp3 - wp1;

	for ( float y = p1.y; y <= (int)p2.y; y ++ )
	{
		// compute gradient
		float gradientY;
		if ( p2.y == p1.y )
			gradientY = 1.f;
		else
			gradientY = ( y - p1.y ) / ( float ) ( p2.y - p1.y );

		// start & end vertex
		Vertex st, ed;
		st.position = p1 + vTemp1 * gradientY;
		st.color = c1 + cTemp1 * gradientY;
		st.normal = vertex1.normal + ( vertex2.normal -  vertex1.normal ) * gradientY;
		st.worldpos = wp1 + wTemp1 * gradientY;

		ed.position = p1 + vTemp2 * gradientY;
		ed.color = c1 + cTemp2 * gradientY;
		ed.normal = vertex1.normal + ( vertex3.normal -  vertex1.normal ) * gradientY;
		ed.worldpos = wp1 + wTemp2 * gradientY;

		Vector vTemp = ed.position - st.position;
		Vector cTemp = ed.color - st.color;

		int se = ( int )st.position.x;
		int ex = ( int )ed.position.x;

		for ( int x = se; x <= ex; x ++ )
		{
			float gradientX = ( x - se ) / ( float )( ex - se );
			if ( gradientX >= 0 )
			{
				Vector newV, newC;
				newV.z = st.position.z + vTemp.z * gradientX;
				newV.x = ( float )x;
				newV.y = ( float )y;
				newC = st.color + cTemp * gradientX;

				Vertex newVertex;
				newVertex.position = newV;
				newVertex.color = newC;
				newVertex.normal = st.normal + ( ed.normal - st.normal ) * gradientX;
				newVertex.worldpos = st.worldpos + ( ed.worldpos - st.worldpos ) * gradientX;

				// add light affect
				switch( changeShader )
				{
				case 0: break;	// fill triangle
				case 1: 
					{
						// add diffuse
						newC = newC.mul( light->diffuse( newVertex ) );
						break;
					}
				case 2: 
					{
						// blinn-phong reflect
						newC = light->blinnPhongSpecularReflection( newVertex, transform );
						break;
					}
				case 3: 
					{
						// material shader
						newC = newC.mul( light->diffuse( newVertex ) );
						newC = newC + light->blinnPhongSpecularReflection( newVertex, transform );
						break;
					}
				case 4: 
					{
						// phong reflect
						newC = light->phongSpecularReflection( newVertex, transform );
						break;
					}
				case 5: 
					{
						// blend shader
						newC = newC.mul( light->diffuse( newVertex ) );
						newC = newC + light->phongSpecularReflection( newVertex, transform );
						break;
					}
				}

				// make sure r,g,b during [0, 1]
				newC.x = saturate( newC.x );
				newC.y = saturate( newC.y );
				newC.z = saturate( newC.z );
				if ( newVertex.normal == Vector( 0.f, 0.f, 0.f ) )
				{
					drawPoint( newV, newVertex.normal );
				}
				// draw point by  position & color
				drawPoint( newV, newVertex.normal );
			}
		}
	}
}

void Device::drawTriangle3D( const int& changeShader, const Triangle& tr )
{
	Matrix wvpMatrix = transform->getWVP( );
	Matrix worldMatrix = transform->getWorld( );
	Vector pos1 = tr.vertex1.position * wvpMatrix;
	Vector pos2 = tr.vertex2.position * wvpMatrix;
	Vector pos3 = tr.vertex3.position * wvpMatrix;

	if ( !pos1.checkCvv( pos1 ) ) return;
	if ( !pos1.checkCvv( pos2 ) ) return;
	if ( !pos1.checkCvv( pos3 ) ) return;

	Vector p1 = transform->homogenize( pos1 );
	Vector p2 = transform->homogenize( pos2 );
	Vector p3 = transform->homogenize( pos3 );

	// backface culling
	//if ( transform->backFaceCulling( p1, p2, p3 ) ) return;

	// sort vertex by y axis
	Vertex ver1 = tr.vertex1;
	Vertex ver2 = tr.vertex2;
	Vertex ver3 = tr.vertex3;
	ver1.position = p1;
	ver2.position = p2;
	ver3.position = p3;

	ver1.normal = tr.vertex1.normal * worldMatrix;
	ver2.normal = tr.vertex2.normal * worldMatrix;
	ver3.normal = tr.vertex3.normal * worldMatrix;

	ver1.worldpos = tr.vertex1.position * worldMatrix;
	ver2.worldpos = tr.vertex2.position * worldMatrix;
	ver3.worldpos = tr.vertex3.position * worldMatrix;

	Vertex temp;
	if ( ver1.position.y > ver2.position.y )
	{
		temp = ver1;
		ver1 = ver2;
		ver2 = temp;
	}
	if ( ver1.position.y > ver3.position.y )
	{
		temp = ver1;
		ver1 = ver3;
		ver3 = temp;
	}
	if ( ver2.position.y > ver3.position.y )
	{
		temp = ver2;
		ver2 = ver3;
		ver3 = temp;
	}

	// compute ver4
	Vector vTemp = ver1.position - ver3.position;
	Vector cTemp = ver1.color - ver3.color;
	Vector nTemp = ver1.normal - ver3.normal;
	Vector wTemp = ver1.worldpos - ver3.worldpos;

	float gradient = ( ver2.position.y - ver3.position.y ) / vTemp.y;

	Vertex ver4;
	ver4.position = ver3.position + vTemp * gradient;
	ver4.color = ver3.color + cTemp * gradient;
	ver4.normal = ver3.normal + nTemp * gradient;
	ver4.worldpos = ver3.worldpos + wTemp * gradient;

	// drawTopTriangle
	if ( ver4.position.x > ver2.position.x )
	{
		fillBottomFlatTriangle( changeShader, ver1, ver2, ver4 );
		fillTopFlatTriangle( changeShader, ver4, ver2, ver3 );
	}
	else
	{
		fillBottomFlatTriangle( changeShader, ver1, ver4, ver2 );
		fillTopFlatTriangle( changeShader, ver2, ver4, ver3 );
	}
}

void Device::drawTriangle3DFlat( const int& changeShader, const Triangle& tr )
{
	Matrix wvpMatrix = transform->getWVP( );
	Matrix worldMatrix = transform->getWorld( );
	Vector pos1 = tr.vertex1.position * wvpMatrix;
	Vector pos2 = tr.vertex2.position * wvpMatrix;
	Vector pos3 = tr.vertex3.position * wvpMatrix;

	if ( !pos1.checkCvv( pos1 ) ) return;
	if ( !pos1.checkCvv( pos2 ) ) return;
	if ( !pos1.checkCvv( pos3 ) ) return;

	Vector p1 = transform->homogenize( pos1 );
	Vector p2 = transform->homogenize( pos2 );
	Vector p3 = transform->homogenize( pos3 );

	// backface culling
	//if ( transform->backFaceCulling( p1, p2, p3 ) ) return;

	// sort vertex by y axis
	Vertex ver1 = tr.vertex1;
	Vertex ver2 = tr.vertex2;
	Vertex ver3 = tr.vertex3;
	ver1.position = p1;
	ver2.position = p2;
	ver3.position = p3;

	Vector normal = ( tr.vertex1.normal * worldMatrix + tr.vertex2.normal * worldMatrix + tr.vertex3.normal * worldMatrix ) * ( 1.f / 3.f );
	ver1.normal = normal;
	ver2.normal = normal;
	ver3.normal = normal;

	ver1.worldpos = tr.vertex1.position * worldMatrix;
	ver2.worldpos = tr.vertex2.position * worldMatrix;
	ver3.worldpos = tr.vertex3.position * worldMatrix;

	Vertex temp;
	if ( ver1.position.y > ver2.position.y )
	{
		temp = ver1;
		ver1 = ver2;
		ver2 = temp;
	}
	if ( ver1.position.y > ver3.position.y )
	{
		temp = ver1;
		ver1 = ver3;
		ver3 = temp;
	}
	if ( ver2.position.y > ver3.position.y )
	{
		temp = ver2;
		ver2 = ver3;
		ver3 = temp;
	}

	// compute ver4
	Vector vTemp = ver1.position - ver3.position;
	Vector cTemp = ver1.color - ver3.color;
	Vector nTemp = ver1.normal - ver3.normal;
	Vector wTemp = ver1.worldpos - ver3.worldpos;

	float gradient = ( ver2.position.y - ver3.position.y ) / vTemp.y;

	Vertex ver4;
	ver4.position = ver3.position + vTemp * gradient;
	ver4.color = ver3.color + cTemp * gradient;
	ver4.normal = ver3.normal + nTemp * gradient;
	ver4.worldpos = ver3.worldpos + wTemp * gradient;

	// drawTopTriangle
	if ( ver4.position.x > ver2.position.x )
	{
		fillBottomFlatTriangle( changeShader, ver1, ver2, ver4 );
		fillTopFlatTriangle( changeShader, ver4, ver2, ver3 );
	}
	else
	{
		fillBottomFlatTriangle( changeShader, ver1, ver4, ver2 );
		fillTopFlatTriangle( changeShader, ver2, ver4, ver3 );
	}
}

void Device::draw3DFullTriangleLight( const int& changeShader, const Triangle& tri )
{
	Matrix wvp, world;
	wvp = transform->getWVP( );
	world = transform->getWorld( );
	Vector pos1, pos2, pos3, phom1, phom2, phom3, pn1, pn2, pn3;
	pos1 = tri.vertex1.position * wvp;
	pos2 = tri.vertex2.position * wvp;
	pos3 = tri.vertex3.position * wvp;
	phom1 = transform->homogenize( pos1 );
	phom2 = transform->homogenize( pos2 );
	phom3 = transform->homogenize( pos3 );
	pn1 = tri.vertex1.normal * world;
	pn2 = tri.vertex2.normal * world;
	pn3 = tri.vertex3.normal * world;
	if( !pos1.checkCvv( pos1 ) ) return;
	if( !pos2.checkCvv( pos2 ) ) return;
	if( !pos3.checkCvv( pos3 ) ) return;
	Vector min, max;
	min.x = phom1.x;
	min.y = phom1.y;
	max.x = phom1.x;
	max.y = phom1.y;
	if( phom2.x < min.x ) min.x = phom2.x;
	if( phom3.x < min.x ) min.x = phom3.x;
	if( phom2.y < min.y ) min.y = phom2.y;
	if( phom3.y < min.y ) min.y = phom3.y;
	if( phom2.x > max.x ) max.x = phom2.x;
	if( phom3.x > max.x ) max.x = phom3.x;
	if( phom2.y > max.y ) max.y = phom2.y;
	if( phom3.y > max.y ) max.y = phom3.y;
	Vector checkp1, checkp2, check;
	checkp1 = phom2 - phom1;
	checkp2 = phom3 - phom2;
	check = checkp2 % checkp1;
	if( check.z < 0 ) return;
	for( int x = ( int )min.x; x <= ( int )max.x; x ++ )
	{
		for( int y = ( int )min.y; y <= ( int )max.y; y ++ )
		{
			float c = caculate( phom1, phom2, phom3, x, y );
			float b = caculate( phom1, phom3, phom2, x, y );
			float a = 1 - b - c;
			if ( a >= 0 && a <= 1 && b >= 0 && b <= 1 && c >= 0 && c <= 1 )
			{
				Vector pc = tri.vertex1.color * a + tri.vertex2.color * b + tri.vertex3.color * c;
				float z = phom1.z * a + phom2.z * b + phom3.z * c;
				Vector pnn = ( pn1 * a + pn2 * b + pn3 * c );
				Vector p( ( float )x, ( float )y, ( float )z );
				Vertex newVertex;
				newVertex.position = p;
				newVertex.color = pc;
				newVertex.normal = pnn;
				Vector newC = pc;
				// add light affect
				switch( changeShader )
				{
				case 0: break;	// fill triangle
				case 1: 
					{
						// add diffuse
						newC = newC.mul( light->diffuse( newVertex ) );
						break;
					}
				case 2: 
					{
						// blinn-phong reflect
						newC = light->blinnPhongSpecularReflection( newVertex, transform );
						break;
					}
				case 3: 
					{
						// material shader
						newC = newC.mul( light->diffuse( newVertex ) );
						newC = newC + light->blinnPhongSpecularReflection( newVertex, transform );
						break;
					}
				case 4: 
					{
						// phong reflect
						newC = light->phongSpecularReflection( newVertex, transform );
						break;
					}
				case 5: 
					{
						// blend shader
						newC = newC.mul( light->diffuse( newVertex ) );
						newC = newC + light->phongSpecularReflection( newVertex, transform );
						break;
					}
				}

				// make sure r,g,b during [0, 1]
				newC.x = saturate( newC.x );
				newC.y = saturate( newC.y );
				newC.z = saturate( newC.z );
				drawPoint( p, newC );
			}
		}
	}
}

void Device::draw3DRectangle( const Vertex& p1, const Vertex& p2, const Vertex& p3, const Vertex& p4 )
{
	Triangle tri1 = Triangle( p3, p2, p1 );
	Triangle tri2 = Triangle( p1, p4, p3 );
	int shader = 0;
	drawTriangle3D( shader, tri1 );
	drawTriangle3D( shader, tri2 );
}

void Device::clear( )
{
	for ( int y = 0; y < height; y ++ )
	{
		for ( int x = 0; x < width; x ++ )
		{
			int c = 0;
			framebuffer[y][x] = ( c << 16| c << 8 | c );
			zbuffer[y * width + x] = 1.f;
		}
	}
}

void Device::close( )
{
	if ( framebuffer != NULL )
	{
		free( framebuffer );
	}
}
