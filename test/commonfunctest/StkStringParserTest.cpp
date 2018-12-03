#include <windows.h>
#include <stdio.h>
#include "..\..\src\commonfunc\StkStringParser.h"

int StkStringParserTest()
{
	printf("StkStringParserTest started\r\n");

	{
		printf("[StkStringParser] normal: two params ...");
		wchar_t Target[100] = L"abcdefg012345+-*/xyz6789";
		wchar_t Format[100] = L"abcdefg#+-*/#6789";
		wchar_t OutStr1[256];
		wchar_t OutStr2[256];
		wchar_t OutStr3[256];
		wchar_t OutStr4[256];
		StkStringParser::ParseInto4Params(Target, Format, L'#', OutStr1, OutStr2, OutStr3, OutStr4);
		if (lstrcmp(OutStr1, L"012345") != 0 || lstrcmp(OutStr2, L"xyz") != 0) {
			printf("NG\r\n");
			exit(0);
		}
		printf("OK\r\n");
	}
	{
		printf("[StkStringParser] normal: two params with length ...");
		wchar_t Target[100] = L"abcdefg012345+-*/xyz6789";
		wchar_t Format[100] = L"abcdefg#+-*/#6789";
		wchar_t OutStr1[256];
		wchar_t OutStr2[256];
		StkStringParser::ParseInto2Params(Target, Format, L'#', OutStr1, 4, OutStr2, 4);
		if (lstrcmp(OutStr1, L"012") != 0 || lstrcmp(OutStr2, L"xyz") != 0) {
			printf("NG\r\n");
			exit(0);
		}
		printf("OK\r\n");
	}
	{
		printf("[StkStringParser] normal: four params ...");
		wchar_t Target[100] = L"abcdefg012345+-*/xyz6789QWERTYUIO@@@****!!!!";
		wchar_t Format[100] = L"abcdefg#+-*/#6789#@@@#!!!!";
		wchar_t OutStr1[256];
		wchar_t OutStr2[256];
		wchar_t OutStr3[256];
		wchar_t OutStr4[256];
		int Ret = StkStringParser::ParseInto4Params(Target, Format, L'#', OutStr1, OutStr2, OutStr3, OutStr4);
		if (lstrcmp(OutStr1, L"012345") != 0 ||
			lstrcmp(OutStr2, L"xyz") != 0 ||
			lstrcmp(OutStr3, L"QWERTYUIO") != 0 ||
			lstrcmp(OutStr4, L"****") != 0 ||
			Ret != 1) {
			printf("NG\r\n");
			exit(0);
		}
		printf("OK\r\n");
	}
	{
		printf("[StkStringParser] normal: three params with length ...");
		wchar_t Target[100] = L"あいうえお東西南北魑魅魍魎老若男女松竹梅アイウエオ";
		wchar_t Format[100] = L"あいうえお$魑魅魍魎$松竹梅$";
		wchar_t OutStr1[256];
		wchar_t OutStr2[256];
		wchar_t OutStr3[256];
		int Ret = StkStringParser::ParseInto3Params(Target, Format, L'$', OutStr1, 10, OutStr2, 4, OutStr3, 3);
		if (lstrcmp(OutStr1, L"東西南北") != 0 ||
			lstrcmp(OutStr2, L"老若男") != 0 ||
			lstrcmp(OutStr3, L"アイ") != 0 ||
			Ret != 1) {
			printf("NG\r\n");
			exit(0);
		}
		printf("OK\r\n");
	}
	{
		printf("[StkStringParser] normal: four params with length ...");
		wchar_t Target[100] = L"abcdefg012345+-*/xyz6789QWERTYUIO@@@****!!!!";
		wchar_t Format[100] = L"abcdefg#+-*/#6789#@@@#!!!!";
		wchar_t OutStr1[256];
		wchar_t OutStr2[256];
		wchar_t OutStr3[256];
		wchar_t OutStr4[256];
		int Ret = StkStringParser::ParseInto4Params(Target, Format, L'#', OutStr1, 5, OutStr2, 2, OutStr3, 4, OutStr4, 3);
		if (lstrcmp(OutStr1, L"0123") != 0 ||
			lstrcmp(OutStr2, L"x") != 0 ||
			lstrcmp(OutStr3, L"QWE") != 0 ||
			lstrcmp(OutStr4, L"**") != 0 ||
			Ret != 1) {
			printf("NG\r\n");
			exit(0);
		}
		printf("OK\r\n");
	}
	{
		printf("[StkStringParser] normal: Appear the target in the 1st and last char ...");
		wchar_t Target[100] = L"abcdefg012345+-*/xyz6789QWERTYUIO@@@****!!!!";
		wchar_t Format[100] = L"%012345+-*/%6789QWERTYUIO@@@****%";
		wchar_t OutStr1[256];
		wchar_t OutStr2[256];
		wchar_t OutStr3[256];
		wchar_t OutStr4[256];
		StkStringParser::ParseInto4Params(Target, Format, L'%', OutStr1, OutStr2, OutStr3, OutStr4);
		if (lstrcmp(OutStr1, L"abcdefg") != 0 || lstrcmp(OutStr2, L"xyz") != 0 || lstrcmp(OutStr3, L"!!!!") != 0) {
			printf("NG\r\n");
			exit(0);
		}
		printf("OK\r\n");
	}
	{
		printf("[StkStringParser] normal: Appear the target in the 1st character ...");
		wchar_t Target[100] = L"abcdefg012345+-*/xyz6789QWERTYUIO@@@****!!!!";
		wchar_t Format[100] = L"#012345+-*/xyz6789QWERTYUIO@@@****!!!!";
		wchar_t OutStr1[256];
		StkStringParser::ParseInto1Param(Target, Format, L'#', OutStr1);
		if (lstrcmp(OutStr1, L"abcdefg") != 0) {
			printf("NG\r\n");
			exit(0);
		}
		printf("OK\r\n");
	}
	{
		printf("[StkStringParser] normal: Appear the target in the last character ...");
		wchar_t Target[100] = L"abcdefg012345+-*/xyz6789QWERTYUIO@@@****!!!!";
		wchar_t Format[100] = L"abcdefg012345+-*/xyz6789QWERTYUIO@@@****#";
		wchar_t OutStr1[256];
		StkStringParser::ParseInto1Param(Target, Format, L'#', OutStr1);
		if (lstrcmp(OutStr1, L"!!!!") != 0) {
			printf("NG\r\n");
			exit(0);
		}
		printf("OK\r\n");
	}
	{
		printf("[StkStringParser] normal: Specify trimed string ...");
		wchar_t Target[100] = L"abcdefg012345+-*/xyz6789QWERTYUIO@@@****!!!!";
		wchar_t Format[100] = L"efg0123&ERTYUIO@@@**";
		wchar_t OutStr1[256];
		wchar_t OutStr2[256];
		wchar_t OutStr3[256];
		wchar_t OutStr4[256];
		int Ret = StkStringParser::ParseInto4Params(Target, Format, L'&', OutStr1, OutStr2, OutStr3, OutStr4);
		if (lstrcmp(OutStr1, L"") != 0 || lstrcmp(OutStr2, L"") != 0 || Ret != 0) {
			printf("NG\r\n");
			exit(0);
		}
		printf("OK\r\n");
	}
	{
		printf("[StkStringParser] normal: Four 1byte chars fetching ...");
		wchar_t Target[100] = L"abcdefg012345+-*/xyz6789QWERTYUIO@@@****!!!!";
		wchar_t Format[100] = L"#bcdefg#12345+-*/xyz6789QWERTYUIO@@@#***!!!#";
		wchar_t OutStr1[256];
		wchar_t OutStr2[256];
		wchar_t OutStr3[256];
		wchar_t OutStr4[256];
		StkStringParser::ParseInto4Params(Target, Format, L'#', OutStr1, OutStr2, OutStr3, OutStr4);
		if (lstrcmp(OutStr1, L"a") != 0 || lstrcmp(OutStr2, L"0") != 0 ||
			lstrcmp(OutStr3, L"*") != 0 || lstrcmp(OutStr4, L"!") != 0) {
			printf("NG\r\n");
			exit(0);
		}
		printf("OK\r\n");
	}
	{
		printf("[StkStringParser] normal: Short string (1) ...");
		wchar_t Target[100] = L"ab";
		wchar_t Format[100] = L"#b";
		wchar_t OutStr1[256];
		StkStringParser::ParseInto4Params(Target, Format, L'#', OutStr1, NULL, NULL, NULL);
		if (lstrcmp(OutStr1, L"a") != 0) {
			printf("NG\r\n");
			exit(0);
		}
		printf("OK\r\n");
	}
	{
		printf("[StkStringParser] normal: Short string (2) ...");
		wchar_t Target[100] = L"ab";
		wchar_t Format[100] = L"a#";
		wchar_t OutStr1[256];
		StkStringParser::ParseInto4Params(Target, Format, L'#', OutStr1, NULL, NULL, NULL);
		if (lstrcmp(OutStr1, L"b") != 0) {
			printf("NG\r\n");
			exit(0);
		}
		printf("OK\r\n");
	}
	{
		printf("[StkStringParser] normal: Short string (3) ...");
		wchar_t Target[100] = L"a";
		wchar_t Format[100] = L"#";
		wchar_t OutStr1[256];
		int Ret = StkStringParser::ParseInto4Params(Target, Format, L'#', OutStr1, NULL, NULL, NULL);
		if (lstrcmp(OutStr1, L"a") != 0 || Ret != 1) {
			printf("NG\r\n");
			exit(0);
		}
		printf("OK\r\n");
	}
	{
		printf("[StkStringParser] normal: Short string (4) ...");
		wchar_t Target[100] = L"abcdefg";
		wchar_t Format[100] = L"#b#d#f#";
		wchar_t OutStr1[256];
		wchar_t OutStr2[256];
		wchar_t OutStr3[256];
		wchar_t OutStr4[256];
		int Ret = StkStringParser::ParseInto4Params(Target, Format, L'#', OutStr1, OutStr2, OutStr3, OutStr4);
		if (lstrcmp(OutStr1, L"a") != 0 || lstrcmp(OutStr2, L"c") != 0 || lstrcmp(OutStr3, L"e") != 0 || lstrcmp(OutStr4, L"g") != 0 || Ret != 1) {
			printf("NG\r\n");
			exit(0);
		}
		printf("OK\r\n");
	}
	{
		printf("[StkStringParser] normal: Recursive string ...");
		wchar_t Target[100] = L"abcd1234xyzabcd1234xyz";
		wchar_t Format[100] = L"abcd1234xyz#12#xyz";
		wchar_t OutStr1[256];
		wchar_t OutStr2[256];
		int Ret = StkStringParser::ParseInto2Params(Target, Format, L'#', OutStr1, OutStr2);
		if (lstrcmp(OutStr1, L"abcd") != 0 || lstrcmp(OutStr2, L"34") != 0 || Ret != 1) {
			printf("NG\r\n");
			exit(0);
		}
		printf("OK\r\n");
	}
	{
		printf("[StkStringParser] normal: All Fetch ...");
		wchar_t Target[100] = L"abcdefg012345+-*/xyz6789QWERTYUIO@@@****!!!!";
		wchar_t Format[100] = L"#";
		wchar_t OutStr1[256];
		int Ret = StkStringParser::ParseInto4Params(Target, Format, L'#', OutStr1, NULL, NULL, NULL);
		if (lstrcmp(OutStr1, L"abcdefg012345+-*/xyz6789QWERTYUIO@@@****!!!!") != 0 || Ret != 1) {
			printf("NG\r\n");
			exit(0);
		}
		printf("OK\r\n");
	}
	{
		printf("[StkStringParser] normal: For multi bytes characters ...");
		wchar_t Target[100] = L"東西南北魑魅魍魎古今東西老若男女赤青白黒１９一九春夏秋冬";
		wchar_t Format[100] = L"%魑魅魍魎%老若男女%１９一九%";
		wchar_t OutStr1[32];
		wchar_t OutStr2[32];
		wchar_t OutStr3[32];
		wchar_t OutStr4[32];
		StkStringParser::ParseInto4Params(Target, Format, L'%', OutStr1, OutStr2, OutStr3, OutStr4);
		if (lstrcmp(OutStr1, L"東西南北") != 0 || lstrcmp(OutStr2, L"古今東西") != 0 ||
			lstrcmp(OutStr3, L"赤青白黒") != 0 || lstrcmp(OutStr4, L"春夏秋冬") != 0) {
			printf("NG\r\n");
			exit(0);
		}
		printf("OK\r\n");
	}
	{
		printf("[StkStringParser] normal: Same string without targets is presented ...");
		wchar_t Target[100] = L"東西南北魑魅魍魎古今東西老若男女赤青白黒１９一九春夏秋冬";
		wchar_t Format[100] = L"東西南北魑魅魍魎古今東西老若男女赤青白黒１９一九春夏秋冬";
		int Ret = StkStringParser::ParseInto4Params(Target, Format, L'%', NULL, NULL, NULL, NULL);
		if (Ret != 1) {
			printf("NG\r\n");
			exit(0);
		}
		printf("OK\r\n");
	}
	{
		printf("[StkStringParser] normal: Partial string without targets is presented ...");
		wchar_t Target[100] = L"東西南北魑魅魍魎古今東西老若男女赤青白黒１９一九春夏秋冬";
		wchar_t Format[100] = L"魑魅魍魎古今東西老若男女赤青白黒１９一九";
		int Ret = StkStringParser::ParseInto4Params(Target, Format, L'%', NULL, NULL, NULL, NULL);
		if (Ret != 0) {
			printf("NG\r\n");
			exit(0);
		}
		printf("OK\r\n");
	}
	{
		printf("[StkStringParser] normal: Large data processing ...");
		wchar_t Target[100000] = L"";
		wchar_t Format[100000] = L"";
		wchar_t TargetPart1[20000];
		wchar_t TargetPart2[20000];
		wchar_t TargetPart3[20000];
		wchar_t TargetPart4[20000];
		wchar_t TargetPart5[20000];
		wchar_t OutStr1[20001];
		wchar_t OutStr2[20001];
		wchar_t OutStr3[20001];
		wchar_t Abc[20] = {L'a', L'b', L'c', L'd', L'e', 
						L'1', L'2', L'3', L'4', L'5', 
						L'風', L'林', L'火', L'山', L'x', 
						L'y', L'魑', L'魅', L'魍', L'魎'
		};

		for (int Loop = 0; Loop < 19999; Loop++) {
			TargetPart1[Loop] = Abc[rand() % 20];
			TargetPart2[Loop] = Abc[rand() % 20];
			TargetPart3[Loop] = Abc[rand() % 20];
			TargetPart4[Loop] = Abc[rand() % 20];
			TargetPart5[Loop] = Abc[rand() % 20];
		}
		TargetPart1[19999] = L'\0';
		TargetPart2[19999] = L'\0';
		TargetPart3[19999] = L'\0';
		TargetPart4[19999] = L'\0';
		TargetPart5[19999] = L'\0';

		lstrcat(Target, TargetPart1);
		lstrcat(Target, TargetPart2);
		lstrcat(Target, TargetPart3);
		lstrcat(Target, TargetPart4);
		lstrcat(Target, TargetPart5);

		lstrcat(Format, L"!");
		lstrcat(Format, TargetPart2);
		lstrcat(Format, L"!");
		lstrcat(Format, TargetPart4);
		lstrcat(Format, L"!");

		int Ret = StkStringParser::ParseInto3Params(Target, Format, L'!', OutStr1, OutStr2, OutStr3);
		if (Ret != 1 || lstrcmp(OutStr1, TargetPart1) != 0 || lstrcmp(OutStr2, TargetPart3) != 0 || lstrcmp(OutStr3, TargetPart5) != 0) {
			printf("NG\r\n");
			exit(0);
		}
		printf("OK\r\n");
	}
	{
		printf("[StkStringParser] abnormal: Fetching empty ...");
		wchar_t Target[100] = L"東西南北魑魅魍魎古今東西老若男女赤青白黒１９一九春夏秋冬";
		wchar_t Format[100] = L"東西老若%男女赤青%白黒１９";
		wchar_t OutStr1[64];
		wchar_t OutStr2[64];
		StkStringParser::ParseInto2Params(Target, Format, L'%', OutStr1, OutStr2);
		if (lstrcmp(OutStr1, L"") != 0 || lstrcmp(OutStr2, L"") != 0) {
			printf("NG\r\n");
			exit(0);
		}
		printf("OK\r\n");
	}
	{
		printf("[StkStringParser] abnormal: Unmatch scenario (1) ...");
		wchar_t Target[100] = L"東西南北魑魅魍魎古今東西老若男女赤青白黒１９一九春夏秋冬";
		wchar_t Format[100] = L"東西南北%古今東西%赤青白黒%焼肉定食";
		wchar_t OutStr1[16];
		wchar_t OutStr2[16];
		wchar_t OutStr3[16];
		int Ret = StkStringParser::ParseInto3Params(Target, Format, L'%', OutStr1, OutStr2, OutStr3);
		if (lstrcmp(OutStr1, L"魑魅魍魎") != 0 || lstrcmp(OutStr2, L"老若男女") != 0 || OutStr3[0] != '\0' || Ret != 0) {
			printf("NG\r\n");
			exit(0);
		}
		printf("OK\r\n");
	}
	{
		printf("[StkStringParser] abnormal: Unmatch scenario (2) ...");
		wchar_t Target[100] = L"東西南北魑魅魍魎古今東西老若男女赤青白黒１９一九春夏秋冬";
		wchar_t Format[100] = L"abc$xyz";
		wchar_t OutStr1[16];
		int Ret = StkStringParser::ParseInto1Param(Target, Format, L'$', OutStr1);
		if (OutStr1[0] != '\0' || Ret != 0) {
			printf("NG\r\n");
			exit(0);
		}
		printf("OK\r\n");
	}
	{
		printf("[StkStringParser] abnormal: Unmatch scenario (3) ...");
		wchar_t Target[100] = L"東西南北魑魅魍魎古今東西老若男女赤青白黒１９一九春夏秋冬";
		wchar_t Format[100] = L"あいうえおかきくけこさしすせそたちつてと";
		wchar_t OutStr1[16];
		wchar_t OutStr2[16];
		wchar_t OutStr3[16];
		wchar_t OutStr4[16];
		int Ret = StkStringParser::ParseInto4Params(Target, Format, L'$', OutStr1, OutStr2, OutStr3, OutStr4);
		if (OutStr1[0] != '\0' || OutStr2[0] != '\0' || OutStr3[0] != '\0' || OutStr4[0] != '\0' || Ret != 0) {
			printf("NG\r\n");
			exit(0);
		}
		printf("OK\r\n");
	}
	{
		printf("[StkStringParser] abnormal: Specify all NULLs ...");
		wchar_t Target[100] = L"東西南北魑魅魍魎古今東西老若男女赤青白黒１９一九春夏秋冬";
		wchar_t Format[100] = L"%魑魅魍魎%老若男女%１９一九%";
		int Ret = StkStringParser::ParseInto4Params(Target, Format, L'%', NULL, NULL, NULL, NULL);
		if (Ret != 0) {
			printf("NG\r\n");
			exit(0);
		}
		printf("OK\r\n");
	}
	{
		printf("[StkStringParser] abnormal: Sequential double targets are specified ...");
		wchar_t Target[100] = L"東西南北魑魅魍魎古今東西老若男女赤青白黒１９一九春夏秋冬";
		wchar_t Format[100] = L"魑魅魍魎%%老若男女";
		wchar_t OutStr1[256];
		wchar_t OutStr2[256];
		StkStringParser::ParseInto4Params(Target, Format, L'%', OutStr1, OutStr2, NULL, NULL);
		if (lstrcmp(OutStr1, L"") != 0 || lstrcmp(OutStr2, L"") != 0) {
			printf("NG\r\n");
			exit(0);
		}
		printf("OK\r\n");
	}
	{
		printf("[StkStringParser] abnormal: Sequential tripple targets are specified ...");
		wchar_t Target[100] = L"東西南北魑魅魍魎古今東西老若男女赤青白黒１９一九春夏秋冬";
		wchar_t Format[100] = L"魑魅魍魎%%%老若男女";
		wchar_t OutStr1[64];
		wchar_t OutStr2[64];
		wchar_t OutStr3[64];
		StkStringParser::ParseInto4Params(Target, Format, L'%', OutStr1, OutStr2, OutStr3, NULL);
		if (lstrcmp(OutStr1, L"") != 0 || lstrcmp(OutStr2, L"") != 00 || lstrcmp(OutStr3, L"") != 0) {
			printf("NG\r\n");
			exit(0);
		}
		printf("OK\r\n");
	}
	{
		printf("[StkStringParser] abnormal: Size exceeded target ...");
		wchar_t Target[100] = L"東西南北魑魅魍魎古今東西老若男女赤青白黒１９一九春夏秋冬";
		wchar_t Format[100] = L"東西南北魑魅魍魎古今東西老若男女%赤青白黒１９一九春夏秋冬";
		int Ret = StkStringParser::ParseInto4Params(Target, Format, L'%', NULL, NULL, NULL, NULL);
		if (Ret != -1) {
			printf("NG\r\n");
			exit(0);
		}
		printf("OK\r\n");
	}
	{
		printf("[StkStringParser] abnormal: NULL string is presented ...");
		int Ret = StkStringParser::ParseInto4Params(NULL, NULL, L'%', NULL, NULL, NULL, NULL);
		if (Ret != -1) {
			printf("NG\r\n");
			exit(0);
		}
		printf("OK\r\n");
	}

	printf("StkStringParserTest completed\r\n\r\n");
	return 0;
}
