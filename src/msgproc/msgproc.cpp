#include "msgproc.h"

MessageProc* MessageProc::Instance = NULL;

class MessageProc::Impl
{
public:
	static const int ENG = 0;
	static const int JPN = 1;

	static const int MAX_MSG_COUNT = 10000;

	int Mode;

	TCHAR* StkMsg[MAX_MSG_COUNT][2];
	BYTE* StkMsgSjis[MAX_MSG_COUNT][2];

	void Eng(int, TCHAR*);
	void Jpn(int, TCHAR*);

	void AllClear();

	int GetLocale();
};

int MessageProc::Impl::GetLocale()
{
	if (Mode == MessageProc::LOCALE_MODE_WIN32) {
		TCHAR Buf[256];
		GetLocaleInfo(GetUserDefaultLCID(), LOCALE_SENGLANGUAGE, Buf, 256);
		if (lstrcmp(Buf, _T("Japanese")) == 0) { // "XXX" or "Japanese"
			return MessageProc::MLANG_JAPANESE;
		}
		return MessageProc::MLANG_ENGLISH;
	}
	if (Mode == MessageProc::LOCALE_MODE_WEB) {
		char* Locale;
		size_t LocaleSize;
		if (_dupenv_s(&Locale, &LocaleSize, "HTTP_ACCEPT_LANGUAGE") == 0) {
			if (Locale == 0 || LocaleSize ==0) {
				return 0;
			}
			if (strstr(Locale, (char*)"ja") == Locale) {
				free(Locale);
				return MessageProc::MLANG_JAPANESE;
			}
		}
		return MessageProc::MLANG_ENGLISH;
	}
	if (Mode == MessageProc::LOCALE_MODE_ENGLISH) {
		return MessageProc::MLANG_ENGLISH;
	}
	if (Mode == MessageProc::LOCALE_MODE_JAPANESE) {
		return MessageProc::MLANG_JAPANESE;
	}
	return MessageProc::MLANG_ENGLISH;
}

void MessageProc::Impl::Eng(int Id, TCHAR* Msg)
{
	if (StkMsg[Id][ENG] != NULL) {
		delete StkMsg[Id][ENG];
	}
	int WcBufLen = lstrlen(Msg);
	StkMsg[Id][ENG] = new TCHAR[WcBufLen + 1];
	lstrcpyn(StkMsg[Id][ENG], Msg, WcBufLen + 1);

	if (StkMsgSjis[Id][ENG] != NULL) {
		delete StkMsgSjis[Id][ENG];
	}
	int MltBufLen = WideCharToMultiByte(CP_THREAD_ACP, 0, Msg, -1, (LPSTR)NULL, 0, NULL, NULL);
	StkMsgSjis[Id][ENG] = (BYTE*)new CHAR[MltBufLen];
	if (WideCharToMultiByte(CP_THREAD_ACP, 0, Msg, -1, (LPSTR)StkMsgSjis[Id][ENG], MltBufLen, NULL, NULL) != 0) {
		StkMsgSjis[Id][ENG][MltBufLen - 1] = 0;
	}
}

void MessageProc::Impl::Jpn(int Id, TCHAR* Msg)
{
	if (StkMsg[Id][JPN] != NULL) {
		delete StkMsg[Id][JPN];
	}
	int WcBufLen = lstrlen(Msg);
	StkMsg[Id][JPN] = new TCHAR[WcBufLen + 1];
	lstrcpyn(StkMsg[Id][JPN], Msg, WcBufLen + 1);

	if (StkMsgSjis[Id][JPN] != NULL) {
		delete StkMsgSjis[Id][JPN];
	}
	int MltBufLen = WideCharToMultiByte(CP_THREAD_ACP, 0, Msg, -1, (LPSTR)NULL, 0, NULL, NULL);
	StkMsgSjis[Id][JPN] = (BYTE*)new CHAR[MltBufLen];
	if (WideCharToMultiByte(CP_THREAD_ACP, 0, Msg, -1, (LPSTR)StkMsgSjis[Id][JPN], MltBufLen, NULL, NULL) != 0) {
		StkMsgSjis[Id][JPN][MltBufLen - 1] = 0;
	}
}

// This function clears all of messages without memory release of existing allocated message
void MessageProc::Impl::AllClear()
{
	for (int Loop = 0; Loop < Impl::MAX_MSG_COUNT; Loop++) {
		StkMsg[Loop][ENG] = NULL;
		StkMsg[Loop][JPN] = NULL;
		StkMsgSjis[Loop][ENG] = NULL;
		StkMsgSjis[Loop][JPN] = NULL;
	}
}

MessageProc::MessageProc()
{
	pImpl = new Impl;
	pImpl->Mode = MessageProc::LOCALE_MODE_WIN32;
	pImpl->AllClear();

	// =====================================================================================================
	//2201 (NC2)
	pImpl->Jpn(VAR_SELECTEDNOTONE, _T("�ϐ����w�肳��Ă��Ȃ����C2�ȏ�̕ϐ����w�肳��܂����B\r\n1�̕ϐ��̂ݎw��\�ł��B"));
	pImpl->Eng(VAR_SELECTEDNOTONE, _T("No variable or more than one variable has been specified.\r\nOnly one variable may be specified."));

	//2202 (NC2)
	pImpl->Jpn(VAR_AREYOUSUREDELETE, _T("�w�肵���ϐ����폜���Ă��ǂ��ł����B"));
	pImpl->Eng(VAR_AREYOUSUREDELETE, _T("Are you sure you want to delete the specified variable(s)?"));

	//2203 (NC2)
	pImpl->Jpn(VAR_NOITEMSELECTED, _T("�ϐ����w�肳��Ă��܂���B\r\n�P�ȏ�̕ϐ����w�肷��K�v������܂��B"));
	pImpl->Eng(VAR_NOITEMSELECTED, _T("No variable has been specified.\r\nPlease specify one or more variables."));

	//2204 (NC2)
	pImpl->Jpn(VAR_NOTTRANSUTF8, _T("UTF-8�ɕϊ��ł��Ȃ��R�[�h�����݂��邽�߁C\r\nUFT-8�\����ʂɑJ�ڂł��܂���B"));
	pImpl->Eng(VAR_NOTTRANSUTF8, _T("The screen cannot be changed to UTF-8 view \r\nbecause the program has found code that cannot be rendered in UTF-8."));

	//2205 (NC2)
	pImpl->Jpn(VAR_INVALIDNAME, _T("�s���ȕϐ������w�肳��܂����B\r\n�w�肵���ϐ������m�F���čēx���s���Ă��������B"));
	pImpl->Eng(VAR_INVALIDNAME, _T("Invalid variable name specified.\r\nCheck the specified variable name and then try again."));

	//2206 (NC2)
	pImpl->Jpn(VAR_ALREADYDELETED, _T("�ҏW�Ώۂ̕ϐ��͊��ɍ폜����Ă��܂��B\r\n�ҏW����͎��s�ł��܂���B"));
	pImpl->Eng(VAR_ALREADYDELETED, _T("The edit operation can not be performed because \r\nthe edit target variable has been deleted."));

	//2207 (NC2)
	pImpl->Jpn(VAR_INVALIDTYPE, _T("�ҏW�Ώۂ̕ϐ��͊��ɈقȂ��ʂ̕ϐ��Ƃ��Ďg�p����Ă��܂��B\r\n�ҏW����͎��s�ł��܂���B"));
	pImpl->Eng(VAR_INVALIDTYPE, _T("The edit operation can not be performed because \r\nthe target variable has already been used as another type of variable."));

	//2208 (NC3)
	pImpl->Jpn(VAR_BUFOVERFLOW, _T("�ϐ��̒����������10M�o�C�g�𒴂��܂����B\r\n����𒴂����f�[�^�͐؂����܂��B"));
	pImpl->Eng(VAR_BUFOVERFLOW, _T("The length of the variable specified exceeds the upper limit of 10 MB.\r\nAny data over this limit will be omitted."));

	//2209 (NC2)
	pImpl->Jpn(VAR_MAXVARSIZE, _T("�ϐ����i�[���郁�����e�ʂ�����𒴂��܂����B"));
	pImpl->Eng(VAR_MAXVARSIZE, _T("The memory size available for storing variable data has exceeded the upper limit."));

	//2210 (NC3)
	pImpl->Jpn(VAR_FLAGVARNOT, _T("�t���O�p�ϐ��́C�C���|�[�g�^�G�N�X�|�[�g���s�����Ƃ͂ł��܂���B"));
	pImpl->Eng(VAR_FLAGVARNOT, _T("Import/export operation of the flag variable cannot be performed."));

	//2211 (NC3)
	pImpl->Jpn(VAR_FOLDERSETERR, _T("�w�肳�ꂽ�C���|�[�g�C�G�N�X�|�[�g�t�H���_�͕s���ł��B\r\n�t�H���_���m�F���C�ēx��������s���Ă��������B"));
	pImpl->Eng(VAR_FOLDERSETERR, _T("An invalid import/export folder has been specified.\r\nCheck the folder and try again."));

	//2212 (NC3)
	pImpl->Jpn(VAR_IMPERR, _T("�C���|�[�g���삪���s���܂����B\r\n�t�H���_�̃A�N�Z�X�����܂��̓t�@�C�������m�F���Ă��������B"));
	pImpl->Eng(VAR_IMPERR, _T("Import operation failed.\r\nCheck the folder permissions and file names."));

	//2213 (NC3)
	pImpl->Jpn(VAR_EXPERR, _T("�G�N�X�|�[�g���삪���s���܂����B\r\n�t�H���_�̃A�N�Z�X������󂫃f�B�X�N�e�ʁC�I�������ϐ������m�F���Ă��������B"));
	pImpl->Eng(VAR_EXPERR, _T("Export operation failed.\r\nCheck the folder permissions, the amount of free disk space and the variable names specified."));

	//2214 (NC3)
	pImpl->Jpn(VAR_NOIMPTARGET, _T("�w�肵���t�H���_�ɂ̓C���|�[�g�Ώۃt�@�C�������݂��܂���B\r\n�C���|�[�g�Ώۃt�@�C���̊g���q��\".xxx\"�ł���K�v������܂��B"));
	pImpl->Eng(VAR_NOIMPTARGET, _T("No import target file exists in the folder specified.\r\nThe extension of import target files must be \".xxx\"."));

	//2215 (NC3)
	pImpl->Jpn(VAR_NOEXPTARGET, _T("�ϐ����w�肳��Ă��܂���B\r\n��ȏ�̕ϐ����w�肷��K�v������܂��B"));
	pImpl->Eng(VAR_NOEXPTARGET, _T("No variables have been specified.\r\nMore than one variable must be specified."));

	// =====================================================================================================
	// 2300 (---)
	pImpl->Jpn(PROP_NAME, _T("����"));
	pImpl->Eng(PROP_NAME, _T("Name"));

	// 2301 (NC2)
	pImpl->Jpn(PROP_CHKDAT_START, _T("���̓f�[�^��...����J�n����"));
	pImpl->Eng(PROP_CHKDAT_START, _T("Input data starts with..."));

	// 2302 (NC2)
	pImpl->Jpn(PROP_CHKDAT_NSTART, _T("���̓f�[�^��...����J�n���Ȃ�"));
	pImpl->Eng(PROP_CHKDAT_NSTART, _T("Input data does not start with..."));

	// 2303 (NC2)
	pImpl->Jpn(PROP_CHKDAT_END, _T("���̓f�[�^��...�ŏI������"));
	pImpl->Eng(PROP_CHKDAT_END, _T("Input data ends with..."));

	// 2304 (NC2)
	pImpl->Jpn(PROP_CHKDAT_NEND, _T("���̓f�[�^��...�ŏI�����Ȃ�"));
	pImpl->Eng(PROP_CHKDAT_NEND, _T("Input data does not end with..."));

	// 2305 (NC2)
	pImpl->Jpn(PROP_CHKDAT_CONT, _T("���̓f�[�^��...���܂�"));
	pImpl->Eng(PROP_CHKDAT_CONT, _T("Input data contains..."));

	// 2306 (NC2)
	pImpl->Jpn(PROP_CHKDAT_NCONT, _T("���̓f�[�^��...���܂܂Ȃ�"));
	pImpl->Eng(PROP_CHKDAT_NCONT, _T("Input data does not contain..."));

	// 2307 (NC2)
	pImpl->Jpn(PROP_CHKDAT_EQUAL, _T("���̓f�[�^��...�ƈ�v����"));
	pImpl->Eng(PROP_CHKDAT_EQUAL, _T("Input data is equal to..."));

	// 2308 (NC2)
	pImpl->Jpn(PROP_CHKDAT_NEQUAL, _T("���̓f�[�^��...�ƈ�v���Ȃ�"));
	pImpl->Eng(PROP_CHKDAT_NEQUAL, _T("Input data is not equal to..."));

	// 2311 (NC2)
	pImpl->Jpn(PROP_CHGDAT_INSERT, _T("���̓f�[�^�̊J�n�o�C�g��(A)��}������"));
	pImpl->Eng(PROP_CHGDAT_INSERT, _T("Insert (A) at the start byte of the input data."));

	// 2312 (NC2)
	pImpl->Jpn(PROP_CHGDAT_JOIN, _T("���̓f�[�^�̏I���o�C�g��(A)��A������"));
	pImpl->Eng(PROP_CHGDAT_JOIN, _T("Join (A) to the end byte of the input data."));

	// 2313 (NC2)
	pImpl->Jpn(PROP_CHGDAT_REPLACE, _T("���̓f�[�^����(A)��������(B)�ɒu��������"));
	pImpl->Eng(PROP_CHGDAT_REPLACE, _T("Search for (A) in the input data and replace with (B)."));

	// 2314 (NC2)
	pImpl->Jpn(PROP_CHGDAT_EXTRACT, _T("���̓f�[�^����(A)�Ŏn�܂�(B)�ŏI���̈�𒊏o����"));
	pImpl->Eng(PROP_CHGDAT_EXTRACT, _T("Extract an area that starts with (A) and ends with (B) from the input data."));

	// 2315 (NC2)
	pImpl->Jpn(PROP_CHGDAT_DROP, _T("���̓f�[�^���̂ċ�f�[�^��Ԃ�"));
	pImpl->Eng(PROP_CHGDAT_DROP, _T("Drop the input data and return empty data."));

	// 2316 (NC2)
	pImpl->Jpn(PROP_CHGDAT_RESET, _T("���̓f�[�^���̂�(A)�Ƀ��Z�b�g����"));
	pImpl->Eng(PROP_CHGDAT_RESET, _T("Drop the input data and reset to (A)."));

	// 2320 (NC2)
	pImpl->Jpn(PROP_CLOSEPORT, _T("�N���[�Y����\�P�b�g"));
	pImpl->Eng(PROP_CLOSEPORT, _T("Socket to be closed"));

	// 2321 (NC2)
	pImpl->Jpn(PROP_TIMER_PAST, _T("���Ɏ������t�Ǝ������o�߂����玟�̃X�e�b�v�Ɉڂ�"));
	pImpl->Eng(PROP_TIMER_PAST, _T("Progress to the next step if the date and time shown below are in the past."));

	// 2322 (NC2)
	pImpl->Jpn(PROP_TIMER_WAIT, _T("��莞�ԑ҂������Ǝ��̃X�e�b�v�Ɉڂ�"));
	pImpl->Eng(PROP_TIMER_WAIT, _T("Progress to the next step after sleeping."));

	// 2323 (---)
	pImpl->Jpn(PROP_TIMER_SEC, _T("(�b) 0-3600"));
	pImpl->Eng(PROP_TIMER_SEC, _T("(Sec) 0-3600"));

	// 2324 (NC2)
	pImpl->Jpn(PROP_MAP_SEARCH, _T("�����Ώەϐ����̃v���t�B�b�N�X"));
	pImpl->Eng(PROP_MAP_SEARCH, _T("Prefix of search target variable name."));

	// 2325 (NC2)
	pImpl->Jpn(PROP_MAP_REPLACE, _T("�u�����Ώەϐ����̃v���t�B�b�N�X"));
	pImpl->Eng(PROP_MAP_REPLACE, _T("Prefix of replacement target variable name"));

	// 2326 (NC2)
	pImpl->Jpn(PROP_MAP_START, _T("���̒l���玩���̔Ԃ����"));
	pImpl->Eng(PROP_MAP_START, _T("Auto numbering from the next value"));

	// 2327 (NC3)
	pImpl->Jpn(PROP_MAP_USEONCE, _T("�e�ϐ��ւ̃}�b�s���O�͈�x�����g�p�����"));
	pImpl->Eng(PROP_MAP_USEONCE, _T("The mapping to each variable is used only once."));

	// 2331 (NC2)
	pImpl->Jpn(PROP_CHECK_TRUE, _T("TRUE�Ȃ�Ύ��̃X�e�b�v�Ɉڂ�"));
	pImpl->Eng(PROP_CHECK_TRUE, _T("If TRUE, progress to the next step."));

	// 2332 (NC2)
	pImpl->Jpn(PROP_CHECK_FALSE, _T("FALSE�Ȃ�Ύ��̃X�e�b�v�Ɉڂ�"));
	pImpl->Eng(PROP_CHECK_FALSE, _T("If FALSE, progress to the next step."));

	// 2333 (NC2)
	pImpl->Jpn(PROP_CHANGE_TRUE, _T("�t���O��TRUE�ɂ���"));
	pImpl->Eng(PROP_CHANGE_TRUE, _T("Change flag to TRUE."));

	// 2334 (NC2)
	pImpl->Jpn(PROP_CHANGE_FALSE, _T("�t���O��FALSE�ɂ���"));
	pImpl->Eng(PROP_CHANGE_FALSE, _T("Change flag to FALSE."));

	// 2341 (NC2)
	pImpl->Jpn(PROP_LOAD_VAR, _T("���̕ϐ�����f�[�^��Ǎ���"));
	pImpl->Eng(PROP_LOAD_VAR, _T("Load data from the following variable."));

	// 2342 (NC2)
	pImpl->Jpn(PROP_LOAD_CONT, _T("���̕ϐ�����A���I�Ƀf�[�^��Ǎ���"));
	pImpl->Eng(PROP_LOAD_CONT, _T("Load data from the following variables continuously."));

	// 2343 (NC2)
	pImpl->Jpn(PROP_STORE_VAR, _T("���̕ϐ��Ƀf�[�^����������"));
	pImpl->Eng(PROP_STORE_VAR, _T("Store data into the following variable."));

	// 2344 (NC2)
	pImpl->Jpn(PROP_STORE_CONT, _T("���̕ϐ��ɘA���I�Ƀf�[�^����������"));
	pImpl->Eng(PROP_STORE_CONT, _T("Store data into the following variables continuously."));

	// 2345 (---)
	pImpl->Jpn(PROP_DATA_COMM, _T("�R�~���j�P�[�V�����p�ϐ�"));
	pImpl->Eng(PROP_DATA_COMM, _T("Communication variable"));

	// 2346 (---)
	pImpl->Jpn(PROP_DATA_PREF, _T("�ϐ����̃v���t�B�b�N�X"));
	pImpl->Eng(PROP_DATA_PREF, _T("Prefix of variable name"));

	// 2347 (NC3)
	pImpl->Jpn(PROP_DATA_NUM, _T("���̒l����̎����̔�"));
	pImpl->Eng(PROP_DATA_NUM, _T("Auto numbering from the next value"));

	// 2351 (NC2)
	pImpl->Jpn(PROP_NET_RECV, _T("�w�肵��IP�A�h���X�ƃ|�[�g����f�[�^����M����"));
	pImpl->Eng(PROP_NET_RECV, _T("Receive data using the specified IP address and port."));

	// 2352 (NC5)
	pImpl->Jpn(PROP_NET_RECVTGT, _T("�w�肵�����M�v�f�̐ڑ��悩��f�[�^����M����"));
	pImpl->Eng(PROP_NET_RECVTGT, _T("Receive data from the connection target of the specified sender element."));

	// 2353 (NC2)
	pImpl->Jpn(PROP_NET_SEND, _T("�w�肵��IP�A�h���X�ƃ|�[�g�Ƀf�[�^�𑗐M����"));
	pImpl->Eng(PROP_NET_SEND, _T("Send data to the specified IP address and port."));

	// 2354 (NC5)
	pImpl->Jpn(PROP_NET_SENDTGT, _T("�w�肵����M�v�f�̐ڑ���Ƀf�[�^�𑗐M����"));
	pImpl->Eng(PROP_NET_SENDTGT, _T("Send data to the connection target of the specified receiver element."));

	// 2355 (NC2)
	pImpl->Jpn(PROP_NET_CLOSE_AFTERSEND, _T("�f�[�^���M��\�P�b�g���N���[�Y����"));
	pImpl->Eng(PROP_NET_CLOSE_AFTERSEND, _T("Close socket after sending data."));

	// 2356 (NC2)
	pImpl->Jpn(PROP_NET_CLOSE_AFTERRECV, _T("�f�[�^��M��\�P�b�g���N���[�Y����"));
	pImpl->Eng(PROP_NET_CLOSE_AFTERRECV, _T("Close socket after receiving data."));

	// 2357 (NC4)
	pImpl->Jpn(PROP_NET_TIMEOUT, _T("�ŏI�A�N�Z�X�ȍ~�Ƀ^�C���A�E�g�����m���� [1-180,000 �~���b]"));
	pImpl->Eng(PROP_NET_TIMEOUT, _T("Time-out detected after last access.  [1 - 180,000 mSec]"));

	// 2358 (---)
	pImpl->Jpn(PROP_NET_SENDER, _T("���M�v�f��"));
	pImpl->Eng(PROP_NET_SENDER, _T("Sender name"));

	// 2359 (---)
	pImpl->Jpn(PROP_NET_RECEIVER, _T("��M�v�f��"));
	pImpl->Eng(PROP_NET_RECEIVER, _T("Receiver name"));

	// 2360 (---)
	pImpl->Jpn(PROP_NET_ICON, _T("�A�C�R��"));
	pImpl->Eng(PROP_NET_ICON, _T("Icon"));

	// 2361 (---)
	pImpl->Jpn(PROP_NET_IPADDR, _T("IP�A�h���X/�z�X�g��"));
	pImpl->Eng(PROP_NET_IPADDR, _T("IP address/hostname"));

	// 2362 (---)
	pImpl->Jpn(PROP_NET_PORT, _T("�|�[�g�ԍ�"));
	pImpl->Eng(PROP_NET_PORT, _T("Port"));

	// 2363 (NC4)
	pImpl->Jpn(PROP_FILEACCESS_NAME, _T("�v���O�������A�N�Z�X����t�@�C�������w��\r\n�J�����g�t�H���_����̑��΃p�X���w�肷��K�v������B(��:\"..\\data\\test.bin\")\r\n�J�����g�t�H���_�͒ʏ�C�Ώۂ�\".std\"�t�@�C�����i�[����Ă���t�H���_�ƂȂ�B"));
	pImpl->Eng(PROP_FILEACCESS_NAME, _T("Specify the file name used by the program. \r\nThe relative path from the current folder should be given (ex: \"..\\data\\test.bin\"). \r\nThe current folder is normally set as the one containing the target \".std\" file."));

	// 2364 (NC4)
	pImpl->Jpn(PROP_FILEACCESSW_ADD, _T("�����̃t�@�C���̍Ō�Ƀf�[�^��A������"));
	pImpl->Eng(PROP_FILEACCESSW_ADD, _T("Add data to the end of the existing file."));

	// 2365 (NC4)
	pImpl->Jpn(PROP_FILEACCESSW_INSERT, _T("�����̃t�@�C���̐擪�ɂɃf�[�^��}������"));
	pImpl->Eng(PROP_FILEACCESSW_INSERT, _T("Insert data at the start of the existing file."));

	// 2366 (NC4)
	pImpl->Jpn(PROP_FILEACCESSW_OVERWRITE, _T("�����̃t�@�C�����㏑������"));
	pImpl->Eng(PROP_FILEACCESSW_OVERWRITE, _T("Overwrite the existing file."));

	// 2367 (NC4)
	pImpl->Jpn(PROP_FILEACCESSR_ADD, _T("���̓f�[�^�̏I���o�C�g�ɓǂݍ��񂾃f�[�^��A������"));
	pImpl->Eng(PROP_FILEACCESSR_ADD, _T("Add loaded data to the end byte of the input data."));

	// 2368 (NC4)
	pImpl->Jpn(PROP_FILEACCESSR_INSERT, _T("���̓f�[�^�̊J�n�o�C�g�ɓǂݍ��񂾃f�[�^��}������"));
	pImpl->Eng(PROP_FILEACCESSR_INSERT, _T("Insert loaded data at the start byte of the input data."));

	// 2369 (NC4)
	pImpl->Jpn(PROP_FILEACCESSR_OVERWRITE, _T("�t�@�C������ǂݍ��񂾃f�[�^���o�͂���"));
	pImpl->Eng(PROP_FILEACCESSR_OVERWRITE, _T("Output data read from the file."));

	// 2370 (NC4)
	pImpl->Jpn(PROP_EXECPROG_COMMAND, _T("�O���v���O�����ւ̃p�X���w��"));
	pImpl->Eng(PROP_EXECPROG_COMMAND, _T("Specify the path to the external program."));

	// 2371 (NC4)
	pImpl->Jpn(PROP_EXECPROG_WAIT, _T("���s�����v���O�������I������܂őҋ@����"));
	pImpl->Eng(PROP_EXECPROG_WAIT, _T("Wait until the program executed is finished."));

	// 2372 (NC4)
	pImpl->Jpn(PROP_EXECPROG_CURRDIR, _T("�O���v���O�������s���̃J�����g�t�H���_���w��\r\n�J�����g�t�H���_���w�肵�Ȃ��ꍇ�C�Ώۂ�\".std\"�t�@�C�����z�u���ꂽ�t�H���_���J�����g�t�H���_�ƂȂ�B"));
	pImpl->Eng(PROP_EXECPROG_CURRDIR, _T("Specify the current folder during external program execution. \r\nIf the current folder is not specified, the one containing the target \".std\" file will be set."));

	// 2373 (NC4)
	pImpl->Jpn(PROP_EXECPROG_STDOUT, _T("�O���v���O������STDOUT�֏������񂾃f�[�^�����̏����v�f�ɓn��"));
	pImpl->Eng(PROP_EXECPROG_STDOUT, _T("Pass data written by the external program to STDOUT to the next element."));

	// 2374 (NC4)
	pImpl->Jpn(PROP_EXECPROG_STDIN, _T("�{�����v�f�̓��̓f�[�^���O���v���O������STDIN�ɓn��"));
	pImpl->Eng(PROP_EXECPROG_STDIN, _T("Pass the input data of this processing element to STDIN."));

	// 2375 (NC4)
	pImpl->Jpn(PROP_NET_UNCOND, _T("�������Ŏ��̏����v�f�Ɉڂ�"));
	pImpl->Eng(PROP_NET_UNCOND, _T("Proceed unconditionally to the next processing element."));

	// 2376 (NC4)
	pImpl->Jpn(PROP_NET_EXCEEDSIZE, _T("��M�f�[�^�T�C�Y���w�肵���l�𒴂��� [1-9,999,999 �o�C�g]"));
	pImpl->Eng(PROP_NET_EXCEEDSIZE, _T("The size of the data received exceeds the preset value. [1-9,999,999 bytes]"));

	// 2377 (NC4)
	pImpl->Jpn(PROP_NET_RECVSTR, _T("�w�肵���f�[�^�Ŋ�������f�[�^����M����"));
	pImpl->Eng(PROP_NET_RECVSTR, _T("Data ending with the specified value received."));

	// 2378 (NC4)
	pImpl->Jpn(PROP_NET_TERMCOND, _T("�I������"));
	pImpl->Eng(PROP_NET_TERMCOND, _T("Termination condition"));

	// 2379 (NC4)
	pImpl->Jpn(PROP_NET_CLOSEDETECT, _T("���M���\�P�b�g���N���[�Y���ꂽ�Ƃ��������̏����v�f�Ɉڂ�"));
	pImpl->Eng(PROP_NET_CLOSEDETECT, _T("Proceed to the next processing element only when the sender socket is closed."));

	// 2380 (---)
	pImpl->Jpn(PROP_NET_CLOSEFORCE, _T("�����I�ɃN���[�Y����"));
	pImpl->Eng(PROP_NET_CLOSEFORCE, _T("Force close"));

	// 2381 (---)
	pImpl->Jpn(PROP_NET_CLOSEUDPPORT, _T("UDP�\�P�b�g���N���[�Y����"));
	pImpl->Eng(PROP_NET_CLOSEUDPPORT, _T("Close UDP socket"));

	// 2382 (---)
	pImpl->Jpn(PROP_NET_CLOSETCPPORT, _T("TCP�\�P�b�g���N���[�Y����"));
	pImpl->Eng(PROP_NET_CLOSETCPPORT, _T("Close TCP socket"));

	// 2383 (NC6)
	pImpl->Jpn(PROP_NET_PROCEEDEVENIFNODATARECV, _T("�f�[�^����M�ł����̏����v�f�ɑJ�ڂ���"));
	pImpl->Eng(PROP_NET_PROCEEDEVENIFNODATARECV, _T("Proceed even if no data are received."));

	// 2384 (��)
	pImpl->Jpn(PROP_NET_RECVMULTI, _T("�w�肵����M�v�f����f�[�^����M����"));
	pImpl->Eng(PROP_NET_RECVMULTI, _T("Receive data from the specified receiver."));

	// =====================================================================================================
	// 2400 (---)
	pImpl->Jpn(STKFW_LOG_TITLE, _T("StkFw - �X���b�h�R���g���[��\r\n"));
	pImpl->Eng(STKFW_LOG_TITLE, _T("StkFw - Thread controller\r\n"));

	// 2401 (NC3)
	pImpl->Jpn(STKFW_LOG_START, _T("�X���b�h�R���g���[���̓��O�̏o�͂��J�n���܂����B\r\n"));
	pImpl->Eng(STKFW_LOG_START, _T("The thread controller has started logging.\r\n"));

	// 2402 (NC3)
	pImpl->Jpn(STKFW_LOG_STOP, _T("�X���b�h�R���g���[���̓��O�̏o�͂��~���܂����B\r\n"));
	pImpl->Eng(STKFW_LOG_STOP, _T("The thread controller has stopped logging.\r\n"));

	// 2403 (NC3)
	pImpl->Jpn(STKFW_LOG_SUCCESSCSC, _T("�\�P�b�g�̐��������CONNECT�ɐ������܂����B"));
	pImpl->Eng(STKFW_LOG_SUCCESSCSC, _T("Creation of socket and connection succeeded."));

	// 2404 (NC3)
	pImpl->Jpn(STKFW_LOG_SUCCESSCSBNLS, _T("�\�P�b�g�̐����CBIND�����LISTEN�ɐ������܂����B"));
	pImpl->Eng(STKFW_LOG_SUCCESSCSBNLS, _T("Creation of socket, binding and listening succeeded."));

	// 2405 (NC3)
	pImpl->Jpn(STKFW_LOG_SOCKCLOSE, _T("�\�P�b�g�̃N���[�Y�ɐ������܂����B"));
	pImpl->Eng(STKFW_LOG_SOCKCLOSE, _T("Closure of socket succeeded."));

	// 2406 (NC3)
	pImpl->Jpn(STKFW_LOG_ACPTRECV, _T("ACCEPT�p�\�P�b�g�Ńf�[�^����M���܂����B"));
	pImpl->Eng(STKFW_LOG_ACPTRECV, _T("Data received using the accepting socket."));

	// 2407 (NC3)
	pImpl->Jpn(STKFW_LOG_CNCTRECV, _T("�ڑ����̃\�P�b�g�Ńf�[�^���ԐM����܂����B"));
	pImpl->Eng(STKFW_LOG_CNCTRECV, _T("Data returned using the communicating socket."));

	// 2408 (NC3)
	pImpl->Jpn(STKFW_LOG_ACPTSEND, _T("�ڑ����̃\�P�b�g�Ńf�[�^��ԐM���܂����B"));
	pImpl->Eng(STKFW_LOG_ACPTSEND, _T("Data sent back using the communicating socket."));

	// 2409 (NC3)
	pImpl->Jpn(STKFW_LOG_CNCTSEND, _T("CONNECT�����\�P�b�g�Ńf�[�^�𑗐M���܂����B"));
	pImpl->Eng(STKFW_LOG_CNCTSEND, _T("Data sent using the connected socket."));

	// 2410 (NC3)
	pImpl->Jpn(STKFW_LOG_SENDERROR, _T("�f�[�^���M���ɃG���[���������܂����B"));
	pImpl->Eng(STKFW_LOG_SENDERROR, _T("An error occurred during data transmission."));

	// 2411 (NC3)
	pImpl->Jpn(STKFW_LOG_RECVERROR, _T("�f�[�^��M���ɃG���[���������܂����B"));
	pImpl->Eng(STKFW_LOG_RECVERROR, _T("An error occurred during data receipt."));

	// 2412 (NC3)
	pImpl->Jpn(STKFW_LOG_NAMESOLVEERR, _T("�w�肳�ꂽ�z�X�g���̉����Ɏ��s���܂����B"));
	pImpl->Eng(STKFW_LOG_NAMESOLVEERR, _T("Resolution of the specified host name failed."));

	// 2413 (NC3)
	pImpl->Jpn(STKFW_LOG_CONNERROR, _T("�w�肳�ꂽ�z�X�g�ւ̐ڑ��Ɏ��s���܂����B"));
	pImpl->Eng(STKFW_LOG_CONNERROR, _T("Connection to the specified host failed."));

	// 2414 (NC3)
	pImpl->Jpn(STKFW_LOG_BINDLISTENERR, _T("BIND�܂���LISTEN�Ɏ��s���܂����B"));
	pImpl->Eng(STKFW_LOG_BINDLISTENERR, _T("Binding or listening failed."));

	// 2415 (NC3)
	pImpl->Jpn(STKFW_LOG_CREATEACCEPTSOCK, _T("ACCEPT�p�\�P�b�g�̐����ɐ������܂����B"));
	pImpl->Eng(STKFW_LOG_CREATEACCEPTSOCK, _T("Creation of accepting socket succeeded."));

	// 2416 (NC3)
	pImpl->Jpn(STKFW_LOG_CLOSEACCEPTSOCK, _T("ACCEPT�p�\�P�b�g�̃N���[�Y�ɐ������܂����B"));
	pImpl->Eng(STKFW_LOG_CLOSEACCEPTSOCK, _T("Closure of accepting socket succeeded."));

	// 2417 (NC5)
	pImpl->Jpn(STKFW_LOG_CLOSELISTENACCEPTSOCK, _T("ACCEPT�p�\�P�b�g�����LISTEN�p�\�P�b�g�̃N���[�Y�ɐ������܂����B"));
	pImpl->Eng(STKFW_LOG_CLOSELISTENACCEPTSOCK, _T("Closure of accept/listen sockets succeeded."));

	// 2418 (NC5)
	pImpl->Jpn(STKFW_LOG_BINDERR, _T("BIND�Ɏ��s���܂����B"));
	pImpl->Eng(STKFW_LOG_BINDERR, _T("Binding to port failed."));

	// 2419 (NC5)
	pImpl->Jpn(STKFW_LOG_SUCCESSCSBN, _T("UDP�\�P�b�g�̐��������BIND�ɐ������܂����B"));
	pImpl->Eng(STKFW_LOG_SUCCESSCSBN, _T("Creation of socket and binding succeeded."));

	// 2420 (NC5)
	pImpl->Jpn(STKFW_LOG_UDPRECV, _T("UDP�\�P�b�g�Ńf�[�^����M���܂����B"));
	pImpl->Eng(STKFW_LOG_UDPRECV, _T("Data received using UDP socket."));

	// 2421 (NC5)
	pImpl->Jpn(STKFW_LOG_UDPSEND, _T("UDP�\�P�b�g�Ńf�[�^�𑗐M���܂����B"));
	pImpl->Eng(STKFW_LOG_UDPSEND, _T("Data sent using UDP socket."));

	// 2422 (NC5)
	pImpl->Jpn(STKFW_LOG_SUCCESSCS, _T("UDP�\�P�b�g�̐����ɐ������܂����B"));
	pImpl->Eng(STKFW_LOG_SUCCESSCS, _T("Creation of UDP socket succeeded."));

	// 2423 (NC5)
	pImpl->Jpn(STKFW_LOG_UDPSOCKCLOSE, _T("UDP�\�P�b�g�̃N���[�Y�ɐ������܂����B"));
	pImpl->Eng(STKFW_LOG_UDPSOCKCLOSE, _T("Closure of UDP socket succeeded."));

	// =====================================================================================================
	//2901 (NC2)
	pImpl->Jpn(UNKNOWNERROR, _T("�s���ȃG���[���������܂����B"));
	pImpl->Eng(UNKNOWNERROR, _T("An unknown error has occurred."));

	//2902 (NC2)
	pImpl->Jpn(FILEACCESSERROR, _T("�t�@�C���A�N�Z�X�G���[���������܂����B"));
	pImpl->Eng(FILEACCESSERROR, _T("A file access error has occurred."));

	//2903 (NC1)
	pImpl->Jpn(NEEDADMINRIGHTS, _T("���̃v���O���������s���邽�߂ɂ�Local Administrator�̌������K�v�ł��B\r\n�v���O�����͏I�����܂��B\r\n\r\n"));
	pImpl->Eng(NEEDADMINRIGHTS, _T("You need local administrator's rights to run this program.\r\nThe program will be terminated.\r\n\r\n"));

	// 2904 (NC3)
	pImpl->Jpn(DATAUPDATED, _T("�v���O�������g�p����f�[�^�͍X�V����Ă��܂��B\r\n�f�[�^�������܂�������𑱂��ėǂ��ł����B"));
	pImpl->Eng(DATAUPDATED, _T("Program data updated.\r\nData will be lost. Continue operation?"));

	// 2905 (NC4)
	pImpl->Jpn(INVALIDVALUE, _T("�w�肵���l���s���ł��B�l�̎w��\�Ȕ͈͂��m�F���Ă��������B"));
	pImpl->Eng(INVALIDVALUE, _T("Invalid value specified. Check the range of values allowed."));

	//2906 (---)
	pImpl->Jpn(AN_ERROR_OCCURRED, _T("�G���[���������܂����B"));
	pImpl->Eng(AN_ERROR_OCCURRED, _T("An error occurred."));

	//2931 (---)
	pImpl->Jpn(COMMON_ADD, _T("�ǉ�"));
	pImpl->Eng(COMMON_ADD, _T("Add"));

	//2932 (---)
	pImpl->Jpn(COMMON_DELETE, _T("�폜"));
	pImpl->Eng(COMMON_DELETE, _T("Delete"));

	//2933 (---)
	pImpl->Jpn(COMMON_EDIT, _T("�ҏW"));
	pImpl->Eng(COMMON_EDIT, _T("Edit"));

	//2934 (---)
	pImpl->Jpn(COMMON_REFRESH, _T("�X�V"));
	pImpl->Eng(COMMON_REFRESH, _T("Refresh"));

	//2935 (---)
	pImpl->Jpn(COMMON_TRUE, _T("True"));
	pImpl->Eng(COMMON_TRUE, _T("True"));

	//2936 (---)
	pImpl->Jpn(COMMON_FALSE, _T("False"));
	pImpl->Eng(COMMON_FALSE, _T("False"));

	//2937 (---)
	pImpl->Jpn(COMMON_UNKNOWN, _T("�s��"));
	pImpl->Eng(COMMON_UNKNOWN, _T("Unknown"));

	//2941 (---)
	pImpl->Jpn(COMMON_OK, _T("OK"));
	pImpl->Eng(COMMON_OK, _T("OK"));

	//2942 (---)
	pImpl->Jpn(COMMON_CANCEL, _T("��ݾ�"));
	pImpl->Eng(COMMON_CANCEL, _T("Cancel"));

	// =====================================================================================================
	//3100 (---)
	pImpl->Jpn(CMDFRK_CMDFRKSRV, _T("CmdFreak service program\r\nCopyright (C) 2014 Shinya Takeuchi\r\nAll Rights Reserved.\r\n"));
	pImpl->Eng(CMDFRK_CMDFRKSRV, _T("CmdFreak service program\r\nCopyright (C) 2014 Shinya Takeuchi\r\nAll Rights Reserved.\r\n"));

	//3101 (NC6)
	pImpl->Jpn(CMDFRK_CANNOT_START, _T("\r\n���̃v���O������Windows�T�[�r�X�v���O�����̂��ߋN�����邱�Ƃ��ł��܂���B\r\n���̃v���O������CmdFreak�̃C���X�g�[������Windows�T�[�r�X�Ƃ��ăV�X�e���ɓo�^����܂��B\r\n\r\n"));
	pImpl->Eng(CMDFRK_CANNOT_START, _T("\r\nThis program cannot be started because it is configured as a Windows service program.\r\nThe program is registered as a Windows service in the system when CmdFreak is installed.\r\n\r\n"));

	//3121 (NC6)
	pImpl->Jpn(CMDFRK_ERROR_UNEXPECTED, _T("�\�����Ȃ��G���[���������܂����B���̃G���[��Web�u���E�U����̃��N�G�X�g����͂ł��Ȃ������Ƃ��ɔ�������ꍇ������܂��B<br>"));
	pImpl->Eng(CMDFRK_ERROR_UNEXPECTED, _T("An unexpected error occurred. This may be caused by inability to analyze request data from the web browser.<br>"));

	//3122 (NC6)
	pImpl->Jpn(CMDFRK_ERROR_SERVICEDOWN, _T("CmdFreak�T�[�r�X�Ƃ̒ʐM�����s���܂����B���̗v�����l�����܂��B<br>(1) CmdFreak�T�[�r�X���J�n����Ă��Ȃ��B<br>(2) CmdFreak�T�[�r�X���t�@�C�A�E�H�[���ɗ�O�o�^����Ă��Ȃ��B<br>(3) �ڑ���z�X�g������у|�[�g�ԍ��̒�`�t�@�C�� [bbb.conf, cmdfrksrv.conf] ���s���B<br>(4) CmdFreak�̓��������ňُ킪�������Ă���B<br>"));
	pImpl->Eng(CMDFRK_ERROR_SERVICEDOWN, _T("Connection with CmdFreak service failed. This may be caused by one of the following issues:<br>(1) CmdFreak service cannot be started.<br>(2) CmdFreak service is not registered as a firewall exception.<br>(3) The definition file [bbb.conf and/or cmdfrksrv.conf] for the host name and port number in the network connectivity settings is invalid.<br>(4) A CmdFreak internal process is invalid.<br>"));

	//3123 (NC6)
	pImpl->Jpn(CMDFRK_ERROR_JAVASCRIPTERR, _T("JavaScript�������ł��B<br>�u���E�U�̐ݒ��ύX����JavaScript��L����C�y�[�W�����t���b�V�����Ă��������B<br>\n"));
	pImpl->Eng(CMDFRK_ERROR_JAVASCRIPTERR, _T("JavaScript is disabled in your browser.<br>Change the browser setting to enable it and refresh the page.<br>\n"));

	//3124 (NC6)
	pImpl->Jpn(CMDFRK_ODBCINFO, _T("ODBC�ڑ��̐ݒ���s���܂��B<br>�ڑ��Ώۂ�DBMS��I�����CODBC�̐ڑ���������w�肵�Ă��������B<br>�{�\�t�g�E�F�A��32�r�b�g�A�v���P�[�V�����̂��߁CODBC�ڑ�������ɂ́C32�r�b�g��ODBC�h���C�o���g�p����悤�Ɏw����s���Ă��������B�I�y���[�e�B���O�V�X�e���ɂ́C���炩����32�r�b�g��ODBC�h���C�o���C���X�g�[������Ă���K�v������܂��B<br>"));
	pImpl->Eng(CMDFRK_ODBCINFO, _T("Configure ODBC connection.<br>Select the connection target DBMS and specify the ODBC connection string.<br>As this is 32-bit application software, this string should be specified for the use of a 32-bit ODBC driver. As a prerequisite, a 32-bit ODBC driver needs to be installed on the operating system.<br>"));

	//3125 (NC6)
	pImpl->Jpn(CMDFRK_ERROR_INVALIDDBCONN, _T("DBMS�Ƃ̐ڑ��Ɏ��s���܂����B<br>���̗v�����l�����܂��B<br>- DBMS���K�؂ɋN�����Ă��Ȃ��B<br>- ODBC�h���C�o���C���X�g�[������Ă��Ȃ��B<br>- ODBC�̐ڑ������񂪕s���B<br>- DBMS�Ƃ̐ڑ��o�H�ɉ��炩�̖�肪����B<br>"));
	pImpl->Eng(CMDFRK_ERROR_INVALIDDBCONN, _T("DBMS connection failed.<br>This may be caused by one of the following issues:<br>- The DBMS is not working properly.<br>- No ODBC driver is installed.<br>- The ODBC connection string is invalid.<br>- There are issues with the DBMS on the network.<br>"));

	//3126 (NC6)
	pImpl->Jpn(CMDFRK_LOG_DBMSCHANGE, _T("ODBC�ڑ��̐ݒ��ύX���܂����B"));
	pImpl->Eng(CMDFRK_LOG_DBMSCHANGE, _T("The ODBC connection configuration has been changed."));

	//3127 (NC6)
	pImpl->Jpn(CMDFRK_FILTER_DESC, _T("�����ł̓t�B���^�����O�̐ݒ���s�����Ƃ��ł��܂��B<br>�w�肵�������Ń��R�[�h��񂪃t�B���^�����O����܂��B<br>�t�B���^�����O���ڂ͍ő�5�����w�肷�邱�Ƃ��ł��܂��B<br>�e�t�B���^�����O���ڊԂ͘_����[AND]�Ō�������܂��B"));
	pImpl->Eng(CMDFRK_FILTER_DESC, _T("Filter settings can be specified here.<br>Records are filtered according to the specified criteria.<br>Up to five filter items can be specified.<br>All items are treated as logical AND operators."));

	//3128 (NC6)
	pImpl->Jpn(CMDFRK_FILTER_INVALID, _T("�ݒ肳��Ă���t�B���^�����O�����͌��݂̃e�[�u���̃X�L�[�}�ƈ�v���Ă��܂���B<br>�t�B���^�����O�������N���A���Ă悢�ł����H"));
	pImpl->Eng(CMDFRK_FILTER_INVALID, _T("The filter conditions set do not match the current table schema.<br>Do you want to clear the filter conditions?"));

	//3129 (NC6)
	pImpl->Jpn(CMDFRK_FILTERINGCOND_UPDATE, _T("�t�B���^�����O�������X�V���܂����B"));
	pImpl->Eng(CMDFRK_FILTERINGCOND_UPDATE, _T("The filter conditions have been updated."));

	//3130 (NC6)
	pImpl->Jpn(CMDFRK_FILTERING_NOTABLE, _T("�t�B���^�����O�̑ΏۂƂȂ�e�[�u�������݂��Ȃ����ߑ�����p���ł��܂���B"));
	pImpl->Eng(CMDFRK_FILTERING_NOTABLE, _T("The operation cannot be performed because the target table for filtering does not exist."));

	//3131 (NC6)
	pImpl->Jpn(CMDFRK_NOTABLEINFO, _T("�\���Ώۂ̃e�[�u�������݂��Ȃ����ߑ�����p���ł��܂���B"));
	pImpl->Eng(CMDFRK_NOTABLEINFO, _T("The operation cannot be performed because the target table for display does not exist."));

	//3132 (NC6)
	pImpl->Jpn(CMDFRK_EMPTYCONNSTR, _T("�{�\�t�g�E�F�A���g�p���ăf�[�^�x�[�X�̃f�[�^���Q�Ƃ���ɂ́C�܂��͂��߂�ODBC�ڑ��̐ݒ���s���Ă��������B"));
	pImpl->Eng(CMDFRK_EMPTYCONNSTR, _T("To refer to data in a database using this software, the ODBC connection needs to be configured first."));

	//3133 (NC6)
	pImpl->Jpn(CMDFRK_WELCOME, _T("�悤�����CCmdFreak�̃y�[�W�ł��I"));
	pImpl->Eng(CMDFRK_WELCOME, _T("Welcome to the CmdFreak page!"));

	//3134 (NC6)
	pImpl->Jpn(CMDFRK_ERROR_TOOMUCHRECS, _T("�Ώۃe�[�u���̃��R�[�h����CmdFreak�ő���\�ȏ���𒴂��܂����B"));
	pImpl->Eng(CMDFRK_ERROR_TOOMUCHRECS, _T("The number of records in the target table exceeds the limit that CmdFreak can handle."));

	//3135 (NC6)
	pImpl->Jpn(CMDFRK_ERROR_TOOLONGCONNSTR, _T("ODBC�̐ڑ�������Ŏw��\�Ȓ����̏���𒴂��܂����B"));
	pImpl->Eng(CMDFRK_ERROR_TOOLONGCONNSTR, _T("The length of the ODBC connection string exceeds the allowable limit."));

	//3136 (NC6)
	pImpl->Jpn(CMDFRK_ERROR_TOOLONGFILTER, _T("�t�B���^�����O�̏������w��\�ȏ���𒴂��܂����B"));
	pImpl->Eng(CMDFRK_ERROR_TOOLONGFILTER, _T("The length of the filtering condition string exceeds the allowable limit."));

	//3142 (NC6)
	pImpl->Jpn(CMDFRK_SVCFAILEDTOSTART, _T("CmdFreak�T�[�r�X�̊J�n�Ɏ��s���܂����B"));
	pImpl->Eng(CMDFRK_SVCFAILEDTOSTART, _T("CmdFreak service initiation failed."));

	//3143 (NC6)
	pImpl->Jpn(CMDFRK_SVCFAILEDTOSTOP, _T("CmdFreak�T�[�r�X�̒�~�Ɏ��s���܂����B"));
	pImpl->Eng(CMDFRK_SVCFAILEDTOSTOP, _T("CmdFreak service termination failed."));

	//3144 (NC6)
	pImpl->Jpn(CMDFRK_SVCALREADYSTART, _T("CmdFreak�T�[�r�X�͂��łɊJ�n���Ă��܂��B"));
	pImpl->Eng(CMDFRK_SVCALREADYSTART, _T("CmdFreak service has already been started."));

	//3145 (NC6)
	pImpl->Jpn(CMDFRK_SVCALREADYSTOP, _T("CmdFreak�T�[�r�X�͂��łɒ�~���Ă��܂��B"));
	pImpl->Eng(CMDFRK_SVCALREADYSTOP, _T("CmdFreak service has already been stopped."));

	//3146 (NC6)
	pImpl->Jpn(CMDFRK_SVCSTART, _T("CmdFreak�T�[�r�X���J�n���܂����B"));
	pImpl->Eng(CMDFRK_SVCSTART, _T("CmdFreak service has started."));

	//3147 (NC6)
	pImpl->Jpn(CMDFRK_SVCSTOP, _T("CmdFreak�T�[�r�X���~���܂����B"));
	pImpl->Eng(CMDFRK_SVCSTOP, _T("CmdFreak service has stopped."));

	//3148 (NC6)
	pImpl->Jpn(CMDFRK_LOG_DESC, _T("�ȉ��Ƀg���[�X���O���\������܂��B<br>�\������鎞����Web�T�[�o�[���z�u���ꂽ�n��̎����ƂȂ�܂��B"));
	pImpl->Eng(CMDFRK_LOG_DESC, _T("The trace log is displayed below.<br>Times are as per the time zone of the web server\\'s location."));

	//3149 (NC6)
	pImpl->Jpn(CMDFRK_TABLEINFO, _T("�ȉ��Ɏw�肳�ꂽ�e�[�u���̏ڍ׏���\�����܂��B"));
	pImpl->Eng(CMDFRK_TABLEINFO, _T("Detailed information on the specified table is shown below."));

	//3150 (---)
	pImpl->Jpn(CMDFRK_TARGETTABLE, _T("�Ώۃe�[�u��: "));
	pImpl->Eng(CMDFRK_TARGETTABLE, _T("The target table: "));

	//3154 (NC6)
	pImpl->Jpn(CMDFRK_COMPOINFO2, _T("���̃\�t�g�E�F�A�͎��̋Z�p����荞��ł��܂��B<br/>- Mongoose 3.7 (Released as MIT License)<br/>- JQuery 1.9.1 (Released as MIT License)<br/>- JQuery UI 1.10.3 (Released as MIT License)<br/>- ParamQuery Grid 1.1.2 (Released as MIT License)<br/>"));
	pImpl->Eng(CMDFRK_COMPOINFO2, _T("This software has the following technologies embedded:<br/>- Mongoose 3.7 (Released as MIT License)<br/>- JQuery 1.9.1 (Released as MIT License)<br/>- JQuery UI 1.10.3 (Released as MIT License)<br/>- ParamQuery Grid 1.1.2 (Released as MIT License)<br/>"));

	//3200 (---)
	pImpl->Jpn(CMDFRK_DBMS, _T("DBMS�̑I�� : "));
	pImpl->Eng(CMDFRK_DBMS, _T("Select DBMS : "));

	//3201 (---)
	pImpl->Jpn(CMDFRK_CONNSTR, _T("�ڑ�������̎w�� : "));
	pImpl->Eng(CMDFRK_CONNSTR, _T("Specify connection string : "));

	//3202 (---)
	pImpl->Jpn(CMDFRK_MANUAL, _T("manual/jpn/index.htm"));
	pImpl->Eng(CMDFRK_MANUAL, _T("manual/eng/index.htm"));

	//3203 (---)
	pImpl->Jpn(CMDFRK_MANUALMSG, _T("�I�����C���}�j���A�����J��"));
	pImpl->Eng(CMDFRK_MANUALMSG, _T("Open online manual"));

	//3210 (---)
	pImpl->Jpn(CMDFRK_COMPOINFO, _T("CmdFreak Version 1.0.0<br/>Copyright (C) 2014 Shinya Takeuchi<br/>All Rights Reserved."));
	pImpl->Eng(CMDFRK_COMPOINFO, _T("CmdFreak Version 1.0.0<br/>Copyright (C) 2014 Shinya Takeuchi<br/>All Rights Reserved."));

	//3226 (---)
	pImpl->Jpn(CMDFRK_LOGGINGTIME, _T("���O�o�͎���"));
	pImpl->Eng(CMDFRK_LOGGINGTIME, _T("Logging time"));

	//3227 (---)
	pImpl->Jpn(CMDFRK_LOGGINGMSG, _T("���b�Z�[�W"));
	pImpl->Eng(CMDFRK_LOGGINGMSG, _T("Message"));

	//3233 (---)
	pImpl->Jpn(CMDFRK_UNSPEC, _T("���w��"));
	pImpl->Eng(CMDFRK_UNSPEC, _T("Unspecified"));

	//3234 (---)
	pImpl->Jpn(CMDFRK_FILTERING, _T("�t�B���^�����O"));
	pImpl->Eng(CMDFRK_FILTERING, _T("Filtering"));

	//3235 (---)
	pImpl->Jpn(CMDFRK_ODBCCONNECTIONS, _T("ODBC�ڑ�"));
	pImpl->Eng(CMDFRK_ODBCCONNECTIONS, _T("ODBC Connections"));

	//3236 (---)
	pImpl->Jpn(CMDFRK_TABLES, _T("�e�[�u�����"));
	pImpl->Eng(CMDFRK_TABLES, _T("Table Information"));

	//3237 (---)
	pImpl->Jpn(CMDFRK_CREATERECORD, _T("���R�[�h����"));
	pImpl->Eng(CMDFRK_CREATERECORD, _T("Create Record"));

	//3238 (---)
	pImpl->Jpn(CMDFRK_EDITRECORD, _T("���R�[�h�ҏW"));
	pImpl->Eng(CMDFRK_EDITRECORD, _T("Edit Record"));

	//3239 (---)
	pImpl->Jpn(CMDFRK_DELETERECORD, _T("���R�[�h�폜"));
	pImpl->Eng(CMDFRK_DELETERECORD, _T("Delete Record"));

	//3240 (---)
	pImpl->Jpn(CMDFRK_INFORMATION, _T("���"));
	pImpl->Eng(CMDFRK_INFORMATION, _T("Information"));

	//3241 (---)
	pImpl->Jpn(CMDFRK_REFRESHTABLELIST, _T("�e�[�u���ꗗ�X�V"));
	pImpl->Eng(CMDFRK_REFRESHTABLELIST, _T("Refresh Table List"));

}

MessageProc::~MessageProc()
{
	delete pImpl;
}

void MessageProc::SetLocaleMode(int SpecifiedMode)
{
	if (Instance == NULL) {
		Instance = new MessageProc();
	}
	Instance->pImpl->Mode = SpecifiedMode;
}

TCHAR* MessageProc::GetMsg(int Id)
{
	if (Instance == NULL) {
		Instance = new MessageProc();
	}
	return Instance->pImpl->StkMsg[Id][Instance->pImpl->GetLocale()];
}

TCHAR* MessageProc::GetMsgEng(int Id)
{
	if (Instance == NULL) {
		Instance = new MessageProc();
	}
	return Instance->pImpl->StkMsg[Id][MessageProc::MLANG_ENGLISH];
}

TCHAR* MessageProc::GetMsgJpn(int Id)
{
	if (Instance == NULL) {
		Instance = new MessageProc();
	}
	return Instance->pImpl->StkMsg[Id][MessageProc::MLANG_JAPANESE];
}

BYTE* MessageProc::GetMsgSjis(int Id)
{
	if (Instance == NULL) {
		Instance = new MessageProc();
	}
	return Instance->pImpl->StkMsgSjis[Id][Instance->pImpl->GetLocale()];
}

BYTE* MessageProc::GetMsgSjisEng(int Id)
{
	if (Instance == NULL) {
		Instance = new MessageProc();
	}
	return Instance->pImpl->StkMsgSjis[Id][MessageProc::MLANG_ENGLISH];
}

BYTE* MessageProc::GetMsgSjisJpn(int Id)
{
	if (Instance == NULL) {
		Instance = new MessageProc();
	}
	return Instance->pImpl->StkMsgSjis[Id][MessageProc::MLANG_JAPANESE];
}

void MessageProc::StkErr(int Id, HWND WndHndl)
{
	if (Instance == NULL) {
		Instance = new MessageProc();
	}
	TCHAR Buf[32];
	wsprintf(Buf, _T("Message ID : %d"), Id);
	MessageBox(WndHndl, GetMsg(Id), Buf, MB_OK | MB_ICONSTOP);
}

void MessageProc::StkErr(int Id, TCHAR* Str, HWND WndHndl)
{
	if (Instance == NULL) {
		Instance = new MessageProc();
	}
	TCHAR Buf[32];
	wsprintf(Buf, _T("Message ID : %d"), Id);
	TCHAR MsgBuf[1024];
	wsprintf(MsgBuf, _T("%s\r\n[%s]"),  GetMsg(Id), Str);
	MessageBox(WndHndl, MsgBuf, Buf, MB_OK | MB_ICONSTOP);
}

void MessageProc::StkInf(int Id, HWND WndHndl)
{
	if (Instance == NULL) {
		Instance = new MessageProc();
	}
	TCHAR Buf[32];
	wsprintf(Buf, _T("Message ID : %d"), Id);
	MessageBox(WndHndl, GetMsg(Id), Buf, MB_OK | MB_ICONINFORMATION);
}

void MessageProc::StkInf(int Id, TCHAR* Str, HWND WndHndl)
{
	if (Instance == NULL) {
		Instance = new MessageProc();
	}
	TCHAR Buf[32];
	wsprintf(Buf, _T("Message ID : %d"), Id);
	TCHAR MsgBuf[1024];
	wsprintf(MsgBuf, _T("%s\r\n[%s]"),  GetMsg(Id), Str);
	MessageBox(WndHndl, MsgBuf, Buf, MB_OK | MB_ICONINFORMATION);
}

int MessageProc::StkYesNo(int Id, HWND WndHndl)
{
	if (Instance == NULL) {
		Instance = new MessageProc();
	}
	TCHAR Buf[32];
	wsprintf(Buf, _T("Message ID : %d"), Id);
	int Ret = MessageBox(WndHndl, GetMsg(Id), Buf, MB_YESNO | MB_ICONQUESTION);
	return Ret;
}

int MessageProc::StkYesNo(int Id, TCHAR* Str, HWND WndHndl)
{
	if (Instance == NULL) {
		Instance = new MessageProc();
	}
	TCHAR Buf[32];
	wsprintf(Buf, _T("Message ID : %d"), Id);
	TCHAR MsgBuf[1024];
	wsprintf(MsgBuf, _T("%s\r\n[%s]"),  GetMsg(Id), Str);
	int Ret = MessageBox(WndHndl, MsgBuf, Buf, MB_YESNO | MB_ICONQUESTION);
	return Ret;
}

void MessageProc::AddEng(int Id, TCHAR* Msg)
{
	if (Instance == NULL) {
		Instance = new MessageProc();
	}
	Instance->pImpl->Eng(Id, Msg);
}

void MessageProc::AddJpn(int Id, TCHAR* Msg)
{
	if (Instance == NULL) {
		Instance = new MessageProc();
	}
	Instance->pImpl->Jpn(Id, Msg);
}
