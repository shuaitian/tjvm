#include "methodmember.h"

MemberItemPtr MethodMember::getMainMethod(){
	return getMemberItemByNameAndDesc("main","(Ljava/lang/String;)V");
}