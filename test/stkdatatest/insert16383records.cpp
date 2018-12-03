#include <windows.h>
#include <stdio.h>
#include <shlwapi.h>
#include "..\..\src\stkdata\stkdata.h"
#include "..\..\src\stkdata\stkdataapi.h"


int Insert16383Records()
{
	printf("CreateTable��Person�e�[�u��(Name:WStr(10), ID;Integer, Address:WStr(15), Key:Str(10), Height:Float) Max=16383 �𐶐����邱�Ƃ��ł���");
	ColumnDefWStr ColDefName(L"Name", 10);
	ColumnDefInt ColDefAge(L"ID");
	ColumnDefWStr ColDefAddr(L"Address", 15);
	ColumnDefStr ColDefKey(L"Key", 10);
	ColumnDefFloat ColDefHeight(L"Height");
	TableDef TabDefPerson(L"Person", 16383);
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
	wchar_t Lname[10][5] = {	L"���", L"�ؑ�", L"�R�c", L"�c��", L"���X��",
							L"�H�R", L"����", L"���J��", L"�n��", L"�ɓ�"
	};
	wchar_t Fname[10][5] = {	L"�a�l", L"���q", L"�B��", L"�����q", L"�q",
							L"�R��", L"����", L"����", L"����", L"�R�I"
	};
	wchar_t Pref[7][15] = {L"�����s", L"�_�ސ쌧", L"��錧", L"��ʌ�", L"��t��", L"�Ȗ،�", L"�R��"};
	ColumnData *ColDat1[5];
	RecordData *CurRecDat;
	for (int i = 0; i < 16383; i++) {
		wchar_t Name[10];
		wsprintf(Name, L"%s %s", Lname[rand() % 10], Fname[rand() % 10]);
		if (i % 5000 == 0) {
			ColDat1[0] = new ColumnDataWStr(L"Name", L"�|�� �L��");
		} else {
			ColDat1[0] = new ColumnDataWStr(L"Name", Name);
		}
		ColDat1[1] = new ColumnDataInt(L"ID", i);
		wchar_t Address[15];
		wsprintf(Address, L"%s%d", Pref[rand() % 7], rand() % 10000);
		ColDat1[2] = new ColumnDataWStr(L"Address", Address);
		ColDat1[3] = new ColumnDataStr(L"Key", "No Key");
		ColDat1[4] = new ColumnDataFloat(L"Height", (float)(150.0f + (rand() % 500) / 10.0f));
		CurRecDat = new RecordData(L"Person", ColDat1, 5);
		LockTable(L"Person", 2);
		if (InsertRecord(CurRecDat) != 0) {
			UnlockTable(L"Person");
			printf("...[NG]\r\n");
			delete CurRecDat;
			return -1;
		}
		UnlockTable(L"Person");
		delete CurRecDat;
	}
	printf("...[OK]\r\n");


	{
		printf("���b�N�����Ń\�[�g(AzSortRecord(L\"Person\", L\"ID\")))���s����-1���Ԃ�");
		if (AzSortRecord(L"Person", L"ID") != -1) {
			printf("...[NG]\r\n");
			return -1;
		}
		printf("...[OK]\r\n");


		printf("���b�N�����Ń\�[�g(ZaSortRecord(L\"Person\", L\"ID\")))���s����-1���Ԃ�");
		if (ZaSortRecord(L"Person", L"ID") != -1) {
			printf("...[NG]\r\n");
			return -1;
		}
		printf("...[OK]\r\n");


		printf("���L���b�N��\�[�g(AzSortRecord(L\"Person\", L\"ID\"))���s����-1���Ԃ�");
		LockTable(L"Person", LOCK_SHARE);
		if (AzSortRecord(L"Person", L"ID") != -1) {
			UnlockTable(L"Person");
			printf("...[NG]\r\n");
			return -1;
		}
		UnlockTable(L"Person");
		printf("...[OK]\r\n");


		printf("���L���b�N��\�[�g(ZaSortRecord(L\"Person\", L\"ID\"))���s����-1���Ԃ�");
		LockTable(L"Person", LOCK_SHARE);
		if (ZaSortRecord(L"Person", L"ID") != -1) {
			UnlockTable(L"Person");
			printf("...[NG]\r\n");
			return -1;
		}
		UnlockTable(L"Person");
		printf("...[OK]\r\n");


		printf("�r�����b�N��\�[�g(AzSortRecord(L\"Person\", L\"ID\"))���s����0���Ԃ�");
		LockTable(L"Person", LOCK_EXCLUSIVE);
		if (AzSortRecord(L"Person", L"ID") != 0) {
			UnlockTable(L"Person");
			printf("...[NG]\r\n");
			return -1;
		}
		UnlockTable(L"Person");
		printf("...[OK]\r\n");


		printf("�r�����b�N��\�[�g(ZaSortRecord(\"Person\", L\"ID\"))���s����0���Ԃ�");
		LockTable(L"Person", LOCK_EXCLUSIVE);
		if (ZaSortRecord(L"Person", L"ID") != 0) {
			UnlockTable(L"Person");
			printf("...[NG]\r\n");
			return -1;
		}
		UnlockTable(L"Person");
		printf("...[OK]\r\n");
	}


	{
		printf("�ǉ�����16383�̃��R�[�h�ɑ΂�GetRecord(�e�[�u�����w��)�ŘA������16383�̃��R�[�h���擾���邱�Ƃ��ł���");
		int Count = 0;
		RecordData *RecDatGet;
		LockTable(L"Person", 1);
		RecDatGet = GetRecord(L"Person");
		UnlockTable(L"Person");
		while (RecDatGet) {
			Count++;
			RecDatGet = RecDatGet->GetNextRecord();
		}
		if (Count != 16383) {
			printf("...[NG]\r\n");
			return -1;
		}
		delete RecDatGet;
		printf("...[OK]\r\n");
	}


	{
		printf("�ǉ�����16383�̃��R�[�h���ɑ��݂���Name=\"�ؑ�\"�܂���\"�c��\"���܂݁C1000 < ID < 2000  �̃��R�[�h���������邱�Ƃ��ł���");
		bool Err = false;
		int FndCnt = 0;
		RecordData *RecDatGet;
		ColumnData *ColDatTake[6];
		RecordData* RecDatKim;
		RecordData* RecDatTan;

		ColDatTake[0] = new ColumnDataWStr(L"Name", L"�ؑ�", COMP_CONTAIN);
		ColDatTake[1] = new ColumnDataInt(L"ID", 1000, COMP_GT);
		ColDatTake[2] = new ColumnDataInt(L"ID", 2000, COMP_LT);
		RecDatKim = new RecordData(L"Person", &ColDatTake[0], 3);

		ColDatTake[3] = new ColumnDataWStr(L"Name", L"�c��", COMP_CONTAIN);
		ColDatTake[4] = new ColumnDataInt(L"ID", 1000, COMP_GT);
		ColDatTake[5] = new ColumnDataInt(L"ID", 2000, COMP_LT);
		RecDatTan = new RecordData(L"Person", &ColDatTake[3], 3);
		RecDatKim->SetNextRecord(RecDatTan);

		LockTable(L"Person", 1);
		RecDatGet = GetRecord(RecDatKim);
		UnlockTable(L"Person");

		if (RecDatGet == NULL) {
			printf("...[NG]\r\n");
			return -1;
		}
		int NumOfFnd = 0;
		for (RecordData* CurRecDat = RecDatGet; CurRecDat != NULL; CurRecDat = CurRecDat->GetNextRecord()) {
			ColumnDataWStr* ColName = (ColumnDataWStr*)CurRecDat->GetColumn(L"Name");
			if (StrStr(ColName->GetValue(), L"�ؑ�") == NULL && StrStr(ColName->GetValue(), L"�c��") == NULL ) {
				printf("...[NG]\r\n");
				return -1;
			}
			ColumnDataInt* ColId = (ColumnDataInt*)CurRecDat->GetColumn(L"ID");
			if (ColId->GetValue() <= 1000 && ColId->GetValue() >= 2000) {
				printf("...[NG]\r\n");
				return -1;
			}
			NumOfFnd++;
		}
		delete RecDatKim;
		delete RecDatGet;
		printf("...%d records found [OK]\r\n", NumOfFnd);
	}


	{
		printf("�ǉ�����16383�̃��R�[�h���ɑ��݂���Name=\"�|�� �L��\"���܂�4�̃��R�[�h��GetRecord�Ō���&�擾���邱�Ƃ��ł���");
		bool Err = false;
		int FndCnt = 0;
		RecordData *RecDatGet;
		ColumnData *ColDatTake[1];
		ColDatTake[0] = new ColumnDataWStr(L"Name", L"�|�� �L��");
		RecordData RecDatTake(L"Person", ColDatTake, 1);
		LockTable(L"Person", 1);
		RecDatGet = GetRecord(&RecDatTake);
		UnlockTable(L"Person");
		while (RecDatGet) {
			ColumnDataWStr *ColDatName = (ColumnDataWStr*)(RecDatGet->GetColumn(0));
			wchar_t *Name = ColDatName->GetValue();
			if (lstrcmp(Name, L"�|�� �L��") != 0) {
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
		delete RecDatGet;
		printf("...[OK]\r\n");
	}

	{
		printf("16383�̃��R�[�h���ɑ��݂��Ȃ����R�[�h(Name = \"�W���[�W �u�b�V��\")�����������Ɏw�肵��GetRecord���s�ヌ�R�[�h���擾�ł��Ȃ�");
		RecordData *RecDatGet;
		ColumnData *ColDat[1];
		ColDat[0] = new ColumnDataWStr(L"Name", L"�W���[�W �u�b�V��");
		RecordData RecDat(L"Person", ColDat, 1);
		LockTable(L"Person", 1);
		RecDatGet = GetRecord(&RecDat);
		UnlockTable(L"Person");
		if (RecDatGet != NULL) {
			printf("...[NG]\r\n");
			return -1;
		}
		delete RecDatGet;
		printf("...[OK]\r\n");
	}

	{
		printf("GetNumOfRecords(\"Person\")�Ŏ擾�������R�[�h������16383���ƂȂ�");
		if (GetNumOfRecords(L"Person") != 16383) {
			printf("...[NG]\r\n");
			return -1;
		}
		printf("...[OK]\r\n");
	}

	{
		printf("GetMaxNumOfRecords(\"Person\")�Ŏ擾�������R�[�h������16383���ƂȂ�");
		if (GetMaxNumOfRecords(L"Person") != 16383) {
			printf("...[NG]\r\n");
			return -1;
		}
		printf("...[OK]\r\n");
	}

	{
		printf("�e�[�u������\"Insert16383records.std\"�ɕۑ�����B");
		LockAllTable(LOCK_SHARE);
		if (SaveData(L"Insert16383records.std") != 0) {
			printf("...[NG]\r\n");
			UnlockAllTable();
			return -1;
		}
		UnlockAllTable();
		printf("...[OK]\r\n");
	}

	{
		printf("DeleteRecord(Person-Name=\"�|�� �L��\")�����b�N�����Ŏ��s�����ꍇ�C-1���ԋp����CGetNumOfRecords(L\"Person\")�̒l��16383�̂܂܂ƂȂ�");
		ColumnData* Col[1];
		Col[0] = new ColumnDataWStr(L"Name", L"�|�� �L��");
		RecordData* Rec = new RecordData(L"Person", Col, 1);
		if (DeleteRecord(Rec) != -1) {
			printf("...[NG]\r\n");
			return -1;
		}
		if (GetNumOfRecords(L"Person") != 16383) {
			printf("...[NG]\r\n");
			return -1;
		}
		printf("...[OK]\r\n");


		printf("DeleteRecord(Person-Name=\"�|�� �L��\")�����L���b�N�Ŏ��s�����ꍇ�C-1���ԋp����CGetNumOfRecords(L\"Person\")�̒l��16383�̂܂܂ƂȂ�");
		LockTable(L"Person", LOCK_SHARE);
		if (DeleteRecord(Rec) != -1) {
			printf("...[NG]\r\n");
			return -1;
		}
		UnlockTable(L"Person");
		if (GetNumOfRecords(L"Person") != 16383) {
			printf("...[NG]\r\n");
			return -1;
		}
		printf("...[OK]\r\n");


		printf("DeleteRecord(Person-Name=\"�|�� �L��\")��r�����b�N�Ŏ��s�����ꍇ�C0���ԋp����CGetNumOfRecords(L\"Person\")�̒l��16379�ƂȂ�");
		LockTable(L"Person", LOCK_EXCLUSIVE);
		if (DeleteRecord(Rec) != 0) {
			printf("...[NG]\r\n");
			return -1;
		}
		UnlockTable(L"Person");
		if (GetNumOfRecords(L"Person") != 16379) {
			printf("...[NG]\r\n");
			return -1;
		}
		delete Rec;
		printf("...[OK]\r\n");
	}

	{
		printf("DeleteRecord(L\"Person\"�����b�N�����Ŏ��s�����ꍇ�C-1���ԋp����CGetNumOfRecords(L\"Person\")�̒l��16379�̂܂܂ƂȂ�");
		if (DeleteRecord(L"Person") != -1) {
			printf("...[NG]\r\n");
			return -1;
		}
		if (GetNumOfRecords(L"Person") != 16379) {
			printf("...[NG]\r\n");
			return -1;
		}
		printf("...[OK]\r\n");


		printf("DeleteRecord(L\"Person\"�����L���b�N�Ŏ��s�����ꍇ�C-1���ԋp����CGetNumOfRecords(L\"Person\")�̒l��16379�̂܂܂ƂȂ�");
		LockTable(L"Person", LOCK_SHARE);
		if (DeleteRecord(L"Person") != -1) {
			printf("...[NG]\r\n");
			return -1;
		}
		UnlockTable(L"Person");
		if (GetNumOfRecords(L"Person") != 16379) {
			printf("...[NG]\r\n");
			return -1;
		}
		printf("...[OK]\r\n");
	}


	{
		printf("16383�̃��R�[�h���ɑ��݂���Name=\"�R�I\"�܂���\"�R��\"���܂݁C100 < ID < 500  �̃��R�[�h��Key�J������\"Key exist\"�ɕύX����B");
		RecordData *RecDatGet;
		ColumnData *ColDat[7];
		RecordData* RecDatSch1;
		RecordData* RecDatSch2;
		RecordData* RecDatUpd;

		ColDat[0] = new ColumnDataWStr(L"Name", L"�R�I", COMP_CONTAIN);
		ColDat[1] = new ColumnDataInt(L"ID", 100, COMP_GT);
		ColDat[2] = new ColumnDataInt(L"ID", 500, COMP_LT);
		RecDatSch1 = new RecordData(L"Person", &ColDat[0], 3);

		ColDat[3] = new ColumnDataWStr(L"Name", L"�R��", COMP_CONTAIN);
		ColDat[4] = new ColumnDataInt(L"ID", 100, COMP_GT);
		ColDat[5] = new ColumnDataInt(L"ID", 500, COMP_LT);
		RecDatSch2 = new RecordData(L"Person", &ColDat[3], 3);
		RecDatSch1->SetNextRecord(RecDatSch2);

		ColDat[6] = new ColumnDataStr(L"Key", "Key exist");
		RecDatUpd = new RecordData(L"Person", &ColDat[6], 1);

		LockTable(L"Person", LOCK_EXCLUSIVE);
		UpdateRecord(RecDatSch1, RecDatUpd);
		UnlockTable(L"Person");


		LockTable(L"Person", LOCK_SHARE);
		RecDatGet = GetRecord(L"Person");
		UnlockTable(L"Person");

		if (RecDatGet == NULL) {
			printf("...[NG]\r\n");
			return -1;
		}
		int NumOfKey = 0;
		int NumOfNoKey = 0;
		for (RecordData* CurRecDat = RecDatGet; CurRecDat != NULL; CurRecDat = CurRecDat->GetNextRecord()) {
			ColumnDataWStr* ColName = (ColumnDataWStr*)CurRecDat->GetColumn(L"Name");
			ColumnDataInt* ColId = (ColumnDataInt*)CurRecDat->GetColumn(L"ID");
			ColumnDataStr* ColKey = (ColumnDataStr*)CurRecDat->GetColumn(L"Key");

			if ((StrStr(ColName->GetValue(), L"�R�I") != NULL || StrStr(ColName->GetValue(), L"�R��") != NULL) && ColId->GetValue() > 100 && ColId->GetValue() < 500) {
				if (strcmp(ColKey->GetValue(), "Key exist") != 0) {
					printf("...[NG]\r\n");
					return -1;
				} else {
					NumOfKey++;
				}
			} else {
				if (strcmp(ColKey->GetValue(), "No Key") != 0) {
					printf("...[NG]\r\n");
					return -1;
				} else {
					NumOfNoKey++;
				}
			}
		}
		printf("(Key=%d, NoKey=%d)...[OK]\r\n", NumOfKey, NumOfNoKey);


		printf("16383�̃��R�[�h���ɑ��݂���Name=\"�R�I\"�܂���\"�R��\"���܂݁C100 < ID < 500  �̃��R�[�h���폜����B");
		if (GetNumOfRecords(L"Person") != 16379) {
			printf("...[NG]\r\n");
			return -1;
		}
		LockTable(L"Person", LOCK_EXCLUSIVE);
		DeleteRecord(RecDatSch1);
		UnlockTable(L"Person");
		int Rest = GetNumOfRecords(L"Person");
		if (Rest != (16379 - NumOfKey)) {
			printf("...[NG]\r\n");
			return -1;
		}
		printf("(Deleted count = %d, Rest = %d)...[OK]\r\n", NumOfKey, Rest);

		delete RecDatSch1;
		delete RecDatUpd;
		delete RecDatGet;
	}


	{
		printf("DeleteRecord(L\"Person\"��r�����b�N�Ŏ��s�����ꍇ�C0���ԋp����CGetNumOfRecords(L\"Person\"))�̒l��0�ƂȂ�");
		LockTable(L"Person", LOCK_EXCLUSIVE);
		if (DeleteRecord(L"Person") != 0) {
			printf("...[NG]\r\n");
			return -1;
		}
		UnlockTable(L"Person");
		if (GetNumOfRecords(L"Person") != 0) {
			printf("...[NG]\r\n");
			return -1;
		}
		printf("...[OK]\r\n");


		printf("�ēxDeleteRecord(L\"Person\"��r�����b�N�Ŏ��s�����ꍇ�C���͂�Ώۃe�[�u�������݂��Ȃ�����-1���ԋp�����");
		LockTable(L"Person", LOCK_EXCLUSIVE);
		if (DeleteRecord(L"Person") != 0) {
			printf("...[NG]\r\n");
			return -1;
		}
		UnlockTable(L"Person");
		printf("...[OK]\r\n");
	}


	{
		printf("DeleteTable(\"Person\")�Ńe�[�u�����폜���邱�Ƃ��ł���");
		if (DeleteTable(L"Person") != 0) {
			printf("...[NG]\r\n");
			return -1;
		}
		printf("...[OK]\r\n");
	}

	return 0;
}
