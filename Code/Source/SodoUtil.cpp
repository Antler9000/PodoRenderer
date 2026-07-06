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