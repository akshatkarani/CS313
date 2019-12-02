/* hash.c: Functions to facilitate finding the buffer page given
a file descriptor and a page number */
#include <stdio.h>
#include "pf.h"
#include "pftypes.h"

/* hash table */

extern char *malloc();
extern char *realloc();
static PFhash_entry **PFhashtbl;

void PFhashInit()
/****************************************************************************
SPECIFICATIONS:
	Init the hash table entries. Must be called before any of the other
	hash functions are used.

AUTHOR: clc

RETURN VALUE: none

GLOBAL VARIABLES MODIFIED:
	PFhashtbl
*****************************************************************************/
{
	PF_HASH_TBL_SIZE = 4;
	PFhashtbl = (PFhash_entry **) malloc(PF_HASH_TBL_SIZE * sizeof(PFhash_entry *));
	for(int i = 0; i < PF_HASH_TBL_SIZE; ++i)
		PFhashtbl[i] = NULL;
}


PFbpage *PFhashFind(fd,page)
int fd;		/* file descriptor */
int page;	/* page number */
/****************************************************************************
SPECIFICATIONS:
	Given the file descriptor "fd", and page number "page",
	find the buffer address of this particular page.

AUTHOR: clc

RETURN VALUE:
	NULL	if not found.
	Buffer address, if found.

*****************************************************************************/
{
	int bucket;	/* bucket to look for the page*/
	PFhash_entry *entry; /* ptr to entries to search */
	/* See which bucket it is in */
	bucket = PFhash(fd,page);
	
	entry = PFhashtbl[bucket]; 
	if(entry != NULL)
	{
		if (entry->f1 == fd && entry->page1 == page )
			return(entry->bpage1);
		if (entry->f2 == fd && entry->page2 == page )
			return(entry->bpage2);
		if (entry->f3 == fd && entry->page3 == page )
			return(entry->bpage3);
		if (entry->f4 == fd && entry->page4 == page )
			return(entry->bpage4);
	}
	/* not found */
	return(NULL);
}

PFhashInsert(fd,page,bpage)
int fd;		/* file descriptor */
int page;	/* page number */
PFbpage *bpage;	/* buffer address for this page */
/*****************************************************************************
SPECIFICATIONS:
	Insert the file descriptor "fd", page number "page", and the
	buffer address "bpage" into the hash table. 

AUTHOR: clc

RETURN VALUE:
	PFE_OK	if OK
	PFE_NOMEM	if nomem
	PFE_HASHPAGEEXIST if the page already exists.
	
GLOBAL VARIABLES MODIFIED:
	PFhashtbl
*****************************************************************************/
{
	int bucket;	/* bucket to insert the page */
	PFhash_entry *entry; /* pointer to new entry */

	if (PFhashFind(fd,page) != NULL)
	{
		/* page already inserted */
		PFerrno = PFE_HASHPAGEEXIST;
		printf("Page Already Existed\n");
		return(PFerrno);
	}
	
	/* find the bucket for this page */
	bucket = PFhash(fd,page);

	if(PFhashtbl[bucket]==NULL)
	{
		/* allocate mem for new entry */
		if ((entry=(PFhash_entry *)malloc(sizeof(PFhash_entry)))== NULL)
		{			
		/* no mem */
			PFerrno = PFE_NOMEM;
			return(PFerrno);
		}
		/* Insert entry as head of list for this bucket */
		entry->f1 = fd;
		entry->page1 = page;
		entry->bpage1 = bpage;
		entry->localDepth = globalDepth;	

		entry->f2 = -1;
		entry->page2 = -1;
		entry->bpage2 = -1;

		entry->f3 = -1;
		entry->page3 = -1;
		entry->bpage3 = -1;

		entry->f4 = -1;
		entry->page4 = -1;
		entry->bpage4 = -1;

		PFhashtbl[bucket] = entry;
		return(PFE_OK);
	}

	entry = PFhashtbl[bucket];
	if((entry->f1)==-1)
	{
		entry->f1 = fd;
		entry->page1 = page;
		entry->bpage1 = bpage;
	}
	else if((entry->f2)==-1)
	{	
		entry->f2 = fd;
		entry->page2 = page;
		entry->bpage2 = bpage;
	}
	else if((entry->f3)==-1)
	{	
		entry->f3 = fd;
		entry->page3 = page;
		entry->bpage3 = bpage;
	}
	else if((entry->f4)==-1)
	{
		entry->f4 = fd;
		entry->page4 = page;
		entry->bpage4 = bpage;
	}
	else
	{
		PFhashSplitBucket(entry->localDepth, bucket, fd, page, bpage);	 
	}
	return(PFE_OK);	
}

PFhashSplitBucket(int localDepth, int bucket, int fd, int page, PFbpage *bpage)
{
	PFhash_entry *entry;

	entry = PFhashtbl[bucket];
	printf("\nBucket have to split\n");
	if(localDepth == globalDepth)
	{
		doubleTable();
	}	

	if(localDepth < globalDepth)
	{
		struct temp
		{
			int fd;
			int page;
			PFbpage *bpage;			
		};

		struct temp *temp[5];
		for (int i = 0; i < 5; ++i)
		{
			temp[i] = (struct temp *)malloc(sizeof(struct temp));
		}
		
		temp[0]->fd = entry->f1;
		temp[0]->page = entry->page1;
		temp[0]->bpage = entry->bpage1;

		temp[1]->fd = entry->f2;
		temp[1]->page = entry->page2;
		temp[1]->bpage = entry->bpage2;

		temp[2]->fd = entry->f3;
		temp[2]->page = entry->page3;
		temp[2]->bpage = entry->bpage3;

		temp[3]->fd = entry->f4;
		temp[3]->page = entry->page4;
		temp[3]->bpage = entry->bpage4;

		temp[4]->fd = fd;
		temp[4]->page = page;
		temp[4]->bpage = bpage;

		int startBucket=(bucket % (1 << entry->localDepth));
		int i = 0;
		while(startBucket < PF_HASH_TBL_SIZE)
		{
			int *t = PFhashtbl[startBucket];
			PFhashtbl[startBucket]=NULL;
			++i;
			startBucket = startBucket + (1 << localDepth);
		}
		
		PFhashInsert(temp[0]->fd,temp[0]->page,temp[0]->bpage);
		PFhashInsert(temp[1]->fd,temp[1]->page,temp[1]->bpage);
		PFhashInsert(temp[2]->fd,temp[2]->page,temp[2]->bpage);
		PFhashInsert(temp[3]->fd,temp[3]->page,temp[3]->bpage);
		PFhashInsert(temp[4]->fd,temp[4]->page,temp[4]->bpage);
		printf("Bucket split Successful\n");
		// PFhashPrint();
		return;
	}
}

void doubleTable()
{
	printf("Hash Table size has to be Doubled.\n");
	PF_HASH_TBL_SIZE = PF_HASH_TBL_SIZE * 2;
	PFhashtbl = (PFhash_entry **) realloc(PFhashtbl, PF_HASH_TBL_SIZE * sizeof(PFhash_entry *));
	for (int i = PF_HASH_TBL_SIZE / 2, j = 0; i < PF_HASH_TBL_SIZE; i++, j++)
	{
		PFhashtbl[i] = PFhashtbl[j];
	}
	globalDepth = globalDepth + 1;
	printf("Doubled Successfully\n");
}

PFhashDelete(int fd, int page)
	/* file descriptor */
	/* page number */
/****************************************************************************
SPECIFICATIONS:
	Delete the entry whose file descriptor is "fd", and whose page number
	is "page" from the hash table.

AUTHOR: clc

RETURN VALUE:
	PFE_OK	if OK
	PFE_HASHNOTFOUND if can't find the entry

GLOBAL VARIABLES MODIFIED:
	PFhashtbl
*****************************************************************************/
{
	int bucket;	/* bucket for this page */
	PFhash_entry *entry;	/* entry to look for */
	/* find the bucket */
	bucket = PFhash(fd,page);
	entry=PFhashtbl[bucket];
	if (entry == NULL)
	{
		/* not found */
		PFerrno = PFE_HASHNOTFOUND;
		return(PFerrno);
	}
	/* See if the entry is in this bucket */
	if (entry->f1 == fd && entry->page1 == page)
	{
		entry->f1=-1;
		entry->page1=-1;
		entry->bpage1=-1;
	}
	else if (entry->f2 == fd && entry->page2 == page)
	{
		entry->f2=-1;
		entry->page2=-1;
		entry->bpage2=-1;
	}
	else if (entry->f3 == fd && entry->page3 == page)
	{
		entry->f3=-1;
		entry->page3=-1;
		entry->bpage3=-1;
	}
	else if (entry->f4 == fd && entry->page4 == page)
	{
		entry->f4=-1;
		entry->page4=-1;
		entry->bpage4=-1;
	}
	
	return(PFE_OK);
}

PFhashPrint()
/****************************************************************************
SPECIFICATIONS:
	Print the hash table entries.

AUTHOR: clc

RETURN VALUE: None
*****************************************************************************/
{
	PFhash_entry *entry;

	printf("%d\n", PF_HASH_TBL_SIZE );
	for (int i=0; i < PF_HASH_TBL_SIZE; ++i)
	{
		printf("bucket %d\n",i);
		if (PFhashtbl[i] == NULL)
		{
			printf("\tempty\n");
		}
		else
		{
			entry = PFhashtbl[i];
			if(entry != NULL)
			{
				if((entry->localDepth) == globalDepth)
				{
					if(entry->f1 == -1)
						printf("\tNULL\n");
					else
						printf("\tfd: %d, page: %d buffer: %d\n",entry->f1, entry->page1,entry->bpage1);
					if(entry->f2 == -1)
						printf("\tNULL\n");
					else
						printf("\tfd: %d, page: %d buffer: %d\n",entry->f2, entry->page2,entry->bpage2);
					if(entry->f3 == -1)
						printf("\tNULL\n");
					else
						printf("\tfd: %d, page: %d buffer: %d\n",entry->f3, entry->page3,entry->bpage3);
					if(entry->f4 == -1)
						printf("\tNULL\n");
					else
						printf("\tfd: %d, page: %d buffer: %d\n",entry->f4, entry->page4,entry->bpage4);
				}
				else
				{
					if(entry->f1 == -1)
						printf("\tNULL\n");
					else
						printf("\tfd: %d, page: %d buffer: %d\n",entry->f1, entry->page1,entry->bpage1);
					if(entry->f2 == -1)
						printf("\tNULL\n");
					else
						printf("\tfd: %d, page: %d buffer: %d\n",entry->f2, entry->page2,entry->bpage2);
					if(entry->f3 == -1)
						printf("\tNULL\n");
					else
						printf("\tfd: %d, page: %d buffer: %d\n",entry->f3, entry->page3,entry->bpage3);
					if(entry->f4 == -1)
						printf("\tNULL\n");
					else
						printf("\tfd: %d, page: %d buffer: %d\n",entry->f4, entry->page4,entry->bpage4);

					if(i != (i % (1 << entry->localDepth)))
						printf("\tThis bucket Pointer is Redirecting to->bucket %d\n",(i % (1 << entry->localDepth)));
				}
			}
		}
	}
}
