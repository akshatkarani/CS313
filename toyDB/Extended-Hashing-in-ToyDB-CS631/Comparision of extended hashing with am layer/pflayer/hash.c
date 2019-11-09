/* hash.c: Functions to facilitate finding the buffer page given
a file descriptor and a page number */
#include <stdio.h>
#include "pf.h"
#include "pftypes.h"
//#include <stdlib.h>



/* hash table */
//static PFhash_entry *PFhashtbl[PF_HASH_TBL_SIZE];

extern char *malloc();
extern char *realloc();
//static PFhash_entry **PFhashtbl=(PFhash_entry **)malloc(PF_HASH_TBL_SIZE*sizeof(PFhash_entry *));
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
	int i;
	PFhashtbl = (PFhash_entry **)malloc(PF_HASH_TBL_SIZE*sizeof(PFhash_entry *));
	for (i=0; i < PF_HASH_TBL_SIZE; i++)
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
	
	/* go through the list of this bucket */
		entry=PFhashtbl[bucket]; 
		if(entry != NULL)
		{
		
		if (entry->fd == fd && entry->page == page )
			/* found it */
			return(entry->bpage);
		if (entry->fd2 == fd && entry->page2 == page )
			/* found it */
			return(entry->bpage2);
		if (entry->fd3 == fd && entry->page3 == page )
			/* found it */
			return(entry->bpage3);
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

	//PFhashPrint();
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
		//printf("if NULL\n");
		if ((entry=(PFhash_entry *)malloc(sizeof(PFhash_entry)))== NULL)
		{
			
		/* no mem */
			PFerrno = PFE_NOMEM;
			return(PFerrno);
		}
	

		

	/* Insert entry as head of list for this bucket */
		entry->fd = fd;
		entry->page = page;
		entry->bpage = bpage;
		entry->localDepth = globalDepth;				//Local depth is initially 2

		entry->fd2 = -1;
		entry->page2 = -1;
		entry->bpage2 = -1;
		entry->fd3 = -1;
		entry->page3 = -1;
		entry->bpage3 = -1;

		//printf("%d %d %d %d\n",entry->localDepth,entry->fd2,entry->fd3,entry->bpage3);
		//entry->nextentry = PFhashtbl[bucket];
		//entry->preventry = NULL;
		//if (PFhashtbl[bucket] != NULL)
		//PFhashtbl[bucket]->preventry = entry;
		PFhashtbl[bucket] = entry;
		return(PFE_OK);
	}

	entry=PFhashtbl[bucket];

	if((entry->fd)==-1)
	{
		
		entry->fd = fd;
		entry->page = page;
		entry->bpage = bpage;
		return(PFE_OK);

	}


	if((entry->fd2)==-1)
	{
		
		entry->fd2 = fd;
		entry->page2 = page;
		entry->bpage2 = bpage;
		return(PFE_OK);

	}

	if((entry->fd3)==-1)
	{
		
		entry->fd3 = fd;
		entry->page3 = page;
		entry->bpage3 = bpage;
		return(PFE_OK);
	}
		
		PFhashSplitBucket(entry->localDepth,bucket,fd,page,bpage);
		
		return(PFE_OK);
	
}





PFhashSplitBucket(int localDepth,int bucket,int fd,int page,PFbpage *bpage)
{
	int i=0;		//used to count while loop
	PFhash_entry *entry; /* pointer to new entry */

	entry=PFhashtbl[bucket];
	printf("\nBucket have to split\n");
	if(localDepth==globalDepth)
	{
		doubleTable();
		//return;	
	}
	
	//printf("after doubleTable\n");
	if(localDepth<globalDepth)
	{
		//printf("After comparisio\n");
		//bucket = PFhash(fd,page);

		struct temp
		{
			int fd;
			int page;
			PFbpage *bpage;			
		};
		struct temp *temp[4];
		temp[0]=(struct temp *)malloc(sizeof(struct temp));
		temp[1]=(struct temp *)malloc(sizeof(struct temp));
		temp[2]=(struct temp *)malloc(sizeof(struct temp));
		temp[3]=(struct temp *)malloc(sizeof(struct temp));


		//printf("before assign\n");
		temp[0]->fd=entry->fd;
		temp[0]->page=entry->page;
		temp[0]->bpage=entry->bpage;

		temp[1]->fd=entry->fd2;
		temp[1]->page=entry->page2;
		temp[1]->bpage=entry->bpage2;

		temp[2]->fd=entry->fd3;
		temp[2]->page=entry->page3;
		temp[2]->bpage=entry->bpage3;

		temp[3]->fd=fd;
		temp[3]->page=page;
		temp[3]->bpage=bpage;
		//printf("After assign\n");
		//printf("Temp value of bucket to be split:- %d %d %d %d\n",temp[0]->fd,temp[1]->fd,temp[2]->fd,temp[3]->fd );
		//return;
		int startBucket=(bucket%(1<<entry->localDepth));
		while(startBucket<PF_HASH_TBL_SIZE)
		{
			int *t=PFhashtbl[startBucket];
			PFhashtbl[startBucket]=NULL;
			i++;
			//printf("Inside while\n");

			//free(t);
			startBucket=startBucket+(1<<localDepth);
		}
		
		//printf("after while\n");
		PFhashInsert(temp[0]->fd,temp[0]->page,temp[0]->bpage);
		PFhashInsert(temp[1]->fd,temp[1]->page,temp[1]->bpage);
		PFhashInsert(temp[2]->fd,temp[2]->page,temp[2]->bpage);
		PFhashInsert(temp[3]->fd,temp[3]->page,temp[3]->bpage);
		printf("Bucket split Successful\n");

		PFhashPrint();
		return;

		
		/*i=0;
		while(initialBucket<PF_HASH_TBL_SIZE)
		{
			PFhashtbl[initialBucket]->localDepth=globalDepth;
			i++;
			initialBucket=initialBucket+(i*(1<<localDepth))
		}*/

	}


}


void doubleTable()
{
	int i,j;
	printf("\nHash Table size have to be Doubled.\n");
	PF_HASH_TBL_SIZE=PF_HASH_TBL_SIZE*2;
	printf("spot1%d\n",PF_HASH_TBL_SIZE);
	PFhashtbl = (PFhash_entry **)realloc(PFhashtbl,PF_HASH_TBL_SIZE*sizeof(PFhash_entry *));
	printf("spot2\n");

	for (i=PF_HASH_TBL_SIZE/2,j=0; i < PF_HASH_TBL_SIZE; i++,j++)
	{
		//printf("%d  %d\n",i,j );
		//printf("beforen%d  %d\n",PFhashtbl[i],PFhashtbl[j] );
		PFhashtbl[i] = PFhashtbl[j];
		//printf("after %d  %d\n",PFhashtbl[i],PFhashtbl[j] );
		//printf("after prev %d  %d\n",PFhashtbl[i-1],PFhashtbl[j-1] );

	}

	//printf("%d\n",PFhashtbl[6] );

	/*for (int i = 0; i < PF_HASH_TBL_SIZE; ++i)
	{
		printf("val%d\n",PFhashtbl[i] );
	}

	printf("spot3\n");*/

	globalDepth=globalDepth+1;
	//printf("spot4\n");
	//PFhashPrint();
	printf("Doubled Successfully\n");


}




PFhashDelete(fd,page)
int fd;		/* file descriptor */
int page;	/* page number */
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
	/* See if the entry is in this bucket */
	//for (entry=PFhashtbl[bucket]; entry != NULL; entry = entry->nextentry)
	if (entry->fd == fd && entry->page == page)
	{
		entry->fd=-1;
		entry->page=-1;
		entry->bpage=-1;
	}

	if (entry->fd2 == fd && entry->page2 == page)
	{
		entry->fd2=-1;
		entry->page2=-1;
		entry->bpage2=-1;
	}

	if (entry->fd3 == fd && entry->page3 == page)
	{
		entry->fd3=-1;
		entry->page3=-1;
		entry->bpage3=-1;
	}


	if (entry == NULL){
		/* not found */
		PFerrno = PFE_HASHNOTFOUND;
		return(PFerrno);
	}

	/* get rid of this entry */
	/*if (entry == PFhashtbl[bucket])
		PFhashtbl[bucket] = entry->nextentry;
	if (entry->preventry != NULL)
		entry->preventry->nextentry = entry->nextentry;
	if (entry->nextentry != NULL)
		entry->nextentry->preventry = entry->preventry;
	free((char *)entry);*/

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
int i;
PFhash_entry *entry;

	printf("%d\n",PF_HASH_TBL_SIZE );
	for (i=0; i < PF_HASH_TBL_SIZE; i++)
	{

		printf("bucket %d\n",i);
		if (PFhashtbl[i] == NULL)
			printf("\tempty\n");
		else
		{
			/*for (entry = PFhashtbl[i]; entry != NULL;
					entry = entry->nextentry)
				printf("\tfd: %d, page: %d %d\n",
					entry->fd, entry->page,entry->bpage);*/
			entry = PFhashtbl[i];
			if(entry != NULL)
			{


			if((entry->localDepth)==globalDepth)
			{
				if(entry->fd==-1)
					printf("\tNULL\n");
				else
				printf("\tfd: %d, page: %d buffer: %d\n",entry->fd, entry->page,entry->bpage );
				



				if(entry->fd2==-1)
					printf("\tNULL\n");
				else
				printf("\tfd: %d, page: %d buffer: %d\n",entry->fd2, entry->page2,entry->bpage2 );



				if(entry->fd3==-1)
					printf("\tNULL\n");
				else
				printf("\tfd: %d, page: %d buffer: %d\n",entry->fd3, entry->page3,entry->bpage3 );
			}
			else
			{


				if(entry->fd==-1)
					printf("\tNULL\n");
				else
				printf("\tfd: %d, page: %d buffer: %d\n",entry->fd, entry->page,entry->bpage );
				



				if(entry->fd2==-1)
					printf("\tNULL\n");
				else
				printf("\tfd: %d, page: %d buffer: %d\n",entry->fd2, entry->page2,entry->bpage2 );



				if(entry->fd3==-1)
					printf("\tNULL\n");
				else
				printf("\tfd: %d, page: %d buffer: %d\n",entry->fd3, entry->page3,entry->bpage3 );

				if(i!=(i%(1<<entry->localDepth)))
				printf("\tThis bucket Pointer is Redirecting to->bucket %d\n",(i%(1<<entry->localDepth)));


			}


		}

		}
	}
}
