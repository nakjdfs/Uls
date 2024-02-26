#include "../inc/header.h"

bool is_existing(char* dir){
    DIR *d; 
    d = opendir(dir); 
    if (d == NULL) { 
        return false;
    }
    closedir(d);
    return true;
}


 
char *get_file_permissions(const char *filename) { 
    struct stat sb; 
 
    if (stat(filename, &sb) == -1) { 
        perror("uls"); 
        exit(EXIT_FAILURE); 
    } 
 
    char *permissions = malloc(12 * sizeof(char)); 
    if (permissions == NULL) { 
        perror("uls"); 
        exit(EXIT_FAILURE); 
    } 
 
    // Встановлюємо 10 символів у permissions знаками-дефісами 
    for (int i = 0; i < 11; i++) { 
        permissions[i] = '-'; 
    } 
    if(is_dir(filename) == true){
        permissions[0] = 'd';
    }
 
    // Встановлюємо дозволи на читання 
    if (sb.st_mode & S_IRUSR) { 
        permissions[1] = 'r'; 
    } 
    if (sb.st_mode & S_IRGRP) { 
        permissions[4] = 'r'; 
    } 
    if (sb.st_mode & S_IROTH) { 
        permissions[7] = 'r'; 
    } 
 
    // Встановлюємо дозволи на запис 
    if (sb.st_mode & S_IWUSR) { 
        permissions[2] = 'w'; 
    } 
    if (sb.st_mode & S_IWGRP) { 
        permissions[5] = 'w'; 
    } 
    if (sb.st_mode & S_IWOTH) { 
        permissions[8] = 'w'; 
    } 
 
    // Встановлюємо дозволи на виконання 
    if (sb.st_mode & S_IXUSR) { 
        permissions[3] = 'x'; 
    } 
    if (sb.st_mode & S_IXGRP) { 
        permissions[6] = 'x'; 
    } 
    if (sb.st_mode & S_IXOTH) { 
        permissions[9] = 'x'; 
    } 
 
   
 
    permissions[10] = '\0'; 
    return permissions; 
}

void print_in_alphabetical(char * file){
    DIR *dir; 
    struct dirent *entry; 
    dir = opendir(file); 
    if (dir == NULL) { 
        perror("uls"); 
        exit(EXIT_FAILURE); 
    } 
    int count = 0;
    while ((entry = readdir(dir)) != NULL) { 
        count++;
    } 
    closedir(dir);
    dir = opendir(file);

    char *files[count];
    for(int i = 0; i < count; i++){
        entry = readdir(dir);
        files[i] = mx_strdup(entry->d_name);
    }
    closedir(dir);
    mx_bubble_sort(files,count);
    for (int i = 0; i < count; i++)
    {
        if(mx_strcmp(files[i],".") != 0 && mx_strcmp(files[i],"..")!= 0){
            mx_printstr(files[i]);
            if(i!=count -1){
                mx_printstr("  ");
            }else{
                mx_printstr("\n");
            }
        }
        
    }
    

}

void print_date(char * filename){

    /*char * res = mx_strndup(&date[4],12);
    mx_printstr(res);
    free(res);*/
    struct stat st; 
    if (stat(filename, &st) == -1) { 
        perror("stat"); 
        exit(1); 
    } 
    long creation = st.st_mtime; 
    long current = time(NULL); 
    double diff_in_seconds = current - creation;
    double diff_in_months = diff_in_seconds / (60 * 60 * 24 * 30); 
    if (diff_in_months > 6) { 
        char * res = mx_strjoin(mx_strndup(&ctime(&creation)[4],7),mx_strndup(&ctime(&creation)[19],5));
        mx_printstr(res);
        free(res);
    } else { 
        char * res = mx_strndup(&ctime(&creation)[4],12);
        mx_printstr(res);
        free(res);
    } 
}

int len_of_num(int num){
    char *s = mx_itoa(num);
    return mx_strlen(s);
}
int max_of(int * arr,int size){
    int max = arr[0];
    for (int i = 0; i < size; i++)
    {
        if(arr[i] > max){
            max = arr[i];
        }
    }
    return max;
}
void print_size(int num, int max, int size){
    if(max != size){
        for (int i = 0; i < max - size; i++)
        {
            mx_printstr(" ");
        }
    }
    mx_printint(num);
}

/*
char get_file_type(const char* filename) { 
    struct stat st; 
    if (stat(filename, &st) != 0) { 
        perror("stat error"); 
        return '?'; 
    } 
 
    if (S_ISREG(st.st_mode)) { 
        return '-'; 
    } else if (S_ISDIR(st.st_mode)) { 
        return 'd'; 
    } else if (S_ISLNK(st.st_mode)) { 
        return 'l'; 
    } else if (S_ISCHR(st.st_mode)) { 
        return 'c'; 
    } else if (S_ISBLK(st.st_mode)) { 
        return 'b'; 
    } else if (S_ISFIFO(st.st_mode)) { 
        return 'p'; 
    } else if ( S_ISSOCK(st.st_mode)) { 
        return 's'; 
    } else { 
        return '?'; 
    } 
}*/
bool is_dir(const char* filename){
    struct stat st; 
    if (stat(filename, &st) != 0) { 

        perror(mx_strjoin("uls: ",filename)); 
        exit(EXIT_FAILURE); 
    } 
    if (S_ISREG(st.st_mode)) { 
        return false; 
    } else{
        return true;
    }
}


void print_right(int argc,char *argv[]){
    //struct winsize w;
    //ioctl(1,TIOCGWINSZ,&w);
    bool isDir[argc];
    int c = 0;
    for(int i = 0; i < argc; i++){
        isDir[i] = is_dir(argv[i]);
        if(!isDir[i]){
            c++;
        }
    }
    if(c != 0){
        char * files1[c];
        int j = 0;
        for (int  i = 0; i < argc; i++)
        {
            if(!isDir[i]){
                files1[j] = mx_strdup(argv[i]);
            }
        }
        print_table(files1,c);
        for (int i = 0; i < c; i++)
        {
            free(files1[i]);
        }
        
    }
    for(int i = 0; i < argc; i++){
        if(isDir[i]){
            DIR *dir; 
            struct dirent *entry; 
            dir = opendir(argv[i]);
            int count = 0;
            while ((entry = readdir(dir)) != NULL) { 
                count++;
            } 
            if(argc == 1){//if(mx_strcmp(argv[i],"./") == 0 || ){

            }else
            {
                if(i != 0){
                    mx_printstr("\n");
                }
                mx_printstr(argv[i]);
                mx_printstr(":\n");   
            }
            if(count - 2 == 0){
                return;
            }
            closedir(dir);
            dir = opendir(argv[i]);
            char *files[count];
            int dots = 0;
            for(int i = 0; i < count; i++){
                entry = readdir(dir);
                files[i] = mx_strdup(entry->d_name);
                if(files[i][0] == '.'){
                    dots++;
                }
            }
            closedir(dir);
            mx_bubble_sort(files,count);
            print_table(&files[dots],count - dots);
            for (int i = 0; i < c; i++)
            {
                free(files[i]);
            }
        }
    }
}

void print_table(char **str_array, int size) { 
    // Get terminal size 
    struct winsize w; 
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w); 
    int cols = w.ws_col; 
    //printf("%d\n", cols);

    // Calculate max string length 
    int max_len = 0;
    int length = 0;
    for (int i = 0; i < size; i++) { 
        int len = mx_strlen(str_array[i]);
        length +=len; 
        if (len > max_len) { 
            max_len = len; 
        } 
    } 
    /*int length = 0;
    for (int i = 0; i < size; i++){
        if(i != size - 1){
            length += mx_strlen(str_array[i]) + 1;
        }else{
            length += mx_strlen(str_array[i]);
        }
        
    }*/
 
    // Calculate number of rows and columns 
    int indent = 2;
    if(((length + (size * indent)) - cols) < 0) {
        for(int i = 0; i < size; i++) {
            mx_printstr(str_array[i]);
            if(i!= size - 1){
                mx_printstr("  ");
            }else{
                mx_printstr("\n");
            }
        }
        return;
    }
    int rows = (size * max_len + (size - 1) * indent ) / cols + ((size * max_len + (size - 1) * indent ) % cols ? 1 : 0); //a a a a a 
    int actual_cols = size / rows + (size % rows ? 1 : 0) ; // a \n a \n a \n 
    //printf("%d\n", rows);
    //printf("%d\n", actual_cols);
    // Print table 
    for (int i = 0; i < rows; i++) { 
        for (int j = 0; j < actual_cols; j++) { 
            int index = i + j * rows; 
            if (index < size) { 
                mx_printstr(str_array[index]);
                if (j < actual_cols - 1)
                {
                    if(rows == 1) {
                        mx_printstr("  ");
                    }else {
                        for (int r = 0; r < max_len - mx_strlen(str_array[index]) + indent; r++) {
                            mx_printstr(" ");
                        }
                    }
                }
                 
            } 
        } 
        mx_printstr("\n"); 
    } 
}

