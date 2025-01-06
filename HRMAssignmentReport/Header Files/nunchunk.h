#ifndef NUNCHUNK_H
#define NUNCHUNK_H

#include <algorithm>
#include <istream>
#include <sstream>
using namespace std;

class Nunchunk{
public:
    int n,m;
    int a[1001];
    int b[1001];
    int dp[1001];

    int bonus(int k);
    int nunchunk(stringstream& inputStream);
};

#endif // NUNCHUNK_H
