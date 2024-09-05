
// input: 0-indexed (0<=i<n)
// query: 0-indexed (0<=i<n)
// query: [l,r) (l<r) (no include r)
// work: 1-indexed (1<=i<=n)

#include<vector>

namespace ET01{
	
	class BIT{
		using INT=long long int;
		private:
			std::vector<INT>BIT1;
			INT n;
			INT lowbit(INT x){
				return x&(-x);
			}
		// private
		public:
			BIT(INT n):n(n){
				BIT1.resize(n+1,0);
			}
			void modify(INT p,INT x){
				p++;
				for(;p<=n;p+=lowbit(p))BIT1[p]+=x;
			}
			INT query(INT p){
				p++;
				INT re=0;
				for(;p;p-=lowbit(p))re+=BIT1[p];
				return re;
			}
			void resize(INT n){
				BIT1.resize(n+1,0);
			}
		// public
	};

	class BITpp{
		using INT=long long int;
		private:
			ET01::BIT BIT1,BIT2;
			INT n;
		// private
		public:
			BITpp(INT n):n(n),BIT1(n),BIT2(n){}
			void modify(INT l,INT r,INT x){ // a[l~r]+=x (0-indexed) (l<r) (no include r)
				BIT1.modify(l,x);
				BIT1.modify(r,-x);
				BIT2.modify(l,x*(l));
				BIT2.modify(r,-x*(r));
			}
			void modify(INT p,INT x){
				modify(p,p+1,x);
			}
			INT query(INT p){
				return BIT1.query(p)*(p+1)-BIT2.query(p);
			}
			INT query(INT l,INT r){
				r--,l--;
				return query(r)-query(l);
			}
		// public
	};
};



#ifdef DBG
#include<bits/stdc++.h>
using namespace std;
using INT=long long int;
int main(){
	INT n;
	cin>>n;
	ET01::BITpp bit(n);
	for(INT i=0;i<n;i++){
		INT x;
		cin>>x;
		bit.modify(i,x);
	}
	INT q;
	cin>>q;
	while(q--){
		INT op;
		cin>>op;
		if(op==1){
			INT l,r,x;
			cin>>l>>r>>x;
			bit.modify(l,r,x);
		}
		else{
			INT l,r;
			cin>>l>>r;
			cout<<bit.query(l,r)<<endl;
		}
	}
	return 0;
}
#endif
