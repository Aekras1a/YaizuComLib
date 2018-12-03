#include <windows.h>
#include <stdio.h>
#include "..\..\src\stkdata\stkdata.h"
#include "..\..\src\stkdata\stkdataapi.h"

/*
TableVersion
�E"���i"�e�[�u��, "�ڋq"�e�[�u���𐶐�����O��GetTableVersion(L"���i")�܂���GetTableVersion(L"�ڋq")�Ăяo����-1���Ԃ�
�ECreateTable��"���i"�e�[�u�����ő僌�R�[�h=500�Ƃ��Đ������邱�Ƃ��ł���
�ECreateTable��"�ڋq"�e�[�u�����ő僌�R�[�h=5000�Ƃ��Đ������邱�Ƃ��ł���
�E"���i"�e�[�u��, "�ڋq"�e�[�u���𐶐����GetTableVersion(L"���i")�܂���GetTableVersion(L"�ڋq")�Ăяo����0���Ԃ�
�EInsertRecord�Ńe�[�u��"�ڋq"��1���R�[�h�ǉ���CGetTableVersion("�ڋq")��1���ԋp�����BGetTableVersion("���i")��0�̂܂�
�EInsertRecord�Ńe�[�u��"�ڋq"�ɑ��݂��Ȃ��J�������w�肵�Ă����R�[�h�͒ǉ����ꂸ�CGetTableVersion("�ڋq")��1���ԋp�����BGetTableVersion("���i")��0�̂܂�
�EUpdateRecord�Ńe�[�u��"�ڋq"��1���R�[�h�i2�J�������j���X�V��CGetTableVersion("�ڋq")��2���ԋp�����BGetTableVersion("���i")��0�̂܂�
�EGetRecord�Ńe�[�u��"�ڋq"��1���R�[�h���擾��CGetTableVersion("�ڋq")��2���ԋp�����BGetTableVersion("���i")��0�̂܂�
�EDeleteRecord�Ńe�[�u��"�ڋq"��1���R�[�h���폜��CGetTableVersion("�ڋq")��3���ԋp�����BGetTableVersion("���i")��0�̂܂�
�EInsertRecord��5���R�[�h���i��2���R�[�h�͕s���j�ǉ���CGetTableVersion("�ڋq")��3���ԋp����CGetTableVersion("���i")��3���ԋp�����
�EUpdateRecord"���i"(Search=�����J�����w��:�������s��, Update=�����J�����w��:�K��)��CGetTableVersion("�ڋq")��3���ԋp����CGetTableVersion("���i")��3���ԋp�����
�EUpdateRecord"���i"(Search=�����J�����w��:������3���R�[�h�w��Ō���, Update=�����J�����w��:�������s��)��CGetTableVersion("�ڋq")��3���ԋp����CGetTableVersion("���i")��3���ԋp�����
�EUpdateRecord"���i"��3���R�[�h�X�V(Search=�����J�����w��, Update=�����J�����w��)��CGetTableVersion("�ڋq")��3���ԋp����CGetTableVersion("���i")��6���ԋp�����
�ESaveData��CGetTableVersion("�ڋq")��3���ԋp����CGetTableVersion("���i")��6���ԋp�����
�ELoadData��CGetTableVersion("�ڋq")��0���ԋp����CGetTableVersion("���i")��0���ԋp�����
�EDeleteTable(L"���i")�Ńe�[�u�����폜��CGetTableVersion(L"���i")��-1���Ԃ�CGetTableVersion(L"�ڋq")��-1�ȊO���Ԃ�
�E�����DeleteTable(L"�ڋq")�Ńe�[�u�����폜��CGetTableVersion(L"���i")�CGetTableVersion(L"�ڋq")�Ƃ���-1���Ԃ�
*/
int TableVersion()
{
	// "���i"�e�[�u��, "�ڋq"�e�[�u���𐶐�����O��GetTableVersion(L"���i")�܂���GetTableVersion(L"�ڋq")�Ăяo����-1���Ԃ�
	{
		printf("\"���i\"�e�[�u��, \"�ڋq\"�e�[�u���𐶐�����O��GetTableVersion(L\"���i\")�܂���GetTableVersion(L\"�ڋq\")�Ăяo����-1���Ԃ�");
		if (GetTableVersion(L"���i") != -1 || GetTableVersion(L"�ڋq") != -1) {
			printf("...[NG]\r\n");
			return -1;
		}
	}
	printf("...[OK]\r\n");

	// CreateTable��"���i"�e�[�u�����ő僌�R�[�h=500�Ƃ��Đ������邱�Ƃ��ł���
	{
		printf("CreateTable��\"���i\"�e�[�u�����ő僌�R�[�h=500�Ƃ��Đ������邱�Ƃ��ł���");
		ColumnDefInt ColDefId(L"���i�ԍ�");
		ColumnDefWStr ColDefName(L"���i��", 10);
		ColumnDefInt ColDefPrice(L"�l�i");
		ColumnDefInt ColDefCount(L"�݌ɐ�");
		TableDef TabDefMarc(L"���i", 500);
		TabDefMarc.AddColumnDef(&ColDefId);
		TabDefMarc.AddColumnDef(&ColDefName);
		TabDefMarc.AddColumnDef(&ColDefPrice);
		TabDefMarc.AddColumnDef(&ColDefCount);
		if (CreateTable(&TabDefMarc) != 0) {
			printf("...[NG]\r\n");
			return -1;
		}
	}
	printf("...[OK]\r\n");

	// CreateTable��"�ڋq"�e�[�u�����ő僌�R�[�h=5000�Ƃ��Đ������邱�Ƃ��ł���
	{
		printf("CreateTable��\"�ڋq\"�e�[�u�����ő僌�R�[�h=5000�Ƃ��Đ������邱�Ƃ��ł���");
		ColumnDefWStr ColDefName(L"����", 10);
		ColumnDefWStr ColDefAddr(L"�Z��", 20);
		ColumnDefStr ColDefTel(L"�d�b�ԍ�", 20);
		TableDef TabDefCustomer(L"�ڋq", 5000);
		TabDefCustomer.AddColumnDef(&ColDefName);
		TabDefCustomer.AddColumnDef(&ColDefAddr);
		TabDefCustomer.AddColumnDef(&ColDefTel);
		if (CreateTable(&TabDefCustomer) != 0) {
			printf("...[NG]\r\n");
			return -1;
		}
	}
	printf("...[OK]\r\n");

	// "���i"�e�[�u��, "�ڋq"�e�[�u���𐶐����GetTableVersion(L"���i")�܂���GetTableVersion(L"�ڋq")�Ăяo����0���Ԃ�
	{
		printf("\"���i\"�e�[�u��, \"�ڋq\"�e�[�u���𐶐����GetTableVersion(L\"���i\")�܂���GetTableVersion(L\"�ڋq\")�Ăяo����0���Ԃ�");
		if (GetTableVersion(L"���i") != 0 || GetTableVersion(L"�ڋq") != 0) {
			printf("...[NG]\r\n");
			return -1;
		}
	}
	printf("...[OK]\r\n");

	// InsertRecord�Ńe�[�u��"�ڋq"��1���R�[�h�ǉ���CGetTableVersion("�ڋq")��1���ԋp�����BGetTableVersion("���i")��0�̂܂�
	{
		printf("InsertRecord�Ńe�[�u��\"�ڋq\"��1���R�[�h�ǉ���CGetTableVersion(\"�ڋq\")��1���ԋp�����BGetTableVersion(\"���i\")��0�̂܂�");
		ColumnData *ColDat[10];
		ColDat[0] = new ColumnDataWStr(L"����", L"�|���L��");
		ColDat[1] = new ColumnDataWStr(L"�Z��", L"�É����ĒÎs");
		ColDat[2] = new ColumnDataStr(L"�d�b�ԍ�", "111-222-3333");
		RecordData *RecDat = new RecordData(L"�ڋq", ColDat, 3);
		LockTable(L"�ڋq", LOCK_EXCLUSIVE);
		InsertRecord(RecDat);
		UnlockTable(L"�ڋq");
		delete RecDat;
		if (GetTableVersion(L"���i") != 0 || GetTableVersion(L"�ڋq") != 1) {
			printf("...[NG]\r\n");
			return -1;
		}
	}
	printf("...[OK]\r\n");

	// InsertRecord�Ńe�[�u��"�ڋq"�ɑ��݂��Ȃ��J�������w�肵�Ă����R�[�h�͒ǉ����ꂸ�CGetTableVersion("�ڋq")��1���ԋp�����BGetTableVersion("���i")��0�̂܂�
	{
		printf("InsertRecord�Ńe�[�u��\"�ڋq\"�ɑ��݂��Ȃ��J�������w�肵�Ă����R�[�h�͒ǉ����ꂸ�CGetTableVersion(\"�ڋq\")��1���ԋp�����BGetTableVersion(\"���i\")��0�̂܂�");
		ColumnData *ColDat[10];
		ColDat[0] = new ColumnDataWStr(L"��", L"�|���L��2");
		ColDat[1] = new ColumnDataWStr(L"�Z", L"�É����ĒÎs2");
		ColDat[2] = new ColumnDataStr(L"�d�b�ԍ�", "000-222-3333");
		RecordData *RecDat = new RecordData(L"�ڋq", ColDat, 3);
		LockTable(L"�ڋq", LOCK_EXCLUSIVE);
		InsertRecord(RecDat);
		UnlockTable(L"�ڋq");
		delete RecDat;
		if (GetNumOfRecords(L"�ڋq") != 1) {
			printf("...[NG]\r\n");
			return -1;
		}
		if (GetTableVersion(L"���i") != 0 || GetTableVersion(L"�ڋq") != 1) {
			printf("...[NG]\r\n");
			return -1;
		}
	}
	printf("...[OK]\r\n");

	// UpdateRecord�Ńe�[�u��"�ڋq"��1���R�[�h�i2�J�������j���X�V��CGetTableVersion("�ڋq")��2���ԋp�����BGetTableVersion("���i")��0�̂܂�
	{
		printf("UpdateRecord�Ńe�[�u��\"�ڋq\"��1���R�[�h�i2�J�������j���X�V��CGetTableVersion(\"�ڋq\")��2���ԋp�����BGetTableVersion(\"���i\")��0�̂܂�");
		ColumnData* ColTgt[5];
		ColumnData* ColUpd[5];
		ColTgt[0] = new ColumnDataWStr(L"����", L"�|���L��");
		ColTgt[1] = new ColumnDataWStr(L"�Z��", L"�É����ĒÎs");
		ColUpd[0] = new ColumnDataWStr(L"����", L"�팩���");
		ColUpd[1] = new ColumnDataWStr(L"�Z��", L"��ʌ��F�J�s");
		RecordData* RecTgt = new RecordData(L"�ڋq", ColTgt, 2);
		RecordData* RecUpd = new RecordData(L"�ڋq", ColUpd, 2);
		LockTable(L"�ڋq", LOCK_EXCLUSIVE);
		UpdateRecord(RecTgt, RecUpd);
		UnlockTable(L"�ڋq");
		delete RecTgt;
		delete RecUpd;
		int a = GetTableVersion(L"�ڋq");
		if (GetTableVersion(L"���i") != 0 || GetTableVersion(L"�ڋq") != 2) {
			printf("...[NG]\r\n");
			return -1;
		}
		printf("...[OK]\r\n");
	}

	// GetRecord�Ńe�[�u��"�ڋq"��1���R�[�h���擾��CGetTableVersion("�ڋq")��2���ԋp�����BGetTableVersion("���i")��0�̂܂�
	{
		printf("GetRecord�Ńe�[�u��\"�ڋq\"��1���R�[�h���擾��CGetTableVersion(\"�ڋq\")��2���ԋp�����BGetTableVersion(\"���i\")��0�̂܂�");
		ColumnData *ColDat[10];
		ColDat[0] = new ColumnDataWStr(L"����", L"�팩���");
		RecordData* RecDat = new RecordData(L"�ڋq", ColDat, 1);
		RecordData* RecGet;
		LockTable(L"�ڋq", LOCK_SHARE);
		RecGet = GetRecord(RecDat);
		UnlockTable(L"�ڋq");
		ColumnDataWStr* GetCol = (ColumnDataWStr*)RecGet->GetColumn(1);
		if (lstrcmp(GetCol->GetValue(), L"��ʌ��F�J�s") != 0) {
			printf("...[NG]\r\n");
			return -1;
		}
		delete RecDat;
		delete RecGet;
		if (GetTableVersion(L"���i") != 0 || GetTableVersion(L"�ڋq") != 2) {
			printf("...[NG]\r\n");
			return -1;
		}
	}
	printf("...[OK]\r\n");

	// DeleteRecord�Ńe�[�u��"�ڋq"��1���R�[�h���폜��CGetTableVersion("�ڋq")��3���ԋp�����BGetTableVersion("���i")��0�̂܂�
	{
		printf("DeleteRecord�Ńe�[�u��\"�ڋq\"��1���R�[�h���폜��CGetTableVersion(\"�ڋq\")��3���ԋp�����BGetTableVersion(\"���i\")��0�̂܂�");
		ColumnData *ColDat[10];
		ColDat[0] = new ColumnDataWStr(L"����", L"�팩���");
		RecordData* RecDat = new RecordData(L"�ڋq", ColDat, 1);
		LockTable(L"�ڋq", LOCK_EXCLUSIVE);
		DeleteRecord(RecDat);
		UnlockTable(L"�ڋq");
		delete RecDat;
		if (GetNumOfRecords(L"�ڋq") != 0) {
			printf("...[NG]\r\n");
			return -1;
		}
		if (GetTableVersion(L"���i") != 0 || GetTableVersion(L"�ڋq") != 3) {
			printf("...[NG]\r\n");
			return -1;
		}
		printf("...[OK]\r\n");
	}

	// InsertRecord��5���R�[�h���i��2���R�[�h�͕s���j�ǉ���CGetTableVersion("�ڋq")��3���ԋp����CGetTableVersion("���i")��3���ԋp�����
	{
		printf("InsertRecord��5���R�[�h���i��2���R�[�h�͕s���j�ǉ���CGetTableVersion(\"�ڋq\")��3���ԋp����CGetTableVersion(\"���i\")��3���ԋp�����");
		ColumnData* ColDat[100][4];
		RecordData* RecDat[100];
		ColDat[0][0] = new ColumnDataInt(L"���i�ԍ�", 1);
		ColDat[0][1] = new ColumnDataWStr(L"���i��", L"������");
		ColDat[0][2] = new ColumnDataInt(L"�l�i", 10000);
		ColDat[0][3] = new ColumnDataInt(L"�݌ɐ�", 10);
		RecDat[0] = new RecordData(L"���i", ColDat[0], 4);

		ColDat[1][0] = new ColumnDataInt(L"����", 2);
		ColDat[1][1] = new ColumnDataWStr(L"���i", L"������");
		ColDat[1][2] = new ColumnDataInt(L"�l", 20000);
		ColDat[1][3] = new ColumnDataInt(L"�݌�", 20);
		RecDat[1] = new RecordData(L"���i", ColDat[1], 4);

		ColDat[2][0] = new ColumnDataInt(L"���i�ԍ�", 3);
		ColDat[2][1] = new ColumnDataWStr(L"���i��", L"������");
		ColDat[2][2] = new ColumnDataInt(L"�l�i", 30000);
		ColDat[2][3] = new ColumnDataInt(L"�݌ɐ�", 30);
		RecDat[2] = new RecordData(L"���i", ColDat[2], 4);

		ColDat[3][0] = new ColumnDataInt(L"���i�ԍ�", 4);
		ColDat[3][1] = new ColumnDataWStr(L"���i��", L"������");
		ColDat[3][2] = new ColumnDataInt(L"�l�i", 40000);
		ColDat[3][3] = new ColumnDataInt(L"�݌ɐ�", 40);
		RecDat[3] = new RecordData(L"���i", ColDat[3], 4);

		ColDat[4][0] = new ColumnDataInt(L"���i�ԍ�", 5);
		ColDat[4][1] = new ColumnDataWStr(L"���i��", L"������");
		ColDat[4][2] = new ColumnDataInt(L"�l", 50000);
		ColDat[4][3] = new ColumnDataInt(L"�݌ɐ�", 50);
		RecDat[4] = new RecordData(L"���i", ColDat[4], 5);

		LockTable(L"���i", LOCK_EXCLUSIVE);
		for (int i = 0; i < 4; i++) {
			InsertRecord(RecDat[i]);
			delete RecDat[i];
		}
		UnlockTable(L"���i");

		if (GetTableVersion(L"���i") != 3 || GetTableVersion(L"�ڋq") != 3) {
			printf("...[NG]\r\n");
			return -1;
		}
		printf("...[OK]\r\n");
	}

	// UpdateRecord"���i"(Search=�����J�����w��:�������s��, Update=�����J�����w��:�K��)��CGetTableVersion("�ڋq")��3���ԋp����CGetTableVersion("���i")��3���ԋp�����
	{
		printf("UpdateRecord\"���i\"(Search=�����J�����w��:�������s��, Update=�����J�����w��:�K��)��CGetTableVersion(\"�ڋq\")��3���ԋp����CGetTableVersion(\"���i\")��3���ԋp�����");
		ColumnData* ColTgt[100][4];
		RecordData* RecTgt[100];
		ColumnData* ColUpd[4];
		RecordData* RecUpd;

		ColTgt[0][0] = new ColumnDataInt(L"���i�ԍ�", 1);
		ColTgt[0][1] = new ColumnDataInt(L"�l", 10000);
		RecTgt[0] = new RecordData(L"���i", ColTgt[0], 2);

		ColTgt[1][0] = new ColumnDataWStr(L"���i��", L"���͂��͂���");
		RecTgt[1] = new RecordData(L"���i", ColTgt[1], 1);

		ColTgt[2][0] = new ColumnDataInt(L"�݌ɐ�", -40);
		ColTgt[2][1] = new ColumnDataInt(L"���i�ԍ�", 4);
		ColTgt[2][2] = new ColumnDataWStr(L"���i��", L"������");
		RecTgt[2] = new RecordData(L"���i", ColTgt[2], 3);

		ColUpd[0] = new ColumnDataInt(L"���i�ԍ�", 100);
		ColUpd[1] = new ColumnDataWStr(L"���i��", L"�|���L��");
		ColUpd[2] = new ColumnDataInt(L"�l�i", 1000000);
		RecUpd = new RecordData(L"���i", ColUpd, 3);

		LockTable(L"���i", LOCK_EXCLUSIVE);
		for (int i = 0; i < 3; i++) {
			UpdateRecord(RecTgt[i], RecUpd);
			delete RecTgt[i];
		}
		UnlockTable(L"���i");
		delete RecUpd;

		if (GetTableVersion(L"���i") != 3 || GetTableVersion(L"�ڋq") != 3) {
			printf("...[NG]\r\n");
			return -1;
		}
		printf("...[OK]\r\n");
	}

	// UpdateRecord"���i"(Search=�����J�����w��:������3���R�[�h�w��Ō���, Update=�����J�����w��:�������s��)��CGetTableVersion("�ڋq")��3���ԋp����CGetTableVersion("���i")��3���ԋp�����
	{
		printf("UpdateRecord\"���i\"(Search=�����J�����w��:������3���R�[�h�w��Ō���, Update=�����J�����w��:�������s��)��CGetTableVersion(\"�ڋq\")��3���ԋp����CGetTableVersion(\"���i\")��3���ԋp�����");
		ColumnData* ColTgt[100][4];
		RecordData* RecTgt[100];
		ColumnData* ColUpd[4];
		RecordData* RecUpd;

		ColTgt[0][0] = new ColumnDataInt(L"���i�ԍ�", 1);
		ColTgt[0][1] = new ColumnDataInt(L"�l�i", 10000);
		RecTgt[0] = new RecordData(L"���i", ColTgt[0], 2);

		ColTgt[1][0] = new ColumnDataWStr(L"���i��", L"������");
		RecTgt[1] = new RecordData(L"���i", ColTgt[1], 1);

		ColTgt[2][0] = new ColumnDataInt(L"�݌ɐ�", 40);
		ColTgt[2][1] = new ColumnDataInt(L"���i�ԍ�", 4);
		ColTgt[2][2] = new ColumnDataWStr(L"���i��", L"������");
		RecTgt[2] = new RecordData(L"���i", ColTgt[2], 3);

		ColUpd[0] = new ColumnDataInt(L"xxx", 200);
		ColUpd[1] = new ColumnDataWStr(L"yyy", L"XXXXX");
		ColUpd[2] = new ColumnDataInt(L"zzz", 2000000);
		RecUpd = new RecordData(L"���i", ColUpd, 3);

		LockTable(L"���i", LOCK_EXCLUSIVE);
		for (int i = 0; i < 3; i++) {
			UpdateRecord(RecTgt[i], RecUpd);
			delete RecTgt[i];
		}
		UnlockTable(L"���i");
		delete RecUpd;
		int a = GetTableVersion(L"���i");

		if (GetTableVersion(L"���i") != 3 || GetTableVersion(L"�ڋq") != 3) {
			printf("...[NG]\r\n");
			return -1;
		}
		printf("...[OK]\r\n");
	}

	// UpdateRecord"���i"��3���R�[�h�X�V(Search=�����J�����w��, Update=�����J�����w��)��CGetTableVersion("�ڋq")��3���ԋp����CGetTableVersion("���i")��6���ԋp�����
	{
		printf("UpdateRecord\"���i\"��3���R�[�h�X�V(Search=�����J�����w��, Update=�����J�����w��)��CGetTableVersion(\"�ڋq\")��3���ԋp����CGetTableVersion(\"���i\")��6���ԋp�����");
		ColumnData* ColTgt[100][4];
		RecordData* RecTgt[100];
		ColumnData* ColUpd[4];
		RecordData* RecUpd;

		ColTgt[0][0] = new ColumnDataInt(L"���i�ԍ�", 1);
		ColTgt[0][1] = new ColumnDataInt(L"�l�i", 10000);
		RecTgt[0] = new RecordData(L"���i", ColTgt[0], 2);

		ColTgt[1][0] = new ColumnDataWStr(L"���i��", L"������");
		RecTgt[1] = new RecordData(L"���i", ColTgt[1], 1);

		ColTgt[2][0] = new ColumnDataInt(L"�݌ɐ�", 40);
		ColTgt[2][1] = new ColumnDataInt(L"���i�ԍ�", 4);
		ColTgt[2][2] = new ColumnDataWStr(L"���i��", L"������");
		RecTgt[2] = new RecordData(L"���i", ColTgt[2], 3);

		ColUpd[0] = new ColumnDataInt(L"���i�ԍ�", 100);
		ColUpd[1] = new ColumnDataWStr(L"���i��", L"�|���L��");
		ColUpd[2] = new ColumnDataInt(L"�l�i", 1000000);
		RecUpd = new RecordData(L"���i", ColUpd, 3);

		LockTable(L"���i", LOCK_EXCLUSIVE);
		for (int i = 0; i < 3; i++) {
			UpdateRecord(RecTgt[i], RecUpd);
			delete RecTgt[i];
		}
		UnlockTable(L"���i");
		delete RecUpd;

		if (GetTableVersion(L"���i") != 6 || GetTableVersion(L"�ڋq") != 3) {
			printf("...[NG]\r\n");
			return -1;
		}
		printf("...[OK]\r\n");
	}

	// SaveData��CGetTableVersion("�ڋq")��3���ԋp����CGetTableVersion("���i")��6���ԋp�����
	// LoadData��CGetTableVersion("�ڋq")��0���ԋp����CGetTableVersion("���i")��0���ԋp�����
	{
		printf("SaveData��CGetTableVersion(\"�ڋq\")��3���ԋp����CGetTableVersion(\"���i\")��6���ԋp�����");
		LockAllTable(LOCK_SHARE);
		SaveData(L"TableVersion.std");
		UnlockAllTable();
		if (GetTableVersion(L"���i") != 6 || GetTableVersion(L"�ڋq") != 3) {
			printf("...[NG]\r\n");
			return -1;
		}
		printf("...[OK]\r\n");
		printf("LoadData��CGetTableVersion(\"�ڋq\")��0���ԋp����CGetTableVersion(\"���i\")��0���ԋp�����");
		LockAllTable(LOCK_EXCLUSIVE);
		LoadData(L"TableVersion.std");
		UnlockAllTable();
		if (GetTableVersion(L"���i") != 0 || GetTableVersion(L"�ڋq") != 0) {
			printf("...[NG]\r\n");
			return -1;
		}
		printf("...[OK]\r\n");
	}

	// ���i��="�|���L��"���w�肵��DeleteRecord��CGetTableVersion("�ڋq")��0���ԋp����CGetTableVersion("���i")��3���ԋp�����
	{
		printf("���i��=\"�|���L��\"���w�肵��DeleteRecord��CGetTableVersion(\"�ڋq\")��0���ԋp����CGetTableVersion(\"���i\")��3���ԋp�����");
		ColumnData* ColDat[5];
		RecordData* RecDat;
		ColDat[0] = new ColumnDataWStr(L"���i��", L"�|���L��");
		RecDat = new RecordData(L"���i", ColDat, 1);
		LockTable(L"���i", LOCK_EXCLUSIVE);
		DeleteRecord(RecDat);
		UnlockTable(L"���i");
		delete RecDat;
		if (GetTableVersion(L"���i") != 3 || GetTableVersion(L"�ڋq") != 0) {
			printf("...[NG]\r\n");
			return -1;
		}
		printf("...[OK]\r\n");
	}

	// DeleteTable(L"���i")�Ńe�[�u�����폜��CGetTableVersion(L"���i")��-1���Ԃ�CGetTableVersion(L"�ڋq")��-1�ȊO���Ԃ�
	{
		printf("DeleteTable(L\"���i\")�Ńe�[�u�����폜��CGetTableVersion(L\"���i\")��-1���Ԃ�CGetTableVersion(L\"�ڋq\")��-1�ȊO���Ԃ�");
		if (DeleteTable(L"���i") != 0) {
			printf("...[NG]\r\n");
			return -1;
		}
		if (GetTableVersion(L"���i") != -1 || GetTableVersion(L"�ڋq") == -1) {
			printf("...[NG]\r\n");
			return -1;
		}
		printf("...[OK]\r\n");
	}

	// �����DeleteTable(L"�ڋq")�Ńe�[�u�����폜��CGetTableVersion(L"���i")�CGetTableVersion(L"�ڋq")�Ƃ���-1���Ԃ�
	{
		printf("�����DeleteTable(L\"�ڋq\")�Ńe�[�u�����폜��CGetTableVersion(L\"���i\")�CGetTableVersion(\"�ڋq\")�Ƃ���-1���Ԃ�");
		if (DeleteTable(L"�ڋq") != 0) {
			printf("...[NG]\r\n");
			return -1;
		}
		if (GetTableVersion(L"���i") != -1 || GetTableVersion(L"�ڋq") != -1) {
			printf("...[NG]\r\n");
			return -1;
		}
		printf("...[OK]\r\n");
	}

	return 0;
}
