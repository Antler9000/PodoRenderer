#define IMGUI_DEFINE_MATH_OPERATORS
#include <windows.h>
#include "imgui.h"
#include "Sodo.h"
#include "Game.h"

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

	ImGui::Dummy(m_imGuiSpacingBaseSize * m_optionGUI.GetMasterScale());

	bool menuButtonClicked = ImGui::Button("Menu", m_imGuiSmallButtonBaseSize * m_optionGUI.GetMasterScale());
	if (menuButtonClicked == true)
	{
		m_gameState = GAME_STATE_PAUSED;
	}

	ImGui::End();
}

void Sodo::GUILobbyMenu(ImGuiViewport* imGuiViewPort, ImVec2 imGuiCenterPos)
{
	ImGui::SetNextWindowPos(imGuiCenterPos, ImGuiCond_Always, ImVec2(0.5f, 0.5f));
	ImGui::SetNextWindowSize(ImVec2(250.0f, 330.0f) * m_optionGUI.GetMasterScale(), ImGuiCond_Always);

	ImGui::Begin("Lobby", nullptr, m_imGuiBasicFlag);

	ImGui::Dummy(m_imGuiSpacingBaseSize * m_optionGUI.GetMasterScale());

	bool playButtonClicked = ImGui::Button("Play", m_imGuiSmallButtonBaseSize * m_optionGUI.GetMasterScale());
	if (playButtonClicked == true)
	{
		m_gameState = GAME_STATE_LOADING_TO_GAME;
	}

	ImGui::Dummy(m_imGuiSpacingBaseSize * m_optionGUI.GetMasterScale());
	ImGui::Separator();
	ImGui::Dummy(m_imGuiSpacingBaseSize * m_optionGUI.GetMasterScale());

	bool optionButtonClicked = ImGui::Button("Option", m_imGuiSmallButtonBaseSize * m_optionGUI.GetMasterScale());
	if (optionButtonClicked == true)
	{
		m_gameState = GAME_STATE_OPTION_FROM_LOBBY;
	}

	ImGui::Dummy(m_imGuiSpacingBaseSize * m_optionGUI.GetMasterScale());
	ImGui::Separator();
	ImGui::Dummy(m_imGuiSpacingBaseSize * m_optionGUI.GetMasterScale());

	bool exitButtonClicked = ImGui::Button("Exit", m_imGuiSmallButtonBaseSize * m_optionGUI.GetMasterScale());
	if (exitButtonClicked == true)
	{
		m_gameState = GAME_STATE_EXIT_FROM_LOBBY_TO_WINDOWS;
	}

	ImGui::End();
}

void Sodo::GUIPausedMenu(ImGuiViewport* imGuiViewPort, ImVec2 imGuiCenterPos)
{
	ImGui::SetNextWindowPos(imGuiCenterPos, ImGuiCond_Always, ImVec2(0.5f, 0.5f));
	ImGui::SetNextWindowSize(ImVec2(300.0f, 430.0f) * m_optionGUI.GetMasterScale(), ImGuiCond_Always);

	ImGui::Begin("Paused", nullptr, m_imGuiBasicFlag);

	ImGui::Dummy(m_imGuiSpacingBaseSize * m_optionGUI.GetMasterScale());

	bool resumeButtonClicked = ImGui::Button("Resume", m_imGuiSmallButtonBaseSize * m_optionGUI.GetMasterScale());
	if (resumeButtonClicked == true)
	{
		m_gameState = GAME_STATE_IN_GAME;
	}

	ImGui::Dummy(m_imGuiSpacingBaseSize * m_optionGUI.GetMasterScale());
	ImGui::Separator();
	ImGui::Dummy(m_imGuiSpacingBaseSize * m_optionGUI.GetMasterScale());

	bool optionButtonClicked = ImGui::Button("Option", m_imGuiSmallButtonBaseSize * m_optionGUI.GetMasterScale());
	if (optionButtonClicked == true)
	{
		m_gameState = GAME_STATE_OPTION_FROM_PAUSED;
	}

	ImGui::Dummy(m_imGuiSpacingBaseSize * m_optionGUI.GetMasterScale());
	ImGui::Separator();
	ImGui::Dummy(m_imGuiSpacingBaseSize * m_optionGUI.GetMasterScale());

	bool exitToLobbyButtonClicked = ImGui::Button("Exit to lobby", m_imGuiMediumButtonBaseSize * m_optionGUI.GetMasterScale());
	if (exitToLobbyButtonClicked == true)
	{
		m_gameState = GAME_STATE_EXIT_FROM_PAUSED_TO_LOBBY;
	}

	ImGui::Dummy(m_imGuiSpacingBaseSize * m_optionGUI.GetMasterScale());
	ImGui::Separator();
	ImGui::Dummy(m_imGuiSpacingBaseSize * m_optionGUI.GetMasterScale());

	bool exitToWindowButtonClicked = ImGui::Button("Exit to window", m_imGuiMediumButtonBaseSize * m_optionGUI.GetMasterScale());
	if (exitToWindowButtonClicked == true)
	{
		m_gameState = GAME_STATE_EXIT_FROM_PAUSED_TO_WINDOWS;
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

	ImGui::Dummy(m_imGuiSpacingBaseSize * m_optionGUI.GetMasterScale());

	bool startButtonClicked = ImGui::Button("Click here to start", m_imguiLargeButtonBaseSize * m_optionGUI.GetMasterScale());
	if (startButtonClicked == true)
	{
		m_gameState = GAME_STATE_IN_GAME;
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

	ImGui::Dummy(m_imGuiSpacingBaseSize * m_optionGUI.GetMasterScale());

	bool endButtonClicked = ImGui::Button("Click here to end", m_imguiLargeButtonBaseSize * m_optionGUI.GetMasterScale());
	if (endButtonClicked == true)
	{
		m_gameState = GAME_STATE_LOBBY;
	}

	ImGui::End();
}

void Sodo::GUIOptionFromLobby(ImGuiViewport* imGuiViewPort, ImVec2 imGuiCenterPos)
{
	ImGui::SetNextWindowPos(imGuiCenterPos, ImGuiCond_Always, ImVec2(0.5f, 0.5f));
	ImGui::SetNextWindowSize(ImVec2(700.0f, 850.0f) * m_optionGUI.GetMasterScale(), ImGuiCond_Always);

	ImGui::Begin("Option", nullptr, m_imGuiBasicFlag);

	bool backButtonClicked = ImGui::Button("Back", m_imGuiSmallButtonBaseSize * m_optionGUI.GetMasterScale());
	if (backButtonClicked == true)
	{
		OptionSave();

		m_gameState = GAME_STATE_LOBBY;
	}

	GUIOptionCommon();

	ImGui::End();
}

void Sodo::GUIOptionFromPaused(ImGuiViewport* imGuiViewPort, ImVec2 imGuiCenterPos)
{
	ImGui::SetNextWindowPos(imGuiCenterPos, ImGuiCond_Always, ImVec2(0.5f, 0.5f));
	ImGui::SetNextWindowSize(ImVec2(700.0f, 850.0f) * m_optionGUI.GetMasterScale(), ImGuiCond_Always);

	ImGui::Begin("Option", nullptr, m_imGuiBasicFlag);

	bool backButtonClicked = ImGui::Button("Back", m_imGuiSmallButtonBaseSize * m_optionGUI.GetMasterScale());
	if (backButtonClicked == true)
	{
		OptionSave();

		m_gameState = GAME_STATE_PAUSED;
	}

	GUIOptionCommon();

	ImGui::End();
}

void Sodo::GUIExitFromLobbyToWindows(ImGuiViewport* imGuiViewPort, ImVec2 imGuiCenterPos)
{
	ImGui::SetNextWindowPos(imGuiCenterPos, ImGuiCond_Always, ImVec2(0.5f, 0.5f));
	ImGui::SetNextWindowSize(ImVec2(600.0f, 200.0f) * m_optionGUI.GetMasterScale(), ImGuiCond_Always);

	ImGui::Begin("Check", nullptr, m_imGuiBasicFlag);

	ImGui::Dummy(m_imGuiSpacingBaseSize * m_optionGUI.GetMasterScale());

	ImGui::Text("Do you really want to exit to window?");

	GUIExitCommon(GAME_STATE_LOBBY, GAME_STATE_TERMINATE);

	ImGui::End();
}

void Sodo::GUIExitFromPausedToWindows(ImGuiViewport* imGuiViewPort, ImVec2 imGuiCenterPos)
{
	ImGui::SetNextWindowPos(imGuiCenterPos, ImGuiCond_Always, ImVec2(0.5f, 0.5f));
	ImGui::SetNextWindowSize(ImVec2(600.0f, 200.0f) * m_optionGUI.GetMasterScale(), ImGuiCond_Always);

	ImGui::Begin("Check", nullptr, m_imGuiBasicFlag);

	ImGui::Dummy(m_imGuiSpacingBaseSize * m_optionGUI.GetMasterScale());

	ImGui::Text("Do you really want to exit to window?");

	GUIExitCommon(GAME_STATE_PAUSED, GAME_STATE_TERMINATE);

	ImGui::End();
}

void Sodo::GUIExitFromPausedToLobby(ImGuiViewport* imGuiViewPort, ImVec2 imGuiCenterPos)
{
	ImGui::SetNextWindowPos(imGuiCenterPos, ImGuiCond_Always, ImVec2(0.5f, 0.5f));
	ImGui::SetNextWindowSize(ImVec2(600.0f, 200.0f) * m_optionGUI.GetMasterScale(), ImGuiCond_Always);

	ImGui::Begin("Check", nullptr, m_imGuiBasicFlag);

	ImGui::Dummy(m_imGuiSpacingBaseSize * m_optionGUI.GetMasterScale());

	ImGui::Text("Do you really want to exit to lobby?");

	GUIExitCommon(GAME_STATE_PAUSED, GAME_STATE_LOADING_TO_LOBBY);

	ImGui::End();
}

void Sodo::GUIOptionCommon()
{
	bool previousFullScreenState = m_optionFullScreen.IsActive();
	bool previousHDRState = m_optionHDR.IsActive();
	int previousGUIState = m_optionGUI.masterSize;

	ImGui::Dummy(m_imGuiSpacingBaseSize * m_optionGUI.GetMasterScale());

	ImGui::Text("Display");
	ImGui::Checkbox("Full Screen", &m_optionFullScreen.userEnabled);
	ImGui::BeginDisabled(m_optionHDR.IsSupported() == false);
	ImGui::Checkbox("HDR", &m_optionHDR.userEnabled);
	ImGui::EndDisabled();
	ImGui::SameLine();
	ImGui::BeginDisabled(m_optionTearing.IsSupported() == false);
	ImGui::Checkbox("VRR", &m_optionTearing.userEnabled);
	ImGui::EndDisabled();

	ImGui::Dummy(m_imGuiSpacingBaseSize * m_optionGUI.GetMasterScale());
	ImGui::Separator();

	ImGui::Text("Graphics");
	ImGui::BeginDisabled(m_optionRayTracing.IsSupported() == false);
	ImGui::Checkbox("Ray Tracing", &m_optionRayTracing.userEnabled);
	ImGui::EndDisabled();
	ImGui::BeginDisabled(m_optionMeshShader.IsSupported() == false);
	ImGui::Checkbox("Mesh Shader", &m_optionMeshShader.userEnabled);
	ImGui::EndDisabled();

	ImGui::Dummy(m_imGuiSpacingBaseSize * m_optionGUI.GetMasterScale());
	ImGui::Separator();

	ImGui::Text("GUI");
	const char* masterSizeStrings[] = { "50%", "75%", "100%", "125%", "150%" };
	int selectedIndex = (m_optionGUI.masterSize - 50) / 25;
	if (ImGui::Combo("Master Size", &selectedIndex, masterSizeStrings, _countof(masterSizeStrings)) == true)
	{
		m_optionGUI.masterSize = 50 + 25 * selectedIndex;
	}

	ImGui::Dummy(m_imGuiSpacingBaseSize * m_optionGUI.GetMasterScale());
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
}

void Sodo::GUIExitCommon(GameState from, GameState to)
{
	ImGui::Dummy(m_imGuiSpacingBaseSize);

	bool noButtonClicked = ImGui::Button("No", m_imGuiSmallButtonBaseSize * m_optionGUI.GetMasterScale());
	if (noButtonClicked == true)
	{
		m_gameState = from;
	}

	ImGui::SameLine();

	bool yesButtonClicked = ImGui::Button("Yes", m_imGuiSmallButtonBaseSize * m_optionGUI.GetMasterScale());
	if (yesButtonClicked == true)
	{
		if (to == GAME_STATE_TERMINATE)
		{
			DestroyWindow(m_hWnd);
		}
		else
		{
			m_gameState = to;
		}
	}
}