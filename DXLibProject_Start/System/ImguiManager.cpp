#include "pch.h"
#include "ImguiManager.h"
#include<d3d11.h>
#include<backends/imgui_impl_dx11.h>
#include<backends/imgui_impl_win32.h>


void ImguiManager::Init()
{
	// imgui本体を生成
	ImGui::CreateContext();

	// ダーク設定
	ImGui::StyleColorsDark();

	HWND hwnd = GetMainWindowHandle();

	// windowsの入力を取得
	ImGui_ImplWin32_Init(hwnd);
	// DiretX11を初期化
	auto* device = (ID3D11Device*)GetUseDirect3D11Device();
	auto* context = (ID3D11DeviceContext*)GetUseDirect3D11DeviceContext();

	ImGui_ImplDX11_Init(device, context);

}

void ImguiManager::BeginFrame()
{
	// マウスの入力状態を取得
	UpdateMouseInput();

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();

	// UI生成を通知
	ImGui::NewFrame();

}

void ImguiManager::EndFrame()
{
	ImGui::Render();

	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

void ImguiManager::Release()
{
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}

void ImguiManager::UpdateMouseInput()
{
	ImGuiIO& io = ImGui::GetIO();

	// DXライブラリからマウス情報を取得
	int mouce = DxLib::GetMouseInput();
	int wheel = DxLib::GetMouseWheelRotVol();

	// 取得しいた情報をImGuiに渡す
	io.AddMouseButtonEvent(0, (mouce & MOUSE_INPUT_LEFT) != 0);
	io.AddMouseButtonEvent(1, (mouce & MOUSE_INPUT_RIGHT) != 0);
	io.AddMouseButtonEvent(2, (mouce & MOUSE_INPUT_MIDDLE) != 0);
	io.AddMouseButtonEvent(0.0f, static_cast<float>(wheel) / 120.0f);

}
