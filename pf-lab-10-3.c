#include <stdio.h>
#include <string.h>

#define maxRecipes 40
#define maxRecipeLen 220
void sortRecipe(char recipe[][maxRecipeLen], int count)
{
    char temp[maxRecipeLen];
    for (int i = 0; i < count - 1; i++)
    {
        for (int j = i + 1; j < count; j++)
        {
            if (strcmp(recipe[i], recipe[j]) > 0)
            {
                strcpy(temp, recipe[i]);
                strcpy(recipe[i], recipe[j]);
                strcpy(recipe[j], temp);
            }
        }
    }
}
int loadFromFile(char recipe[][maxRecipeLen])
{
    FILE *fp;
    fp = fopen("recipes.txt", "r");
    int count = 0;
    if (!fp)
    {
        return 0;
    }
    while (fgets(recipe[count], maxRecipeLen, fp))
    {
        recipe[count][strcspn(recipe[count], "\n")] = '\0';
        count++;

        if (count >= maxRecipes)
            break;
    }
    fclose(fp);
    return count;
}
void saveToFile(char recipe[][maxRecipeLen], int count)
{
    FILE *fp;
    fp = fopen("recipes.txt", "w");
    for (int i = 0; i < count; i++)
    {
        fprintf(fp, "%s\n", recipe[i]);
    }
    fclose(fp);
}

int main()
{
    char recipe[maxRecipes][maxRecipeLen];
    int count = loadFromFile(recipe);

    while (1)
    {
        printf("\n\n====== RECIPES MENU ======\n");
        printf("1. Add Recipe\n");
        printf("2. Modify Recipe\n");
        printf("3. search Recipe\n");
        printf("4. Delete Recipe\n");
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
            if (count >= maxRecipes)
            {
                printf("\nRecipe List is full! No more spaces");
                continue;
            }
            printf("\nEnter new Recipe Name: ");
            fgets(recipe[count], maxRecipeLen, stdin);
            recipe[count][strcspn(recipe[count], "\n")] = '\0';
            count++;
            printf("\nRecipe added successfully.");
        }
        else if (choice[0] == '2')
        {
            char oldRecipe[maxRecipeLen];
            printf("\nEnter recipe name to modify: \n");
            fgets(oldRecipe, maxRecipeLen, stdin);
            oldRecipe[strcspn(oldRecipe, "\n")] = '\0';

            int found = -1;

            for (int i = 0; i < count; i++)
            {
                if (strcmp(recipe[i], oldRecipe) == 0)
                {
                    found = i;
                    break;
                }
            }
            if (found == -1)
            {
                printf("Recipe not found \n");
            }
            else
            {
                printf("Enter new Recipe to modify: ");
                fgets(recipe[found], maxRecipeLen, stdin);
                recipe[found][strcspn(recipe[found], "\n")] = '\0';
                printf("\nRecipe modified sucessfully.\n");
            }
        }
        else if (choice[0] == '3')
        {
            char title[maxRecipeLen];
            printf("\n Enter the recipe name to search: ");
            fgets(title, maxRecipeLen, stdin);
            title[strcspn(title, "\n")] = '\0';

            if (strlen(title) == 0)
            {
                printf("\nSearch term cannot be empty.\n");
                continue;
            }

            int found = 0;
            for (int i = 0; i < count; i++)
            {
                if (strstr(recipe[i], title))
                {
                    found = 1;
                    printf("\nRecipe Found: %s", recipe[i]);
                }
            }
            if (!found)
            {
                printf("\nNo recipe matached\n");
            }
        }
        else if (choice[0] == '4')
        {
            char title[maxRecipeLen];
            printf("\nEnter recipe name to delete:\n");

            if (fgets(title, maxRecipeLen, stdin) == NULL)
                continue;
            title[strcspn(title, "\n")] = '\0';

            int found = -1;

            for (int i = 0; i < count; i++)
            {
                if (strcmp(recipe[i], title) == 0)
                {
                    found = i;
                    break;
                }
            }

            if (found == -1)
            {
                printf("Recipe not found to delete\n");
            }
            else
            {
                for (int i = found; i < count - 1; i++)
                {
                    strcpy(recipe[i], recipe[i + 1]);
                }
                count--;
                printf("Recipe deleted sucessfully.\n");
            }
        }
        else
        {
            printf("\nInvalid choice....Try again\n");
        }
        sortRecipe(recipe, count);
        printf("\n-------RECIPE APLHABATICAL ORDER---------\n");
        for (int i = 0; i < count; i++)
        {
            printf("%d. %s", i + 1, recipe[i]);
        }

        saveToFile(recipe, count);
        printf("\nFile saved successfully.");
    }
    return 0;
}