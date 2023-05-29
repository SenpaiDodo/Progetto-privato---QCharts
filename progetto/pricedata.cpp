#include "pricedata.h"
#include<vector>

PriceData::PriceData(const Data& d)
{
    for(int i=0; i<d.Size(); ++i)
    {
        double price_d=d[i]->price();
        data.push_back(price_d);
    }
}

int PriceData::Size() const
{
    return data.size();
}

bool PriceData::IsEmpty() const
{
    return data.size()==0;
}

double& PriceData::operator[](int i) const
{
    vector<double>::const_iterator it=data.begin()+i;
    return const_cast<double&>(*it);
}

double PriceData::max() const
{
    vector<double>::const_iterator it=data.begin();
    double max=*it;
    ++it;
    for(; it!=data.end(); ++it)
    {
        if((*it)>max)
            max=(*it);
    }
    return max;
}
