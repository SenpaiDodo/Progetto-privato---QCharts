#include "videogame.h"

Videogame::Videogame() : name(""), author(""), publication("")
{
}

Videogame::Videogame(const std::string& n, const std::string& a, const std::string& p) : name(n), author(a), publication(p)
{
}

Videogame::~Videogame()
{
}

std::string Videogame::GetName() const
{
    return name;
}

std::string Videogame::GetAuthor() const
{
    return author;
}

std::string Videogame::GetPublication() const
{
    return publication;
}

void Videogame::SetName(const std::string& n)
{
    name=n;
}
void Videogame::SetAuthor(const std::string& a)
{
    author=a;
}

void Videogame::SetPublication(const std::string& p)
{
    publication=p;
}
