/* testhash.c: tests the hash table functions */
#include <stdio.h>
#include "pf.h"
#include <stdlib.h>

void insert();
void delete();
void find();
void printHash();

int main()
{
	PFhashInit();
	printf("Welcome to our simulator. Let's Begin\nFollowing options can be simulated\n\n");
	while(1)
	{
	int choice;
	printf("\n1.Current status of hash table\n2.Insert a page\n3.Find a page\n4.Delete a page\n5.Exit\n\n");
	scanf("%d", &choice);
	if(choice == 1)
	{
		printHash();
	}
	else if(choice == 2)
	{
		insert();
	}
	else if(choice == 3)
	{
		find();
	}
	else if(choice == 4)
	{
		delete();
	}
	else if(choice == 5)
	{
		exit(0);
	}
	else
	{
		printf("Sorry wrong Option. Choose again.\n");
	}
	}
	return 0;
}

void insert()
{
	int fd, pageno, buff;
	printf("File Descriptor: ");
	scanf("%d", &fd);
	printf("\nPage No.: ");
	scanf("%d", &pageno);
	printf("\nBuffer address: ");
	scanf("%d", &buff);
	if (PFhashInsert(fd,pageno,buff) != PFE_OK)
	{
		printf("Insert Terminated due to error\n");
	}
}

void delete()
{
	int fd, pageno;
	printf("File Descriptor: ");
	scanf("%d", &fd);
	printf("\nPage No.: ");
	scanf("%d", &pageno);
	if (PFhashDelete(fd, pageno) != PFE_OK)
	{
		printf("Delete could not take place at %d %d\n", fd, pageno);
	}
	else
		printf("Delete Successfully\n");
}

void find()
{
	int fd, pageno;
	int *buff;
	printf("File Descriptor: ");
	scanf("%d",&fd);
	printf("\nPage No.: ");
	scanf("%d",&pageno);
	buff = PFhashFind(fd,pageno);
	if (buff == NULL)
	{
		printf("Could not find %d %d\n",fd,pageno);
	}
	else
		printf("Address found = %d\n",buff);
}

void printHash()
{
	PFhashPrint();
}
