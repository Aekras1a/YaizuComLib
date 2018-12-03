#include <windows.h>
#include <stdio.h>
#include "..\..\src\stkdata\stkdata.h"
#include "..\..\src\stkdata\stkdataapi.h"


int Insert16383RecordsAtOneTime()
{
	printf("CreateTable�Ŏ����ԃe�[�u��(�ʂ��ԍ�:Int, �Ԗ�:WStr(50), �^��:Str(100), �������:WStr(20)) Max=16383 �𐶐����邱�Ƃ��ł���");
	ColumnDefInt ColDefId(L"�ʂ��ԍ�");
	ColumnDefWStr ColDefName(L"�Ԗ�", 50);
	ColumnDefStr ColDefType(L"�^��", 100);
	ColumnDefWStr ColDefManuf(L"�������", 20);
	TableDef TabDefPerson(L"������", 16383);
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
		ColDat[0] = new ColumnDataInt(L"�ʂ��ԍ�", i);
		ColDat[1] = new ColumnDataWStr(L"�Ԗ�", L"�X�[�p�[�`���[�W���[�t2400cc 2�V�[�^�[�I�[�v���J�[ �h�[���X�^�[ VS");
		ColDat[2] = new ColumnDataStr(L"�^��", "ABCDEFGHIJABCDEFGHIJABCDEFGHIJ01234567890123456789012345678901234567890123456789");
		ColDat[3] = new ColumnDataWStr(L"�������", L"Mazzzzzzzda�����ԍH��");
		CurRecDat = new RecordData(L"������", ColDat, 4);
		if (i == 0) {
			TopRecDat = CurRecDat;
		}
		if (i >= 1) {
			PrvRecDat->SetNextRecord(CurRecDat);
		}
		PrvRecDat = CurRecDat;
	}
	LockTable(L"������", 2);
	if (InsertRecord(TopRecDat) != 0) {
		delete TopRecDat;
		printf("...[NG]\r\n");
		return -1;
	}
	UnlockTable(L"������");
	delete TopRecDat;
	printf("...[OK]\r\n");


	printf("GetTableVersion(L\"������\")��16383��Ԃ����Ƃ��m�F����");
	if (GetTableVersion(L"������") != 16383) {
		printf("...[NG]\r\n");
		return -1;
	}
	printf("...[OK]\r\n");


	printf("�ǉ�����16383�̃��R�[�h�ɑ΂�GetRecord(���R�[�h�w��)�ŘA������16383�̃��R�[�h���擾���邱�Ƃ��ł���");
	int Count = 0;
	ColumnData *ColDatTake[1];
	ColDatTake[0] = new ColumnDataStr(L"�^��", "ABCDEFGHIJABCDEFGHIJABCDEFGHIJ01234567890123456789012345678901234567890123456789");
	RecordData RecDatTake(L"������", ColDatTake, 1);
	RecordData *RecDatGet;
	LockTable(L"������", 1);
	RecDatGet = GetRecord(&RecDatTake);
	UnlockTable(L"������");
	while (RecDatGet) {
		if (lstrcmp(((ColumnDataWStr*)(RecDatGet->GetColumn(1)))->GetValue(), L"�X�[�p�[�`���[�W���[�t2400cc 2�V�[�^�[�I�[�v���J�[ �h�[���X�^�[ VS") != 0) {
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
		printf("GetColumnCount(L\"������\")�����GetColumnName(L\"������\")�̌��ʂ�4�ƂȂ�BGetColumnName�Ŏ擾����1�Ԗڂ̃J��������\"�ʂ��ԍ�\",4�Ԗڂ̃J��������\"�������\"�ƂȂ�");
		wchar_t ColNames[MAX_COLUMN_NUMBER][16];
		if (GetColumnCount(L"������") != 4) {
			printf("...[NG]\r\n");
			return -1;
		}
		if (GetColumnName(L"������", ColNames) != 4) {
			printf("...[NG]\r\n");
			return -1;
		}
		if (lstrcmp(ColNames[0], L"�ʂ��ԍ�") != 0) {
			printf("...[NG]\r\n");
			return -1;
		}
		if (lstrcmp(ColNames[3], L"�������") != 0) {
			printf("...[NG]\r\n");
			return -1;
		}
		printf("...[OK]\r\n");
	}


	{
		printf("GetColumnCount(L\"���]��\")�����GetColumnName(L\"���]��\")�̌��ʂ�-1�ƂȂ�");
		wchar_t ColNames[MAX_COLUMN_NUMBER][16];
		if (GetColumnCount(L"���]��") != -1) {
			printf("...[NG]\r\n");
			return -1;
		}
		if (GetColumnName(L"���]��", ColNames) != -1) {
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
		ColDat[0] = new ColumnDataInt(L"�ʂ��ԍ�", 100);
		ColDat[1] = new ColumnDataWStr(L"�Ԗ�", L"���{�����t������b��p�N�[�y");
		ColDat[2] = new ColumnDataStr(L"�^��", "So-Ri");
		ColDat[3] = new ColumnDataWStr(L"�������", L"���t�{");
		CurRecDat = new RecordData(L"������", ColDat, 4);
		for (int i = 1; i < 16383; i += 2) {
			ColumnData* ColDatSch[1];
			ColDatSch[0] = new ColumnDataInt(L"�ʂ��ԍ�", i);
			RecordData* RecDatSch = new RecordData(L"������", ColDatSch, 1);
			if (i == 1) {
				TopRecDat = RecDatSch;
			}
			if (i >= 2) {
				PrvRecDat->SetNextRecord(RecDatSch);
			}
			PrvRecDat = RecDatSch;
		}
		LockTable(L"������", 2);
		if (UpdateRecord(TopRecDat, CurRecDat) != 0) {
			UnlockTable(L"������");
			delete TopRecDat;
			delete CurRecDat;
			printf("...[NG]\r\n");
			return -1;
		}
		UnlockTable(L"������");
		delete TopRecDat;
		delete CurRecDat;
		printf("...[OK]\r\n");


		printf("GetRecord(L\"������\")�Ŏ擾�������R�[�h�́C�h�ʂ��ԍ�����h���{���E�E�E�h�C�������h�X�[�p�[�`���[�W���[�t�E�E�E�h�ƂȂ��Ă���");
		int Count = 0;
		RecordData *RecDatGet;
		LockTable(L"������", 1);
		RecDatGet = GetRecord(L"������");
		UnlockTable(L"������");
		while (RecDatGet) {
			wchar_t *ColName = ((ColumnDataWStr*)(RecDatGet->GetColumn(1)))->GetValue();
			if (Count % 2 == 0) {
				if (lstrcmp(ColName, L"�X�[�p�[�`���[�W���[�t2400cc 2�V�[�^�[�I�[�v���J�[ �h�[���X�^�[ VS") != 0) {
					printf("...[NG]\r\n");
					return -1;
				}
			} else {
				if (lstrcmp(ColName, L"���{�����t������b��p�N�[�y") != 0) {
					printf("...[NG]\r\n");
					return -1;
				}
			}
			Count++;
			RecDatGet = RecDatGet->GetNextRecord();
		}
		printf("...[OK]\r\n");


		printf("GetRecord(L\"������\")��16383�̃��R�[�h���擾�ł�����GetNumOfRecords()���ʂ�16383�ƂȂ�");
		if (Count != 16383 || GetNumOfRecords(L"������") != 16383) {
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
		ColDat[0] = new ColumnDataWStr(L"�������", L"���t�{X");
		RecordData *RecDat = new RecordData(L"������", ColDat, 1);
		LockTable(L"������", LOCK_EXCLUSIVE);
		if (DeleteRecord(RecDat) != 0) {
			printf("...[NG]\r\n");
			return -1;
		}
		UnlockTable(L"������");
		delete RecDat;
		if (GetNumOfRecords(L"������") != 16383) {
			printf("...[NG]\r\n");
			return -1;
		}
		printf("...[OK]\r\n");
	}


	{
		printf("\"������\"�e�[�u������\"�������\" = \"���t�{\"�ƂȂ郌�R�[�h�̍폜���s���BDeleteRecord���GetNumOfRecords��8192��Ԃ�");
		ColumnData *ColDat[1];
		ColDat[0] = new ColumnDataWStr(L"�������", L"���t�{");
		RecordData *RecDat = new RecordData(L"������", ColDat, 1);
		LockTable(L"������", LOCK_EXCLUSIVE);
		if (DeleteRecord(RecDat) != 0) {
			printf("...[NG]\r\n");
			return -1;
		}
		UnlockTable(L"������");
		delete RecDat;
		if (GetNumOfRecords(L"������") != 8192) {
			printf("...[NG]\r\n");
			return -1;
		}
		printf("...[OK]\r\n");
	}

	{
		printf("GetMaxNumOfRecords(L\"������\")�̌��ʂ�16383�ƂȂ�");
		if (GetMaxNumOfRecords(L"������") != 16383) {
			printf("...[NG]\r\n");
			return -1;
		}
		printf("...[OK]\r\n");
	}


	{
		printf("���R�[�h��8192�����݂����Ԃ�DeleteTable(L\"������\")�����s��CGetNumOfRecords(L\"������\")�����GetMaxNumOfRecords(L\"������\")�̕Ԃ�l��-1�ƂȂ�B");
		if (DeleteTable(L"������") != 0) {
			printf("...[NG]\r\n");
			return -1;
		}
		if (GetMaxNumOfRecords(L"������") != -1) {
			printf("...[NG]\r\n");
			return -1;
		}
		if (GetNumOfRecords(L"������") != -1) {
			printf("...[NG]\r\n");
			return -1;
		}
		printf("...[OK]\r\n");
	}


	return 0;
}
