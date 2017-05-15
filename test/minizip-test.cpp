#include <iostream>
#include <fstream>
#include <zlib.h>
#include <zip.h>
#include <unzip.h>

using namespace std;

int main(){
	char *buf = new char[1024 * 512];
	zipFile zf = NULL;
	zf = zipOpen64("zlib-test.zip",0);
	zip_fileinfo fileInfo;
	int ret;
	
	zipOpenNewFileInZip(zf,"zlib-test.cpp",&fileInfo,NULL,0,NULL,0,NULL,Z_DEFLATED,9);
	ifstream infile("zlib-test.cpp");

	do{
		infile.read(buf,1024 * 512);
		long readlen = infile.gcount();
		ret = zipWriteInFileInZip(zf,buf,readlen);
		if(ret != ZIP_OK){
		}

	}while(!infile.eof());

	delete[] buf;
	zipClose(zf,NULL);
	
}
