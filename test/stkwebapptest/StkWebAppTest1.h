#pragma once
#include "..\..\src\stkwebapp\StkWebAppExec.h"

class StkWebAppTest1 : StkWebAppExec
{
	StkObject* Execute(StkObject*, int, TCHAR[StkWebAppExec::URL_PATH_LENGTH], int*, TCHAR[3]);
};
