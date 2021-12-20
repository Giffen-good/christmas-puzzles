#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct {
  int *array;
  size_t used;
  size_t size;
} Array;


void initPointerArray(Array *a, size_t initialSize) {
  a->array = malloc(initialSize * 8);
  a->used = 0;
  a->size = initialSize;
}

void insertPointerArray(Array *a, Array* element) {
   // a->used is the number of used entries, because a->array[a->used++] updates a->used only *after* the array has been accessed.
  // Therefore a->used can go up to a->size 
  if (a->used == a->size) {
    a->size *= 2;
    a->array = realloc(a->array, a->size * 8);
  }
  a->array[a->used++] = element;
}


void initArray(Array *a, size_t initialSize) {
  a->array = malloc(initialSize * sizeof(int));
  a->used = 0;
  a->size = initialSize;
}

void insertArray(Array *a, int element) {
  // a->used is the number of used entries, because a->array[a->used++] updates a->used only *after* the array has been accessed.
  // Therefore a->used can go up to a->size 
  if (a->used == a->size) {
    a->size *= 2;
    a->array = realloc(a->array, a->size * sizeof(int));
  }
  a->array[a->used++] = element;
}


void insert(Array *a, int element) {
  // a->used is the number of used entries, because a->array[a->used++] updates a->used only *after* the array has been accessed.
  // Therefore a->used can go up to a->size 
  if (a->used == a->size) {
    a->size *= 2;
    a->array = realloc(a->array, a->size * sizeof(int));
  }
  a->array[a->used++] = element;
}

void freeArray(Array *a) {
  free(a->array);
  a->array = NULL;
  a->used = a->size = 0;
}

Array dayElapsed(Array *fishes)
{
    int *f = fishes->array;
    Array newFish;
    initArray(&newFish,100);
    for (int i = 1; i < fishes->used;i++)
    {
        if (f[i] == -1)
        {
            f[i] = 6;
            insertArray(&newFish, 8);
        } else {
            f[i] -= 1;
        }
    }
    return newFish;

}
void runSimulation(Array *fishes, int NumberOfDays)
{
    Array schools_of_fish;
    initPointerArray(&schools_of_fish, 40);
    for (int i = 0; i < NumberOfDays; i++)
    {
        Array* newFish = dayElapsed(fishes);
        insertPointerArray(&schools_of_fish, newFish);
    }
    int finalCountOfFish = fishes->used;
    int *f = fishes->array;
    // for (int i = 1; i < fishes->used;i++)
    // {
    //    printf("%i\n", f[i]);
    // }
    printf("Number of fish by day %i: %i\n", NumberOfDays, finalCountOfFish - 1);
}

void getFishDataFromFile(Array *fishes, FILE *file) 
{
    char ch;
    while(ch != EOF)
    {
        // int v = ch - '0';
        if ( ch != ',')
        {
            int v = ch - '0';
            insertArray(fishes, v);
        }

        ch = getc(file);
    } 
    
    fclose(file);
}
int main(int argc, char* argv[])
{
    char const* const fileName = argv[1]; /* should check that argc > 1 */
    FILE* file = fopen(fileName, "r"); /* should check the result */
    Array fishes;
    initArray(&fishes, 301);

    getFishDataFromFile(&fishes, file);
    runSimulation(&fishes, 80);

    return 0;
}