#pragma once
#include "../framework.h"
#include "Singleton.h"
class UniConverter : public Singleton<UniConverter> {
public:
	void ConvUnicodeToMulti(const wchar_t* uni, char* strMulti);
	void ConvMultiToUnicode(const char* multi, wchar_t* unicode);
	void ConvUnicodeToUTF8(const wchar_t* uni, char* multi);
	void ConvUTF8ToUnicode(const char* multi, wchar_t* uni);
};