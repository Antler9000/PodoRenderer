#pragma once
#include <windows.h>
#include <d3dx12_root_signature.h>
#include <d3d12.h>
#include <dxgi1_6.h>
#include <dxgi1_4.h>
#include <dxgi.h>
#include <dxgicommon.h>
#include <dxgiformat.h>
#include <wrl/client.h>
#include <stack>
#include <string>
#include <fstream>
#include "imgui.h"
#include "BaseApp.h"
#include "Game.h"
#include "Option.h"
#include "Timer.h"
#include "Alloc.h"

class Sodo : public BaseApp<Sodo>
{
public:

	Sodo() : BaseApp(L"Sodo Sandbox")
	{

	}

	~Sodo()
	{
		ResetQueuedCommands();

		CloseFenceEvent();
		CloseImGui();
	}

	void InitApp()
	{
		InitFactory();
		InitAdapterAndOutput();
		InitDevice();
		InitFence();
		InitFenceEvent();
		InitCommandQueue();
		InitCommandAllocator();
		InitCommandList();
		InitFormatSupport();
		InitHDRSwapChainSupport();
		InitSavedOptions();
		InitScreenMode();
		InitSwapChain();
		InitBackBuffers();
		InitViewPort();
		InitScissorRectangle();
		InitDepthStencilBuffer();
		InitDescriptorHeapRTV();
		InitDescriptorHeapDSV();
		InitDescriptorHeapCBVSRVUAV();
		InitRTV();
		InitDSV();
		InitCBVSRVUAV();
		InitImGui();
		InitTimer();

		m_optionFullScreen.DebugPrint();
		m_optionHDR.DebugPrint();
		m_optionTearing.DebugPrint();
		m_optionRayTracing.DebugPrint();
		m_optionMeshShader.DebugPrint();
		m_optionGUI.DebugPrint();
		m_optionSound.DebugPrint();
	}

	int RunMessageLoop()
	{
		MSG msg = { };

		while (msg.message != WM_QUIT)
		{
			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else if (NeedResetDxgiInterface() == true)
			{
				ResetDxgiInterface();
			}
			else if (NeedResetScreenSetting() == true)
			{
				ResetScreenSetting();
			}
			else
			{
				if (IsStopped() == true)
				{
					Sleep(100);
				}
				else
				{
					UpdateTimers();
					UpdateCaption();
					UpdateImGui();
					UpdateScreen();
				}
			}
		}

		return (int)msg.wParam;
	}

	//NOTE : 이 메소드는 BaseApp에 작석된 WindowProcedure 정적 메소드에서 호출함
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

private:

	void CloseFenceEvent();
	void CloseImGui();

	void InitFactory();
	void InitAdapterAndOutput();
	bool InitOutput(IDXGIAdapter3* pAdapter);
	void InitDevice();
	void InitFence();
	void InitFenceEvent();
	void InitCommandQueue();
	void InitCommandAllocator();
	void InitCommandList();
	void InitFormatSupport();
	void InitHDRSwapChainSupport();
	void InitSavedOptions();
	void InitScreenMode();
	void InitSwapChain();
	void InitBackBuffers();
	void InitViewPort();
	void InitScissorRectangle();
	void InitDepthStencilBuffer();
	void InitDescriptorHeapRTV();
	void InitDescriptorHeapDSV();
	void InitDescriptorHeapCBVSRVUAV();
	void InitRTV();
	void InitDSV();
	void InitCBVSRVUAV();
	void InitImGui();
	void InitTimer();

	void UpdateTimers();
	void UpdateCaption();
	void UpdateImGui();
	void UpdateScreen();

	void InputMouseMove(WPARAM wParam, LPARAM lParam);
	void InputMouseLeftButtonDown(WPARAM wParam, LPARAM lParam);
	void InputMouseLeftButtonUp(WPARAM wParam, LPARAM lParam);
	void InputMouseRightButtonDown(WPARAM wParam, LPARAM lParam);
	void InputMouseRightButtonUp(WPARAM wParam, LPARAM lParam);
	void InputMouseMiddleButtonDown(WPARAM wParam, LPARAM lParam);
	void InputMouseMiddleButtonUp(WPARAM wParam, LPARAM lParam);
	void InputMouseWheelScroll(WPARAM wParam, LPARAM lParam);
	void InputKeyboardDown(WPARAM wParam, LPARAM lParam);

private:

	void ResetQueuedCommands();
	void ResetDxgiInterface();
	void ResetScreenSetting();
	void ResetToFullScreenMode();
	void ResetToWindowMode();

	void OptionSave();
	void OptionRestore();
	bool OptionReadBool(std::ifstream& fin, std::string optionName, bool& outOptionEnabled);
	bool OptionReadInt(std::ifstream& fin, std::string optionName, int& outOptionValue);

	void GUILobby(ImGuiViewport* pImGuiViewPort, ImVec2 imGuiCenterPos);
	void GUILoadingToGame(ImGuiViewport* pImGuiViewPort, ImVec2 imGuiCenterPos);
	void GUIInGame(ImGuiViewport* pImGuiViewPort, ImVec2 imGuiCenterPos);
	void GUIPausedGame(ImGuiViewport* pImGuiViewPort, ImVec2 imGuiCenterPos);
	void GUICheckExitToLobby(ImGuiViewport* pImGuiViewPort, ImVec2 imGuiCenterPos);
	void GUILoadingToLobby(ImGuiViewport* pImGuiViewPort, ImVec2 imGuiCenterPos);
	void GUIOption(ImGuiViewport* pImGuiViewPort, ImVec2 imGuiCenterPos);
	void GUICheckExitToWindow(ImGuiViewport* pImGuiViewPort, ImVec2 imGuiCenterPos);

public:

	//NOTE : ImGui에 넘겨주는 콜백 함수 속에서 기능해야 하므로 static으로 둠
	static inline		ImGuiDescriptorHeapAllocator	m_imGuiDescriptorHeapAllocator		= {};

	static constexpr	UINT							m_screenBackBufferCount				= 2;
	static constexpr	DXGI_FORMAT						m_screenBackBufferFormatSDR			= DXGI_FORMAT_R8G8B8A8_UNORM;
	static constexpr	DXGI_FORMAT						m_screenBackBufferFormatHDR			= DXGI_FORMAT_R16G16B16A16_FLOAT;
	static constexpr	DXGI_COLOR_SPACE_TYPE			m_screenBackBufferColorSpaceSDR		= DXGI_COLOR_SPACE_RGB_FULL_G22_NONE_P709;
	static constexpr	DXGI_COLOR_SPACE_TYPE			m_screenBackBufferColorSpaceHDR		= DXGI_COLOR_SPACE_RGB_FULL_G10_NONE_P709;
	static constexpr	DXGI_FORMAT						m_screenDepthStencilBufferFormat	= DXGI_FORMAT_D24_UNORM_S8_UINT;

	static constexpr	unsigned int					m_inputDragThresholdDist			= 20;

	static constexpr	UINT							m_imGuiDescriptorHeapCapacity		= 64;
	static constexpr	ImGuiWindowFlags				m_imGuiBasicFlag					= ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove
																							| ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings;

private:

	template <typename Interface>
	using ComPtr = Microsoft::WRL::ComPtr<Interface>;

	ComPtr<IDXGIFactory6>				m_dxgiFactory;													//NOTE : (기본) 성능순 어댑터 획득
	ComPtr<IDXGIAdapter3>				m_dxgiAdapter;													//NOTE : (기본) 자원의 메모리 상주성 관리
	ComPtr<IDXGIOutput>					m_dxgiOutput;
	ComPtr<IDXGIOutput6>				m_dxgiOutput6;													//NOTE : (옵션) HDR 모니터 정보 획득
	DXGI_OUTPUT_DESC1					m_dxgiOutputDesc									= {};		//NOTE : (옵션) HDR 모니터 정보 획득
	
	ComPtr<ID3D12Device>				m_device;
	ComPtr<ID3D12Device2>				m_device2;														//NOTE : (옵션) 메시 셰이더
	ComPtr<ID3D12Device5>				m_device5;														//NOTE : (옵션) 레이 트레이싱
	
	ComPtr<ID3D12Fence>					m_fence;
	UINT64								m_fenceCurrent										= 0;
	HANDLE								m_fenceEvent										= nullptr;
	
	ComPtr<ID3D12CommandQueue>			m_commandQueue;
	ComPtr<ID3D12CommandAllocator>		m_commandAllocator;
	ComPtr<ID3D12GraphicsCommandList>	m_commandList;
	ComPtr<ID3D12GraphicsCommandList4>	m_commandList4;													//NOTE : (옵션) 레이 트레이싱
	ComPtr<ID3D12GraphicsCommandList6>	m_commandList6;													//NOTE : (옵션) 메시 셰이더 생성
	
	ComPtr<IDXGISwapChain3>				m_screenSwapChain;												//NOTE : (기본) 백버퍼 인덱스 추적
	ComPtr<ID3D12Resource>				m_screenBackBuffers[m_screenBackBufferCount];
	UINT								m_screenBackBufferIndex								= 0;
	UINT								m_screenBackBufferWidth								= 0;
	UINT								m_screenBackBufferHeight							= 0;
	float								m_screenBackBufferAspectRatio						= 0.0f;
	D3D12_VIEWPORT						m_screenViewPort									= {};
	D3D12_RECT							m_screenScissorRectangle							= {};
	ComPtr<ID3D12Resource>				m_screenDepthStencilBuffer;
	
	UINT								m_descriptorHeapCBVCount							= 0;
	UINT								m_descriptorHeapSRVCount							= 0;
	UINT								m_descriptorHeapUAVCount							= 0;
	UINT								m_descriptorHeapRTVIncrementSize					= 0;
	UINT								m_descriptorHeapDSVIncrementSize					= 0;
	UINT								m_descriptorHeapCBVSRVUAVIncrementSize				= 0;
	ComPtr<ID3D12DescriptorHeap>		m_descriptorHeapRTV;
	ComPtr<ID3D12DescriptorHeap>		m_descriptorHeapDSV;
	ComPtr<ID3D12DescriptorHeap>		m_descriptorHeapCBVSRVUAV;
	CD3DX12_CPU_DESCRIPTOR_HANDLE		m_descriptorHeapRTVCpuStartHandle;
	CD3DX12_CPU_DESCRIPTOR_HANDLE		m_descriptorHeapDSVCpuStartHandle;
	CD3DX12_CPU_DESCRIPTOR_HANDLE		m_descriptorHeapCBVSRVUAVSCpuStartHandleForImGui;
	CD3DX12_GPU_DESCRIPTOR_HANDLE		m_descriptorHeapCBVSRVUAVSGpuStartHandleForImGui;
	CD3DX12_CPU_DESCRIPTOR_HANDLE		m_descriptorHeapCBVSRVUAVSCpuStartHandleForGame;
	CD3DX12_GPU_DESCRIPTOR_HANDLE		m_descriptorHeapCBVSRVUAVSGpuStartHandleForGame;
	
	OptionFullScreen		m_optionFullScreen;
	OptionHDR				m_optionHDR;
	OptionTearing			m_optionTearing;
	OptionGUI				m_optionGUI;
	OptionRayTracing		m_optionRayTracing;
	OptionMeshShader		m_optionMeshShader;
	OptionSound				m_optionSound;

	bool					m_imGuiInitialized					= false;
	ImVec2					m_imGuiSpacingSize					= ImVec2(0.0f, 10.0f);
	ImVec2					m_imGuiSmallButtonSize				= ImVec2(120.0f, 40.0f);
	ImVec2					m_imGuiMediumButtonSize				= ImVec2(240.0f, 40.0f);
	ImVec2					m_imGuiLargeButtonSize				= ImVec2(360.0f, 40.0f);

	void					TimersReset()						{ m_timerTotal.Reset(); m_timerCaption.Reset(); m_timerFrame.Reset(); }
	void					TimersStop()						{ if (IsStopped() == true) { m_timerTotal.Stop(); m_timerCaption.Stop(); m_timerFrame.Stop(); } }
	void					TimersStart()						{ if (IsStopped() == false) { m_timerTotal.Start(); m_timerCaption.Start(); m_timerFrame.Start(); } }
	Timer					m_timerTotal;
	Timer					m_timerCaption;
	Timer					m_timerFrame;
	
	bool					IsStopped()	const					{ return m_isResizing || m_isMoving || m_isInactive; }
	bool					m_isResizing						= false;
	bool					m_isMoving							= false;
	bool					m_isInactive						= false;

	bool					NeedResetDxgiInterface() const		{ return (m_dxgiFactory->IsCurrent() == FALSE) || m_needResetAdapterAndOutput; }
	bool					m_needResetAdapterAndOutput			= false;
	bool					NeedResetScreenSetting() const		{ return m_needResetScreenMode || m_needResetScreenResolution || m_needResetHDR || m_needResetGUI; }
	bool					m_needResetScreenMode				= false;
	bool					m_needResetScreenResolution			= false;
	bool					m_needResetHDR						= false;
	bool					m_needResetGUI						= false;

	LONG					m_previousWindowPosX				= 0; 
	LONG					m_previousWindowPosY				= 0;
	LONG					m_previousWindowWidth				= 1600;
	LONG					m_previousWindowHeight				= 900;

	POINT					m_inputMousePositionClient			= { 0, 0 };
	POINT					m_inputMouseClickedPositionClient	= { 0, 0 };
	bool					m_inputIsClicked					= false;
	int						m_inputScrollDelta					= 0;

	bool					GameNeedSave()						{ return (m_presentGameState == GAME_STATE_IN_GAME) || (m_presentGameState == GAME_STATE_PAUSED_GAME) || ((m_presentGameState == GAME_STATE_OPTION) && (m_previousGameStates.top() == GAME_STATE_PAUSED_GAME)); }
	GameState				m_presentGameState					= GAME_STATE_LOBBY;
	std::stack<GameState>	m_previousGameStates;
};