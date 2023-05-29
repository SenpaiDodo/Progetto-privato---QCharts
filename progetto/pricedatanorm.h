#ifndef PRICEDATANORM_H
#define PRICEDATANORM_H
#include <vector>
#include "pricedata.h"

using std::vector;

class PriceDataNorm
{
private:
    vector<double> norm;
    double max;

public:
    PriceDataNorm(const PriceData& price_d, double m=200);
    int Size() const;
    bool IsEmpty() const;
    double Max() const;
    double& operator[](int i) const;
};

#endif // PRICEDATANORM_H
