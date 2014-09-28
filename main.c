/*
 *
 * Dong Mai
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>
#include <ctype.h>
#include <sys/time.h>
#include <sys/resource.h>


#include "list.h"

bool is_integer(const char *tok){
	for (int i = 0; i < strlen(tok); i++){
		if (i == 0){
			if ((tok[i] != '-') & (!isdigit(tok[i]))){
				return false;
			}
		}else if (tok[i] == '#'){
			break;
		}else if (!isdigit(tok[i])){
			return false;
		}
	}
	return true;
	
}

int* tokenify(const char *s) {
    // your code here
    char *str1 = strdup(s);
    char *str2 = strdup(s);
    char *tok;
    int count = 0;
    tok = strtok(str1, " \n\t");
    while (tok != NULL) {
		if (strcasecmp(tok, "#") == 0){
			break;
		}else if (is_integer(tok)){
			count++;
		}
        tok = strtok(NULL, " \n\t");        
    }
    int *ptr = malloc((count+1)*sizeof(int));
	ptr[0] = count;
    tok = strtok(str2, " \n\t");
	int i = 1;
    while (tok != NULL){
		if (strcasecmp(tok, "#") == 0){
			break;
		}else if (is_integer(tok)){        
        	ptr[i] = atoi(tok);
			i++;
		}
        tok = strtok(NULL, " \n\t");
    }
	free(str1);
	free(str2);
    return ptr;
}


void process_data(FILE *input_file) {
    // !! your code should start here.  the input_file parameter
    // is an already-open file.  you can read data from it using
    // the fgets() C library function.  close it with the fclose()
    // built-in function
	char line[255];	
	struct node *head = NULL;
	struct node **ptrToPtr = &head;
	struct rusage usage;
	while (fgets(line, 255, input_file) != NULL){		
		char *s = line;
		int *ptr = tokenify(s);
		for (int i = 1; i < ptr[0]+1; i++){
			list_append(ptr[i], ptrToPtr);
		}
		free(ptr);
	}
	list_sort(ptrToPtr);
	list_print(*ptrToPtr);
	list_clear(*ptrToPtr);
	int callResult = getrusage(RUSAGE_SELF, &usage);
	if (callResult == 0){
		printf("User time: %ld.%lds\n", (usage.ru_utime).tv_sec, (usage.ru_utime).tv_usec);
		printf("System time: %ld.%lds\n", (usage.ru_stime).tv_sec, (usage.ru_stime).tv_usec);
	}else{
		printf("ERROR: %s\n", strerror(errno));
	}
}


void usage(char *program) {
    fprintf(stderr, "usage: %s [<datafile>]\n", program);
    exit(1);
}

#ifndef AUTOTEST
int main(int argc, char **argv) {
    FILE *datafile = NULL;

    /* find out how we got invoked and deal with it */
    switch (argc) {
        case 1:
            /* only one program argument (the program name) */ 
            /* just equate stdin with our datafile */
            datafile = stdin;        
            break;

        case 2:
            /* two arguments: program name and input file */
            /* open the file, assign to datafile */
            datafile = fopen(argv[1], "r");
            if (datafile == NULL) {
                printf("Unable to open file %s: %s\n", argv[1], strerror(errno));
                exit(-1);
            }
            break;

        default:
            /* more than two arguments?  throw hands up in resignation */
            usage(argv[0]);
    }

    /* 
     * you should be able to just read from datafile regardless 
     * whether it's stdin or a "real" file.
     */
    process_data(datafile);
    fclose(datafile);
    return 0;
}
#endif
