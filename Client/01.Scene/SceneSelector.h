#pragma once

#ifndef __SCENESELECTOR_H__
#define __SCENESELECTOR_H__

#include "stdafx.h"
#include "Logo.h"
#include "Stage.h"
#include "Stage2.h"
#include "Stage3.h"
#include "Stage4.h"
#include "Stage5.h"
#include "EndingScene.h"
class CSceneSelector
{
public:
	enum SCENE_ID { LOGO, STAGE, STAGE2, STAGE3, STAGE4, STAGE5, ENDING, SCENE_END };

public:
	explicit CSceneSelector(SCENE_ID eSceneID)
		: m_eSceneID(eSceneID)
	{

	}

public:
	HRESULT operator()(ENGINE::CScene** ppScene, LPDIRECT3DDEVICE9 pGraphicDev)
	{
		switch (m_eSceneID)
		{
		case CSceneSelector::LOGO:
			*ppScene = CLogo::Create(pGraphicDev);
			break;
		case CSceneSelector::STAGE:
			*ppScene = CStage::Create(pGraphicDev);
			break;
		case CSceneSelector::STAGE2:
			*ppScene = CStage2::Create(pGraphicDev);
			break;
		case CSceneSelector::STAGE3:
			*ppScene = CStage3::Create(pGraphicDev);
			break;
		case CSceneSelector::STAGE4:
			*ppScene = CStage4::Create(pGraphicDev);
			break;
		case CSceneSelector::STAGE5:
			*ppScene = CStage5::Create(pGraphicDev);
			break;
		case CSceneSelector::ENDING:
			*ppScene = CEndingScene::Create(pGraphicDev);
		//	(*ppScene)->SetIsEnding(true);
			break;
		case CSceneSelector::SCENE_END:
			break;
		default:
			break;
		}

		NULL_CHECK_RETURN(*ppScene, E_FAIL);
		return S_OK;
	}

private:
	SCENE_ID m_eSceneID;
};

#endif // !__SCENESELECTOR_H__
