#ifndef MAINTITLE_H
#define MAINTITLE_H
#include<string>
#include "videogame.h"

using std::string;

class MainTitle : public Videogame
{
private:
    double fixedprice;

public:
    MainTitle();
    MainTitle(const string& n, const string& a, const string& p, double f);
    virtual ~MainTitle();
    double GetFixedPrice() const;
    void SetFixedPrice(double f);
    virtual double price() const;
    virtual bool operator==(const Videogame& v) const;
    virtual bool operator!=(const Videogame& v) const;
};

#endif // MAINTITLE_H
