#include<stdio.h>
#include<string.h>
#include<ctype.h>

#define maxPodTitil 10
#define maxPodTitleLen 200


void addNotes(char podtitle[maxPodTitil][maxPodTitleLen],int *count);
void searchNotes(char podtitle[maxPodTitil][maxPodTitleLen],int count);
void modifyNotes(char podtitle[maxPodTitil][maxPodTitleLen],int count);
void deleteNotes(char podtitle[maxPodTitil][maxPodTitleLen],int *count);
void totalWords(char podtile[maxPodTitil][maxPodTitleLen], int count);


int wordCount(char *s){
 int count=0, inWord=0;
 while (*s)
 {
   if (isspace(*s)&&inWord==0)
   {
    count++;
    inWord=1;
   }
   else if(isspace(*s)){
    inWord=0;
   }
   s++;
   
 }
 return count;
}

int loadFromFile(char podTitle[maxPodTitil][maxPodTitleLen]){
 FILE *fp;
 fp=fopen("episodes.txt","r");
 int count=0;
 if (!fp)
 {
    printf("\nFile is empty");
    return 0;
 }
 while (fgets(podTitle[count],maxPodTitleLen,fp))
 {
   podTitle[count][strcspn(podTitle[count],"\n")]='\0';
   count++;
   if (count>=maxPodTitil)
   {
    break;
   }
  }
  fclose(fp);
  return count;
 }
 void saveToFile(char podTitle[maxPodTitil][maxPodTitleLen],int count){
   FILE*fp;
   fp=fopen("episodes.txt","w");
   for (int i = 0; i < count; i++)
   {
     fprintf(fp,"%s\n",podTitle[i]);
   }
   fclose(fp);
}
 
int main()
{
   char  podTitle[maxPodTitil][maxPodTitleLen];
   int count=0;
   count=loadFromFile(podTitle);
   while (1)
   {
     printf("\n\n======* PODCAST RECORDING NOTE MENU *======\n");
      printf("1. Add notes \n");
      printf("2. search notes\n");
      printf("3. Modify notes\n");
      printf("4. Delete notes\n");
      printf("5. Count Words in All Notes\n");
      printf("6. Display all notes\n");
      printf("\nEnter -1 to Exit\n");
      printf("\nEnter your choice: ");

      char choice[10];
      fgets(choice, 10, stdin);
      if (strcmp(choice, "-1\n") == 0)
      {
        printf("\nSaving changes...\n");
            saveToFile(podTitle,count);
            printf("All updates saved. Exiting...\n");
            break;
      }
      switch (choice[0])
      {
      case '1':
        addNotes(podTitle,&count);
        break;
        case '2':
        searchNotes(podTitle,count);
        break;
         case '3':
        modifyNotes(podTitle,count);
        break;
        case '4':
        deleteNotes(podTitle,&count);
        break;
        case'5':
         totalWords(podTitle,count);
         break;
        case '6':
        printf("\nAll notes:\n ");
         for (int i = 0; i < count; i++)
         {
           printf("%d. %s\n",i+1,podTitle[i]);
         }
         break;
         
      default:
      printf("\nInvalid choice ....");
        break;
      }
   }
   

    return 0;
}
void addNotes(char podtitle[maxPodTitil][maxPodTitleLen],int *count){
  if (*count>=maxPodTitil)
  {
    printf("\nStorage is full.Cannot add more notes");
    return;
  }
  char newNotes[maxPodTitil];
  printf("\nEnter new notes to add: ");
  fgets(newNotes,maxPodTitleLen,stdin);
  newNotes[strcspn(newNotes,"\n")]='\0';
   strcpy(podtitle[*count],newNotes);
   (*count)++;
   printf("\nNotes added successfu=lly.");
   
  
}
void searchNotes(char podtitle[maxPodTitil][maxPodTitleLen],int count){
  char oldNotes[maxPodTitil];
  printf("\nEnter the notes to search: ");
  fgets(oldNotes,maxPodTitleLen,stdin);
  oldNotes[strcspn(oldNotes,"\n")]='\0';
  if (strlen(oldNotes)==0)
  {
    printf("\nSearch term cannot be emtpy");
    return;
  }
 int found=0;
 for (int i = 0; i < count; i++)
 {
   if (strcmp(podtitle[i],oldNotes))
   {
     printf("\nNotes found: %s",podtitle[i]);
     found=1;
   }
   
 }
 if (!found)
 {
   printf("\nNotes are not found.");
 }
 
}
void modifyNotes(char podtitle[maxPodTitil][maxPodTitleLen],int count){
 char oldNotes[maxPodTitil];
 printf("\nEnter notes to modify: ");
 fgets(oldNotes,maxPodTitleLen,stdin);
 oldNotes[strcspn(oldNotes,"\n")]='\0';
  int found=-1;
  for (int i = 0; i < count; i++)
  {
    if(strcmp(podtitle[i],oldNotes)){
      found=i;
      break;
    }
  }
  if(found==-1){
    printf("\nNotes not found.");
    return;
  }
  char newNotes[maxPodTitil];
  printf("\nEnter new notes to modify: ");
  fgets(newNotes,maxPodTitleLen,stdin);
  newNotes[strcspn(newNotes,"\n")]='\0';
  strcpy(podtitle[found],newNotes);
  printf("\nNotes modified sucessfully.");
}

void deleteNotes(char podtitle[maxPodTitil][maxPodTitleLen],int *count){
   char oldNotes[maxPodTitil];
  printf("\nEnter notes to delete: ");
 fgets(oldNotes,maxPodTitleLen,stdin);
 oldNotes[strcspn(oldNotes,"\n")]='\0';
  int found=-1;
  for (int i = 0; i < *count; i++)
  {
    if(strcmp(podtitle[i],oldNotes)){
      found=i;
      break;
    }
  }
  if(found==-1){
    printf("\nNotes not found.");
    return;
  }
  for (int i = found; i < *count-1; i++)
  {
     strcpy(podtitle[i],podtitle[i+1]);
  }
  (*count)--;
  printf("\nNotes deleted successfully.");
}
void totalWords(char podtitle[maxPodTitil][maxPodTitleLen], int count){
 int total=0;
 for (int i = 0; i < count; i++)
 {
   total+=wordCount(podtitle[i]);
 }
 printf("\nTotal number of words in notes: %d\n",total);
}
