#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define maxTag 7
#define maxTagLen 200

int countWords(char *str) {
    int count = 0, inWord = 0;
    while (*str) {
        if (!isspace(*str) && inWord == 0) {
            inWord = 1;
            count++;
        }
        else if (isspace(*str)) {
            inWord = 0;
        }
        str++;
    }
    return count;
}
int loadFromFile(char tag[maxTag][maxTagLen])
{
   FILE *fp;
   fp = fopen("tag.txt", "r");
   int count = 0;
   if (!fp)
   {
      return 0;
   }
   while (fgets(tag[count], maxTagLen, fp))
   {
      tag[count][strcspn(tag[count], "\n")] = '\0';
      count++;

      if (count >= maxTag)
         break;
   }
   fclose(fp);
   return count;
}

void saveToFile(char tag[][maxTagLen], int count)
{
    FILE *fp;
    fp = fopen("tag.txt", "w");
    for (int i = 0; i < count; i++)
    {
        fprintf(fp, "%s\n", tag[i]);
    }
    fclose(fp);
}

void addTag(char tag[maxTag][maxTagLen],int *count);
void modifyTag(char tag[maxTag][maxTagLen],int count);
void searchTag(char tag[maxTag][maxTagLen],int count);
void deleteTag(char tag[maxTag][maxTagLen],int *count);
int main()
{
   char tag[maxTag][maxTagLen];
   int count = loadFromFile(tag);

   while (1)
   {
      printf("\n\n======* TAG MENU *======\n");
      printf("1. Add Tags \n");
      printf("2. Modify tags\n");
      printf("3. search tags\n");
      printf("4. Delete tags\n");
      printf("5. Display all tags\n");
      printf("\nEnter -1 to Exit\n");
      printf("\nEnter your choice: ");

      char choice[10];
      fgets(choice, 10, stdin);

      if (strcmp(choice, "-1\n") == 0)
      {
        printf("\nSaving changes...\n");
            saveToFile(tag,count);
            printf("All updates saved. Exiting...\n");
            break;
      }
      if (choice[0] == '1')
      {
         addTag(tag,&count);
      }
      else if (choice[0] == '2')
      {

         modifyTag(tag,count);
      }
      else if (choice[0] == '3')
      {
         searchTag(tag,count);
      }
      else if (choice[0] == '4')
      {
        deleteTag(tag,&count);
      }
      else if( choice[0]=='5'){
        for (int i = 0; i < count; i++)
        {
            printf("%d. %s\n",i+1,tag[i]);
        }
        
      }
      else
      {
         printf("\nInvalid choice......Please enter correct choice.");
      }
   }
   return 0;
}



 void addTag(char tag[maxTag][maxTagLen],int *count){
         if (*count >= maxTag) {
         printf("\nStorage full. No space available\n");
         return;
        }
         char newTag[maxTagLen];
            printf("\nEnter new tag (5 to 7 words only): ");
            fgets(newTag, maxTagLen, stdin);
            newTag[strcspn(newTag, "\n")] = '\0';

         int words = countWords(newTag);
            if (words<5||words > 7) {
                printf("\n Tag must be upto 7 words.\n");
                return;
            }
         
            strcpy(tag[*count], newTag);
            (*count)++;
        
            printf("\nTag added successfully.");
         
            
      }
    
     
void modifyTag(char tag[maxTag][maxTagLen],int count){
    char oldTag[maxTagLen];
         printf("\nEnter Tag name to modify: \n");
         fgets(oldTag, maxTagLen, stdin);
         oldTag[strcspn(oldTag, "\n")] = '\0';

         int found = -1;

         for (int i = 0; i < count; i++)
         {
            if (strcmp(tag[i], oldTag) == 0)
            {
               found = i;
               break;
            }
         }
         if (found == -1)
         {
            printf("\nTag is not found.");
            return;
         }
         
         
            char newTag[maxTagLen];
            printf("\nEnter new tag to modify: ");
            fgets(newTag, maxTagLen, stdin);
            newTag[strcspn(newTag, "\n")] = '\0';
            strcpy(tag[found], newTag);
            printf("\nTag modified successfully.");
         
}
void searchTag(char tag[maxTag][maxTagLen],int count){
    char serachTag[maxTagLen];
         printf("\n Enter the tag name to search: ");
         fgets(serachTag, maxTagLen, stdin);
         serachTag[strcspn(serachTag, "\n")] = '\0';
         if (strlen(serachTag) == 0)
         {
            printf("\nSearch term cannot be empty.\n");
            return;
         }
         int found = 0;
         for (int i = 0; i < count; i++)
         {
            if (strstr(tag[i], serachTag))
            {
               found = 1;
               printf("\nTag Found: %s", tag[i]);
            }
         }
         if (!found)
         {
            printf("\nNo Tag found.");
         }
}
void deleteTag(char tag[maxTag][maxTagLen],int *count){
    char delTag[maxTagLen];
         printf("\nEnter tag to delete: ");
         fgets(delTag, maxTagLen, stdin);
         delTag[strcspn(delTag, "\n")] = '\0';
         int found = -1;
         for (int i = 0; i < *count; i++)
         {
            if (strcmp(tag[i], delTag) == 0)
            {
               found = i;
               break;
            }
         }
         if (found == -1)
         {
            printf("\nTag not found.");
            return;
         }
         
         
            for (int i = found; i < *count-1; i++)
            {
               strcpy(tag[i], tag[i + 1]);
            }
            (*count)--;
            printf("\nTag deleted successfully.");
        
}