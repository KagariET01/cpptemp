#include<cmath>
namespace ET01{
	using INT=long long int;
	#define PII std::pair<INT,INT>
	#define PIPII std::pair<INT,PII>
	PIPII exgcd(INT a,INT b){
		if(b==0){
			return PIPII(a,PII(INT(1),INT(0)));
		}else{
			INT lst[3][3]={
				{a,1,0},
				{b,0,1},
				{0,0,0}
			};
			INT i=2;
			while(1){
				INT nw=lst[(i+1)%3][0]/lst[(i+2)%3][0];
				lst[i][0]=lst[(i+1)%3][0]-nw*lst[(i+2)%3][0];
				lst[i][1]=lst[(i+1)%3][1]-nw*lst[(i+2)%3][1];
				lst[i][2]=lst[(i+1)%3][2]-nw*lst[(i+2)%3][2];
				if(lst[i][0]==0){
					break;
				}
				i++;
				i%=3;
			}
			return PIPII(lst[(i+2)%3][0],PII(lst[(i+2)%3][1],lst[(i+2)%3][2]));
		}
	}
	INT mod_1(INT a,INT n){
		PIPII re=exgcd(a,n);
		if(re.first!=1)return -1;
		return (re.second.first%n+n)%n;
	}
};



#ifdef DBG
#include<bits/stdc++.h>
using namespace std;
using INT=long long int;
int main(){
	INT a,b;
	cin>>a>>b;
	auto re=ET01::exgcd(a,b);
	cout<<re.first<<' '<<re.second.first<<' '<<re.second.second<<endl;
	auto re2=ET01::mod_1(a,b);
	cout<<re2<<endl;
	return 0;
}
#endif