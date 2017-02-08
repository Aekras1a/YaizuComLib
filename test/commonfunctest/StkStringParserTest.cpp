#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include "..\..\src\commonfunc\StkStringParser.h"

int StkStringParserTest()
{
	printf("StkStringParserTest started\r\n");

	{
		printf("[StkStringParser] normal: two params ...");
		TCHAR Target[100] = _T("abcdefg012345+-*/xyz6789");
		TCHAR Format[100] = _T("abcdefg#+-*/#6789");
		TCHAR OutStr1[256];
		TCHAR OutStr2[256];
		TCHAR OutStr3[256];
		TCHAR OutStr4[256];
		StkStringParser::ParseInto4Params(Target, Format, _T('#'), OutStr1, OutStr2, OutStr3, OutStr4);
		if (lstrcmp(OutStr1, _T("012345")) != 0 || lstrcmp(OutStr2, _T("xyz")) != 0) {
			printf("NG\r\n");
			exit(0);
		}
		printf("OK\r\n");
	}
	{
		printf("[StkStringParser] normal: four params ...");
		TCHAR Target[100] = _T("abcdefg012345+-*/xyz6789QWERTYUIO@@@****!!!!");
		TCHAR Format[100] = _T("abcdefg#+-*/#6789#@@@#!!!!");
		TCHAR OutStr1[256];
		TCHAR OutStr2[256];
		TCHAR OutStr3[256];
		TCHAR OutStr4[256];
		int Ret = StkStringParser::ParseInto4Params(Target, Format, _T('#'), OutStr1, OutStr2, OutStr3, OutStr4);
		if (lstrcmp(OutStr1, _T("012345")) != 0 ||
			lstrcmp(OutStr2, _T("xyz")) != 0 ||
			lstrcmp(OutStr3, _T("QWERTYUIO")) != 0 ||
			lstrcmp(OutStr4, _T("****")) != 0 ||
			Ret != 1) {
			printf("NG\r\n");
			exit(0);
		}
		printf("OK\r\n");
	}
	{
		printf("[StkStringParser] normal: Appear the target in the 1st and last char ...");
		TCHAR Target[100] = _T("abcdefg012345+-*/xyz6789QWERTYUIO@@@****!!!!");
		TCHAR Format[100] = _T("%012345+-*/%6789QWERTYUIO@@@****%");
		TCHAR OutStr1[256];
		TCHAR OutStr2[256];
		TCHAR OutStr3[256];
		TCHAR OutStr4[256];
		StkStringParser::ParseInto4Params(Target, Format, _T('%'), OutStr1, OutStr2, OutStr3, OutStr4);
		if (lstrcmp(OutStr1, _T("abcdefg")) != 0 || lstrcmp(OutStr2, _T("xyz")) != 0 || lstrcmp(OutStr3, _T("!!!!")) != 0) {
			printf("NG\r\n");
			exit(0);
		}
		printf("OK\r\n");
	}
	{
		printf("[StkStringParser] normal: Appear the target in the 1st character ...");
		TCHAR Target[100] = _T("abcdefg012345+-*/xyz6789QWERTYUIO@@@****!!!!");
		TCHAR Format[100] = _T("#012345+-*/xyz6789QWERTYUIO@@@****!!!!");
		TCHAR OutStr1[256];
		StkStringParser::ParseInto1Param(Target, Format, _T('#'), OutStr1);
		if (lstrcmp(OutStr1, _T("abcdefg")) != 0) {
			printf("NG\r\n");
			exit(0);
		}
		printf("OK\r\n");
	}
	{
		printf("[StkStringParser] normal: Appear the target in the last character ...");
		TCHAR Target[100] = _T("abcdefg012345+-*/xyz6789QWERTYUIO@@@****!!!!");
		TCHAR Format[100] = _T("abcdefg012345+-*/xyz6789QWERTYUIO@@@****#");
		TCHAR OutStr1[256];
		StkStringParser::ParseInto1Param(Target, Format, _T('#'), OutStr1);
		if (lstrcmp(OutStr1, _T("!!!!")) != 0) {
			printf("NG\r\n");
			exit(0);
		}
		printf("OK\r\n");
	}
	{
		printf("[StkStringParser] normal: Specify trimed string ...");
		TCHAR Target[100] = _T("abcdefg012345+-*/xyz6789QWERTYUIO@@@****!!!!");
		TCHAR Format[100] = _T("efg0123&ERTYUIO@@@**");
		TCHAR OutStr1[256];
		TCHAR OutStr2[256];
		TCHAR OutStr3[256];
		TCHAR OutStr4[256];
		int Ret = StkStringParser::ParseInto4Params(Target, Format, _T('&'), OutStr1, OutStr2, OutStr3, OutStr4);
		if (lstrcmp(OutStr1, _T("45+-*/xyz6789QW")) != 0 || Ret != 1) {
			printf("NG\r\n");
			exit(0);
		}
		printf("OK\r\n");
	}
	{
		printf("[StkStringParser] normal: Four 1byte chars fetching ...");
		TCHAR Target[100] = _T("abcdefg012345+-*/xyz6789QWERTYUIO@@@****!!!!");
		TCHAR Format[100] = _T("#bcdefg#12345+-*/xyz6789QWERTYUIO@@@#***!!!#");
		TCHAR OutStr1[256];
		TCHAR OutStr2[256];
		TCHAR OutStr3[256];
		TCHAR OutStr4[256];
		StkStringParser::ParseInto4Params(Target, Format, _T('#'), OutStr1, OutStr2, OutStr3, OutStr4);
		if (lstrcmp(OutStr1, _T("a")) != 0 || lstrcmp(OutStr2, _T("0")) != 0 ||
			lstrcmp(OutStr3, _T("*")) != 0 || lstrcmp(OutStr4, _T("!")) != 0) {
			printf("NG\r\n");
			exit(0);
		}
		printf("OK\r\n");
	}
	{
		printf("[StkStringParser] normal: Short string (1) ...");
		TCHAR Target[100] = _T("ab");
		TCHAR Format[100] = _T("#b");
		TCHAR OutStr1[256];
		StkStringParser::ParseInto4Params(Target, Format, _T('#'), OutStr1, NULL, NULL, NULL);
		if (lstrcmp(OutStr1, _T("a")) != 0) {
			printf("NG\r\n");
			exit(0);
		}
		printf("OK\r\n");
	}
	{
		printf("[StkStringParser] normal: Short string (2) ...");
		TCHAR Target[100] = _T("ab");
		TCHAR Format[100] = _T("a#");
		TCHAR OutStr1[256];
		StkStringParser::ParseInto4Params(Target, Format, _T('#'), OutStr1, NULL, NULL, NULL);
		if (lstrcmp(OutStr1, _T("b")) != 0) {
			printf("NG\r\n");
			exit(0);
		}
		printf("OK\r\n");
	}
	{
		printf("[StkStringParser] normal: Short string (3) ...");
		TCHAR Target[100] = _T("a");
		TCHAR Format[100] = _T("#");
		TCHAR OutStr1[256];
		int Ret = StkStringParser::ParseInto4Params(Target, Format, _T('#'), OutStr1, NULL, NULL, NULL);
		if (lstrcmp(OutStr1, _T("a")) != 0 || Ret != 1) {
			printf("NG\r\n");
			exit(0);
		}
		printf("OK\r\n");
	}
	{
		printf("[StkStringParser] normal: All Fetch ...");
		TCHAR Target[100] = _T("abcdefg012345+-*/xyz6789QWERTYUIO@@@****!!!!");
		TCHAR Format[100] = _T("#");
		TCHAR OutStr1[256];
		int Ret = StkStringParser::ParseInto4Params(Target, Format, _T('#'), OutStr1, NULL, NULL, NULL);
		if (lstrcmp(OutStr1, _T("abcdefg012345+-*/xyz6789QWERTYUIO@@@****!!!!")) != 0 || Ret != 1) {
			printf("NG\r\n");
			exit(0);
		}
		printf("OK\r\n");
	}
	{
		printf("[StkStringParser] normal: For multi bytes characters ...");
		TCHAR Target[100] = _T("������k鳖��鲌Í������V��j���Ԑ����P�X���t�ďH�~");
		TCHAR Format[100] = _T("%鳖���%�V��j��%�P�X���%");
		TCHAR OutStr1[32];
		TCHAR OutStr2[32];
		TCHAR OutStr3[32];
		TCHAR OutStr4[32];
		StkStringParser::ParseInto4Params(Target, Format, _T('%'), OutStr1, OutStr2, OutStr3, OutStr4);
		if (lstrcmp(OutStr1, _T("������k")) != 0 || lstrcmp(OutStr2, _T("�Í�����")) != 0 ||
			lstrcmp(OutStr3, _T("�Ԑ���")) != 0 || lstrcmp(OutStr4, _T("�t�ďH�~")) != 0) {
			printf("NG\r\n");
			exit(0);
		}
		printf("OK\r\n");
	}
	{
		printf("[StkStringParser] normal: Same string without targets is presented ...");
		TCHAR Target[100] = _T("������k鳖��鲌Í������V��j���Ԑ����P�X���t�ďH�~");
		TCHAR Format[100] = _T("������k鳖��鲌Í������V��j���Ԑ����P�X���t�ďH�~");
		int Ret = StkStringParser::ParseInto4Params(Target, Format, _T('%'), NULL, NULL, NULL, NULL);
		if (Ret != 1) {
			printf("NG\r\n");
			exit(0);
		}
		printf("OK\r\n");
	}
	{
		printf("[StkStringParser] normal: Partial without targets is presented ...");
		TCHAR Target[100] = _T("������k鳖��鲌Í������V��j���Ԑ����P�X���t�ďH�~");
		TCHAR Format[100] = _T("鳖��鲌Í������V��j���Ԑ����P�X���");
		int Ret = StkStringParser::ParseInto4Params(Target, Format, _T('%'), NULL, NULL, NULL, NULL);
		if (Ret != 1) {
			printf("NG\r\n");
			exit(0);
		}
		printf("OK\r\n");
	}
	{
		printf("[StkStringParser] abnormal: Fetching empty ...");
		TCHAR Target[100] = _T("������k鳖��鲌Í������V��j���Ԑ����P�X���t�ďH�~");
		TCHAR Format[100] = _T("�����V��%�j���Ԑ�%�����P�X");
		TCHAR OutStr1[64];
		TCHAR OutStr2[64];
		StkStringParser::ParseInto2Params(Target, Format, _T('%'), OutStr1, OutStr2);
		if (lstrcmp(OutStr1, _T("")) != 0 || lstrcmp(OutStr2, _T("")) != 0) {
			printf("NG\r\n");
			exit(0);
		}
		printf("OK\r\n");
	}
	{
		printf("[StkStringParser] abnormal: Unmatch scenario (1) ...");
		TCHAR Target[100] = _T("������k鳖��鲌Í������V��j���Ԑ����P�X���t�ďH�~");
		TCHAR Format[100] = _T("������k%�Í�����%�Ԑ���%�ē���H");
		TCHAR OutStr1[16];
		TCHAR OutStr2[16];
		TCHAR OutStr3[16];
		int Ret = StkStringParser::ParseInto3Params(Target, Format, _T('%'), OutStr1, OutStr2, OutStr3);
		if (lstrcmp(OutStr1, _T("鳖���")) != 0 || lstrcmp(OutStr2, _T("�V��j��")) != 0 || OutStr3[0] != '\0' || Ret != 0) {
			printf("NG\r\n");
			exit(0);
		}
		printf("OK\r\n");
	}
	{
		printf("[StkStringParser] abnormal: Unmatch scenario (2) ...");
		TCHAR Target[100] = _T("������k鳖��鲌Í������V��j���Ԑ����P�X���t�ďH�~");
		TCHAR Format[100] = _T("abc$xyz");
		TCHAR OutStr1[16];
		int Ret = StkStringParser::ParseInto1Param(Target, Format, _T('$'), OutStr1);
		if (OutStr1[0] != '\0' || Ret != 0) {
			printf("NG\r\n");
			exit(0);
		}
		printf("OK\r\n");
	}
	{
		printf("[StkStringParser] abnormal: Specify all NULLs ...");
		TCHAR Target[100] = _T("������k鳖��鲌Í������V��j���Ԑ����P�X���t�ďH�~");
		TCHAR Format[100] = _T("%鳖���%�V��j��%�P�X���%");
		int Ret = StkStringParser::ParseInto4Params(Target, Format, _T('%'), NULL, NULL, NULL, NULL);
		if (Ret != 0) {
			printf("NG\r\n");
			exit(0);
		}
		printf("OK\r\n");
	}
	{
		printf("[StkStringParser] abnormal: Sequential double targets are specified ...");
		TCHAR Target[100] = _T("������k鳖��鲌Í������V��j���Ԑ����P�X���t�ďH�~");
		TCHAR Format[100] = _T("鳖���%%�V��j��");
		TCHAR OutStr1[256];
		TCHAR OutStr2[256];
		StkStringParser::ParseInto4Params(Target, Format, _T('%'), OutStr1, OutStr2, NULL, NULL);
		if (lstrcmp(OutStr1, _T("")) != 0 || lstrcmp(OutStr2, _T("")) != 0) {
			printf("NG\r\n");
			exit(0);
		}
		printf("OK\r\n");
	}
	{
		printf("[StkStringParser] abnormal: Sequential tripple targets are specified ...");
		TCHAR Target[100] = _T("������k鳖��鲌Í������V��j���Ԑ����P�X���t�ďH�~");
		TCHAR Format[100] = _T("鳖���%%%�V��j��");
		TCHAR OutStr1[64];
		TCHAR OutStr2[64];
		TCHAR OutStr3[64];
		StkStringParser::ParseInto4Params(Target, Format, _T('%'), OutStr1, OutStr2, OutStr3, NULL);
		if (lstrcmp(OutStr1, _T("")) != 0 || lstrcmp(OutStr2, _T("")) != 00 || lstrcmp(OutStr3, _T("")) != 0) {
			printf("NG\r\n");
			exit(0);
		}
		printf("OK\r\n");
	}
	{
		printf("[StkStringParser] abnormal: Size exceeded target ...");
		TCHAR Target[100] = _T("������k鳖��鲌Í������V��j���Ԑ����P�X���t�ďH�~");
		TCHAR Format[100] = _T("������k鳖��鲌Í������V��j��%�Ԑ����P�X���t�ďH�~");
		int Ret = StkStringParser::ParseInto4Params(Target, Format, _T('%'), NULL, NULL, NULL, NULL);
		if (Ret != -1) {
			printf("NG\r\n");
			exit(0);
		}
		printf("OK\r\n");
	}
	{
		printf("[StkStringParser] abnormal: NULL string is presented ...");
		int Ret = StkStringParser::ParseInto4Params(NULL, NULL, _T('%'), NULL, NULL, NULL, NULL);
		if (Ret != -1) {
			printf("NG\r\n");
			exit(0);
		}
		printf("OK\r\n");
	}

	printf("StkStringParserTest completed\r\n\r\n");
	return 0;
}
