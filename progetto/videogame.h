#ifndef VIDEOGAME_H
#define VIDEOGAME_H
#include<string>

using std::string;

class Videogame
{
private:
    string name;
    string author;
    string publication;

public:
    Videogame();
    Videogame(const string& n, const string& a, const string& p);
    virtual ~Videogame();
    string GetName() const;
    string GetAuthor() const;
    string GetPublication() const;
    void SetName(const string& n);
    void SetAuthor(const string& a);
    void SetPublication(const string& p);
    virtual double price() const=0;
    virtual bool operator==(const Videogame& v) const=0;
    virtual bool operator!=(const Videogame& v) const=0;
};

#endif // VIDEOGAME_H
