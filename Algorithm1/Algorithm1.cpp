#include "pch.h"
#include <iostream>
#include "CMyString.h"

int main()
{
	char text[] = "Test";
	char* str = text;
	CMyString str1(str);
	CMyString str2(str1);

	CMyString str3, str4;
	str3 = str4 = str1;

	str1.show();
	str2.show();
	str3.show();
	str4.show();

	return 0;
}