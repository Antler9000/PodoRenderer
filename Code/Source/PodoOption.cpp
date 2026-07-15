#include "Podo.h"
#include <algorithm>
#include <string>
#include <cstdio>
#include <fstream>

void Podo::OptionSave()
{
	std::ofstream fout("SavedSettingsTemp.txt", std::ios::out | std::ios::trunc);

	if (!fout)
	{
		return;
	}

	fout << "FullScreen"		<< " " << (m_optionFullScreen.userEnabled	? "Yes" : "No") << '\n';
	fout << "HDR"				<< " " << (m_optionHDR.userEnabled			? "Yes" : "No") << '\n';
	fout << "Tearing"			<< " " << (m_optionTearing.userEnabled		? "Yes" : "No") << '\n';
	fout << "RayTracing"		<< " " << (m_optionRayTracing.userEnabled	? "Yes" : "No") << '\n';
	fout << "MeshShader"		<< " " << (m_optionMeshShader.userEnabled	? "Yes" : "No") << '\n';
	fout << "GUIMasterSize"		<< " " << m_optionGUI.masterSize		<< '\n';

	fout.close();

	std::remove("SavedSettings.txt");

	int renameResult = std::rename("SavedSettingsTemp.txt", "SavedSettings.txt");
	if (renameResult != 0)
	{
		return;
	}
}

void Podo::OptionRestore()
{
	std::ifstream fin("SavedSettings.txt", std::ios::in);

	if (!fin)
	{
		return;
	}

	bool result = true;

	bool fullScreenEnabledTemp	= false;
	bool hdrEnabledTemp			= false;
	bool tearingEnabledTemp		= false;
	bool rayTracingEnabledTemp	= false;
	bool meshShaderEnabledTemp	= false;
	int guiMasterSizeTemp		= 0;

	result &= OptionReadBool(fin, "FullScreen", fullScreenEnabledTemp);
	result &= OptionReadBool(fin, "HDR", hdrEnabledTemp);
	result &= OptionReadBool(fin, "Tearing", tearingEnabledTemp);
	result &= OptionReadBool(fin, "RayTracing", rayTracingEnabledTemp);
	result &= OptionReadBool(fin, "MeshShader", meshShaderEnabledTemp);
	result &= OptionReadInt(fin, "GUIMasterSize", guiMasterSizeTemp);

	if (result == false)
	{
		return;
	}

	m_optionFullScreen.userEnabled	= fullScreenEnabledTemp;
	m_optionHDR.userEnabled			= hdrEnabledTemp;
	m_optionTearing.userEnabled		= tearingEnabledTemp;
	m_optionRayTracing.userEnabled	= rayTracingEnabledTemp;
	m_optionMeshShader.userEnabled	= meshShaderEnabledTemp;
	m_optionGUI.masterSize			= std::clamp(guiMasterSizeTemp, 50, 150);
}

bool Podo::OptionReadBool(std::ifstream& fin, std::string optionName, bool& outOptionEnabled)
{
	std::string buffer;

	fin >> buffer;
	if (buffer != optionName)
	{
		return false;
	}

	fin >> buffer;
	if (buffer == "Yes")
	{
		outOptionEnabled = true;
	}
	else if (buffer == "No")
	{
		outOptionEnabled = false;
	}
	else
	{
		return false;
	}

	return true;
}

bool Podo::OptionReadInt(std::ifstream& fin, std::string optionName, int& outOptionValue)
{
	std::string buffer;

	fin >> buffer;
	if (buffer != optionName)
	{
		return false;
	}
	fin >> outOptionValue;

	return true;
}