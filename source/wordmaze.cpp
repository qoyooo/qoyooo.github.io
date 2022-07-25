#include<bits/stdc++.h>
using namespace std;
string a;
const int maxn=100;
char c[maxn][maxn] = {0};
int n,m;
int d[maxn][maxn]= {0};
int dx[4]={1,-1,0,0};
int dy[4]={0,0,1,-1};
bool flag=false;
bool maze(int x,int y,int b){
    if(b==a.length()+1){
        flag=true;
        return true;
    }
    for(int i=0;i<4;i++){
        int px=x+dx[i],py=y+dy[i];
        if(px<0||px>=n) continue;
        if(py<0||py>=m) continue;
        if(d[px][py]!=0) continue;
        if(c[px][py]==a[b]){
            d[px][py]=1;
            bool value=maze(px,py,b+1);
            if(value) return value;
            d[px][py]=0;
        }
    }
    return false;
}
int main(){
    cin>>n>>m;
    cin>>a;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cin>>c[i][j];
            d[i][j]=0;
        }
        printf("%s\n", c[i]);
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if((!flag)&&(c[i][j]==a[0])){
                d[i][j]=1;
                maze(i,j,1);
                d[i][j]=0;
            }
        }
    }
    if(flag==true) cout<<"YES";
    else cout<<"NO";
    return 0;
}
 
