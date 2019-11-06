/* testhash.c: tests the hash table functions */
#include <stdio.h>
#include "pf.h"




void menu();
void insert();
void delete();
void find();
void printHash();
void fileHash();


main()
{
int i,k;
long j;
int  fd;


PFhashInit();

menu();


//initial code commented

	
	/*PF_Init();
	PF_CreateFile("fname");
	fd=PF_OpenFile("file1");*/
	/* insert a few entries */
	/*for (i=1; i < 11; i++)
		for (j=1; j < 11; j ++){
			if (PFhashInsert(i,j,i+j) != PFE_OK){
				printf("PFhashInsert failed\n");
				exit(1);
			}
		}*/

	/* Now, find all the entries */
	/*for (i=1; i < 11; i++)
		for (j=1; j < 11; j++){
			k = PFhashFind(i,j);
			if (k == NULL){
				printf("PFfind failed at %d %d\n",i,j);
				exit(1);
			}
			else
			printf("found \n");
		}*/

	/* Now, delete them in reverse */
	/*for (j =10; j > 0; j--)
		for (i=10; i > 0; i--)
			if (PFhashDelete(i,j) != PFE_OK){
				printf("PFhashDelete failed at %d %d",i,j);
				exit(1);
			}*/

	/* print the hash table out */
	//PFhashPrint();
}							//end of main


void menu()
{
	int choice;
	printf("****MENU****\n");
	printf("Please enter a choice:-\n1.Insert\n2.Delete\n3.Find\n4.Print Current hash table\n5.Hash a given file\n6.Exit\n");
	scanf("%d",&choice);
	switch(choice)
	{
	case 1:
		insert();
		break;
	case 2:
		delete();
		break;
	case 3:
		find();
		break;
	case 4:
		printHash();
		break;
	case 5:
		fileHash();
		break;
	case 6:
		exit(0);
	default:
		printf("Invalid Option. Try again.\n");
		menu();
	}

}


void insert()
{
	int fd, pageno,buff;
	printf("Please enter file descriptor\n");
	scanf("%d",&fd);
	printf("Please enter page no.\n");
	scanf("%d",&pageno);
	printf("Please enter Buffer address\n");
	scanf("%d",&buff);
	if (PFhashInsert(fd,pageno,buff) != PFE_OK)
	{
		printf("PFhashInsert failed\n");
		//exit(1);
	}

	menu();


}



void delete()
{

	int fd, pageno;
	printf("Please enter file descriptor\n");
	scanf("%d",&fd);
	printf("Please enter page no.\n");
	scanf("%d",&pageno);
	if (PFhashDelete(fd,pageno) != PFE_OK)
	{
		printf("PFhashDelete failed at %d %d\n",fd,pageno);
		//exit(1);
	}
	else
		printf("Delete Success\n");

	menu();

}

void find()
{
	int fd, pageno;
	int *buff;
	printf("Please enter file descriptor\n");
	scanf("%d",&fd);
	printf("Please enter page no.\n");
	scanf("%d",&pageno);
	buff = PFhashFind(fd,pageno);
	if (buff == NULL)
	{
		printf("PFfind failed at %d %d\n",fd,pageno);
		///exit(1);
	}
	else
		printf("found!!Address=%d\n",buff);
	menu();


}

void printHash()
{

	PFhashPrint();
	menu();

}


void fileHash()
{
	//char *fname;
	//scanf("%s",&fname);

	char *fname="file1";

	int error;
	int *buf;
	int pagenum;
	int fd;



	if ((fd=PF_OpenFile(fname))<0){
		PF_PrintError("open file1");
		exit(1);
	}
	printf("opened %s\n",fname);



	printf("reading file\n");
	pagenum = -1;
	while ((error=PF_GetNextPage(fd,&pagenum,&buf))== PFE_OK){
		printf("got page%d %d, %d\n",fd,pagenum,*buf);
		//PFhashPrint();
		/*if ((error=PF_UnfixPage(fd,pagenum,FALSE))!= PFE_OK){
			PF_PrintError("unfix");
			exit(1);
		}*/
	}
	if (error != PFE_EOF){
		PF_PrintError("not eof\n");
		exit(1);
	}
	printf("eof reached\n");

	menu();

}
