#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]){

    // if (argc != 3){
    //     printf("Two args required\n");
    //     exit(-1);
    // }

    // this is how to use flags 

    int option;
    while((option = getopt(argc , argv, ":i:o")) != -1){
        switch (option)
        {
        case 'i':
            printf("I got a: %s\n", optarg);
            break;
        case 'o':
            printf("I got b\n");
            break;
        case '?':
            printf("ERROR");
            exit(-1);
        }
    }

    // printf("argc: %d\n", argc);

    // printf("argv[0] = %s\n", argv[0]);
    // printf("argv[1] = %s\n", argv[1]);
    // printf("argv[2] = %s\n", argv[2]);
    // printf("argv[3] = %s\n", argv[3]);

    return 0;
}