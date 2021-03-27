#include <stdio.h>
#include <stdlib.h>
#include "cstring.h"
#include "clist.h"
#include "cdict.h"
#include "defuzzification.h"
#include "aggreagation.h"
#include "variables.h"

int main(void)
{
    float array1[4] = { 1, 5, 6, 10 }, array2[3] = { 3, 4, 5 };
    float count1 = 4, count2 = 3;
    cdictdict * cptr;
    //TrapezioidalFuzzyset * self1 = InitTrapezioidalFuzzyset( InitClist(array1, count1), "Tra" );
    //TriangularFuzzyset * self2 = InitTriangularFuzzyset( InitClist(array2, count2), "Tri" );
    Fuzzysets * sets = InitFuzzysets();
    fnode * fptr = InitFnode();
    FuzzyVariable * variable = InitFuzzyVariable( "BABA" );

    addFuzzyset( variable, InitCstring("Tra"), InitClist( array1, count1 ) );
    addFuzzyset( variable, InitCstring("Tri"), InitClist( array2, count2 ) );
    //printf("%s\n", GetCdict(get_degrees(variable, 4)) );
    //printf("%s\n", GetCdictlist( get_fuzzysets(variable) ));
    cptr = getDictOfFuzzyVariable(variable);
    printf("%s\n", GetCdictdict( cptr ));

    return 0;
}
