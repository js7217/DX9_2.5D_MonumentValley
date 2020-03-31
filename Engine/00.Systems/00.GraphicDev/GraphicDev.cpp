#include "GraphicDev.h"

IMPLEMENT_SINGLETON(ENGINE::CGraphicDev)

ENGINE::CGraphicDev::CGraphicDev()
{
}


ENGINE::CGraphicDev::~CGraphicDev()
{
	Release();
}

LPDIRECT3DDEVICE9 ENGINE::CGraphicDev::GetDevice()
{
	return m_pGraphicDev;
}

LPD3DXSPRITE ENGINE::CGraphicDev::GetSprite()
{
	return m_pSprite;
}

LPD3DXFONT ENGINE::CGraphicDev::GetFont()
{
	return m_pFont;
}

HRESULT ENGINE::CGraphicDev::InitDevice(HWND hWnd,
	const DWORD & dwWinCX, 
	const DWORD & dwWinCY, 
	WIN_MODE eMode)
{
	// 장치 초기화
	// 1. 장치를 조사할 객체 생성 (IDirect3D9)
	// IDirect3D9 Com객체는 장치 검증과 IDirect3DDevice9 객체를 생성할 용도로 사용.
	m_pSDK = Direct3DCreate9(D3D_SDK_VERSION);
	NULL_CHECK_MSG_RETURN(m_pSDK, L"Direct3DCreate9 Failed", E_FAIL);

	//if (nullptr == m_pSDK)
	//{
	//	// AfxMessageBox: MFC에서 제공하는 MessageBox 함수.
	//	ERR_MSG(L"Direct3DCreate9 Failed");
	//	return E_FAIL;
	//}

	// 2. 장치를 조사(지원 수준)
	D3DCAPS9	DeviceCaps;
	ZeroMemory(&DeviceCaps, sizeof(D3DCAPS9));

	// GetDeviceCaps함수: 그래픽 장치에 대한 정보(지원 수준)를 얻어오는 함수.
	// D3DDEVTYPE_HAL: HAL을 토대로 장치를 조사.
	// *** HAL(Hardware Abstraction Layer, 하드웨어 추상 계층)
	HRESULT hr = m_pSDK->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &DeviceCaps);
	FAILED_CHECK_MSG_RETURN(hr, L"GetDeviceCaps Failed", E_FAIL);

	/*if (FAILED(m_pSDK->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &DeviceCaps)))
	{
		ERR_MSG(L"GetDeviceCaps Failed");
		return E_FAIL;
	}*/

	// 2-1. 조사한 장치의 버텍스 프로세싱 유무를 조사.
	// 버텍스 프로세싱: 정점 변환 + 조명 처리.
	DWORD vp = 0;

	if (DeviceCaps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
		vp |= D3DCREATE_HARDWARE_VERTEXPROCESSING;	// 하드웨어의 버텍스 프로세싱을 사용한다.
	else
		vp |= D3DCREATE_SOFTWARE_VERTEXPROCESSING;

	// 다이렉트 상에서 쓰레드를 안전하게 사용하도록 하겠다.
	vp |= D3DCREATE_MULTITHREADED;

	// 3. 장치를 제어할 객체 생성 (IDirect3DDevice9)
	D3DPRESENT_PARAMETERS	d3dpp;
	ZeroMemory(&d3dpp, sizeof(D3DPRESENT_PARAMETERS));

	d3dpp.BackBufferCount = 1;
	d3dpp.BackBufferWidth = dwWinCX;
	d3dpp.BackBufferHeight = dwWinCY;
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;

	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	d3dpp.MultiSampleQuality = 0;

	// 화면 깜빡임 해소를 위해 "스왑체인" 방식을 사용.
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;

	d3dpp.hDeviceWindow = hWnd;
	d3dpp.Windowed = eMode;

	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
	
	// 전체 화면 시 현재 모니터 주사율을 토대로 장치가 알아서 수행.
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	hr = m_pSDK->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,	hWnd, vp, &d3dpp, &m_pGraphicDev);
	FAILED_CHECK_MSG_RETURN(hr, L"CreateDevice Failed", E_FAIL);	

	// 스프라이트 Com객체 생성
	hr = D3DXCreateSprite(m_pGraphicDev, &m_pSprite);
	FAILED_CHECK_MSG_RETURN(hr, L"D3DXCreateSprite Failed", E_FAIL);


	// 폰트 Com객체 생성
	D3DXFONT_DESCW tFontInfo = {};
	tFontInfo.Width = 10;
	tFontInfo.Height = 20;
	tFontInfo.Weight = FW_HEAVY;
	tFontInfo.CharSet = HANGEUL_CHARSET;
	lstrcpy(tFontInfo.FaceName, L"고딕");
	
	hr = D3DXCreateFontIndirect(m_pGraphicDev, &tFontInfo, &m_pFont);
	FAILED_CHECK_MSG_RETURN(hr, L"D3DXCreateFontIndirect Failed", E_FAIL);

	return S_OK;
}

void ENGINE::CGraphicDev::Release()
{
	// 해제 순서 주의.
	if (SafeRelease(m_pFont))
		MSG_BOX(L"m_pFont Release Failed");	
	if (SafeRelease(m_pSprite))
		MSG_BOX(L"m_pSprite Release Failed");
	if(SafeRelease(m_pGraphicDev))
		MSG_BOX(L"m_pGraphicDev Release Failed");

	if (SafeRelease(m_pSDK))
		MSG_BOX(L"m_pSDK Release Failed");
}
