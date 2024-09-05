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
			};
			node *root=nullptr;
		public:
			INT zero=0;
			std::function<INT(INT,INT,INT)>szop=[](INT orig,INT v,INT sz){ // update
				return orig+v;
			};
			void build(
				std::vector<INT>::iterator l,
				std::vector<INT>::iterator r,
				node *nw=nullptr){
					if(!nw){
						root=new node;
						nw=root;
						n=r-l;
					}
					if(r-l==1){
						free(nw->l());
						free(nw->r());
						nw->l()=nw->r()=nullptr;
						nw->v=*l;
						return;
					}
					else{
						auto mid=(r-l)/2+l;
						build(l,mid,nw->l());
						build(mid,r,nw->r());
						nw->v=std::max(nw->l()->v, nw->r()->v); // update
					}
			}
			void modify(INT x,INT v,node *nw=nullptr,INT l=0,INT r=-1){
				if(!nw)nw=root;
				if(r==-1)r=n;

				std::cout<<"x:"<<x<<" v:"<<v<<" l:"<<l<<" r:"<<r<<std::endl;

				if(r-l==1){
					nw->v=nw->v+v; // update
					return;
				}
				INT mid=(r-l)/2+l;
				if(l<=x&&x<mid){
					modify(x,v,nw->l(),l,mid);
				}else{
					modify(x,v,nw->r(),mid,r);
				}
				nw->v=std::max(nw->l()->v,nw->r()->v); // update
			}
			void loop_modify(INT l,INT r,INT v,node *nw=nullptr,INT nl=0,INT nr=-1){
				if(!nw)nw=root;
				if(nr==-1)nr=n;
				if(l<=nl&&nr<=r){
					nw->land=nw->land+v; // update
					return;
				}
				if(r<=nl||nr<=l)return;
				INT mid=(nr-nl)/2+nl;
				loop_modify(l,r,v,nw->l(),nl,mid);
				loop_modify(l,r,v,nw->r(),mid,nr);
			}
			INT loop_query(INT l,INT r,node *nw=nullptr,INT nl=0,INT nr=-1){
				if(!nw)nw=root;
				if(nr==-1)nr=n;
				INT mid=(nr-nl)/2+nl;
				nw->v=szop(nw->v,nw->land,nr-nl);
				if(nw->_l)nw->l()->land=nw->l()->land+nw->land;
				if(nw->_r)nw->r()->land=nw->r()->land+nw->land;
				nw->land=zero;
				if(l<=nl&&nr<=r){
					return nw->v;
				}
				else
				if(l<mid && mid<r){
					return std::max( // update
						loop_query(l,r,nw->l(),nl,mid),
						loop_query(l,r,nw->r(),mid,nr)
					);
				}
				else if(l<mid){
					return loop_query(l,r,nw->l(),nl,mid);
				}
				else{
					return loop_query(l,r,nw->r(),mid,nr);
				}
			}
			INT query(INT x){
				return loop_query(x,x+1);
			}
	};
};