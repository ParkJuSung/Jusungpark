// include the basic windows header files and the Direct3D header file
#include <windows.h>
#include <windowsx.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <iostream>
#include <math.h>
#include"resource.h"
#include <MMSystem.h>
// define the screen resolution and keyboard macros
#define SCREEN_WIDTH  1024
#define SCREEN_HEIGHT 500
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
#define KEY_UP(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 0 : 1)
#define ENEMY_NUM 10

// include the Direct3D Library file
#pragma comment(lib, "winmm.lib")
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")

// global declarations
LPDIRECT3D9 d3d;    // the pointer to our Direct3D interface
LPDIRECT3DDEVICE9 d3ddev;    // the pointer to the device class
LPD3DXSPRITE d3dspt;    // the pointer to our Direct3D Sprite interface

						// sprite declarations
LPDIRECT3DTEXTURE9 sprite_background;    // 배경1
LPDIRECT3DTEXTURE9 sprite_background2;    // 배경2
LPDIRECT3DTEXTURE9 sprite_hero;    // the pointer to the sprite
LPDIRECT3DTEXTURE9 sprite_enemy;    // enemy1
LPDIRECT3DTEXTURE9 sprite_enemy2;    // enemy2
LPDIRECT3DTEXTURE9 sprite_Boss;    // Boss
LPDIRECT3DTEXTURE9 sprite_slave; //Boss slave
LPDIRECT3DTEXTURE9 sprite_slave1; //Boss slave1
LPDIRECT3DTEXTURE9 sprite_Boss_bullet;
LPDIRECT3DTEXTURE9 sprite_Boss_bullet2;
LPDIRECT3DTEXTURE9 sprite_Boss_bullet3;
LPDIRECT3DTEXTURE9 sprite_bullet;    // 위방향
LPDIRECT3DTEXTURE9 sprite_Bbullet; // 아래방향
LPDIRECT3DTEXTURE9 sprite_skill; //
LPDIRECT3DTEXTURE9 sprite_skill1; //
LPDIRECT3DTEXTURE9 sprite_skill2; //
LPDIRECT3DTEXTURE9 sprite_skill3; //
LPDIRECT3DTEXTURE9 sprite_Main;    // the pointer to the sprite
LPDIRECT3DTEXTURE9 sprite_SOne;    // 스코어 1의자리
LPDIRECT3DTEXTURE9 sprite_STen;    // 스코어 10의자리
LPDIRECT3DTEXTURE9 sprite_SHund;    // 스코어 100의자리
LPDIRECT3DTEXTURE9 sprite_SThou;    // 스코어 1000의자리
LPDIRECT3DTEXTURE9 sprite_GameOver;    // the pointer to the sprite
LPDIRECT3DTEXTURE9 sprite_EnemyBullet;    // Enemy1 Bullet
LPDIRECT3DTEXTURE9 sprite_Enemy2Bullet;    // Enemy2 Bullet
LPDIRECT3DTEXTURE9 sprite_Clear;    //Clear Screen

bool start = false;
bool isLive = true;
bool effect = false;
bool isClear = false;

int score = 0;
int Bullet_Time=16;
int wave = 1;
int Boss_Pattern = 0;
									 // function prototypes
void initD3D(HWND hWnd);    // sets up and initializes Direct3D
void render_frame(void);    // renders a single frame
void cleanD3D(void);		// closes Direct3D and releases memory
void init_game(void);
void do_game_logic(void);
bool sphere_collision_check(float x0, float y0, float size0, float x1, float y1, float size1);
void Score_Manager();
void Coll();
void B_Coll();
void Enemy_Move(bool &Create);
void Create_Wave(int wave, bool &Create);
void Wave_Up(bool &Create);
void Image_Change(int score, LPDIRECT3DTEXTURE9 &Num_image);
// the WindowProc function prototype
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

using namespace std;

enum { MOVE_UP, MOVE_DOWN, MOVE_LEFT, MOVE_RIGHT };


//기본 클래스 
class entity {

public:
	float x_pos;
	float y_pos;
	int status;
	int HP;
	int speed;
};


bool sphere_collision_check(float x0, float y0, float size0, float x1, float y1, float size1)
{

	if ((x0 - x1)*(x0 - x1) + (y0 - y1)*(y0 - y1) < (size0 + size1) * (size0 + size1))
		return true;
	else
		return false;
}


//주인공 클래스 
class Hero :public entity {

public:
	void fire();
	void super_fire();
	void move(int i);
	void init(float x, float y);


};

void Hero::init(float x, float y)
{

	x_pos = x;
	y_pos = y;

}

void Hero::move(int i)
{
	switch (i)
	{
	case MOVE_UP:
		if (y_pos >=0)
			y_pos -= 20;
		
		break;

	case MOVE_DOWN:
		if(y_pos<440)
			y_pos += 20;
		break;


	case MOVE_LEFT:
		if(x_pos>0)
			x_pos -= 20;
		break;


	case MOVE_RIGHT:
		if(x_pos<960)
			x_pos += 20;
		break;

	}

}




// 적 클래스 
class Enemy :public entity {

public:
	void init(float x, float y);
	void move();
	void Forward_move();
	bool Enemy_Show;
};

void Enemy::init(float x, float y)
{

	x_pos = x;
	y_pos = y;

}


void Enemy::move()
{
	y_pos += speed;

}

void Enemy::Forward_move()
{
	y_pos -=speed;
}


// 총알 클래스 
class Bullet :public entity {

public:
	bool bShow;
	bool bbShow; //뒤로쏘는거
	bool super_bShow;
	void init(float x, float y);
	void B_init(float x, float y);
	void move();
	void Bmove();
	bool show();
	bool Back_Show();
	void active();
	void Back_Active();
	void hide();
	void Back_Hide();
	bool check_collision(float x, float y);
	int B_ypos;
	int B_xpos;
};


bool Bullet::check_collision(float x, float y)
{

	//충돌 처리 시 
	if (sphere_collision_check(x_pos, y_pos, 32, x, y, 32) == true)
	{
		bShow = false;
		score++;
		return true;
	}
	else {
		return false;
	}
}

void Bullet::init(float x, float y)
{
	x_pos = x;
	y_pos = y;
}

void Bullet::B_init(float x, float y)
{
	B_xpos = x;
	B_ypos = y;
}

bool Bullet::Back_Show()
{
	return bbShow;
}

void Bullet::Back_Active()
{
	bbShow = true;
}
void Bullet::Back_Hide()
{
	bbShow = false;
}

void Bullet::Bmove()
{
	B_ypos += speed;
}
bool Bullet::show()
{
	return bShow;
}

void Bullet::active()
{
	bShow = true;
}

void Bullet::move()
{
	y_pos -= speed;
}

void Bullet::hide()
{
	bShow = false;
}



//객체 생성 
Hero hero;
Enemy enemy[ENEMY_NUM];
Enemy enemy2[ENEMY_NUM];
Enemy Boss_enemy;
Enemy Boss_slave[20];    // load to sprite
Enemy Boss_slave1[20];    // load to sprite

Bullet bullet[10];
Bullet Enemy_bullet[10]; //enemy1 Bullet
Bullet Enemy2_bullet[10]; //enemy2 Bullet

Bullet Boss_bullet[20];
Bullet Boss_bullet1[20];
Bullet Boss_bullet2[20];


// the entry point for any Windows program
int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	HWND hWnd;
	WNDCLASSEX wc;

	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = (WNDPROC)WindowProc;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.lpszClassName = L"WindowClass";

	RegisterClassEx(&wc);

	hWnd = CreateWindowEx(NULL, L"WindowClass", L"Our Direct3D Program",
		WS_EX_TOPMOST | WS_POPUP, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT,
		NULL, NULL, hInstance, NULL);

	ShowWindow(hWnd, nCmdShow);

	// set up and initialize Direct3D
	initD3D(hWnd);


	//게임 오브젝트 초기화 
	init_game();

	// enter the main loop:

	MSG msg;

	while (TRUE)
	{
		DWORD starting_point = GetTickCount();

		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		do_game_logic();

		render_frame();

		// check the 'escape' key
		if (KEY_DOWN(VK_ESCAPE))
			PostMessage(hWnd, WM_DESTROY, 0, 0);




		while ((GetTickCount() - starting_point) < 25);
	}

	// clean up DirectX and COM
	cleanD3D();

	return msg.wParam;
}


// this is the main message handler for the program
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	} break;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}


// this function initializes and prepares Direct3D for use
void initD3D(HWND hWnd)
{
	d3d = Direct3DCreate9(D3D_SDK_VERSION);

	D3DPRESENT_PARAMETERS d3dpp;

	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = true;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = hWnd;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.BackBufferWidth = SCREEN_WIDTH;
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;


	// create a device class using this information and the info from the d3dpp stuct
	d3d->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&d3ddev);

	D3DXCreateSprite(d3ddev, &d3dspt);    // create the Direct3D Sprite object


	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"Boss_Bullet3.png",    // the file name
		D3DX_DEFAULT,    // default width
		D3DX_DEFAULT,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&sprite_Boss_bullet3);    // load to sprite

	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"Boss_Bullet.png",    // the file name
		D3DX_DEFAULT,    // default width
		D3DX_DEFAULT,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&sprite_Boss_bullet);    // load to sprite

	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"Boss_Bullet2.png",    // the file name
		D3DX_DEFAULT,    // default width
		D3DX_DEFAULT,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&sprite_Boss_bullet2);    // load to sprite

	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"Boss_slave2.png",    // the file name
		D3DX_DEFAULT,    // default width
		D3DX_DEFAULT,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&sprite_slave1);    // load to sprite

	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"Boss_slave.png",    // the file name
		D3DX_DEFAULT,    // default width
		D3DX_DEFAULT,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&sprite_slave);    // load to sprite

	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"Boss_slave2.png",    // the file name
		D3DX_DEFAULT,    // default width
		D3DX_DEFAULT,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&sprite_slave1);    // load to sprite

	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"Clear.png",    // the file name
		D3DX_DEFAULT,    // default width
		D3DX_DEFAULT,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&sprite_Clear);    // load to sprite

	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"Boss.png",    // the file name
		D3DX_DEFAULT,    // default width
		D3DX_DEFAULT,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&sprite_Boss);    // load to sprite

	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"background2.png",    // the file name
		D3DX_DEFAULT,    // default width
		D3DX_DEFAULT,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&sprite_background2);    // load to sprite

	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"Enemy_Bullet2.png",    // the file name
		D3DX_DEFAULT,    // default width
		D3DX_DEFAULT,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&sprite_Enemy2Bullet);    // load to sprite

	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"Enemy_Bullet.png",    // the file name
		D3DX_DEFAULT,    // default width
		D3DX_DEFAULT,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&sprite_EnemyBullet);    // load to sprite

	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"enemy1.png",    // the file name
		D3DX_DEFAULT,    // default width
		D3DX_DEFAULT,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&sprite_enemy2);    // load to sprite

	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"bomb.png",    // the file name
		D3DX_DEFAULT,    // default width
		D3DX_DEFAULT,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&sprite_Bbullet);    // load to sprite

	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"skill1.png",    // the file name
		D3DX_DEFAULT,    // default width
		D3DX_DEFAULT,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&sprite_skill);    // load to sprite

	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"skill2.png",    // the file name
		D3DX_DEFAULT,    // default width
		D3DX_DEFAULT,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&sprite_skill1);    // load to sprite

	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"skill3.png",    // the file name
		D3DX_DEFAULT,    // default width
		D3DX_DEFAULT,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&sprite_skill2);    // load to sprite

	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"skill4.png",    // the file name
		D3DX_DEFAULT,    // default width
		D3DX_DEFAULT,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&sprite_skill3);    // load to sprite

	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"GameOver.png",    // the file name
		D3DX_DEFAULT,    // default width
		D3DX_DEFAULT,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&sprite_GameOver);    // load to sprite

	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"background1.png",    // the file name
		D3DX_DEFAULT,    // default width
		D3DX_DEFAULT,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&sprite_background);    // load to sprite


	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"hero1.png",    // the file name
		D3DX_DEFAULT,    // default width
		D3DX_DEFAULT,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&sprite_hero);    // load to sprite

	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"enemy2.png",    // the file name
		D3DX_DEFAULT,    // default width
		D3DX_DEFAULT,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&sprite_enemy);    // load to sprite


	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"bullet2.png",    // the file name
		D3DX_DEFAULT,    // default width
		D3DX_DEFAULT,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&sprite_bullet);    // load to sprite


	return;
}


void init_game(void)
{
	PlaySound(TEXT("Strikers 1945 - BGM 04 Track 04.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP | SND_NODEFAULT);
	hero.HP = 4;
	Boss_enemy.HP = 110;
	
	//객체 초기화 
	SIZE s;
	ZeroMemory(&s, sizeof(SIZE));
	s.cx = (LONG)::GetSystemMetrics(SM_CXFULLSCREEN);
	s.cy = (LONG)::GetSystemMetrics(SM_CYFULLSCREEN);

	hero.init(s.cx/4, s.cy/4);
	
	
	//적들 초기화 
	for (int i = 0; i<ENEMY_NUM; i++)
	{

			/*enemy[i].init((float)((rand() % 400) + 300), rand() % 300 - 300);
			Enemy_bullet[i].B_init(enemy[i].x_pos, enemy[i].y_pos);
			Enemy_bullet[i].bShow = true;

			enemy2[i].init((float)((rand() % 400) + 300), rand() % 300 + 400);
			Enemy2_bullet[i].init(enemy2[i].x_pos, enemy2[i].y_pos);
			Enemy2_bullet[i].bShow = true;*/
		enemy[i].speed = 3;
		enemy2[i].speed = 3;
		Enemy_bullet[i].speed = 15;
		Enemy2_bullet[i].speed = 20;
		bullet[i].speed = 18;
		bullet[i].init(hero.x_pos, hero.y_pos);
	}
	for (int i = 0; i < 20; i++)
	{
		Boss_slave[i].speed = 5;
		Boss_slave1[i].speed = 10;
		Boss_bullet[i].speed = 15;
		Boss_bullet1[i].speed = 20;
		Boss_bullet2[i].speed = 25;
		Boss_bullet[i].bShow = false;
		Boss_bullet1[i].bShow = false;
	}
	//총알 초기화 

}


void do_game_logic(void)
{
	static bool Create = false;

	if (!Create)
	{
		Create = true;	
		Create_Wave(wave,Create);
	}
	else {
		Wave_Up(Create);
		Enemy_Move(Create);
	}


	Bullet_Time++;
	//주인공 처리
	if (start)
	{
		if (KEY_DOWN(VK_UP))
			hero.move(MOVE_UP);

		if (KEY_DOWN(VK_DOWN))
			hero.move(MOVE_DOWN);

		if (KEY_DOWN(VK_LEFT))
			hero.move(MOVE_LEFT);

		if (KEY_DOWN(VK_RIGHT))
			hero.move(MOVE_RIGHT);


		//총알 처리 
		
		if (KEY_DOWN(0x5A))
		{
			for(int i=0;i<10;i++)
			{
  				if (bullet[i].show() == false)
				{
					if (Bullet_Time >= 3)
					{
						Bullet_Time = 0;
						bullet[i].active();
						bullet[i].init(hero.x_pos, hero.y_pos-50);
					}
					break;
				}
			}
		}
		if (KEY_DOWN(0x58))
		{
			for (int i = 0; i < 10; i++)
			{
				if (bullet[i].Back_Show() == false)
				{
					if (Bullet_Time >= 3)
					{
						Bullet_Time = 0;
						bullet[i].Back_Active();
						bullet[i].B_init(hero.x_pos, hero.y_pos+50);
					}
					break;
				}
			}
		}

		//적들 처리 ,충돌 처리
		Coll();
		B_Coll();

	}
	else
	{
		if (KEY_DOWN(VK_SPACE))
			start = true;
	}
}

// this is the function used to render a single frame
void render_frame(void)
{
	// clear the window to a deep blue
	static int Main_Frame = 0;
	d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

	d3ddev->BeginScene();    // begins the 3D scene

	d3dspt->Begin(D3DXSPRITE_ALPHABLEND);    // // begin sprite drawing with transparency

	if (!start)
	{
		static int frame=0;
		Main_Frame++;
		if (Main_Frame % 16 == 0)
			frame++;

		switch (frame % 2)
		{
		case 0:
			D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
				L"MainScreen.png",    // the file name
				D3DX_DEFAULT,    // default width
				D3DX_DEFAULT,    // default height
				D3DX_DEFAULT,    // no mip mapping
				NULL,    // regular usage
				D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
				D3DPOOL_MANAGED,    // typical memory handling
				D3DX_DEFAULT,    // no filtering
				D3DX_DEFAULT,    // no mip filtering
				D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
				NULL,    // no image info struct
				NULL,    // not using 256 colors
				&sprite_Main);    // load to sprite
			break;
		default:
			D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
				L"MainScreen1.png",    // the file name
				D3DX_DEFAULT,    // default width
				D3DX_DEFAULT,    // default height
				D3DX_DEFAULT,    // no mip mapping
				NULL,    // regular usage
				D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
				D3DPOOL_MANAGED,    // typical memory handling
				D3DX_DEFAULT,    // no filtering
				D3DX_DEFAULT,    // no mip filtering
				D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
				NULL,    // no image info struct
				NULL,    // not using 256 colors
				&sprite_Main);    // load to sprite
			break;
		}
		RECT part;
		SIZE s;
		ZeroMemory(&s, sizeof(SIZE));
		s.cx = (LONG)::GetSystemMetrics(SM_CXFULLSCREEN);
		s.cy = (LONG)::GetSystemMetrics(SM_CYFULLSCREEN);
		SetRect(&part, 0, 0, s.cx, s.cy);
		D3DXVECTOR3 center(0.0f, 0.0f, 0.0f);
		D3DXVECTOR3 position(0, 0, 0.0f);
		d3dspt->Draw(sprite_Main, &part, &center, &position, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
	else if (start && isLive)
	{
		static bool Move_Mode = false;
		static int Back_Move = 0;
		//배경
		RECT part3;
		SIZE s;
		ZeroMemory(&s, sizeof(SIZE));
		s.cx = (LONG)::GetSystemMetrics(SM_CXFULLSCREEN);
		s.cy = (LONG)::GetSystemMetrics(SM_CYFULLSCREEN);
		SIZE s1;
		ZeroMemory(&s1, sizeof(SIZE));
		s1.cx = (LONG)::GetSystemMetrics(SM_CXFULLSCREEN);
		s1.cy = (LONG)::GetSystemMetrics(SM_CYFULLSCREEN);
		if (Move_Mode)
		{
			D3DXVECTOR3 center3(0.0f, 0.0f, 0.0f);

			RECT part4;
			D3DXVECTOR3 position4(0, 0, 0.0f);
			SetRect(&part4, 0, Back_Move, s1.cx, s1.cy);
			d3dspt->Draw(sprite_background2, &part4, &center3, &position4, D3DCOLOR_ARGB(255, 255, 255, 255));

			SetRect(&part3, 0, 0, s.cx, s.cy);
			D3DXVECTOR3 position3(0, 480 - Back_Move, 0.0f);
			d3dspt->Draw(sprite_background, &part3, &center3, &position3, D3DCOLOR_ARGB(255, 255, 255, 255));
			Back_Move++;

			if (Back_Move >= 480)
			{
				Move_Mode = false;
				Back_Move = 0;
			}
		}
		else
		{
			SetRect(&part3, 0, Back_Move, s.cx, s.cy);
			D3DXVECTOR3 center3(0.0f, 0.0f, 0.0f);
			D3DXVECTOR3 position3(0, 0, 0.0f);
			d3dspt->Draw(sprite_background, &part3, &center3, &position3, D3DCOLOR_ARGB(255, 255, 255, 255));
			Back_Move++;

			RECT part4;
			SIZE s1;
			ZeroMemory(&s1, sizeof(SIZE));
			s1.cx = (LONG)::GetSystemMetrics(SM_CXFULLSCREEN);
			s1.cy = (LONG)::GetSystemMetrics(SM_CYFULLSCREEN);
			D3DXVECTOR3 position4(0, 480 - Back_Move, 0.0f);
			SetRect(&part4, 0, 0, s1.cx, s1.cy);
			d3dspt->Draw(sprite_background2, &part4, &center3, &position4, D3DCOLOR_ARGB(255, 255, 255, 255));
			if (Back_Move >= 480)
			{
				Move_Mode = true;
				Back_Move = 0;
			}
		}


		//주인공 
		RECT part;
		SetRect(&part, 0, 0, 64, 64);
		D3DXVECTOR3 center(0.0f, 0.0f, 0.0f);    // center at the upper-left corner
		D3DXVECTOR3 position(hero.x_pos, hero.y_pos, 0.0f);    // position at 50, 50 with no depth
		d3dspt->Draw(sprite_hero, &part, &center, &position, D3DCOLOR_ARGB(255, 255, 255, 255));

		////총알 


		int enemy_kind = (int)rand() % 10;

		RECT part2;
		SetRect(&part2, 0, 0, 64, 64);
		D3DXVECTOR3 center2(0.0f, 0.0f, 0.0f);    // center at the upper-left corner

		for (int i = 0; i < ENEMY_NUM; i++)
		{
			if (bullet[i].bShow == true)
			{
				RECT part1;
				SetRect(&part1, 0, 0, 64, 64);
				D3DXVECTOR3 center1(0.0f, 0.0f, 0.0f);    // center at the upper-left corner
				D3DXVECTOR3 position1(bullet[i].x_pos, bullet[i].y_pos, 0.0f);    // position at 50, 50 with no depth
				d3dspt->Draw(sprite_bullet, &part1, &center1, &position1, D3DCOLOR_ARGB(255, 255, 255, 255));
			}

			if (bullet[i].bbShow == true)
			{
				RECT part1;
				SetRect(&part1, 0, 0, 64, 64);
				D3DXVECTOR3 center1(0.0f, 0.0f, 0.0f);    // center at the upper-left corner
				D3DXVECTOR3 position1(bullet[i].B_xpos, bullet[i].B_ypos, 0.0f);    // position at 50, 50 with no depth
				d3dspt->Draw(sprite_Bbullet, &part1, &center1, &position1, D3DCOLOR_ARGB(255, 255, 255, 255));
			}
			////에네미
			if (enemy[i].Enemy_Show == true)
			{
				D3DXVECTOR3 position2(enemy[i].x_pos, enemy[i].y_pos, 0.0f);    // position at 50, 50 with no depth
				d3dspt->Draw(sprite_enemy, &part2, &center2, &position2, D3DCOLOR_ARGB(255, 255, 255, 255));
			}
			else
			{
				enemy[i].x_pos = -50; enemy[i].y_pos = -50;
				D3DXVECTOR3 position2(enemy[i].x_pos, enemy[i].y_pos, 0.0f);    // position at 50, 50 with no depth
				d3dspt->Draw(sprite_enemy, &part2, &center2, &position2, D3DCOLOR_ARGB(255, 255, 255, 255));
			}

			if (enemy2[i].Enemy_Show == true)
			{
				D3DXVECTOR3 position3(enemy2[i].x_pos, enemy2[i].y_pos, 0.0f);    // position at 50, 50 with no depth
				d3dspt->Draw(sprite_enemy2, &part2, &center2, &position3, D3DCOLOR_ARGB(255, 255, 255, 255));
			}
			else
			{
				enemy2[i].x_pos = 520; enemy2[i].y_pos = 520;
				D3DXVECTOR3 position3(enemy2[i].x_pos, enemy2[i].y_pos, 0.0f);    // position at 50, 50 with no depth
				d3dspt->Draw(sprite_enemy2, &part2, &center2, &position3, D3DCOLOR_ARGB(255, 255, 255, 255));
			}
			//

			if (Boss_enemy.Enemy_Show)
			{
				RECT part5;
				SetRect(&part5, 0, 0, 128, 128);
				D3DXVECTOR3 position3(Boss_enemy.x_pos, Boss_enemy.y_pos, 0.0f);    // position at 50, 50 with no depth
				d3dspt->Draw(sprite_Boss, &part5, &center2, &position3, D3DCOLOR_ARGB(255, 255, 255, 255));
			}
			else
			{
				RECT part5;
				SetRect(&part5, 0, 0, 128, 128);
				Boss_enemy.x_pos = -200; Boss_enemy.y_pos = -200;
				D3DXVECTOR3 position3(Boss_enemy.x_pos, Boss_enemy.y_pos, 0.0f);    // position at 50, 50 with no depth
				d3dspt->Draw(sprite_Boss, &part5, &center2, &position3, D3DCOLOR_ARGB(255, 255, 255, 255));
			}
		}
		for (int i = 0; i < ENEMY_NUM; i++)
		{
			if (Enemy_bullet[i].bShow == true)
			{
				RECT part1;
				SetRect(&part1, 0, 0, 64, 64);
				D3DXVECTOR3 center1(0.0f, 0.0f, 0.0f);    // center at the upper-left corner
				D3DXVECTOR3 position1(Enemy_bullet[i].B_xpos, Enemy_bullet[i].B_ypos, 0.0f);    // position at 50, 50 with no depth
				d3dspt->Draw(sprite_EnemyBullet, &part1, &center1, &position1, D3DCOLOR_ARGB(255, 255, 255, 255));
			}
			if (Enemy2_bullet[i].bShow)
			{
				RECT part2;
				SetRect(&part2, 0, 0, 64, 64);
				D3DXVECTOR3 center2(0.0f, 0.0f, 0.0f);    // center at the upper-left corner
				D3DXVECTOR3 position2(Enemy2_bullet[i].x_pos, Enemy2_bullet[i].y_pos, 0.0f);    // position at 50, 50 with no depth
				d3dspt->Draw(sprite_Enemy2Bullet, &part2, &center2, &position2, D3DCOLOR_ARGB(255, 255, 255, 255));
			}
		}
		for (int i = 0; i < ENEMY_NUM; i++)
		{
			if (abs(hero.x_pos - enemy[i].x_pos) <= 30 && abs(hero.y_pos - enemy[i].y_pos) <= 10 ||
				abs(hero.x_pos - enemy2[i].x_pos) <= 30 && abs(hero.y_pos - enemy2[i].y_pos) <= 10 )
				effect = true;
		}
		if (hero.HP > 0)
		{
			if (effect)
			{
				RECT part7;
				D3DXVECTOR3 center7(0.0f, 0.0f, 0.0f);
				D3DXVECTOR3 position7(hero.x_pos, hero.y_pos, 0.0f);
				static int show = 0;
				if (show % 17 > 12)
				{
					SetRect(&part7, 0, 0, 128, 128);
					d3dspt->Draw(sprite_skill3, &part7, &center7, &position7, D3DCOLOR_ARGB(255, 255, 255, 255));
				}
				else if (show % 15 > 8)
				{
					SetRect(&part7, 0, 0, 128, 128);
					d3dspt->Draw(sprite_skill2, &part7, &center7, &position7, D3DCOLOR_ARGB(255, 255, 255, 255));
				}

				else if (show % 15 > 4)
				{
					SetRect(&part7, 0, 0, 64, 64);
					d3dspt->Draw(sprite_skill1, &part7, &center7, &position7, D3DCOLOR_ARGB(255, 255, 255, 255));
				}
				else
				{
					SetRect(&part7, 0, 0, 64, 64);
					d3dspt->Draw(sprite_skill, &part7, &center7, &position7, D3DCOLOR_ARGB(255, 255, 255, 255));
				}
				show++;
				if (show >= 16)
				{
					show = 0;
					effect = false;
					if (Boss_Pattern == 5)
						hero.HP -= 2;
					else
						hero.HP--;
				}
			}
		}
		else
			isLive = false;

		if (wave == 7)
		{
			for (int i = 0; i < 20; i++)
			{
				if (Boss_slave[i].Enemy_Show)
				{
					RECT part7;
					D3DXVECTOR3 center7(0.0f, 0.0f, 0.0f);
					SetRect(&part7, 0, 0, 64, 64);
					for (int i = 0; i < 20; i++)
					{
						D3DXVECTOR3 position7(Boss_slave[i].x_pos, Boss_slave[i].y_pos, 0.0f);
						d3dspt->Draw(sprite_slave, &part7, &center7, &position7, D3DCOLOR_ARGB(255, 255, 255, 255));
					}
				}
				else
				{
					RECT part7;
					D3DXVECTOR3 center7(0.0f, 0.0f, 0.0f);
					SetRect(&part7, 0, 0, 64, 64);
						D3DXVECTOR3 position7(Boss_slave[i].x_pos=-80, Boss_slave[i].y_pos=600, 0.0f);
						d3dspt->Draw(sprite_slave, &part7, &center7, &position7, D3DCOLOR_ARGB(255, 255, 255, 255));
				}

				if (Boss_slave1[i].Enemy_Show)
				{
					RECT part7;
					D3DXVECTOR3 center7(0.0f, 0.0f, 0.0f);
					SetRect(&part7, 0, 0, 64, 64);
					for (int i = 0; i < 20; i++)
					{
						D3DXVECTOR3 position7(Boss_slave1[i].x_pos, Boss_slave1[i].y_pos, 0.0f);
						d3dspt->Draw(sprite_slave1, &part7, &center7, &position7, D3DCOLOR_ARGB(255, 255, 255, 255));
					}
				}
				else
				{
					RECT part7;
					D3DXVECTOR3 center7(0.0f, 0.0f, 0.0f);
					SetRect(&part7, 0, 0, 64, 64);
					D3DXVECTOR3 position7(Boss_slave1[i].x_pos = -80, Boss_slave1[i].y_pos = -80, 0.0f);
					d3dspt->Draw(sprite_slave1, &part7, &center7, &position7, D3DCOLOR_ARGB(255, 255, 255, 255));
				}

				if (Boss_bullet[i].bShow == true)
				{
					RECT part7;
					D3DXVECTOR3 center7(0.0f, 0.0f, 0.0f);
					SetRect(&part7, 0, 0, 64, 64);
					for (int i = 0; i < 20; i++)
					{
						D3DXVECTOR3 position7(Boss_bullet[i].B_xpos, Boss_bullet[i].B_ypos, 0.0f);
						d3dspt->Draw(sprite_Boss_bullet, &part7, &center7, &position7, D3DCOLOR_ARGB(255, 255, 255, 255));
					}
				}
				else
				{
					RECT part7;
					D3DXVECTOR3 center7(0.0f, 0.0f, 0.0f);
					SetRect(&part7, 0, 0, 64, 64);
					D3DXVECTOR3 position7(Boss_bullet[i].B_xpos = -80, Boss_bullet[i].B_ypos = -80, 0.0f);
					d3dspt->Draw(sprite_Boss_bullet, &part7, &center7, &position7, D3DCOLOR_ARGB(255, 255, 255, 255));
				}

				if (Boss_bullet1[i].bShow == true)
				{
					RECT part7;
					D3DXVECTOR3 center7(0.0f, 0.0f, 0.0f);
					SetRect(&part7, 0, 0, 64, 64);
					for (int i = 0; i < 20; i++)
					{
						D3DXVECTOR3 position7(Boss_bullet1[i].B_xpos, Boss_bullet1[i].B_ypos, 0.0f);
						d3dspt->Draw(sprite_Boss_bullet2, &part7, &center7, &position7, D3DCOLOR_ARGB(255, 255, 255, 255));
					}
				}
				else
				{
					RECT part7;
					D3DXVECTOR3 center7(0.0f, 0.0f, 0.0f);
					SetRect(&part7, 0, 0, 64, 64);
					D3DXVECTOR3 position7(Boss_bullet1[i].B_xpos = -80, Boss_bullet1[i].B_ypos = -80, 0.0f);
					d3dspt->Draw(sprite_Boss_bullet2, &part7, &center7, &position7, D3DCOLOR_ARGB(255, 255, 255, 255));
				}

				if (Boss_bullet2[i].bShow == true)
				{
					RECT part7;
					D3DXVECTOR3 center7(0.0f, 0.0f, 0.0f);
					SetRect(&part7, 0, 0, 64, 64);
					for (int i = 0; i < 20; i++)
					{
						D3DXVECTOR3 position7(Boss_bullet2[i].B_xpos, Boss_bullet2[i].B_ypos, 0.0f);
						d3dspt->Draw(sprite_Boss_bullet3, &part7, &center7, &position7, D3DCOLOR_ARGB(255, 255, 255, 255));
					}
				}
				else
				{
					RECT part7;
					D3DXVECTOR3 center7(0.0f, 0.0f, 0.0f);
					SetRect(&part7, 0, 0, 64, 64);
					D3DXVECTOR3 position7(Boss_bullet2[i].B_xpos = -80, Boss_bullet2[i].B_ypos = -80, 0.0f);
					d3dspt->Draw(sprite_Boss_bullet3, &part7, &center7, &position7, D3DCOLOR_ARGB(255, 255, 255, 255));
				}
			}
		}
		Score_Manager();
	}

	if (!isLive)
	{
		RECT part;
		SIZE s;
		ZeroMemory(&s, sizeof(SIZE));
		s.cx = (LONG)::GetSystemMetrics(SM_CXFULLSCREEN);
		s.cy = (LONG)::GetSystemMetrics(SM_CYFULLSCREEN);
		SetRect(&part, 0, 0, s.cx, s.cy);
		D3DXVECTOR3 center(0.0f, 0.0f, 0.0f);
		D3DXVECTOR3 position(0, 0, 0.0f);
		d3dspt->Draw(sprite_GameOver, &part, &center, &position, D3DCOLOR_ARGB(255, 255, 255, 255));
		if (score > 100)
			score -= 100;
		else
			score = 0;
		Score_Manager();
	}

	if (isClear)
	{
		RECT part;
		SIZE s;
		ZeroMemory(&s, sizeof(SIZE));
		s.cx = (LONG)::GetSystemMetrics(SM_CXFULLSCREEN);
		s.cy = (LONG)::GetSystemMetrics(SM_CYFULLSCREEN);
		SetRect(&part, 0, 0, s.cx, s.cy);
		D3DXVECTOR3 center(0.0f, 0.0f, 0.0f);
		D3DXVECTOR3 position(0, 0, 0.0f);
		d3dspt->Draw(sprite_Clear, &part, &center, &position, D3DCOLOR_ARGB(255, 255, 255, 255));
		Score_Manager();
	}

	d3dspt->End();    // end sprite drawing

	d3ddev->EndScene();    // ends the 3D scene

	d3ddev->Present(NULL, NULL, NULL, NULL);

	return;
}

// this is the function that cleans up Direct3D and COM
void cleanD3D(void)
{
	sprite_background->Release();
	d3ddev->Release();
	d3d->Release();

	//객체 해제 
	sprite_hero->Release();
	sprite_enemy->Release();
	sprite_bullet->Release();
	sprite_GameOver->Release();
	sprite_Main->Release();
	sprite_SOne->Release();
	sprite_SHund->Release();
	sprite_STen->Release();
	sprite_SThou->Release();
	sprite_Bbullet->Release();
	sprite_enemy2->Release();
	sprite_EnemyBullet->Release();
	sprite_skill->Release();
	sprite_skill1->Release();
	sprite_skill2->Release();
	sprite_skill3->Release();
	sprite_Clear->Release();
	sprite_Boss_bullet->Release();
	sprite_Boss_bullet2->Release();
	sprite_Boss_bullet3->Release();
	return;
}

void Score_Manager()
{
	RECT part;
	D3DXVECTOR3 center(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 position(0, 0, 0.0f);
	SetRect(&part, 0, 0, 32, 64);
	int score_temp = score;
	int temp;
	temp = score_temp / 1000;
	Image_Change(temp, sprite_SThou);

	score_temp = score_temp % 1000;
	temp = score_temp / 100;
	Image_Change(temp, sprite_SHund);

	score_temp = score_temp % 100;
	temp = score_temp / 10;

	Image_Change(temp, sprite_STen);
	temp = score_temp % 10;

	Image_Change(temp, sprite_SOne);

	d3dspt->Draw(sprite_SThou, &part, &center, &position, D3DCOLOR_ARGB(255, 255, 255, 255));
	D3DXVECTOR3 position1(32, 0, 0.0f);

	d3dspt->Draw(sprite_SHund, &part, &center, &position1, D3DCOLOR_ARGB(255, 255, 255, 255));

	D3DXVECTOR3 position2(64, 0, 0.0f);

	d3dspt->Draw(sprite_STen, &part, &center, &position2, D3DCOLOR_ARGB(255, 255, 255, 255));

	D3DXVECTOR3 position3(96, 0, 0.0f);

	d3dspt->Draw(sprite_SOne, &part, &center, &position3, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void Coll()
{
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		if (bullet[i].show() == true)
		{
			for (int j = 0; j < ENEMY_NUM; j++)
			{
				if (bullet[i].check_collision(enemy[j].x_pos, enemy[j].y_pos) == true && (wave != 4 && wave != 6))
				{
					//enemy[j].init((float)(rand() % 300+200), rand() % 100-100);
					enemy[j].Enemy_Show = false;
					Enemy_bullet[j].bShow = false;
					break;
				}
				else if (bullet[i].check_collision(enemy[j].x_pos, enemy[j].y_pos) == true && (wave == 4 || wave == 6))
				{
					break;
				}

				if (bullet[i].check_collision(enemy2[j].x_pos, enemy2[j].y_pos) == true && wave != 6)
				{
					//enemy2[j].init((float)(rand() % 200), rand() % 100 + 500);
					enemy2[j].Enemy_Show = false;
					Enemy2_bullet[j].bShow = false;
					break;
				}
				else if (bullet[i].check_collision(enemy[j].x_pos, enemy[j].y_pos) == true && wave == 6)
				{
					break;
				}

				if (bullet[i].check_collision(Boss_enemy.x_pos, Boss_enemy.y_pos) == true)
				{
					Boss_enemy.HP--;
					if (Boss_enemy.HP <= 0)
					{
						Boss_enemy.Enemy_Show = false;
						score += 1000;
						isClear = true;
					}
					break;
				}
			}
		}
		if (bullet[i].show() == true)
		{
			if (bullet[i].y_pos < -10)
			{
				bullet[i].hide();
			}
			else
				bullet[i].move();
		}
	}

	if (wave == 7)
	{
		for (int i = 0; i < ENEMY_NUM; i++)
		{
			if (bullet[i].bShow == true)
			{
				for (int j = 0; j < 20; j++)
				{
					if (j < 2)
					{
						if (bullet[i].check_collision(Boss_slave[j].x_pos, Boss_slave[j].y_pos))
						{
							Boss_slave[j].Enemy_Show = false;
							break;
						}
					}
					else
					{
						if (bullet[i].check_collision(Boss_slave[j].x_pos, Boss_slave[j].y_pos))
							break;
					}
				}
			}
		}
		if (abs(hero.x_pos - Boss_enemy.x_pos) <= 65 && abs(hero.y_pos - Boss_enemy.y_pos) <= 70)
			effect = true;
	}
}

void B_Coll()
{
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		if (bullet[i].Back_Show() == true)
		{
			for (int j = 0; j < ENEMY_NUM; j++)
			{

				if (abs(bullet[i].B_xpos - enemy[j].x_pos) <= 30 && abs(bullet[i].B_ypos - enemy[j].y_pos) <= 10  && wave!=6)
				{
					//enemy[j].init((float)(rand() % 300+200), rand() % 100 - 100);
					enemy[j].Enemy_Show = false;
					Enemy_bullet[j].bShow = false;
					bullet[i].bbShow = false;
					score++;;
					break;
				}
				else if (abs(bullet[i].B_xpos - enemy[j].x_pos) <= 30 && abs(bullet[i].B_ypos - enemy[j].y_pos) <= 10 && wave == 6)
				{
					score++;
					bullet[i].bbShow = false;
					break;
				}


				if (abs(bullet[i].B_xpos - enemy2[j].x_pos) <= 30 && abs(bullet[i].B_ypos - enemy2[j].y_pos) <= 10 & (wave != 5 && wave!=6))
				{
					//enemy2[j].init((float)(rand() % 200), rand() % 100 + 500);
					enemy2[j].Enemy_Show = false;
					Enemy2_bullet[j].bShow = false;
					bullet[i].bbShow = false;
					score++;
					break;
				}
				else if (abs(bullet[i].B_xpos - enemy2[j].x_pos) <= 30 && abs(bullet[i].B_ypos - enemy2[j].y_pos) <= 10 && (wave == 5 || wave==6))
				{
					score ++;
					bullet[i].bbShow = false;
					break;
				}
			}
		}
		if (bullet[i].Back_Show() == true)
		{
			if (bullet[i].B_ypos > 500)
			{
				bullet[i].Back_Hide();
			}
			else
				bullet[i].Bmove();
		}
	}

	if (wave == 7)
	{
		for (int i = 0; i < ENEMY_NUM; i++)
		{
			if (bullet[i].bbShow == true)
			{
				for (int j = 0; j < 20; j++)
				{
					if (abs(bullet[i].B_xpos - Boss_slave[j].x_pos) <= 30 && abs(bullet[i].B_ypos - Boss_slave[j].y_pos) <= 10)
					{
						score++;
						bullet[i].bbShow = false;
						Boss_slave[j].Enemy_Show = false;
						break;
					}

					if (j < 2)
					{
						if (abs(bullet[i].B_xpos - Boss_slave1[j+10].x_pos) <= 30 && abs(bullet[i].B_ypos - Boss_slave1[j+10].y_pos) <= 10)
						{
							score++;
							bullet[i].bbShow = false;
							Boss_slave1[j+10].Enemy_Show = false;
							break;
						}
					}
					else if (abs(bullet[i].B_xpos - Boss_slave1[j].x_pos) <= 30 && abs(bullet[i].B_ypos - Boss_slave1[j].y_pos) <= 10)
					{
						score++;
						bullet[i].bbShow = false;
						break;
					}
				}
				if (abs(bullet[i].B_xpos - Boss_enemy.x_pos) <= 65 && abs(bullet[i].B_ypos - Boss_enemy.y_pos) <= 50)
				{
					Boss_enemy.HP--;
					score++;						
					bullet[i].bbShow = false;
					if (Boss_enemy.HP <= 0)
						isClear = true;
					break;
				}

			}
		}
	}
}

void Enemy_Move(bool &Create)
{
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		if (enemy[i].y_pos > 500)
		{
			//enemy[i].init((float)(rand() % 300), rand() % 100 - 100);
			enemy[i].Enemy_Show = false;
			Enemy_bullet[i].bShow = false;
		}
		else
			enemy[i].move();

		if (enemy2[i].y_pos < 0)
		{
			//enemy2[i].init((float)(rand() % 200), rand() % 100 + 500);
			enemy2[i].Enemy_Show = false;
			Enemy2_bullet[i].bShow = false;
		}
		else
			enemy2[i].Forward_move();
		if(Enemy_bullet[i].B_ypos<500)
			Enemy_bullet[i].Bmove();
		else
		{
			if (enemy[i].Enemy_Show)
			{
				Enemy_bullet[i].bShow = false;
				Enemy_bullet[i].B_init(enemy[i].x_pos, enemy[i].y_pos);
				Enemy_bullet[i].bShow = true;
			}
		}

		if (Enemy2_bullet[i].y_pos >0)
			Enemy2_bullet[i].move();
		else
		{
			if (enemy2[i].Enemy_Show)
			{
				Enemy2_bullet[i].bShow = false;
				Enemy2_bullet[i].init(enemy2[i].x_pos, enemy2[i].y_pos);
				Enemy2_bullet[i].bShow = true;
			}
		}

		if (Enemy_bullet[i].bShow == true )
		{

			if (abs(Enemy_bullet[i].B_xpos - hero.x_pos) <= 30 && abs(Enemy_bullet[i].B_ypos - hero.y_pos) <= 10 && wave != 4)
			{
				Enemy_bullet[i].bShow = false;
				if (score > 2)
					score -= 3;
				else
					score = 0;
			}
			else if (abs(Enemy_bullet[i].B_xpos - hero.x_pos) <= 30 && abs(Enemy_bullet[i].B_ypos - hero.y_pos) <= 10 && wave == 4)
				if (score > 9)
					score -= 10;
				else
					score = 0;
		}

		if (Enemy2_bullet[i].bShow == true)
		{

			if (abs(Enemy2_bullet[i].x_pos - hero.x_pos) <= 30 && abs(Enemy2_bullet[i].y_pos - hero.y_pos) <= 10 && wave !=5)
			{
				Enemy2_bullet[i].bShow = false;
				if (score > 2)
					score -= 3;
				else 
					score = 0;					
			}
			else if (abs(Enemy2_bullet[i].x_pos - hero.x_pos) <= 30 && abs(Enemy2_bullet[i].y_pos - hero.y_pos) <= 10 && wave == 5)
			{
				Enemy2_bullet[i].bShow = false;
				if (score > 9)
					score -= 10;
				else
					score = 0;
			}
		}
	}
	if (wave == 7)
	{
		int count = 0;
		for (int i = 0; i < 20; i++)
		{

			if (Boss_slave[i].y_pos > 500)
				Boss_slave[i].Enemy_Show = false;
			else
				Boss_slave[i].move();

			if (Boss_slave[i].Enemy_Show == false)
			{
				count++;
			}

			if (Boss_slave1[i].y_pos < 0)
				Boss_slave1[i].Enemy_Show = false;
			else
				Boss_slave1[i].Forward_move();
			
			if(Boss_slave1[i].Enemy_Show == false)
			{
				count++;
			}

			if (abs(Boss_slave[i].x_pos - hero.x_pos) <= 30 && abs(Boss_slave[i].y_pos - hero.y_pos)<=10 ||
				abs(Boss_slave1[i].x_pos - hero.x_pos) <= 30 && abs(Boss_slave1[i].y_pos - hero.y_pos) <= 10)
			{
				effect = true;
			}

			if (Boss_bullet[i].bShow == true)
			{
				if (Boss_bullet[i].B_ypos < 500)
					Boss_bullet[i].Bmove();
				else
					Boss_bullet[i].bShow = false;

				if (abs(Boss_bullet[i].B_xpos - hero.x_pos) <= 30 && abs(Boss_bullet[i].B_ypos - hero.y_pos) <= 10)
				{
					Boss_bullet[i].bShow = false;
					effect = true;

				}
			}
			if (Boss_bullet1[i].bShow == true)
			{
				if (Boss_bullet1[i].B_ypos < 500)
					Boss_bullet1[i].Bmove();
				else
					Boss_bullet1[i].bShow = false;

				if (abs(Boss_bullet1[i].B_xpos - hero.x_pos) <= 30 && abs(Boss_bullet1[i].B_ypos - hero.y_pos) <= 10)
				{
					Boss_bullet1[i].bShow = false;
					effect = true;
				}
			}

			if (Boss_bullet2[i].bShow == true)
			{
				if (Boss_bullet2[i].B_ypos < 500)
					Boss_bullet2[i].Bmove();
				else
					Boss_bullet2[i].bShow = false;

				if (abs(Boss_bullet2[i].B_xpos - hero.x_pos) <= 30 && abs(Boss_bullet2[i].B_ypos - hero.y_pos) <= 10)
				{
					Boss_bullet2[i].bShow = false;
					effect = true;
				}
			}

			if (Boss_bullet[i].bShow == false)
				count++;

			if (Boss_bullet1[i].bShow == false)
				count++;

			if (Boss_bullet2[i].bShow == false)
				count++;

			if (count >= 100 && 
				(Boss_Pattern == 0 || Boss_Pattern == 1 || Boss_Pattern == 3 || Boss_Pattern == 4 || Boss_Pattern==5) && Create==true)
			{
				Boss_Pattern++;
				Create = false;
			}
		}
	}

}

void Wave_Up(bool &Create)
{
	int count = 0;
	static int Time=0;


	for (int i = 0; i < ENEMY_NUM; i++)
	{
		if (wave == 1 && enemy[i].Enemy_Show == false)
		{
			count++;
			if (count == 10)
			{
				Time++;
				if (Time == 90)
				{
					wave++;
					count = 0;
					Create = false;
					Time = 0;
				}
			}
		}
		else if (wave == 2 && enemy2[i].Enemy_Show == false)
		{
			count++;
			if (count == 10)
			{
				Time++;
				if (Time == 90)
				{
					wave++;
					count = 0;
					Create = false;
					Time = 0;
				}
			}
		}

		else if (wave == 3 && enemy[i].Enemy_Show == false)
		{
			count++;
			if (enemy2[i].Enemy_Show == false)
				count++;
			if (count == 20)
			{
				Time++;
				if (Time == 90)
				{
					wave++;
					count = 0;
					Create = false;
					Time = 0;
				}
			}
		}
		else if (wave == 4 && enemy[i].Enemy_Show == false)
		{
			count++;
			if (count == 10)
			{
				Time++;
				if (Time == 60)
				{
					wave++;
					count = 0;
					Create = false;
					Time = 0;

				}
			}
		}
		else if (wave == 5 && enemy2[i].Enemy_Show == false)
		{
			count++;
			if (count == 10)
			{
				Time++;
				if (Time == 30)
				{
					wave++;
					count = 0;
					Create = false;
					Time = 0;
				}
			}
		}
		else if (wave == 6 && enemy[i].Enemy_Show == false)
		{
			count++;
			if (enemy2[i].Enemy_Show == false)
				count++;
			if (count == 20)
			{
				Time++;
				if (Time == 90)
				{
					wave++;
					count = 0;
					Create = false;
					Time = 0;
				}
			}
		}
		else
			break;
	}
}

void Create_Wave(int wave,bool &Create)
{
	static int Time = 0;  static int Count = 0;
	if (wave == 1)
	{
		for (int i = 0; i < ENEMY_NUM; i++)
		{
			enemy[i].init((float)((rand() % 400) + 300), rand() % 300 - 300);
			enemy[i].Enemy_Show = true;
			Enemy_bullet[i].B_init(enemy[i].x_pos, enemy[i].y_pos);
			Enemy_bullet[i].bShow = true;
		}
	}

	if (wave == 2)
	{
		for (int i = 0; i < ENEMY_NUM; i++)
		{
			enemy2[i].init((float)((rand() % 400) + 300), rand() % 300 + 400);
			enemy2[i].Enemy_Show = true;
		}
	}

	if (wave == 3)
	{
		for (int i = 0; i < ENEMY_NUM; i++)
		{
			enemy[i].init((float)((rand() % 400) + 300), rand() % 300 - 300);
			enemy[i].Enemy_Show = true;
			enemy2[i].init((float)((rand() % 400) + 300), rand() % 300 + 400);
			enemy2[i].Enemy_Show = true;
			Enemy_bullet[i].B_init(enemy[i].x_pos, enemy[i].y_pos);
			Enemy_bullet[i].bShow = true;
		}
	}
	if (wave == 4)
	{
		static int x_pos = 0;
		for (int i = 0; i < ENEMY_NUM; i++)
		{
			enemy[i].init(x_pos, 0);
			enemy[i].Enemy_Show = true;
			Enemy_bullet[i].B_init(enemy[i].x_pos, enemy[i].y_pos);
			Enemy_bullet[i].bShow = true;
			x_pos += 100;
		}
	}

	if (wave == 5)
	{
		static int x_pos = 0;
		for (int i = 0; i < ENEMY_NUM; i++)
		{
			enemy2[i].init(x_pos, 500);
			enemy2[i].Enemy_Show = true;
			x_pos += 100;
		}
	}

	if (wave == 6)
	{
		static int x_pos = 0;
		static int x1_pos = 35;
		for (int i = 0; i < ENEMY_NUM; i++)
		{
			enemy[i].speed = 8;
			enemy2[i].speed = 8;
			enemy[i].init(x_pos, 0);
			enemy[i].Enemy_Show = true;
			enemy2[i].init(x1_pos, 500);
			enemy2[i].Enemy_Show = true;
			Enemy_bullet[i].B_init(enemy[i].x_pos, enemy[i].y_pos);
			Enemy_bullet[i].bShow = true;
			x_pos += 100;
			x1_pos += 100;
		}
	}

	if (wave == 7)
	{
		if(Boss_Pattern!=2)
			Boss_enemy.init(450, 30);

		Boss_enemy.Enemy_Show = true;
		static int x_pos = 0;
		if (Boss_Pattern == 0)
		{
			for (int i = 0; i < 20; i++)
			{
				Boss_slave[i].init(x_pos, 0);
				Boss_slave[i].Enemy_Show = true;
				x_pos += 50;
			}
			x_pos = 0;
		}
		else if (Boss_Pattern == 1)
		{
			for (int i = 0; i < 20; i++)
			{
				Boss_slave1[i].init(x_pos, 500);
				Boss_slave1[i].Enemy_Show = true;
				x_pos += 50;
			}
			x_pos = 0;

		}
		else if (Boss_Pattern == 2)
		{
			Time++;
			if (Time >= 60 && Count < 5)
			{
				Boss_enemy.init((float)((rand() % 1000)), rand() % 400);
				Count++;
				Time = 0;
			}
			else if (Count >= 5)
			{
				Count = 0;
				Time = 0;
				Boss_Pattern++;
			}
			Create = false;
		}
		else if (Boss_Pattern == 3)
		{
			for (int i = 0; i < 10; i++)
			{
				Boss_bullet[i].B_xpos = i * 50;
				Boss_bullet[i].B_ypos = i * 20;
				Boss_bullet[i].bShow = true;
			}
		}

		else if (Boss_Pattern == 4)
		{
			for (int i = 0; i < 10; i++)
			{
				Boss_bullet1[i].B_xpos = i * 50 + 500;
				Boss_bullet1[i].B_ypos = i * 20;
				Boss_bullet1[i].bShow = true;
			}
		}
		else if (Boss_Pattern == 5)
		{
			for (int i = 0; i < 20; i++)
			{
				Boss_bullet2[i].B_xpos = i * 80;
				Boss_bullet2[i].B_ypos = 0;
				Boss_bullet2[i].bShow = true;
			}
		}
		else if (Boss_Pattern == 6)
			isClear = true;
	}
}


void Image_Change(int score, LPDIRECT3DTEXTURE9 &Num_image)
{
	switch (score)
	{
	case 0:
		D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
			L"Number0.png",    // the file name
			D3DX_DEFAULT,    // default width
			D3DX_DEFAULT,    // default height
			D3DX_DEFAULT,    // no mip mapping
			NULL,    // regular usage
			D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
			D3DPOOL_MANAGED,    // typical memory handling
			D3DX_DEFAULT,    // no filtering
			D3DX_DEFAULT,    // no mip filtering
			D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
			NULL,    // no image info struct
			NULL,    // not using 256 colors
			&Num_image);    // load to sprite
		break;

	case 1:
		D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
			L"Number1.png",    // the file name
			D3DX_DEFAULT,    // default width
			D3DX_DEFAULT,    // default height
			D3DX_DEFAULT,    // no mip mapping
			NULL,    // regular usage
			D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
			D3DPOOL_MANAGED,    // typical memory handling
			D3DX_DEFAULT,    // no filtering
			D3DX_DEFAULT,    // no mip filtering
			D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
			NULL,    // no image info struct
			NULL,    // not using 256 colors
			&Num_image);    // load to sprite
		break;
	case 2:
		D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
			L"Number2.png",    // the file name
			D3DX_DEFAULT,    // default width
			D3DX_DEFAULT,    // default height
			D3DX_DEFAULT,    // no mip mapping
			NULL,    // regular usage
			D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
			D3DPOOL_MANAGED,    // typical memory handling
			D3DX_DEFAULT,    // no filtering
			D3DX_DEFAULT,    // no mip filtering
			D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
			NULL,    // no image info struct
			NULL,    // not using 256 colors
			&Num_image);    // load to sprite
		break;
	case 3:
		D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
			L"Number3.png",    // the file name
			D3DX_DEFAULT,    // default width
			D3DX_DEFAULT,    // default height
			D3DX_DEFAULT,    // no mip mapping
			NULL,    // regular usage
			D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
			D3DPOOL_MANAGED,    // typical memory handling
			D3DX_DEFAULT,    // no filtering
			D3DX_DEFAULT,    // no mip filtering
			D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
			NULL,    // no image info struct
			NULL,    // not using 256 colors
			&Num_image);    // load to sprite
		break;
	case 4:
		D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
			L"Number4.png",    // the file name
			D3DX_DEFAULT,    // default width
			D3DX_DEFAULT,    // default height
			D3DX_DEFAULT,    // no mip mapping
			NULL,    // regular usage
			D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
			D3DPOOL_MANAGED,    // typical memory handling
			D3DX_DEFAULT,    // no filtering
			D3DX_DEFAULT,    // no mip filtering
			D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
			NULL,    // no image info struct
			NULL,    // not using 256 colors
			&Num_image);    // load to sprite
		break;
	case 5:
		D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
			L"Number5.png",    // the file name
			D3DX_DEFAULT,    // default width
			D3DX_DEFAULT,    // default height
			D3DX_DEFAULT,    // no mip mapping
			NULL,    // regular usage
			D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
			D3DPOOL_MANAGED,    // typical memory handling
			D3DX_DEFAULT,    // no filtering
			D3DX_DEFAULT,    // no mip filtering
			D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
			NULL,    // no image info struct
			NULL,    // not using 256 colors
			&Num_image);    // load to sprite
		break;
	case 6:
		D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
			L"Number6.png",    // the file name
			D3DX_DEFAULT,    // default width
			D3DX_DEFAULT,    // default height
			D3DX_DEFAULT,    // no mip mapping
			NULL,    // regular usage
			D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
			D3DPOOL_MANAGED,    // typical memory handling
			D3DX_DEFAULT,    // no filtering
			D3DX_DEFAULT,    // no mip filtering
			D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
			NULL,    // no image info struct
			NULL,    // not using 256 colors
			&Num_image);    // load to sprite
		break;
	case 7:
		D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
			L"Number7.png",    // the file name
			D3DX_DEFAULT,    // default width
			D3DX_DEFAULT,    // default height
			D3DX_DEFAULT,    // no mip mapping
			NULL,    // regular usage
			D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
			D3DPOOL_MANAGED,    // typical memory handling
			D3DX_DEFAULT,    // no filtering
			D3DX_DEFAULT,    // no mip filtering
			D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
			NULL,    // no image info struct
			NULL,    // not using 256 colors
			&Num_image);    // load to sprite
		break;
	case 8:
		D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
			L"Number8.png",    // the file name
			D3DX_DEFAULT,    // default width
			D3DX_DEFAULT,    // default height
			D3DX_DEFAULT,    // no mip mapping
			NULL,    // regular usage
			D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
			D3DPOOL_MANAGED,    // typical memory handling
			D3DX_DEFAULT,    // no filtering
			D3DX_DEFAULT,    // no mip filtering
			D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
			NULL,    // no image info struct
			NULL,    // not using 256 colors
			&Num_image);    // load to sprite
		break;
	case 9:
		D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
			L"Number9.png",    // the file name
			D3DX_DEFAULT,    // default width
			D3DX_DEFAULT,    // default height
			D3DX_DEFAULT,    // no mip mapping
			NULL,    // regular usage
			D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
			D3DPOOL_MANAGED,    // typical memory handling
			D3DX_DEFAULT,    // no filtering
			D3DX_DEFAULT,    // no mip filtering
			D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
			NULL,    // no image info struct
			NULL,    // not using 256 colors
			&Num_image);    // load to sprite
		break;
	}
}