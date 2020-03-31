#include "Engine_Include.h"
#include "SetTransForm.h"

using namespace ENGINE;

D3DXMATRIX CSetTransForm::m_matWorld = { 1.f, 0.f, 0.f, 0.f,
										0.f, 1.f, 0.f, 0.f,
										0.f, 0.f, 1.f, 0.f,
										0.f, 0.f, 0.f, 1.f };
D3DXMATRIX CSetTransForm::m_matView = { 1.f, 0.f, 0.f, 0.f,
										0.f, 1.f, 0.f, 0.f,
										0.f, 0.f, 1.f, 0.f,
										0.f, 0.f, 0.f, 1.f };

D3DXMATRIX CSetTransForm::m_matProj = { 1.f, 0.f, 0.f, 0.f,
										0.f, 1.f, 0.f, 0.f,
										0.f, 0.f, 1.f, 0.f,
										0.f, 0.f, 0.f, 1.f };

const D3DXMATRIX & CSetTransForm::GetMatWorld()
{
	// TODO: 여기에 반환 구문을 삽입합니다.
	return m_matWorld;
}

const D3DXMATRIX & CSetTransForm::GetMatView()
{
	// TODO: 여기에 반환 구문을 삽입합니다.
	return m_matView;
}

const D3DXMATRIX & CSetTransForm::GetMatProj()
{
	// TODO: 여기에 반환 구문을 삽입합니다.
	return m_matProj;
}

void CSetTransForm::Set_TransForm(D3DTRANSFORMSTATETYPE eTransformStateType, const D3DXMATRIX* matTrans)
{
	switch (eTransformStateType)
	{
	case D3DTS_WORLD:
		D3DXMatrixIdentity(&m_matWorld);
		m_matWorld = *matTrans;
		break;
	case D3DTS_VIEW:
		D3DXMatrixIdentity(&m_matView);
		m_matView = *matTrans;
		break;
	case D3DTS_PROJECTION:
		D3DXMatrixIdentity(&m_matProj);
		m_matProj = *matTrans;
		break;
	default:
		break;
	}
}