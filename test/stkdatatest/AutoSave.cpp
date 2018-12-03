#include <windows.h>
#include <stdio.h>
#include "..\..\src\stkdata\stkdata.h"
#include "..\..\src\stkdata\stkdataapi.h"


int AutoSaveTest()
{
	printf("AutoSave(�Ԋu=30�b, �o��=AutoSave.std)���J�n����");
	if (AutoSave(L"AutoSave.std", 30, true) != 0) {
		printf("...[NG]\r\n");
		return -1;
	}
	printf("...[OK]\r\n");


	for (int Loop = 0; Loop < 30; Loop++) {
		if (Loop == 5) {
			printf("AutoSave(30�b�Ԋu)�J�n��50�b���Person�e�[�u�����쐬����");
			ColumnDefWStr ColDefName(L"Name", 50);
			ColumnDefInt ColDefAge(L"Age");
			TableDef TabDefPerson(L"Person", 16383);
			TabDefPerson.AddColumnDef(&ColDefName);
			TabDefPerson.AddColumnDef(&ColDefAge);
			if (CreateTable(&TabDefPerson) != 0) {
				printf("...[NG]\r\n");
				return -1;
			}
			printf("...[OK]\r\n");
		}


		if (Loop == 10) {
			printf("AutoSave(30�b�Ԋu)�J�n��100�b���Shinya Takeuchi, 35��InsertRecord�Œǉ�����");
			ColumnData* ColDat[2];
			ColDat[0] = new ColumnDataWStr(L"Name", L"Shinya Takeuchi");
			ColDat[1] = new ColumnDataInt(L"Age", 35);
			RecordData* RecDat = new RecordData(L"Person", ColDat, 2);
			LockTable(L"Person", LOCK_EXCLUSIVE);
			if (InsertRecord(RecDat) != 0) {
				UnlockTable(L"Person");
				delete RecDat;
				printf("...[NG]\r\n");
				return -1;
			}
			UnlockTable(L"Person");
			delete RecDat;
			printf("...[OK]\r\n");
		}


		if (Loop == 11) {
			printf("AutoSave(30�b�Ԋu)�J�n��110�b���Akemi Tsunemi, 38��InsertRecord�Œǉ�����");
			ColumnData* ColDat[2];
			ColDat[0] = new ColumnDataWStr(L"Name", L"Akemi Tsunemi");
			ColDat[1] = new ColumnDataInt(L"Age", 38);
			RecordData* RecDat = new RecordData(L"Person", ColDat, 2);
			LockTable(L"Person", LOCK_EXCLUSIVE);
			if (InsertRecord(RecDat) != 0) {
				UnlockTable(L"Person");
				delete RecDat;
				printf("...[NG]\r\n");
				return -1;
			}
			UnlockTable(L"Person");
			delete RecDat;
			printf("...[OK]\r\n");
		}


		if (Loop == 15) {
			printf("AutoSave(30�b�Ԋu)�J�n��150�b���Joe Satriani, 50��InsertRecord�Œǉ�����");
			ColumnData* ColDat[2];
			ColDat[0] = new ColumnDataWStr(L"Name", L"Joe Satriani");
			ColDat[1] = new ColumnDataInt(L"Age", 50);
			RecordData* RecDat = new RecordData(L"Person", ColDat, 2);
			LockTable(L"Person", LOCK_EXCLUSIVE);
			if (InsertRecord(RecDat) != 0) {
				UnlockTable(L"Person");
				delete RecDat;
				printf("...[NG]\r\n");
				return -1;
			}
			UnlockTable(L"Person");
			delete RecDat;
			printf("...[OK]\r\n");
		}


		if (Loop == 20) {
			printf("AutoSave(30�b�Ԋu)�J�n��200�b���AutoSave���~����");
			if (AutoSave(L"AutoSave.std", 30, false) != 0) {
				printf("...[NG]\r\n");
				return -1;
			}
			printf("...[OK]\r\n");
		}

		if (Loop == 21) {
			printf("AutoSave��~��Steve Vail, 45��InsertRecord�Œǉ�����");
			ColumnData* ColDat[2];
			ColDat[0] = new ColumnDataWStr(L"Name", L"Steve Vai");
			ColDat[1] = new ColumnDataInt(L"Age", 45);
			RecordData* RecDat = new RecordData(L"Person", ColDat, 2);
			LockTable(L"Person", LOCK_EXCLUSIVE);
			if (InsertRecord(RecDat) != 0) {
				UnlockTable(L"Person");
				delete RecDat;
				printf("...[NG]\r\n");
				return -1;
			}
			UnlockTable(L"Person");
			delete RecDat;
			printf("...[OK]\r\n");
		}

		Sleep(10000);
	}

	printf("AutoSave�ŕۑ������f�[�^(AutoSave.std)��ǂݍ��݁C3���̃��R�[�h�����݂��邱�Ƃ��m�F����");
	LockAllTable(LOCK_EXCLUSIVE);
	if (LoadData(L"AutoSave.std") != 0) {
		printf("...[NG]\r\n");
		return -1;
	}
	LockAllTable(LOCK_EXCLUSIVE);
	UnlockAllTable();
	if (GetNumOfRecords(L"Person") != 3) {
		printf("...[NG]\r\n");
		return -1;
	}
	printf("...[OK]\r\n");

	return 0;
}
