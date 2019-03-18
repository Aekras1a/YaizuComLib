﻿#include "../../src/stkpl/StkPl.h"
#include "../../src/stkdata/stkdata.h"
#include "../../src/stkdata/stkdataapi.h"


int Insert16383Records()
{
	StkPlPrintf("Person table(Name:WStr(10), ID;Integer, Address:WStr(15), Key:Str(10), Height:Float) Max=16383 can be generated by CreateTable.");
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
		StkPlPrintf("...[NG]\r\n");
		return -1;
	}
	StkPlPrintf("...[OK]\r\n");


	StkPlPrintf("16383 records can be added to Person table with 16383 repeat of InsertRecord.");
	wchar_t Lname[10][5] = {	L"鈴木", L"木村", L"山田", L"田中", L"佐々木",
							L"秋山", L"高橋", L"長谷川", L"渡辺", L"伊藤"
	};
	wchar_t Fname[10][5] = {	L"和人", L"明子", L"達也", L"今日子", L"智",
							L"由美", L"健一", L"亜美", L"琢磨", L"由紀"
	};
	wchar_t Pref[7][15] = {L"東京都", L"神奈川県", L"茨城県", L"埼玉県", L"千葉県", L"栃木県", L"山梨"};
	ColumnData *ColDat1[5];
	RecordData *CurRecDat;
	for (int i = 0; i < 16383; i++) {
		wchar_t Name[10];
		StkPlSwPrintf(Name, 10, L"%ls %ls", Lname[StkPlRand() % 10], Fname[StkPlRand() % 10]);
		if (i % 5000 == 0) {
			ColDat1[0] = new ColumnDataWStr(L"Name", L"竹内 伸也");
		} else {
			ColDat1[0] = new ColumnDataWStr(L"Name", Name);
		}
		ColDat1[1] = new ColumnDataInt(L"ID", i);
		wchar_t Address[15];
		StkPlSwPrintf(Address, 15, L"%ls%d", Pref[StkPlRand() % 7], StkPlRand() % 10000);
		ColDat1[2] = new ColumnDataWStr(L"Address", Address);
		ColDat1[3] = new ColumnDataStr(L"Key", "No Key");
		ColDat1[4] = new ColumnDataFloat(L"Height", (float)(150.0f + (StkPlRand() % 500) / 10.0f));
		CurRecDat = new RecordData(L"Person", ColDat1, 5);
		LockTable(L"Person", 2);
		if (InsertRecord(CurRecDat) != 0) {
			UnlockTable(L"Person");
			StkPlPrintf("...[NG]\r\n");
			delete CurRecDat;
			return -1;
		}
		UnlockTable(L"Person");
		delete CurRecDat;
	}
	StkPlPrintf("...[OK]\r\n");


	{
		StkPlPrintf("-1 is returned if sorting of (AzSortRecord(L\"Person\", L\"ID\")) is performed without locking.");
		if (AzSortRecord(L"Person", L"ID") != -1) {
			StkPlPrintf("...[NG]\r\n");
			return -1;
		}
		StkPlPrintf("...[OK]\r\n");


		StkPlPrintf("-1 is returned if sorting of (ZaSortRecord(L\"Person\", L\"ID\")) is performed without locking.");
		if (ZaSortRecord(L"Person", L"ID") != -1) {
			StkPlPrintf("...[NG]\r\n");
			return -1;
		}
		StkPlPrintf("...[OK]\r\n");


		StkPlPrintf("-1 is returned if sorting of (AzSortRecord(L\"Person\", L\"ID\")) is performed after shared lock.");
		LockTable(L"Person", LOCK_SHARE);
		if (AzSortRecord(L"Person", L"ID") != -1) {
			UnlockTable(L"Person");
			StkPlPrintf("...[NG]\r\n");
			return -1;
		}
		UnlockTable(L"Person");
		StkPlPrintf("...[OK]\r\n");


		StkPlPrintf("-1 is returned if sorting of (ZaSortRecord(L\"Person\", L\"ID\")) is performed after shared lock.");
		LockTable(L"Person", LOCK_SHARE);
		if (ZaSortRecord(L"Person", L"ID") != -1) {
			UnlockTable(L"Person");
			StkPlPrintf("...[NG]\r\n");
			return -1;
		}
		UnlockTable(L"Person");
		StkPlPrintf("...[OK]\r\n");


		StkPlPrintf("0 is returned if sorting of (AzSortRecord(L\"Person\", L\"ID\")) is performed after exclusive lock.");
		LockTable(L"Person", LOCK_EXCLUSIVE);
		if (AzSortRecord(L"Person", L"ID") != 0) {
			UnlockTable(L"Person");
			StkPlPrintf("...[NG]\r\n");
			return -1;
		}
		UnlockTable(L"Person");
		StkPlPrintf("...[OK]\r\n");


		StkPlPrintf("0 is returned if sorting of (ZaSortRecord(\"Person\", L\"ID\")) is performed after exclusive lock.");
		LockTable(L"Person", LOCK_EXCLUSIVE);
		if (ZaSortRecord(L"Person", L"ID") != 0) {
			UnlockTable(L"Person");
			StkPlPrintf("...[NG]\r\n");
			return -1;
		}
		UnlockTable(L"Person");
		StkPlPrintf("...[OK]\r\n");
	}


	{
		StkPlPrintf("Connected 16383 records can be acquired by GetRecord(table name specification) from 16383 records which are added.");
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
			StkPlPrintf("...[NG]\r\n");
			return -1;
		}
		delete RecDatGet;
		StkPlPrintf("...[OK]\r\n");
	}


	{
		StkPlPrintf("Target records can be acquired if particular name and 1000 < ID < 2000 criteria is presented from 16383 records.");
		bool Err = false;
		int FndCnt = 0;
		RecordData *RecDatGet;
		ColumnData *ColDatTake[6];
		RecordData* RecDatKim;
		RecordData* RecDatTan;

		ColDatTake[0] = new ColumnDataWStr(L"Name", L"木村", COMP_CONTAIN);
		ColDatTake[1] = new ColumnDataInt(L"ID", 1000, COMP_GT);
		ColDatTake[2] = new ColumnDataInt(L"ID", 2000, COMP_LT);
		RecDatKim = new RecordData(L"Person", &ColDatTake[0], 3);

		ColDatTake[3] = new ColumnDataWStr(L"Name", L"田中", COMP_CONTAIN);
		ColDatTake[4] = new ColumnDataInt(L"ID", 1000, COMP_GT);
		ColDatTake[5] = new ColumnDataInt(L"ID", 2000, COMP_LT);
		RecDatTan = new RecordData(L"Person", &ColDatTake[3], 3);
		RecDatKim->SetNextRecord(RecDatTan);

		LockTable(L"Person", 1);
		RecDatGet = GetRecord(RecDatKim);
		UnlockTable(L"Person");

		if (RecDatGet == NULL) {
			StkPlPrintf("...[NG]\r\n");
			return -1;
		}
		int NumOfFnd = 0;
		for (RecordData* CurRecDat = RecDatGet; CurRecDat != NULL; CurRecDat = CurRecDat->GetNextRecord()) {
			ColumnDataWStr* ColName = (ColumnDataWStr*)CurRecDat->GetColumn(L"Name");
			if (StkPlWcsStr(ColName->GetValue(), L"木村") == NULL && StkPlWcsStr(ColName->GetValue(), L"田中") == NULL ) {
				StkPlPrintf("...[NG]\r\n");
				return -1;
			}
			ColumnDataInt* ColId = (ColumnDataInt*)CurRecDat->GetColumn(L"ID");
			if (ColId->GetValue() <= 1000 && ColId->GetValue() >= 2000) {
				StkPlPrintf("...[NG]\r\n");
				return -1;
			}
			NumOfFnd++;
		}
		delete RecDatKim;
		delete RecDatGet;
		StkPlPrintf("...%d records found [OK]\r\n", NumOfFnd);
	}


	{
		StkPlPrintf("4 records can be acquired by GetRecord search criteria from 16383 records that are added.");
		bool Err = false;
		int FndCnt = 0;
		RecordData *RecDatGet;
		ColumnData *ColDatTake[1];
		ColDatTake[0] = new ColumnDataWStr(L"Name", L"竹内 伸也");
		RecordData RecDatTake(L"Person", ColDatTake, 1);
		LockTable(L"Person", 1);
		RecDatGet = GetRecord(&RecDatTake);
		UnlockTable(L"Person");
		while (RecDatGet) {
			ColumnDataWStr *ColDatName = (ColumnDataWStr*)(RecDatGet->GetColumn(0));
			wchar_t *Name = ColDatName->GetValue();
			if (StkPlWcsCmp(Name, L"竹内 伸也") != 0) {
				StkPlPrintf("...[NG]\r\n");
				return -1;
			}
			FndCnt++;
			RecDatGet = RecDatGet->GetNextRecord();
		}
		if (FndCnt != 4) {
			StkPlPrintf("...[NG]\r\n");
			return -1;
		}
		delete RecDatGet;
		StkPlPrintf("...[OK]\r\n");
	}

	{
		StkPlPrintf("No record is returned as a result of GetRecord if non existing record in 16383 records is specified as criterion.");
		RecordData *RecDatGet;
		ColumnData *ColDat[1];
		ColDat[0] = new ColumnDataWStr(L"Name", L"ジョージ ブッシュ");
		RecordData RecDat(L"Person", ColDat, 1);
		LockTable(L"Person", 1);
		RecDatGet = GetRecord(&RecDat);
		UnlockTable(L"Person");
		if (RecDatGet != NULL) {
			StkPlPrintf("...[NG]\r\n");
			return -1;
		}
		delete RecDatGet;
		StkPlPrintf("...[OK]\r\n");
	}

	{
		StkPlPrintf("Number of records which is acquired by GetNumOfRecords(\"Person\") shows 16383.");
		if (GetNumOfRecords(L"Person") != 16383) {
			StkPlPrintf("...[NG]\r\n");
			return -1;
		}
		StkPlPrintf("...[OK]\r\n");
	}

	{
		StkPlPrintf("Number of records which is acquired by GetMaxNumOfRecords(\"Person\") shows 16383.");
		if (GetMaxNumOfRecords(L"Person") != 16383) {
			StkPlPrintf("...[NG]\r\n");
			return -1;
		}
		StkPlPrintf("...[OK]\r\n");
	}

	{
		StkPlPrintf("Preserve table information to\"Insert16383records.std\".");
		LockAllTable(LOCK_SHARE);
		if (SaveData(L"Insert16383records.std") != 0) {
			StkPlPrintf("...[NG]\r\n");
			UnlockAllTable();
			return -1;
		}
		UnlockAllTable();
		StkPlPrintf("...[OK]\r\n");
	}

	{
		StkPlPrintf("In case DeleteRecord(Person-Name=existing name) is executed without lock, -1 is returned and GetNumOfRecords(L\"Person\") returns 16383.");
		ColumnData* Col[1];
		Col[0] = new ColumnDataWStr(L"Name", L"竹内 伸也");
		RecordData* Rec = new RecordData(L"Person", Col, 1);
		if (DeleteRecord(Rec) != -1) {
			StkPlPrintf("...[NG]\r\n");
			return -1;
		}
		if (GetNumOfRecords(L"Person") != 16383) {
			StkPlPrintf("...[NG]\r\n");
			return -1;
		}
		StkPlPrintf("...[OK]\r\n");


		StkPlPrintf("In case DeleteRecord(Person-Name=existing name) is executed with shared lock, -1 is returned and GetNumOfRecords(L\"Person\") returns 16383.");
		LockTable(L"Person", LOCK_SHARE);
		if (DeleteRecord(Rec) != -1) {
			StkPlPrintf("...[NG]\r\n");
			return -1;
		}
		UnlockTable(L"Person");
		if (GetNumOfRecords(L"Person") != 16383) {
			StkPlPrintf("...[NG]\r\n");
			return -1;
		}
		StkPlPrintf("...[OK]\r\n");


		StkPlPrintf("In case DeleteRecord(Person-Name=same name of previous execution) is executed with exclusive lock, 0 is returned and GetNumOfRecords(L\"Person\") returns 16379.");
		LockTable(L"Person", LOCK_EXCLUSIVE);
		if (DeleteRecord(Rec) != 0) {
			StkPlPrintf("...[NG]\r\n");
			return -1;
		}
		UnlockTable(L"Person");
		if (GetNumOfRecords(L"Person") != 16379) {
			StkPlPrintf("...[NG]\r\n");
			return -1;
		}
		delete Rec;
		StkPlPrintf("...[OK]\r\n");
	}

	{
		StkPlPrintf("In case DeleteRecord(L\"Person\") is executed without lock, -1 is returned and GetNumOfRecords(L\"Person\") returns 16379.");
		if (DeleteRecord(L"Person") != -1) {
			StkPlPrintf("...[NG]\r\n");
			return -1;
		}
		if (GetNumOfRecords(L"Person") != 16379) {
			StkPlPrintf("...[NG]\r\n");
			return -1;
		}
		StkPlPrintf("...[OK]\r\n");


		StkPlPrintf("In case DeleteRecord(L\"Person\") is executed with shared lock, -1 is returned and GetNumOfRecords(L\"Person\") returns 16379.");
		LockTable(L"Person", LOCK_SHARE);
		if (DeleteRecord(L"Person") != -1) {
			StkPlPrintf("...[NG]\r\n");
			return -1;
		}
		UnlockTable(L"Person");
		if (GetNumOfRecords(L"Person") != 16379) {
			StkPlPrintf("...[NG]\r\n");
			return -1;
		}
		StkPlPrintf("...[OK]\r\n");
	}


	{
		StkPlPrintf("Change the value of 'Key' column into 'Key exist' in the condition that 16383 records contains particular name in multibyte  and ID is in the scope of 100 < ID < 500.");
		RecordData *RecDatGet;
		ColumnData *ColDat[7];
		RecordData* RecDatSch1;
		RecordData* RecDatSch2;
		RecordData* RecDatUpd;

		ColDat[0] = new ColumnDataWStr(L"Name", L"由紀", COMP_CONTAIN);
		ColDat[1] = new ColumnDataInt(L"ID", 100, COMP_GT);
		ColDat[2] = new ColumnDataInt(L"ID", 500, COMP_LT);
		RecDatSch1 = new RecordData(L"Person", &ColDat[0], 3);

		ColDat[3] = new ColumnDataWStr(L"Name", L"由美", COMP_CONTAIN);
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
			StkPlPrintf("...[NG]\r\n");
			return -1;
		}
		int NumOfKey = 0;
		int NumOfNoKey = 0;
		for (RecordData* CurRecDat = RecDatGet; CurRecDat != NULL; CurRecDat = CurRecDat->GetNextRecord()) {
			ColumnDataWStr* ColName = (ColumnDataWStr*)CurRecDat->GetColumn(L"Name");
			ColumnDataInt* ColId = (ColumnDataInt*)CurRecDat->GetColumn(L"ID");
			ColumnDataStr* ColKey = (ColumnDataStr*)CurRecDat->GetColumn(L"Key");

			if ((StkPlWcsStr(ColName->GetValue(), L"由紀") != NULL || StkPlWcsStr(ColName->GetValue(), L"由美") != NULL) && ColId->GetValue() > 100 && ColId->GetValue() < 500) {
				if (StkPlStrCmp(ColKey->GetValue(), "Key exist") != 0) {
					StkPlPrintf("...[NG]\r\n");
					return -1;
				} else {
					NumOfKey++;
				}
			} else {
				if (StkPlStrCmp(ColKey->GetValue(), "No Key") != 0) {
					StkPlPrintf("...[NG]\r\n");
					return -1;
				} else {
					NumOfNoKey++;
				}
			}
		}
		StkPlPrintf("(Key=%d, NoKey=%d)...[OK]\r\n", NumOfKey, NumOfNoKey);


		StkPlPrintf("The records are deleted in the condition that 16383 records contains particular name in multibyte  and ID is in the scope of 100 < ID < 500.");
		if (GetNumOfRecords(L"Person") != 16379) {
			StkPlPrintf("...[NG]\r\n");
			return -1;
		}
		LockTable(L"Person", LOCK_EXCLUSIVE);
		DeleteRecord(RecDatSch1);
		UnlockTable(L"Person");
		int Rest = GetNumOfRecords(L"Person");
		if (Rest != (16379 - NumOfKey)) {
			StkPlPrintf("...[NG]\r\n");
			return -1;
		}
		StkPlPrintf("(Deleted count = %d, Rest = %d)...[OK]\r\n", NumOfKey, Rest);

		delete RecDatSch1;
		delete RecDatUpd;
		delete RecDatGet;
	}


	{
		StkPlPrintf("The value of GetNumOfRecords(L\"Person\") becomes zero because zero is returned if DeleteRecord(L\"Person\") is executed with exclusive lock.");
		LockTable(L"Person", LOCK_EXCLUSIVE);
		if (DeleteRecord(L"Person") != 0) {
			StkPlPrintf("...[NG]\r\n");
			return -1;
		}
		UnlockTable(L"Person");
		if (GetNumOfRecords(L"Person") != 0) {
			StkPlPrintf("...[NG]\r\n");
			return -1;
		}
		StkPlPrintf("...[OK]\r\n");


		StkPlPrintf("-1 is returned due to target table not exist in case DeleteRecord(L\"Person\") is executed with exclusive lock again.");
		LockTable(L"Person", LOCK_EXCLUSIVE);
		if (DeleteRecord(L"Person") != 0) {
			StkPlPrintf("...[NG]\r\n");
			return -1;
		}
		UnlockTable(L"Person");
		StkPlPrintf("...[OK]\r\n");
	}


	{
		StkPlPrintf("Table can be deleted using DeleteTable(\"Person\").");
		if (DeleteTable(L"Person") != 0) {
			StkPlPrintf("...[NG]\r\n");
			return -1;
		}
		StkPlPrintf("...[OK]\r\n");
	}

	return 0;
}
