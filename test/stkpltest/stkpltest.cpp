﻿#include "../../src/stkpl/StkPl.h"


void Test_Conv_Utf16_Utf32(const char16_t* MsgPtr, int NumOfByte)
{
	char32_t Utf32[256] = U"";
	char16_t Utf16[256] = u"";
	size_t LenUtf32 = StkPlConvUtf16ToUtf32(Utf32, 256, MsgPtr);
	size_t LenUtf16 = StkPlConvUtf32ToUtf16(Utf16, 256, Utf32);
	if (LenUtf16 != LenUtf32 * NumOfByte || StkPlMemCmp(MsgPtr, Utf16, LenUtf16 * sizeof(char16_t)) != 0) {
		StkPlPrintf("UTF16(%d word) -> UTF32 -> UTF16(%d word) ... NG case\n", NumOfByte, NumOfByte);
		StkPlExit(-1);
	}
	StkPlPrintf("UTF16(%d word) -> UTF32 -> UTF16(%d word) ... OK case\n", NumOfByte, NumOfByte);
}

void Test_Conv_Utf8_Utf32(const char32_t* MsgPtr, int NumOfByte)
{
	char Utf8[256] = "";
	char32_t Utf32[256] = U"";
	size_t LenUtf8 = StkPlConvUtf32ToUtf8(Utf8, 256, MsgPtr);
	size_t LenUtf32 = StkPlConvUtf8ToUtf32(Utf32, 256, Utf8);
	if (LenUtf8 != LenUtf32 * NumOfByte || StkPlMemCmp(MsgPtr, Utf32, LenUtf32 * sizeof(char32_t)) != 0) {
		StkPlPrintf("UTF32 -> UTF8(%d byte) -> UTF32 ... NG case\n", NumOfByte);
		StkPlExit(-1);
	}
	StkPlPrintf("UTF32 -> UTF8(%d byte) -> UTF32 ... OK case\n", NumOfByte);
}

void Test_Conv_Utf8_Utf16(const char16_t* MsgPtr, int NumOfByte)
{
	char Utf8[256] = "";
	char16_t Utf16[256] = u"";
	size_t LenUtf8 = StkPlConvUtf16ToUtf8(Utf8, 256, MsgPtr);
	size_t LenUtf16 = StkPlConvUtf8ToUtf16(Utf16, 256, Utf8);
	if (LenUtf8 != LenUtf16 * NumOfByte || StkPlMemCmp(MsgPtr, Utf16, LenUtf16 * sizeof(char16_t)) != 0) {
		StkPlPrintf("UTF16 -> UTF8(%d byte) -> UTF16 ... NG case\n", NumOfByte);
		StkPlExit(-1);
	}
	StkPlPrintf("UTF16 -> UTF8(%d byte) -> UTF16 ... OK case\n", NumOfByte);
}

size_t Test_Insufficient_Buffer_Utf16_Utf32(const char16_t* MsgPtr, size_t Size)
{
	StkPlPrintf("UTF16 -> UTF32 with insufficient buffer ... ");
	char32_t Utf32[256] = U"";
	char32_t Utf32f[256] = U"";
	size_t LenUtf32 = StkPlConvUtf16ToUtf32(Utf32, Size, MsgPtr);
	size_t LenUtf32f = StkPlConvUtf16ToUtf32(Utf32f, 256, MsgPtr);
	if (LenUtf32 > Size - 1 || LenUtf32 >= LenUtf32f || StkPlMemCmp(Utf32, Utf32f, LenUtf32 * sizeof(char32_t)) != 0) {
		StkPlPrintf("NG case\n");
		StkPlExit(-1);
	}
	StkPlPrintf("OK case\n");
	return LenUtf32;
}

size_t Test_Insufficient_Buffer_Utf32_Utf16(const char32_t* MsgPtr, size_t Size)
{
	StkPlPrintf("UTF32 -> UTF16 with insufficient buffer ... ");
	char16_t Utf16[256] = u"";
	char16_t Utf16f[256] = u"";
	size_t LenUtf16 = StkPlConvUtf32ToUtf16(Utf16, Size, MsgPtr);
	size_t LenUtf16f = StkPlConvUtf32ToUtf16(Utf16f, 256, MsgPtr);
	if (LenUtf16 > Size - 1 || LenUtf16 >= LenUtf16f || StkPlMemCmp(Utf16, Utf16f, LenUtf16 * sizeof(char16_t)) != 0) {
		StkPlPrintf("NG case\n");
		StkPlExit(-1);
	}
	StkPlPrintf("OK case\n");
	return LenUtf16;
}

size_t Test_Insufficient_Buffer_Utf8_Utf32(const char* MsgPtr, size_t Size)
{
	StkPlPrintf("UTF8 -> UTF32 with insufficient buffer ... ");
	char32_t Utf32[256] = U"";
	char32_t Utf32f[256] = U"";
	size_t LenUtf32 = StkPlConvUtf8ToUtf32(Utf32, Size, MsgPtr);
	size_t LenUtf32f = StkPlConvUtf8ToUtf32(Utf32f, 256, MsgPtr);
	if (LenUtf32 > Size - 1 || LenUtf32 >= LenUtf32f || StkPlMemCmp(Utf32, Utf32f, LenUtf32 * sizeof(char32_t)) != 0) {
		StkPlPrintf("NG case\n");
		StkPlExit(-1);
	}
	StkPlPrintf("OK case\n");
	return LenUtf32;
}

size_t Test_Insufficient_Buffer_Utf32_Utf8(const char32_t* MsgPtr, size_t Size)
{
	StkPlPrintf("UTF32 -> UTF8 with insufficient buffer ... ");
	char Utf8[256] = "";
	char Utf8f[256] = "";
	size_t LenUtf8 = StkPlConvUtf32ToUtf8(Utf8, Size, MsgPtr);
	size_t LenUtf8f = StkPlConvUtf32ToUtf8(Utf8f, 256, MsgPtr);
	if (LenUtf8 > Size - 1 || LenUtf8 >= LenUtf8f || StkPlMemCmp(Utf8, Utf8f, LenUtf8) != 0) {
		StkPlPrintf("NG case\n");
		StkPlExit(-1);
	}
	StkPlPrintf("OK case\n");
	return LenUtf8;
}

size_t Test_Insufficient_Buffer_Utf8_Utf16(const char* MsgPtr, size_t Size)
{
	StkPlPrintf("UTF8 -> UTF16 with insufficient buffer ... ");
	char16_t Utf16[256] = u"";
	char16_t Utf16f[256] = u"";
	size_t LenUtf16 = StkPlConvUtf8ToUtf16(Utf16, Size, MsgPtr);
	size_t LenUtf16f = StkPlConvUtf8ToUtf16(Utf16f, 256, MsgPtr);
	if (LenUtf16 > Size - 1 || LenUtf16 >= LenUtf16f || StkPlMemCmp(Utf16, Utf16f, LenUtf16 * sizeof(char16_t)) != 0) {
		StkPlPrintf("NG case\n");
		StkPlExit(-1);
	}
	StkPlPrintf("OK case\n");
	return LenUtf16;
}

size_t Test_Insufficient_Buffer_Utf16_Utf8(const char16_t* MsgPtr, size_t Size)
{
	StkPlPrintf("UTF16 -> UTF8 with insufficient buffer ... ");
	char Utf8[256] = "";
	char Utf8f[256] = "";
	size_t LenUtf8 = StkPlConvUtf16ToUtf8(Utf8, Size, MsgPtr);
	size_t LenUtf8f = StkPlConvUtf16ToUtf8(Utf8f, 256, MsgPtr);
	if (LenUtf8 > Size - 1 || LenUtf8 >= LenUtf8f || StkPlMemCmp(Utf8, Utf8f, LenUtf8) != 0) {
		StkPlPrintf("NG case\n");
		StkPlExit(-1);
	}
	StkPlPrintf("OK case\n");
	return LenUtf8;
}

void Test_Invalid_String_Utf16_Utf32(const char16_t* MsgPtr, int Count)
{
	StkPlPrintf("Invalid string (UTF16->UTF32) is presented ... ");
	char32_t Buf[256];
	size_t LenUtf32 = StkPlConvUtf16ToUtf32(Buf, 256, MsgPtr);
	if (LenUtf32 != Count) {
		StkPlPrintf("NG case\n");
		StkPlExit(-1);
	}
	StkPlPrintf("OK case\n");
}

void Test_Invalid_String_Utf8_Utf32(const char* MsgPtr, int Count)
{
	StkPlPrintf("Invalid string (UTF8->UTF32) is presented ... ");
	char32_t Buf[256];
	size_t LenUtf32 = StkPlConvUtf8ToUtf32(Buf, 256, MsgPtr);
	if (LenUtf32 != Count) {
		StkPlPrintf("NG case\n");
		StkPlExit(-1);
	}
	StkPlPrintf("OK case\n");
}

void Test_Invalid_String_Utf8_Utf16(const char* MsgPtr, int Count)
{
	StkPlPrintf("Invalid string (UTF8->UTF16) is presented ... ");
	char16_t Buf[256];
	size_t LenUtf16 = StkPlConvUtf8ToUtf16(Buf, 256, MsgPtr);
	if (LenUtf16 != Count) {
		StkPlPrintf("NG case\n");
		StkPlExit(-1);
	}
	StkPlPrintf("OK case\n");
}

void Test_Time()
{
	StkPlPrintf("Test time in RFC 2822 ... ");
	char Time[64];
	wchar_t WTime[64];

	//
	StkPlGetTimeInRfc2822(Time, true);
	if (Time == NULL || StkPlStrStr(Time, ",") == NULL || StkPlStrStr(Time, " ") == NULL || StkPlStrStr(Time, ":") == NULL) {
		StkPlPrintf("NG case\n");
		StkPlExit(-1);
	}
	StkPlGetTimeInRfc2822(Time, false);
	if (Time == NULL || StkPlStrStr(Time, "+0000") == NULL) {
		StkPlPrintf("NG case\n");
		StkPlExit(-1);
	}
	StkPlGetWTimeInRfc2822(WTime, true);
	if (Time == NULL || StkPlWcsStr(WTime, L",") == NULL || StkPlWcsStr(WTime, L" ") == NULL || StkPlWcsStr(WTime, L":") == NULL) {
		StkPlPrintf("NG case\n");
		StkPlExit(-1);
	}
	StkPlPrintf("OK case\n");

	//
	StkPlPrintf("Test time in ISO 8601 ... ");
	StkPlGetTimeInIso8601(Time, true);
	if (Time == NULL || StkPlStrStr(Time, "-") == NULL || StkPlStrStr(Time, "T") == NULL || StkPlStrStr(Time, ":") == NULL) {
		StkPlPrintf("NG case\n");
		StkPlExit(-1);
	}
	StkPlGetTimeInIso8601(Time, false);
	if (Time == NULL || StkPlStrStr(Time, "+00:00") == NULL) {
		StkPlPrintf("NG case\n");
		StkPlExit(-1);
	}
	StkPlGetWTimeInIso8601(WTime, true);
	if (Time == NULL || StkPlWcsStr(WTime, L"-") == NULL || StkPlWcsStr(WTime, L"T") == NULL || StkPlWcsStr(WTime, L":") == NULL) {
		StkPlPrintf("NG case\n");
		StkPlExit(-1);
	}
	StkPlPrintf("OK case\n");

	//
	StkPlPrintf("Test time in old format ... ");
	StkPlGetTimeInOldFormat(Time, true);
	if (Time == NULL || StkPlStrStr(Time, "-") == NULL || StkPlStrStr(Time, " ") == NULL || StkPlStrStr(Time, ":") == NULL) {
		StkPlPrintf("NG case\n");
		StkPlExit(-1);
	}
	StkPlGetTimeInOldFormat(Time, false);
	if (Time == NULL || StkPlStrStr(Time, "-") == NULL || StkPlStrStr(Time, " ") == NULL || StkPlStrStr(Time, ":") == NULL) {
		StkPlPrintf("NG case\n");
		StkPlExit(-1);
	}
	StkPlPrintf("OK case\n");
}

void TestHostName()
{
	StkPlPrintf("Test StkPlCheckHostName ... ");
	if (!StkPlCheckHostName(L"09azAz-.:")) {
		StkPlPrintf("NG case\n");
		StkPlExit(-1);
	}
	if (!StkPlCheckHostName(L"xxx.example.com")) {
		StkPlPrintf("NG case\n");
		StkPlExit(-1);
	}
	if (!StkPlCheckHostName(L"192.168.0.1")) {
		StkPlPrintf("NG case\n");
		StkPlExit(-1);
	}
	if (!StkPlCheckHostName(L"1::2::3::4")) {
		StkPlPrintf("NG case\n");
		StkPlExit(-1);
	}
	if (StkPlCheckHostName(L"あいうえおわをん")) {
		StkPlPrintf("NG case\n");
		StkPlExit(-1);
	}
	if (StkPlCheckHostName(L"*")) {
		StkPlPrintf("NG case\n");
		StkPlExit(-1);
	}
	if (StkPlCheckHostName(L"$")) {
		StkPlPrintf("NG case\n");
		StkPlExit(-1);
	}
	StkPlPrintf("OK case\n");
}

int main(int Argc, char* Argv[])
{
	StkPlPrintf("stkpltest started.\n");
	Test_Time();
	{
		Test_Conv_Utf16_Utf32(u"abcdexyz-0123456789あいうえおかきくけこさしすせそたちつてと", 1);
		Test_Conv_Utf16_Utf32(u"𠮷𠮷𠮷𠮷𠀋𡈽𡌛𡑮𡢽𠮟𡚴𡸴𣗄𣜿", 2);
		Test_Conv_Utf8_Utf32(U" !\"#$z{|}~abcdexyz012789", 1);
		Test_Conv_Utf8_Utf32(U"¡¢£¶»¾ÀÁÂÃÄ߶߷߸߹ߺǖǖǛʥʧΠθωҖ", 2);
		Test_Conv_Utf8_Utf32(U"東西南北春夏秋冬魑魅魍魎焼肉定食老若男女", 3);
		Test_Conv_Utf8_Utf32(U"🀀🀁🀂🀃🀄🀅🀆𠀋𡈽𡌛𡑮𡢽", 4);
		Test_Conv_Utf8_Utf16(u"abcdexyz-0123456789", 1);
		Test_Conv_Utf8_Utf16(u"¡¢£¶»¾ÀÁÂÃÄ߶߷߸߹ߺǖǖǛʥʧΠθωҖ", 2);
		Test_Conv_Utf8_Utf16(u"𠮷𠮷𠮷𠮷𠀋𡈽𡌛𡑮𡢽𠮟𡚴𡸴𣗄𣜿", 2);
		Test_Conv_Utf8_Utf16(u"あいうえおかきくけこさしすせそたちつてと", 3);
	}

	{
		Test_Insufficient_Buffer_Utf16_Utf32(u"あいうえおかきくけこ", 5);
		Test_Insufficient_Buffer_Utf32_Utf16(U"𠀋𡈽𡌛𡑮𡢽𠮟𡚴𡸴𣗄𣜿", 5);
		Test_Insufficient_Buffer_Utf32_Utf16(U"あ𠀋𡈽𡌛𡑮𡢽𠮟𡚴𡸴𣗄𣜿", 5);
		Test_Insufficient_Buffer_Utf32_Utf16(U"魑魅魍魎サザンクロス", 5);
		Test_Insufficient_Buffer_Utf8_Utf32("\xe3\x9b\x90\xe3\x9b\x90\xe3\x9b\x90\xe3\x9b\x90\xe3\x9b\x90\xe3\x9b\x90\xe3\x9b\x90", 5);
		Test_Insufficient_Buffer_Utf32_Utf8(U"君が代は千代に八千代にさざれ石の巌となりて苔のむすまで", 5);
		Test_Insufficient_Buffer_Utf8_Utf16("\xe3\x9b\x90\xe3\x9b\x90\xe3\x9b\x90\xe3\x9b\x90\xe3\x9b\x90\xe3\x9b\x90\xe3\x9b\x90", 5);
		Test_Insufficient_Buffer_Utf16_Utf8(u"君が代は千代に八千代にさざれ石の巌となりて苔のむすまで", 5);
	}

	{
		char16_t Input[32] = u"𠀋𡈽𡌛𡑮𡢽𠮟𡚴𡸴𣗄𣜿";
		Input[5] = u'\0';
		Test_Invalid_String_Utf16_Utf32(Input, 3);

		Test_Invalid_String_Utf8_Utf32("\xe3\x9b\x90\xe3\x9b\x90\xe3\x9b\x00\xe3\x9b\x90\xe3\x9b\x90\xe3\x9b\x90\xe3\x9b\x90", 2);
		Test_Invalid_String_Utf8_Utf32("\xe3\x9b\x90\xe3\x9b\x90\xe3\x9b\x90\xe3\x00\x90\xe3\x9b\x90\xe3\x9b\x90\xe3\x9b\x90", 3);
		Test_Invalid_String_Utf8_Utf32("\xe3\x9b\x90\xe3\x9b\x90\xe3\x9b\x90\xe3\x00\x90\xe3\x9b\x90\xe3\x9b\x90\xe3\x9b\x90", 3);
		Test_Invalid_String_Utf8_Utf32("\xf0\x90\x8c\xb0\xf0\x90\x8c\xb0\xf0\x90\x8c\xb0\xf0\x90\x8c\x00\xf0\x90\x8c\xb0", 3);
		Test_Invalid_String_Utf8_Utf32("\xf0\x90\x8c\xb0\xf0\x90\x8c\xb0\xf0\x90\x8c\xb0\xf0\x90\x00\xb0\xf0\x90\x8c\xb0", 3);
		Test_Invalid_String_Utf8_Utf32("\xf0\x90\x8c\xb0\xf0\x90\x8c\xb0\xf0\x90\x8c\xb0\xf0\x00\x8c\xb0\xf0\x90\x8c\xb0", 3);

		Test_Invalid_String_Utf8_Utf16("\xe3\x9b\x90\xe3\x9b\x90\xe3\x9b\x00\xe3\x9b\x90\xe3\x9b\x90\xe3\x9b\x90\xe3\x9b\x90", 2);
		Test_Invalid_String_Utf8_Utf16("\xe3\x9b\x90\xe3\x9b\x90\xe3\x9b\x90\xe3\x00\x90\xe3\x9b\x90\xe3\x9b\x90\xe3\x9b\x90", 3);
		Test_Invalid_String_Utf8_Utf16("\xe3\x9b\x90\xe3\x9b\x90\xe3\x9b\x90\xe3\x00\x90\xe3\x9b\x90\xe3\x9b\x90\xe3\x9b\x90", 3);
		Test_Invalid_String_Utf8_Utf16("\xf0\x90\x8c\xb0\xf0\x90\x8c\xb0\xf0\x90\x8c\xb0\xf0\x90\x8c\x00\xf0\x90\x8c\xb0", 6);
		Test_Invalid_String_Utf8_Utf16("\xf0\x90\x8c\xb0\xf0\x90\x8c\xb0\xf0\x90\x8c\xb0\xf0\x90\x00\xb0\xf0\x90\x8c\xb0", 6);
		Test_Invalid_String_Utf8_Utf16("\xf0\x90\x8c\xb0\xf0\x90\x8c\xb0\xf0\x90\x8c\xb0\xf0\x00\x8c\xb0\xf0\x90\x8c\xb0", 6);
	}

	StkPlPrintf("Length check with size=0 specification ... ");
	char32_t Utf32[256] = U"";
	char16_t Utf16[256] = u"";
	char Utf8[256] = "";
	size_t Len32f_16 = StkPlConvUtf16ToUtf32(Utf32, 256, u"abcde◆□■敬景桂𩀀𩀁𩀂ЀЁЂ");
	size_t Len32n_16 = StkPlConvUtf16ToUtf32(NULL, 0, u"abcde◆□■敬景桂𩀀𩀁𩀂ЀЁЂ");
	size_t Len16f_32 = StkPlConvUtf32ToUtf16(Utf16, 256, U"abcde◆□■敬景桂𩀀𩀁𩀂ЀЁЂ");
	size_t Len16n_32 = StkPlConvUtf32ToUtf16(NULL, 0, U"abcde◆□■敬景桂𩀀𩀁𩀂ЀЁЂ");
	size_t Len8f_32 = StkPlConvUtf32ToUtf8(Utf8, 256, U"abcde◆□■敬景桂𩀀𩀁𩀂ЀЁЂ");
	size_t Len8n_32 = StkPlConvUtf32ToUtf8(NULL, 0, U"abcde◆□■敬景桂𩀀𩀁𩀂ЀЁЂ");
	size_t Len32f_8 = StkPlConvUtf8ToUtf32(Utf32, 256, Utf8);
	size_t Len32n_8 = StkPlConvUtf8ToUtf32(NULL, 0, Utf8);
	size_t Len8f_16 = StkPlConvUtf16ToUtf8(Utf8, 256, u"abcde◆□■敬景桂𩀀𩀁𩀂ЀЁЂ");
	size_t Len8n_16 = StkPlConvUtf16ToUtf8(NULL, 0, u"abcde◆□■敬景桂𩀀𩀁𩀂ЀЁЂ");
	size_t Len16f_8 = StkPlConvUtf8ToUtf16(Utf16, 256, Utf8);
	size_t Len16n_8 = StkPlConvUtf8ToUtf16(NULL, 0, Utf8);
	if (Len32f_16 != Len32n_16 || Len16f_32 != Len16n_32 || Len32f_8 != Len32n_8 || Len8f_32 != Len8n_32 || Len8f_16 != Len8n_16 || Len16f_8 != Len16n_8) {
		StkPlPrintf("NG case\n");
		StkPlExit(-1);
	}
	StkPlPrintf("OK case\n");

	{
		StkPlPrintf("Create UTF16 string ... ");
		char* Utf8a = StkPlCreateUtf8FromUtf16(u"abcdeあいうえお");
		char* Utf8b = StkPlCreateUtf8FromUtf32(U"abcdeあいうえお");
		if (StkPlMemCmp(Utf8a, Utf8b, 15) != 0) {
			StkPlPrintf("NG case\n");
			StkPlExit(-1);
		}
		delete Utf8a;
		delete Utf8b;
		StkPlPrintf("OK case\n");

		StkPlPrintf("Create UTF32 & UTF16 string ... ");
		char32_t* Utf32a = StkPlCreateUtf32FromUtf16(u"abcdeあいうえお，a２３４");
		char16_t* Utf16a = StkPlCreateUtf16FromUtf32(U"abcdeあいうえお，a２３４");
		if (StkPlMemCmp(Utf32a, U"abcdeあいうえお，a２３４", 60) != 0 || StkPlMemCmp(Utf16a, u"abcdeあいうえお，a２３４", 30) != 0) {
			StkPlPrintf("NG case\n");
			StkPlExit(-1);
		}
		delete Utf32a;
		delete Utf16a;
		StkPlPrintf("OK case\n");

		StkPlPrintf("Create from UTF8 string ... ");
		char32_t* Utf32b = StkPlCreateUtf32FromUtf8("\x0e3\x09b\x090\x0e3\x09b\x090\x0e3\x09b\x090\x0e3\x09b\x090\x0e3\x09b\x090\x0e3\x09b\x090\x0e3\x09b\x090 abcde");
		char16_t* Utf16b = StkPlCreateUtf16FromUtf8("\x0e3\x09b\x090\x0e3\x09b\x090\x0e3\x09b\x090\x0e3\x09b\x090\x0e3\x09b\x090\x0e3\x09b\x090\x0e3\x09b\x090 abcde");
		if (StkPlMemCmp(Utf32b, U"㛐㛐㛐㛐㛐㛐㛐 abcde", 10) != 0 || StkPlMemCmp(Utf16b, u"㛐㛐㛐㛐㛐㛐㛐 abcde", 15) != 0) {
			StkPlPrintf("NG case\n");
			StkPlExit(-1);
		}
		delete Utf32b;
		delete Utf16b;
		StkPlPrintf("OK case\n");
	}

	{
		StkPlPrintf("Wide char conversion ... ");
		wchar_t* Str1 = StkPlCreateWideCharFromUtf16(u"abcdeあいうえお㛐㛐魑魅魍魎 0123456789 １２３４５６７８９０，a　￥ 𠮷野家㛐㛐わをんxyz!!!");
		char32_t* Str2 = StkPlCreateUtf32FromWideChar(Str1);
		wchar_t* Str3 = StkPlCreateWideCharFromUtf32(Str2);
		char* Str4 = StkPlCreateUtf8FromWideChar(Str3);
		wchar_t* Str5 = StkPlCreateWideCharFromUtf8(Str4);
		char16_t* Str6 = StkPlCreateUtf16FromWideChar(Str5);
		wchar_t* Str7 = StkPlCreateWideCharFromUtf16(Str6);
		if (StkPlWcsCmp(Str7, Str1) != 0) {
			StkPlPrintf("NG case\n");
			StkPlExit(-1);
		}
		wchar_t StrA[128];
		wchar_t StrB[128];
		wchar_t StrC[128];
		char Utf8[128];
		char16_t Utf16[128];
		char32_t Utf32[128];
		StkPlConvUtf8ToWideChar(StrA, 128, Str4);
		StkPlConvUtf16ToWideChar(StrB, 128, Str6);
		StkPlConvUtf32ToWideChar(StrC, 128, Str2);
		StkPlConvWideCharToUtf8(Utf8, 128, Str1);
		StkPlConvWideCharToUtf16(Utf16, 128, Str3);
		StkPlConvWideCharToUtf32(Utf32, 128, Str5);
		if (StkPlWcsCmp(StrA, Str1) != 0 || StkPlWcsCmp(StrB, Str3) != 0 || StkPlWcsCmp(StrC, Str5) != 0 ||
			StkPlMemCmp(Utf8, Str4, 30) != 0 || StkPlMemCmp(Utf16, Str6, 30) != 0 || StkPlMemCmp(Utf32, Str2, 30) != 0) {
			StkPlPrintf("NG case\n");
			StkPlExit(-1);
		}


		StkPlPrintf("OK case\n");
		delete Str1;
		delete Str2;
		delete Str3;
		delete Str4;
		delete Str5;
		delete Str6;
		delete Str7;
	}

	TestHostName();

	StkPlPrintf("stkpltest completed.\n\n\n");
	return 0;
}
