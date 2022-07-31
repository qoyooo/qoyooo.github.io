#include<bits/stdc++.h>
using namespace std;
int n;
int a[105];
double p;
double c[105];
double dp[11025];

int main(){
    int t;
    cin>>t;
    while(t--){
        for(int i=0; i<105; i++){
            dp[i]=0;
        }
        cin>>p>>n;
        int money;
        for(int i=1; i<=n; i++){
            cin>>a[i]>>c[i];
            money+=a[i];
        }
        dp[0]=1;
        for(int i=1; i<=n; i++){
            for(int j=money; j>=a[i]; j--){
                dp[j]=max(dp[j], double(dp[j-a[i]])*c[i]);
            }
        }
        int maxn=0;
        for(int i=money; i>=0; i++){
            if(dp[i]>=p){
                maxn=i;
                break;
            }
        }
        cout<<maxn<<endl;
    }
    return 0;
}