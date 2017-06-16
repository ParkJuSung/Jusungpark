//-----------------------------------------------------------------------------
// File: Textures1.cpp
//
// Desc: Better than just lights and materials, 3D objects look much more
//       convincing when texture-mapped. Textures1 can be thought of as a sort
//       of wallpaper, that is shrinkwrapped to fit a texture. Textures1 are
//       typically loaded from image files, and D3DX provides a utility to
//       function to do this for us. Like a vertex buffer, Textures1 have
//       Lock() and Unlock() functions to access (read or write) the image
//       data. Textures1 have a width, height, miplevel, and pixel format. The
//       miplevel is for "mipmapped" Textures1, an advanced performance-
//       enhancing feature which uses lower resolutions of the texture for
//       objects in the distance where detail is less noticeable. The pixel
//       format determines how the colors are stored in a texel. The most
//       common formats are the 16-bit R5G6B5 format (5 bits of red, 6-bits of
//       green and 5 bits of blue) and the 32-bit A8R8G8B8 format (8 bits each
//       of alpha, red, green, and blue).
//
//       Textures1 are associated with geometry through texture coordinates.
//       Each vertex has one or more sets of texture coordinates, which are
//       named tu and tv and range from 0.0 to 1.0. Texture coordinates can be
//       supplied by the geometry, or can be automatically generated using
//       Direct3D texture coordinate generation (which is an advanced feature).
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//-----------------------------------------------------------------------------
#include <Windows.h>
#include <mmsystem.h>
#include <d3dx9.h>
#pragma warning( disable : 4996 ) // disable deprecated warning 
#include <strsafe.h>
#pragma warning( default : 4996 )

//-----------------------------------------------------------------------------
// Global variables
//-----------------------------------------------------------------------------
LPDIRECT3D9             g_pD3D = NULL; // Used to create the D3DDevice
LPDIRECT3DDEVICE9       g_pd3dDevice = NULL; // Our rendering device
LPDIRECT3DVERTEXBUFFER9 g_pVB = NULL; // Buffer to hold vertices
LPDIRECT3DTEXTURE9      g_pTexture = NULL; // Our texture
LPDIRECT3DTEXTURE9      g_pTexture1 = NULL; // Our texture
LPDIRECT3DTEXTURE9      g_pTexture2 = NULL; // Our texture
LPDIRECT3DTEXTURE9      g_pTexture3 = NULL; // Our texture
bool down = false;
bool up = false;
bool left = false;
bool right = false;
float x = 0;
float y = 0;
bool scale = false;

										   // A structure for our custom vertex type. We added texture coordinates
struct CUSTOMVERTEX
{
	D3DXVECTOR3 position; // The position
	D3DCOLOR color;    // The color
	FLOAT tu, tv;   // The texture coordinates
};

#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ|D3DFVF_DIFFUSE|D3DFVF_TEX1)


//-----------------------------------------------------------------------------
// Name: InitD3D()
// Desc: Initializes Direct3D
//-----------------------------------------------------------------------------
HRESULT InitD3D(HWND hWnd)
{
	// Create the D3D object.
	if (NULL == (g_pD3D = Direct3DCreate9(D3D_SDK_VERSION)))
		return E_FAIL;
	// Set up the structure used to create the D3DDevice. Since we are now
	// using more complex geometry, we will create a device with a zbuffer.
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	// Create the D3DDevice
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp, &g_pd3dDevice)))
	{
		return E_FAIL;
	}
	// Turn off culling
	g_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	// Turn off D3D lighting
	g_pd3dDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	// Turn on the zbuffer
	g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	return S_OK;
}


//-----------------------------------------------------------------------------
// Name: InitGeometry()
// Desc: Create the Textures1 and vertex buffers
//-----------------------------------------------------------------------------
HRESULT InitGeometry()
{
	// Use D3DX to create a texture from a file based image
	//D3DXCreateTextureFromFile(g_pd3dDevice, L"forward1.png", &g_pTexture);


	// Create the vertex buffer.
	if (FAILED(g_pd3dDevice->CreateVertexBuffer(6 * sizeof(CUSTOMVERTEX),
		0, D3DFVF_CUSTOMVERTEX,
		D3DPOOL_DEFAULT, &g_pVB, NULL)))
	{
		return E_FAIL;
	}
	// Fill the vertex buffer. We are setting the tu and tv texture
	// coordinates, which range from 0.0 to 1.0
	CUSTOMVERTEX* pVertices;
	if (FAILED(g_pVB->Lock(0, 0, (void**)&pVertices, 0)))
		return E_FAIL;
	/*for( DWORD i = 0; i < 50; i++ )
	{*/
	D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVertices[0].position = D3DXVECTOR3(x, y, 0.0f);
	pVertices[0].color = 0xffffffff;
	pVertices[0].tu = 0.0f;
	pVertices[0].tv = 0.0f;

	pVertices[1].position = D3DXVECTOR3(x+1.0f, y, 0.0f);
	pVertices[1].color = 0xffffffff;
	pVertices[1].tu = 1.0f;
	pVertices[1].tv = 0.0f;

	pVertices[2].position = D3DXVECTOR3(x, y+1.0f, 0.0f);
	pVertices[2].color = 0xffffffff;
	pVertices[2].tu = 0.0f;
	pVertices[2].tv = 1.0f;

	pVertices[3].position = D3DXVECTOR3(x+1.0f, y+1.0f, 0.0f);
	pVertices[3].color = 0xffffffff;
	pVertices[3].tu = 1.0f;
	pVertices[3].tv = 1.0f;

	pVertices[4].position = D3DXVECTOR3(x+1.0f, y, 0.0f);
	pVertices[4].color = 0xffffffff;
	pVertices[4].tu = 1.0f;
	pVertices[4].tv = 0.0f;

	pVertices[5].position = D3DXVECTOR3(x, y+1.0f, 0.0f);
	pVertices[5].color = 0xffffffff;
	pVertices[5].tu = 0.0f;
	pVertices[5].tv = 1.0f;
	// }
	g_pVB->Unlock();
	return S_OK;
}


//-----------------------------------------------------------------------------
// Name: Cleanup()
// Desc: Releases all previously initialized objects
//-----------------------------------------------------------------------------
VOID Cleanup()
{
	if (g_pTexture != NULL)
		g_pTexture->Release();
	if (g_pVB != NULL)
		g_pVB->Release();
	if (g_pd3dDevice != NULL)
		g_pd3dDevice->Release();
	if (g_pD3D != NULL)
		g_pD3D->Release();
}

//-----------------------------------------------------------------------------
// Name: SetupMatrices()
// Desc: Sets up the world, view, and projection transform matrices.
//-----------------------------------------------------------------------------
VOID SetupMatrices()
{
	// Set up world matrix
	D3DXMATRIXA16 matWorld;
	D3DXMATRIXA16 matWorld1;
	D3DXMATRIXA16 matWorld2;
	D3DXMATRIXA16 matWorld3;
	D3DXMATRIXA16 matWorld4;
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixRotationX(&matWorld, 180.0f);
	D3DXMatrixTranslation(&matWorld1, x, y, 0);
	D3DXMatrixMultiply(&matWorld2, &matWorld, &matWorld1);

	if (scale)
		D3DXMatrixScaling(&matWorld3, 3.0f, 3.0f, 1.0f);
	else
		D3DXMatrixScaling(&matWorld3, 1.0f, 1.0f, 1.0f);

	D3DXMatrixMultiply(&matWorld4, &matWorld2, &matWorld3);
	g_pd3dDevice->SetTransform(D3DTS_WORLD, &matWorld4);
	// Set up our view matrix. A view matrix can be defined given an eye point,
	// a point to lookat, and a direction for which way is up. Here, we set the
	// eye five units back along the z-axis and up three units, look at the
	// origin, and define "up" to be in the y-direction.
	D3DXVECTOR3 vEyePt(0.0f, 0.0f, -5.0f);
	D3DXVECTOR3 vLookatPt(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);
	D3DXMATRIXA16 matView;
	D3DXMatrixLookAtLH(&matView, &vEyePt, &vLookatPt, &vUpVec);
	g_pd3dDevice->SetTransform(D3DTS_VIEW, &matView);
	// For the projection matrix, we set up a perspective transform (which
	// transforms geometry from 3D view space to 2D viewport space, with
	// a perspective divide making objects smaller in the distance). To build
	// a perpsective transform, we need the field of view (1/4 pi is common),
	// the aspect ratio, and the near and far clipping planes (which define at
	// what distances geometry should be no longer be rendered).
	D3DXMATRIXA16 matProj;
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4, 1.0f, 1.0f, 100.0f);
	g_pd3dDevice->SetTransform(D3DTS_PROJECTION, &matProj);
}


//-----------------------------------------------------------------------------
// Name: Render()
// Desc: Draws the scene
//-----------------------------------------------------------------------------
VOID Render()
{
	static int counter = 0;
	static int timecount = 0;
	// Clear the backbuffer and the zbuffer
	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB(255, 255, 255), 1.0f, 0);
	// Begin the scene
	if (SUCCEEDED(g_pd3dDevice->BeginScene()))
	{
		// Setup the world, view, and projection matrices
		SetupMatrices();
		timecount = timecount + 1;

		if(timecount%10==0)
			counter = counter + 1;

		if (down)
		{
			switch (counter % 4)
			{
			case 0:
				D3DXCreateTextureFromFile(g_pd3dDevice, L"forward1.png", &g_pTexture);
				g_pd3dDevice->SetTexture(0, g_pTexture);
				break;
			case 1:
				D3DXCreateTextureFromFile(g_pd3dDevice, L"forward2.png", &g_pTexture1);
				g_pd3dDevice->SetTexture(0, g_pTexture1);
				break;
			case 2:
				D3DXCreateTextureFromFile(g_pd3dDevice, L"forward3.png", &g_pTexture2);
				g_pd3dDevice->SetTexture(0, g_pTexture2);
				break;
			case 3:
				D3DXCreateTextureFromFile(g_pd3dDevice, L"forward4.png", &g_pTexture3);
				g_pd3dDevice->SetTexture(0, g_pTexture3);
				break;
			}
		}
		if (up)
		{
			switch (counter % 4)
			{
			case 0:
				D3DXCreateTextureFromFile(g_pd3dDevice, L"up1.png", &g_pTexture);
				g_pd3dDevice->SetTexture(0, g_pTexture);
				break;
			case 1:
				D3DXCreateTextureFromFile(g_pd3dDevice, L"up2.png", &g_pTexture1);
				g_pd3dDevice->SetTexture(0, g_pTexture1);
				break;
			case 2:
				D3DXCreateTextureFromFile(g_pd3dDevice, L"up3.png", &g_pTexture2);
				g_pd3dDevice->SetTexture(0, g_pTexture2);
				break;
			case 3:
				D3DXCreateTextureFromFile(g_pd3dDevice, L"up4.png", &g_pTexture3);
				g_pd3dDevice->SetTexture(0, g_pTexture3);
				break;
			}
		}
		if (left)
		{
			switch (counter % 4)
			{
			case 0:
				D3DXCreateTextureFromFile(g_pd3dDevice, L"left1.png", &g_pTexture);
				g_pd3dDevice->SetTexture(0, g_pTexture);
				break;
			case 1:
				D3DXCreateTextureFromFile(g_pd3dDevice, L"left2.png", &g_pTexture1);
				g_pd3dDevice->SetTexture(0, g_pTexture1);
				break;
			case 2:
				D3DXCreateTextureFromFile(g_pd3dDevice, L"left3.png", &g_pTexture2);
				g_pd3dDevice->SetTexture(0, g_pTexture2);
				break;
			case 3:
				D3DXCreateTextureFromFile(g_pd3dDevice, L"left4.png", &g_pTexture3);
				g_pd3dDevice->SetTexture(0, g_pTexture3);
				break;
			}
		}
		if (right)
		{
			switch (counter % 4)
			{
			case 0:
				D3DXCreateTextureFromFile(g_pd3dDevice, L"right1.png", &g_pTexture);
				g_pd3dDevice->SetTexture(0, g_pTexture);
				break;
			case 1:
				D3DXCreateTextureFromFile(g_pd3dDevice, L"right2.png", &g_pTexture1);
				g_pd3dDevice->SetTexture(0, g_pTexture1);
				break;
			case 2:
				D3DXCreateTextureFromFile(g_pd3dDevice, L"right3.png", &g_pTexture2);
				g_pd3dDevice->SetTexture(0, g_pTexture2);
				break;
			case 3:
				D3DXCreateTextureFromFile(g_pd3dDevice, L"right4.png", &g_pTexture3);
				g_pd3dDevice->SetTexture(0, g_pTexture3);
				break;
			}
		}
		//g_pd3dDevice->SetTexture(0, g_pTexture);
		g_pd3dDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
		g_pd3dDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
		g_pd3dDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
		g_pd3dDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_DISABLE);

		g_pd3dDevice->SetStreamSource(0, g_pVB, 0, sizeof(CUSTOMVERTEX));
		g_pd3dDevice->SetFVF(D3DFVF_CUSTOMVERTEX);
		g_pd3dDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);
		// End the scene
		g_pd3dDevice->EndScene();
	}
	// Present the backbuffer contents to the display
	g_pd3dDevice->Present(NULL, NULL, NULL, NULL);
}


//-----------------------------------------------------------------------------
// Name: MsgProc()
// Desc: The window's message handler
//-----------------------------------------------------------------------------
LRESULT WINAPI MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		Cleanup();
		PostQuitMessage(0);
		return 0;
	case WM_KEYDOWN:
		if (GetKeyState(0x41) && (wParam == 0x41))
		{
			right = false;
			down = false;
			up = false;
			left = true;
			x = x - 0.3f;

		}
		else if (GetKeyState(0x44) && (wParam == 0x44))
		{
			left = false;
			down = false;
			up = false;
			right = true;
			x = x + 0.3f;

		}
		else if (GetKeyState(0x53) && (wParam == 0x53))
		{
			left = false;
			right = false;
			up = false;
			down = true;
			y = y - 0.3f;

		}
		else if (GetKeyState(0x57) && (wParam == 0x57))
		{
			left = false;
			right = false;
			down = false;
			up = true;
			y = y + 0.3f;
		}
		else if (GetKeyState(VK_SPACE) && (wParam == VK_SPACE))
			scale = true;
		return 0;

	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}


//-----------------------------------------------------------------------------
// Name: WinMain()
// Desc: The application's entry point
//-----------------------------------------------------------------------------
INT WINAPI wWinMain(HINSTANCE hInst, HINSTANCE, LPWSTR, INT)
{
	UNREFERENCED_PARAMETER(hInst);
	// Register the window class
	WNDCLASSEX wc =
	{
		sizeof(WNDCLASSEX), CS_CLASSDC, MsgProc, 0L, 0L,
		GetModuleHandle(NULL), NULL, NULL, NULL, NULL,
		L"D3D Tutorial", NULL
	};
	RegisterClassEx(&wc);
	// Create the application's window
	HWND hWnd = CreateWindow(L"D3D Tutorial", L"D3D Tutorial 05: Textures1",
		WS_OVERLAPPEDWINDOW, 100, 100, 600, 600,
		NULL, NULL, wc.hInstance, NULL);
	// Initialize Direct3D
	if (SUCCEEDED(InitD3D(hWnd)))
	{
		// Create the scene geometry
		if (SUCCEEDED(InitGeometry()))
		{
			// Show the window
			ShowWindow(hWnd, SW_SHOWDEFAULT);
			UpdateWindow(hWnd);
			// Enter the message loop
			MSG msg;
			ZeroMemory(&msg, sizeof(msg));
			while (msg.message != WM_QUIT)
			{
				if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
				{
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
				else
					Render();
			}
		}
	}
	UnregisterClass(L"D3D Tutorial", wc.hInstance);
	return 0;
}