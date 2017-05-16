#include <boost/filesystem.hpp>
#include <iostream>
using namespace std;
using namespace boost::filesystem;
int main(){
	path p("/usr");
	p /= "lib";
	directory_iterator end;
	for(directory_iterator pos(p);pos != end; ++pos){
		cout << *pos << endl;
	}
}
