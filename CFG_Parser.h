#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char str[30];
int f = 0,len,i =0;
void loop_stat()
{
    if(str[i] == 'w' || str[i+1] == 'h'|| str[i+2] == 'i'|| str[i+3] == 'l'|| str[i+4] == 'e')
    {
        i = i+5;
        if(str[i] == '(')
        {
            i++;
            expn();
            if(str[i] == ')')
            {
                i++;
                stat();
                if(i==len)
                    return;
                else
                {
                    f = 0;
                    return;
                }

            }
            else
                return;
        }
        else
        {
            f = 0;
            return;
        }
    }
    else if(str[i] == 'f' || str[i+1] == 'o' || str[i+2] == 'r')
    {
        i = i+3;
        if(str[i] == '(')
        {
            i++;
            asgn_stat();
            if(str[i] == ';')
            {
                i++;
                expn();
                if(str[i] == ';')
                {
                    i++;
                    asgn_stat();
                    if(str[i] == ')')
                    {
                        i++;
                        stat();
                        if(i==len)
                            return;
                        else
                        {
                            f = 0;
                            return;
                        }
                    }
                    else
                    {
                        f = 0;
                        return;
                    }

                }
                else
                {
                    f = 0;
                    return;
                }
            }
            else
            {
                f = 0;
                return;
            }
        }
        else
        {
            f = 0;
            return;
        }
    }
    else
    {
        f = 0;
        return;
    }
}


void extn1()
{
    if((len-1) == i)
    {
        f = 1;
        i++;
        return;
    }
    else
    {
        if(str[i] == 'e' && str[i+1] == 'l' && str[i+2] =='s' || str[i+3] == 'e')
        {
            i=i+4;
            f=0;
            stat();
            if(f == 1)
                return;
            else
            {
                f = 0;
                return;
            }
        }
        else
        {
            f = 0;
            return;
        }
    }
}


void dscn_stat()
{
    if(str[i] == 'i')
    {
        i++;
        if(str[i] == 'f')
        {
            i++;
            if(str[i] == '(')
            {
                i++;
                expn();
                if(str[i] == ')')
                {
                    i++;
                    stat();
                    if(i==len)
                        return;
                    else
                    {
                        if(f == 1)
                        {
                            extn1();
                        }
                        else
                            return;
                        }

                }
            }
        }
    }
    else
    {
        f = 0;
        return;
    }
}
void F()
{
    if(isdigit(str[i]))
    {
        i++;
        f = 1;
        return;
    }
    else if(str[i] == 'a' || str[i] == 'b' || str[i] == 'c' || str[i] == 'd')
    {
        i++;
        f = 1;
        return;
    }
    else if(str[i] == '(')
    {
        i++;
        E();
        i++;
        if(str[i] == ')')
        {
            f = 1;
            return;
        }
    }
}


void T()
{
    F();
    if(i==len)
        return;
    if(i<len-1)
    {
        if(str[i] == '*' || str[i] == '/')
        {
            i++;
            F();
        }
        else if(f == 1)
        {
            return;
        }
    }

}

void E()
{
    T();

    if(i == len)
        return;
    if(i < len-1)
    {
        if(str[i] == '+' || str[i] == '-')
        {
            i++;
            T();
        }
        else if(f == 1)
        {
            return;
        }
    }

}

void smpl_expn()
{
    E();
    if(f == 1 && len==i)
    {
        return;
    }
    else
        return;
}

void relop()
{
    if(str[i] == '=')
    {
        i++;
        if(str[i] == '=')
        {
           f  = 1;
           return;
        }
        else
        {
            f = 0;
            return;
        }
    }
    else if(str[i] == '!')
    {
        i++;
        if(str[i] == '=')
        {
           f  = 1;
           return;
        }
        else
        {
            f = 0;
            return;
        }
    }
    else if(str[i] == '<')
    {
        i++;
        f = 1;
        if(str[i] == '=')
        {
           f  = 1;
           return;
        }
        else
        {
            return;
        }
    }
    else if(str[i] == '>')
    {
        i++;
        f = 1;
        if(str[i] == '=')
        {
           i++;
           f  = 1;
           return;
        }
        else
        {
            return;
        }
    }
    else if(str[i] == '>')
    {
        i++;
        f  = 1;
        return;
    }
    else if(str[i] == '<')
    {
        i++;
        f  = 1;
        return;
    }
    else
    {
        f = 0;
        return;
    }

}


void extn()
{
    if((len-1) == i)
    {
        f = 1;
        i++;
        return;
    }
    else
    {
        relop();
        if(f == 1)
        {
            smpl_expn();
            if(len == i)
                return;
        }
        else
            return;
    }
}


void expn()
{
    smpl_expn();
    if(len == i)
    {
        return;
    }
    else
    {

        if(f == 1)
        {
            extn();
            return;
        }

    }


}


void asgn_stat()
{
    if(str[i] == 'a' || str[i] == 'b' || str[i] == 'c'|| str[i] == 'd'|| str[i] == 'e')
    {
        i++;
        if(str[i] == '=')
        {
            i++;
            expn();
            if(f ==1 && i==len)
            {
                return;
            }
            else
            {
                f=1;
                return;
            }

        }

    }
    else
    {
        f = 0;
        return;
    }
}



void stat()
{
    int as = 0;
    asgn_stat();
    as = 1;
    if(f ==1 && (len==i))
    {
        return;
    }
    else if(f==1)
        return;

    if(as == 1 && f == 0)
    {

        dscn_stat();
        if(f == 0)
        {
            loop_stat();
        }

    }
}
void searchCFG()
{

    FILE *p1,*p2;
    char line[500],buffer[50];
    int count=0;
    p1 = fopen("output4_formated_file.txt", "r");
    p2 = fopen("cfg_found.txt", "w");

    while(fgets(line, sizeof(line), p1)) {
        if(strstr(line,"for") || strstr(line,"while"))
        {
            int i=0,startWriting=0;
            for(i=0;i<strlen(line);i++)
              {

                if(isdigit(line[i]) && startWriting==0)
                    fputc(line[i],p2);
                if(line[i]=='w'|| line[i]=='f')
                {
                    startWriting=1;


                    fputc(' ',p2);
                }
                if(startWriting && line[i]!=' ' && line[i]!=';')
                {
                   fputc(line[i],p2);
                }
            }

        }


count++;
}
fclose(p1);
fclose(p2);
}
void Execute_Parsing()
{
    printf("\n\n CFG Parsing: \n");
    searchCFG();
    char c[100];
    FILE *ptr,*p1;
    p1 = fopen("cfg_errors.txt","w");
    if ((ptr = fopen("cfg_found.txt","r")) == NULL){
        printf("Error! opening file");

    }
    int check_line,error_line;
    while(fscanf(ptr,"%s",&str)>0)
    {       char cfg[100];


             check_line=atoi(str);
             if(check_line> 0)
             {
                 error_line=check_line;
                 continue;
             }

            i = 0;
            len = strlen(str);
            if(len>=1)
                {
                    stat();
                }
            else
                fprintf(p1,"Please find another string %s.\n",str);
            if(len == i && f == 1)
                fprintf(p1,"",str);
            else
                fprintf(p1,"Error at line %d: %s is not valid.\n",error_line,str);
    }
    fclose(ptr);
    fclose(p1);
    printf("\n");
    char ch;
    p1 = fopen("cfg_errors.txt","r");
    do
    {
        ch = fgetc(p1);
        putchar(ch);
    }while(ch != EOF);

    fclose(p1);
    return 0;
}
