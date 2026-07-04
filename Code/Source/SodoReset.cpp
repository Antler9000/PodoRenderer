#include <windows.h>
#include <dxgi.h>
#include <stdexcept>
#include "Sodo.h"
#include "Debug.h"

void Sodo::ResetQueuedCommands()
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

void Sodo::ResetDxgiInterfaces()
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
		InitTimer();
	}

	m_needResetAdapterAndOutput = false;
}

void Sodo::ResetScreenSettings()
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

		for (int i = 0; i < m_screenBackBufferCount; i++)
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

	m_needResetScreenResolution = false;
	m_needResetScreenMode = false;
	m_needResetHDR = false;
}

void Sodo::ResetToFullScreenMode()
{
	SetWindowLongPtr(m_hWnd, GWL_STYLE, WS_POPUP | WS_VISIBLE);

	HMONITOR monitor = MonitorFromWindow(m_hWnd, MONITOR_DEFAULTTONEAREST);
	MONITORINFO monitorInfo{};
	monitorInfo.cbSize = sizeof(MONITORINFO);
	GetMonitorInfo(monitor, &monitorInfo);

	LONG monitorXBase = monitorInfo.rcMonitor.left;
	LONG monitorYBase = monitorInfo.rcMonitor.top;
	LONG monitorWidth = monitorInfo.rcMonitor.right - monitorInfo.rcMonitor.left;
	LONG monitorHeight = monitorInfo.rcMonitor.bottom - monitorInfo.rcMonitor.top;

	SetWindowPos(
		m_hWnd,
		HWND_TOP,
		monitorXBase,
		monitorYBase,
		monitorWidth,
		monitorHeight,
		SWP_NOOWNERZORDER | SWP_FRAMECHANGED
	);
}

void Sodo::ResetToWindowMode()
{
	SetWindowLongPtr(m_hWnd, GWL_STYLE, WS_OVERLAPPEDWINDOW | WS_VISIBLE);

	HMONITOR monitor = MonitorFromWindow(m_hWnd, MONITOR_DEFAULTTONEAREST);
	MONITORINFO monitorInfo{};
	monitorInfo.cbSize = sizeof(MONITORINFO);
	GetMonitorInfo(monitor, &monitorInfo);

	LONG monitorXBase = monitorInfo.rcMonitor.left;
	LONG monitorYBase = monitorInfo.rcMonitor.top;
	LONG monitorWidth = monitorInfo.rcMonitor.right - monitorInfo.rcMonitor.left;
	LONG monitorHeight = monitorInfo.rcMonitor.bottom - monitorInfo.rcMonitor.top;

	LONG windowWidth = monitorWidth * 2 / 3;
	LONG windowHeight = monitorHeight * 2 / 3;
	LONG windowXBase = monitorXBase + (monitorWidth / 2) - (windowWidth / 2);
	LONG windowYBase = monitorYBase + (monitorHeight / 2) - (windowHeight / 2);

	SetWindowPos(
		m_hWnd,
		HWND_TOP,
		windowXBase,
		windowYBase,
		windowWidth,
		windowHeight,
		SWP_NOOWNERZORDER | SWP_FRAMECHANGED
	);
}