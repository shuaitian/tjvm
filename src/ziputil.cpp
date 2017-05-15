#include "ziputil.h"
#include <stdio.h>
#include <unzip.h>

ZipUtil::ZipUtil(string_ref filename):
	zipFilename(filename.data())
{
	uf = unzOpen(zipFilename.c_str());
	if(uf == NULL){
		printf("open file %s failed\n", zipFilename.c_str());
		exit(-1);
	}
	//get file list
	unsigned long i;
	unz_global_info64 gi;
	int err;
	err = unzGetGlobalInfo64(uf,&gi);
	if(err != UNZ_OK){
		printf("error %d with zipfile in unzGetGlobalInfo \n",err);
	}
	for(i=0;i<gi.number_entry;i++){
		char filename_inzip[256];
		unz_file_info64 file_info;
		err = unzGetCurrentFileInfo64(uf,&file_info,filename_inzip,sizeof(filename_inzip),NULL,0,NULL,0);
		if(err!=UNZ_OK){
			printf("error %d with zipfile in unzGetCurrentFileInfo\n",err);
            break;
		}
		fileList.push_back(filename_inzip);
		if((i+1)<gi.number_entry){
			err = unzGoToNextFile(uf);
			if(err != UNZ_OK){
				printf("error %d with zipfile in unzGoToNextFile\n",err);
                break;
			}
		}
	}
}

vector<string>& ZipUtil::getFileNames(){
	return fileList;
}

shared_ptr<ByteArray> ZipUtil::extractFileByName(string_ref filename){
	shared_ptr<ByteArray> ret = make_shared<ByteArray>();
	unzFile uf = unzOpen(zipFilename.c_str());
	int err = UNZ_OK;
	//locate file
	if(unzLocateFile(uf,filename.data(),0)!=UNZ_OK){
		printf("file %s not found in the zipfile\n",filename.data());
        exit(-1);
	}
	
	//extract current file
	char filename_inzip[256];
	char *filename_withoutpath;
	char *p;
	FILE *fout = NULL;
	void *buf;
	unsigned int size_buf;
	unz_file_info64 file_info;

	err = unzGetCurrentFileInfo64(uf,&file_info,filename_inzip,sizeof(filename_inzip),NULL,0,NULL,0);
	if(err!=UNZ_OK){
		printf("error %d with zipfile in unzGetCurrentFileInfo\n",err);
        exit(-1);
	}
	size_buf = 8192;
	buf = (void*)malloc(size_buf);
	if(buf == NULL){
		printf("Error allocating memory\n");
        exit(-1);
	}

	p = filename_withoutpath = filename_inzip;
	while ((*p) != '\0')
    {
        if (((*p)=='/') || ((*p)=='\\'))
            filename_withoutpath = p+1;
        p++;
    }

	{
		const char* write_filename;
		write_filename = filename_withoutpath;
		fout=fopen(write_filename,"wb");

		err = unzOpenCurrentFilePassword(uf,NULL);
		if(UNZ_OK != err){
			printf("unzOpenCurrentFilePassword failed... error:%d\n", err);  
        	exit(-1);
		}
		do{
			err = unzReadCurrentFile(uf,buf,size_buf);
			if(err < 0){
				 printf("error %d with zipfile in unzReadCurrentFile\n",err);
                 break;
			}
			if(err > 0){
				//if(fwrite(buf,err,1,fout)!=1){
				//	 printf("error in writing extracted file\n");
                //     err=UNZ_ERRNO;
                //     break;
				//}
				ret->append(buf,err);
			}
		}while(err>0);

		if(fout){
			fclose(fout);
		}
		
	}

	if(err == UNZ_OK){
		err = unzCloseCurrentFile(uf);
		if(err != UNZ_OK){
			printf("error %d with zipfile in unzCloseCurrentFile\n",err);
		}
	}
	else
		unzCloseCurrentFile(uf);

	free(buf);
	return ret;
}
