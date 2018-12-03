#include <windows.h>
#include <stdio.h>
#include "..\..\src\stkdata\stkdata.h"
#include "..\..\src\stkdata\stkdataapi.h"

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
�EDeleteRecord(L"SmallTable")��CGetNumOfRecords(L"SmallTable")��0��ԋp����
�EDeleteTable(L"SmallTable")��0��ԋp����
*/
int SmallTable()
{
	// CreateTable��SmallTable�e�[�u��(ID:Int) Max=1 �𐶐����邱�Ƃ��ł���
	printf("CreateTable��SmallTable�e�[�u��(ID:Int) Max=1 �𐶐����邱�Ƃ��ł���");
	ColumnDefInt ColDefId(L"ID");
	TableDef TabDefPerson(L"SmallTable", 1);
	TabDefPerson.AddColumnDef(&ColDefId);
	if (CreateTable(&TabDefPerson) != 0) {
		printf("...[NG]\r\n");
		return -1;
	}
	if (GetMaxNumOfRecords(L"SmallTable") != 1) {
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
			ColDat[0] = new ColumnDataInt(L"ID", i);
			CurRecDat = new RecordData(L"SmallTable", ColDat, 1);
			if (i == 0) {
				TopRecDat = CurRecDat;
			}
			if (i >= 1) {
				PrvRecDat->SetNextRecord(CurRecDat);
			}
			PrvRecDat = CurRecDat;
		}
		LockTable(L"SmallTable", 2);
		InsertRecord(TopRecDat);
		UnlockTable(L"SmallTable");
		delete TopRecDat;
		if (GetMaxNumOfRecords(L"SmallTable") != 1) {
			printf("...[NG]\r\n");
			return -1;
		}
		printf("...[OK]\r\n");
	}

	// BigTable("ID"�J���� = 1)�����������Ɏw�肵GetRecord�i���R�[�h�w��j�����s�����NULL���Ԃ�
	{
		printf("BigTable(\"ID\"�J���� = 1)�����������Ɏw�肵GetRecord�i���R�[�h�w��j�����s�����NULL���Ԃ�");
		ColumnData *ColDatTake[1];
		ColDatTake[0] = new ColumnDataInt(L"ID", 1);
		RecordData RecDatTake(L"BigTable", ColDatTake, 1);
		RecordData *RecDatGet;
		LockTable(L"SmallTable", 1);
		RecDatGet = GetRecord(&RecDatTake);
		UnlockTable(L"SmallTable");
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
		ColDatTake[0] = new ColumnDataInt(L"ID", 0);
		RecordData RecDatTake(L"SmallTable", ColDatTake, 1);
		RecordData *RecDatGet;
		LockTable(L"SmallTable", 1);
		RecDatGet = GetRecord(&RecDatTake);
		UnlockTable(L"SmallTable");
		if (RecDatGet == NULL) {
			printf("...[NG]\r\n");
			return -1;
		}
		delete RecDatGet;
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
		if (GetNumOfRecords(L"SmallTable") != 1) {
			printf("...[NG]\r\n");
			return -1;
		}
		printf("...[OK]\r\n");
	}

	// GetMaxNumOfRecords("SmallTable")�Ŏ擾�������R�[�h������1���ƂȂ�
	{
		printf("GetMaxNumOfRecords(\"SmallTable\")�Ŏ擾�������R�[�h������1���ƂȂ�");
		if (GetMaxNumOfRecords(L"SmallTable") != 1) {
			printf("...[NG]\r\n");
			return -1;
		}
		printf("...[OK]\r\n");
	}

	// GetNumOfRecords("BigTable")�Ŏ擾�������R�[�h������-1���ƂȂ�
	{
		printf("GetNumOfRecords(\"BigTable\")�Ŏ擾�������R�[�h������-1���ƂȂ�");
		if (GetNumOfRecords(L"BigTable") != -1) {
			printf("...[NG]\r\n");
			return -1;
		}
		printf("...[OK]\r\n");
	}

	// GetMaxNumOfRecords("BigTable")�Ŏ擾�������R�[�h������-1���ƂȂ�
	{
		printf("GetMaxNumOfRecords(\"BigTable\")�Ŏ擾�������R�[�h������-1���ƂȂ�");
		if (GetMaxNumOfRecords(L"BigTable") != -1) {
			printf("...[NG]\r\n");
			return -1;
		}
		printf("...[OK]\r\n");
	}

	// DeleteRecord(L"SmallTable")��CGetNumOfRecords(L"SmallTable")��0��ԋp����
	{
		printf("DeleteRecord(L\"SmallTable\")��CGetNumOfRecords(L\"SmallTable\")��0��ԋp����");
		LockTable(L"SmallTable", LOCK_EXCLUSIVE);
		DeleteRecord(L"SmallTable");
		UnlockTable(L"SmallTable");
		if (GetNumOfRecords(L"SmallTable") != 0) {
			printf("...[NG]\r\n");
			return -1;
		}
		printf("...[OK]\r\n");
	}

	// CreateTable��SmallTable�e�[�u��2(ID:Int) Max=100 �𐶐����邱�Ƃ��ł���
	printf("CreateTable��SmallTable�e�[�u��2(ID:Int) Max=100 �𐶐����邱�Ƃ��ł���");
	ColumnDefInt ColDefId2(L"ID");
	TableDef TabDefPerson2(L"SmallTable2", 100);
	TabDefPerson2.AddColumnDef(&ColDefId2);
	if (CreateTable(&TabDefPerson2) != 0) {
		printf("...[NG]\r\n");
		return -1;
	}
	if (GetMaxNumOfRecords(L"SmallTable2") != 100) {
		printf("...[NG]\r\n");
		return -1;
	}
	printf("...[OK]\r\n");

	// Rename table name (UnexistTable ---> RenamedTable)
	printf("Rename table name (UnexistTable ---> RenamedTable)  Does the API return -1?");
	if (RenameTable(L"UnexistTable", L"RenamedTable") != -1) {
		printf("...[NG]\r\n");
		return -1;
	}
	printf("...[OK]\r\n");

	// Rename table name (SmallTable ---> SmallTable2)
	printf("Rename table name (SmallTable ---> SmallTable2)  Does the API return -1?");
	if (RenameTable(L"SmallTable", L"SmallTable2") != -1) {
		printf("...[NG]\r\n");
		return -1;
	}
	printf("...[OK]\r\n");

	// Rename table name (SmallTable2 ---> SmallTable3)
	printf("Rename table name (SmallTable2 ---> SmallTable3)  Does the API return 0?");
	if (RenameTable(L"SmallTable2", L"SmallTable3") != 0) {
		printf("...[NG]\r\n");
		return -1;
	}
	printf("...[OK]\r\n");

	// Check that SmallTable2 is renamed as SmallTable3.
	printf("Check that SmallTable2 is renamed as SmallTable3.");
	wchar_t TblNames[MAX_TABLE_NUMBER][TABLE_NAME_SIZE];
	int TblCnt = GetTableName(TblNames);
	if (lstrcmp(TblNames[0], L"SmallTable") != 0 && lstrcmp(TblNames[1], L"SmallTable2") != 0) {
		printf("...[NG]\r\n");
		return -1;
	}
	printf("...[OK]\r\n");

	// Rename table name (SmallTable3 ---> SmallTable4)
	printf("Rename table name (SmallTable3 ---> SmallTable4)  Does the API return 0?");
	if (RenameTable(L"SmallTable3", L"SmallTable4") != 0) {
		printf("...[NG]\r\n");
		return -1;
	}
	printf("...[OK]\r\n");

	// Rename table name (SmallTable ---> SmallTable5)
	printf("Rename table name (SmallTable ---> SmallTable5)  Does the API return 0?");
	if (RenameTable(L"SmallTable", L"SmallTable5") != 0) {
		printf("...[NG]\r\n");
		return -1;
	}
	printf("...[OK]\r\n");

	// Check that SmallTable is renamed as SmallTable5.
	printf("Check that SmallTable is renamed as SmallTable5.");
	TblCnt = GetTableName(TblNames);
	if (lstrcmp(TblNames[0], L"SmallTable5") != 0 && lstrcmp(TblNames[1], L"SmallTable4") != 0) {
		printf("...[NG]\r\n");
		return -1;
	}
	printf("...[OK]\r\n");

	// DeleteTable(L"SmallTable4")��0��ԋp����
	{
		printf("DeleteTable(L\"SmallTable4\")��0��ԋp����");
		if (DeleteTable(L"SmallTable4") != 0) {
			printf("...[NG]\r\n");
			return -1;
		}
		printf("...[OK]\r\n");
	}

	// DeleteTable(L"SmallTable5")��0��ԋp����
	{
		printf("DeleteTable(L\"SmallTable5\")��0��ԋp����");
		if (DeleteTable(L"SmallTable5") != 0) {
			printf("...[NG]\r\n");
			return -1;
		}
		printf("...[OK]\r\n");
	}
	return 0;
}
