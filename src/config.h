#ifndef _CONFIG_H_
#define _CONFIG_H_
#include <string>
#include <vector>
#include <boost/utility/string_ref.hpp>
#include <boost/smart_ptr.hpp>
#include <boost/program_options.hpp>
using namespace std;
using namespace boost;
using namespace boost::program_options;
class Config{
private:
	char** argv;
	int argc;
	static shared_ptr<Config> self;
	variables_map vm;
	options_description opts;
public:
	static void build(char** argv,int argc);
	static shared_ptr<Config> instance();
	Config(char** argv,int argc);
	string get(string_ref key);
	bool contains(string_ref key);
	options_description& getOpts();
	bool check();
};


#endif
