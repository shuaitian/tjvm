#include <boost/program_options.hpp>
#include <string>
#include <iostream>

using namespace std;
using namespace boost;
using namespace boost::program_options;

int main(int arc,char** argv){
	positional_options_description pod;
	pod.add("filename",1);
	
	store(
		command_line_parser(argc,argv)
			.positional(pod)
			.run(),
		vm
	);
}
