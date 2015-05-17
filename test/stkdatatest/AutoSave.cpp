#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include "..\..\src\stkdata\stkdata.h"


int AutoSaveTest()
{
	printf("AutoSave(�Ԋu=30�b, �o��=AutoSave.std)���J�n����");
	if (AutoSave(_T("AutoSave.std"), 30, TRUE) != 0) {
		printf("...[NG]\r\n");
		return -1;
	}
	printf("...[OK]\r\n");


	for (int Loop = 0; Loop < 30; Loop++) {
		if (Loop == 5) {
			printf("AutoSave(30�b�Ԋu)�J�n��50�b���Person�e�[�u�����쐬����");
			ColumnDefWStr ColDefName(_T("Name"), 50);
			ColumnDefInt ColDefAge(_T("Age"));
			TableDef TabDefPerson(_T("Person"), 16383);
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
			ColDat[0] = new ColumnDataWStr(_T("Name"), _T("Shinya Takeuchi"));
			ColDat[1] = new ColumnDataInt(_T("Age"), 35);
			RecordData* RecDat = new RecordData(_T("Person"), ColDat, 2);
			LockTable(_T("Person"), LOCK_EXCLUSIVE);
			if (InsertRecord(RecDat) != 0) {
				UnlockTable(_T("Person"));
				ClearRecordData(RecDat);
				printf("...[NG]\r\n");
				return -1;
			}
			UnlockTable(_T("Person"));
			ClearRecordData(RecDat);
			printf("...[OK]\r\n");
		}


		if (Loop == 11) {
			printf("AutoSave(30�b�Ԋu)�J�n��110�b���Akemi Tsunemi, 38��InsertRecord�Œǉ�����");
			ColumnData* ColDat[2];
			ColDat[0] = new ColumnDataWStr(_T("Name"), _T("Akemi Tsunemi"));
			ColDat[1] = new ColumnDataInt(_T("Age"), 38);
			RecordData* RecDat = new RecordData(_T("Person"), ColDat, 2);
			LockTable(_T("Person"), LOCK_EXCLUSIVE);
			if (InsertRecord(RecDat) != 0) {
				UnlockTable(_T("Person"));
				ClearRecordData(RecDat);
				printf("...[NG]\r\n");
				return -1;
			}
			UnlockTable(_T("Person"));
			ClearRecordData(RecDat);
			printf("...[OK]\r\n");
		}


		if (Loop == 15) {
			printf("AutoSave(30�b�Ԋu)�J�n��150�b���Joe Satriani, 50��InsertRecord�Œǉ�����");
			ColumnData* ColDat[2];
			ColDat[0] = new ColumnDataWStr(_T("Name"), _T("Joe Satriani"));
			ColDat[1] = new ColumnDataInt(_T("Age"), 50);
			RecordData* RecDat = new RecordData(_T("Person"), ColDat, 2);
			LockTable(_T("Person"), LOCK_EXCLUSIVE);
			if (InsertRecord(RecDat) != 0) {
				UnlockTable(_T("Person"));
				ClearRecordData(RecDat);
				printf("...[NG]\r\n");
				return -1;
			}
			UnlockTable(_T("Person"));
			ClearRecordData(RecDat);
			printf("...[OK]\r\n");
		}


		if (Loop == 20) {
			printf("AutoSave(30�b�Ԋu)�J�n��200�b���AutoSave���~����");
			if (AutoSave(_T("AutoSave.std"), 30, FALSE) != 0) {
				printf("...[NG]\r\n");
				return -1;
			}
			printf("...[OK]\r\n");
		}

		if (Loop == 21) {
			printf("AutoSave��~��Steve Vail, 45��InsertRecord�Œǉ�����");
			ColumnData* ColDat[2];
			ColDat[0] = new ColumnDataWStr(_T("Name"), _T("Steve Vai"));
			ColDat[1] = new ColumnDataInt(_T("Age"), 45);
			RecordData* RecDat = new RecordData(_T("Person"), ColDat, 2);
			LockTable(_T("Person"), LOCK_EXCLUSIVE);
			if (InsertRecord(RecDat) != 0) {
				UnlockTable(_T("Person"));
				ClearRecordData(RecDat);
				printf("...[NG]\r\n");
				return -1;
			}
			UnlockTable(_T("Person"));
			ClearRecordData(RecDat);
			printf("...[OK]\r\n");
		}

		Sleep(10000);
	}

	printf("AutoSave�ŕۑ������f�[�^(AutoSave.std)��ǂݍ��݁C3���̃��R�[�h�����݂��邱�Ƃ��m�F����");
	LockAllTable(LOCK_EXCLUSIVE);
	if (LoadData(_T("AutoSave.std")) != 0) {
		printf("...[NG]\r\n");
		return -1;
	}
	LockAllTable(LOCK_EXCLUSIVE);
	UnlockAllTable();
	if (GetNumOfRecords(_T("Person")) != 3) {
		printf("...[NG]\r\n");
		return -1;
	}
	printf("...[OK]\r\n");

	return 0;
}
