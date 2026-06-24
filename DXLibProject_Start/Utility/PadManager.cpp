#include "PadManager.h"
#include"../World/Character/Player/Player.h"
#include"../World/UI/ItemCursor.h"
#include"../World/Map/TileManager.h"
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
		if (m_pPlayer->m_pad == Input::Pad::Invalid) {
			ChangePadState(PadManager::PadState::Player);
			m_pItemCursor->UseItem();
		}
		else {
			ChangePadState(PadManager::PadState::ItemMenu);
		}
	}

	if (Input::IsPressed(Input::Button::A, Input::Pad::P1))
	if (m_pPlayer->m_pad == Input::Pad::Invalid) {
		ChangePadState(PadManager::PadState::Player);
	}
}

void PadManager::ChangePadState(const PadState& padState)
{
	m_padState = padState;
	switch (m_padState)
	{
	case PadManager::PadState::Invalid:
		if (m_pItemCursor)
			m_pItemCursor->SetPad(Input::Pad::Invalid);
	
		if (m_pPlayer)
			m_pPlayer->m_pad = Input::Pad::Invalid;

		if (m_pTileManager)
			m_pTileManager->SetPad(Input::Pad::Invalid);

		break;
	case PadManager::PadState::Player:
		if (m_pPlayer)
			m_pPlayer->m_pad = Input::Pad::P1;
		
		if (m_pItemCursor)
			m_pItemCursor->SetPad(Input::Pad::Invalid);

		if (m_pTileManager)
			m_pTileManager->SetPad(Input::Pad::P1);
		break;
	case PadManager::PadState::ItemMenu:
		if (m_pItemCursor)
			m_pItemCursor->SetPad(Input::Pad::P1);
		
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
