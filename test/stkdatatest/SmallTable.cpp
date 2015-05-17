#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include "..\..\src\stkdata\stkdata.h"

/*
SmallTable
�ECreateTable��SmallTable�e�[�u��(ID:Int) Max=1 �𐶐����邱�Ƃ��ł���
�E�ő僌�R�[�h�o�^�\��=1��SmallTable�ɑ΂���16383�̘A�����ꂽ���R�[�h��InsertRecord�����1���R�[�h�̂ݒǉ������
�EBigTable("ID"�J���� = 1)�����������Ɏw�肵GetRecord�i���R�[�h�w��j�����s�����NULL���Ԃ�
�ESmallTable("ID"�J���� = 0)�����������Ɏw�肵���b�N���GetRecord�i���R�[�h�w��j�����s�����RecordData���Ԃ�B���������b�N�����Ŏ��s�����ꍇNULL���Ԃ�
�EGetNumOfRecords("SmallTable")�Ŏ擾�������R�[�h������1���ƂȂ�
�EGetMaxNumOfRecords("SmallTable")�Ŏ擾�������R�[�h������1���ƂȂ�
�EGetNumOfRecords("BigTable")�Ŏ擾�������R�[�h������-1���ƂȂ�
�EGetMaxNumOfRecords("BigTable")�Ŏ擾�������R�[�h������-1���ƂȂ�
�EDeleteRecord(_T("SmallTable"))��CGetNumOfRecords(_T("SmallTable"))��0��ԋp����
�EDeleteTable(_T("SmallTable"))��0��ԋp����
*/
int SmallTable()
{
	// CreateTable��SmallTable�e�[�u��(ID:Int) Max=1 �𐶐����邱�Ƃ��ł���
	printf("CreateTable��SmallTable�e�[�u��(ID:Int) Max=1 �𐶐����邱�Ƃ��ł���");
	ColumnDefInt ColDefId(_T("ID"));
	TableDef TabDefPerson(_T("SmallTable"), 1);
	TabDefPerson.AddColumnDef(&ColDefId);
	if (CreateTable(&TabDefPerson) != 0) {
		printf("...[NG]\r\n");
		return -1;
	}
	if (GetMaxNumOfRecords(_T("SmallTable")) != 1) {
		printf("...[NG]\r\n");
		return -1;
	}
	printf("...[OK]\r\n");

	// �ő僌�R�[�h�o�^�\��=1��SmallTable�ɑ΂���16383�̘A�����ꂽ���R�[�h��InsertRecord�����1���R�[�h�̂ݒǉ������
	{
		printf("�ő僌�R�[�h�o�^�\��=1��SmallTable�ɑ΂���16383�̘A�����ꂽ���R�[�h��InsertRecord�����1���R�[�h�̂ݒǉ������");
		ColumnData *ColDat[4];
		RecordData *TopRecDat;
		RecordData *PrvRecDat;
		RecordData *CurRecDat;
		for (int i = 0; i < 16383; i++) {
			ColDat[0] = new ColumnDataInt(_T("ID"), i);
			CurRecDat = new RecordData(_T("SmallTable"), ColDat, 1);
			if (i == 0) {
				TopRecDat = CurRecDat;
			}
			if (i >= 1) {
				PrvRecDat->SetNextRecord(CurRecDat);
			}
			PrvRecDat = CurRecDat;
		}
		LockTable(_T("SmallTable"), 2);
		InsertRecord(TopRecDat);
		UnlockTable(_T("SmallTable"));
		ClearRecordData(TopRecDat);
		if (GetMaxNumOfRecords(_T("SmallTable")) != 1) {
			printf("...[NG]\r\n");
			return -1;
		}
		printf("...[OK]\r\n");
	}

	// BigTable("ID"�J���� = 1)�����������Ɏw�肵GetRecord�i���R�[�h�w��j�����s�����NULL���Ԃ�
	{
		printf("BigTable(\"ID\"�J���� = 1)�����������Ɏw�肵GetRecord�i���R�[�h�w��j�����s�����NULL���Ԃ�");
		ColumnData *ColDatTake[1];
		ColDatTake[0] = new ColumnDataInt(_T("ID"), 1);
		RecordData RecDatTake(_T("BigTable"), ColDatTake, 1);
		RecordData *RecDatGet;
		LockTable(_T("SmallTable"), 1);
		RecDatGet = GetRecord(&RecDatTake);
		UnlockTable(_T("SmallTable"));
		if (RecDatGet != NULL) {
			printf("...[NG]\r\n");
			return -1;
		}
		printf("...[OK]\r\n");
	}

	// SmallTable("ID"�J���� = 0)�����������Ɏw�肵���b�N���GetRecord�i���R�[�h�w��j�����s�����RecordData���Ԃ�B���������b�N�����Ŏ��s�����ꍇNULL���Ԃ�
	{
		printf("SmallTable(\"ID\"�J���� = 0)�����������Ɏw�肵���b�N���GetRecord�i���R�[�h�w��j�����s�����RecordData���Ԃ�B���������b�N�����Ŏ��s�����ꍇNULL���Ԃ�");
		ColumnData *ColDatTake[1];
		ColDatTake[0] = new ColumnDataInt(_T("ID"), 0);
		RecordData RecDatTake(_T("SmallTable"), ColDatTake, 1);
		RecordData *RecDatGet;
		LockTable(_T("SmallTable"), 1);
		RecDatGet = GetRecord(&RecDatTake);
		UnlockTable(_T("SmallTable"));
		if (RecDatGet == NULL) {
			printf("...[NG]\r\n");
			return -1;
		}
		ClearRecordData(RecDatGet);
		RecDatGet = GetRecord(&RecDatTake);
		if (RecDatGet != NULL) {
			printf("...[NG]\r\n");
			return -1;
		}
		printf("...[OK]\r\n");
	}

	// GetNumOfRecords("SmallTable")�Ŏ擾�������R�[�h������1���ƂȂ�
	{
		printf("GetNumOfRecords(\"SmallTable\")�Ŏ擾�������R�[�h������1���ƂȂ�");
		if (GetNumOfRecords(_T("SmallTable")) != 1) {
			printf("...[NG]\r\n");
			return -1;
		}
		printf("...[OK]\r\n");
	}

	// GetMaxNumOfRecords("SmallTable")�Ŏ擾�������R�[�h������1���ƂȂ�
	{
		printf("GetMaxNumOfRecords(\"SmallTable\")�Ŏ擾�������R�[�h������1���ƂȂ�");
		if (GetMaxNumOfRecords(_T("SmallTable")) != 1) {
			printf("...[NG]\r\n");
			return -1;
		}
		printf("...[OK]\r\n");
	}

	// GetNumOfRecords("BigTable")�Ŏ擾�������R�[�h������-1���ƂȂ�
	{
		printf("GetNumOfRecords(\"BigTable\")�Ŏ擾�������R�[�h������-1���ƂȂ�");
		if (GetNumOfRecords(_T("BigTable")) != -1) {
			printf("...[NG]\r\n");
			return -1;
		}
		printf("...[OK]\r\n");
	}

	// GetMaxNumOfRecords("BigTable")�Ŏ擾�������R�[�h������-1���ƂȂ�
	{
		printf("GetMaxNumOfRecords(\"BigTable\")�Ŏ擾�������R�[�h������-1���ƂȂ�");
		if (GetMaxNumOfRecords(_T("BigTable")) != -1) {
			printf("...[NG]\r\n");
			return -1;
		}
		printf("...[OK]\r\n");
	}

	// DeleteRecord(_T("SmallTable"))��CGetNumOfRecords(_T("SmallTable"))��0��ԋp����
	{
		printf("DeleteRecord(_T(\"SmallTable\"))��CGetNumOfRecords(_T(\"SmallTable\"))��0��ԋp����");
		LockTable(_T("SmallTable"), LOCK_EXCLUSIVE);
		DeleteRecord(_T("SmallTable"));
		UnlockTable(_T("SmallTable"));
		if (GetNumOfRecords(_T("SmallTable")) != 0) {
			printf("...[NG]\r\n");
			return -1;
		}
		printf("...[OK]\r\n");
	}

	// DeleteTable(_T("SmallTable"))��0��ԋp����
	{
		printf("DeleteTable(_T(\"SmallTable\"))��0��ԋp����");
		if (DeleteTable(_T("SmallTable")) != 0) {
			printf("...[NG]\r\n");
			return -1;
		}
		printf("...[OK]\r\n");
	}
	return 0;
}
