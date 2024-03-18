#define _GNU_SOURCE
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<glib.h>
#include<locale.h>

#include"../include/queries.h"

//verifica se um prefixo contém números
int hasNumbers(char *prefix){
    int len = strlen(prefix);
    for(int i=0;i<len;i++){
        if(isdigit(prefix[i])) return 1;
    }

    return 0;
}

//verifica se um nome contem o prefixo
int verify_prefix(char *prefix, const char *id){
    int len = strlen(prefix);

    if(strlen(id) < len) return 0;

    for(int i=0;i<len;i++){
        if(prefix[i] != id[i]) return 0;
    }

    return 1;
}

//função usada para ordenar as respostas
gint compare9(gconstpointer a, gconstpointer b){
	USER *user1 =(USER *) a;
	USER *user2 =(USER *) b;
	const char *name1 = getName(user1);
	const char *name2 = getName(user2);
    setlocale(LC_COLLATE, "en_US.UTF-8");

	if(strcoll(name1,name2)<0){
		return -1; 
	}
	if(strcoll(name1,name2)>0){
		return 1;
	}
	else{
		if(strcoll(getUserId(user1),getUserId(user2))<0){
			return -1;
		}
		else return 1;
	}
}

void query9(char *out_path, char *prefix, CATALOG *c, int f){

    if(hasNumbers(prefix)==1){
        if(f==2)printline(out_path, NULL, 2,-1,-1,-1);
        else printline(out_path, NULL, 1,-1,-1,-1);
        return;
    }
    
    
    GSList *resposta = NULL;

    GSList *atual = getUserIdsList(getDataUsers(c));

    if(prefix[0]=='"'){
        prefix[strlen(prefix)-1]='\0';
        prefix=prefix+1;        
    }

    int aux=0;
    int acc=0;
    for(;atual!=NULL;atual=atual->next){
        USER *u = (USER *)atual->data;
        if(verify_prefix(prefix,getName(u))==1 &&(getAccStatus(u)==1)){
            resposta = g_slist_prepend(resposta,u);
            acc++;
            aux=1;
        }
        else{
            if(aux==1){
                if(verify_prefix(prefix,getName(u))==0) break;
            }
        }
        

    }

    resposta = g_slist_sort(resposta,compare9);

    if(resposta==NULL){
        if(f==2)printline(out_path, NULL, 2,-1,-1,-1);
        else printline(out_path, NULL, 1,-1,-1,-1);
        return;
    }

    char **answer = malloc(acc * sizeof(char*));

    int a=0;

    for(atual=resposta; atual != NULL; atual=atual->next){
        USER *user = (USER *)atual->data;
        
        if(asprintf(&answer[a], "%s;%s", getUserId(user),getName(user))==0) return;
		a++; 

    }

    if(f==0) printline(out_path, answer, 1,9,1,a);
    else if(f==1) printline(out_path, answer, 2,9,1,a);
    else printline(out_path, answer, 3,9,1,a);

    //freelist(answer, acc);
    
    g_slist_free(resposta);

}




