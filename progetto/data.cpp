#include "data.h"
#include<vector>

Data::Data()
{
}

Data::~Data()
{
    for(vector<Videogame*>::iterator it=obj.begin(); it!=obj.end(); ++it)
         delete *it;
}

void Data::Add(const Videogame & v)
{
    Videogame* vg=const_cast<Videogame*>(&v);
    obj.push_back(vg);
}

void Data::Delete(int i)
{
    vector<Videogame*>::iterator it=obj.begin()+i;
    if(*it)
        delete *it;
    obj.erase(it);
}

int Data::Size() const
{
    return obj.size();
}

bool Data::IsEmpty() const
{
    return obj.size()==0;
}

void Data::DeleteAll()
{
    for(vector<Videogame*>::const_iterator it=obj.begin(); it!=obj.end(); ++it)
        delete *it;
    obj.clear();
}

Videogame* Data::operator[](int i) const
{
    vector<Videogame*>::const_iterator it=obj.begin()+i;
    return *it;
}

bool Data::operator==(const Data& o) const
{
    bool ok = true;
    if(Size()!=o.Size())
        ok=false;
    for(int i=0; i<Size() && ok; ++i)
    {
        if((*obj[i])!=(*o.obj[i]))
            ok=false;
    }
    return ok;
}

bool Data::operator!=(const Data& o) const
{
    bool ok=true;
    if(Size() != o.Size())
        ok=false;
    for(int i=0; i<Size() && ok; ++i)
        if((*obj[i])!=(*o.obj[i]))
            ok=false;
    return !ok;
}

void Data::Change(int i, const Videogame& v)
{
    Videogame* vg=const_cast<Videogame*>(&v);
    delete obj[i];
    obj[i]=vg;
}
