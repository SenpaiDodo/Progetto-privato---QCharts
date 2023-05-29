#include "expansion.h"

Expansion::Expansion() : Videogame(), numexpansion(0), expansionprice(0.0)
{
}

Expansion::Expansion(const string& n, const string& a, const string& p, int num_e, double e) : Videogame(n, a, p), numexpansion(num_e), expansionprice(e)
{
}

Expansion::~Expansion()
{
}

int Expansion::GetNumExpansion() const
{
    return numexpansion;
}

double Expansion::GetExpansionPrice() const
{
    return expansionprice;
}

void Expansion::SetNumExpansion(int num_e)
{
    numexpansion=num_e;
}

void Expansion::SetExpansionPrice(double e)
{
    expansionprice=e;
}

double Expansion::price() const
{
    return numexpansion*expansionprice;
}

bool Expansion::operator==(const Videogame& v) const
{
    if(dynamic_cast<const Expansion*>(&v))
    {
        const Expansion& temp=dynamic_cast<const Expansion&>(v);
        return GetName()==temp.GetName() && GetAuthor()==temp.GetAuthor() && GetPublication()==temp.GetPublication() && GetNumExpansion()==temp.GetNumExpansion() && GetExpansionPrice()==temp.GetExpansionPrice();
    }
    return false;
}

bool Expansion::operator!=(const Videogame& v) const
{
    if(dynamic_cast<const Expansion*>(&v))
    {
        const Expansion& temp=dynamic_cast<const Expansion&>(v);
        return !(GetName()==temp.GetName() && GetAuthor()==temp.GetAuthor() && GetPublication()==temp.GetPublication() && GetNumExpansion()==temp.GetNumExpansion() && GetExpansionPrice()==temp.GetExpansionPrice());
    }
    return true;
}
