#include <windows.h>
#include <tchar.h>
#include <string.h>
#include <stdio.h>
#include "DataAcController.h"
#include "stkdata.h"


int CreateTable(TableDef*);
int DeleteTable(TCHAR*);

int LockTable(TCHAR*, int);
int LockAllTable(int);
int UnlockTable(TCHAR*);
int UnlockAllTable();

int InsertRecord(RecordData*);
int DeleteRecord(TCHAR*);
int DeleteRecord(RecordData*);
int UpdateRecord(RecordData*, RecordData*);
RecordData* GetRecord(TCHAR*);
RecordData* GetRecord(RecordData*);
void ClearRecordData(RecordData*);

int AzSortRecord(TCHAR*, TCHAR*);
int ZaSortRecord(TCHAR*, TCHAR*);

int GetColumnCount(TCHAR*);
int GetColumnSize(TCHAR*, TCHAR*);
int GetColumnName(TCHAR*, TCHAR[MAX_COLUMN_NUMBER][COLUMN_NAME_SIZE]);
int GetColumnType(TCHAR*, TCHAR*);
int GetTableCount();
int GetTableName(TCHAR [MAX_TABLE_NUMBER][TABLE_NAME_SIZE]);
int GetTableSize(TCHAR*);
int GetMaxNumOfRecords(TCHAR*);
int GetNumOfRecords(TCHAR*);
int GetTableVersion(TCHAR*);

int SaveData(TCHAR*);
int LoadData(TCHAR*);
int AutoSave(TCHAR*, int, BOOL);



int CreateTable(TableDef* TabDef)
{
	return DataAcController::GetInstance()->CreateTable(TabDef);
}

int DeleteTable(TCHAR* TableName)
{
	return DataAcController::GetInstance()->DeleteTable(TableName);
}

int LockTable(TCHAR* TableName, int Type)
{
	return DataAcController::GetInstance()->LockTable(TableName, Type);
}

int LockAllTable(int Type)
{
	return DataAcController::GetInstance()->LockAllTable(Type);
}

int UnlockTable(TCHAR* TableName)
{
	return DataAcController::GetInstance()->UnlockTable(TableName);
}

int UnlockAllTable()
{
	return DataAcController::GetInstance()->UnlockAllTable();
}

int InsertRecord(RecordData* RecDat)
{
	return DataAcController::GetInstance()->InsertRecord(RecDat);
}

int DeleteRecord(TCHAR* TableName)
{
	return DataAcController::GetInstance()->DeleteRecord(TableName);
}

int DeleteRecord(RecordData* RecDat)
{
	return DataAcController::GetInstance()->DeleteRecord(RecDat);
}

int UpdateRecord(RecordData* RecDat, RecordData* UdRecDat)
{
	return DataAcController::GetInstance()->UpdateRecord(RecDat, UdRecDat);
}

RecordData* GetRecord(TCHAR* TableName)
{
	return DataAcController::GetInstance()->GetRecord(TableName);
}

RecordData* GetRecord(RecordData* RecDat)
{
	return DataAcController::GetInstance()->GetRecord(RecDat);
}

int AzSortRecord(TCHAR* TableName, TCHAR* ColumnName)
{
	return DataAcController::GetInstance()->AzSortRecord(TableName, ColumnName);
}

int ZaSortRecord(TCHAR* TableName, TCHAR* ColumnName)
{
	return DataAcController::GetInstance()->ZaSortRecord(TableName, ColumnName);
}

void ClearRecordData(RecordData* RecDat)
{
	DataAcController::GetInstance()->ClearRecordData(RecDat);
}

int SaveData(TCHAR* FilePath)
{
	return DataAcController::GetInstance()->SaveData(FilePath);
}
int LoadData(TCHAR* FilePath)
{
	return DataAcController::GetInstance()->LoadData(FilePath);
}

int AutoSave(TCHAR* FilePath, int Sec, BOOL Flag)
{
	return DataAcController::GetInstance()->AutoSave(FilePath, Sec, Flag);
}

int GetMaxNumOfRecords(TCHAR* TableName)
{
	return DataAcController::GetInstance()->GetMaxNumOfRecords(TableName);
}

int GetNumOfRecords(TCHAR* TableName)
{
	return DataAcController::GetInstance()->GetNumOfRecords(TableName);
}

int GetColumnCount(TCHAR* TableName)
{
	return DataAcController::GetInstance()->GetColumnCount(TableName);
}

int GetColumnSize(TCHAR* TableName, TCHAR* ColumnName)
{
	return DataAcController::GetInstance()->GetColumnSize(TableName, ColumnName);
}

int GetColumnName(TCHAR* TableName, TCHAR ColumnNames[MAX_COLUMN_NUMBER][COLUMN_NAME_SIZE])
{
	return DataAcController::GetInstance()->GetColumnName(TableName, ColumnNames);
}

int GetColumnType(TCHAR* TableName, TCHAR* ColumnName)
{
	return DataAcController::GetInstance()->GetColumnType(TableName, ColumnName);
}

int GetTableCount()
{
	return DataAcController::GetInstance()->GetTableCount();
}

int GetTableName(TCHAR TableNames[MAX_TABLE_NUMBER][TABLE_NAME_SIZE])
{
	return DataAcController::GetInstance()->GetTableName(TableNames);
}

int GetTableSize(TCHAR* TableName)
{
	return DataAcController::GetInstance()->GetTableSize(TableName);
}

int GetTableVersion(TCHAR* TableName)
{
	return DataAcController::GetInstance()->GetTableVersion(TableName);
}
