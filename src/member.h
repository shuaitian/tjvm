#ifndef _MEMBER_H_
#define _MEMBER_H_
#include <boost/smart_ptr.hpp>
#include <boost/utility/string_ref.hpp>
#include "memberitem.h"
#include <vector>
using namespace boost;
using namespace std;

typedef shared_ptr<vector<shared_ptr<MemberItem> > > MemItemVecPtr;

class Member{
protected:
	MemItemVecPtr member_items;
public:
	void setMemberItems(MemItemVecPtr member_items){
		this->member_items = member_items;
	}

	MemItemVecPtr getMemberItems(){
		return this->member_items;
	}
	void display(const char* memberType);
	MemberItemPtr getMemberItemByNameAndDesc(string_ref name,string_ref desc);
};

typedef shared_ptr<Member> MemberPtr;

#endif
