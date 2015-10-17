#include <stdio.h>
#include <tchar.h>
#include "..\..\src\stksocket\stksocket.h"
#include "StkSocketTestMa.h"

int StkSocketTestMa::ThreadStartCount = 0;
int StkSocketTestMa::ThreadEndCount = 0;

DWORD WINAPI StkSocketTestMa::TestThreadForAccept2Recv1(LPVOID Param)
{
	ThreadStartCount++;
	BYTE Buf[1000000];
	while (TRUE) {
		if (StkSocket_Accept(121) == 0) {
			while (StkSocket_GetStatus(121) == STKSOCKET_STATUS_ACCEPT) {
				StkSocket_Receive(121, 121, Buf, 1000000, 100, NULL, 0, TRUE);
				Sleep(100);
			}
			StkSocket_CloseAccept(121, 121, FALSE);
			break;
		}
		Sleep(100);
	}
	ThreadEndCount++;
	return 0;
}

DWORD WINAPI StkSocketTestMa::TestThreadForAccept2Recv2(LPVOID Param)
{
	ThreadStartCount++;
	BYTE Buf[1000000];
	while (TRUE) {
		if (StkSocket_Accept(122) == 0) {
			while (StkSocket_GetStatus(122) == STKSOCKET_STATUS_ACCEPT) {
				StkSocket_Receive(122, 122, Buf, 1000000, 100, NULL, 0, TRUE);
				Sleep(100);
			}
			StkSocket_CloseAccept(122, 122, FALSE);
			break;
		}
		Sleep(100);
	}
	ThreadEndCount++;
	return 0;
}

DWORD WINAPI StkSocketTestMa::TestThreadForAccept2Recv3(LPVOID Param)
{
	ThreadStartCount++;
	BYTE Buf[1000000];
	while (TRUE) {
		if (StkSocket_Accept(123) == 0) {
			while (StkSocket_GetStatus(123) == STKSOCKET_STATUS_ACCEPT) {
				StkSocket_Receive(123, 123, Buf, 1000000, 100, NULL, 0, TRUE);
				Sleep(100);
			}
			StkSocket_CloseAccept(123, 123, FALSE);
			break;
		}
		Sleep(100);
	}
	ThreadEndCount++;
	return 0;
}

DWORD WINAPI StkSocketTestMa::TestThreadForAccept2Send1(LPVOID Param)
{
	ThreadStartCount++;
	char Buf[1024];
	strcpy_s(Buf, 1024, "Hello, world from #1\r\n");
	Sleep(1000);
	StkSocket_Connect(201);
	for (int Loop = 0; Loop < 50; Loop++) {
		StkSocket_Send(201, 201, (BYTE*)Buf, strlen(Buf) + 1);
		Sleep(100);
	}
	StkSocket_Disconnect(201, 201, FALSE);

	ThreadEndCount++;
	return 0;
}

DWORD WINAPI StkSocketTestMa::TestThreadForAccept2Send2(LPVOID Param)
{
	ThreadStartCount++;
	char Buf[1024];
	strcpy_s(Buf, 1024, "Hello, world from #2\r\n");
	Sleep(1000);
	StkSocket_Connect(202);
	for (int Loop = 0; Loop < 50; Loop++) {
		StkSocket_Send(202, 202, (BYTE*)Buf, strlen(Buf) + 1);
		Sleep(100);
	}
	StkSocket_Disconnect(202, 202, FALSE);

	ThreadEndCount++;
	return 0;
}

DWORD WINAPI StkSocketTestMa::TestThreadForAccept2Send3(LPVOID Param)
{
	ThreadStartCount++;
	char Buf[1024];
	strcpy_s(Buf, 1024, "Hello, world from #3\r\n");
	Sleep(1000);
	StkSocket_Connect(203);
	for (int Loop = 0; Loop < 50; Loop++) {
		StkSocket_Send(203, 203, (BYTE*)Buf, strlen(Buf) + 1);
		Sleep(100);
	}
	StkSocket_Disconnect(203, 203, FALSE);

	ThreadEndCount++;
	return 0;
}

void StkSocketTestMa::TestMultiAccept2()
{
	printf("[StkSocketTestMa::TestMultiAccept2] : Create socket --> Status validation [open] ... ");
	StkSocket_AddInfo(121, STKSOCKET_TYPE_STREAM, STKSOCKET_ACTIONTYPE_RECEIVER, _T("127.0.0.1"), 2202);
	StkSocket_Open(121);
	StkSocket_CopyInfo(122, 121);
	StkSocket_CopyInfo(123, 121);
	if (StkSocket_GetStatus(121) != STKSOCKET_STATUS_OPEN ||
		StkSocket_GetStatus(122) != STKSOCKET_STATUS_OPEN ||
		StkSocket_GetStatus(123) != STKSOCKET_STATUS_OPEN) {
			printf("NG\r\n");
			exit(-1);
	}
	printf("OK\r\n");

	StkSocket_AddInfo(201, STKSOCKET_TYPE_STREAM, STKSOCKET_ACTIONTYPE_SENDER, _T("127.0.0.1"), 2202);
	StkSocket_Open(201);
	StkSocket_AddInfo(202, STKSOCKET_TYPE_STREAM, STKSOCKET_ACTIONTYPE_SENDER, _T("127.0.0.1"), 2202);
	StkSocket_Open(202);
	StkSocket_AddInfo(203, STKSOCKET_TYPE_STREAM, STKSOCKET_ACTIONTYPE_SENDER, _T("127.0.0.1"), 2202);
	StkSocket_Open(203);

	DWORD TmpId;
	CreateThread(NULL, 0, &TestThreadForAccept2Recv1, NULL, 0, &TmpId);
	CreateThread(NULL, 0, &TestThreadForAccept2Recv2, NULL, 0, &TmpId);
	CreateThread(NULL, 0, &TestThreadForAccept2Recv3, NULL, 0, &TmpId);
	CreateThread(NULL, 0, &TestThreadForAccept2Send1, NULL, 0, &TmpId);
	CreateThread(NULL, 0, &TestThreadForAccept2Send2, NULL, 0, &TmpId);
	CreateThread(NULL, 0, &TestThreadForAccept2Send3, NULL, 0, &TmpId);

	int Loop;
	for (Loop = 0; Loop < 30; Loop++) {
		if (ThreadStartCount == 6 &&
			StkSocket_GetStatus(122) == STKSOCKET_STATUS_ACCEPT &&
			StkSocket_GetStatus(123) == STKSOCKET_STATUS_ACCEPT &&
			StkSocket_GetStatus(121) == STKSOCKET_STATUS_ACCEPT) {
			break;
		}
		Sleep(100);
	}
	printf("[StkSocketTestMa::TestMultiAccept2] : All threads are started [wait=%d msec] ... ", Loop * 100);
	if (Loop == 30) {
		printf("NG\r\n");
		exit(-1);
	}
	printf("OK\r\n");
	Sleep(500);

	printf("[StkSocketTestMa::TestMultiAccept2] : All receiver status are showing STKSOCKET_STATUS_ACCEPT ... ");
	if (StkSocket_GetStatus(122) != STKSOCKET_STATUS_ACCEPT ||
		StkSocket_GetStatus(123) != STKSOCKET_STATUS_ACCEPT ||
		StkSocket_GetStatus(121) != STKSOCKET_STATUS_ACCEPT) {
		printf("NG\r\n");
		exit(-1);
	}
	printf("OK\r\n");
	Sleep(500);

	StkSocket_Close(122, FALSE);
	printf("[StkSocketTestMa::TestMultiAccept2] : Target socket status is showing STKSOCKET_STATUS_CLOSE ... ");
	if (StkSocket_GetStatus(122) != STKSOCKET_STATUS_CLOSE ||
		StkSocket_GetStatus(123) != STKSOCKET_STATUS_ACCEPT ||
		StkSocket_GetStatus(121) != STKSOCKET_STATUS_ACCEPT) {
		printf("NG\r\n");
		exit(-1);
	}
	printf("OK\r\n");
	Sleep(500);

	StkSocket_Close(121, FALSE);
	printf("[StkSocketTestMa::TestMultiAccept2] : All receiver status are showing STKSOCKET_STATUS_CLOSE ... ");
	if (StkSocket_GetStatus(121) != STKSOCKET_STATUS_CLOSE ||
		StkSocket_GetStatus(122) != STKSOCKET_STATUS_CLOSE ||
		StkSocket_GetStatus(123) != STKSOCKET_STATUS_CLOSE) {
		printf("NG\r\n");
		exit(-1);
	}
	printf("OK\r\n");
	Sleep(1000);

	for (Loop = 0; Loop < 30; Loop++) {
		if (ThreadEndCount == 6) {
			break;
		}
		Sleep(100);
	}
	printf("[StkSocketTestMa::TestMultiAccept2] : All threads are ended [wait=%d msec] ... ", Loop * 100);
	if (Loop == 30) {
		printf("NG\r\n");
		exit(-1);
	}
	printf("OK\r\n");

	StkSocket_DeleteInfo(121);
	StkSocket_DeleteInfo(122);
	StkSocket_DeleteInfo(123);
	StkSocket_DeleteInfo(201);
	StkSocket_DeleteInfo(202);
	StkSocket_DeleteInfo(203);
}
