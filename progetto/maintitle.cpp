#include "maintitle.h"

MainTitle::MainTitle() : Videogame(), fixedprice(0.0)
{
}

MainTitle::MainTitle(const string& n, const string& a, const string& p, double f) : Videogame(n, a, p), fixedprice(f)
{
}

MainTitle::~MainTitle()
{
}

double MainTitle::GetFixedPrice() const
{
    return fixedprice;
}

void MainTitle::SetFixedPrice(double f)
{
    fixedprice=f;
}

double MainTitle::price() const
{
    return fixedprice;
}

bool MainTitle::operator==(const Videogame& v) const
{
    if(dynamic_cast<const MainTitle*>(&v))
    {
        const MainTitle& temp=dynamic_cast<const MainTitle&>(v);
        return GetName()==temp.GetName() && GetAuthor()==temp.GetAuthor() && GetPublication()==temp.GetPublication() && GetFixedPrice()==temp.GetFixedPrice();
    }
    return false;
}

bool MainTitle::operator!=(const Videogame& v) const
{
    if(dynamic_cast<const MainTitle*>(&v))
    {
        const MainTitle& temp=dynamic_cast<const MainTitle&>(v);
        return !(GetName()==temp.GetName() && GetAuthor()==temp.GetAuthor() && GetPublication()==temp.GetPublication() && GetFixedPrice()==temp.GetFixedPrice());
    }
    return true;
}
