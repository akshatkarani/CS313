/* testhash.c: tests the hash table functions */
#include <stdio.h>
#include "am.h"
#include "pf.h"
#include "pftypes.h"
#include "testam.h"
#include <sys/time.h>

#define FILE1 "file1"

struct timeval stop, start;
int i,*buf1,filed1,count,fd1;
char fname[100];

void menu();
void indexing();
void insert();

static int fd;
static int filed;
static int errVal;
  //PF_Init();


main()
{
  int i,k,error,numrec,recnum;
  long j;
  long long int sd,testval;
  int pagenum1,*buf,pagenum;
  int pageno,errVal,count;




  PFhashInit();
  PF_Init();

  menu();



}             //end of main


void menu()
{
  int choice;
  printf("****COMPARISON MENU****\n");
  printf("Please enter a choice:-\n1.Creation of Index time\n2.Insertion time \n3.Exit\n");
  scanf("%d",&choice);
  switch(choice)
  {
  case 1:
    indexing();
    break;
  case 2:
    insert();
    break;
  case 3:
    exit(0);
  default:
    printf("Invalid Option. Try again.\n");
    menu();
  }

}

void indexing()
{
  int error,pagenum1,time1,time2,size1,size2,pagenum;
  int * buf;
  char * a;

  PFhashInit();
  PF_Init();



  if ((filed1=PF_OpenFile("file1"))<0)
          {
            PF_PrintError("Open file\n");
            exit(1);
          }

       printf("%d",filed1);


        sprintf(fname,"%s.0","file1");
        //filed = PF_OpenFile(fname);

       gettimeofday(&start, NULL);
 pagenum1=-1;
  while ((error=PF_GetNextPage(filed1,&pagenum1,&buf1))== PFE_OK)
              {
                //printf("2\n");
    printf("got page %d, %d\n",pagenum1,buf1);
                if ((error=PF_UnfixPage(filed1,pagenum1,TRUE))!= PFE_OK)
                    {
                PF_PrintError("unfix file1");
      exit(1);
                     }
                 AM_InsertEntry(filed,INT_TYPE,sizeof(int),(char *)buf1,IntToRecId(pagenum1));
              }
      //errVal = AM_CreateIndex("file1", 1, 'i', 4);


      gettimeofday(&stop, NULL);
      time1=stop.tv_usec - start.tv_usec;
       size1=sizeof(PFhash_entry)*PF_HASH_TBL_SIZE+sizeof(pagenum1)+sizeof(buf1)+sizeof(filed1);
      PF_CloseFile(filed1);

        if ((fd=PF_OpenFile("file1"))<0)
        {
          PF_PrintError("open file1");
          exit(1);
        }




      gettimeofday(&start, NULL);


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
      gettimeofday(&stop, NULL);
      time2=stop.tv_usec - start.tv_usec;
      size2=sizeof(pagenum)+sizeof(buf)+sizeof(fname)+sizeof(fd);
      printf("Time Taken by AM layer in microsecond :%d\n",time1);
      printf("Time Taken by Hashing in microsecond :%d\n",time2);
        printf("Size used by AM layer in bytes :%d\n",size1);
      printf("Size used by Hashing in bytes :%d\n",size2);
      if (time1 < time2)
        printf("AM layer is better\n");
      else
        printf("Hashing is better\n");

  //printf("eof reached\n");


  menu();


}

void insert()
{

    struct timeval stop, start;
    int fd2, pageno,buff,time1,time2,error;
    int *buf1;
    int size1,size2;
    char fname[300];

   sprintf(fname,"%s.0","file1");
        //filed = PF_OpenFile(fname);

    gettimeofday(&start, NULL);

      pageno=1;
     // *((int *)buf1) =pageno;
    /*
     if(error=PF_AllocPage(fd,&pageno,&buf1)!=PFE_OK)
    {

         PF_PrintError("first buffer\n");
         exit(1);
    }

    *((int *)buf1) =pageno;
    //printf("allocated page %d\n",pageno);

    if ((error=PF_UnfixPage(fd,pageno,TRUE))!= PFE_OK)
        {
         PF_PrintError("unfix file1");
       exit(1);
        }*/
    //printf("%d\n",buf1);
      /*if ((error=PF_UnfixPage(fd,pageno,TRUE))!= PFE_OK)
                    {
                PF_PrintError("unfix file1");
      exit(1);
                     }*/
if((fd1=PF_OpenFile("file2"))<0)
  {
    PF_PrintError("Open file\n");
    exit(1);
  }


  for(i=0;i<=1000;i++)
  {
    if(error=PF_AllocPage(fd1,&pageno,&buf1)!=PFE_OK)
    {

         PF_PrintError("first buffer\n");
         exit(1);
    }
    *((int *)buf1) = i;
    printf("allocated page %d\n",pageno);
    if ((error=PF_UnfixPage(fd1,pageno,TRUE))!= PFE_OK)
        {
  PF_PrintError("unfix file1");
      exit(1);
        }
    printf("%d\n",buf1);
  }
   gettimeofday(&stop, NULL);

      time1=stop.tv_usec - start.tv_usec;
      size1=sizeof(pageno)+sizeof(buf1)+sizeof(fd1)+(1000*2);

      // printf("Starting of the program...\n");
    gettimeofday(&start, NULL);

   for (pageno=1041;pageno<=2041;pageno++)
   {
     /* if(error=PF_AllocPage(filed1,&pageno,&buf1)!=PFE_OK)
       {

         PF_PrintError("first buffer\n");
         exit(1);
       }

       *((int *)buf1) =pageno;*/
      if (PFhashInsert(fd,pageno,buf1) != PFE_OK)
       {
        printf("PFhashInsert failed\n");
       }
   }

  gettimeofday(&stop, NULL);

     size2=sizeof(PFhash_entry)*PF_HASH_TBL_SIZE+sizeof(pageno)+sizeof(buff)+sizeof(fd);
     time2=stop.tv_usec - start.tv_usec;
      printf("Time Taken by AM layer in microsecond :%d\n",time1);
      printf("Time Taken by Hashing in microsecond :%d\n",time2);
      printf("Size used by AM layer in bytes :%d\n",size1);
      printf("Size used by Hashing in bytes :%d\n",size2);
menu();

}



