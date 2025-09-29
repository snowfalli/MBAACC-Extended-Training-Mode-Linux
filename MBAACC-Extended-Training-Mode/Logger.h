#pragma once
#include <string>
#include <vector>
#include <filesystem>
#include <chrono>
#include <format>
#include <fstream>

#include "..\Common\Common.h"

static std::string m_sLogFile;
static std::ofstream m_fLogFile;
static std::wofstream wm_fLogFile;
static bool bLogOpen = false;

static void LogInfo(std::string sInfo);

static std::string Time()
{
	return std::format("{:%m-%d-%y_%OH-%OM-%OS}", std::chrono::zoned_time{ std::chrono::current_zone(), std::chrono::system_clock::now() });
}

static void ResetLog() {
	if(m_fLogFile.is_open()) {
		m_fLogFile.clear();
	}
}



static void InitializeLogger(bool dll)
{
	if (bLogOpen)
		return;


	std::string sTempPath = std::filesystem::temp_directory_path().string();
	std::string sTime = Time();

	m_sLogFile = sTempPath + "ExtendedTrainingMode";
	m_sLogFile += (dll) ? "-dll" : "";
	m_sLogFile += ".log";

	wm_fLogFile.open(m_sLogFile);
	m_fLogFile.open(m_sLogFile);

	ResetLog();
	
	LogInfo(VERSION);

	bLogOpen = true;
}

static void CloseLogger()
{
	if (!bLogOpen) return;

	LogInfo("Closed Extended Training Mode");

	m_fLogFile.close();
	bLogOpen = false;
}

static void LogInfo(std::string sInfo)
{
	if (!bLogOpen) return;

	m_fLogFile << "\n";
	m_fLogFile << "*** INFO *** Time: " << Time() << "\n";
	m_fLogFile << "\n";
	m_fLogFile << "\t" << sInfo << "\n";
	m_fLogFile << "\n";

	m_fLogFile.flush();
}

static void LogInfo(std::wstring sInfo)
{
	if (!bLogOpen) return;

	wm_fLogFile << L"\n";
	wm_fLogFile << L"*** INFO *** Time: " << "" << L"\n";
	wm_fLogFile << L"\n";
	wm_fLogFile << L"\t" << sInfo << L"\n";
	wm_fLogFile << L"\n";

	wm_fLogFile.flush();
}

static void LogError(std::string sError)
{
	if (!bLogOpen) return;

	m_fLogFile << "\n";
	m_fLogFile << "*** ERROR ***";
	m_fLogFile << "\tTime: " << Time() << "\n";
	m_fLogFile << "\n";
	m_fLogFile << "\t" << sError << "\n";
	m_fLogFile << "\n";

	m_fLogFile.flush();
}
