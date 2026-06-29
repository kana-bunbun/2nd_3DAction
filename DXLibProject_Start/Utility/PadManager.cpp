#include "PadManager.h"
#include"../World/Character/Player/Player.h"
#include"../World/UI/ItemCursor.h"
#include"../World/Map/TileManager.h"
#include"../System/TimeManager.h"
PadManager::PadManager():
	m_pPlayer(nullptr),
	m_pItemCursor(nullptr),
	m_pTileManager(nullptr),
	m_padState(PadManager::PadState::Invalid)
{

}

PadManager::~PadManager()
{

}

void PadManager::Init()
{

}

void PadManager::End()
{

}

void PadManager::Update()
{
	

	if (Input::IsPressed(Input::Button::Y, Input::Pad::P1)) {
		if (m_pItemCursor->GetIsBlendMenu()) {
			ChangePadState(PadManager::PadState::Player);
		}
		else {
			ChangePadState(PadManager::PadState::ItemMenu);
		}
	}

	if (Input::IsPressed(Input::Button::A, Input::Pad::P1)) {
		if (m_pPlayer->m_pad == Input::Pad::Invalid) {
		}
			ChangePadState(PadManager::PadState::Player);
	}
}

void PadManager::ChangePadState(const PadState& padState)
{
	m_padState = padState;
	switch (m_padState)
	{
	case PadManager::PadState::Invalid:
		if (m_pItemCursor) {
			m_pItemCursor->SetPad(Input::Pad::P1);
			m_pItemCursor->SetIsBlendMenu(false);
		}
		if (m_pPlayer)
			m_pPlayer->m_pad = Input::Pad::Invalid;

		if (m_pTileManager)
			m_pTileManager->SetPad(Input::Pad::Invalid);

		break;
	case PadManager::PadState::Player:
		if (m_pPlayer)
			m_pPlayer->m_pad = Input::Pad::P1;
		
		if (m_pItemCursor) {
			m_pItemCursor->SetPad(Input::Pad::P1);
		}
		if (m_pTileManager)
			m_pTileManager->SetPad(Input::Pad::P1);
		TimeManager::SetTimeScale(1.0f);
		break;
	case PadManager::PadState::ItemMenu:
		if (m_pItemCursor) {
			m_pItemCursor->SetPad(Input::Pad::P1);
		TimeManager::SetTimeScale(0.0f);
		//m_pItemCursor->SetIsBlendMenu(true);
		}
		
		if (m_pPlayer)
			m_pPlayer->m_pad = Input::Pad::Invalid;

		if (m_pTileManager)
			m_pTileManager->SetPad(Input::Pad::Invalid);
		break;
	case PadManager::PadState::Title:
		break;
	case PadManager::PadState::Max:
		break;
	default:
		break;
	}
}
