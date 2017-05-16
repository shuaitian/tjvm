#include "config.h"
#include <iostream>
#include <stdlib.h>

shared_ptr<Config> Config::self;

void Config::build(char** argv,int argc){
	if(!self){
		self = make_shared<Config>(argv,argc);
	}
}

shared_ptr<Config> Config::instance(){
	return self;
}

Config::Config(char** argv,int argc):
	argv(argv),
	argc(argc),
	opts("Options")
{
	const char* jrePath = getenv("JAVA_HOME");
	if(jrePath == NULL){
		jrePath = ".";
	}
	opts.add_options()
		("help","help info")
		("versionv","version")
		("classpath",value<string>()->default_value("."),"class path")
		("jre",value<string>()->default_value(jrePath),"jre home")
		("mainClass",value<string>(),"main class")
	;
	positional_options_description pod;
	pod.add("mainClass",1);
	store(
		command_line_parser(argc,argv)
			.options(opts)
			.positional(pod)
			.run(),
		vm);
//	notify(vm);
}

string Config::get(string_ref key){
	return vm[key.data()].as<string>();
}

bool Config::contains(string_ref key){
	return vm.count(key.data());
}

options_description& Config::getOpts(){
	return opts;
}

bool Config::check(){
	try{
		vm["mainClass"].as<string>();
	}catch(boost::exception &e){
		return false;
	}
	return true;
}
