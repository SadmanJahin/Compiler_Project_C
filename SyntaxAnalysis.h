#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char identifiers[100][40];
int identifierIndex=0;

int search(char *name)
{
    int i = 0;
    for(; i<identifierIndex; i++){
        if(!strcmp(identifiers[i],name))
            return 1;
    }
    return 0;
}
void Display()
{
    printf("\n\n");
    int i = 0;
    for(; i<identifierIndex; i++){
        printf("%s\t",identifiers[i]);
    }
}


int isIdentifier(char *lex)
{


    char identifier[32][10] = {"auto","break","case","char","const","continue","default",
							"do","double","else","enum","extern","float","for","goto",
							"if","int","long","register","return","short","signed",
							"sizeof","static","struct","switch","typedef","union",
							"unsigned","void","volatile","while"};
	int i;
	for(i = 0; i < 32; i++){
		if(strcmp(identifier[i], lex) == 0){
			return 0;
		}
	}

    if(isupper(lex[0]) || islower(lex[0]) || lex[0] == '_'){
        int s = 1,i;
        for(i=1; i<strlen(lex); i++){
            if(isupper(lex[i]) || islower(lex[i]) || isdigit(lex[i]) || lex[i] == '_'){
                s = 1;
            }else
                return 0;
        }
        if(s) return 1;
    }else{
        return 0;
    }
}

int isKeyword(char *lex)
{
    char keywords[8][10] = {"char","double","float",
							"int","long","short","signed","unsigned"};
	int i, s = 0;

	for(i = 0; i < 8; i++){
		if(strcmp(keywords[i], lex) == 0){
			s = 1;
			break;
		}
	}

	return s;
}

void print_line_number()
{
    FILE *p1,*p2;
    char c;
    int count=1;

    p1 = fopen("input1.c", "r");
    p2 = fopen("output4_linenum.txt","w");

    if(!p1)
        printf("\ninput.c can't be opened!");
    else
    {
        fprintf(p2, "ln %d ", count++);
        while((c = fgetc(p1)) != EOF)
        {
            if (c == '\r' || c == '\n')
            {
                fputc(c, p2);
                fprintf(p2, "ln %d ", count++);
            }
            else
            {
                fputc(c, p2);
            }

        }
    }
    fclose(p1);
    fclose(p2);


}


void comment_removed()
{

    FILE *p1,*p2;
    char c;

    //opening files
    p1 = fopen("output4_linenum.txt", "r");
    p2 = fopen("output4_comment_removed.txt","w");

    if(!p1)
        printf("\noutput_linenumber.txt can't be opened!");
    else
    {

        while((c = fgetc(p1)) != EOF)
        {
            if ((c == '/'))
            {
                char c1 = fgetc(p1);
                if(c1 == '/')
                {
                    while(fgetc(p1) != '\n');
                    fputc('\n',p2);
                }
                else if(c1 == '*')
                {
                    char c1;
                    while((c1 = fgetc(p1)) != '*')
                    {
                        if(c1 == '\n')
                            fputc(c1,p2);
                    }
                    while(fgetc(p1) != '/');
                }
                else
                {
                    fputc(c,p2);
                    fputc(c1,p2);
                }
            }

            else
            {
                fputc(c, p2);
            }

        }
    }
    fclose(p1);
    fclose(p2);

     p1 = fopen("output4_comment_removed.txt", "r");
    p2 = fopen("output4_line&comment_removed.txt","w");

    if(!p1)
        printf("\noutput4_line&comment_removed.txt can't be opened!");
    else
    {
        /*reading file */
        while((c = fgetc(p1)) != EOF)
        {

            if(c == ' ')
            {
                char c1;
                int count = 0;
                do
                {
                    count++;
                    c1 = fgetc(p1);
                }
                while(c1 == ' ');
                if(count%4 != 0)
                    fputc(c,p2);

                if(c1 != '\n')
                {
                    fputc(c1,p2);
                }


            }
            else
            {
                fputc(c, p2);
            }

        }
    }
    fclose(p1);
    fclose(p2);


}

void formatted_file()
{
    FILE *p1,*p2;
    char c;

    p1 = fopen("output4_line&comment_removed.txt", "r");
    p2 = fopen("output4_formated_file.txt","w");

    if(!p1)
        printf("\noutput_without_comments.txt can't be opened!");
    else
    {
        char prev;
        while((c = fgetc(p1)) != EOF)
        {
            if(c == ';' || c == ':' || c == ',' || c == '(' || c == ')' || c == '{' || c == '}' || c == '[' || c == ']' ||
                c == '\'' || c == '\"' || c == '%' || c == '^'){

                if(prev == ' '){
                    prev = c;
                    fputc(c, p2);

                    char c1 = fgetc(p1);


                    if(c1 != ' '){
                        fprintf(p2," %c",c1);
                        prev = c1;
                        if(!isupper(c1) && !islower(c1) && !isdigit(c1)){
                            fputc(' ',p2);
                            prev = ' ';
                        }
                    }else{
                        prev = c1;
                        fputc(c1,p2);
                    }

                }else{
                    fputc(' ', p2);
                    prev = c;
                    fputc(c, p2);
                    char c1 = fgetc(p1);

                    if( c1 == '.'){
                        char c2 = fgetc(p1);
                        fputc(' ',p2);
                        fputc(c1,p2);
                        while(isdigit(c2)){
                            fputc(c2,p2);
                            c2 = fgetc(p1);
                        }
                        fputc(' ',p2);
                        //fputc(c2,p2);
                        c1 = c2;
                        prev = c2;
                    }


                    if(c1 != ' '){
                        fprintf(p2," %c",c1);
                        prev = c1;
                        //handling non space after separator
                        if(!isupper(c1) && !islower(c1) && !isdigit(c1)){
                            fputc(' ',p2);
                            prev = ' ';
                        }

                    }else{
                        prev = c1;
                        fputc(c1,p2);
                    }
                }
            }else if(c == '+' || c == '-' || c == '*' || c == '/' || c == '!'){
                char c1 = fgetc(p1);
                if(c1 == '='){          /// for +=, -=, *= , /=, !=
                    if(prev == ' '){
                        fprintf(p2,"%c%c ",c,c1);
                        prev = ' ';

                    }else{
                        fprintf(p2," %c%c ",c,c1);
                        prev = ' ';

                    }
                }else if((c == '+' && c1 == '+') || (c == '-' && c1 == '-')) {      ///for ++, --
                    if(prev == ' '){
                        fprintf(p2,"%c%c ",c,c1);
                        prev = ' ';

                    }else{
                        fprintf(p2," %c%c ",c,c1);
                        prev = ' ';

                    }
                }
                else{          ///for +, -, *, /, !
                    if(prev == ' '){
                        fprintf(p2,"%c %c",c,c1);
                        prev = c1;

                    }else{
                        fprintf(p2, " %c %c",c,c1);
                        prev = c1;
                    }
                }

            }else if(c == '&' || c == '|'){
                char c1 = fgetc(p1);
                if((c == '&' && c1 == '&') || (c == '|' && c1 == '|')){          /// for && , ||
                    if(prev == ' '){
                        fprintf(p2,"%c%c ",c,c1);
                        prev = ' ';

                    }else{
                        fprintf(p2," %c%c ",c,c1);
                        prev = ' ';

                    }
                }else{          ///for & , |
                    if(prev == ' '){
                        fprintf(p2,"%c %c",c,c1);
                        prev = c1;

                    }else{
                        fprintf(p2, " %c %c",c,c1);
                        prev = c1;
                    }
                }
            }
            else if(c == '<' || c == '>'){
                char c1 = fgetc(p1);
                if(c1 == '=' || c1 == '<' || c1 == '>'){
                    if(prev == ' '){
                        fprintf(p2,"%c%c ",c,c1);
                        prev = ' ';

                    }else{
                        fprintf(p2," %c%c ",c,c1);
                        prev = ' ';

                    }
                }else{          ///for < or >
                    if(prev == ' '){
                        fprintf(p2,"%c %c",c,c1);
                        prev = c1;

                    }else{
                        fprintf(p2, " %c %c",c,c1);
                        prev = c1;
                    }
                }
            }else if(c == '='){         ///for =
                char c1 = fgetc(p1);
                if(c1 == '='){          /// for ==
                    if(prev == ' '){
                        fprintf(p2,"%c%c ",c,c1);
                        prev = ' ';
                    }else{
                        fprintf(p2," %c%c ",c,c1);
                        prev = ' ';
                    }

                }else{
                    if(prev == ' '){
                        if(c1 == ';' || c1 == ',' || c1 == '+' || c1 == '*' || c1 == '/' || c1 == '-' ||
                            c1 == '(' || c1 == ')' || c1 == '\'' || c1 == '\"' || c1 == '&' || c1 == '|' || c1 == '%'){
                                fprintf(p2,"%c %c ",c,c1);
                        }else{
                            fprintf(p2,"%c %c",c,c1);
                            prev = c1;
                        }

                    }else{
                        if(c1 == ';' || c1 == ',' || c1 == '+' || c1 == '*' || c1 == '/' || c1 == '-' ||
                            c1 == '(' || c1 == ')' || c1 == '\'' || c1 == '\"' || c1 == '&' || c1 == '|' || c1 == '%'){
                                fprintf(p2," %c %c ",c,c1);
                        }else if(c1 == ' '){        ///space after =
                            fprintf(p2," %c%c",c,c1);
                            prev = c1;
                        }else{
                            fprintf(p2," %c %c",c,c1);
                            prev = c1;
                        }
                    }
                }
            }


            else{
                prev = c;
                fputc(c, p2);

            }

        }

    }
    fclose(p1);
    fclose(p2);

}

void printIdentifer()
{
    FILE *p1,*p2;
    char c;
    p1 = fopen("output4_formated_file.txt", "r");
    p2 = fopen("output4_identifier.txt","w");

    if(!p1)
        printf("\noutput4_formated_file.txt can't be opened!");
    else
    {
        char word[10],prev_word[10];
        int count_error = 1;

        while(fscanf(p1,"%s",word)>0){

            if(isKeyword(word)){
                fprintf(p2,"kw %s ",word);
            }else if(!strcmp(word,"ln")){
                fprintf(p2,"\nln ");
            }else if(isIdentifier(word) && strcmp(word,"ln")){
                fprintf(p2,"id %s ",word);

            }else if(!strcmp(word,",") || !strcmp(word,";") || !strcmp(word,"\"")
                     || !strcmp(word,":")){
                fprintf(p2,"sep %s ",word);
            }else{
                fprintf(p2,"%s ",word);
            }
            strcpy(prev_word,word);

        }
    }
    fclose(p1);
    fclose(p2);

}
void printIntermediateOutput()
{
     FILE *p1,*p2;
      char c;
    p1 = fopen("output4_identifier.txt", "r");
    p2 = fopen("output4_intermediate.txt","w");

    while((c=fgetc(p1))!=EOF)
    {
        if(c=='\n')
        {
            printf("%c",c);
            fprintf(p2,"%c",c);
            c=fgetc(p1);
            c=fgetc(p1);
            c=fgetc(p1);
        }
        printf("%c",c);
        fprintf(p2,"%c",c);
    }
   fclose(p1);
   fclose(p2);
}
void check_error()
{

    FILE *p1;
    char c;
    p1 = fopen("output4_identifier.txt", "r");


    if(!p1)
        printf("\noutput_categories.txt can't be opened!");
    else
    {
        char word[10],prev_word[10],current_line[10]="0",error_name[40],error_line[10];;
        int count_error = 1;
        int count_second_open_brac = 0,count_second_close_brac = 0,count_if = 0,count_else = 0;

        while(fscanf(p1,"%s",word)>0){
            if(!strcmp(word,"ln")){
                fscanf(p1,"%s",current_line);
            }else if(!strcmp(word,"sep")){
                char present_sep[10];
                fscanf(p1,"%s",present_sep);
                if(!strcmp(prev_word,"sep")){
                    if(strcmp(error_name,"Duplicate token") || strcmp(current_line,error_line))
                        printf("Duplicate token at line %s\n",current_line);
                        strcpy(error_name,"Duplicate token");
                        strcpy(error_line,current_line);

                }
            }else if(!strcmp(word,"{") || !strcmp(word,"}")){
                if(!strcmp(word,"{")){
                    count_second_open_brac++;
                }
                if(!strcmp(word,"}")){
                    count_second_close_brac++;
                    if(count_second_close_brac > count_second_open_brac){
                        if(strcmp(error_name,"Misplaced") || strcmp(current_line,error_line))
                        printf("Misplaced '%s' at line %s\n",word,current_line);
                        strcpy(error_name,"Misplaced");
                        strcpy(error_line,current_line);
                        count_second_open_brac=0 ;
                        count_second_close_brac=0;
                    }

                }

            }else if(!strcmp(word,"if") || !strcmp(word,"else")){
                if(!strcmp(word,"if")){
                    count_if++;
                }else{
                    count_else++;
                    if(count_else > count_if){
                        if(strcmp(error_name,"Unmatched ifelse") || strcmp(current_line,error_line))
                        printf("Unmatched 'else' at line %s\n",current_line);
                        strcpy(error_name,"Unmatched ifelse");
                        strcpy(error_line,current_line);
                    }
                }
            }else if(!strcmp(word,"kw")){
                char data_type[20],id[5],id_name[50];
                fscanf(p1,"%s",data_type);
                while(strcmp(data_type,"id")){
                    fscanf(p1,"%s",data_type);
                    if(!strcmp(data_type,"kw")){
                        if(strcmp(error_name,"Duplicate datatype") || strcmp(current_line,error_line))
                        printf("Duplicate data type at line %s\n",current_line);
                        strcpy(error_name,"Duplicate datatype");
                        strcpy(error_line,current_line);
                    }
                }
                fscanf(p1,"%s",id_name);
                strcpy(identifiers[identifierIndex++],id_name);
            }else if(!strcmp(word,"id")){
                char id_name[50];
                fscanf(p1,"%s",id_name);
                if(!search(id_name)){
                    if(strcmp(error_name,"Undeclared") || strcmp(current_line,error_line))
                        printf("Undeclared '%s' at line %s\n",id_name,current_line);
                        strcpy(error_name,"Undeclared");
                        strcpy(error_line,current_line);
                }
            }else if(!strcmp(word,"for")){
                char name[10],id_name[50];
                fscanf(p1,"%s",name);
                fscanf(p1,"%s",name);
                if(!search(id_name)){
                    if(strcmp(error_name,"Undeclared") || strcmp(current_line,error_line))
                        printf("Undeclared '%s' at line %s\n",id_name,current_line);
                        strcpy(error_name,"Undeclared");
                        strcpy(error_line,current_line);
                }

            }

            strcpy(prev_word,word);
        }

        if(count_second_open_brac > count_second_close_brac){
            if((count_second_open_brac - count_second_close_brac) > 1){
                printf("expected '}' %d times at line %s\n",(count_second_open_brac - count_second_close_brac),current_line);

            }else{
                printf("expected '}' at line %s\n",current_line);

            }

        }else if(count_second_open_brac < count_second_close_brac){
            if((count_second_close_brac - count_second_open_brac) > 1){
                printf("expected '{' %d times to balance\n",(count_second_close_brac - count_second_open_brac));

            }else{
                printf("expected '{' to balance\n");

            }
        }
    }
    fclose(p1);
}


void FindSyntaxError()

{
printf("\n\n Syntax Analysis: \n");
print_line_number();
comment_removed();
formatted_file();
printIdentifer();
printf("\n Intermediate Output:");
printIntermediateOutput();
printf("\n\n Errors Detected: \n");
check_error();

}

