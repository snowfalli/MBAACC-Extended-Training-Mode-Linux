#pragma once
#include "../Common/Common.h"

#include "dllmain.h"

extern HWND window;

extern bool bInit;

extern void* d3d9Device[119];
extern LPDIRECT3DDEVICE9 pD3DDevice;
extern LPD3DXFONT d3dFont;

void DrawFilledRect(int x, int y, int w, int h, D3DCOLOR color, IDirect3DDevice9* dev);

bool Hook(char* src, char* dst, int len);

char* TrampHook(char* src, char* dst, unsigned int len);

BOOL CALLBACK EnumWindowsCallback(HWND handle, LPARAM lParam);

HWND GetProcessWindow();
bool GetD3D9Device(void** pTable, size_t Size);

HRESULT APIENTRY hkEndScene(LPDIRECT3DDEVICE9 pDevice);
HRESULT APIENTRY hkBeginScene(LPDIRECT3DDEVICE9 pDevice);
HRESULT APIENTRY hkReset(LPDIRECT3DDEVICE9 pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters);
HRESULT APIENTRY hkPresent(LPDIRECT3DDEVICE9 pDevice, const RECT *pScourceRect, const RECT *pDestRect, HWND hDestWindowOverride, const RGNDATA *pDirtyRegion);

typedef HRESULT(APIENTRY* tEndScene)(LPDIRECT3DDEVICE9 pDevice);
typedef HRESULT(APIENTRY* tBeginScene)(LPDIRECT3DDEVICE9 pDevice);
typedef HRESULT(APIENTRY* tReset)(LPDIRECT3DDEVICE9 pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters);
typedef HRESULT(APIENTRY* tPresent)(LPDIRECT3DDEVICE9 pDevice, const RECT *pScourceRect, const RECT *pDestRect, HWND hDestWindowOverride, const RGNDATA *pDirtyRegion);

extern tEndScene oEndScene;
extern tBeginScene oBeginScene;
extern tReset oReset;
extern tPresent oPresent;
