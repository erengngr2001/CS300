#include <iostream>
#include <fstream>
#include "HashTable.h"

using namespace std;

int main()
{
	int code;
	int prevCode;
	ifstream deneme("yaz");
	ofstream sonuc("tale");
	HashTable<HashedObj> hashtable;
	deneme >> code;
	sonuc << hashtable.getObject(code).str;
	prevCode = code;

	while (deneme >> code)
	{
		if (hashtable.isInList(code)) //if the code is already in the list
		{
			sonuc << hashtable.getObject(code).str;
			HashedObj tempObj;
			tempObj.str = hashtable.getObject(prevCode).str + hashtable.getObject(code).str[0];
			//hashtable.getObject(step++) = tempObj;
			hashtable.insert(tempObj.str, tempObj);
			prevCode = code;
		}
		else
		{
			HashedObj tempObj;
			tempObj.str = hashtable.getObject(prevCode).str + hashtable.getObject(prevCode).str[0];
			hashtable.insert(tempObj.str, tempObj);
			sonuc << hashtable.getObject(code).str;
		}
		prevCode = code;
	}

	deneme.close();
	sonuc.close();
	return 0;
}