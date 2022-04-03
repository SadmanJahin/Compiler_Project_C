#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int slCount=1;
float value[100];
char name[100][30];
char idType[100][30];
char dataType[100][30];
char scope[100][30];
int globalFlag=1;
int functionFlag=0;
int assignFlag=0;
char functionInUse[20];
int bracketCount=-5;
int bracketStarted=0;

float default_value=-99999;
void initialize()
{
    int i=0;
    for(i=1; i<17; i++)
    {
        strcpy(idType[i],"var");
    }
    for(i=1; i<17; i++)
    {
        value[i]=default_value;
    }
}

void insert()
{

}

void Update(int k,int m)
{

    if(idType[k][0]<idType[m][0])
        strcpy(idType[k],idType[m]);
    else
        strcpy(idType[m],idType[k]);

    if(dataType[k][0]<dataType[m][0])
        strcpy(dataType[k],dataType[m]);
    else
        strcpy(dataType[m],dataType[k]);

    strcpy(scope[k],scope[m]);

    value[k]=value[m];


}
void Dump(int j)
{
    for(j; j<17; j++)
    {
        strcpy(name[j],name[j+1]);
        strcpy(idType[j],idType[j+1]);
        strcpy(dataType[j],dataType[j+1]);
        strcpy(scope[j],scope[j+1]);
        value[j]=value[j+1];
    }
}
void Delete()
{
    int i=0,j;
    for(i=1; i<17; i++)
        for(j=i+1; j<17; j++)
        {
            if(strcmp(name[i],name[j])==0 && strcmp(scope[i],scope[j])==0)
            {
                Update(i,j);
                Dump(j);

            }
        }
}
void display()
{

    printf("\n Step 2:\n\nSymbol Table :\n");
    printf("SL NO\t");
    printf("Name\t");
    printf("Id Type\t");
    printf("Data Type\t");
    printf("Scope \t");
    printf("Value \t");
    printf("\n");


    int i=0;
    for(i=1; i<17; i++)
    {

        int isEmpty=name[i][0]*dataType[i][0];
//printf("%d",isEmpty);
        if(!isEmpty)
        {
            continue;
        }

        printf("%d \t",i);
        printf("%s \t",name[i]);
        printf("%s \t",idType[i]);
        printf("%s \t\t",dataType[i]);
        printf("%s \t",scope[i]);
        if(value[i]==default_value)
        {
            printf(" ");
        }
        else if(strstr(dataType[i],"int"))
            printf("%.0f \t",value[i]);
        else
            printf("%.3f \t",value[i]);
        printf("\n");
    }
    writeOnFile();
}

char lastScope[40];
int searchforId(char* idName)
{

    if(strlen(lastScope)!=0)
    {
        int p;
        for(p=1; p<17; p++)
        {
            if(strcmp(scope[p],lastScope)==0 && strcmp(name[p],idName)==0)
            {
                return p;
            }
        }
    }

    int i=0;
    for(i=1; i<17; i++)
    {



        if(strcmp(name[i],idName)==0)
        {
            strcpy(lastScope,scope[i]);
            return i;
        }

    }
    return -1;
}

void writeOnFile()
{
    FILE * p4;
    p4=fopen("symboltable.txt","w");

    fprintf(p4,"Symbol Table :\n");
    fprintf(p4,"SL NO\t");
    fprintf(p4,"Name\t");
    fprintf(p4,"Id Type\t");
    fprintf(p4,"Data Type\t");
    fprintf(p4,"Scope \t");
    fprintf(p4,"Value \t");
    fprintf(p4,"\n");


    int i=0;
    for(i=1; i<17; i++)
    {

        int isEmpty=name[i][0]*dataType[i][0];

        if(!isEmpty)
        {
            continue;
        }

        fprintf(p4,"%d \t",i);
        fprintf(p4,"%s \t",name[i]);
        fprintf(p4,"%s \t",idType[i]);
        fprintf(p4,"%s \t\t",dataType[i]);
        fprintf(p4,"%s \t",scope[i]);
        fprintf(p4,"%.3f \t",value[i]);
        fprintf(p4,"\n");
    }

}


void CreateSymbolTable()
{
    printf("\n\n Symbol Table Generation: \n");
    initialize();


    char c;
    int i=0;


    char input[500],modifedInput[700];

    FILE *p1,*p2,*p3;
    p1=fopen("output2.txt","r");
    p2=fopen("output3.txt","w");
    if(!p2)printf("\n File Can not be opened");


    while((c=fgetc(p1))!=EOF)
    {
        input[i]=c;
        i++;
    }
    input[i]='\0';
    // puts(input);

    //for(i=0;i<len(input);i++)
    int nextToken=0;
    char * token = strtok(input, " ");

    while( token != NULL )
    {
        if(strstr(token,"id"))
        {
            fprintf(p2,"%s ",token);
            nextToken=1;
        }
        else if(nextToken==1)
        {
            fprintf(p2,"%s ",token);
            nextToken=0;
        }
        else
        {
            if(strstr(token,"kw")|| strstr(token,"op") || strstr(token,"num") || strstr(token,"sep") || strstr(token,"par") || strstr(token,"brc") )
            {
                fprintf(p2,"[");
                token = strtok(NULL, " ");
                fprintf(p2,"%s ",token);
            }
        }

        token = strtok(NULL, " ");
    }
    fclose(p2);


    p3=fopen("output3.txt","r");
    i=0;
    while((c=fgetc(p3))!=EOF)
    {
        modifedInput[i]=c;
        i++;
    }
    modifedInput[i]='\0';
    printf("\n Step 1: \n\n");
    puts(modifedInput);

    token = strtok(modifedInput, "[");

    while( token != NULL )
    {
        // printf("%s",token);
        if(strstr(token,"float"))
        {

            strcpy(dataType[slCount],"float");

        }
        if(strstr(token,"double"))
        {

            strcpy(dataType[slCount],"double");

        }

        if(strstr(token,"int"))
        {

            strcpy(dataType[slCount],"int");

        }

        if(strstr(token,"main"))
        {
            strcpy(dataType[slCount],"int");
            strcpy(idType[slCount],"func");
            functionFlag=1;
            globalFlag=0;
            token = strtok(NULL, "[");
            token = strtok(NULL, "[");
            token = strtok(NULL, "[");
            token = strtok(NULL, "[");
            strcpy(functionInUse,"main");
            //printf("%s",token);
            strcpy(name[slCount],"main");
            slCount++;

        }
        if(strstr(token,"return"))
        {

            token = strtok(NULL, ";");
            token = strtok(NULL, "]");

            continue;
        }


        if( strstr(token,"{") )
        {
            if(bracketCount==-5)
            {
                bracketCount=0;
                bracketStarted=1;
            }


            bracketCount++;

        }
        if( strstr(token,"}") )
        {
            bracketCount--;

        }
        if(bracketCount==0 && bracketStarted==1)
        {
            globalFlag=1;
            functionFlag=0;
            bracketStarted=0;

        }
        if(globalFlag==1)
        {
            strcpy(scope[slCount],"global");
        }

        if(strstr(token,"="))
        {
            assignFlag=1;
            token = strtok(NULL, "]");
            continue;
        }

        if(assignFlag==1)
        {

            float temp = atof(token);
            value[slCount]=temp;
            assignFlag=0;
        }

        if(strstr(token,"id"))
        {
            char temp[20];
            int flag=0,j=0;

            for(i=0; i<strlen(token)-1; i++)
            {

                if(token[i]==' ')
                {
                    flag=1;

                }
                if(flag==1)
                {
                    temp[j]=token[i+1];
                    j++;
                }

            }
            temp[j-2]='\0';
            //printf("%s",temp);
            strcpy(name[slCount],temp);

        }

        if(strstr(token,";") || strstr(token,"(" ) || strstr(token,")"))
        {
            slCount+=1;


        }
        if( strstr(token,"(") )
        {
            functionFlag=1;
            globalFlag=0;
            strcpy(functionInUse,name[slCount-1]);
            strcpy(idType[slCount-1],"func");
        }

        if(functionFlag==1)
        {
            strcpy(scope[slCount],functionInUse);

        }



        token = strtok(NULL, "[");
    }
    // display();

    Delete();
    display();


    p3=fopen("output3.txt","r");
    i=0;
    while((c=fgetc(p3))!=EOF)
    {
        modifedInput[i]=c;
        i++;
    }
    modifedInput[i]='\0';


    //puts(modifedInput

    printf("\n\n Step 3: \n\n");


    token = strtok(modifedInput, "[");

    while( token != NULL )
    {
        if(strstr(token,"id") && !strstr(token,"void"))
        {

            char idName[15]="0";
            int started=0;
            int j=0;
            printf("[");
            for(i=0; i<strlen(token)-2; i++)
            {
                if(started==0)
                    printf("%c",token[i]);
                if(token[i]==' ')
                {
                    started=1;
                    continue;
                }
                if(started==1)
                {
                    idName[j]=token[i];
                    j++;
                }

            }

            int value=searchforId(idName);
            printf("%d] ",value);
        }
        else
        {
            printf("[%s",token);
        }

        token = strtok(NULL, "[");
    }

    return 0;

}



