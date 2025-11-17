#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define maxSong 10
#define songTitleLen 220

void sortSong(char songs[][songTitleLen], int count)
{
    char temp[songTitleLen];
    for (int i = 0; i < count - 1; i++)
    {
        for (int j = i + 1; j < count; j++)
        {
            if (strcmp(songs[i], songs[j]) > 0)
            {
                strcpy(temp, songs[i]);
                strcpy(songs[i], songs[j]);
                strcpy(songs[j], temp);
            }
        }
    }
}
void saveToFile(char songs[][songTitleLen], int count)
{
    FILE *fp;
    fp = fopen("Playlist.txt", "w");
    for (int i = 0; i < count; i++)
    {
        fprintf(fp, "%s\n", songs[i]);
    }
    fclose(fp);
}
int loadFromFile(char songs[][songTitleLen])
{
    FILE *fp;
    fp = fopen("Playlist.txt", "r");
    int count = 0;
    if (!fp)
    {
        return 0;
    }
    while (fgets(songs[count], songTitleLen, fp))
    {
        songs[count][strcspn(songs[count], "\n")] = '\0';
        count++;

        if (count >= maxSong)
            break;
    }
    fclose(fp);
    return count;
}

int main()
{
    char songs[maxSong][songTitleLen];
    int count = loadFromFile(songs);
   

    while (1)
    {
        printf("\n\n==== MUSIC PLAYLIST MENU ====\n");
        printf("1. Add Song\n");
        printf("2. Delete Song\n");
        printf("3. Update Song\n");
        printf("4. Search Song\n");
        printf("\nEnter -1 to Exit\n");
        printf("Enter your choice: ");

        char choice[10];
        fgets(choice, 10, stdin);

        if (strcmp(choice, "-1\n") == 0)
        {
            break;
        }
        if (choice[0] == '1')
        {
            if (count >= maxSong)
            {
                printf("\nPlaylist is full no more spaces");
                continue;
            }
            printf("\nEnter song title (5 to 7 words)");
            fgets(songs[count], songTitleLen, stdin);
            songs[count][strcspn(songs[count], "\n")] = '\0';
            count++;
            printf("\nSong added successfully.");
        }
        else if (choice[0] == '2')
        {
            char title[songTitleLen];
            printf("\nEnter song title to delete\n");
            fgets(title, songTitleLen, stdin);
            title[strcspn(title, "\n")] = '\0';

            int found = -1;

            for (int i = 0; i < count; i++)
            {
                if (strcmp(songs[i], title) == 0)
                {
                    found = i;
                    break;
                }
            }

                if (found == -1)
                {
                    printf("Song not found. please try again\n");
                }
                else
                {
                    for (int i = found; i < count - 1; i++)
                    {
                        strcpy(songs[i], songs[i + 1]);
                    }
                    count--;
                    printf("Songs deleted sucessfully.\n");
                }
            }
        
          else if(choice[0] == '3')
          {
            char updateTitle[songTitleLen];
            printf("\nEnter song title to update\n");
            fgets(updateTitle, songTitleLen, stdin);
            updateTitle[strcspn(updateTitle, "\n")] = '\0';

            int found = -1;

            for (int i = 0; i < count; i++)
            {
                if (strcmp(songs[i], updateTitle) == 0)
                {
                    found = i;
                    break;
                }
            }
                if (found == -1)
                {
                    printf("Song not found. please try again\n");
                }
                else
                {
                    printf("Enter new song title to update: ");
                    fgets(songs[found], songTitleLen, stdin);
                    songs[found][strcspn(songs[found], "\n")] = '\0';
                    printf("Songs updated sucessfully.\n");
                }
            }
        
          else if (choice[0] == '4')
          {
            char title[songTitleLen];
            printf("\nEnter song title to search:");
            fgets(title, songTitleLen, stdin);
            title[strcspn(title, "\n")] = '\0';

            int found = 0;
            for (int i = 0; i < count; i++)
            {
                if (strstr(songs[i], title))
                {
                    found = 1;
                    printf("\nfound: %s", songs[i]);
                }
            }
            if (!found)
            {
                printf("\nNo song matached\n");
            }
        }
        else{
            printf("\nInvalid choice....Try again\n");
        }
        sortSong(songs, count);
        printf("\n------------PLAYLIST---------------\n");
        for (int i = 0; i < count; i++)
        {
            printf("%d. %s\n", i + 1, songs[i]);
        }
        saveToFile(songs, count);
        printf("\nPlaylist saved sucessfully.");
    }
    printf("\nGood bye! End of program");
}
