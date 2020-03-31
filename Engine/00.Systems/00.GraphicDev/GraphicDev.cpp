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
	// ��ġ �ʱ�ȭ
	// 1. ��ġ�� ������ ��ü ���� (IDirect3D9)
	// IDirect3D9 Com��ü�� ��ġ ������ IDirect3DDevice9 ��ü�� ������ �뵵�� ���.
	m_pSDK = Direct3DCreate9(D3D_SDK_VERSION);
	NULL_CHECK_MSG_RETURN(m_pSDK, L"Direct3DCreate9 Failed", E_FAIL);

	//if (nullptr == m_pSDK)
	//{
	//	// AfxMessageBox: MFC���� �����ϴ� MessageBox �Լ�.
	//	ERR_MSG(L"Direct3DCreate9 Failed");
	//	return E_FAIL;
	//}

	// 2. ��ġ�� ����(���� ����)
	D3DCAPS9	DeviceCaps;
	ZeroMemory(&DeviceCaps, sizeof(D3DCAPS9));

	// GetDeviceCaps�Լ�: �׷��� ��ġ�� ���� ����(���� ����)�� ������ �Լ�.
	// D3DDEVTYPE_HAL: HAL�� ���� ��ġ�� ����.
	// *** HAL(Hardware Abstraction Layer, �ϵ���� �߻� ����)
	HRESULT hr = m_pSDK->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &DeviceCaps);
	FAILED_CHECK_MSG_RETURN(hr, L"GetDeviceCaps Failed", E_FAIL);

	/*if (FAILED(m_pSDK->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &DeviceCaps)))
	{
		ERR_MSG(L"GetDeviceCaps Failed");
		return E_FAIL;
	}*/

	// 2-1. ������ ��ġ�� ���ؽ� ���μ��� ������ ����.
	// ���ؽ� ���μ���: ���� ��ȯ + ���� ó��.
	DWORD vp = 0;

	if (DeviceCaps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
		vp |= D3DCREATE_HARDWARE_VERTEXPROCESSING;	// �ϵ������ ���ؽ� ���μ����� ����Ѵ�.
	else
		vp |= D3DCREATE_SOFTWARE_VERTEXPROCESSING;

	// ���̷�Ʈ �󿡼� �����带 �����ϰ� ����ϵ��� �ϰڴ�.
	vp |= D3DCREATE_MULTITHREADED;

	// 3. ��ġ�� ������ ��ü ���� (IDirect3DDevice9)
	D3DPRESENT_PARAMETERS	d3dpp;
	ZeroMemory(&d3dpp, sizeof(D3DPRESENT_PARAMETERS));

	d3dpp.BackBufferCount = 1;
	d3dpp.BackBufferWidth = dwWinCX;
	d3dpp.BackBufferHeight = dwWinCY;
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;

	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	d3dpp.MultiSampleQuality = 0;

	// ȭ�� ������ �ؼҸ� ���� "����ü��" ����� ���.
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;

	d3dpp.hDeviceWindow = hWnd;
	d3dpp.Windowed = eMode;

	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
	
	// ��ü ȭ�� �� ���� ����� �ֻ����� ���� ��ġ�� �˾Ƽ� ����.
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	hr = m_pSDK->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,	hWnd, vp, &d3dpp, &m_pGraphicDev);
	FAILED_CHECK_MSG_RETURN(hr, L"CreateDevice Failed", E_FAIL);	

	// ��������Ʈ Com��ü ����
	hr = D3DXCreateSprite(m_pGraphicDev, &m_pSprite);
	FAILED_CHECK_MSG_RETURN(hr, L"D3DXCreateSprite Failed", E_FAIL);


	// ��Ʈ Com��ü ����
	D3DXFONT_DESCW tFontInfo = {};
	tFontInfo.Width = 10;
	tFontInfo.Height = 20;
	tFontInfo.Weight = FW_HEAVY;
	tFontInfo.CharSet = HANGEUL_CHARSET;
	lstrcpy(tFontInfo.FaceName, L"���");
	
	hr = D3DXCreateFontIndirect(m_pGraphicDev, &tFontInfo, &m_pFont);
	FAILED_CHECK_MSG_RETURN(hr, L"D3DXCreateFontIndirect Failed", E_FAIL);

	return S_OK;
}

void ENGINE::CGraphicDev::Release()
{
	// ���� ���� ����.
	if (SafeRelease(m_pFont))
		MSG_BOX(L"m_pFont Release Failed");	
	if (SafeRelease(m_pSprite))
		MSG_BOX(L"m_pSprite Release Failed");
	if(SafeRelease(m_pGraphicDev))
		MSG_BOX(L"m_pGraphicDev Release Failed");

	if (SafeRelease(m_pSDK))
		MSG_BOX(L"m_pSDK Release Failed");
}
