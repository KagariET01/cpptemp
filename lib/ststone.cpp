#include<vector>
#include<functional>
namespace ET01{
	using INT=long long int;
	const INT lg=30;
	class ST{
		private:
			std::vector<INT>st[lg];
			INT n;
		public:
			std::function<INT(INT,INT)> op=[](INT a,INT b)->INT{
				if(a>b)return a;
				else return b;
			};

			void build(std::vector<INT>&a){
				n=a.size();
				st[0].resize(n);
				for(INT i=0;i<n;i++)st[0][i]=a[i];
				for(INT i=1;i<lg;i++){
					st[i].resize(n);
					for(INT j=0;j+(1<<(i-1))<n;j++){
						st[i][j]=op(
							st[i-1][j],
							st[i-1][j+(1<<(i-1))]
						);
					}
				}
			}
			INT query(INT l,INT r){
				INT k=std::__lg(r-l);
				return op(
					st[k][l],
					st[k][r-(1<<k)]
				);
			}
	};
};



#ifdef DBG
#include<bits/stdc++.h>
using namespace std;
using INT=long long int;
int main(){
	INT n,q;
	cin>>n>>q;
	vector<INT>a(n);
	for(INT i=0;i<n;i++)cin>>a[i];
	ET01::ST st1,st2;
	st1.op=[](INT a,INT b){
		return max(a,b);
	};
	st2.op=[](INT a,INT b){
		return min(a,b);
	};
	st1.build(a);
	st2.build(a);
	// INT q;
	// cin>>q;
	while(q--){
		INT l,r;
		cin>>l>>r;
		l--;
		cout<<st1.query(l,r)-st2.query(l,r)<<endl;
	}
	return 0;
}
#endif
