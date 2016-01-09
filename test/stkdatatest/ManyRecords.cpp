#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <shlwapi.h>
#include "..\..\src\stkdata\stkdata.h"
#include "..\..\src\stkdata\stkdataapi.h"

/*
ManyRecords
�EWStr(256)�~32�J�����~16383���R�[�h�̃e�[�u�����쐬���邱�Ƃ��ł���BInsertRecord��16383��J��Ԃ����R�[�h��ǉ��ł���
�E������[�ĒÏ��ÒC�����a�򒬒��c�k���y]�e�[�u������10���R�[�h���폜�ł���B�����Ƃ��ĘA�����ꂽ���R�[�h���w�肷��
�E���݂��Ȃ��J���������w�肵��ZaSortRecord�����s�����Ƃ��C-1���ԋp�����B
*/
int ManyRecords()
{
	{
		printf("WStr(256)�~32�J�����~16383���R�[�h�̃e�[�u�����쐬���邱�Ƃ��ł���BInsertRecord��16383��J��Ԃ����R�[�h��ǉ��ł���");
		ColumnDefWStr* ColDef[32];
		TableDef LargeTable(_T("�ĒÏ��ÒC�����a�򒬒��c�k���y"), 16383);
		for (int i = 0; i < 32; i++) {
			TCHAR ColName[16];
			wsprintf(ColName, _T("������k�V��j���ē���H��%d"), i);
			ColDef[i] = new ColumnDefWStr(ColName, 256);
			LargeTable.AddColumnDef(ColDef[i]);
		}
		if (CreateTable(&LargeTable) != 0) {
			printf("...[NG]\r\n");
			return -1;
		}
		for (int i = 0; i < 32; i++) {
			delete ColDef[i];
		}

		for (int k = 0; k < 16383; k++) {
			RecordData* RecDat;
			ColumnData* ColDat[32];
			for (int i = 0; i < 32; i++) {
				TCHAR ColName[16];
				TCHAR Val[256] = _T("");
				wsprintf(ColName, _T("������k�V��j���ē���H��%d"), i);
				wsprintf(Val, _T("%d %d :12345"), k, i);
				for (int j = 0; j < 24; j++) {
					lstrcat(Val, _T("���O�l�ܘZ������\"));
				}
				ColDat[i] = new ColumnDataWStr(ColName, Val);
			}
			RecDat = new RecordData(_T("�ĒÏ��ÒC�����a�򒬒��c�k���y"), ColDat, 32);
			LockTable(_T("�ĒÏ��ÒC�����a�򒬒��c�k���y"), 2);
			if (InsertRecord(RecDat) != 0) {
				printf("...[NG]\r\n");
				return -1;
			}
			UnlockTable(_T("�ĒÏ��ÒC�����a�򒬒��c�k���y"));
			delete RecDat;
		}
		printf("...[OK]\r\n");
	}

	{
		printf("������[�ĒÏ��ÒC�����a�򒬒��c�k���y]�e�[�u�����烌�R�[�h���擾����B");
		LockTable(_T("�ĒÏ��ÒC�����a�򒬒��c�k���y"), LOCK_SHARE);
		RecordData* RecDat = GetRecord(_T("�ĒÏ��ÒC�����a�򒬒��c�k���y"));
		UnlockTable(_T("�ĒÏ��ÒC�����a�򒬒��c�k���y"));
		RecordData* CurRecDat = RecDat;
		printf("�J�������w���[������k�V��j���ē���H��0]or[������k�V��j���ē���H��31]�̃J���������擾�ł��邩");
		do {
			ColumnDataWStr* ColDat0 = (ColumnDataWStr*)CurRecDat->GetColumn(_T("������k�V��j���ē���H��0"));
			if (ColDat0 == NULL) {
				printf("...[NG]\r\n");
				return -1;
			}
			TCHAR* ColDat0Value = ColDat0->GetValue();
			if (ColDat0Value == NULL || lstrlen(ColDat0Value) == 0) {
				printf("...[NG]\r\n");
				return -1;
			}
			ColumnDataWStr* ColDat31 = (ColumnDataWStr*)CurRecDat->GetColumn(_T("������k�V��j���ē���H��31"));
			if (ColDat31 == NULL) {
				printf("...[NG]\r\n");
				return -1;
			}
			TCHAR* ColDat31Value = ColDat0->GetValue();
			if (ColDat31Value == NULL || lstrlen(ColDat31Value) == 0) {
				printf("...[NG]\r\n");
				return -1;
			}
		} while (CurRecDat = CurRecDat->GetNextRecord());
		printf("...[OK]\r\n");
		delete RecDat;
	}

	{
		printf("������[�ĒÏ��ÒC�����a�򒬒��c�k���y]�e�[�u�����烌�R�[�h������(WStr��������:CONTAIN�w��)����B");
		ColumnData* ColDat[2];
		ColDat[0] = new ColumnDataWStr(_T("������k�V��j���ē���H��2"), _T("100 2 :"));
		ColDat[0]->SetComparisonOperator(COMP_CONTAIN);
		ColDat[1] = new ColumnDataWStr(_T("������k�V��j���ē���H��3"), _T("100 3 :"));
		ColDat[1]->SetComparisonOperator(COMP_CONTAIN);
		RecordData* RecDatSch = new RecordData(_T("�ĒÏ��ÒC�����a�򒬒��c�k���y"), ColDat, 2);
		LockTable(_T("�ĒÏ��ÒC�����a�򒬒��c�k���y"), LOCK_SHARE);
		RecordData* RecDatRet = GetRecord(RecDatSch);
		UnlockTable(_T("�ĒÏ��ÒC�����a�򒬒��c�k���y"));
		RecordData* CurRecDat = RecDatRet;
		do {
			ColumnDataWStr* ColDat2 = (ColumnDataWStr*)CurRecDat->GetColumn(_T("������k�V��j���ē���H��2"));
			ColumnDataWStr* ColDat3 = (ColumnDataWStr*)CurRecDat->GetColumn(_T("������k�V��j���ē���H��3"));
			if (ColDat2 == NULL || ColDat3 == NULL) {
				printf("...[NG]\r\n");
				return -1;
			}
			TCHAR* ColDat0Value2 = ColDat2->GetValue();
			TCHAR* ColDat0Value3 = ColDat3->GetValue();
			if (StrStr(ColDat0Value2, _T("100 2 :")) == NULL) {
				printf("...[NG]\r\n");
				return -1;
			}
			if (StrStr(ColDat0Value3, _T("100 3 :")) == NULL) {
				printf("...[NG]\r\n");
				return -1;
			}
		} while (CurRecDat = CurRecDat->GetNextRecord());
		delete RecDatSch;
		delete RecDatRet;
		printf("...[OK]\r\n");
	}

	{
		printf("������[�ĒÏ��ÒC�����a�򒬒��c�k���y]�e�[�u�����烌�R�[�h������(WStr��������(�s��EQUAL)�w��)����B");
		ColumnData* ColDat[1];
		ColDat[0] = new ColumnDataWStr(_T("������k�V��j���ē���H��2"), _T("100 2 :"));
		ColDat[0]->SetComparisonOperator(COMP_EQUAL);
		RecordData* RecDatSch = new RecordData(_T("�ĒÏ��ÒC�����a�򒬒��c�k���y"), ColDat, 1);
		LockTable(_T("�ĒÏ��ÒC�����a�򒬒��c�k���y"), LOCK_SHARE);
		RecordData* RecDatRet = GetRecord(RecDatSch);
		UnlockTable(_T("�ĒÏ��ÒC�����a�򒬒��c�k���y"));
		if (RecDatRet != NULL) {
			printf("...[NG]\r\n");
			return -1;
		}
		delete RecDatSch;
		printf("...[OK]\r\n");
	}

	{
		printf("������[�ĒÏ��ÒC�����a�򒬒��c�k���y]�e�[�u�����烌�R�[�h������(WStr��������:NOT CONTAIN�w��)����B");
		ColumnData* ColDat[2];
		ColDat[0] = new ColumnDataWStr(_T("������k�V��j���ē���H��2"), _T("100 2 :"), COMP_NOT_CONTAIN);
		ColDat[1] = new ColumnDataWStr(_T("������k�V��j���ē���H��3"), _T("100 3 :"), COMP_NOT_CONTAIN);
		RecordData* RecDatSch = new RecordData(_T("�ĒÏ��ÒC�����a�򒬒��c�k���y"), ColDat, 2);
		LockTable(_T("�ĒÏ��ÒC�����a�򒬒��c�k���y"), LOCK_SHARE);
		RecordData* RecDatRet = GetRecord(RecDatSch);
		UnlockTable(_T("�ĒÏ��ÒC�����a�򒬒��c�k���y"));
		RecordData* CurRecDat = RecDatRet;
		int NumOfDat = 0;
		do {
			ColumnDataWStr* ColDat2 = (ColumnDataWStr*)CurRecDat->GetColumn(_T("������k�V��j���ē���H��2"));
			ColumnDataWStr* ColDat3 = (ColumnDataWStr*)CurRecDat->GetColumn(_T("������k�V��j���ē���H��3"));
			if (ColDat2 == NULL || ColDat3 == NULL) {
				printf("...[NG]\r\n");
				return -1;
			}
			TCHAR* ColDat0Value2 = ColDat2->GetValue();
			TCHAR* ColDat0Value3 = ColDat3->GetValue();
			if (StrStr(ColDat0Value2, _T("100 2 :")) != NULL) {
				printf("...[NG]\r\n");
				return -1;
			}
			if (StrStr(ColDat0Value3, _T("100 3 :")) != NULL) {
				printf("...[NG]\r\n");
				return -1;
			}
			NumOfDat++;
		} while (CurRecDat = CurRecDat->GetNextRecord());
		delete RecDatSch;
		delete RecDatRet;
		printf("...%d[OK]\r\n", NumOfDat);
	}

	{
		printf("������[�ĒÏ��ÒC�����a�򒬒��c�k���y]�e�[�u�����烌�R�[�h������(WStr��������(�s��)�w��)����B");
		ColumnData* ColDat[2];
		ColDat[0] = new ColumnDataWStr(_T("������k�V��j���ē���H��2"), _T("100 2 :"), COMP_CONTAIN);
		ColDat[1] = new ColumnDataWStr(_T("������k�V��j���ē���H��3"), _T("100 3 :"), COMP_NOT_CONTAIN);
		RecordData* RecDatSch = new RecordData(_T("�ĒÏ��ÒC�����a�򒬒��c�k���y"), ColDat, 2);
		LockTable(_T("�ĒÏ��ÒC�����a�򒬒��c�k���y"), LOCK_SHARE);
		RecordData* RecDatRet = GetRecord(RecDatSch);
		UnlockTable(_T("�ĒÏ��ÒC�����a�򒬒��c�k���y"));
		if (RecDatRet != NULL) {
			printf("...[NG]\r\n");
			return -1;
		}
		delete RecDatSch;
		printf("...[OK]\r\n");
	}

	{
		printf("������[�ĒÏ��ÒC�����a�򒬒��c�k���y]�e�[�u������10���R�[�h���폜�ł���B�����Ƃ��ĘA�����ꂽ���R�[�h���w�肷��");
		RecordData* RecDat;
		RecordData* TopRecDat;
		RecordData* PrvRecDat;
		ColumnData* ColDat;
		for (int i = 0; i < 10; i ++) {
			TCHAR ColName[16];
			TCHAR Val[256] = _T("");
			wsprintf(ColName, _T("������k�V��j���ē���H��%d"), 0);
			wsprintf(Val, _T("%d %d :12345"), i, 0);
			for (int j = 0; j < 24; j++) {
				lstrcat(Val, _T("���O�l�ܘZ������\"));
			}
			ColDat = new ColumnDataWStr(ColName, Val);
			RecDat = new RecordData(_T("�ĒÏ��ÒC�����a�򒬒��c�k���y"), &ColDat, 1);

			if (i == 0) {
				TopRecDat = RecDat;
			}
			if (i >= 1) {
				PrvRecDat->SetNextRecord(RecDat);
			}
			PrvRecDat = RecDat;
		}
		LockTable(_T("�ĒÏ��ÒC�����a�򒬒��c�k���y"), 2);
		DeleteRecord(TopRecDat);
		UnlockTable(_T("�ĒÏ��ÒC�����a�򒬒��c�k���y"));
		delete TopRecDat;
		if (GetNumOfRecords(_T("�ĒÏ��ÒC�����a�򒬒��c�k���y")) != 16373) {
			printf("...[NG]\r\n");
			return -1;
		}
		printf("...[OK]\r\n");
	}

	{
		printf("���݂��Ȃ��J���������w�肵��ZaSortRecord�����s�����Ƃ��C-1���ԋp�����B");
		LockTable(_T("�ĒÏ��ÒC�����a�򒬒��c�k���y"), LOCK_EXCLUSIVE);
		if (ZaSortRecord(_T("�ĒÏ��ÒC�����a�򒬒��c�k���y"), _T("aaa")) != -1) {
			printf("...[NG]\r\n");
			return -1;
		}
		UnlockTable(_T("�ĒÏ��ÒC�����a�򒬒��c�k���y"));
		printf("...[OK]\r\n");
	}

	printf("��ʃ��R�[�h���܂܂��e�[�u���̍폜");
	if (DeleteTable(_T("�ĒÏ��ÒC�����a�򒬒��c�k���y")) != 0) {
		printf("...[NG]\r\n");
		return -1;
	}
	printf("...[OK]\r\n");

	return 0;
}
