#include <stdio.h>
#include "pf.h"
#include "pftypes.h"

#define FILE1   "file3"
#define FILE2   "file4"

int main()

{

    int error;
    int i;
    int pagenum,*buf;
    int *buf1,*buf2;
    int fd1,fd2;

    if ((error=PF_CreateFile(FILE1))!= PFE_OK){
		PF_PrintError("file1");
		exit(1);
	}

	if ((error=PF_CreateFile(FILE2))!= PFE_OK){
		PF_PrintError("file2");
		exit(1);
	}

    writefile(FILE1);
    //PFhashPrint();
	//PFbufPrint();

	// writefile(FILE2);
    // PFhashPrint();
	// PFbufPrint();
    
}

writefile(char *fname)
{
    int i;
    int fd,pagenum;
    int *buf;
    int error;

	/* open file1, and allocate a few pages in there */
	if ((fd=PF_OpenFile(fname))<0){
		PF_PrintError("open file1");
		exit(1);
	}
	printf("opened %s\n",fname);

	for (i=0; i < 2; i++){
		if ((error=PF_AllocPage(fd,&pagenum,&buf))!= PFE_OK){
			PF_PrintError("first buffer\n");
			exit(1);
		}
		*((int *)buf) = i;
		printf("allocated page %d\n",pagenum);
		// printf("buf page %d\n",*buf);
	}

	// if ((error=PF_AllocPage(fd,&pagenum,&buf))==PFE_OK){
	// 	printf("too many buffers, and it's still OK\n");
	// 	//exit(1);
	// }
	PFhashPrint();
	PFbufPrint();
	for (i=0; i < 1; i++){
		if ((error=PF_UnfixPage(fd,i,TRUE))!= PFE_OK){
			PF_PrintError("unfix buffer\n");
			exit(1);
		}
	}
	PFhashPrint();
	PFbufPrint();
	if ((error=PF_CloseFile(fd))!= PFE_OK){
		PF_PrintError("close file1\n");
		exit(1);
	}

}
