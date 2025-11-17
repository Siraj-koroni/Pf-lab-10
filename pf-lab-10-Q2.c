#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

#define maxWord 7
#define maxDescpn 100
#define levelLen 220

int wordCount(const char *s) {
    int count = 0;
    int in_word = 0; 

    for (int i = 0; s[i] != '\0'; i++) {
        if (isspace((unsigned char)s[i]) || s[i] == '\n' || s[i] == '\r') {
            in_word = 0;
        } else if (in_word == 0) {
            in_word = 1;
            count++;
        }
    }
    return count;
}
void saveToFile(char levels[][levelLen], int count)
{
    FILE *fp;
    fp = fopen("levels.txt", "r");
    for (int i = 0; i < count; i++)
    {
        fprintf(fp, "%s\n", levels[i]);
    }
    fclose(fp);
}

int loadFromFile(char levels[][levelLen])
{
    FILE *fp;
    fp = fopen("levels.txt", "r");
    int count = 0;
    if (!fp)
    {
        return 0;
    }
    while (fgets(levels[count], levelLen, fp))
    {
        levels[count][strcspn(levels[count], "\n")] = '\0';
        count++;

        if (count >= maxDescpn)
            break;
    }
    fclose(fp);
    return count;
}

int main(){
    char levels[maxDescpn][levelLen];
     int count = loadFromFile(levels);
     printf("Loaded %d level(s):\n",count);
      if (count > 0) {
        printf("\n--- Current Levels ---\n");
        for (int i = 0; i < count; i++) {
            printf("%d. %s\n", i + 1, levels[i]);
        }
    }

      while (1)
    {
        printf("\n\n==== LEVEL MENU ====\n");
        printf("1. Add level\n");
        printf("2. Update level\n");
        printf("3. Search level\n");
        printf("4. Delete level\n");
        printf("\nEnter -1 to Exit\n");
        printf("\nEnter your choice: ");

        char choice[10];
        fgets(choice, 10, stdin);

        if (strcmp(choice, "-1\n") == 0)
        {
            break;
        }
        if (choice[0] == '1')
        {
            if (count >= maxDescpn)
            {
                printf("\nLevel is full. No more level is available ");
                continue;
            }
            printf("\nEnter exact level description  (Not more than 7 words): ");
            fgets(levels[count], levelLen, stdin);
            levels[count][strcspn(levels[count], "\n")] = '\0';
            count++;
            printf("\nLevel added successfully.");
        }
         else if(choice[0] == '2')
          {
            char updateLevel[levelLen];
            printf("\nEnter the exact level description to update\n");
            fgets(updateLevel, levelLen, stdin);
            updateLevel[strcspn(updateLevel, "\n")] = '\0';

            int found = -1;

            for (int i = 0; i < count; i++)
            {
                if (strcmp(levels[i], updateLevel) == 0)
                {
                    found = i;
                    break;
                }
            }
                if (found == -1)
                {
                    printf("Level not found. please try again\n");
                }
                else
                {
                    printf("Enter new Level  to update: ");
                    fgets(levels[found], levelLen, stdin);
                    levels[found][strcspn(levels[found], "\n")] = '\0';
                    printf("\nLevel updated sucessfully.\n");
                }
            }
            else if (choice[0] == '3')
          {
            char title[levelLen];
            printf("\nEnter exact level description to search:");
            fgets(title, levelLen, stdin);
            title[strcspn(title, "\n")] = '\0';

            
            if (strlen(title) == 0) {
                printf("\nSearch term cannot be empty.\n");
                continue;
            }

            int found = 0;
            for (int i = 0; i < count; i++)
            {
                if (strstr(levels[i], title))
                {
                    found = 1;
                    printf("\nfound: %s", levels[i]);
                }
            }
            if (!found)
            {
                printf("\nNo level matached\n");
            }
        }
        else if (choice[0] == '4')
        {
            char title[levelLen];
            printf("\nEnter the EXACT level description to delete:\n");
            
             if (fgets(title, levelLen, stdin) == NULL) continue;
            title[strcspn(title, "\n")] = '\0';

            int found = -1;

            for (int i = 0; i < count; i++)
            {
                if (strcmp(levels[i], title) == 0)
                {
                    found = i;
                    break;
                }
            }

                if (found == -1)
                {
                    printf("level not found. please try again\n");
                }
                else
                {
                    for (int i = found; i < count - 1; i++)
                    {
                        strcpy(levels[i], levels[i + 1]);
                    }
                    count--;
                    printf("level deleted sucessfully.\n");
                }
            }
            else{
                printf("\nInvalid choice....Try again\n");
            }
    
        
       
        saveToFile(levels,count);
        printf("\nLevel Description saved sucessfully.");
    }
    printf("\nGood bye! End of program");
}








