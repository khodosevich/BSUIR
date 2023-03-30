#include <stdio.h>
#include <string.h>  
#include <dirent.h>
#include <stdlib.h>

int compareStr(const void *s1, const void *s2)	// Функция для QSort, которая сравнивает строки
{
	int ifEqual = 0;
	
	if (strcmp((char*)s1,(char*)s2) == 1)
	{
		ifEqual = 1;
	}
	if (strcmp((char*)s1,(char*)s2) != 1)
	{
		ifEqual = 2;
	}
	
	return ifEqual;
}

int* getFlags(int argc, char** argv)	// Функция для получения массива флагов
{

	int* flags = (int*)calloc(4, sizeof(int));
	
    	for(int i = 2; i < argc; i++) 
    	{ 
		switch (argv[i][1]) 
		{
			case 'l':
				flags[0] = 1; 
				printf("\nflag - l\n");
				break;
			case 'd':
				flags[1] = 1; 
				printf("\nflag - d\n");
				break;
			case 'f':
				flags[2] = 1; 
				printf("\nflag - f\n");
				break;
			case 's':
				flags[3] = 1; 
				printf("\nflag - s\n");
				break;
			default:
				break;
		}
    	}	

	return flags;
}

char** getFileArr(const char* dirname, int flags[], int *numOfElems) {	// Функция для получения массива имён файлов, ссылок, директорий

    	char** files_arr = (char**)malloc(1*sizeof(char*));
    	DIR* dir;	//Поток директории
    	struct dirent* d;	// Структура для получения информации о директории

	dir = opendir(dirname); 

    	if(dir == NULL) 
    	{
		printf("Enter correctly second parameter (dir)\n");
		return NULL;
	}
        
    	while (d = readdir(dir)) 
    	{

            if (!strcmp(".", d->d_name) || !strcmp("..", d->d_name))
            {
                continue;
            }
		
		int addCond = 0;
		
		if (flags[0] && d->d_type == DT_LNK || flags[1] && d->d_type == DT_DIR || flags[2] && d->d_type == DT_REG)	// Условие добавления в общий массив элемента
		{
			addCond = 1;
		}

        	if(addCond)
        	{
            		files_arr = (char**)realloc(files_arr, sizeof(char*)*(*numOfElems + 1)); 
            		files_arr[*numOfElems] = (char*)malloc(sizeof(char)*NAME_MAX);	// NAME_MAX - макрос, равный максимальному размеру пути в окружении
            		memcpy(files_arr[*numOfElems], d->d_name, NAME_MAX);	// Запись в массив имени файла, ссылки, директории			
            		*numOfElems += 1;	// Увеличиваем количество элементов на 1
        	}  
    	}

    	closedir(dir);	// Закрываем поток директории

    	return files_arr; 
}

int main(int argc, char** argv) 
{

	int *flags = getFlags(argc, argv);
	int numOfElems = 0;
	
    char** files = getFileArr(argv[1], flags, &numOfElems);

	if(!numOfElems)	// Если количество найденых элементов равно 0
	{
		printf("No elements\n");
	}
    
    	if(flags[3])	// Если был встеречен флаг сортировки
    	{
	      	printf("\nQSort:\n");
        	qsort(files, numOfElems, sizeof(char*), compareStr);
	    }

    	for(int i = 0; i < numOfElems; i++)	// Вывод элементов массива
    	{
        	printf("  -  %s\n", files[i]); 
        	free(files[i]);
    	}

    	free(files); 

        return 0;
}
