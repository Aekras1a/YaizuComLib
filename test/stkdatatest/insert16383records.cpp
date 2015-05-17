#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include "..\..\src\com\stkdata\stkdata.h"


int Insert16383Records()
{
	printf("CreateTable��Person�e�[�u��(Name:WStr(10), ID;Integer, Address:WStr(15), Key:Str(10), Height:Float) Max=16383 �𐶐����邱�Ƃ��ł���");
	ColumnDefWStr ColDefName(_T("Name"), 10);
	ColumnDefInt ColDefAge(_T("ID"));
	ColumnDefWStr ColDefAddr(_T("Address"), 15);
	ColumnDefStr ColDefKey(_T("Key"), 10);
	ColumnDefFloat ColDefHeight(_T("Height"));
	TableDef TabDefPerson(_T("Person"), 16383);
	TabDefPerson.AddColumnDef(&ColDefName);
	TabDefPerson.AddColumnDef(&ColDefAge);
	TabDefPerson.AddColumnDef(&ColDefAddr);
	TabDefPerson.AddColumnDef(&ColDefKey);
	TabDefPerson.AddColumnDef(&ColDefHeight);
	if (CreateTable(&TabDefPerson) != 0) {
		printf("...[NG]\r\n");
		return -1;
	}
	printf("...[OK]\r\n");


	printf("Person�e�[�u���ɑ΂���InsertRecord��16383��J��Ԃ��C16383�̃��R�[�h��ǉ����邱�Ƃ��ł���");
	TCHAR Lname[10][5] = {	_T("���"), _T("�ؑ�"), _T("�R�c"), _T("�c��"), _T("���X��"),
							_T("�H�R"), _T("����"), _T("���J��"), _T("�n��"), _T("�ɓ�")
	};
	TCHAR Fname[10][5] = {	_T("�a�l"), _T("���q"), _T("�B��"), _T("�����q"), _T("�q"),
							_T("�R��"), _T("����"), _T("����"), _T("����"), _T("�R�I")
	};
	TCHAR Pref[7][15] = {_T("�����s"), _T("�_�ސ쌧"), _T("��錧"), _T("��ʌ�"), _T("��t��"), _T("�Ȗ،�"), _T("�R��")};
	ColumnData *ColDat1[5];
	RecordData *CurRecDat;
	for (int i = 0; i < 16383; i++) {
		TCHAR Name[10];
		wsprintf(Name, _T("%s %s"), Lname[rand() % 10], Fname[rand() % 10]);
		if (i % 5000 == 0) {
			ColDat1[0] = new ColumnDataWStr(_T("Name"), _T("�|�� �L��"));
		} else {
			ColDat1[0] = new ColumnDataWStr(_T("Name"), Name);
		}
		ColDat1[1] = new ColumnDataInt(_T("ID"), i);
		TCHAR Address[15];
		wsprintf(Address, _T("%s%d"), Pref[rand() % 7], rand() % 10000);
		ColDat1[2] = new ColumnDataWStr(_T("Address"), Address);
		ColDat1[3] = new ColumnDataStr(_T("Key"), "No Key");
		ColDat1[4] = new ColumnDataFloat(_T("Height"), (float)(150.0f + (rand() % 500) / 10.0f));
		CurRecDat = new RecordData(_T("Person"), ColDat1, 5);
		LockTable(_T("Person"), 2);
		if (InsertRecord(CurRecDat) != 0) {
			UnlockTable(_T("Person"));
			printf("...[NG]\r\n");
			ClearRecordData(CurRecDat);
			return -1;
		}
		UnlockTable(_T("Person"));
		delete ColDat1[0];
		delete ColDat1[1];
		delete ColDat1[2];
		delete ColDat1[3];
		delete ColDat1[4];
		delete CurRecDat;
	}
	printf("...[OK]\r\n");


	{
		printf("���b�N�����Ń\�[�g(AzSortRecord(_T(\"Person\"), _T(\"ID\")))���s����-1���Ԃ�");
		if (AzSortRecord(_T("Person"), _T("ID")) != -1) {
			printf("...[NG]\r\n");
			return -1;
		}
		printf("...[OK]\r\n");


		printf("���b�N�����Ń\�[�g(ZaSortRecord(_T(\"Person\"), _T(\"ID\")))���s����-1���Ԃ�");
		if (ZaSortRecord(_T("Person"), _T("ID")) != -1) {
			printf("...[NG]\r\n");
			return -1;
		}
		printf("...[OK]\r\n");


		printf("���L���b�N��\�[�g(AzSortRecord(_T(\"Person\"), _T(\"ID\")))���s����-1���Ԃ�");
		LockTable(_T("Person"), LOCK_SHARE);
		if (AzSortRecord(_T("Person"), _T("ID")) != -1) {
			UnlockTable(_T("Person"));
			printf("...[NG]\r\n");
			return -1;
		}
		UnlockTable(_T("Person"));
		printf("...[OK]\r\n");


		printf("���L���b�N��\�[�g(ZaSortRecord(_T(\"Person\"), _T(\"ID\")))���s����-1���Ԃ�");
		LockTable(_T("Person"), LOCK_SHARE);
		if (ZaSortRecord(_T("Person"), _T("ID")) != -1) {
			UnlockTable(_T("Person"));
			printf("...[NG]\r\n");
			return -1;
		}
		UnlockTable(_T("Person"));
		printf("...[OK]\r\n");


		printf("�r�����b�N��\�[�g(AzSortRecord(_T(\"Person\"), _T(\"ID\")))���s����0���Ԃ�");
		LockTable(_T("Person"), LOCK_EXCLUSIVE);
		if (AzSortRecord(_T("Person"), _T("ID")) != 0) {
			UnlockTable(_T("Person"));
			printf("...[NG]\r\n");
			return -1;
		}
		UnlockTable(_T("Person"));
		printf("...[OK]\r\n");


		printf("�r�����b�N��\�[�g(ZaSortRecord(_T(\"Person\"), _T(\"ID\")))���s����0���Ԃ�");
		LockTable(_T("Person"), LOCK_EXCLUSIVE);
		if (ZaSortRecord(_T("Person"), _T("ID")) != 0) {
			UnlockTable(_T("Person"));
			printf("...[NG]\r\n");
			return -1;
		}
		UnlockTable(_T("Person"));
		printf("...[OK]\r\n");
	}


	{
		printf("�ǉ�����16383�̃��R�[�h�ɑ΂�GetRecord(�e�[�u�����w��)�ŘA������16383�̃��R�[�h���擾���邱�Ƃ��ł���");
		int Count = 0;
		RecordData *RecDatGet;
		LockTable(_T("Person"), 1);
		RecDatGet = GetRecord(_T("Person"));
		UnlockTable(_T("Person"));
		while (RecDatGet) {
			Count++;
			RecDatGet = RecDatGet->GetNextRecord();
		}
		if (Count != 16383) {
			printf("...[NG]\r\n");
			return -1;
		}
		ClearRecordData(RecDatGet);
		printf("...[OK]\r\n");
	}


	{
		printf("�ǉ�����16383�̃��R�[�h���ɑ��݂���Name=\"�|�� �L��\"���܂�4�̃��R�[�h��GetRecord�Ō���&�擾���邱�Ƃ��ł���");
		BOOL Err = FALSE;
		int FndCnt = 0;
		RecordData *RecDatGet;
		ColumnData *ColDatTake[1];
		ColDatTake[0] = new ColumnDataWStr(_T("Name"), _T("�|�� �L��"));
		RecordData RecDatTake(_T("Person"), ColDatTake, 1);
		LockTable(_T("Person"), 1);
		RecDatGet = GetRecord(&RecDatTake);
		UnlockTable(_T("Person"));
		while (RecDatGet) {
			ColumnDataWStr *ColDatName = (ColumnDataWStr*)(RecDatGet->GetColumn(0));
			TCHAR *Name = ColDatName->GetValue();
			if (lstrcmp(Name, _T("�|�� �L��")) != 0) {
				printf("...[NG]\r\n");
				return -1;
			}
			FndCnt++;
			RecDatGet = RecDatGet->GetNextRecord();
		}
		if (FndCnt != 4) {
			printf("...[NG]\r\n");
			return -1;
		}
		ClearRecordData(RecDatGet);
		printf("...[OK]\r\n");
	}

	{
		printf("16383�̃��R�[�h���ɑ��݂��Ȃ����R�[�h(Name = \"�W���[�W �u�b�V��\")�����������Ɏw�肵��GetRecord���s�ヌ�R�[�h���擾�ł��Ȃ�");
		RecordData *RecDatGet;
		ColumnData *ColDat[1];
		ColDat[0] = new ColumnDataWStr(_T("Name"), _T("�W���[�W �u�b�V��"));
		RecordData RecDat(_T("Person"), ColDat, 1);
		LockTable(_T("Person"), 1);
		RecDatGet = GetRecord(&RecDat);
		UnlockTable(_T("Person"));
		if (RecDatGet != NULL) {
			printf("...[NG]\r\n");
			return -1;
		}
		ClearRecordData(RecDatGet);
		printf("...[OK]\r\n");
	}

	{
		printf("GetNumOfRecords(\"Person\")�Ŏ擾�������R�[�h������16383���ƂȂ�");
		if (GetNumOfRecords(_T("Person")) != 16383) {
			printf("...[NG]\r\n");
			return -1;
		}
		printf("...[OK]\r\n");
	}

	{
		printf("GetMaxNumOfRecords(\"Person\")�Ŏ擾�������R�[�h������16383���ƂȂ�");
		if (GetMaxNumOfRecords(_T("Person")) != 16383) {
			printf("...[NG]\r\n");
			return -1;
		}
		printf("...[OK]\r\n");
	}

	{
		printf("�e�[�u������\"Insert16383records.std\"�ɕۑ�����B");
		LockAllTable(LOCK_SHARE);
		if (SaveData(_T("Insert16383records.std")) != 0) {
			printf("...[NG]\r\n");
			UnlockAllTable();
			return -1;
		}
		UnlockAllTable();
		printf("...[OK]\r\n");
	}

	{
		printf("DeleteRecord(Person-Name=\"�|�� �L��\")�����b�N�����Ŏ��s�����ꍇ�C-1���ԋp����CGetNumOfRecords(_T(\"Person\"))�̒l��16383�̂܂܂ƂȂ�");
		ColumnData* Col[1];
		Col[0] = new ColumnDataWStr(_T("Name"), _T("�|�� �L��"));
		RecordData* Rec = new RecordData(_T("Person"), Col, 1);
		if (DeleteRecord(Rec) != -1) {
			printf("...[NG]\r\n");
			return -1;
		}
		if (GetNumOfRecords(_T("Person")) != 16383) {
			printf("...[NG]\r\n");
			return -1;
		}
		printf("...[OK]\r\n");


		printf("DeleteRecord(Person-Name=\"�|�� �L��\")�����L���b�N�Ŏ��s�����ꍇ�C-1���ԋp����CGetNumOfRecords(_T(\"Person\"))�̒l��16383�̂܂܂ƂȂ�");
		LockTable(_T("Person"), LOCK_SHARE);
		if (DeleteRecord(Rec) != -1) {
			printf("...[NG]\r\n");
			return -1;
		}
		UnlockTable(_T("Person"));
		if (GetNumOfRecords(_T("Person")) != 16383) {
			printf("...[NG]\r\n");
			return -1;
		}
		printf("...[OK]\r\n");


		printf("DeleteRecord(Person-Name=\"�|�� �L��\")��r�����b�N�Ŏ��s�����ꍇ�C0���ԋp����CGetNumOfRecords(_T(\"Person\"))�̒l��16379�ƂȂ�");
		LockTable(_T("Person"), LOCK_EXCLUSIVE);
		if (DeleteRecord(Rec) != 0) {
			printf("...[NG]\r\n");
			return -1;
		}
		UnlockTable(_T("Person"));
		if (GetNumOfRecords(_T("Person")) != 16379) {
			printf("...[NG]\r\n");
			return -1;
		}
		ClearRecordData(Rec);
		printf("...[OK]\r\n");
	}

	{
		printf("DeleteRecord(_T(\"Person\")�����b�N�����Ŏ��s�����ꍇ�C-1���ԋp����CGetNumOfRecords(_T(\"Person\"))�̒l��16379�̂܂܂ƂȂ�");
		if (DeleteRecord(_T("Person")) != -1) {
			printf("...[NG]\r\n");
			return -1;
		}
		if (GetNumOfRecords(_T("Person")) != 16379) {
			printf("...[NG]\r\n");
			return -1;
		}
		printf("...[OK]\r\n");


		printf("DeleteRecord(_T(\"Person\")�����L���b�N�Ŏ��s�����ꍇ�C-1���ԋp����CGetNumOfRecords(_T(\"Person\"))�̒l��16379�̂܂܂ƂȂ�");
		LockTable(_T("Person"), LOCK_SHARE);
		if (DeleteRecord(_T("Person")) != -1) {
			printf("...[NG]\r\n");
			return -1;
		}
		UnlockTable(_T("Person"));
		if (GetNumOfRecords(_T("Person")) != 16379) {
			printf("...[NG]\r\n");
			return -1;
		}
		printf("...[OK]\r\n");


		printf("DeleteRecord(_T(\"Person\")��r�����b�N�Ŏ��s�����ꍇ�C0���ԋp����CGetNumOfRecords(_T(\"Person\"))�̒l��0�ƂȂ�");
		LockTable(_T("Person"), LOCK_EXCLUSIVE);
		if (DeleteRecord(_T("Person")) != 0) {
			printf("...[NG]\r\n");
			return -1;
		}
		UnlockTable(_T("Person"));
		if (GetNumOfRecords(_T("Person")) != 0) {
			printf("...[NG]\r\n");
			return -1;
		}
		printf("...[OK]\r\n");


		printf("�ēxDeleteRecord(_T(\"Person\")��r�����b�N�Ŏ��s�����ꍇ�C���͂�Ώۃe�[�u�������݂��Ȃ�����-1���ԋp�����");
		LockTable(_T("Person"), LOCK_EXCLUSIVE);
		if (DeleteRecord(_T("Person")) != 0) {
			printf("...[NG]\r\n");
			return -1;
		}
		UnlockTable(_T("Person"));
		printf("...[OK]\r\n");
	}


	{
		printf("DeleteTable(_T(\"Person\"))�Ńe�[�u�����폜���邱�Ƃ��ł���");
		if (DeleteTable(_T("Person")) != 0) {
			printf("...[NG]\r\n");
			return -1;
		}
		printf("...[OK]\r\n");
	}

	return 0;
}
