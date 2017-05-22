#ifndef _SWITCHMANAGER_H_
#define _SWITCHMANAGER_H_
#include <utility>
#include <vector>
#include <boost/smart_ptr.hpp>
#include <boost/function.hpp>
using namespace boost;
using namespace std;
template<class T,class V,class P>
class SwitchManager{
public:
	typedef pair<T,function<V(P)> > ActorPair;
private:
	vector<ActorPair> actors;
public:
	void addCondition(T key,function<V(P)> handler);
	V execute(T key,P data);
};


template<class T,class V,class P>
void SwitchManager<T,V,P>::addCondition(T key,function<V(P)> handler){
	ActorPair p;
	p.first= key;
	p.second = handler;
	actors.push_back(p);
}

template<class T ,class V,class P>
V SwitchManager<T,V,P>::execute(T key,P data){
    typename vector<pair<T,function<V(P)> > >::iterator iter;
	for(iter=actors.begin();iter!=actors.end();++iter){
		ActorPair p = *iter;
		if(p.first == key){
			return p.second(data);
		}
	}
	return make_shared<V>();
}

#endif
