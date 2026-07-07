#include <windows.h>
#include <dxgi1_6.h>
#include <dxgi1_4.h>
#include <dxgi.h>
#include <wrl/client.h>
#include "Sodo.h"

bool Sodo::FindMostIntersectingOutput(IDXGIAdapter3* adapter)
{
	m_dxgiOutput.Reset();
	m_dxgiOutput6.Reset();

	ComPtr<IDXGIOutput> tempOutput = nullptr;
	m_optionHDR.outputSupported = false;

	HMONITOR targetMonitor = MonitorFromWindow(m_hWnd, MONITOR_DEFAULTTONEAREST);

	HRESULT result = S_OK;
	for (UINT i = 0; result != DXGI_ERROR_NOT_FOUND; i++)
	{
		result = adapter->EnumOutputs(i, tempOutput.ReleaseAndGetAddressOf());

		if (SUCCEEDED(result) == true)
		{
			DXGI_OUTPUT_DESC tempOutputDesc;
			tempOutput->GetDesc(&tempOutputDesc);

			if (tempOutputDesc.Monitor == targetMonitor)
			{
				m_dxgiOutput = tempOutput;

				m_optionHDR.outputSupported = SUCCEEDED(m_dxgiOutput.As(&m_dxgiOutput6));

				if (m_optionHDR.outputSupported == true)
				{
					m_dxgiOutput6->GetDesc1(&m_dxgiOutputDesc);
				}

				return true;
			}
		}
	}

	return false;
}

void Sodo::CheckAndExit()
{
	if (m_gameNeedAlive == true)
	{
		return;
	}
	if (m_gameNeedSave == true)
	{
		if (m_gameState == GAME_STATE_LOBBY || m_gameState == GAME_STATE_OPTION_FROM_LOBBY)
		{
			m_gameState = GAME_STATE_EXIT_FROM_LOBBY_TO_WINDOWS;
		}
		else if (m_gameState == GAME_STATE_IN_GAME || m_gameState == GAME_STATE_PAUSED || m_gameState == GAME_STATE_OPTION_FROM_PAUSED || m_gameState == GAME_STATE_EXIT_FROM_PAUSED_TO_LOBBY)
		{
			m_gameState = GAME_STATE_EXIT_FROM_PAUSED_TO_WINDOWS;
		}
	}
	else
	{
		DestroyWindow(m_hWnd);
	}
}