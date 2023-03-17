#include <iostream>
#include <fstream>
#include "HashTable.h"

using namespace std;

int main()
{
	char ch;
	ifstream deneme("tale");
	ofstream sonuc("yaz");
	HashTable<HashedObj> hashtable;

	HashedObj obj;
	obj.str = "";

	while (!deneme.eof()) //eof returns true if next character is eof (burda son karakter mi eof yoksa son karakterden sonraki adým mý)
	{
		deneme.get(ch); //get command reads next character unless you are at the end of the file
		obj.str += (ch + "");
		if (hashtable.find(obj.str).str == "notfound") //if the item with given string exists in the list or not
		{
			hashtable.insert(obj.str.substr(0, obj.str.length() - 1), obj);
			sonuc << hashtable.findIdx(obj.str.substr(0, obj.str.length() - 1)) << " ";
			obj.str = obj.str.substr(obj.str.length()-1, 1);
		}
	}
	//for the end-of-file condition
	hashtable.insert(obj.str.substr(0, obj.str.length() - 1), obj);
	sonuc << hashtable.findIdx(obj.str.substr(0, obj.str.length() - 1)) << " ";
	
	deneme.close();
	sonuc.close();
	return 0;
}
