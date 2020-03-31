#include "Engine_Include.h"
#include "BillBoard.h"
#include "Transform.h"
#include "SetTransform.h"

using namespace ENGINE;

CBillBoard::CBillBoard()
{
}

CBillBoard::CBillBoard(ENGINE::CTransform * pTransform)
	: m_pTransform(pTransform)
{
}

CBillBoard::~CBillBoard()
{
}

void CBillBoard::LateUpdate()
{
	D3DXMATRIX matView = ENGINE::CSetTransForm::GetMatView(); // ������� �����´�.
	D3DXMatrixInverse(&matView, nullptr, &matView);

	D3DXMATRIX matRotY, matScale;
	D3DXMatrixIdentity(&matRotY);

	D3DXMatrixScaling(&matScale, 
		m_pTransform->GetSize().x, 
		m_pTransform->GetSize().y, 
		m_pTransform->GetSize().z);

	matRotY._11 = matView._11;
	matRotY._13 = matView._13;
	matRotY._31 = matView._31;
	matRotY._33 = matView._33; // y�� ȸ�� ��� ���� ����.

	memcpy(&matRotY._41, &m_pTransform->GetPos(), sizeof(D3DXVECTOR3)); // ��ġ�� ����.


	m_pTransform->SetWorldMatrix(matScale * matRotY); // ������ * ���� * �̵���.
}

CBillBoard * CBillBoard::Create(ENGINE::CTransform * pTransform)
{
	NULL_CHECK_MSG_RETURN(pTransform, L"This GameObject Transform Component Create Failed", nullptr);
	return new CBillBoard(pTransform);
}
