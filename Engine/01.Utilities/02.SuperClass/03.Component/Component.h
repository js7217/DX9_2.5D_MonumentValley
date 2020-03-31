#pragma once

#ifndef __COMPONENT_H__
#define __COMPONENT_H__

#include "Engine_Include.h"

BEGIN(ENGINE)

class ENGINE_DLL CComponent // 컴포넌트들의 가장 최상위 부모가 될것이다.
{
protected:
	explicit CComponent();
public:
	virtual ~CComponent() PURE; // 강제로 자식들이 오버라이딩 하게끔 할것.
	// 멤버 변수와 멤버 함수의 구성이 매 컴포넌트마다 다를것이기 때문에 부모의 소멸자는 부를 필요가 없지만
	// 자식의 소멸자는 무조건 불러야하기 때문.

public:
	virtual void Update() {}
	virtual void LateUpdate() {}
	virtual void Render() { }
	// 어떤건 렌더만 할수있고 어떤건 렌더없이 update만 할 수 있다.
};

END
#endif