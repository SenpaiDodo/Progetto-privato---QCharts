#include "pricedatanorm.h"
#include<vector>

PriceDataNorm::PriceDataNorm(const PriceData& price_d, double m) : max(m)
{
    double maxt=price_d.max();
    for(int i=0; i<price_d.Size(); ++i)
    {
        double value=max*price_d[i]/maxt;
        norm.push_back(value);
    }
}

int PriceDataNorm::Size() const
{
    return norm.size();
}

bool PriceDataNorm::IsEmpty() const
{
    return norm.size()==0;
}

double PriceDataNorm::Max() const
{
    return max;
}

double& PriceDataNorm::operator [](int i) const
{
    vector<double>::const_iterator it=norm.begin()+i;
    return const_cast<double&>(*it);
}
