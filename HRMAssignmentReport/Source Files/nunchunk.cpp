#include "nunchunk.h"

int Nunchunk::bonus(int k) {
    int res=0;
    do {
        k/=2;
        res+=k;
    } while (k!=0);
    return res*233;
}

int Nunchunk::nunchunk(stringstream& inputStream){
    inputStream>>n>>m;
    for(int i=0;i<n;++i) {
        inputStream>>a[i];
    }
    for(int i=0;i<n;++i) {
        inputStream>>b[i];
    }

    for(int i=0;i<m;++i) {
        dp[i]=-0x3f3f3f3f;
    } dp[0]=0;

    for(int i=0;i<n;++i) {
        for(int j=a[i];j<=m;++j) {
            int maxBonus=0;
            for(int k=1;k*a[i]<=j;++k) {
                maxBonus = max(maxBonus,dp[j-k*a[i]]+k*b[i]+bonus(k));
                dp[j]=max(dp[j],maxBonus);
            }
        }
    }

    return dp[m];
}
