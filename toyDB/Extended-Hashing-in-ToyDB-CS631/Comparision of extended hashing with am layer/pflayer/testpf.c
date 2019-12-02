/* testpf.c */
#include <stdio.h>
#include <stdlib.h>
#include "pf.h"
#include "pftypes.h"

#define FILE1	"file1"
#define FILE2	"file2"

main()
{
int error;
int i;
int pagenum,*buf;
int *buf1,*buf2;
int fd1,fd2;

	PFhashInit();
	if ((error = PF_CreateFile(FILE1)) != PFE_OK){
		PF_PrintError("file1");
		exit(1);
	}
	printf("file1 created\n");
	writefile(FILE1);
	readfile(FILE1);
	if ((error=PF_DestroyFile(FILE1))!= PFE_OK){
		PF_PrintError("destroy file1");
		exit(1);
	}

	printf("=========File1 Destroyed===========\n");

	if ((fd1=PF_CreateFile(FILE1))< 0){
		PF_PrintError("create file1");
		exit(1);
	}
	printf("file1 created\n");
	writefile(FILE1);

	/* Open the files, and see how the buffer manager
	handles more insertions, and deletions */
	if ((fd1=PF_OpenFile(FILE1))<0) {
		PF_PrintError("open file1\n");
		exit(1);
	}
	printf("opened file1\n");

	printf("=========Adding New Pages===========\n");
	for (i = 69; i < 73; i++){
		if ((error=PF_AllocPage(fd1,&pagenum,&buf))!= PFE_OK){
			PF_PrintError("first buffer\n");
			exit(1);
		}
		*((int *)buf) = i;
		if ((error=PF_UnfixPage(fd1,pagenum,TRUE))!= PFE_OK){
			PF_PrintError("unfix file1");
			exit(1);
		}
		printf("allocated page %d \n", pagenum);
	}

	PFhashPrint();

	printf("=========Deleting Pages===========\n");
	for (i = 12; i < 15; i++){
		if ((error=PF_DisposePage(fd1, i))!= PFE_OK){
			PF_PrintError("dispose fd1");
			exit(1);
		}
		printf("disposed page %d\n", i);
	}

	PFhashPrint();

	// printf("=========File 1===========\n");
	// printfile(fd1);
	// PFbufPrint();
	// PFhashPrint();

	if (PF_CloseFile(fd1) != PFE_OK){
		PF_PrintError("close fd1");
		exit(1);
	}
	return;
}


/************************************************************
Open the File.
allocate as many pages in the file as the buffer
manager would allow, and write the page number
into the data.
then, close file.
******************************************************************/
writefile(fname)
char *fname;
{
int fd,pagenum;
int *buf;
int error;

	/* open file1, and allocate a few pages in there */
	if ((fd = PF_OpenFile(fname)) < 0){
		PF_PrintError("open file1");
		exit(1);
	}
	printf("opened %s\n",fname);

	for (int i = 10; i < 25; ++i){
		if ((error=PF_AllocPage(fd ,&pagenum ,&buf))!= PFE_OK){
			PF_PrintError("first buffer\n");
			exit(1);
		}
		if ((error=PF_UnfixPage(fd,pagenum,TRUE))!= PFE_OK){
			PF_PrintError("unfix buffer\n");
			exit(1);
		}
		*((int *)buf) = i;
		printf("allocated page %d\n",pagenum);
	}
	PFhashPrint();
	if ((error=PF_CloseFile(fd))!= PFE_OK){
		PF_PrintError("close file11\n");
		exit(1);
	}
}

/**************************************************************
print the content of file
*************************************************************/
readfile(fname)
char *fname;
{
int error;
int pagenum;
int fd;

	printf("opening %s\n",fname);
	if ((fd=PF_OpenFile(fname))<0){
		PF_PrintError("open file");
		exit(1);
	}
	printfile(fd);
	if ((error=PF_CloseFile(fd))!= PFE_OK){
		PF_PrintError("close file");
		exit(1);
	}
	printf("closed %s\n",fname);
}

printfile(fd)
int fd;
{
int error;
int *buf;
int pagenum;

	printf("reading file\n");
	pagenum = -1;
	while ((error=PF_GetNextPage(fd,&pagenum,&buf))== PFE_OK){
		printf("got page %d, %d\n",pagenum, *buf);
		if ((error=PF_UnfixPage(fd,pagenum,FALSE))!= PFE_OK){
			PF_PrintError("unfix");
			exit(1);
		}
	}
	if (error != PFE_EOF){
		PF_PrintError("not eof\n");
		exit(1);
	}
	printf("eof reached\n");
}
