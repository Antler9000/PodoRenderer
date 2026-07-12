#define IMGUI_DEFINE_MATH_OPERATORS
#include <windows.h>
#include <d3dx12_root_signature.h>
#include <d3dx12_barriers.h>
#include <d3d12.h>
#include <DirectXMath.h>
#include <dxgi.h>
#include <stack>
#include <format>
#include <string>
#include <cstdlib>
#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx12.h"
#include "Sodo.h"
#include "Game.h"
#include "Debug.h"

using namespace DirectX;
using std::wstring;

void Sodo::UpdateWorldTimers()
{
	m_worldTimerTotal.Update();
	m_worldTimerFrame.Update();

	m_worldTimerFrame.Mark();
}

void Sodo::UpdateDebugCaption()
{
#ifdef _DEBUG
	static Timer worldTimerCaption;

	worldTimerCaption.Update();

	//NOTE : SetWindowTextW를 너무 자주 호출하면 시스템 부하로 인해 윈도우 전체가 먹통이 되니 반복에 텀을 주자
	if (worldTimerCaption.GetTimeMilli() > 100.0f)
	{
		
		int fps = (m_worldTimerFrame.GetTimeMilli() != 0) ? static_cast<int>(1000 / m_worldTimerFrame.GetTimeMilli()) : 0;

		wstring caption = std::format(
			L"{} (월드 경과 시간 : {:06.1F} s / 월드 프레임 시간 : {:0.4f} ms / FPS : {:3d} fps / 마우스 위치 : {:04d} p, {:04d} p / 스크롤 각도 : {:04d} unit)",
			m_pAppName,
			m_worldTimerTotal.GetTimeMilli() / 1000,
			m_worldTimerFrame.GetTimeMilli(),
			(fps > 999) ? 999 : fps,
			m_inputMousePositionClient.x,
			m_inputMousePositionClient.y,
			m_inputScrollDelta
		);

		SetWindowTextW(m_hWnd, caption.c_str());

		worldTimerCaption.Mark();
	}
#endif
}

void Sodo::UpdateWorld()
{
	if (IsWorldStopped() == true)
	{
		return;
	}
}

void Sodo::UpdateSceneAndGUI()
{
	if (IsSceneAndGUIStopped() == true)
	{
		return;
	}

	ResetQueuedCommands();

	ThrowIfFailed(m_commandAllocator->Reset());
	ThrowIfFailed(m_commandList->Reset(m_commandAllocator.Get(), nullptr));

	ID3D12DescriptorHeap* descriptorHeaps[] = { m_descriptorHeapCBVSRVUAV.Get() };
	m_commandList->SetDescriptorHeaps(_countof(descriptorHeaps), descriptorHeaps);

	CD3DX12_RESOURCE_BARRIER barrierPresentToRenderTarget = CD3DX12_RESOURCE_BARRIER::Transition(
		m_screenBackBuffers[m_screenBackBufferIndex].Get(),
		D3D12_RESOURCE_STATE_PRESENT,
		D3D12_RESOURCE_STATE_RENDER_TARGET
	);
	m_commandList->ResourceBarrier(1, &barrierPresentToRenderTarget);

	CD3DX12_CPU_DESCRIPTOR_HANDLE cpuHandleRTV = m_descriptorHeapRTVCpuStartHandle;
	cpuHandleRTV.Offset(m_screenBackBufferIndex, m_descriptorHeapRTVIncrementSize);

	m_commandList->OMSetRenderTargets(1, &cpuHandleRTV, true, &m_descriptorHeapDSVCpuStartHandle);
	m_commandList->RSSetViewports(1, &m_screenViewPort);
	m_commandList->RSSetScissorRects(1, &m_screenScissorRectangle);
		

	FLOAT sinZeroToOne = (XMScalarSin(static_cast<float>(m_worldTimerTotal.GetTimeMilli()) / 1000) + 1) / 2;
	FLOAT pTestColor[4] = { sinZeroToOne, sinZeroToOne, sinZeroToOne, 1.0f };
	m_commandList->ClearRenderTargetView(cpuHandleRTV, pTestColor, 0, nullptr);
	m_commandList->ClearDepthStencilView(
		m_descriptorHeapDSVCpuStartHandle,
		D3D12_CLEAR_FLAG_DEPTH | D3D12_CLEAR_FLAG_STENCIL,
		1.0f,
		0,
		0,
		nullptr
	);

	UpdateGUI();

	CD3DX12_RESOURCE_BARRIER barrierRenderTargetToPresent = CD3DX12_RESOURCE_BARRIER::Transition(
		m_screenBackBuffers[m_screenBackBufferIndex].Get(),
		D3D12_RESOURCE_STATE_RENDER_TARGET,
		D3D12_RESOURCE_STATE_PRESENT
	);
	m_commandList->ResourceBarrier(1, &barrierRenderTargetToPresent);

	ThrowIfFailed(m_commandList->Close());
	ID3D12CommandList* commandLists[] = { m_commandList.Get() };
	m_commandQueue->ExecuteCommandLists(_countof(commandLists), commandLists);

	if (m_optionTearing.IsActive() == true)
	{
		ThrowIfFailed(m_screenSwapChain->Present(0, DXGI_PRESENT_ALLOW_TEARING));
	}
	else
	{
		ThrowIfFailed(m_screenSwapChain->Present(1, 0));
	}

	m_screenBackBufferIndex = m_screenSwapChain->GetCurrentBackBufferIndex();
}

void Sodo::UpdateGUI()
{
	ImGui_ImplDX12_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	ImGuiViewport* pImGuiViewPort = ImGui::GetMainViewport();
	ImVec2 imGuiCenterPos = pImGuiViewPort->GetCenter();

	m_imGuiSpacingSize = ImVec2(0.0f, 10.0f) * m_optionGUI.GetMasterScale();
	m_imGuiSmallButtonSize = ImVec2(120.0f, 40.0f) * m_optionGUI.GetMasterScale();
	m_imGuiMediumButtonSize = ImVec2(240.0f, 40.0f) * m_optionGUI.GetMasterScale();
	m_imGuiLargeButtonSize = ImVec2(360.0f, 40.0f) * m_optionGUI.GetMasterScale();

	switch (m_gameStatePresent)
	{
		case GAME_STATE_LOBBY:
		{
			UpdateGUILobby(pImGuiViewPort, imGuiCenterPos);

			break;
		}

		case GAME_STATE_LOADING_TO_GAME:
		{
			UpdateGUILoadingToGame(pImGuiViewPort, imGuiCenterPos);

			break;
		}

		case GAME_STATE_IN_GAME:
		{
			UpdateGUIInGame(pImGuiViewPort, imGuiCenterPos);

			break;
		}

		case GAME_STATE_PAUSED_GAME:
		{
			UpdateGUIPausedGame(pImGuiViewPort, imGuiCenterPos);

			break;
		}

		case GAME_STATE_CHECK_EXIT_TO_LOBBY:
		{
			UpdateGUICheckExitToLobby(pImGuiViewPort, imGuiCenterPos);

			break;
		}

		case GAME_STATE_LOADING_TO_LOBBY:
		{
			UpdateGUILoadingToLobby(pImGuiViewPort, imGuiCenterPos);

			break;
		}

		case GAME_STATE_OPTION:
		{
			UpdateGUIOption(pImGuiViewPort, imGuiCenterPos);

			break;
		}

		case GAME_STATE_CHECK_EXIT_TO_WINDOW:
		{
			UpdateGUICheckExitToWindow(pImGuiViewPort, imGuiCenterPos);

			break;
		}
	}

	ImGui::Render();
	ImGui_ImplDX12_RenderDrawData(ImGui::GetDrawData(), m_commandList.Get());
}


void Sodo::UpdateGUILobby(ImGuiViewport* pImGuiViewPort, ImVec2 imGuiCenterPos)
{
	ImGui::SetNextWindowPos(imGuiCenterPos, ImGuiCond_Always, ImVec2(0.5f, 0.5f));
	ImGui::SetNextWindowSize(ImVec2(250.0f, 330.0f) * m_optionGUI.GetMasterScale(), ImGuiCond_Always);

	ImGui::Begin("Lobby", nullptr, m_imGuiBasicFlag);

	ImGui::Dummy(m_imGuiSpacingSize);

	bool playButtonClicked = ImGui::Button("Play", m_imGuiSmallButtonSize);
	if (playButtonClicked == true)
	{
		m_gameStatesPrevious = std::stack<GameState>();
		m_gameStatePresent = GAME_STATE_LOADING_TO_GAME;
		WorldTimersReset();
		WorldTimersStop();
		InputReset();
	}

	ImGui::Dummy(m_imGuiSpacingSize);
	ImGui::Separator();
	ImGui::Dummy(m_imGuiSpacingSize);

	bool optionButtonClicked = ImGui::Button("Option", m_imGuiSmallButtonSize);
	if (optionButtonClicked == true)
	{
		m_gameStatesPrevious.push(m_gameStatePresent);
		m_gameStatePresent = GAME_STATE_OPTION;
	}

	ImGui::Dummy(m_imGuiSpacingSize);
	ImGui::Separator();
	ImGui::Dummy(m_imGuiSpacingSize);

	bool exitButtonClicked = ImGui::Button("Exit", m_imGuiSmallButtonSize);
	if (exitButtonClicked == true)
	{
		m_gameStatesPrevious.push(m_gameStatePresent);
		m_gameStatePresent = GAME_STATE_CHECK_EXIT_TO_WINDOW;
	}

	ImGui::End();
}

void Sodo::UpdateGUILoadingToGame(ImGuiViewport* pImGuiViewPort, ImVec2 imGuiCenterPos)
{
	ImGuiWindowFlags loadingGuiFlag = m_imGuiBasicFlag | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground;

	ImVec2 pos = ImVec2(
		imGuiCenterPos.x,
		pImGuiViewPort->Pos.y + pImGuiViewPort->Size.y * 0.9f
	);

	ImGui::SetNextWindowPos(pos, ImGuiCond_Always, ImVec2(0.5f, 0.5f));
	ImGui::SetNextWindowSize(ImVec2(400.0f, 200.0f) * m_optionGUI.GetMasterScale(), ImGuiCond_Always);

	ImGui::Begin("Loading", nullptr, loadingGuiFlag);

	ImGui::Dummy(m_imGuiSpacingSize);

	bool startButtonClicked = ImGui::Button("Click here to start", m_imGuiLargeButtonSize);
	if (startButtonClicked == true)
	{
		m_gameStatesPrevious = std::stack<GameState>();
		m_gameStatePresent = GAME_STATE_IN_GAME;
		WorldTimersReset();
		WorldTimersStart();
		InputReset();
	}

	ImGui::End();
}

void Sodo::UpdateGUIInGame(ImGuiViewport* pImGuiViewPort, ImVec2 imGuiCenterPos)
{
	ImVec2 pos = ImVec2(
		pImGuiViewPort->Pos.x,
		pImGuiViewPort->Pos.y + pImGuiViewPort->Size.y * 0.75f
	);

	ImVec2 size = ImVec2(
		pImGuiViewPort->Size.x,
		pImGuiViewPort->Size.y * 0.25f
	);

	ImGui::SetNextWindowPos(pos, ImGuiCond_Always);
	ImGui::SetNextWindowSize(size, ImGuiCond_Always);

	ImGui::Begin("In game", nullptr, m_imGuiBasicFlag);

	ImGui::Dummy(m_imGuiSpacingSize);

	bool menuButtonClicked = ImGui::Button("Menu", m_imGuiSmallButtonSize);
	bool escKeyPressed = ImGui::IsKeyPressed(ImGuiKey_Escape, false);
	if (menuButtonClicked == true || escKeyPressed == true)
	{
		m_gameStatesPrevious.push(m_gameStatePresent);
		m_gameStatePresent = GAME_STATE_PAUSED_GAME;
		WorldTimersStop();
	}

	ImGui::End();
}

void Sodo::UpdateGUIPausedGame(ImGuiViewport* pImGuiViewPort, ImVec2 imGuiCenterPos)
{
	ImGui::SetNextWindowPos(imGuiCenterPos, ImGuiCond_Always, ImVec2(0.5f, 0.5f));
	ImGui::SetNextWindowSize(ImVec2(300.0f, 430.0f) * m_optionGUI.GetMasterScale(), ImGuiCond_Always);

	ImGui::Begin("Paused", nullptr, m_imGuiBasicFlag);

	ImGui::Dummy(m_imGuiSpacingSize);

	bool resumeButtonClicked = ImGui::Button("Resume", m_imGuiSmallButtonSize);
	bool escKeyPressed = ImGui::IsKeyPressed(ImGuiKey_Escape, false);
	if (resumeButtonClicked == true || escKeyPressed == true)
	{
		if (m_gameStatesPrevious.empty() == false)
		{
			m_gameStatePresent = m_gameStatesPrevious.top();
			m_gameStatesPrevious.pop();
			WorldTimersStart();
		}
	}

	ImGui::Dummy(m_imGuiSpacingSize);
	ImGui::Separator();
	ImGui::Dummy(m_imGuiSpacingSize);

	bool optionButtonClicked = ImGui::Button("Option", m_imGuiSmallButtonSize);
	if (optionButtonClicked == true)
	{
		m_gameStatesPrevious.push(m_gameStatePresent);
		m_gameStatePresent = GAME_STATE_OPTION;
	}

	ImGui::Dummy(m_imGuiSpacingSize);
	ImGui::Separator();
	ImGui::Dummy(m_imGuiSpacingSize);

	bool exitToLobbyButtonClicked = ImGui::Button("Exit to lobby", m_imGuiMediumButtonSize);
	if (exitToLobbyButtonClicked == true)
	{
		m_gameStatesPrevious.push(m_gameStatePresent);
		m_gameStatePresent = GAME_STATE_CHECK_EXIT_TO_LOBBY;
	}

	ImGui::Dummy(m_imGuiSpacingSize);
	ImGui::Separator();
	ImGui::Dummy(m_imGuiSpacingSize);

	bool exitToWindowButtonClicked = ImGui::Button("Exit to window", m_imGuiMediumButtonSize);
	if (exitToWindowButtonClicked == true)
	{
		m_gameStatesPrevious.push(m_gameStatePresent);
		m_gameStatePresent = GAME_STATE_CHECK_EXIT_TO_WINDOW;
	}

	ImGui::End();
}

void Sodo::UpdateGUICheckExitToLobby(ImGuiViewport* pImGuiViewPort, ImVec2 imGuiCenterPos)
{
	ImGui::SetNextWindowPos(imGuiCenterPos, ImGuiCond_Always, ImVec2(0.5f, 0.5f));
	ImGui::SetNextWindowSize(ImVec2(600.0f, 200.0f) * m_optionGUI.GetMasterScale(), ImGuiCond_Always);

	ImGui::Begin("Check", nullptr, m_imGuiBasicFlag);

	ImGui::Dummy(m_imGuiSpacingSize);

	ImGui::Text("Do you really want to exit to lobby?");

	ImGui::Dummy(m_imGuiSpacingSize);

	bool noButtonClicked = ImGui::Button("No", m_imGuiSmallButtonSize);
	bool escKeyPressed = ImGui::IsKeyPressed(ImGuiKey_Escape, false);
	if (noButtonClicked == true || escKeyPressed == true)
	{
		if (m_gameStatesPrevious.empty() == false)
		{
			m_gameStatePresent = m_gameStatesPrevious.top();
			m_gameStatesPrevious.pop();
		}
	}

	ImGui::SameLine();

	bool yesButtonClicked = ImGui::Button("Yes", m_imGuiSmallButtonSize);
	if (yesButtonClicked == true)
	{
		m_gameStatesPrevious = std::stack<GameState>();
		m_gameStatePresent = GAME_STATE_LOADING_TO_LOBBY;
		WorldTimersReset();
		WorldTimersStop();
		InputReset();
	}

	ImGui::End();
}

void Sodo::UpdateGUILoadingToLobby(ImGuiViewport* pImGuiViewPort, ImVec2 imGuiCenterPos)
{
	ImGuiWindowFlags loadingGuiFlag = m_imGuiBasicFlag | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground;

	ImVec2 pos = ImVec2(
		imGuiCenterPos.x,
		pImGuiViewPort->Pos.y + pImGuiViewPort->Size.y * 0.9f
	);

	ImGui::SetNextWindowPos(pos, ImGuiCond_Always, ImVec2(0.5f, 0.5f));
	ImGui::SetNextWindowSize(ImVec2(400.0f, 200.0f) * m_optionGUI.GetMasterScale(), ImGuiCond_Always);

	ImGui::Begin("Loading", nullptr, loadingGuiFlag);

	ImGui::Dummy(m_imGuiSpacingSize);

	bool endButtonClicked = ImGui::Button("Click here to end", m_imGuiLargeButtonSize);
	if (endButtonClicked == true)
	{
		m_gameStatesPrevious = std::stack<GameState>();
		m_gameStatePresent = GAME_STATE_LOBBY;
		WorldTimersReset();
		WorldTimersStop();
		InputReset();
	}

	ImGui::End();
}

void Sodo::UpdateGUIOption(ImGuiViewport* pImGuiViewPort, ImVec2 imGuiCenterPos)
{
	ImGui::SetNextWindowPos(imGuiCenterPos, ImGuiCond_Always, ImVec2(0.5f, 0.5f));
	ImGui::SetNextWindowSize(ImVec2(700.0f, 850.0f) * m_optionGUI.GetMasterScale(), ImGuiCond_Always);

	ImGui::Begin("Option", nullptr, m_imGuiBasicFlag);

	bool backButtonClicked = ImGui::Button("Back", m_imGuiSmallButtonSize);
	bool escKeyPressed = ImGui::IsKeyPressed(ImGuiKey_Escape, false);
	if (backButtonClicked == true || escKeyPressed == true)
	{
		OptionSave();

		if (m_gameStatesPrevious.empty() == false)
		{
			m_gameStatePresent = m_gameStatesPrevious.top();
			m_gameStatesPrevious.pop();
		}
	}

	bool previousFullScreenState = m_optionFullScreen.IsActive();
	bool previousHDRState = m_optionHDR.IsActive();
	int previousGUIState = m_optionGUI.masterSize;

	ImGui::Dummy(m_imGuiSpacingSize);

	ImGui::Text("Display");
	ImGui::Checkbox("Full Screen", &m_optionFullScreen.userEnabled);
	ImGui::BeginDisabled(m_optionHDR.IsSupported() == false);
	ImGui::Checkbox("HDR", &m_optionHDR.userEnabled);
	ImGui::EndDisabled();
	ImGui::SameLine();
	ImGui::BeginDisabled(m_optionTearing.IsSupported() == false);
	ImGui::Checkbox("VRR", &m_optionTearing.userEnabled);
	ImGui::EndDisabled();

	ImGui::Dummy(m_imGuiSpacingSize);
	ImGui::Separator();

	ImGui::Text("Graphics");
	ImGui::BeginDisabled(m_optionRayTracing.IsSupported() == false);
	ImGui::Checkbox("Ray Tracing", &m_optionRayTracing.userEnabled);
	ImGui::EndDisabled();
	ImGui::BeginDisabled(m_optionMeshShader.IsSupported() == false);
	ImGui::Checkbox("Mesh Shader", &m_optionMeshShader.userEnabled);
	ImGui::EndDisabled();

	ImGui::Dummy(m_imGuiSpacingSize);
	ImGui::Separator();

	ImGui::Text("GUI");
	const char* masterSizeStringArray[] = { "50%", "75%", "100%", "125%", "150%" };
	int selectedIndex = (m_optionGUI.masterSize - 50) / 25;
	if (ImGui::Combo("Master Size", &selectedIndex, masterSizeStringArray, _countof(masterSizeStringArray)) == true)
	{
		m_optionGUI.masterSize = 50 + 25 * selectedIndex;
	}

	ImGui::Dummy(m_imGuiSpacingSize);
	ImGui::Separator();

	ImGui::Text("Sound");
	ImGui::SliderInt("Master Volume", &m_optionSound.masterVolume, 0, 100, "%d%%");
	ImGui::SliderInt("UI Volume", &m_optionSound.uiVolume, 0, 100, "%d%%");
	ImGui::SliderInt("Unit Volume", &m_optionSound.unitVolume, 0, 100, "%d%%");
	ImGui::SliderInt("Effect Volume", &m_optionSound.effectVolume, 0, 100, "%d%%");
	ImGui::SliderInt("Music Volume", &m_optionSound.musicVolume, 0, 100, "%d%%");

	bool nowFullScreenState = m_optionFullScreen.IsActive();
	bool nowHDRState = m_optionHDR.IsActive();
	int nowGUIState = m_optionGUI.masterSize;

	if (previousFullScreenState != nowFullScreenState)
	{
		m_needResetScreenMode = true;
	}
	if (previousHDRState != nowHDRState)
	{
		m_needResetHDR = true;
	}
	if (previousGUIState != nowGUIState)
	{
		m_needResetGUI = true;
	}

	ImGui::End();
}

void Sodo::UpdateGUICheckExitToWindow(ImGuiViewport* pImGuiViewPort, ImVec2 imGuiCenterPos)
{
	ImGui::SetNextWindowPos(imGuiCenterPos, ImGuiCond_Always, ImVec2(0.5f, 0.5f));
	ImGui::SetNextWindowSize(ImVec2(600.0f, 200.0f) * m_optionGUI.GetMasterScale(), ImGuiCond_Always);

	ImGui::Begin("Check", nullptr, m_imGuiBasicFlag);

	ImGui::Dummy(m_imGuiSpacingSize);

	ImGui::Text("Do you really want to exit to window?");

	ImGui::Dummy(m_imGuiSpacingSize);

	bool noButtonClicked = ImGui::Button("No", m_imGuiSmallButtonSize);
	bool escKeyPressed = ImGui::IsKeyPressed(ImGuiKey_Escape, false);
	if (noButtonClicked == true || escKeyPressed == true)
	{
		if (m_gameStatesPrevious.empty() == false)
		{
			m_gameStatePresent = m_gameStatesPrevious.top();
			m_gameStatesPrevious.pop();
		}

		if (m_gameStatePresent == GAME_STATE_IN_GAME)
		{
			WorldTimersStart();
		}
	}

	ImGui::SameLine();

	bool yesButtonClicked = ImGui::Button("Yes", m_imGuiSmallButtonSize);
	if (yesButtonClicked == true)
	{
		DestroyWindow(m_hWnd);
	}

	ImGui::End();
}