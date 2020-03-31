#pragma once

#ifndef __COMPONENT_H__
#define __COMPONENT_H__

#include "Engine_Include.h"

BEGIN(ENGINE)

class ENGINE_DLL CComponent // ������Ʈ���� ���� �ֻ��� �θ� �ɰ��̴�.
{
protected:
	explicit CComponent();
public:
	virtual ~CComponent() PURE; // ������ �ڽĵ��� �������̵� �ϰԲ� �Ұ�.
	// ��� ������ ��� �Լ��� ������ �� ������Ʈ���� �ٸ����̱� ������ �θ��� �Ҹ��ڴ� �θ� �ʿ䰡 ������
	// �ڽ��� �Ҹ��ڴ� ������ �ҷ����ϱ� ����.

public:
	virtual void Update() {}
	virtual void LateUpdate() {}
	virtual void Render() { }
	// ��� ������ �Ҽ��ְ� ��� �������� update�� �� �� �ִ�.
};

END
#endif