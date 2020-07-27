#include "UniConverter.h"

void UniConverter::ConvUnicodeToMulti(const wchar_t* uni, char* strMulti)
{
	int len = WideCharToMultiByte(CP_ACP, 0, uni, -1, NULL, 0, NULL, NULL);
	WideCharToMultiByte(CP_ACP, 0, uni, -1, strMulti, len, NULL, NULL);
}

void UniConverter::ConvMultiToUnicode(const char* multi, wchar_t* unicode)
{
	int len = MultiByteToWideChar(CP_ACP, 0, multi, strlen(multi), NULL, NULL);
	MultiByteToWideChar(CP_ACP, 0, multi, strlen(multi), unicode, len);
}

void UniConverter::ConvUnicodeToUTF8(const wchar_t* uni, char* multi)
{
	int len = WideCharToMultiByte(CP_UTF8, 0, uni, lstrlenW(uni), NULL, 0, NULL, NULL);
	WideCharToMultiByte(CP_UTF8, 0, uni, lstrlenW(uni), multi, len, NULL, NULL);
}

void UniConverter::ConvUTF8ToUnicode(const char* multi, wchar_t* uni)
{
	int len = MultiByteToWideChar(CP_UTF8, 0, multi, strlen(multi), NULL, NULL);
	MultiByteToWideChar(CP_UTF8, 0, multi, strlen(multi), uni, len);
}