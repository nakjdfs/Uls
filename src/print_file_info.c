#include "../inc/header.h"
void print_files_info(char *file_path) {
    bool isDir = true; 
    DIR *dir; 
    struct dirent *entry; 
    dir = opendir(file_path); 
    if (dir == NULL) { 
        isDir = false;
    } 
    if (isDir)
    {
        int count = 0;
        while ((entry = readdir(dir)) != NULL) { 
            count++;
        } 
        closedir(dir);
        dir = opendir(file_path);
        char *files[count];
        int sumfil = 0;
        int dots = 0;
        for(int i = 0; i < count; i++){
            struct stat file_stat;
            entry = readdir(dir);
            files[i] = mx_strdup(entry->d_name);
            char *temp = mx_strjoin(file_path,mx_strjoin("/",files[i]));
            if (stat(temp, &file_stat) < 0) { 
                perror("stat1"); 
                exit(EXIT_FAILURE); 
            }
            if(files[i][0] == '.'){
                dots++;
            }else{
                sumfil += file_stat.st_blocks;
            }
            free(temp);
        }
        closedir(dir);
        mx_bubble_sort(files,count);
        int amount_of_num[count];
        int amount_of_nlin[count];
        for(int i = 0; i < count; i++){
            struct stat file_stat;
            char *temp = mx_strjoin(file_path,mx_strjoin("/",files[i]));
            if (stat(temp, &file_stat) < 0) { 
                perror("uls"); 
                exit(EXIT_FAILURE); 
            }
            amount_of_num[i] = len_of_num(file_stat.st_size);
            amount_of_nlin[i] = len_of_num(file_stat.st_nlink);
            free(temp);
        }
        
        #ifdef __linux__
        sumfil /= 2;
        #endif
        mx_printstr("total ");
        mx_printint(sumfil);
        mx_printstr("\n");
        int max = max_of(amount_of_num, count);
        int max_n = max_of(amount_of_nlin, count);
        for(int i = 0; i < count; i++){
            if(files[i][0] =='.'){
                continue;
            }
            struct stat file_stat; 
            struct passwd *pwd; 
            struct group *grp;
            char *temp = mx_strjoin(file_path,mx_strjoin("/",files[i]));
            if (stat(temp, &file_stat) < 0) { 
                perror("uls"); 
                exit(EXIT_FAILURE); 
            }
            pwd = getpwuid(file_stat.st_uid); 
            grp = getgrgid(file_stat.st_gid); 
            mx_printstr(get_file_permissions(temp));
            mx_printstr("  ");
            print_size(file_stat.st_nlink, max_n, amount_of_nlin[i]);
            mx_printstr(" ");
            mx_printstr((pwd != NULL) ? pwd->pw_name : ""); 
            mx_printstr("  ");
            mx_printstr((grp != NULL) ? grp->gr_name : ""); 
            mx_printstr("  ");
            print_size(file_stat.st_size,max,amount_of_num[i]);
            mx_printstr(" ");
            print_date(temp);
            mx_printstr(" ");
            mx_printstr(files[i]);
            mx_printstr("\n");
            free(temp);
        }
    } else {
        print_file_info(file_path);
    }
    
    
    
    /*
    struct stat file_stat; 
    struct passwd *pwd; 
    struct group *grp; 
    //struct tm *tm_info; 
    //char time_buf[80]; 
    file_path ="./";
    //if (stat(file_path, &file_stat) < 0) { 
    //    perror("stat"); 
    //    exit(EXIT_FAILURE); 
    //}
    //char * str =  get_file_permissions(file_path);
 
    // Get user and group name from uid and gid 
    pwd = getpwuid(file_stat.st_uid); 
    grp = getgrgid(file_stat.st_gid); 
 
    // Format time string 
    //tm_info = localtime(&file_stat.st_mtime); 
    //strftime(time_buf, 80, "%b %d %H:%M", tm_info); 
 
    // Print file details 
    printf("%s %ld %s %s %5ld %s \n", 
        get_file_permissions(file_path), 
        file_stat.st_nlink, 
        (pwd != NULL) ? pwd->pw_name : "", 
        (grp != NULL) ? grp->gr_name : "", 
        file_stat.st_size, 
        ctime(&file_stat.st_mtime)//time_buf, 
         
    ); */
}

void print_file_info(char *file_path){
    struct stat file_stat; 
    struct passwd *pwd; 
    struct group *grp;
    if (stat(file_path, &file_stat) < 0) { 
        perror("uls"); 
        exit(EXIT_FAILURE); 
    }
    pwd = getpwuid(file_stat.st_uid); 
    grp = getgrgid(file_stat.st_gid); 
    mx_printstr(get_file_permissions(file_path));
    mx_printstr("  ");
    mx_printint(file_stat.st_nlink);
    mx_printstr(" ");
    mx_printstr((pwd != NULL) ? pwd->pw_name : ""); 
    mx_printstr("  ");
    mx_printstr((grp != NULL) ? grp->gr_name : ""); 
    mx_printstr("  ");
    mx_printint(file_stat.st_size);//print_size(file_stat.st_size,max,amount_of_num[i]);
    mx_printstr(" ");
    print_date(file_path);
    mx_printstr(" ");
    mx_printstr(file_path);
    mx_printstr("\n");
}
