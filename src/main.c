#include "../inc/header.h"

int main(int argc,char* argv[]){
    //DIR *dir; 
    //struct dirent *entry; 
    if(argc == 1){
        char *temp[1] = {"./"};
        print_right(1 ,temp);
 
        //dir = opendir("./"); 
        
        /*if (dir == NULL) { 
            perror("uls"); 
            exit(EXIT_FAILURE); 
        } 
 
        while ((entry = readdir(dir)) != NULL) { 
            printf("%s\n", entry->d_name); 
        } 

        closedir(dir); */
    }else if(argc >= 2){
        if(mx_strcmp(argv[1],"-l")==0){
            if(argc==2){
                print_files_info("./");
                exit(0);
            }else{
                for (int i = 2; i < argc; i++)
                {
                    print_files_info(argv[i]);
                }
                exit(0);
            }
        }else if(argv[1][0]== '-'){
            mx_printerr("uls: illegal option -");
            mx_printerr(argv[1]);
            mx_printerr("\n");
            mx_printerr("usage: uls [-l] [file ...]\n");
            exit(EXIT_FAILURE); 

        }else {


            print_right(argc - 1,&argv[1]);
        }

        /*for(int i = 1; i < argc; i++){
            //DIR *dir;
            //char *str = mx_strjoin(argv[i],"./");
            dir = opendir( argv[i]); 
            if (dir == NULL) {
                 
                perror(mx_strjoin("uls: ",argv[i])); 
                exit(EXIT_FAILURE); 
            } 
            while ((entry = readdir(dir)) != NULL) { 
                printf("%s\n", entry->d_name); 
            } 
            closedir(dir);
        }*/

    }
    //printf("%d", argc);
    //argv[0] = " ";
   
    return 0;

}
