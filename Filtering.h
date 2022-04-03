#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>



void comment_remove(char * fileName)
{

    FILE *p1,*p2;
    char c;

    //opening files
    p1 = fopen(fileName, "r");
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

void formating_file()
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
void removeNewline()
{
     FILE *p1,*p2;
    char c,prev,c1;


    p1 = fopen("output4_formated_file.txt","r");
    p2 = fopen("line-comment-deleted.txt","w");

     while((c = fgetc(p1)) != EOF)
        {
            if(c=='\n')
            {
             c1=fgetc(p1);
             if(c1!=' ')
             {
                 fprintf(p2,"%c",c1);
                 printf("%c",c1);
             }

            }
            if(prev == c)
            continue;
            if(c != '\n')
            {
            fprintf(p2,"%c",c);
             printf("%c",c);
             }
            prev=c;
        }

   fclose(p1);
   fclose(p2);
}



void Filter(char * fileName)
{
printf("\n Scanning And Filtering: \n\n");

comment_remove(fileName);
formating_file();
removeNewline();

}

