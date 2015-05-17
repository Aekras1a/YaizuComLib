#include <windows.h>
#include <tchar.h>
#include <stdio.h>

#define BUFSIZE 500000

void WriteText(TCHAR* Txt, TCHAR* Type)
{
	int Charset = 0;
	if (lstrcmp(Type, _T("mysql")) == 0) {
		Charset = CP_OEMCP;
	} else if (lstrcmp(Type, _T("postgresql")) == 0) {
		Charset = CP_UTF8;
	} else {
		return;
	}
	int cSize = WideCharToMultiByte(Charset, 0, Txt, -1, NULL, 0, NULL, NULL);
	if (cSize > 0) {
		BYTE* cTxt = new BYTE[cSize + 1];
		cSize = WideCharToMultiByte(Charset, 0, Txt, -1, (LPSTR)cTxt, cSize, NULL, NULL);
		cTxt[cSize] = '\0';
		printf_s("%s", cTxt);
		delete cTxt;
	}
}

void GenerateProductName(TCHAR* Name)
{
	TCHAR Head1[8][80] = {
		_T("������"), _T("������"), _T("������"), _T("�y����"), _T("�D���"), _T("������"), _T("�D���"), _T("���K��")
	};
	TCHAR Head2[5][80] = {
		_T("����т₩��"), _T("�����ڂ̂Ȃ�"), _T("�ƂĂ��ώ��I��"), _T("�n������"), _T("��邹�Ȃ�")
	};
	TCHAR Country[5][80] = {
		_T("����{�鍑��"), _T("�A�����J���O���Y"), _T("��p�鍑�I���W�i��"), _T("�Q���}���鍑��"), _T("�t�����X��������")
	};
	TCHAR Engine[5][80] = {
		_T("�u�^�U�C���R�O�O�O�b�b�\"), _T("����S�C���P�T�O�O�b�b�\"), _T("���`�E���C�I���d���\"), _T("����S�C���P�O�O�O�b�b�n�C�u���b�h�\"), _T("�����Ό��Q�O�O�O�b�b�^�[�{�\")
	};
	TCHAR Type[5][80] = {
		_T("�N�[�y�^"), _T("�I�[�v���^"), _T("�Z�_���^"), _T("�{�b�N�X�^"), _T("�r�t�u�^")
	};
	TCHAR Person[5][80] = {
		_T("��l���"), _T("�S�l���"), _T("�T�l���"), _T("�W�l���"), _T("�U�l���")
	};
	lstrcat(Name, Head1[rand() % 8]);
	lstrcat(Name, Head2[rand() % 5]);
	lstrcat(Name, Country[rand() % 5]);
	lstrcat(Name, Engine[rand() % 5]);
	lstrcat(Name, Type[rand() % 5]);
	lstrcat(Name, Person[rand() % 5]);
	lstrcat(Name, _T("������"));
}

int main(int argc, char* argv[])
{
	if (argc != 3) {
		printf("Usage: %s <record count> <type of target dbms>\r\n", argv[0]);
		printf("type = mysql | postgresql\r\n");
		return -1;
	}
	TCHAR Type[100];
	_snwprintf_s(Type, 100, _TRUNCATE, _T("%S"), argv[2]);
	int MaxCnt = atoi(argv[1]);
	for (int Lo = 1; Lo <= MaxCnt; Lo++) {
		for (int Loop = 0; Loop < 51; Loop++) {
			TCHAR Name[BUFSIZE] = _T("");
			TCHAR Buf[BUFSIZE] = _T("");
			GenerateProductName(Name);
			if (lstrcmp(Type, _T("mysql")) == 0) {
				_snwprintf_s(Buf, BUFSIZE, _TRUNCATE, _T("%s(Rec%05d)"), Name, Lo);
			} else {
				_snwprintf_s(Buf, BUFSIZE, _TRUNCATE, _T("\"%s(Rec%05d)\""), Name, Lo);
			}
			if (Loop == 50) {
				lstrcat(Buf, _T("\n"));
			} else {
				lstrcat(Buf, _T(","));
			}
			WriteText(Buf, Type);
		}
	}
	return 0;
}
