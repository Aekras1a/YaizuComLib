#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include "..\..\src\stkdata\stkdata.h"
#include "..\..\src\stkdata\stkdataapi.h"


int Insert16383RecordsAtOneTime()
{
	printf("CreateTable�Ŏ����ԃe�[�u��(�ʂ��ԍ�:Int, �Ԗ�:WStr(50), �^��:Str(100), �������:WStr(20)) Max=16383 �𐶐����邱�Ƃ��ł���");
	ColumnDefInt ColDefId(_T("�ʂ��ԍ�"));
	ColumnDefWStr ColDefName(_T("�Ԗ�"), 50);
	ColumnDefStr ColDefType(_T("�^��"), 100);
	ColumnDefWStr ColDefManuf(_T("�������"), 20);
	TableDef TabDefPerson(_T("������"), 16383);
	TabDefPerson.AddColumnDef(&ColDefId);
	TabDefPerson.AddColumnDef(&ColDefName);
	TabDefPerson.AddColumnDef(&ColDefType);
	TabDefPerson.AddColumnDef(&ColDefManuf);
	if (CreateTable(&TabDefPerson) != 0) {
		printf("...[NG]\r\n");
		return -1;
	}
	printf("...[OK]\r\n");


	printf("16383�̌������ꂽ���R�[�h�������ԃe�[�u���ɑ΂���InsertRecord(�Ăяo��1��)�����s���C16383�̃��R�[�h��ǉ����邱�Ƃ��ł���");
	ColumnData *ColDat[4];
	RecordData *TopRecDat;
	RecordData *PrvRecDat;
	RecordData *CurRecDat;
	for (int i = 0; i < 16383; i++) {
		ColDat[0] = new ColumnDataInt(_T("�ʂ��ԍ�"), i);
		ColDat[1] = new ColumnDataWStr(_T("�Ԗ�"), _T("�X�[�p�[�`���[�W���[�t2400cc 2�V�[�^�[�I�[�v���J�[ �h�[���X�^�[ VS"));
		ColDat[2] = new ColumnDataStr(_T("�^��"), "ABCDEFGHIJABCDEFGHIJABCDEFGHIJ01234567890123456789012345678901234567890123456789");
		ColDat[3] = new ColumnDataWStr(_T("�������"), _T("Mazzzzzzzda�����ԍH��"));
		CurRecDat = new RecordData(_T("������"), ColDat, 4);
		if (i == 0) {
			TopRecDat = CurRecDat;
		}
		if (i >= 1) {
			PrvRecDat->SetNextRecord(CurRecDat);
		}
		PrvRecDat = CurRecDat;
	}
	LockTable(_T("������"), 2);
	if (InsertRecord(TopRecDat) != 0) {
		delete TopRecDat;
		printf("...[NG]\r\n");
		return -1;
	}
	UnlockTable(_T("������"));
	delete TopRecDat;
	printf("...[OK]\r\n");


	printf("GetTableVersion(_T(\"������\"))��16383��Ԃ����Ƃ��m�F����");
	if (GetTableVersion(_T("������")) != 16383) {
		printf("...[NG]\r\n");
		return -1;
	}
	printf("...[OK]\r\n");


	printf("�ǉ�����16383�̃��R�[�h�ɑ΂�GetRecord(���R�[�h�w��)�ŘA������16383�̃��R�[�h���擾���邱�Ƃ��ł���");
	int Count = 0;
	ColumnData *ColDatTake[1];
	ColDatTake[0] = new ColumnDataStr(_T("�^��"), "ABCDEFGHIJABCDEFGHIJABCDEFGHIJ01234567890123456789012345678901234567890123456789");
	RecordData RecDatTake(_T("������"), ColDatTake, 1);
	RecordData *RecDatGet;
	LockTable(_T("������"), 1);
	RecDatGet = GetRecord(&RecDatTake);
	UnlockTable(_T("������"));
	while (RecDatGet) {
		if (lstrcmp(((ColumnDataWStr*)(RecDatGet->GetColumn(1)))->GetValue(), _T("�X�[�p�[�`���[�W���[�t2400cc 2�V�[�^�[�I�[�v���J�[ �h�[���X�^�[ VS")) != 0) {
			printf("...[NG]\r\n");
			return -1;
		}
		Count++;
		RecDatGet = RecDatGet->GetNextRecord();
	}
	if (Count != 16383) {
		printf("...[NG]\r\n");
		return -1;
	}
	delete RecDatGet;
	printf("...[OK]\r\n");


	{
		printf("GetColumnCount(_T(\"������\"))�����GetColumnName(_T(\"������\"))�̌��ʂ�4�ƂȂ�BGetColumnName�Ŏ擾����1�Ԗڂ̃J��������\"�ʂ��ԍ�\",4�Ԗڂ̃J��������\"�������\"�ƂȂ�");
		TCHAR ColNames[MAX_COLUMN_NUMBER][16];
		if (GetColumnCount(_T("������")) != 4) {
			printf("...[NG]\r\n");
			return -1;
		}
		if (GetColumnName(_T("������"), ColNames) != 4) {
			printf("...[NG]\r\n");
			return -1;
		}
		if (lstrcmp(ColNames[0], _T("�ʂ��ԍ�")) != 0) {
			printf("...[NG]\r\n");
			return -1;
		}
		if (lstrcmp(ColNames[3], _T("�������")) != 0) {
			printf("...[NG]\r\n");
			return -1;
		}
		printf("...[OK]\r\n");
	}


	{
		printf("GetColumnCount(_T(\"���]��\"))�����GetColumnName(_T(\"���]��\"))�̌��ʂ�-1�ƂȂ�");
		TCHAR ColNames[MAX_COLUMN_NUMBER][16];
		if (GetColumnCount(_T("���]��")) != -1) {
			printf("...[NG]\r\n");
			return -1;
		}
		if (GetColumnName(_T("���]��"), ColNames) != -1) {
			printf("...[NG]\r\n");
			return -1;
		}
		printf("...[OK]\r\n");
	}

	{
		printf("�����̎����ԃe�[�u����[�ʂ��ԍ�=�]�ƂȂ郌�R�[�h(8191��)�ɂ��ĎԖ�=\"���{�����t������b��p�N�[�y\"�ɕύX����(8191�̘A�����ꂽRecordData��UpdateRecord�ɓn��)");
		ColumnData *ColDat[4];
		RecordData *TopRecDat;
		RecordData *PrvRecDat;
		RecordData *CurRecDat;
		ColDat[0] = new ColumnDataInt(_T("�ʂ��ԍ�"), 100);
		ColDat[1] = new ColumnDataWStr(_T("�Ԗ�"), _T("���{�����t������b��p�N�[�y"));
		ColDat[2] = new ColumnDataStr(_T("�^��"), "So-Ri");
		ColDat[3] = new ColumnDataWStr(_T("�������"), _T("���t�{"));
		CurRecDat = new RecordData(_T("������"), ColDat, 4);
		for (int i = 1; i < 16383; i += 2) {
			ColumnData* ColDatSch[1];
			ColDatSch[0] = new ColumnDataInt(_T("�ʂ��ԍ�"), i);
			RecordData* RecDatSch = new RecordData(_T("������"), ColDatSch, 1);
			if (i == 1) {
				TopRecDat = RecDatSch;
			}
			if (i >= 2) {
				PrvRecDat->SetNextRecord(RecDatSch);
			}
			PrvRecDat = RecDatSch;
		}
		LockTable(_T("������"), 2);
		if (UpdateRecord(TopRecDat, CurRecDat) != 0) {
			UnlockTable(_T("������"));
			delete TopRecDat;
			delete CurRecDat;
			printf("...[NG]\r\n");
			return -1;
		}
		UnlockTable(_T("������"));
		delete TopRecDat;
		delete CurRecDat;
		printf("...[OK]\r\n");


		printf("GetRecord(_T(\"������\"))�Ŏ擾�������R�[�h�́C�h�ʂ��ԍ�����h���{���E�E�E�h�C�������h�X�[�p�[�`���[�W���[�t�E�E�E�h�ƂȂ��Ă���");
		int Count = 0;
		RecordData *RecDatGet;
		LockTable(_T("������"), 1);
		RecDatGet = GetRecord(_T("������"));
		UnlockTable(_T("������"));
		while (RecDatGet) {
			TCHAR *ColName = ((ColumnDataWStr*)(RecDatGet->GetColumn(1)))->GetValue();
			if (Count % 2 == 0) {
				if (lstrcmp(ColName, _T("�X�[�p�[�`���[�W���[�t2400cc 2�V�[�^�[�I�[�v���J�[ �h�[���X�^�[ VS")) != 0) {
					printf("...[NG]\r\n");
					return -1;
				}
			} else {
				if (lstrcmp(ColName, _T("���{�����t������b��p�N�[�y")) != 0) {
					printf("...[NG]\r\n");
					return -1;
				}
			}
			Count++;
			RecDatGet = RecDatGet->GetNextRecord();
		}
		printf("...[OK]\r\n");


		printf("GetRecord(_T(\"������\"))��16383�̃��R�[�h���擾�ł�����GetNumOfRecords()���ʂ�16383�ƂȂ�");
		if (Count != 16383 || GetNumOfRecords(_T("������")) != 16383) {
			printf("...[NG]\r\n");
			delete RecDatGet;
			return -1;
		}
		delete RecDatGet;
		printf("...[OK]\r\n");
	}

	{
		printf("\"������\"�e�[�u������\"�������\" = \"���t�{X\"�ƂȂ郌�R�[�h�̍폜���s���B�����O���s��v�̂���DeleteRecord���GetNumOfRecords��16383��Ԃ�");
		ColumnData *ColDat[1];
		ColDat[0] = new ColumnDataWStr(_T("�������"), _T("���t�{X"));
		RecordData *RecDat = new RecordData(_T("������"), ColDat, 1);
		LockTable(_T("������"), LOCK_EXCLUSIVE);
		if (DeleteRecord(RecDat) != 0) {
			printf("...[NG]\r\n");
			return -1;
		}
		UnlockTable(_T("������"));
		delete RecDat;
		if (GetNumOfRecords(_T("������")) != 16383) {
			printf("...[NG]\r\n");
			return -1;
		}
		printf("...[OK]\r\n");
	}


	{
		printf("\"������\"�e�[�u������\"�������\" = \"���t�{\"�ƂȂ郌�R�[�h�̍폜���s���BDeleteRecord���GetNumOfRecords��8192��Ԃ�");
		ColumnData *ColDat[1];
		ColDat[0] = new ColumnDataWStr(_T("�������"), _T("���t�{"));
		RecordData *RecDat = new RecordData(_T("������"), ColDat, 1);
		LockTable(_T("������"), LOCK_EXCLUSIVE);
		if (DeleteRecord(RecDat) != 0) {
			printf("...[NG]\r\n");
			return -1;
		}
		UnlockTable(_T("������"));
		delete RecDat;
		if (GetNumOfRecords(_T("������")) != 8192) {
			printf("...[NG]\r\n");
			return -1;
		}
		printf("...[OK]\r\n");
	}

	{
		printf("GetMaxNumOfRecords(_T(\"������\"))�̌��ʂ�16383�ƂȂ�");
		if (GetMaxNumOfRecords(_T("������")) != 16383) {
			printf("...[NG]\r\n");
			return -1;
		}
		printf("...[OK]\r\n");
	}


	{
		printf("���R�[�h��8192�����݂����Ԃ�DeleteTable(_T(\"������\"))�����s��CGetNumOfRecords(_T(\"������\"))�����GetMaxNumOfRecords(_T(\"������\"))�̕Ԃ�l��-1�ƂȂ�B");
		if (DeleteTable(_T("������")) != 0) {
			printf("...[NG]\r\n");
			return -1;
		}
		if (GetMaxNumOfRecords(_T("������")) != -1) {
			printf("...[NG]\r\n");
			return -1;
		}
		if (GetNumOfRecords(_T("������")) != -1) {
			printf("...[NG]\r\n");
			return -1;
		}
		printf("...[OK]\r\n");
	}


	return 0;
}
