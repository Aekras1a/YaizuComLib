#include <windows.h>
#include <stdio.h>
#include "..\..\src\stkdata\stkdata.h"
#include "..\..\src\stkdata\stkdataapi.h"


int BasicBinaryTest01()
{
	// 10�o�C�g�̃o�C�i���^�J�������܂ރe�[�u��"Bin-Test"��CreateTable�Ő����ł���
	printf("10�o�C�g�̃o�C�i���^�J�������܂ރe�[�u��\"Bin-Test\"��CreateTable�Ő����ł���");
	ColumnDefInt ColDefId(L"ID");
	ColumnDefBin ColDefImg1(L"Img1", 10);
	ColumnDefBin ColDefImg2(L"Img2", 10);
	TableDef TabDefTest(L"Bin-Test", 100);

	TabDefTest.AddColumnDef(&ColDefId);
	TabDefTest.AddColumnDef(&ColDefImg1);
	TabDefTest.AddColumnDef(&ColDefImg2);
	CreateTable(&TabDefTest);
	printf("...[OK]\r\n");

	// �e�[�u��"Bin-Test"��InsertRecord��1���R�[�h��ǉ�
	{
		printf("�e�[�u��\"Bin-Test\"��InsertRecord��1���R�[�h��ǉ�");
		ColumnData* ColDat[10];
		RecordData* RecDat;
		unsigned char one_img1[10] = {0x00, 0xFF, 0x01, 0x02, 0x03, 0x04, 0x05, 0x00, 0xFF, 0xFF};
		unsigned char one_img2[10] = {0x11, 0x22, 0x33, 0x44, 0x55, 0x00, 0x66, 0x00, 0x77, 0x00};
		ColDat[0] = new ColumnDataInt(L"ID", 10);
		ColDat[1] = new ColumnDataBin(L"Img1", one_img1, 10);
		ColDat[2] = new ColumnDataBin(L"Img2", one_img2, 10);
		RecDat = new RecordData(L"Bin-Test", ColDat, 3);
		LockTable(L"Bin-Test", 2);
		InsertRecord(RecDat);
		UnlockTable(L"Bin-Test");
		delete RecDat;
		printf("...[OK]\r\n");
	}

	// �e�[�u��"Bin-Test"��InsertRecord�ŘA�����ꂽ���R�[�h�R��ǉ�
	{
		printf("�e�[�u��\"Bin-Test\"��InsertRecord�ŘA�����ꂽ���R�[�h�R��ǉ�");
		ColumnData* ColDat1[10];
		ColumnData* ColDat2[10];
		ColumnData* ColDat3[10];
		RecordData* RecDat1;
		RecordData* RecDat2;
		RecordData* RecDat3;

		unsigned char one_img11[10] = {0xAB, 0xCD, 0xEF, 0x00, 0xFF, 0x10, 0x20, 0x30, 0x40, 0x50};
		unsigned char one_img12[10] = {0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF};
		ColDat1[0] = new ColumnDataInt(L"ID", 777);
		ColDat1[1] = new ColumnDataBin(L"Img1", one_img11, 10);
		ColDat1[2] = new ColumnDataBin(L"Img2", one_img12, 10);
		RecDat1 = new RecordData(L"Bin-Test", ColDat1, 3);

		unsigned char one_img21[10] = {0x00, 0xFF, 0x01, 0x02, 0x03, 0x04, 0x05, 0x00, 0xFF, 0xFF};
		unsigned char one_img22[10] = {0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF};
		ColDat2[0] = new ColumnDataInt(L"ID", -500);
		ColDat2[1] = new ColumnDataBin(L"Img1", one_img21, 10);
		ColDat2[2] = new ColumnDataBin(L"Img2", one_img22, 10);
		RecDat2 = new RecordData(L"Bin-Test", ColDat2, 3);
		RecDat1->SetNextRecord(RecDat2);

		unsigned char one_img31[10] = {0xAB, 0xCD, 0xEF, 0x00, 0xFF, 0x10, 0x20, 0x30, 0x40, 0x50};
		unsigned char one_img32[10] = {0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF};
		ColDat3[0] = new ColumnDataInt(L"ID", 10);
		ColDat3[1] = new ColumnDataBin(L"Img1", one_img31, 10);
		ColDat3[2] = new ColumnDataBin(L"Img2", one_img32, 10);
		RecDat3 = new RecordData(L"Bin-Test", ColDat3, 3);
		RecDat2->SetNextRecord(RecDat3);

		LockTable(L"Bin-Test", 2);
		InsertRecord(RecDat1);
		UnlockTable(L"Bin-Test");
		delete RecDat1;
		printf("...[OK]\r\n");
	}

	// �e�[�u��"Bin-Test"��InsertRecord��1���R�[�h��ǉ�
	{
		printf("�e�[�u��\"Bin-Test\"��InsertRecord��1���R�[�h��ǉ�");
		ColumnData* ColDat[10];
		RecordData* RecDat;
		unsigned char one_img1[10] = {0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF, 0x00, 0x00, 0x00, 0xFF};
		unsigned char one_img2[10] = {0xFF, 0xEE, 0xDD, 0xCC, 0xBB, 0xAA, 0x00, 0x00, 0x00, 0xFF};
		ColDat[0] = new ColumnDataInt(L"ID", 12345);
		ColDat[1] = new ColumnDataBin(L"Img1", one_img1, 10);
		ColDat[2] = new ColumnDataBin(L"Img2", one_img2, 10);
		RecDat = new RecordData(L"Bin-Test", ColDat, 3);
		LockTable(L"Bin-Test", 2);
		InsertRecord(RecDat);
		UnlockTable(L"Bin-Test");
		delete RecDat;
		printf("...[OK]\r\n");
	}

	return 0;
}

// �e�[�u��"Bin-Test"���̑S�Ẵ��R�[�h��GetRecrd(L"Bin-Test")�Ŏ擾���C�擾�����A�����R�[�h���K�؂ł��邱�Ƃ��m�F����
int BasicBinaryTest02()
{
	printf("�e�[�u��\"Bin-Test\"���̑S�Ẵ��R�[�h��GetRecrd(L\"Bin-Test\")�Ŏ擾���C�擾�����A�����R�[�h���K�؂ł��邱�Ƃ��m�F����");
	RecordData* RecDat;
	LockTable(L"Bin-Test", 1);
	RecDat = GetRecord(L"Bin-Test");
	UnlockTable(L"Bin-Test");
	RecordData* TopRecDat = RecDat;

	int Cnt = 0;
	int Err = 0;
	ColumnDataBin* ColBin1;
	ColumnDataBin* ColBin2;
	do {
		ColBin1 = (ColumnDataBin*)RecDat->GetColumn(1);
		ColBin2 = (ColumnDataBin*)RecDat->GetColumn(2);
		if (Cnt == 0) {
			unsigned char one_img1[10] = {0x00, 0xFF, 0x01, 0x02, 0x03, 0x04, 0x05, 0x00, 0xFF, 0xFF};
			unsigned char one_img2[10] = {0x11, 0x22, 0x33, 0x44, 0x55, 0x00, 0x66, 0x00, 0x77, 0x00};
			if (memcmp(ColBin1->GetValue(), one_img1, 10) != 0 || memcmp(ColBin2->GetValue(), one_img2, 10) != 0) {
				Err = 1;
				break;
			}
		}
		if (Cnt == 2) {
			unsigned char one_img1[10] = {0x00, 0xFF, 0x01, 0x02, 0x03, 0x04, 0x05, 0x00, 0xFF, 0xFF};
			unsigned char one_img2[10] = {0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF};
			if (memcmp(ColBin1->GetValue(), one_img1, 10) != 0 || memcmp(ColBin2->GetValue(), one_img2, 10) != 0) {
				Err = 1;
				break;
			}
		}
		if (Cnt == 4) {
			unsigned char one_img1[10] = {0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF, 0x00, 0x00, 0x00, 0xFF};
			unsigned char one_img2[10] = {0xFF, 0xEE, 0xDD, 0xCC, 0xBB, 0xAA, 0x00, 0x00, 0x00, 0xFF};
			if (memcmp(ColBin1->GetValue(), one_img1, 10) != 0 || memcmp(ColBin2->GetValue(), one_img2, 10) != 0) {
				Err = 1;
				break;
			}
		}
		Cnt++;
		RecDat = RecDat->GetNextRecord();
	} while (RecDat);

	delete TopRecDat;

	if (Err == 1 || Cnt != 5) {
		printf("...[NG]\r\n");
		return -1;
	}
	printf("...[OK]\r\n");
	return 0;
}

// �e�[�u��"Bin-Test"���̃��R�[�h��GetRecrd(Img1:�o�C�i���f�[�^�����w��)�Ŏ擾���C�擾�����A�����R�[�h���K�؂ł��邱�Ƃ��m�F����
int BasicBinaryTest04()
{
	printf("�e�[�u��\"Bin-Test\"���̃��R�[�h��GetRecrd(Img1:�o�C�i���f�[�^�����w��)�Ŏ擾���C�擾�����A�����R�[�h���K�؂ł��邱�Ƃ��m�F����");
	ColumnData* ColDat[10];
	RecordData* RecDat;
	RecordData* GetRecDat;
	unsigned char one_img[10] = {0x00, 0xFF, 0x01, 0x02, 0x03, 0x04, 0x05, 0x00, 0xFF, 0xFF};
	ColDat[0] = new ColumnDataBin(L"Img1", one_img, 10);
	RecDat = new RecordData(L"Bin-Test", ColDat, 1);
	LockTable(L"Bin-Test", 1);
	GetRecDat = GetRecord(RecDat);
	UnlockTable(L"Bin-Test");

	RecordData* RecDat1 = GetRecDat;
	unsigned char one_img1[10] = {0x11, 0x22, 0x33, 0x44, 0x55, 0x00, 0x66, 0x00, 0x77, 0x00};
	if (memcmp(((ColumnDataBin*)(RecDat1->GetColumn(2)))->GetValue(), one_img1, 10) != 0) {
		printf("...[NG]#1\r\n");
		return -1;
	}
	RecordData* RecDat2 = GetRecDat->GetNextRecord();
	unsigned char one_img2[10] = {0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF};
	if (memcmp(((ColumnDataBin*)(RecDat2->GetColumn(2)))->GetValue(), one_img2, 10) != 0) {
		printf("...[NG]#2\r\n");
		return -1;
	}
	RecordData* RecDat3 = RecDat2->GetNextRecord();
	if (RecDat3 != NULL) {
		printf("...[NG]#3\r\n");
		return -1;
	}

	delete RecDat;
	delete GetRecDat;
	printf("...[OK]\r\n");
	return 0;
}

// �e�[�u��"Bin-Test"���̃��R�[�h��GetRecrd(�����f�[�^�����w��)�Ŏ擾���C�擾�����A�����R�[�h���K�؂ł��邱�Ƃ��m�F����
int BasicBinaryTest05()
{
	printf("�e�[�u��\"Bin-Test\"���̃��R�[�h��GetRecrd(�����f�[�^�����w��)�Ŏ擾���C�擾�����A�����R�[�h���K�؂ł��邱�Ƃ��m�F����");
	ColumnData* ColDat[10];
	RecordData* RecDat;
	RecordData* GetRecDat;
	ColDat[0] = new ColumnDataInt(L"ID", 10);
	RecDat = new RecordData(L"Bin-Test", ColDat, 1);
	LockTable(L"Bin-Test", 1);
	GetRecDat = GetRecord(RecDat);
	UnlockTable(L"Bin-Test");

	RecordData* RecDat1 = GetRecDat;
	unsigned char one_img1[10] = {0x00, 0xFF, 0x01, 0x02, 0x03, 0x04, 0x05, 0x00, 0xFF, 0xFF};
	if (memcmp(((ColumnDataBin*)(RecDat1->GetColumn(1)))->GetValue(), one_img1, 10) != 0) {
		printf("...[NG]#1\r\n");
		return -1;
	}
	RecordData* RecDat2 = GetRecDat->GetNextRecord();
	unsigned char one_img2[10] = {0xAB, 0xCD, 0xEF, 0x00, 0xFF, 0x10, 0x20, 0x30, 0x40, 0x50};
	if (memcmp(((ColumnDataBin*)(RecDat2->GetColumn(1)))->GetValue(), one_img2, 10) != 0) {
		printf("...[NG]#2\r\n");
		return -1;
	}
	RecordData* RecDat3 = RecDat2->GetNextRecord();
	if (RecDat3 != NULL) {
		printf("...[NG]#3\r\n");
		return -1;
	}

	delete RecDat;
	delete GetRecDat;
	printf("...[OK]\r\n");
	return 0;
}

// �e�[�u��"Bin-Test"���̃��R�[�h��GetRecrd(Img2:�o�C�i���f�[�^�����w��)�Ŏ擾���C�擾�����A�����R�[�h���K�؂ł��邱�Ƃ��m�F����
int BasicBinaryTest06()
{
	printf("�e�[�u��\"Bin-Test\"���̃��R�[�h��GetRecrd(Img2:�o�C�i���f�[�^�����w��)�Ŏ擾���C�擾�����A�����R�[�h���K�؂ł��邱�Ƃ��m�F����");
	ColumnData* ColDat[10];
	RecordData* RecDat;
	RecordData* GetRecDat;
	unsigned char one_img[10] = {0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF};
	ColDat[0] = new ColumnDataBin(L"Img2", one_img, 10);
	RecDat = new RecordData(L"Bin-Test", ColDat, 1);
	LockTable(L"Bin-Test", 1);
	GetRecDat = GetRecord(RecDat);
	UnlockTable(L"Bin-Test");

	RecordData* RecDat1 = GetRecDat;
	unsigned char one_img1[10] = {0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF};
	if (memcmp(((ColumnDataBin*)(RecDat1->GetColumn(2)))->GetValue(), one_img1, 10) != 0) {
		printf("...[NG]#1\r\n");
		return -1;
	}
	RecordData* RecDat2 = GetRecDat->GetNextRecord();
	unsigned char one_img2[10] = {0x00, 0xFF, 0x01, 0x02, 0x03, 0x04, 0x05, 0x00, 0xFF, 0xFF};
	if (memcmp(((ColumnDataBin*)(RecDat2->GetColumn(1)))->GetValue(), one_img2, 10) != 0) {
		printf("...[NG]#2\r\n");
		return -1;
	}
	RecordData* RecDat3 = RecDat2->GetNextRecord();
	RecordData* RecDat4 = RecDat3->GetNextRecord();
	if (RecDat4 != NULL) {
		printf("...[NG]#3\r\n");
		return -1;
	}

	delete RecDat;
	delete GetRecDat;
	printf("...[OK]\r\n");
	return 0;
}

// �e�[�u��"Bin-Test"���̃��R�[�h��GetRecrd(Img1, Img2:�o�C�i���f�[�^�����w��)�Ŏ擾���C�擾�����A�����R�[�h���K�؂ł��邱�Ƃ��m�F����
int BasicBinaryTest07()
{
	printf("�e�[�u��\"Bin-Test\"���̃��R�[�h��GetRecrd(Img1, Img2:�o�C�i���f�[�^�����w��)�Ŏ擾���C�擾�����A�����R�[�h���K�؂ł��邱�Ƃ��m�F����");
	ColumnData* ColDat[10];
	RecordData* RecDat;
	RecordData* GetRecDat;
	unsigned char one_img1[10] = {0x00, 0xFF, 0x01, 0x02, 0x03, 0x04, 0x05, 0x00, 0xFF, 0xFF};
	unsigned char one_img2[10] = {0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF};
	ColDat[0] = new ColumnDataBin(L"Img1", one_img1, 10);
	ColDat[1] = new ColumnDataBin(L"Img2", one_img2, 10);
	RecDat = new RecordData(L"Bin-Test", ColDat, 2);
	LockTable(L"Bin-Test", 1);
	GetRecDat = GetRecord(RecDat);
	UnlockTable(L"Bin-Test");

	RecordData* RecDat1 = GetRecDat;
	if (((ColumnDataInt*)(RecDat1->GetColumn(0)))->GetValue() != -500) {
		printf("...[NG]#4\r\n");
		return -1;
	}
	RecordData* RecDat2 = GetRecDat->GetNextRecord();
	if (RecDat2 != NULL) {
		printf("...[NG]#4\r\n");
		return -1;
	}

	delete RecDat;
	delete GetRecDat;
	printf("...[OK]\r\n");
	return 0;
}

// �e�[�u��"Bin-Test"���̃��R�[�h��GetRecrd(Img1, Img2:�����̘A�����ꂽ���R�[�h�ɂ��o�C�i���f�[�^�����w��)�Ŏ擾���C�擾�����A�����R�[�h���K�؂ł��邱�Ƃ��m�F����
int BasicBinaryTest08()
{
	printf("�e�[�u��\"Bin-Test\"���̃��R�[�h��GetRecrd(Img1, Img2:�����̘A�����ꂽ���R�[�h�ɂ��o�C�i���f�[�^�����w��)�Ŏ擾���C�擾�����A�����R�[�h���K�؂ł��邱�Ƃ��m�F����");
	ColumnData* ColDat[10];
	RecordData* RecDat1;
	RecordData* RecDat2;
	RecordData* GetRecDat;

	unsigned char one_img1[10] = {0x00, 0xFF, 0x01, 0x02, 0x03, 0x04, 0x05, 0x00, 0xFF, 0xFF};
	ColDat[0] = new ColumnDataBin(L"Img1", one_img1, 10);
	RecDat1 = new RecordData(L"Bin-Test", ColDat, 1);

	unsigned char one_img2[10] = {0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF, 0x00, 0x00, 0x00, 0xFF};
	ColDat[0] = new ColumnDataBin(L"Img1", one_img2, 10);
	RecDat2 = new RecordData(L"Bin-Test", ColDat, 1);
	RecDat1->SetNextRecord(RecDat2);

	LockTable(L"Bin-Test", 1);
	GetRecDat = GetRecord(RecDat1);
	UnlockTable(L"Bin-Test");

	RecordData* RecoDat1 = GetRecDat;
	RecordData* RecoDat2 = RecoDat1->GetNextRecord();
	RecordData* RecoDat3 = RecoDat2->GetNextRecord();
	RecordData* RecoDat4 = RecoDat3->GetNextRecord();
	if (RecoDat4 != NULL) {
		printf("...[NG]#4\r\n");
		return -1;
	}

	delete RecDat1;
	delete GetRecDat;
	printf("...[OK]\r\n");
	return 0;
}

// 2�̘A���������R�[�h(�o�C�i���f�[�^�J�����L��)���w�肵�ăo�C�i���f�[�^��UpdateRecord�ōX�V����
int BasicBinaryTest09()
{
	printf("2�̘A���������R�[�h(�o�C�i���f�[�^�J�����L��)���w�肵�ăo�C�i���f�[�^��UpdateRecord�ōX�V����");
	ColumnData* ColDat[10];
	RecordData* RecDat1;
	RecordData* RecDat2;
	RecordData* RecDat3;
	RecordData* GetRecDat;

	unsigned char one_img1[10] = {0x00, 0xFF, 0x01, 0x02, 0x03, 0x04, 0x05, 0x00, 0xFF, 0xFF};
	ColDat[0] = new ColumnDataBin(L"Img1", one_img1, 10);
	RecDat1 = new RecordData(L"Bin-Test", ColDat, 1);

	unsigned char one_img2[10] = {0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF, 0x00, 0x00, 0x00, 0xFF};
	ColDat[0] = new ColumnDataBin(L"Img1", one_img2, 10);
	RecDat2 = new RecordData(L"Bin-Test", ColDat, 1);
	RecDat1->SetNextRecord(RecDat2);

	unsigned char one_img3[10] = {0x39, 0x39, 0x39, 0x39, 0x39, 0x19, 0x19, 0x19, 0x19, 0x19};
	ColDat[0] = new ColumnDataBin(L"Img2", one_img3, 10);
	RecDat3 = new RecordData(L"Bin-Test", ColDat, 1);

	LockTable(L"Bin-Test", 2);
	UpdateRecord(RecDat1, RecDat3);
	UnlockTable(L"Bin-Test");

	LockTable(L"Bin-Test", 1);
	GetRecDat = GetRecord(RecDat3);
	UnlockTable(L"Bin-Test");

	RecordData* Top = GetRecDat;
	for (int i = 0; i < 3; i++) {
		ColumnDataBin* img1 = (ColumnDataBin*)GetRecDat->GetColumn(2);
		if (memcmp(img1->GetValue(), one_img3, 10) != 0) {
			printf("...[NG]#1\r\n");
			return -1;
		}
		ColumnDataInt* Id = (ColumnDataInt*)GetRecDat->GetColumn(0);
		if (i == 0 && Id->GetValue() != 10) {
			printf("...[NG]#2\r\n");
			return -1;
		}
		if (i == 1 && Id->GetValue() != -500) {
			printf("...[NG]#3\r\n");
			return -1;
		}
		if (i == 2 && Id->GetValue() != 12345) {
			printf("...[NG]#4\r\n");
			return -1;
		}
		GetRecDat = GetRecDat->GetNextRecord();
	}
	if (GetRecDat != NULL) {
		printf("...[NG]\r\n");
		return -1;
	}
	printf("...[OK]\r\n");

	// �o�C�i���^�J����"Img2"���w�肵�ă��R�[�h���~���\�[�g���K���Ƀ\�[�g����Ă���
	{
		printf("�o�C�i���^�J����\"Img2\"���w�肵�ă��R�[�h���~���\�[�g���K���Ƀ\�[�g����Ă���");
		LockTable(L"Bin-Test", LOCK_EXCLUSIVE);
		if (ZaSortRecord(L"Bin-Test", L"Img2") != 0) {
			printf("...[NG]\r\n");
			return -1;
		}
		RecordData* Top = GetRecord(L"Bin-Test");
		UnlockTable(L"Bin-Test");
		RecordData* Cul = Top;
		ColumnDataInt* Col = (ColumnDataInt*)Cul->GetColumn(0);
		int Val = Col->GetValue();
		if (Val != 12345) {
			printf("...[NG]\r\n");
			return -1;
		}
		delete Top;
		printf("...[OK]\r\n");
	}

	// Img1���\�[�g�ōŏ��ƕ]������郌�R�[�h��ǉ���C�o�C�i���^�J����"Img1"���w�肵�ă��R�[�h�������\�[�g���遨�K���Ƀ\�[�g����Ă���
	{
		printf("Img1���\�[�g�ōŏ��ƕ]������郌�R�[�h��ǉ���C�o�C�i���^�J����\"Img1\"���w�肵�ă��R�[�h�������\�[�g���遨�K���Ƀ\�[�g����Ă���");
		ColumnData* ColDat[10];
		RecordData* RecDat;
		unsigned char one_img1[10] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF};
		unsigned char one_img2[10] = {0xcc, 0x2a, 0x3b, 0xcc, 0x5d, 0x6e, 0xcc, 0x00, 0x00, 0x00};
		ColDat[0] = new ColumnDataInt(L"ID", 9292);
		ColDat[1] = new ColumnDataBin(L"Img1", one_img1, 10);
		ColDat[2] = new ColumnDataBin(L"Img2", one_img2, 10);
		RecDat = new RecordData(L"Bin-Test", ColDat, 3);
		LockTable(L"Bin-Test", 2);
		InsertRecord(RecDat);
		UnlockTable(L"Bin-Test");
		delete RecDat;

		LockTable(L"Bin-Test", LOCK_EXCLUSIVE);
		if (AzSortRecord(L"Bin-Test", L"Img1") != 0) {
			printf("...[NG]\r\n");
			return -1;
		}
		RecordData* Top = GetRecord(L"Bin-Test");
		UnlockTable(L"Bin-Test");
		RecordData* Cul = Top;
		ColumnDataInt* Col = (ColumnDataInt*)Cul->GetColumn(0);
		int Val = Col->GetValue();
		if (Val != 9292) {
			printf("...[NG]\r\n");
			return -1;
		}
		delete Top;
		printf("...[OK]\r\n");
	}

	// �o�C�i���f�[�^�����������ɂ��ă��R�[�h���폜����
	printf("�o�C�i���f�[�^�����������ɂ��ă��R�[�h���폜����");
	LockTable(L"Bin-Test", 2);
	DeleteRecord(RecDat3);
	UnlockTable(L"Bin-Test");

	delete RecDat1;
	delete RecDat3;
	delete Top;

	if (DeleteTable(L"Bin-Test") != 0) {
		printf("...[NG]\r\n");
		return -1;
	}
	printf("...[OK]\r\n");
	return 0;
}

// 1MB(�o�C�i���^�J����) * 32 * 10 = 320MB�̃e�[�u��"LargeBinTable"��CreateTable�ō쐬���C���̌�DeleteTable�ō폜����
// 2MB(�o�C�i���^�J����) * 32 * 10 = 640MB�̃e�[�u��"LargeBinTable"��CreateTable�ō쐬���C���̌�DeleteTable�ō폜����
int LargeBinaryTableTest01()
{
	TableDef* LargeBinTable;
	ColumnDefBin* ColDef[32];
	for (int i = 1000000; i < 2000001; i += 1000000) {
		if (i == 1000000) {
			printf("1MB(�o�C�i���^�J����) * 32 * 10 = 320MB�̃e�[�u��\"LargeBinTable\"��CreateTable�ō쐬���C���̌�DeleteTable�ō폜����");
		} else {
			printf("2MB(�o�C�i���^�J����) * 32 * 10 = 640MB�̃e�[�u��\"LargeBinTable\"��CreateTable�ō쐬���C���̌�DeleteTable�ō폜����");
		}

		LargeBinTable = new TableDef(L"LargeBinTable", 10);
		for (int j = 0; j < 32; j++) {
			wchar_t ColName[16];
			wsprintf(ColName, L"BinBin%d", j);
			ColDef[j] = new ColumnDefBin(ColName, i);
			LargeBinTable->AddColumnDef(ColDef[j]);
		}
		int Ret = CreateTable(LargeBinTable);
		if (Ret != 0) {
			wchar_t MsgBuf[256];
			wsprintf(MsgBuf, L"�e�[�u���쐬�Ɏ��s���܂���  %d", i);
			return -1;
		}
		for (int j = 0; j < 32; j++) {
			delete ColDef[j];
		}
		delete LargeBinTable;
		if (DeleteTable(L"LargeBinTable") != 0) {
			wchar_t MsgBuf[256];
			wsprintf(MsgBuf, L"�e�[�u���폜�Ɏ��s���܂���  %d", i);
			return -1;
		}
		printf("...[OK]\r\n");
	}

	return 0;
}

// 6MB * 64 = 384MB�̃e�[�u��"LargeBinTable2"��CreateTable�ō쐬�ł���
// 6MB�̃o�C�i���f�[�^���܂ރ��R�[�h��64��InsertRecord�Œǉ�����B
int LargeBinaryTableTest02()
{
	printf("6MB * 64 = 384MB�̃e�[�u��\"LargeBinTable2\"��CreateTable�ō쐬�ł���");
	TableDef* LargeBinTable;
	ColumnDef* ColDef[32];
	LargeBinTable = new TableDef(L"LargeBinTable2", 64);
	ColDef[0] = new ColumnDefInt(L"ID");
	ColDef[1] = new ColumnDefBin(L"Data", 6000000);
	LargeBinTable->AddColumnDef(ColDef[0]);
	LargeBinTable->AddColumnDef(ColDef[1]);
	int Ret = CreateTable(LargeBinTable);
	if (Ret != 0) {
		printf("...[NG]\r\n");
		return -1;
	}
	printf("...[OK]\r\n");

	printf("6MB�̃o�C�i���f�[�^���܂ރ��R�[�h��64��InsertRecord�Œǉ�����");
	unsigned char *Dat = new unsigned char[6000000];
	for (int i = 0; i < 6000000; i++) {
		Dat[i] = 127;
	}
	ColumnData* ColDat[3];
	RecordData* RecDat;
	LockTable(L"LargeBinTable2", 2);
	for (int i = 0; i < 64; i++) {
		ColDat[0] = new ColumnDataInt(L"ID", i);
		ColDat[1] = new ColumnDataBin(L"Data", Dat, 6000000);
		RecDat = new RecordData(L"LargeBinTable2", ColDat, 2);
		InsertRecord(RecDat);
		delete RecDat;
	}
	UnlockTable(L"LargeBinTable2");
	if (DeleteTable(L"LargeBinTable2") != 0) {
		printf("...[NG]\r\n");
		return -1;
	}
	printf("...[OK]\r\n");

	return 0;
}

/*
BinaryTest
�E10�o�C�g�̃o�C�i���^�J�������܂ރe�[�u��"Bin-Test"��CreateTable�Ő����ł���
�E�e�[�u��"Bin-Test"��InsertRecord��1���R�[�h��ǉ�
�E�e�[�u��"Bin-Test"��InsertRecord�ŘA�����ꂽ���R�[�h�R��ǉ�
�E�e�[�u��"Bin-Test"��InsertRecord��1���R�[�h��ǉ�
�E�e�[�u��"Bin-Test"���̑S�Ẵ��R�[�h��GetRecrd(L"Bin-Test")�Ŏ擾���C�擾�����A�����R�[�h���K�؂ł��邱�Ƃ��m�F����
�E�e�[�u��"Bin-Test"���̃��R�[�h��GetRecrd(Img1:�o�C�i���f�[�^�����w��)�Ŏ擾���C�擾�����A�����R�[�h���K�؂ł��邱�Ƃ��m�F����
�E�e�[�u��"Bin-Test"���̃��R�[�h��GetRecrd(�����f�[�^�����w��)�Ŏ擾���C�擾�����A�����R�[�h���K�؂ł��邱�Ƃ��m�F����
�E�e�[�u��"Bin-Test"���̃��R�[�h��GetRecrd(Img2:�o�C�i���f�[�^�����w��)�Ŏ擾���C�擾�����A�����R�[�h���K�؂ł��邱�Ƃ��m�F����
�E�e�[�u��"Bin-Test"���̃��R�[�h��GetRecrd(Img1, Img2:�o�C�i���f�[�^�����w��)�Ŏ擾���C�擾�����A�����R�[�h���K�؂ł��邱�Ƃ��m�F����
�E�e�[�u��"Bin-Test"���̃��R�[�h��GetRecrd(Img1, Img2:�����̘A�����ꂽ���R�[�h�ɂ��o�C�i���f�[�^�����w��)�Ŏ擾���C�擾�����A�����R�[�h���K�؂ł��邱�Ƃ��m�F����
�E2�̘A���������R�[�h(�o�C�i���f�[�^�J�����L��)���w�肵�ăo�C�i���f�[�^��UpdateRecord�ōX�V����
�E�o�C�i���^�J����"Img2"���w�肵�ă��R�[�h���~���\�[�g���K���Ƀ\�[�g����Ă���
�EImg1���\�[�g�ōŏ��ƕ]������郌�R�[�h��ǉ���C�o�C�i���^�J����"Img1"���w�肵�ă��R�[�h�������\�[�g���遨�K���Ƀ\�[�g����Ă���
�E�o�C�i���f�[�^�����������ɂ���DeleteRecord�Ń��R�[�h���폜����
�E1MB(�o�C�i���^�J����) * 32 * 10 = 320MB�̃e�[�u��"LargeBinTable"��CreateTable�ō쐬���C���̌�DeleteTable�ō폜����
�E2MB(�o�C�i���^�J����) * 32 * 10 = 640MB�̃e�[�u��"LargeBinTable"��CreateTable�ō쐬���C���̌�DeleteTable�ō폜����
�E6MB * 64 = 384MB�̃e�[�u��"LargeBinTable2"��CreateTable�ō쐬�ł���
�E6MB�̃o�C�i���f�[�^���܂ރ��R�[�h��64��InsertRecord�Œǉ�����B
*/
int BinaryTest()
{
	if (BasicBinaryTest01() != 0) {
		return -1;
	}
	if (BasicBinaryTest02() != 0) {
		return -1;
	}
	if (BasicBinaryTest04() != 0) {
		return -1;
	}
	if (BasicBinaryTest05() != 0) {
		return -1;
	}
	if (BasicBinaryTest06() != 0) {
		return -1;
	}
	if (BasicBinaryTest07() != 0) {
		return -1;
	}
	if (BasicBinaryTest08() != 0) {
		return -1;
	}
	if (BasicBinaryTest09() != 0) {
		return -1;
	}
	if (LargeBinaryTableTest01() != 0) {
		return -1;
	}
	if (LargeBinaryTableTest02() != 0) {
		return -1;
	}
	return 0;
}
