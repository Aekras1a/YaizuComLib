#pragma once
#include <winsock2.h>
#include <windows.h>
#include <tchar.h>

struct StkSocketInfo
{
	// Status�̂̎�蓾��l
	static const int STATUS_OPEN = 1;
	static const int STATUS_ACCEPT = 2;
	static const int STATUS_CLOSE = 3;

	// Socket Type
	int SocketType;

	// ViewElement��ID
	int ElementId;

	// �\�P�b�g
	SOCKET Sock;
	// Accept�����\�P�b�g
	SOCKET AcceptedSock;

	// ���
	int Status;

	// ������ (Receiver=0�܂���Sender=1)
	int ActionType;

	// �z�X�g���܂���IP�A�h���X
	// Receiver�̏ꍇ�҂��󂯁CSender�̏ꍇ�ڑ���
	TCHAR HostOrIpAddr[256];
	// In case of UDP receiver, last accessed IP address is stored.
	sockaddr_in LastAccessedAddr;

	// �ʐM�p�|�[�g�ԍ�
	// Receiver�̏ꍇ�҂��󂯁CSender�̏ꍇ�ڑ���
	int Port;

	// Flag which shows whether this socket is copied socket or not.
	BOOL CopiedSocketFlag;
	// If CopiedSocketFlag is true, Element ID of copy source is set. Otherwise -1 is set.
	int CopySourceId;

};
