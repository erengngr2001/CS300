#pragma once
#include <string>
#include <vector>

using namespace std;

int hashFunc(const string& str, int size)
{
    int hashVal = 0;

    for (int i = 0; i < str.length(); i++)
        hashVal += str[i];

    hashVal = hashVal % size;
    if (hashVal < 0)
        hashVal += size;

    return hashVal;
}

struct HashedObj
{
    string str = "";

    HashedObj() {};
    HashedObj(const string& s) :
        str(s)
    {}

    bool operator==(const HashedObj& rhs) const
    {
        return(str == rhs.str);
    }
    bool operator!=(const HashedObj& rhs) const
    {
        return !(*this == rhs);
    }
};

template <class HashedObj>
class HashTable
{
public:
    HashTable()
    {
        //makeEmpty();
        HashedObj notFound("notfound");
        ITEM_NOT_FOUND = notFound;

        //Determine vec size
        for (int i = 0; i < 4096; i++)
        {
            HashedObj temp;
            HashEntry entry(temp, EMPTY);
            vec.push_back(entry);
        }

        //Initialize hashtable with ASCII characters
        for (int i = 0; i < 256; i++)
        {
            unsigned char ch = i;
            HashedObj obj(ch + "");
            insert(obj.str, obj); 
        }
    }

    //Returns object with given string
    const HashedObj& find(const string& str) const
    {
        int currentPos = findPos(str);

        if (isActive(currentPos))
            return vec[currentPos].element;

        return ITEM_NOT_FOUND;
    }

    void makeEmpty()
    {
        //Make class logically "EMPTY"
        for (int i = 0; i < vec.size(); i++)
            vec[i].info = EMPTY;
    }

    //Return object with given code (not by index)
    HashedObj& getObject(int code)
    {
        int idx = 0;
        for (int i = 0; i < 4096; i++)
        {
            if (vec[i].num == code)
            {
                idx = i;
                break;
            }
        }
        return vec[idx].element;
    }

    //Check whether code item is in the list or not
    bool isInList(int code)
    {
        for (int i = 0; i < 4096; i++)
        {
            if (vec[i].num == code)
                return true;
        }
        return false;
    }

    void insert(const string& str, const HashedObj& obj)
    {
        // Insert str as active
        int currentPos = findPos(str);

        if (isActive(currentPos))
            return;

        HashEntry entry(obj, ACTIVE);
        entry.num = currentSize++;
        vec[currentPos] = entry;
    }

    void remove(const string& str)
    {
        int currentPos = findPos(str);

        if (isActive(currentPos))
            vec[currentPos].info = DELETED;
    }

    //Find location of the object in the list with given string
    int findIdx(const string& str) const
    {
        return vec[ hashFunc(str, vec.size()) ].num;
    }

    const HashTable& operator=(const HashTable& rhs)
    {
        HashTable newHT;

        for (int i = 0; i < rhs.vec.size(); i++)
            newHT.vec.push_back(rhs.vec[i]);

        newHT.currentSize = rhs.currentSize;

        return newHT;
    }

    enum EntryType { ACTIVE, EMPTY, DELETED }; //to check emptiness of given index in list

    struct HashEntry
    {
        HashedObj element;
        EntryType info;
        int num;

        HashEntry(const HashedObj& e = HashedObj(), EntryType i = EMPTY)
            : element(e), info(i)
        {
            num = 0;
        }
    };

private:

    vector<HashEntry> vec;
    int currentSize = 0;
    HashedObj ITEM_NOT_FOUND;

    bool isActive(int currentPos) const
    {
        return vec[currentPos].info == ACTIVE;
    }

    int findPos(const string& str) const
    {
        int p = hashFunc(str, vec.size()); // current position

        while (vec[p].info != EMPTY && vec[p].element != str) {
            p++;  // increment 

            if (p >= vec.size())             // perform the mod
                p = p - vec.size();                // if necessary
        }

        return p;
    }
};

