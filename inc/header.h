#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/stat.h> 
#include "../libmx/inc/libmx.h"
#include <sys/ioctl.h>


#include <errno.h>  
#include <pwd.h> 
#include <grp.h> 
#include <time.h> 

bool is_existing(char* dir);
void print_file_info(char *file_path);
char *get_file_permissions(const char *filename);
void print_in_alphabetical(char * file);
void print_date(char *date);
int len_of_num(int num);
int max_of(int * arr,int size);
void print_size(int num, int max, int size);
bool is_dir(const char* filename);
void print_files_info(char *file_path);
void print_right(int argc,char *argv[]);
void print_table(char **str_array, int num_elements);
