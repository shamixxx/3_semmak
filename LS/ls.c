#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <dirent.h>
#include <errno.h>
#include <pwd.h>
#include <limits.h>
#include <stdlib.h>

	
int main(int argc, const char** argv)                             //argc - Количество принимаемых аргументов     //argv - имя файла
{
 	DIR* dir;                                                                    //Создаём переменную dir типа DIR* (Поток данных о директории)
	struct dirent* curr_file_info;                                               //Создаём специальную структуру чтобы складывать всю инфу о файле из потока
	struct stat sb;                                                              //Сложим готовую статистику о файле сюда
	char* full_path = NULL;                                                      //Создаём строковую переменную под путь к файлу (Пустую)
	struct passwd  *pw_d;                                        //<--                                                        
	if(argc < 2)                                                                 //Если выполнено это условие, это значит, что не задан файл, свойства которого нужно описать.
	{
		printf("No arguments supplied\n");
		return -1;                                                           //Вывод ошибки
	}
	dir = opendir(argv[1]);                                                      //Открываем поток данных dir= поток данных о первом элементе argv
	if(dir == NULL)                                                              //Если такого файла нет, то ОШИБКА
	{
		printf("Error - %d\n", errno);
		return -1;
	}
	full_path = realpath(argv[1], NULL);                                         //Фулпас присвоили местонахождение файла (реалпас Выводит местонахождение файла)
	while( ( curr_file_info = readdir(dir) ) != NULL )                           //Всю информацию из потока данных о файле (дир) складываем в curr_file_info и зацикливаем это пока всё не прочтём
	{
		printf("--------------------------------------------\n");
		printf("File path:  %s/%s\n", full_path, curr_file_info->d_name);    //Пропустили строку и выводим путь к файлу и его имя, взятое из структуры curr_file_info
		full_path = realpath(argv[1], NULL);                                 //Фулпас присвоили местонахождение файла (реалпас Выводит местонахождение файла)
                char* tempp = full_path;                                             //Создали переменную темп в которую записали имя файла
                tempp = strcat(tempp, "/");                                          //Добавили в конец строки слэш
                tempp = strcat(tempp, curr_file_info->d_name);                       //Добавили имя файла взятое из структуры курфайлинфо
		if (stat(tempp, &sb) == -1)                                          //Получаем статистику файла указаного в темп и кладём его в сб, если нет, то ОШИБКА
			{                    
        			printf("Statistics couldn't be taken.");
        			return -1;
    			}	
    	printf("File size:                %lld bytes\n", (long long) sb.st_size);   //Выводим статистику из сб
    	pw_d = getpwuid ( sb.st_uid ); 
  		printf ( "File owner:               %s \n", pw_d->pw_name); 
    	printf("Mode:                     %lo (octal)\n", (unsigned long) sb.st_mode);
    	printf("Last file access:         %s", ctime(&sb.st_atime));                //Время последнего доступа
      printf("Last file modification:   %s", ctime(&sb.st_mtime));                  //Изменения
      printf("File create time:         %s", ctime(&sb.st_ctime));                  //Создания
	}
	free(full_path);							    //Освобождаем фулпас
	closedir(dir);								    //Закрываем поток
	printf("%s %s\n", argv[0], argv[1]);
	return 0;
}
