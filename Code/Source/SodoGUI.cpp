#define IMGUI_DEFINE_MATH_OPERATORS
#include <windows.h>
#include <stack>
#include <cstdlib>
#include "imgui.h"
#include "Sodo.h"
#include "Game.h"

void Sodo::GUILobby(ImGuiViewport* imGuiViewPort, ImVec2 imGuiCenterPos)
{
	ImGui::SetNextWindowPos(imGuiCenterPos, ImGuiCond_Always, ImVec2(0.5f, 0.5f));
	ImGui::SetNextWindowSize(ImVec2(250.0f, 330.0f) * m_optionGUI.GetMasterScale(), ImGuiCond_Always);

	ImGui::Begin("Lobby", nullptr, m_imGuiBasicFlag);

	ImGui::Dummy(m_imGuiSpacingSize);

	bool playButtonClicked = ImGui::Button("Play", m_imGuiSmallButtonSize);
	if (playButtonClicked == true)
	{
		m_previousGameStates = std::stack<GameState>();
		m_nowGameState = GAME_STATE_LOADING_TO_GAME;
	}

	ImGui::Dummy(m_imGuiSpacingSize);
	ImGui::Separator();
	ImGui::Dummy(m_imGuiSpacingSize);

	bool optionButtonClicked = ImGui::Button("Option", m_imGuiSmallButtonSize);
	if (optionButtonClicked == true)
	{
		m_previousGameStates.push(m_nowGameState);
		m_nowGameState = GAME_STATE_OPTION;
	}

	ImGui::Dummy(m_imGuiSpacingSize);
	ImGui::Separator();
	ImGui::Dummy(m_imGuiSpacingSize);

	bool exitButtonClicked = ImGui::Button("Exit", m_imGuiSmallButtonSize);
	if (exitButtonClicked == true)
	{
		m_previousGameStates.push(m_nowGameState);
		m_nowGameState = GAME_STATE_CHECK_EXIT_TO_WINDOW;
	}

	ImGui::End();
}

void Sodo::GUILoadingToGame(ImGuiViewport* imGuiViewPort, ImVec2 imGuiCenterPos)
{
	ImGuiWindowFlags loadingGuiFlag = m_imGuiBasicFlag | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground;

	ImVec2 pos = ImVec2(
		imGuiCenterPos.x,
		imGuiViewPort->Pos.y + imGuiViewPort->Size.y * 0.9f
	);

	ImGui::SetNextWindowPos(pos, ImGuiCond_Always, ImVec2(0.5f, 0.5f));
	ImGui::SetNextWindowSize(ImVec2(400.0f, 200.0f) * m_optionGUI.GetMasterScale(), ImGuiCond_Always);

	ImGui::Begin("Loading", nullptr, loadingGuiFlag);

	ImGui::Dummy(m_imGuiSpacingSize);

	bool startButtonClicked = ImGui::Button("Click here to start", m_imGuiLargeButtonSize);
	if (startButtonClicked == true)
	{
		m_previousGameStates = std::stack<GameState>();
		m_nowGameState = GAME_STATE_IN_GAME;
	}

	ImGui::End();
}

void Sodo::GUIInGame(ImGuiViewport* imGuiViewPort, ImVec2 imGuiCenterPos)
{
	ImVec2 pos = ImVec2(
		imGuiViewPort->Pos.x,
		imGuiViewPort->Pos.y + imGuiViewPort->Size.y * 0.75f
	);

	ImVec2 size = ImVec2(
		imGuiViewPort->Size.x,
		imGuiViewPort->Size.y * 0.25f
	);

	ImGui::SetNextWindowPos(pos, ImGuiCond_Always);
	ImGui::SetNextWindowSize(size, ImGuiCond_Always);

	ImGui::Begin("In game", nullptr, m_imGuiBasicFlag);

	ImGui::Dummy(m_imGuiSpacingSize);

	bool menuButtonClicked = ImGui::Button("Menu", m_imGuiSmallButtonSize);
	if (menuButtonClicked == true)
	{
		m_previousGameStates.push(m_nowGameState);
		m_nowGameState = GAME_STATE_PAUSED_GAME;
	}

	ImGui::End();
}

void Sodo::GUIPausedGame(ImGuiViewport* imGuiViewPort, ImVec2 imGuiCenterPos)
{
	ImGui::SetNextWindowPos(imGuiCenterPos, ImGuiCond_Always, ImVec2(0.5f, 0.5f));
	ImGui::SetNextWindowSize(ImVec2(300.0f, 430.0f) * m_optionGUI.GetMasterScale(), ImGuiCond_Always);

	ImGui::Begin("Paused", nullptr, m_imGuiBasicFlag);

	ImGui::Dummy(m_imGuiSpacingSize);

	bool resumeButtonClicked = ImGui::Button("Resume", m_imGuiSmallButtonSize);
	bool escKeyPressed = ImGui::IsKeyPressed(ImGuiKey_Escape, false);
	if (resumeButtonClicked == true || escKeyPressed == true)
	{
		m_nowGameState = m_previousGameStates.top();
		m_previousGameStates.pop();
	}

	ImGui::Dummy(m_imGuiSpacingSize);
	ImGui::Separator();
	ImGui::Dummy(m_imGuiSpacingSize);

	bool optionButtonClicked = ImGui::Button("Option", m_imGuiSmallButtonSize);
	if (optionButtonClicked == true)
	{
		m_previousGameStates.push(m_nowGameState);
		m_nowGameState = GAME_STATE_OPTION;
	}

	ImGui::Dummy(m_imGuiSpacingSize);
	ImGui::Separator();
	ImGui::Dummy(m_imGuiSpacingSize);

	bool exitToLobbyButtonClicked = ImGui::Button("Exit to lobby", m_imGuiMediumButtonSize);
	if (exitToLobbyButtonClicked == true)
	{
		m_previousGameStates.push(m_nowGameState);
		m_nowGameState = GAME_STATE_CHECK_EXIT_TO_LOBBY;
	}

	ImGui::Dummy(m_imGuiSpacingSize);
	ImGui::Separator();
	ImGui::Dummy(m_imGuiSpacingSize);

	bool exitToWindowButtonClicked = ImGui::Button("Exit to window", m_imGuiMediumButtonSize);
	if (exitToWindowButtonClicked == true)
	{
		m_previousGameStates.push(m_nowGameState);
		m_nowGameState = GAME_STATE_CHECK_EXIT_TO_WINDOW;
	}

	ImGui::End();
}

void Sodo::GUICheckExitToLobby(ImGuiViewport* imGuiViewPort, ImVec2 imGuiCenterPos)
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
		m_nowGameState = m_previousGameStates.top();
		m_previousGameStates.pop();
	}

	ImGui::SameLine();

	bool yesButtonClicked = ImGui::Button("Yes", m_imGuiSmallButtonSize);
	if (yesButtonClicked == true)
	{
		m_previousGameStates = std::stack<GameState>();
		m_nowGameState = GAME_STATE_LOADING_TO_LOBBY;
	}

	ImGui::End();
}

void Sodo::GUILoadingToLobby(ImGuiViewport* imGuiViewPort, ImVec2 imGuiCenterPos)
{
	ImGuiWindowFlags loadingGuiFlag = m_imGuiBasicFlag | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground;

	ImVec2 pos = ImVec2(
		imGuiCenterPos.x,
		imGuiViewPort->Pos.y + imGuiViewPort->Size.y * 0.9f
	);

	ImGui::SetNextWindowPos(pos, ImGuiCond_Always, ImVec2(0.5f, 0.5f));
	ImGui::SetNextWindowSize(ImVec2(400.0f, 200.0f) * m_optionGUI.GetMasterScale(), ImGuiCond_Always);

	ImGui::Begin("Loading", nullptr, loadingGuiFlag);

	ImGui::Dummy(m_imGuiSpacingSize);

	bool endButtonClicked = ImGui::Button("Click here to end", m_imGuiLargeButtonSize);
	if (endButtonClicked == true)
	{
		m_previousGameStates = std::stack<GameState>();
		m_nowGameState = GAME_STATE_LOBBY;
	}

	ImGui::End();
}

void Sodo::GUIOption(ImGuiViewport* imGuiViewPort, ImVec2 imGuiCenterPos)
{
	ImGui::SetNextWindowPos(imGuiCenterPos, ImGuiCond_Always, ImVec2(0.5f, 0.5f));
	ImGui::SetNextWindowSize(ImVec2(700.0f, 850.0f) * m_optionGUI.GetMasterScale(), ImGuiCond_Always);

	ImGui::Begin("Option", nullptr, m_imGuiBasicFlag);

	bool backButtonClicked = ImGui::Button("Back", m_imGuiSmallButtonSize);
	bool escKeyPressed = ImGui::IsKeyPressed(ImGuiKey_Escape, false);
	if (backButtonClicked == true || escKeyPressed == true)
	{
		OptionSave();

		m_nowGameState = m_previousGameStates.top();
		m_previousGameStates.pop();
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
	const char* masterSizeStrings[] = { "50%", "75%", "100%", "125%", "150%" };
	int selectedIndex = (m_optionGUI.masterSize - 50) / 25;
	if (ImGui::Combo("Master Size", &selectedIndex, masterSizeStrings, _countof(masterSizeStrings)) == true)
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

void Sodo::GUICheckExitToWindow(ImGuiViewport* imGuiViewPort, ImVec2 imGuiCenterPos)
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
		m_nowGameState = m_previousGameStates.top();
		m_previousGameStates.pop();
	}

	ImGui::SameLine();

	bool yesButtonClicked = ImGui::Button("Yes", m_imGuiSmallButtonSize);
	if (yesButtonClicked == true)
	{
		DestroyWindow(m_hWnd);
	}

	ImGui::End();
}