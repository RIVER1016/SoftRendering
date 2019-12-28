#pragma once

// �������
#include <windows.h>

class Screen
{
public:
	int init( int width, int height, LPCTSTR title ); // ��ʼ������
	void update( ); // ����
	void dispatch( ); // �ɷ���Ϣ
	void close( ); // �ر�
	int isExit( ); // �Ƿ�ر�
	int isKeyPressed( int key );
	int getKeyUpEvent( int key );
	LPVOID getFrameBuffer( ); 

private:
	HWND wndHandle;
	HDC wndDc;
	HBITMAP wndHb;
	HBITMAP wndOb;
	LPVOID wndFramebuffer; // framebuffer
	int width;
	int height;
};
