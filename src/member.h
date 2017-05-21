#ifndef _MEMBER_H_
#define _MEMBER_H_
#include <boost/smart_ptr.hpp>
#include "memberitem.h"
#include <vector>
using namespace boost;
using namespace std;

typedef shared_ptr<vector<shared_ptr<MemberItem> > > MemItemVecPtr;

class Member{
private:
	MemItemVecPtr member_items;
public:
	void setMemberItems(MemItemVecPtr member_items){
		this->member_items = member_items;
	}

	MemItemVecPtr getMemberItems(){
		return this->member_items;
	}
	void display(const char* memberType);
};

typedef shared_ptr<Member> MemberPtr;

#endif
