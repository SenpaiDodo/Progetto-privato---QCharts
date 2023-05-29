#ifndef EXPANSION_H
#define EXPANSION_H
#include<string>
#include "videogame.h"

using std::string;

class Expansion : public Videogame
{
private:
    int numexpansion;
    double expansionprice;

public:
    Expansion();
    Expansion(const string& n, const string& a, const string& p, int num_e, double e);
    virtual ~Expansion();
    int GetNumExpansion() const;
    double GetExpansionPrice() const;
    void SetNumExpansion(int num_e);
    void SetExpansionPrice(double e);
    virtual double price() const;
    virtual bool operator==(const Videogame& v) const;
    virtual bool operator!=(const Videogame& v) const;
};

#endif // EXPANSION_H
