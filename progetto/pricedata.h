#ifndef PRICEDATA_H
#define PRICEDATA_H
#include "data.h"
#include<vector>

using std::vector;

class PriceData
{
private:
    vector<double> data;

public:
    PriceData(const Data& d);
    int Size() const;
    bool IsEmpty() const;
    double& operator[](int i) const;
    double max() const;
};

#endif // PRICEDATA_H
