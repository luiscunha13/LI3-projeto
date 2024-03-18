#include<glib.h>

#include"../include/parsing.h"


int main(int argc, char **input){

    if(argc==3){

        CATALOG *c = open_folder(input[1]); 
        normal_program (input[2], c);  
        delete_Catalog(c);
    
    }
    else if(argc==1){

        interactive_program();
    
    }
    
    return 0;
}