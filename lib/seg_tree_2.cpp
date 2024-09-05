#include<iostream>
#include<functional>
namespace ET01{
	using INT=long long int;
	class SEG{
		private:
			INT n;
			struct node{
				INT v=0;
				INT land=0;
				node *_l=nullptr;
				node *_r=nullptr;
				node*&l(){
					if(!_l)_l=new node;
					return _l;
				}
				node*&r(){
					if(!_r)_r=new node;
					return _r;
				}
				bool have_l(){
					return _l;
				}
				bool have_r(){
					return _r;
				}
			};
			node *root=nullptr;
		public:
			INT zero=0;
			std::function<INT(INT,INT)> merge2node=[](INT a,INT b){  // 兩子節點合併成父節點
				return a+b;
			};
			std::function<INT(INT,INT,INT)> land2node=[](INT orig,INT v,INT sz){  // 將懶標加入到節點
				return orig+v*sz;
			};
			std::function<INT(INT,INT)> add2node=[](INT orig,INT v){  // 將要增加的值(modify操作)加入到節點，此操作只會在最底層的節點執行
				return orig+v;
			};
			std::function<INT(INT,INT)> add2land=[](INT orig,INT v){  // 將要增加的值(loop_modify操作)加入到懶標
				return orig+v;
			};
			void update(node*nw,INT sz){
				if(nw->have_l()&&nw->have_r()){
					nw->v=merge2node(nw->l()->v,nw->r()->v);
					nw->v=land2node(nw->v,nw->land,sz);
				}else if(nw->have_l()){
					nw->v=nw->l()->v;
					nw->v=land2node(nw->v,nw->land,sz);
				}else if(nw->have_r()){
					nw->v=nw->r()->v;
					nw->v=land2node(nw->v,nw->land,sz);
				}
			}

			void free(node*nw){
				if(nw->have_l())free(nw->l());
				if(nw->have_r())free(nw->r());
				delete nw;
			}

			void build(
				std::vector<INT>::iterator l,
				std::vector<INT>::iterator r,
				node *nw=nullptr
			){
				if(!nw){
					free(root);
					root=new node;
					nw=root;
					n=r-l;
				}
				if(r-l==1){
					nw->v=*l;
					return;
				}else{
					auto mid=(r-l)/2+l;
					build(l,mid,nw->l());
					build(mid,r,nw->r());
					update(nw,r-l);
				}
			}

			void modify(INT x,INT v,node *nw=nullptr,INT l=0,INT r=-1){
				if(!nw)nw=root;
				if(r==-1)r=n;
				if(r-l==1){
					nw->v=add2node(nw->v,v);
					return;
				}
				INT mid=(r-l)/2+l;
				if(l<=x&&x<mid){
					modify(x,v,nw->l(),l,mid);
				}else{
					modify(x,v,nw->r(),mid,r);
				}
				update(nw,r-l);
			}

	};
}



#ifdef DBG
using INT=long long int;
int main(){
	ET01::SEG seg;
	seg.merge2node=[](INT a,INT b){
		return std::max(a,b);
	};
	return 0;
}
#endif