#include<stdio.h>
#include<ctype.h>
#include<string.h>

void stepOne()
{
    FILE *p1,*p2;
    char c;

    p1 = fopen("line-comment-deleted.txt", "r");
    p2 = fopen("output1.txt","w");

    if(!p1)
        printf("\nInput file can't be opened!");
    else
    {
        char prev;
        while((c = fgetc(p1)) != EOF)
        {
            if(c == ';' || c == ':' || c == ',' || c == '(' || c == ')' || c == '{' || c == '}' || c == '[' || c == ']' ||
                c == '\'' || c == '\"'){

                if(prev == ' '){
                    prev = c;
                    fputc(c, p2);

                    char c1 = fgetc(p1);


                    if(c1 != ' '){
                        fprintf(p2," %c",c1);
                        prev = c1;
                    }else{
                        prev = c1;
                        fputc(c1,p2);
                    }

                }else{
                    fputc(' ', p2);
                    prev = c;
                    fputc(c, p2);
                    char c1 = fgetc(p1);

                    if(c1 != ' '){
                        fprintf(p2," %c",c1);
                        prev = c1;

                    }else{
                        prev = c1;
                        fputc(c1,p2);
                    }
                }
            }else if(c == '+' || c == '-' || c == '*' || c == '/' || c == '!'|| c == '%' || c == '^')
            {
                char c1 = fgetc(p1);
                if(c=='-'&&isdigit(c1))
                {
                    if(prev == ' '){
                        fprintf(p2,"%c%c",c,c1);
                        prev =c1;
                    }
                }
                if(c1 == '='){
                    if(prev == ' '){
                        fprintf(p2,"%c%c ",c,c1);
                        prev = ' ';

                    }else{
                        fprintf(p2," %c%c ",c,c1);
                        prev = ' ';

                    }
                }else if(c1 == '+'|| c1 == '-') {
                    if(prev == ' '){
                        fprintf(p2,"%c%c ",c,c1);
                        prev = ' ';

                    }else{
                        fprintf(p2," %c%c ",c,c1);
                        prev = ' ';

                    }
                }
                else{
                    if(prev == ' '){
                        fprintf(p2,"%c %c",c,c1);
                        prev = c1;

                    }else{
                        fprintf(p2, " %c %c",c,c1);
                        prev = c1;
                    }
                }

            }else if(c == '&' || c == '|')
            {
                char c1 = fgetc(p1);
                if(c1 == '&' || c1 == '|'){
                    if(prev == ' '){
                        fprintf(p2,"%c%c ",c,c1);
                        prev = ' ';

                    }else{
                        fprintf(p2," %c%c ",c,c1);
                        prev = ' ';

                    }
                }else{
                    if(prev == ' '){
                        fprintf(p2,"%c %c",c,c1);
                        prev = c1;

                    }else{
                        fprintf(p2, " %c %c",c,c1);
                        prev = c1;
                    }
                }
            }
            else if(c == '<' || c == '>')
                {
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
            }else if(c == '=')
            {
                char c1 = fgetc(p1);
                if(c1 == '='){
                    if(prev == ' '){
                        fprintf(p2,"%c%c ",c,c1);
                        prev = ' ';
                    }else{
                        fprintf(p2," %c%c ",c,c1);
                        prev = ' ';
                    }

                }else{

                     if(prev == ' '){
                        if( c1 == '-' || c1 == '*' ||c1 == '(' || c1 == '\'' || c1 == '\"' || c1 == '&'){
                                    if(c1=='-')
                                    {
                                    fprintf(p2,"%c %c",c,c1);
                                    }
                                    else
                                    fprintf(p2,"%c %c ",c,c1);
                        }else{
                            fprintf(p2,"%c %c",c,c1);
                            prev = c1;
                        }

                    }else{
                        if(c1 == '-' || c1 == '*' ||c1 == '(' || c1 == '\'' || c1 == '\"' || c1 == '&'){
                                if(c1=='-')
                                    {
                                    fprintf(p2," %c %c",c,c1);
                                    }
                                    else
                                fprintf(p2," %c %c ",c,c1);
                        }else if(c1 == ' '){
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

void stepTwo()
{
    FILE *p1,*p2;
    char c;
    p1 = fopen("output1.txt", "r");
    p2 = fopen("output2.txt","w");

    if(!p1)
        printf("\nFile can't be opened!");
    else
    {
        char word[10],prev_word[10];
        int count_error = 1;

        while(fscanf(p1,"%s",word)>0){
            int s;
            if(s=keyword_rec(word)){
                fprintf(p2,"[kw ");
                fprintf(p2,"%s] ",word);
            }else if( (s = num_rec(word))){
                if(s == 1){
                    if(!strcmp(prev_word,"'")){
                        fprintf(p2,"[char ");
                        fprintf(p2,"'%s'] ",word);
                    }else{
                        fprintf(p2,"[num ");
                        fprintf(p2,"%s] ",word);
                    }

                }
                else{
                    if(!strcmp(prev_word,"'")){
                        fprintf(p2,"[char ");
                        fprintf(p2,"'%s'] ",word);
                    }
                }

            }else if(identifier_rec(word)){
                if(!strcmp(prev_word,"'")){
                    fprintf(p2,"[char ");
                    fprintf(p2,"'%s'] ",word);
                }else if(!strcmp(prev_word,"\"")){
                    fprintf(p2,"[str ");
                    fprintf(p2,"\"%s\"] ",word);
                }else{
                    fprintf(p2,"[id ");
                    fprintf(p2,"%s] ",word);
                }

            }else if(separator_rec(word)){
                fprintf(p2,"[sep ");
                fprintf(p2,"%s] ",word);
            }else if(operator_rec(word)){
                fprintf(p2,"[op ");
                fprintf(p2,"%s] ",word);
            }else if(parenthesis_rec(word)){
                fprintf(p2,"[par ");
                fprintf(p2,"%s] ",word);
            }
            else{
                printf("\nError %d: '%s' is not valid",count_error++,word);
                fprintf(p2,"[unkn ");
                fprintf(p2,"%s] ",word);
            }
            strcpy(prev_word,word);


        }
    }
    fclose(p1);
    fclose(p2);
    printf("\n\n");

    p2 = fopen("output2.txt","r");
    while((c=fgetc(p2))!=EOF)
        printf("%c",c);
    fclose(p2);

}
int parenthesis_rec(char *lex)
{
    char separators[11][10] = {"(",")","{","}","[","]"};
	int i, s = 0;

	for(i = 0; i < 6; i++){
		if(strcmp(separators[i], lex) == 0){
			s = 1;
			break;
		}
	}

	return s;
}
int separator_rec(char *lex)
{
    char separators[11][10] = {",",";","'","\"",":"};
	int i, s = 0;

	for(i = 0; i < 11; i++){
		if(strcmp(separators[i], lex) == 0){
			s = 1;
			break;
		}
	}

	return s;
}
int operator_rec(char *lex)
{    int s,i,l;
    l=strlen(lex);
    if(l>2)
        s=4;
    else
    {   s=0;
        for(i=0; i<l; i++)
        {
            if(s==0){

            if(lex[i]=='+' || lex[i]=='-' || lex[i]=='*' || lex[i]=='/' || lex[i]=='%' || lex[i]=='=' || lex[i]=='!' || lex[i]=='<' || lex[i]=='>' || lex[i]=='|'|| lex[i]=='&'|| lex[i]=='~'|| lex[i]=='^')
            {
                s=1;
            }
            else
            {
                s=4;
                break;
            }
            }
            else if(s=1)
            {
                if(lex[i]=='+' || lex[i]=='-' || lex[i]=='=' || lex[i]=='<' || lex[i]=='>' || lex[i]=='|' || lex[i]=='&')
                {
                    if(lex[i]==lex[i-1])
                        s=2;
                    else if(lex[i]=='=')
                        {

                        if(lex[i-1]=='+' || lex[i-1]=='-' || lex[i-1]=='*' || lex[i-1]=='/' || lex[i-1]=='%' || lex[i-1]=='!' || lex[i-1]=='<' || lex[i-1]=='>' || lex[i-1]=='|'|| lex[i-1]=='&'|| lex[i-1]=='^')
                        {   s=2;
                        }
                        else
                        {
                            s=4;
                            break;
                        }

                    }
                    else
                    {
                        s=4;
                        break;
                    }
                }
                else
                {
                    s=4;
                    break;
                }

            }
        }

    }
    if(s==1||s==2||s==3)
        s=1;
    else
        s=0;
    return s;
}

int keyword_rec(char *lex)
{
    char keywords[32][10] = {"auto","break","case","char","const","continue","default",
							"do","double","else","enum","extern","float","for","goto",
							"if","int","long","register","return","short","signed",
							"sizeof","static","struct","switch","typedef","union",
							"unsigned","void","volatile","while"};
	int i, s = 0;

	for(i = 0; i < 32; i++){
		if(strcmp(keywords[i], lex) == 0){
			s = 1;
			break;
		}
	}

	return s;
}
int identifier_rec(char *lex)
{
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

int num_rec(char *lex)
{
    int i, l, s;
    i=0;
    if(isdigit(lex[i])) {
        s=1; i++;
    }
    else if(lex[i]=='.'||lex[i]=='-') {
        s=2; i++;
    }else s=0;

    l=strlen(lex);

    if(s==1)
        for( ; i<l; i++){
            if(isdigit(lex[i]))
                s=1;
            else if(lex[i]=='.') {
                s=2; i++;
                break;
            }else {
                s=0;
                break;
            }
        }
    if(s==2)
        if(isdigit(lex[i])) {
            s=3; i++;
        }
        else
            s=0;

    if(s==3)
        for(; i<l; i++) {
            if(isdigit(lex[i]))
                s=3;
            else {
                s=0;
                break;
            }
        }
        if(s==3) s=1;
    return s;
}
void LexicalAnalysis()
{
printf("\n\n\n Lexical Analysis:");
    stepOne();

    stepTwo();

    return 0;
}
