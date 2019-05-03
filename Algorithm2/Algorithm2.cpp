#include "pch.h"
#include <iostream>
#include "Singleton.h"

int main()
{
	Singleton* singleton = Singleton::GetInstance();

	return 0;
}