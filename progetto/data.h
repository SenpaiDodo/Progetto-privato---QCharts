#ifndef DATA_H
#define DATA_H
#include "videogame.h"
#include "maintitle.h"
#include "expansion.h"
#include <vector>

using std::vector;

class Data
{
private:
    vector<Videogame*> obj;

public:
    Data();
    ~Data();
    void Add(const Videogame& v);
    void Delete(int i);
    int Size() const;
    bool IsEmpty() const;
    void DeleteAll();
    Videogame* operator[](int i) const;
    bool operator==(const Data& o) const;
    bool operator!=(const Data& o) const;
    void Change(int i, const Videogame& v);
};

#endif // DATA_H
