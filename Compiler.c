#include <stdio.h>
#include "Filtering.h"
#include "Lexical_Analysis.h"
#include "SymbolTable.h"
#include "SyntaxAnalysis.h"
#include "CFG_Parser.h"

int main(void)
{

    char fileName[40]="input1.c";

    Filter(fileName);
    LexicalAnalysis();
    CreateSymbolTable();
    FindSyntaxError();
    Execute_Parsing();

}
