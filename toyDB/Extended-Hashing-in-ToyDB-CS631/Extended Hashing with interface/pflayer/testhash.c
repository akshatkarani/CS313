/* testhash.c: tests the hash table functions */
#include <stdio.h>
#include "pf.h"
#include <stdlib.h>

void menu();
void insert();
void delete();
void find();
void printHash();

int main()
{
	PFhashInit();
	menu();
	return 0;
}

void menu()
{
	int choice;
	printf("****MENU****\n");
	printf("Please enter a choice:-\n1.Insert\n2.Delete\n3.Find\n4.Print Current hash table\n5.Exit\n");
	scanf("%d", &choice);
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
		exit(0);
	default:
		printf("Invalid Option. Try again.\n");
		menu();
	}
}

void insert()
{
	int fd, pageno, buff;
	printf("Please enter file descriptor\n");
	scanf("%d", &fd);
	printf("Please enter page no.\n");
	scanf("%d", &pageno);
	printf("Please enter Buffer address\n");
	scanf("%d", &buff);
	if (PFhashInsert(fd,pageno,buff) != PFE_OK)
	{
		printf("PFhashInsert failed\n");
	}
	menu();
}

void delete()
{
	int fd, pageno;
	printf("Please enter file descriptor\n");
	scanf("%d", &fd);
	printf("Please enter page no.\n");
	scanf("%d", &pageno);
	if (PFhashDelete(fd, pageno) != PFE_OK)
	{
		printf("PFhashDelete failed at %d %d\n", fd, pageno);
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
