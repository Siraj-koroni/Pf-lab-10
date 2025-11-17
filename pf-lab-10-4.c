#include <stdio.h>
#include <string.h>

#define maxAffrim 7
#define affrimLen 200

int loadFromFile(char affrim[maxAffrim][affrimLen])
{
   FILE *fp;
   fp = fopen("affirm.txt", "r");
   int count = 0;
   if (!fp)
   {
      return 0;
   }
   while (fgets(affrim[count], affrimLen, fp))
   {
      affrim[count][strcspn(affrim[count], "\n")] = '\0';
      count++;

      if (count >= maxAffrim)
         break;
   }
   fclose(fp);
   return count;
}

void saveToFile(char affrim[][affrimLen], int count)
{
    FILE *fp;
    fp = fopen("affirm.txt", "w");
    for (int i = 0; i < count; i++)
    {
        fprintf(fp, "%s\n", affrim[i]);
    }
    fclose(fp);
}

int main()
{
   char affrim[maxAffrim][affrimLen];
   int count = loadFromFile(affrim);

   while (1)
   {
      printf("\n\n======* AFFIRMATION MENU *======\n");
      printf("1. Add Affirmation \n");
      printf("2. Modify Affirmation\n");
      printf("3. search Affirmation\n");
      printf("4. Delete affirmation\n");
      printf("\nEnter -1 to Exit\n");
      printf("\nEnter your choice: ");

      char choice[10];
      fgets(choice, 10, stdin);

      if (strcmp(choice, "-1\n") == 0)
      {
        printf("\nSaving changes...\n");
            saveToFile(affrim,count);
            printf("All updates saved. Exiting...\n");
            break;
      }
      if (choice[0] == '1')
      {
         if (count >= maxAffrim)
         {
            printf("\nAffirmation is full no more spaces");
            continue;
         }
         else
         {
            printf("\nEnter affrimation (not more than 7 words )");
            fgets(affrim[count], affrimLen, stdin);
            affrim[count][strcspn(affrim[count], "\n")] = '\0';
            count++;
            printf("\nAffirmation added successfully.");
         }
      }
      else if (choice[0] == '2')
      {

         char oldRAffirm[affrimLen];
         printf("\nEnter affrim name to modify: \n");
         fgets(oldRAffirm, affrimLen, stdin);
         oldRAffirm[strcspn(oldRAffirm, "\n")] = '\0';

         int found = -1;

         for (int i = 0; i < count; i++)
         {
            if (strcmp(affrim[i], oldRAffirm) == 0)
            {
               found = i;
               break;
            }
         }
         if (found == -1)
         {
            printf("\nAffirmation is not found.");
         }
         else
         {
            char newAffirm[affrimLen];
            printf("\nEnter new affrim to modify: ");
            fgets(newAffirm, affrimLen, stdin);
            newAffirm[strcspn(newAffirm, "\n")] == '\0';
            printf("\nAffrimation modified successfully.");
         }
      }
      else if (choice[0] == '3')
      {
         char serachAffrim[maxAffrim];
         printf("\n Enter the affrim name to search: ");
         fgets(serachAffrim, maxAffrim, stdin);
         serachAffrim[strcspn(serachAffrim, "\n")] = '\0';
         if (strlen(serachAffrim) == 0)
         {
            printf("\nSearch term cannot be empty.\n");
            continue;
         }
         int found = 0;
         for (int i = 0; i < count; i++)
         {
            if (strstr(affrim[i], serachAffrim))
            {
               found = 1;
               printf("\nAffirm Found: %s", affrim[i]);
            }
         }
         if (!found)
         {
            printf("\nNo affirmation found.");
         }
      }
      else if (choice[0] == '4')
      {
         char delAffrim[maxAffrim];
         printf("\nEnter affirm to delete: ");
         fgets(delAffrim, maxAffrim, stdin);
         delAffrim[strcspn(delAffrim, "\n")] = '\0';
         int found = -1;
         for (int i = 0; i < count; i++)
         {
            if (strcmp(affrim[i], delAffrim) == 0)
            {
               found = i;
               break;
            }
         }
         if (found == -1)
         {
            printf("\nAffrim not found.");
            continue;
         }
         else
         {
            for (int i = found; i < count; i++)
            {
               strcpy(affrim[i], affrim[i + 1]);
            }
            count--;
            printf("\nAffrim deleted successfully.");
         }
      }
      else
      {
         printf("\nInvalid choice......Please enter correct choice.");
      }
   }
   return 0;
}
