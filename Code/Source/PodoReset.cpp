#include "Podo.h"
#include "Debug.h"
#include <windows.h>
#include <dxgi.h>
#include <stdexcept>

void Podo::ResetQueuedCommands()
{
	if (m_fenceEvent == nullptr || m_fence == nullptr || m_commandQueue == nullptr)
	{
		return;
	}
	
	m_fenceCurrent++;

	ThrowIfFailed(m_commandQueue->Signal(m_fence.Get(), m_fenceCurrent));

	ThrowIfFailed(m_fence->SetEventOnCompletion(m_fenceCurrent, m_fenceEvent));
	auto waitResult = WaitForSingleObject(m_fenceEvent, INFINITE);

	if (waitResult != WAIT_OBJECT_0)
	{
		throw std::runtime_error("wait fence failed");
	}
}

void Podo::ResetDxgiInterface()
{
	ResetQueuedCommands();

	if (m_dxgiFactory->IsCurrent() == FALSE)
	{
		InitFactory();
	}

	DXGI_ADAPTER_DESC previousAdapterDesc;
	m_dxgiAdapter->GetDesc(&previousAdapterDesc);

	InitAdapterAndOutput();

	DXGI_ADAPTER_DESC newAdapterDesc;
	m_dxgiAdapter->GetDesc(&newAdapterDesc);


	bool adapterIsDifferent	= (previousAdapterDesc.AdapterLuid.HighPart != newAdapterDesc.AdapterLuid.HighPart)
							|| (previousAdapterDesc.AdapterLuid.LowPart != newAdapterDesc.AdapterLuid.LowPart);

	if (adapterIsDifferent == true)
	{
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
		InitTimers();
	}

	m_needResetAdapterAndOutput = false;
}

void Podo::ResetScreenSetting()
{
	if (m_needResetScreenMode == true)
	{
		if (m_optionFullScreen.userEnabled == true)
		{
			ResetToFullScreenMode();
		}
		else
		{
			ResetToWindowMode();
		}
	}

	if (m_screenSwapChain != nullptr)
	{
		ResetQueuedCommands();

		for (UINT i = 0; i < m_screenBackBufferCount; i++)
		{
			m_screenBackBuffers[i].Reset();
		}

		ThrowIfFailed(
			m_screenSwapChain->ResizeBuffers(
				0,
				0,
				0,
				m_optionHDR.IsActive() ? m_screenBackBufferFormatHDR : m_screenBackBufferFormatSDR,
				DXGI_SWAP_CHAIN_FLAG_FRAME_LATENCY_WAITABLE_OBJECT
				| (m_optionTearing.featureSupported ? DXGI_SWAP_CHAIN_FLAG_ALLOW_TEARING : 0)
			)
		);

		if (m_optionHDR.IsActive() == true)
		{
			m_screenSwapChain->SetColorSpace1(m_screenBackBufferColorSpaceHDR);
		}
		else
		{
			m_screenSwapChain->SetColorSpace1(m_screenBackBufferColorSpaceSDR);
		}

		InitBackBuffers();
		InitViewPort();
		InitScissorRectangle();
		InitDepthStencilBuffer();
		InitRTV();
		InitDSV();
		InitImGui();
	}

	m_needResetScreenMode		= false;
	m_needResetScreenResolution	= false;
	m_needResetHDR				= false;
	m_needResetGUI				= false;
}

void Podo::ResetToFullScreenMode()
{
	LONG tempPreviousWindowPosX = 0;
	LONG tempPreviousWindowPosY = 0;
	LONG tempPreviousWindowWidth = 0;
	LONG tempPreviousWindowHeight = 0;
	RECT rectWindow = {};
	BOOL queryResult = GetWindowRect(m_hWnd, &rectWindow);
	if (queryResult != FALSE)
	{
		tempPreviousWindowPosX = rectWindow.left;
		tempPreviousWindowPosY = rectWindow.top;
		tempPreviousWindowWidth = rectWindow.right - rectWindow.left;
		tempPreviousWindowHeight = rectWindow.bottom - rectWindow.top;
	}

	SetWindowLongPtr(m_hWnd, GWL_STYLE, WS_POPUP | WS_VISIBLE);

	HMONITOR monitor = MonitorFromWindow(m_hWnd, MONITOR_DEFAULTTONEAREST);
	MONITORINFO monitorInfo{};
	monitorInfo.cbSize = sizeof(MONITORINFO);
	GetMonitorInfo(monitor, &monitorInfo);

	LONG monitorBaseX = monitorInfo.rcMonitor.left;
	LONG monitorBaseY = monitorInfo.rcMonitor.top;
	LONG monitorWidth = monitorInfo.rcMonitor.right - monitorInfo.rcMonitor.left;
	LONG monitorHeight = monitorInfo.rcMonitor.bottom - monitorInfo.rcMonitor.top;
	
	SetWindowPos(
		m_hWnd,
		HWND_TOP,
		monitorBaseX,
		monitorBaseY,
		monitorWidth,
		monitorHeight,
		SWP_NOOWNERZORDER | SWP_FRAMECHANGED
	);

	if (monitorBaseX <= tempPreviousWindowPosX && tempPreviousWindowPosX <= monitorBaseX + monitorWidth)
	{
		if (monitorBaseY <= tempPreviousWindowPosY && tempPreviousWindowPosY <= monitorBaseY + monitorHeight)
		{
			if (30 <= tempPreviousWindowWidth && tempPreviousWindowWidth <= monitorWidth)
			{
				if (30 <= tempPreviousWindowHeight && tempPreviousWindowHeight <= monitorHeight)
				{
					m_previousWindowPosX = tempPreviousWindowPosX;
					m_previousWindowPosY = tempPreviousWindowPosY;
					m_previousWindowWidth = tempPreviousWindowWidth;
					m_previousWindowHeight = tempPreviousWindowHeight;
				}
			}
		}
	}
}

void Podo::ResetToWindowMode()
{
	SetWindowLongPtr(m_hWnd, GWL_STYLE, WS_OVERLAPPEDWINDOW | WS_VISIBLE);

	HMONITOR monitor = MonitorFromWindow(m_hWnd, MONITOR_DEFAULTTONEAREST);
	MONITORINFO monitorInfo{};
	monitorInfo.cbSize = sizeof(MONITORINFO);
	GetMonitorInfo(monitor, &monitorInfo);

	LONG monitorBaseX = monitorInfo.rcMonitor.left;
	LONG monitorBaseY = monitorInfo.rcMonitor.top;
	LONG monitorWidth = monitorInfo.rcMonitor.right - monitorInfo.rcMonitor.left;
	LONG monitorHeight = monitorInfo.rcMonitor.bottom - monitorInfo.rcMonitor.top;

	SetWindowPos(
		m_hWnd,
		HWND_TOP,
		(monitorBaseX <= m_previousWindowPosX) && (m_previousWindowPosX <= monitorBaseX + monitorWidth) ? m_previousWindowPosX : monitorBaseX,
		(monitorBaseY <= m_previousWindowPosY) && (m_previousWindowPosY <= monitorBaseY + monitorHeight) ? m_previousWindowPosY : monitorBaseY,
		(m_previousWindowWidth <= monitorWidth) ? m_previousWindowWidth : monitorWidth,
		(m_previousWindowHeight <= monitorHeight) ? m_previousWindowHeight : monitorHeight,
		SWP_NOOWNERZORDER | SWP_FRAMECHANGED
	);
}