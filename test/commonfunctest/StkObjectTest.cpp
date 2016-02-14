#include <windows.h>
#include <string>
#include <tchar.h>
#include <stdio.h>
#include <Psapi.h>

#include "..\..\src\commonfunc\StkObject.h"
#include "..\..\src\commonfunc\StkObjectUtil.h"

int GetUsedMemorySizeOfCurrentProcess()
{
	DWORD dwProcessID = GetCurrentProcessId();
	HANDLE hProcess;
	PROCESS_MEMORY_COUNTERS pmc = { 0 };

	long Size;
	if ((hProcess = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, dwProcessID)) != NULL) {
		if (GetProcessMemoryInfo(hProcess, &pmc, sizeof(pmc))) {
			Size = pmc.WorkingSetSize;
		}
	}
	CloseHandle(hProcess);
	return Size;
}

StkObject* MakeTestData1()
{
	StkObject* Elem1 = new StkObject(_T("SoftwareCompany"));

	for (int Loop = 0; Loop < 20; Loop++) {
		StkObject* Elem6 = new StkObject(_T("Product"));
		Elem6->AppendAttribute(new StkObject(StkObject::STKOBJECT_ATTRIBUTE, _T("Name"), _T("qwer")));
		Elem6->AppendAttribute(new StkObject(StkObject::STKOBJECT_ATTRIBUTE, _T("Price"), 10000));
		Elem1->AppendChildElement(Elem6);
	}

	StkObject* Elem2 = new StkObject(_T("Product"));
	Elem2->AppendAttribute(new StkObject(StkObject::STKOBJECT_ATTRIBUTE, _T("Name"), _T("Xxxxx paint")));
	Elem2->AppendAttribute(new StkObject(StkObject::STKOBJECT_ATTRIBUTE, _T("Price"), _T("11000")));

	StkObject* Elem5 = new StkObject(_T("License"));
	Elem5->AppendAttribute(new StkObject(StkObject::STKOBJECT_ATTRIBUTE, _T("Cap"), 322.44f));
	Elem2->AppendChildElement(Elem5);

	StkObject* Elem3 = new StkObject(_T("Product"));
	Elem3->AppendAttribute(new StkObject(StkObject::STKOBJECT_ATTRIBUTE, _T("Name"), _T("Aaaaa 3D")));
	Elem3->AppendAttribute(new StkObject(StkObject::STKOBJECT_ATTRIBUTE, _T("Price"), _T("39000")));

	StkObject* Elem4 = new StkObject(StkObject::STKOBJECT_ELEMENT, _T("ELEM_INT"), 123);
	StkObject* Elem7 = new StkObject(StkObject::STKOBJECT_ELEMENT, _T("ELEM_FLOAT"), 456.7f);
	StkObject* Elem8 = new StkObject(StkObject::STKOBJECT_ELEMENT, _T("ELEM_STRING"), _T(" ABC FFF DDD EEE "));

	Elem1->AppendAttribute(new StkObject(StkObject::STKOBJECT_ATTRIBUTE, _T("CompanyName"), _T("TakeuchiSoft")));
	Elem1->AppendAttribute(new StkObject(StkObject::STKOBJECT_ATTRIBUTE, _T("Employee"), _T("110")));
	Elem1->AppendAttribute(new StkObject(StkObject::STKOBJECT_ATTRIBUTE, _T("Address"), _T("Shizuoka Pref. Yaizu city")));
	Elem1->AppendChildElement(Elem2);
	Elem1->AppendChildElement(Elem3);
	Elem1->AppendChildElement(Elem4);
	Elem1->AppendChildElement(Elem7);
	Elem1->AppendChildElement(Elem8);

	return Elem1;
}

StkObject* MakeTestData2()
{
	StkObject* Xml2 = new StkObject(_T("EncodeTesting"));
	Xml2->AppendAttribute(new StkObject(StkObject::STKOBJECT_ATTRIBUTE, _T("Lt"), _T("<")));
	Xml2->AppendAttribute(new StkObject(StkObject::STKOBJECT_ATTRIBUTE, _T("Gt"), _T(">")));
	Xml2->AppendAttribute(new StkObject(StkObject::STKOBJECT_ATTRIBUTE, _T("Amp"), _T("&")));
	Xml2->AppendAttribute(new StkObject(StkObject::STKOBJECT_ATTRIBUTE, _T("Quot"), _T("\"")));
	Xml2->AppendAttribute(new StkObject(StkObject::STKOBJECT_ATTRIBUTE, _T("Apos"), _T("\'")));
	Xml2->AppendChildElement(new StkObject(StkObject::STKOBJECT_ELEMENT, _T("Element"), _T("<")));
	Xml2->AppendChildElement(new StkObject(StkObject::STKOBJECT_ELEMENT, _T("Element"), _T(">")));
	Xml2->AppendChildElement(new StkObject(StkObject::STKOBJECT_ELEMENT, _T("Element"), _T("&")));
	Xml2->AppendChildElement(new StkObject(StkObject::STKOBJECT_ELEMENT, _T("Element"), _T("\"")));
	Xml2->AppendChildElement(new StkObject(StkObject::STKOBJECT_ELEMENT, _T("Element"), _T("\'")));
	return Xml2;
}

StkObject* MakeTestData3()
{
	StkObject* Xml2 = new StkObject(_T("EncodeTesting"));
	Xml2->AppendAttribute(new StkObject(StkObject::STKOBJECT_ATTRIBUTE, _T("Lt"), _T("<<<<<<<<<<")));
	Xml2->AppendAttribute(new StkObject(StkObject::STKOBJECT_ATTRIBUTE, _T("Gt"), _T(">>>>>>>>>>")));
	Xml2->AppendAttribute(new StkObject(StkObject::STKOBJECT_ATTRIBUTE, _T("Amp"), _T("&&&&&&&&&&")));
	Xml2->AppendAttribute(new StkObject(StkObject::STKOBJECT_ATTRIBUTE, _T("Quot"), _T("\"\"\"\"\"\"\"\"\"\"")));
	Xml2->AppendAttribute(new StkObject(StkObject::STKOBJECT_ATTRIBUTE, _T("Apos"), _T("\'\'\'\'\'\'\'\'\'\'")));
	Xml2->AppendChildElement(new StkObject(StkObject::STKOBJECT_ELEMENT, _T("Element"), _T("<<<<<<<<<<")));
	Xml2->AppendChildElement(new StkObject(StkObject::STKOBJECT_ELEMENT, _T("Element"), _T(">>>>>>>>>>")));
	Xml2->AppendChildElement(new StkObject(StkObject::STKOBJECT_ELEMENT, _T("Element"), _T("&&&&&&&&&&")));
	Xml2->AppendChildElement(new StkObject(StkObject::STKOBJECT_ELEMENT, _T("Element"), _T("\"\"\"\"\"\"\"\"\"\"")));
	Xml2->AppendChildElement(new StkObject(StkObject::STKOBJECT_ELEMENT, _T("Element"), _T("\'\'\'\'\'\'\'\'\'\'")));
	return Xml2;
}

TCHAR* MakeTestData4()
{
	TCHAR* RtnXml = new TCHAR[512];
	lstrcpy(RtnXml, _T("<Aaaa Lt=\"&lt;\" Gt=\"&gt;\" Amp=\"&amp;\" Quot=\"&quot;\" Apos=\"&apos;\"><Bbbb>&lt;</Bbbb><Bbbb>&gt;</Bbbb><Bbbb>&amp;</Bbbb><Bbbb>&quot;</Bbbb><Bbbb>&apos;</Bbbb></Aaaa>"));
	return RtnXml;
}

TCHAR* MakeTestData5()
{
	TCHAR* RtnXml = new TCHAR[512];
	lstrcpy(RtnXml, _T("<Aaaa Lt=\"&lt;&lt;&lt;&lt;&lt;&lt;&lt;&lt;&lt;&lt;\" Apos=\"&apos;&apos;&apos;&apos;&apos;&apos;&apos;&apos;&apos;&apos;\"><Bbbb>&amp;&amp;&amp;&amp;&amp;&amp;&amp;&amp;&amp;&amp;</Bbbb><Bbbb>&quot;&quot;&quot;&quot;&quot;&quot;&quot;&quot;&quot;&quot;</Bbbb></Aaaa>"));
	return RtnXml;
}

StkObject* MakeTestData6()
{
	StkObject* TopElem = new StkObject(_T("House"));
	TopElem->AppendAttribute(new StkObject(StkObject::STKOBJECT_ATTRIBUTE, _T("Material"), _T("Wood")));
	TopElem->AppendAttribute(new StkObject(StkObject::STKOBJECT_ATTRIBUTE, _T("Size"), 200));
	TopElem->AppendAttribute(new StkObject(StkObject::STKOBJECT_ATTRIBUTE, _T("Address"), _T("�_�ސ쌧����s���q 1000-2000")));

	StkObject* ChildElem1 = new StkObject(_T("KitchenRoom"));
	ChildElem1->AppendAttribute(new StkObject(StkObject::STKOBJECT_ATTRIBUTE, _T("Speca"), 20));
	ChildElem1->AppendAttribute(new StkObject(StkObject::STKOBJECT_ATTRIBUTE, _T("WallColor"), _T("Brown")));
	ChildElem1->AppendChildElement(new StkObject(StkObject::STKOBJECT_ELEMENT, _T("Furniture"), _T("Kitchen Table")));
	ChildElem1->AppendChildElement(new StkObject(StkObject::STKOBJECT_ELEMENT, _T("Furniture"), _T("Gas Cooker")));
	ChildElem1->AppendChildElement(new StkObject(StkObject::STKOBJECT_ELEMENT, _T("Furniture"), _T("Kitchen Rack")));

	StkObject* ChildElem2 = new StkObject(_T("KidsRoom"));

	StkObject* ChildElem2a = new StkObject(_T("Kid"));
	ChildElem2a->AppendAttribute(new StkObject(StkObject::STKOBJECT_ATTRIBUTE, _T("Speca"), 30));
	ChildElem2a->AppendAttribute(new StkObject(StkObject::STKOBJECT_ATTRIBUTE, _T("WallColor"), _T("Red")));
	ChildElem2a->AppendChildElement(new StkObject(StkObject::STKOBJECT_ELEMENT, _T("Furniture"), _T("Desk")));
	ChildElem2a->AppendChildElement(new StkObject(StkObject::STKOBJECT_ELEMENT, _T("Furniture"), _T("Chair")));
	ChildElem2a->AppendChildElement(new StkObject(StkObject::STKOBJECT_ELEMENT, _T("Furniture"), _T("Bed")));
	ChildElem2->AppendChildElement(ChildElem2a);

	StkObject* ChildElem2b = new StkObject(_T("Kid"));
	ChildElem2b->AppendAttribute(new StkObject(StkObject::STKOBJECT_ATTRIBUTE, _T("Speca"), 35));
	ChildElem2b->AppendAttribute(new StkObject(StkObject::STKOBJECT_ATTRIBUTE, _T("WallColor"), _T("White")));
	ChildElem2b->AppendChildElement(new StkObject(StkObject::STKOBJECT_ELEMENT, _T("Furniture"), _T("Desk")));
	ChildElem2b->AppendChildElement(new StkObject(StkObject::STKOBJECT_ELEMENT, _T("Furniture"), _T("Chair")));
	ChildElem2b->AppendChildElement(new StkObject(StkObject::STKOBJECT_ELEMENT, _T("Furniture"), _T("Bed")));
	ChildElem2->AppendChildElement(ChildElem2b);

	TopElem->AppendChildElement(ChildElem1);
	TopElem->AppendChildElement(ChildElem2);

	return TopElem;
}

void GeneralTestCase1(StkObject* Elem1, TCHAR* Name)
{
	int Len1 = Elem1->GetFirstChildElement()->GetArrayLength();
	wprintf(_T("%s#Len of top level element's child = %d..."), Name, Len1);
	if (Len1 == 25) {
		printf("OK\r\n");
	} else {
		printf("NG\r\n");
		exit(0);
	}
	StkObject* Elem3 = Elem1->GetFirstChildElement();
	for (int Loop = 0; Loop < 21; Loop++) {
		Elem3 = Elem3->GetNext();
	}
	int Len1_1 = Elem3->GetArrayLength();
	wprintf(_T("%s#Len of top level element's 2nd child = %d..."), Name, Len1_1);
	if (Len1_1 == 4) {
		printf("OK\r\n");
	} else {
		printf("NG\r\n");
		exit(0);
	}
	int Len2 = Elem1->GetArrayLength();
	wprintf(_T("%s#Len of top level element = %d..."), Name, Len2);
	if (Len2 == 1) {
		printf("OK\r\n");
	} else {
		printf("NG\r\n");
		exit(0);
	}
	int ElemCount = Elem1->GetChildElementCount();
	wprintf(_T("%s#ElemCount = %d..."), Name, ElemCount);
	if (ElemCount == Len1) {
		printf("OK\r\n");
	} else {
		printf("NG\r\n");
		exit(0);
	}
	int AttrCount = Elem1->GetAttributeCount();
	wprintf(_T("%s#AttrCount = %d..."), Name, AttrCount);
	if (AttrCount == 3) {
		printf("OK\r\n");
	} else {
		printf("NG\r\n");
		exit(0);
	}
	StkObject* Elem4 = Elem3->GetNext();
	int Elem4ElemCnt = Elem4->GetChildElementCount();
	int Elem4AttrCnt = Elem4->GetAttributeCount();
	wprintf(_T("%s#SingleElement Count..."), Name, AttrCount);
	if (Elem4ElemCnt == 0 && Elem4AttrCnt == 0) {
		printf("OK\r\n");
	} else {
		printf("NG\r\n");
		exit(0);
	}
}

void GeneralTestCase2(StkObject* Elem, TCHAR* Name)
{
	StkObject* Attr1 = Elem->GetFirstAttribute();
	std::wstring Attr1Val;
	Attr1->ToXml(&Attr1Val);
	wprintf(_T("%s#Attribute value '<', '>', '&', '\"' and '\'' are escaped ... "), Name);
	if (Attr1Val.find(_T("Lt=\"&lt;\"")) == std::wstring::npos ||
		Attr1Val.find(_T("Gt=\"&gt;\"")) == std::wstring::npos ||
		Attr1Val.find(_T("Amp=\"&amp;\"")) == std::wstring::npos ||
		Attr1Val.find(_T("Quot=\"&quot;\"")) == std::wstring::npos ||
		Attr1Val.find(_T("Apos=\"&apos;\"")) == std::wstring::npos) {
		printf("NG\r\n");
		exit(0);
	} else {
		printf("OK\r\n");
	}

	StkObject* Elem1 = Elem->GetFirstChildElement();
	std::wstring Elem1Val;
	Elem1->ToXml(&Elem1Val);
	wprintf(_T("%s#Element value '<', '>', '&', '\"' and '\'' are escaped ... "), Name);
	if (Elem1Val.find(_T(">&lt;<")) == std::wstring::npos ||
		Elem1Val.find(_T(">&gt;<")) == std::wstring::npos ||
		Elem1Val.find(_T(">&amp;<")) == std::wstring::npos ||
		Elem1Val.find(_T(">&quot;<")) == std::wstring::npos ||
		Elem1Val.find(_T(">&apos;<")) == std::wstring::npos) {
		printf("NG\r\n");
		exit(0);
	} else {
		printf("OK\r\n");
	}
}

void GeneralTestCase3(StkObject* Elem, TCHAR* Name)
{
	StkObject* Attr1 = Elem->GetFirstAttribute();
	std::wstring Attr1Val;
	Attr1->ToXml(&Attr1Val);
	wprintf(_T("%s#Attribute value '<', '>', '&', '\"' and '\'' are escaped ... "), Name);
	if (Attr1Val.find(_T("Lt=\"&lt;&lt;&lt;&lt;&lt;&lt;&lt;&lt;&lt;&lt;\"")) == std::wstring::npos ||
		Attr1Val.find(_T("Gt=\"&gt;&gt;&gt;&gt;&gt;&gt;&gt;&gt;&gt;&gt;\"")) == std::wstring::npos ||
		Attr1Val.find(_T("Amp=\"&amp;&amp;&amp;&amp;&amp;&amp;&amp;&amp;&amp;&amp;\"")) == std::wstring::npos ||
		Attr1Val.find(_T("Quot=\"&quot;&quot;&quot;&quot;&quot;&quot;&quot;&quot;&quot;&quot;\"")) == std::wstring::npos ||
		Attr1Val.find(_T("Apos=\"&apos;&apos;&apos;&apos;&apos;&apos;&apos;&apos;&apos;&apos;\"")) == std::wstring::npos) {
		printf("NG\r\n");
		exit(0);
	} else {
		printf("OK\r\n");
	}

	StkObject* Elem1 = Elem->GetFirstChildElement();
	std::wstring Elem1Val;
	Elem1->ToXml(&Elem1Val);
	wprintf(_T("%s#Element value '<', '>', '&', '\"' and '\'' are escaped ... "), Name);
	if (Elem1Val.find(_T(">&lt;&lt;&lt;&lt;&lt;&lt;&lt;&lt;&lt;&lt;<")) == std::wstring::npos ||
		Elem1Val.find(_T(">&gt;&gt;&gt;&gt;&gt;&gt;&gt;&gt;&gt;&gt;<")) == std::wstring::npos ||
		Elem1Val.find(_T(">&amp;&amp;&amp;&amp;&amp;&amp;&amp;&amp;&amp;&amp;<")) == std::wstring::npos ||
		Elem1Val.find(_T(">&quot;&quot;&quot;&quot;&quot;&quot;&quot;&quot;&quot;&quot;<")) == std::wstring::npos ||
		Elem1Val.find(_T(">&apos;&apos;&apos;&apos;&apos;&apos;&apos;&apos;&apos;&apos;<")) == std::wstring::npos) {
		printf("NG\r\n");
		exit(0);
	} else {
		printf("OK\r\n");
	}
}

void GeneralTestCase4(TCHAR* Xml, TCHAR* Name)
{
	StkObjectUtil Sou;
	int Offset = 0;
	StkObject* Elem = Sou.CreateObjectFromXml(Xml, &Offset);
	StkObject* Attr1 = Elem->GetFirstAttribute();
	StkObject* Attr2 = Attr1->GetNext();
	StkObject* Attr3 = Attr2->GetNext();
	StkObject* Attr4 = Attr3->GetNext();
	StkObject* Attr5 = Attr4->GetNext();
	StkObject* Elem1 = Elem->GetFirstChildElement();
	StkObject* Elem2 = Elem1->GetNext();
	StkObject* Elem3 = Elem2->GetNext();
	StkObject* Elem4 = Elem3->GetNext();
	StkObject* Elem5 = Elem4->GetNext();

	wprintf(_T("%s#Attribute value '&lt;', '&gt;', '&amp;', '&quot;' and '&apos;' are decoded appropriately... "), Name);
	if (lstrcmp(Attr1->GetStringValue(), _T("<")) != 0 ||
		lstrcmp(Attr2->GetStringValue(), _T(">")) != 0 ||
		lstrcmp(Attr3->GetStringValue(), _T("&")) != 0 ||
		lstrcmp(Attr4->GetStringValue(), _T("\"")) != 0 ||
		lstrcmp(Attr5->GetStringValue(), _T("\'")) != 0) {
		printf("NG\r\n");
		exit(0);
	} else {
		printf("OK\r\n");
	}

	wprintf(_T("%s#Element value '&lt;', '&gt;', '&amp;', '&quot;' and '&apos;' are decoded appropriately... "), Name);
	if (lstrcmp(Elem1->GetStringValue(), _T("<")) != 0 ||
		lstrcmp(Elem2->GetStringValue(), _T(">")) != 0 ||
		lstrcmp(Elem3->GetStringValue(), _T("&")) != 0 ||
		lstrcmp(Elem4->GetStringValue(), _T("\"")) != 0 ||
		lstrcmp(Elem5->GetStringValue(), _T("\'")) != 0) {
		printf("NG\r\n");
		exit(0);
	} else {
		printf("OK\r\n");
	}

	delete Elem;
}

void GeneralTestCase5(TCHAR* Xml, TCHAR* Name)
{
	StkObjectUtil Sou;
	int Offset = 0;
	StkObject* Elem = Sou.CreateObjectFromXml(Xml, &Offset);
	StkObject* Attr1 = Elem->GetFirstAttribute();
	StkObject* Attr2 = Attr1->GetNext();
	StkObject* Elem1 = Elem->GetFirstChildElement();
	StkObject* Elem2 = Elem1->GetNext();

	wprintf(_T("%s#Attribute value '&lt;...&lt;' and '&apos;...&apos;' are decoded appropriately... "), Name);
	if (lstrcmp(Attr1->GetStringValue(), _T("<<<<<<<<<<")) != 0 ||
		lstrcmp(Attr2->GetStringValue(), _T("\'\'\'\'\'\'\'\'\'\'")) != 0) {
		printf("NG\r\n");
		exit(0);
	} else {
		printf("OK\r\n");
	}

	wprintf(_T("%s#Element value '&amp;...&amp;' and '&quot;...&quot;' are decoded appropriately... "), Name);
	if (lstrcmp(Elem1->GetStringValue(), _T("&&&&&&&&&&")) != 0 ||
		lstrcmp(Elem2->GetStringValue(), _T("\"\"\"\"\"\"\"\"\"\"")) != 0) {
		printf("NG\r\n");
		exit(0);
	} else {
		printf("OK\r\n");
	}

	delete Elem;
}

void GeneralTestCase6()
{
	int Offset = 0;
	StkObjectUtil Sou;

	TCHAR* Xml1 = _T("<?xml version=\"1.0\"?><!-- comment --><Aaaa A1=\"a1\" A2=\"a2\" A3=\"a3\"><Bbbb B1=\"b1\" B2=\"b2\" B3=\"b3\"/><Cccc C1=\"c1\" C2=\"c2\" C3=\"c3\"/></Aaaa>");
	TCHAR* Xml2 = _T("<?xml version=\"1.0\"?><!-- comment --><Aaaa A1=\"a1\" A2=\"a2\" A3=\"a3\"><Bbbb B1=\"b1\" B2=\"b2\" B3=\"b3\"></Bbbb><Cccc C1=\"c1\" C2=\"c2\" C3=\"c3\"></Cccc></Aaaa>");
	TCHAR* Xml3 = _T("  <  Aaaa  A1  =  \"a1\"  A2  =  \"a2\"  A3  =  \"a3\"  >  <  Bbbb  B1  =  \"b1\"  B2  =  \"b2\"  B3  =  \"b3\"  /  >  <  Cccc  C1  =  \"c1\"  C2  =  \"c2\"  C3  =  \"c3\"  /  >  <  /  Aaaa  >  ");
	TCHAR* Xml4 = _T("\t<\tAaaa\tA1\t=\t\"a1\"\tA2\t=\t\"a2\"\tA3\t=\t\"a3\"\t>\t<\tBbbb\tB1\t=\t\"b1\"\tB2\t=\t\"b2\"\tB3\t=\t\"b3\"\t/\t>\t<\tCccc\tC1\t=\t\"c1\"\tC2\t=\t\"c2\"\tC3\t=\t\"c3\"\t/\t>\t<\t/\tAaaa\t>\t");
	TCHAR* Xml5 = _T("\r\n<\r\nAaaa\r\nA1\r\n=\r\n\"a1\"\r\nA2\r\n=\r\n\"a2\"\r\nA3\r\n=\r\n\"a3\"\r\n>\r\n<\r\nBbbb\r\nB1\r\n=\r\n\"b1\"\r\nB2\r\n=\r\n\"b2\"\r\nB3\r\n=\r\n\"b3\"\r\n/\r\n>\r\n<\r\nCccc\r\nC1\r\n=\r\n\"c1\"\r\nC2\r\n=\r\n\"c2\"\r\nC3\r\n=\r\n\"c3\"\r\n/\r\n>\r\n<\r\n/\r\nAaaa\r\n>\r\n");

	StkObject* RetObj1 = Sou.CreateObjectFromXml(Xml1, &Offset);
	StkObject* RetObj2 = Sou.CreateObjectFromXml(Xml2, &Offset);
	StkObject* RetObj3 = Sou.CreateObjectFromXml(Xml3, &Offset);
	StkObject* RetObj4 = Sou.CreateObjectFromXml(Xml4, &Offset);
	StkObject* RetObj5 = Sou.CreateObjectFromXml(Xml5, &Offset);

	std::wstring Msg1;
	std::wstring Msg2;
	std::wstring Msg3;
	std::wstring Msg4;
	std::wstring Msg5;

	RetObj1->ToXml(&Msg1);
	RetObj2->ToXml(&Msg2);
	RetObj3->ToXml(&Msg3);
	RetObj4->ToXml(&Msg4);
	RetObj5->ToXml(&Msg5);

	printf("Decoding variation test (sampling check)...");
	if (lstrcmp(RetObj1->GetFirstChildElement()->GetNext()->GetFirstAttribute()->GetStringValue(), _T("c1")) != 0 ||
		lstrcmp(RetObj2->GetFirstChildElement()->GetNext()->GetFirstAttribute()->GetStringValue(), _T("c1")) != 0 ||
		lstrcmp(RetObj3->GetFirstChildElement()->GetNext()->GetFirstAttribute()->GetStringValue(), _T("c1")) != 0 ||
		lstrcmp(RetObj4->GetFirstChildElement()->GetNext()->GetFirstAttribute()->GetStringValue(), _T("c1")) != 0 ||
		lstrcmp(RetObj5->GetFirstChildElement()->GetNext()->GetFirstAttribute()->GetStringValue(), _T("c1")) != 0) {
		printf("NG\r\n");
		exit(0);
	} else {
		printf("OK\r\n");
	}

	printf("Decoding variation test (ToXml check)...");
	if (Msg1.compare(Msg2.c_str()) != 0 || Msg1.compare(Msg3.c_str()) != 0 || Msg1.compare(Msg4.c_str()) != 0 || Msg1.compare(Msg5.c_str()) != 0) {
		printf("NG\r\n");
		exit(0);
	} else {
		printf("OK\r\n");
	}

	delete RetObj1;
	delete RetObj2;
	delete RetObj3;
	delete RetObj4;
	delete RetObj5;
}

void GeneralTestCase7()
{
	int Offset = 0;
	StkObjectUtil Sou;
	StkObject* RetObj;

	{
		printf("Abnormal case: \"\" is presented...");
		RetObj = Sou.CreateObjectFromXml(_T(""), &Offset);
		if (RetObj != NULL || Offset != StkObjectUtil::ERROR_XML_NO_ELEMENT_FOUND) {
			printf("NG\r\n");
			exit(0);
		} else {
			printf("OK\r\n");
		}
	}

	{
		printf("Abnormal case: NULL is presented...");
		RetObj = Sou.CreateObjectFromXml(NULL, &Offset);
		if (RetObj != NULL || Offset != StkObjectUtil::ERROR_XML_NO_ELEMENT_FOUND) {
			printf("NG\r\n");
			exit(0);
		} else {
			printf("OK\r\n");
		}
	}

	{
		printf("Abnormal case: \"<>\" is presented...");
		RetObj = Sou.CreateObjectFromXml(_T("<>"), &Offset);
		if (RetObj != NULL || Offset != StkObjectUtil::ERROR_XML_INVALID_ELEMENT_END_FOUND) {
			printf("NG\r\n");
			exit(0);
		} else {
			printf("OK\r\n");
		}
	}

	{
		printf("Abnormal case: \"<<\" is presented...");
		RetObj = Sou.CreateObjectFromXml(_T("<<"), &Offset);
		if (RetObj != NULL || Offset != StkObjectUtil::ERROR_XML_INVALID_ELEMENT_START_FOUND) {
			printf("NG\r\n");
			exit(0);
		} else {
			printf("OK\r\n");
		}
	}

	{
		printf("Abnormal case: \"<\"ABC\"/>\" is presented...");
		RetObj = Sou.CreateObjectFromXml(_T("<\"ABC\"/>"), &Offset);
		if (RetObj != NULL || Offset != StkObjectUtil::ERROR_XML_INVALID_QUOT_FOUND) {
			printf("NG\r\n");
			exit(0);
		} else {
			printf("OK\r\n");
		}
	}

	{
		printf("Abnormal case: \"xyz\" is presented...");
		RetObj = Sou.CreateObjectFromXml(_T("xyz"), &Offset);
		if (RetObj != NULL || Offset != StkObjectUtil::ERROR_XML_CANNOT_HANDLE) {
			printf("NG\r\n");
			exit(0);
		} else {
			printf("OK\r\n");
		}
	}

	{
		printf("Abnormal case: \"<Aaa Bbb=Ccc/>\" is presented...");
		RetObj = Sou.CreateObjectFromXml(_T("<Aaa Bbb=Ccc/>"), &Offset);
		if (RetObj != NULL || Offset != StkObjectUtil::ERROR_XML_CANNOT_HANDLE) {
			printf("NG\r\n");
			exit(0);
		} else {
			printf("OK\r\n");
		}
	}

	{
		printf("Abnormal case: \"<Aaa Bbb=></Aaa>\" is presented...");
		RetObj = Sou.CreateObjectFromXml(_T("<Aaa Bbb=></Aaa>"), &Offset);
		if (RetObj != NULL || Offset != StkObjectUtil::ERROR_XML_INVALID_ELEMENT_END_FOUND) {
			printf("NG\r\n");
			exit(0);
		} else {
			printf("OK\r\n");
		}
	}

	{
		printf("Abnormal case: \"<Aaa =></Aaa>\" is presented...");
		RetObj = Sou.CreateObjectFromXml(_T("<Aaa =></Aaa>"), &Offset);
		if (RetObj != NULL || Offset != StkObjectUtil::ERROR_XML_EQUAL_FOUND_WITHOUT_ATTRIBUTE_NAME) {
			printf("NG\r\n");
			exit(0);
		} else {
			printf("OK\r\n");
		}
	}

	{
		printf("Abnormal case: \"<Aaa></Aaa\" is presented...");
		RetObj = Sou.CreateObjectFromXml(_T("<Aaa></Aaa"), &Offset);
		if (RetObj != NULL || Offset != StkObjectUtil::ERROR_XML_SLASH_FOUND_WITHOUT_ELEMENT_END) {
			printf("NG\r\n");
			exit(0);
		} else {
			printf("OK\r\n");
		}
	}

	{
		printf("Abnormal case: \"<Aaa>/Aaa\" is presented...");
		RetObj = Sou.CreateObjectFromXml(_T("<Aaa>/Aaa"), &Offset);
		if (RetObj != NULL || Offset != StkObjectUtil::ERROR_XML_ELEMENT_END_NOT_FOUND) {
			printf("NG\r\n");
			exit(0);
		} else {
			printf("OK\r\n");
		}
	}

	{
		printf("Abnormal case: \"</Aaa>\" is presented...");
		RetObj = Sou.CreateObjectFromXml(_T("</Aaa>"), &Offset);
		if (RetObj != NULL || Offset != StkObjectUtil::ERROR_XML_SLASH_FOUND_WITHOUT_ELEMENT) {
			printf("NG\r\n");
			exit(0);
		} else {
			printf("OK\r\n");
		}
	}

	{
		printf("Abnormal case: \"<Aaaa\" is presented...");
		RetObj = Sou.CreateObjectFromXml(_T("<Aaaa"), &Offset);
		if (RetObj != NULL || Offset != StkObjectUtil::ERROR_XML_ELEMENT_END_NOT_FOUND) {
			printf("NG\r\n");
			exit(0);
		} else {
			printf("OK\r\n");
		}
	}

	{
		printf("Abnormal case: \"<Aaaa Xxx=\"Xxx\" is presented...");
		RetObj = Sou.CreateObjectFromXml(_T("<Aaaa Xxx=\"Xxx"), &Offset);
		if (RetObj != NULL || Offset != StkObjectUtil::ERROR_XML_ELEMENT_END_NOT_FOUND) {
			printf("NG\r\n");
			exit(0);
		} else {
			printf("OK\r\n");
		}
	}

	{
		printf("Abnormal case: \"<?xml?></?xml?>\" is presented...");
		RetObj = Sou.CreateObjectFromXml(_T("<?xml?></?xml?>"), &Offset);
		if (RetObj != NULL || Offset != StkObjectUtil::ERROR_XML_SLASH_FOUND_WITHOUT_ELEMENT) {
			printf("NG\r\n");
			exit(0);
		} else {
			printf("OK\r\n");
		}
	}
}

void GeneralTestCase8()
{
	printf("<Aaaa>=</Aaaa> ; <Aaaa>/</Aaaa> ; <Aaaa>?</Aaaa> ; <Aaaa>!</Aaaa> ; ---> Element value can be acquired...");
	int Offset = 0;
	StkObjectUtil Sou;

	TCHAR* Xml1 = _T("<Aaaa>=</Aaaa>");
	TCHAR* Xml2 = _T("<Aaaa>/</Aaaa>");
	TCHAR* Xml3 = _T("<Aaaa>?</Aaaa>");
	TCHAR* Xml4 = _T("<Aaaa>!</Aaaa>");

	StkObject* RetObj1 = Sou.CreateObjectFromXml(Xml1, &Offset);
	StkObject* RetObj2 = Sou.CreateObjectFromXml(Xml2, &Offset);
	StkObject* RetObj3 = Sou.CreateObjectFromXml(Xml3, &Offset);
	StkObject* RetObj4 = Sou.CreateObjectFromXml(Xml4, &Offset);

	if (lstrcmp(RetObj1->GetStringValue(), _T("=")) != 0) {
		printf("NG\r\n");
		exit(0);
	}
	if (lstrcmp(RetObj2->GetStringValue(), _T("/")) != 0) {
		printf("NG\r\n");
		exit(0);
	}
	if (lstrcmp(RetObj3->GetStringValue(), _T("?")) != 0) {
		printf("NG\r\n");
		exit(0);
	}
	if (lstrcmp(RetObj4->GetStringValue(), _T("!")) != 0) {
		printf("NG\r\n");
		exit(0);
	}

	delete RetObj1;
	delete RetObj2;
	delete RetObj3;
	delete RetObj4;
	printf("OK\r\n");
}

void GeneralTestCase9(StkObject* TopElem)
{
	std::wstring XmlTxt;
	std::wstring JsonTxt;
	TopElem->ToXml(&XmlTxt);
	TopElem->ToJson(&JsonTxt);
}

void CloneTest(StkObject* Obj)
{
	std::wstring OrgMsg;
	Obj->ToXml(&OrgMsg);

	StkObject* NewObj1 = Obj->Clone();
	StkObject* NewObj2 = NewObj1->Clone();

	std::wstring Msg1;
	std::wstring Msg2;
	NewObj1->ToXml(&Msg1);
	NewObj2->ToXml(&Msg2);

	printf("Clone Test#Validation of two clone's string...");
	if (lstrcmp(Msg1.c_str(), Msg2.c_str()) == 0 && lstrcmp(Msg1.c_str(), OrgMsg.c_str()) == 0) {
		printf("OK\r\n");
	} else {
		printf("NG\r\n");
		exit(0);
	}

	delete NewObj1;
	delete NewObj2;
}

int MemoryLeakChecking1(StkObject* PassedObj)
{
	printf("Checks memory leak (repeat cloning)...");
	long MaxMem[30];
	for (int CreationLoop = 0; CreationLoop < 30; CreationLoop++) {
		for (int Loop = 0; Loop < 1000; Loop++) {
			StkObject* NewObj = PassedObj->Clone();
			delete NewObj;
		}
		MaxMem[CreationLoop] = GetUsedMemorySizeOfCurrentProcess();
	}
	if (MaxMem[0] < MaxMem[3] &&
		MaxMem[3] < MaxMem[6] &&
		MaxMem[6] < MaxMem[9] &&
		MaxMem[9] < MaxMem[12] &&
		MaxMem[12] < MaxMem[15] &&
		MaxMem[15] < MaxMem[18] &&
		MaxMem[18] < MaxMem[21] &&
		MaxMem[21] < MaxMem[24] &&
		MaxMem[24] < MaxMem[27]) {
		printf("NG\r\n");
		return -1;
	}
	printf("OK\r\n");
	return 0;
}

int MemoryLeakChecking2()
{
	printf("Checks memory leak (repeat encoding and decoding)...");
	long MaxMem[30];

	for (int CreationLoop = 0; CreationLoop < 30; CreationLoop++) {
		for (int Loop = 0; Loop < 250; Loop++) {
			StkObject* NewObj = MakeTestData3();
			std::wstring StrVal;
			NewObj->ToXml(&StrVal);
			delete NewObj;

			TCHAR* NewStr = MakeTestData5();
			StkObjectUtil Sou;
			int Offset = 0;
			StkObject* NewObj2 = Sou.CreateObjectFromXml(NewStr, &Offset);
			delete NewStr;
			delete NewObj2;
		}
		MaxMem[CreationLoop] = GetUsedMemorySizeOfCurrentProcess();
	}
	if (MaxMem[0] < MaxMem[3] &&
		MaxMem[3] < MaxMem[6] &&
		MaxMem[6] < MaxMem[9] &&
		MaxMem[9] < MaxMem[12] &&
		MaxMem[12] < MaxMem[15] &&
		MaxMem[15] < MaxMem[18] &&
		MaxMem[18] < MaxMem[21] &&
		MaxMem[21] < MaxMem[24] &&
		MaxMem[24] < MaxMem[27]) {
		printf("NG\r\n");
		return -1;
	}
	printf("OK\r\n");
	return 0;
}

int MemoryLeakChecking3()
{
	printf("Checks memory leak (repeat abnormal case)...");
	long MaxMem[30];
	StkObjectUtil Sou;
	int Offset = 0;

	for (int CreationLoop = 0; CreationLoop < 30; CreationLoop++) {
		for (int Loop = 0; Loop < 1000; Loop++) {
			Sou.CreateObjectFromXml(_T(""), &Offset);
			Sou.CreateObjectFromXml(NULL, &Offset);
			Sou.CreateObjectFromXml(_T("<X><Y><Z><></X></Y></Z>"), &Offset);
			Sou.CreateObjectFromXml(_T("<X><Y><Z><<</X></Y></Z>"), &Offset);
			Sou.CreateObjectFromXml(_T("<X><Y><Z><\"ABC\"/></X></Y></Z>"), &Offset);
			Sou.CreateObjectFromXml(_T("xyz"), &Offset);
			Sou.CreateObjectFromXml(_T("<X><Y><Z><Aaa Bbb=Ccc/></X></Y></Z>"), &Offset);
			Sou.CreateObjectFromXml(_T("<X><Y><Z><Aaa Bbb=></Aaa></X></Y></Z>"), &Offset);
			Sou.CreateObjectFromXml(_T("<X><Y><Z><Aaa =></Aaa></X></Y></Z>"), &Offset);
			Sou.CreateObjectFromXml(_T("<Aaa></Aaa"), &Offset);
			Sou.CreateObjectFromXml(_T("<Aaa>/Aaa"), &Offset);
			Sou.CreateObjectFromXml(_T("</Aaa>"), &Offset);
			Sou.CreateObjectFromXml(_T("<X><Y><Z><Aaaa"), &Offset);
			Sou.CreateObjectFromXml(_T("<X><Y><Z><Aaaa Xxx=\"Xxx"), &Offset);
		}
		MaxMem[CreationLoop] = GetUsedMemorySizeOfCurrentProcess();
	}
	if (MaxMem[0] < MaxMem[3] &&
		MaxMem[3] < MaxMem[6] &&
		MaxMem[6] < MaxMem[9] &&
		MaxMem[9] < MaxMem[12] &&
		MaxMem[12] < MaxMem[15] &&
		MaxMem[15] < MaxMem[18] &&
		MaxMem[18] < MaxMem[21] &&
		MaxMem[21] < MaxMem[24] &&
		MaxMem[24] < MaxMem[27]) {
		printf("NG\r\n");
		return -1;
	}
	printf("OK\r\n");
	return 0;
}

void StkObjectTest()
{
	printf("StkObjectTest started.\r\n");

	// Encode check
	{
		StkObject* Elem2 = MakeTestData2();
		GeneralTestCase2(Elem2, _T("EncodeCheck1"));
		delete Elem2;

		StkObject* Elem3 = MakeTestData3();
		GeneralTestCase3(Elem3, _T("EncodeCheck2"));
		delete Elem3;

		StkObject* Elem6 = MakeTestData6();
		GeneralTestCase9(Elem6);
		delete Elem6;
	}

	// Decode check
	{
		TCHAR* Xml4 = MakeTestData4();
		GeneralTestCase4(Xml4, _T("DecodeCheck1"));
		delete Xml4;

		TCHAR* Xml5 = MakeTestData5();
		GeneralTestCase5(Xml5, _T("DecodeCheck2"));
		delete Xml5;

		GeneralTestCase6();
		GeneralTestCase8();
	}

	// General check
	{
		StkObject* Elem1 = MakeTestData1();
		GeneralTestCase1(Elem1, _T("Sample1"));
		delete Elem1;
	}

	// Clone check
	{
		StkObject* Elem1 = MakeTestData1();
		CloneTest(Elem1);
		delete Elem1;

		StkObject* Elem2 = MakeTestData2();
		CloneTest(Elem2);
		delete Elem2;

		StkObject* Elem3 = MakeTestData3();
		CloneTest(Elem3);
		delete Elem3;
	}

	// Decoding error case
	{
		GeneralTestCase7();
	}

	// Memory leak check
	{
		MemoryLeakChecking3();
		StkObject* Elem1 = MakeTestData1();
		MemoryLeakChecking1(Elem1);
		delete Elem1;
		MemoryLeakChecking2();
	}

	printf("StkObjectTest completed.\r\n\r\n\r\n");

}
