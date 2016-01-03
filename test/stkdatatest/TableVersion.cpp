#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include "..\..\src\stkdata\stkdata.h"
#include "..\..\src\stkdata\stkdataapi.h"

/*
TableVersion
�E"���i"�e�[�u��, "�ڋq"�e�[�u���𐶐�����O��GetTableVersion(_T("���i"))�܂���GetTableVersion(_T("�ڋq"))�Ăяo����-1���Ԃ�
�ECreateTable��"���i"�e�[�u�����ő僌�R�[�h=500�Ƃ��Đ������邱�Ƃ��ł���
�ECreateTable��"�ڋq"�e�[�u�����ő僌�R�[�h=5000�Ƃ��Đ������邱�Ƃ��ł���
�E"���i"�e�[�u��, "�ڋq"�e�[�u���𐶐����GetTableVersion(_T("���i"))�܂���GetTableVersion(_T("�ڋq"))�Ăяo����0���Ԃ�
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
�EDeleteTable(_T("���i"))�Ńe�[�u�����폜��CGetTableVersion(_T("���i"))��-1���Ԃ�CGetTableVersion(_T("�ڋq"))��-1�ȊO���Ԃ�
�E�����DeleteTable(_T("�ڋq"))�Ńe�[�u�����폜��CGetTableVersion(_T("���i"))�CGetTableVersion(_T("�ڋq"))�Ƃ���-1���Ԃ�
*/
int TableVersion()
{
	// "���i"�e�[�u��, "�ڋq"�e�[�u���𐶐�����O��GetTableVersion(_T("���i"))�܂���GetTableVersion(_T("�ڋq"))�Ăяo����-1���Ԃ�
	{
		printf("\"���i\"�e�[�u��, \"�ڋq\"�e�[�u���𐶐�����O��GetTableVersion(_T(\"���i\"))�܂���GetTableVersion(_T(\"�ڋq\"))�Ăяo����-1���Ԃ�");
		if (GetTableVersion(_T("���i")) != -1 || GetTableVersion(_T("�ڋq")) != -1) {
			printf("...[NG]\r\n");
			return -1;
		}
	}
	printf("...[OK]\r\n");

	// CreateTable��"���i"�e�[�u�����ő僌�R�[�h=500�Ƃ��Đ������邱�Ƃ��ł���
	{
		printf("CreateTable��\"���i\"�e�[�u�����ő僌�R�[�h=500�Ƃ��Đ������邱�Ƃ��ł���");
		ColumnDefInt ColDefId(_T("���i�ԍ�"));
		ColumnDefWStr ColDefName(_T("���i��"), 10);
		ColumnDefInt ColDefPrice(_T("�l�i"));
		ColumnDefInt ColDefCount(_T("�݌ɐ�"));
		TableDef TabDefMarc(_T("���i"), 500);
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
		ColumnDefWStr ColDefName(_T("����"), 10);
		ColumnDefWStr ColDefAddr(_T("�Z��"), 20);
		ColumnDefStr ColDefTel(_T("�d�b�ԍ�"), 20);
		TableDef TabDefCustomer(_T("�ڋq"), 5000);
		TabDefCustomer.AddColumnDef(&ColDefName);
		TabDefCustomer.AddColumnDef(&ColDefAddr);
		TabDefCustomer.AddColumnDef(&ColDefTel);
		if (CreateTable(&TabDefCustomer) != 0) {
			printf("...[NG]\r\n");
			return -1;
		}
	}
	printf("...[OK]\r\n");

	// "���i"�e�[�u��, "�ڋq"�e�[�u���𐶐����GetTableVersion(_T("���i"))�܂���GetTableVersion(_T("�ڋq"))�Ăяo����0���Ԃ�
	{
		printf("\"���i\"�e�[�u��, \"�ڋq\"�e�[�u���𐶐����GetTableVersion(_T(\"���i\"))�܂���GetTableVersion(_T(\"�ڋq\"))�Ăяo����0���Ԃ�");
		if (GetTableVersion(_T("���i")) != 0 || GetTableVersion(_T("�ڋq")) != 0) {
			printf("...[NG]\r\n");
			return -1;
		}
	}
	printf("...[OK]\r\n");

	// InsertRecord�Ńe�[�u��"�ڋq"��1���R�[�h�ǉ���CGetTableVersion("�ڋq")��1���ԋp�����BGetTableVersion("���i")��0�̂܂�
	{
		printf("InsertRecord�Ńe�[�u��\"�ڋq\"��1���R�[�h�ǉ���CGetTableVersion(\"�ڋq\")��1���ԋp�����BGetTableVersion(\"���i\")��0�̂܂�");
		ColumnData *ColDat[10];
		ColDat[0] = new ColumnDataWStr(_T("����"), _T("�|���L��"));
		ColDat[1] = new ColumnDataWStr(_T("�Z��"), _T("�É����ĒÎs"));
		ColDat[2] = new ColumnDataStr(_T("�d�b�ԍ�"), "111-222-3333");
		RecordData *RecDat = new RecordData(_T("�ڋq"), ColDat, 3);
		LockTable(_T("�ڋq"), LOCK_EXCLUSIVE);
		InsertRecord(RecDat);
		UnlockTable(_T("�ڋq"));
		delete RecDat;
		if (GetTableVersion(_T("���i")) != 0 || GetTableVersion(_T("�ڋq")) != 1) {
			printf("...[NG]\r\n");
			return -1;
		}
	}
	printf("...[OK]\r\n");

	// InsertRecord�Ńe�[�u��"�ڋq"�ɑ��݂��Ȃ��J�������w�肵�Ă����R�[�h�͒ǉ����ꂸ�CGetTableVersion("�ڋq")��1���ԋp�����BGetTableVersion("���i")��0�̂܂�
	{
		printf("InsertRecord�Ńe�[�u��\"�ڋq\"�ɑ��݂��Ȃ��J�������w�肵�Ă����R�[�h�͒ǉ����ꂸ�CGetTableVersion(\"�ڋq\")��1���ԋp�����BGetTableVersion(\"���i\")��0�̂܂�");
		ColumnData *ColDat[10];
		ColDat[0] = new ColumnDataWStr(_T("��"), _T("�|���L��2"));
		ColDat[1] = new ColumnDataWStr(_T("�Z"), _T("�É����ĒÎs2"));
		ColDat[2] = new ColumnDataStr(_T("�d�b�ԍ�"), "000-222-3333");
		RecordData *RecDat = new RecordData(_T("�ڋq"), ColDat, 3);
		LockTable(_T("�ڋq"), LOCK_EXCLUSIVE);
		InsertRecord(RecDat);
		UnlockTable(_T("�ڋq"));
		delete RecDat;
		if (GetNumOfRecords(_T("�ڋq")) != 1) {
			printf("...[NG]\r\n");
			return -1;
		}
		if (GetTableVersion(_T("���i")) != 0 || GetTableVersion(_T("�ڋq")) != 1) {
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
		ColTgt[0] = new ColumnDataWStr(_T("����"), _T("�|���L��"));
		ColTgt[1] = new ColumnDataWStr(_T("�Z��"), _T("�É����ĒÎs"));
		ColUpd[0] = new ColumnDataWStr(_T("����"), _T("�팩���"));
		ColUpd[1] = new ColumnDataWStr(_T("�Z��"), _T("��ʌ��F�J�s"));
		RecordData* RecTgt = new RecordData(_T("�ڋq"), ColTgt, 2);
		RecordData* RecUpd = new RecordData(_T("�ڋq"), ColUpd, 2);
		LockTable(_T("�ڋq"), LOCK_EXCLUSIVE);
		UpdateRecord(RecTgt, RecUpd);
		UnlockTable(_T("�ڋq"));
		delete RecTgt;
		delete RecUpd;
		int a = GetTableVersion(_T("�ڋq"));
		if (GetTableVersion(_T("���i")) != 0 || GetTableVersion(_T("�ڋq")) != 2) {
			printf("...[NG]\r\n");
			return -1;
		}
		printf("...[OK]\r\n");
	}

	// GetRecord�Ńe�[�u��"�ڋq"��1���R�[�h���擾��CGetTableVersion("�ڋq")��2���ԋp�����BGetTableVersion("���i")��0�̂܂�
	{
		printf("GetRecord�Ńe�[�u��\"�ڋq\"��1���R�[�h���擾��CGetTableVersion(\"�ڋq\")��2���ԋp�����BGetTableVersion(\"���i\")��0�̂܂�");
		ColumnData *ColDat[10];
		ColDat[0] = new ColumnDataWStr(_T("����"), _T("�팩���"));
		RecordData* RecDat = new RecordData(_T("�ڋq"), ColDat, 1);
		RecordData* RecGet;
		LockTable(_T("�ڋq"), LOCK_SHARE);
		RecGet = GetRecord(RecDat);
		UnlockTable(_T("�ڋq"));
		ColumnDataWStr* GetCol = (ColumnDataWStr*)RecGet->GetColumn(1);
		if (lstrcmp(GetCol->GetValue(), _T("��ʌ��F�J�s")) != 0) {
			printf("...[NG]\r\n");
			return -1;
		}
		delete RecDat;
		delete RecGet;
		if (GetTableVersion(_T("���i")) != 0 || GetTableVersion(_T("�ڋq")) != 2) {
			printf("...[NG]\r\n");
			return -1;
		}
	}
	printf("...[OK]\r\n");

	// DeleteRecord�Ńe�[�u��"�ڋq"��1���R�[�h���폜��CGetTableVersion("�ڋq")��3���ԋp�����BGetTableVersion("���i")��0�̂܂�
	{
		printf("DeleteRecord�Ńe�[�u��\"�ڋq\"��1���R�[�h���폜��CGetTableVersion(\"�ڋq\")��3���ԋp�����BGetTableVersion(\"���i\")��0�̂܂�");
		ColumnData *ColDat[10];
		ColDat[0] = new ColumnDataWStr(_T("����"), _T("�팩���"));
		RecordData* RecDat = new RecordData(_T("�ڋq"), ColDat, 1);
		LockTable(_T("�ڋq"), LOCK_EXCLUSIVE);
		DeleteRecord(RecDat);
		UnlockTable(_T("�ڋq"));
		delete RecDat;
		if (GetNumOfRecords(_T("�ڋq")) != 0) {
			printf("...[NG]\r\n");
			return -1;
		}
		if (GetTableVersion(_T("���i")) != 0 || GetTableVersion(_T("�ڋq")) != 3) {
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
		ColDat[0][0] = new ColumnDataInt(_T("���i�ԍ�"), 1);
		ColDat[0][1] = new ColumnDataWStr(_T("���i��"), _T("������"));
		ColDat[0][2] = new ColumnDataInt(_T("�l�i"), 10000);
		ColDat[0][3] = new ColumnDataInt(_T("�݌ɐ�"), 10);
		RecDat[0] = new RecordData(_T("���i"), ColDat[0], 4);

		ColDat[1][0] = new ColumnDataInt(_T("����"), 2);
		ColDat[1][1] = new ColumnDataWStr(_T("���i"), _T("������"));
		ColDat[1][2] = new ColumnDataInt(_T("�l"), 20000);
		ColDat[1][3] = new ColumnDataInt(_T("�݌�"), 20);
		RecDat[1] = new RecordData(_T("���i"), ColDat[1], 4);

		ColDat[2][0] = new ColumnDataInt(_T("���i�ԍ�"), 3);
		ColDat[2][1] = new ColumnDataWStr(_T("���i��"), _T("������"));
		ColDat[2][2] = new ColumnDataInt(_T("�l�i"), 30000);
		ColDat[2][3] = new ColumnDataInt(_T("�݌ɐ�"), 30);
		RecDat[2] = new RecordData(_T("���i"), ColDat[2], 4);

		ColDat[3][0] = new ColumnDataInt(_T("���i�ԍ�"), 4);
		ColDat[3][1] = new ColumnDataWStr(_T("���i��"), _T("������"));
		ColDat[3][2] = new ColumnDataInt(_T("�l�i"), 40000);
		ColDat[3][3] = new ColumnDataInt(_T("�݌ɐ�"), 40);
		RecDat[3] = new RecordData(_T("���i"), ColDat[3], 4);

		ColDat[4][0] = new ColumnDataInt(_T("���i�ԍ�"), 5);
		ColDat[4][1] = new ColumnDataWStr(_T("���i��"), _T("������"));
		ColDat[4][2] = new ColumnDataInt(_T("�l"), 50000);
		ColDat[4][3] = new ColumnDataInt(_T("�݌ɐ�"), 50);
		RecDat[4] = new RecordData(_T("���i"), ColDat[4], 5);

		LockTable(_T("���i"), LOCK_EXCLUSIVE);
		for (int i = 0; i < 4; i++) {
			InsertRecord(RecDat[i]);
			delete RecDat[i];
		}
		UnlockTable(_T("���i"));

		if (GetTableVersion(_T("���i")) != 3 || GetTableVersion(_T("�ڋq")) != 3) {
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

		ColTgt[0][0] = new ColumnDataInt(_T("���i�ԍ�"), 1);
		ColTgt[0][1] = new ColumnDataInt(_T("�l"), 10000);
		RecTgt[0] = new RecordData(_T("���i"), ColTgt[0], 2);

		ColTgt[1][0] = new ColumnDataWStr(_T("���i��"), _T("���͂��͂���"));
		RecTgt[1] = new RecordData(_T("���i"), ColTgt[1], 1);

		ColTgt[2][0] = new ColumnDataInt(_T("�݌ɐ�"), -40);
		ColTgt[2][1] = new ColumnDataInt(_T("���i�ԍ�"), 4);
		ColTgt[2][2] = new ColumnDataWStr(_T("���i��"), _T("������"));
		RecTgt[2] = new RecordData(_T("���i"), ColTgt[2], 3);

		ColUpd[0] = new ColumnDataInt(_T("���i�ԍ�"), 100);
		ColUpd[1] = new ColumnDataWStr(_T("���i��"), _T("�|���L��"));
		ColUpd[2] = new ColumnDataInt(_T("�l�i"), 1000000);
		RecUpd = new RecordData(_T("���i"), ColUpd, 3);

		LockTable(_T("���i"), LOCK_EXCLUSIVE);
		for (int i = 0; i < 3; i++) {
			UpdateRecord(RecTgt[i], RecUpd);
			delete RecTgt[i];
		}
		UnlockTable(_T("���i"));
		delete RecUpd;

		if (GetTableVersion(_T("���i")) != 3 || GetTableVersion(_T("�ڋq")) != 3) {
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

		ColTgt[0][0] = new ColumnDataInt(_T("���i�ԍ�"), 1);
		ColTgt[0][1] = new ColumnDataInt(_T("�l�i"), 10000);
		RecTgt[0] = new RecordData(_T("���i"), ColTgt[0], 2);

		ColTgt[1][0] = new ColumnDataWStr(_T("���i��"), _T("������"));
		RecTgt[1] = new RecordData(_T("���i"), ColTgt[1], 1);

		ColTgt[2][0] = new ColumnDataInt(_T("�݌ɐ�"), 40);
		ColTgt[2][1] = new ColumnDataInt(_T("���i�ԍ�"), 4);
		ColTgt[2][2] = new ColumnDataWStr(_T("���i��"), _T("������"));
		RecTgt[2] = new RecordData(_T("���i"), ColTgt[2], 3);

		ColUpd[0] = new ColumnDataInt(_T("xxx"), 200);
		ColUpd[1] = new ColumnDataWStr(_T("yyy"), _T("XXXXX"));
		ColUpd[2] = new ColumnDataInt(_T("zzz"), 2000000);
		RecUpd = new RecordData(_T("���i"), ColUpd, 3);

		LockTable(_T("���i"), LOCK_EXCLUSIVE);
		for (int i = 0; i < 3; i++) {
			UpdateRecord(RecTgt[i], RecUpd);
			delete RecTgt[i];
		}
		UnlockTable(_T("���i"));
		delete RecUpd;
		int a = GetTableVersion(_T("���i"));

		if (GetTableVersion(_T("���i")) != 3 || GetTableVersion(_T("�ڋq")) != 3) {
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

		ColTgt[0][0] = new ColumnDataInt(_T("���i�ԍ�"), 1);
		ColTgt[0][1] = new ColumnDataInt(_T("�l�i"), 10000);
		RecTgt[0] = new RecordData(_T("���i"), ColTgt[0], 2);

		ColTgt[1][0] = new ColumnDataWStr(_T("���i��"), _T("������"));
		RecTgt[1] = new RecordData(_T("���i"), ColTgt[1], 1);

		ColTgt[2][0] = new ColumnDataInt(_T("�݌ɐ�"), 40);
		ColTgt[2][1] = new ColumnDataInt(_T("���i�ԍ�"), 4);
		ColTgt[2][2] = new ColumnDataWStr(_T("���i��"), _T("������"));
		RecTgt[2] = new RecordData(_T("���i"), ColTgt[2], 3);

		ColUpd[0] = new ColumnDataInt(_T("���i�ԍ�"), 100);
		ColUpd[1] = new ColumnDataWStr(_T("���i��"), _T("�|���L��"));
		ColUpd[2] = new ColumnDataInt(_T("�l�i"), 1000000);
		RecUpd = new RecordData(_T("���i"), ColUpd, 3);

		LockTable(_T("���i"), LOCK_EXCLUSIVE);
		for (int i = 0; i < 3; i++) {
			UpdateRecord(RecTgt[i], RecUpd);
			delete RecTgt[i];
		}
		UnlockTable(_T("���i"));
		delete RecUpd;

		if (GetTableVersion(_T("���i")) != 6 || GetTableVersion(_T("�ڋq")) != 3) {
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
		SaveData(_T("TableVersion.std"));
		UnlockAllTable();
		if (GetTableVersion(_T("���i")) != 6 || GetTableVersion(_T("�ڋq")) != 3) {
			printf("...[NG]\r\n");
			return -1;
		}
		printf("...[OK]\r\n");
		printf("LoadData��CGetTableVersion(\"�ڋq\")��0���ԋp����CGetTableVersion(\"���i\")��0���ԋp�����");
		LockAllTable(LOCK_EXCLUSIVE);
		LoadData(_T("TableVersion.std"));
		UnlockAllTable();
		if (GetTableVersion(_T("���i")) != 0 || GetTableVersion(_T("�ڋq")) != 0) {
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
		ColDat[0] = new ColumnDataWStr(_T("���i��"), _T("�|���L��"));
		RecDat = new RecordData(_T("���i"), ColDat, 1);
		LockTable(_T("���i"), LOCK_EXCLUSIVE);
		DeleteRecord(RecDat);
		UnlockTable(_T("���i"));
		delete RecDat;
		if (GetTableVersion(_T("���i")) != 3 || GetTableVersion(_T("�ڋq")) != 0) {
			printf("...[NG]\r\n");
			return -1;
		}
		printf("...[OK]\r\n");
	}

	// DeleteTable(_T("���i"))�Ńe�[�u�����폜��CGetTableVersion(_T("���i"))��-1���Ԃ�CGetTableVersion(_T("�ڋq"))��-1�ȊO���Ԃ�
	{
		printf("DeleteTable(_T(\"���i\"))�Ńe�[�u�����폜��CGetTableVersion(_T(\"���i\"))��-1���Ԃ�CGetTableVersion(_T(\"�ڋq\"))��-1�ȊO���Ԃ�");
		if (DeleteTable(_T("���i")) != 0) {
			printf("...[NG]\r\n");
			return -1;
		}
		if (GetTableVersion(_T("���i")) != -1 || GetTableVersion(_T("�ڋq")) == -1) {
			printf("...[NG]\r\n");
			return -1;
		}
		printf("...[OK]\r\n");
	}

	// �����DeleteTable(_T("�ڋq"))�Ńe�[�u�����폜��CGetTableVersion(_T("���i"))�CGetTableVersion(_T("�ڋq"))�Ƃ���-1���Ԃ�
	{
		printf("�����DeleteTable(_T(\"�ڋq\"))�Ńe�[�u�����폜��CGetTableVersion(_T(\"���i\"))�CGetTableVersion(_T(\"�ڋq\"))�Ƃ���-1���Ԃ�");
		if (DeleteTable(_T("�ڋq")) != 0) {
			printf("...[NG]\r\n");
			return -1;
		}
		if (GetTableVersion(_T("���i")) != -1 || GetTableVersion(_T("�ڋq")) != -1) {
			printf("...[NG]\r\n");
			return -1;
		}
		printf("...[OK]\r\n");
	}

	return 0;
}
