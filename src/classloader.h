#ifndef _CLASSLOADER_H_
#define _CLASSLOADER_H_
#include <boost/smart_ptr.hpp>
#include <boost/utility/string_ref.hpp>
#include <map>
#include <string>
#include <vector>
//#include <map>
using namespace boost;
using namespace std;
class Class;
class Field;
class Slot;

class ClassLoader
{
public:
	typedef shared_ptr<ClassLoader> Pointer;
	typedef shared_ptr<map<string,shared_ptr<Class> > > ClassMap;
private:
	ClassMap classMap;
	ClassLoader();
public:
	static Pointer build();
	shared_ptr<Class> loadClass(string_ref name);
	shared_ptr<vector<string> > mapedNames();
private:
	shared_ptr<Class> loadNonArrayClass(string_ref name);
	void link(shared_ptr<Class> clazz);
	void verify(shared_ptr<Class> clazz);
	void prepare(shared_ptr<Class> clazz);
	void resolveSuperClass(shared_ptr<Class> clazz);
	void resolveInterfaces(shared_ptr<Class> clazz);
	void calcInstanceFieldSlotIds(shared_ptr<Class> clazz);
	void calcStaticFieldSlotIds(shared_ptr<Class> clazz);
	void allocAndInitStaticVars(shared_ptr<Class> clazz);
	void initStaticFinalField(shared_ptr<Class> clazz,shared_ptr<Field> field,shared_ptr<vector<Slot> > staticFields);
	
};

#endif