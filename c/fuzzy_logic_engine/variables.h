#ifndef VARIABLES_H_INCLUDED
#define VARIABLES_H_INCLUDED

#include "cstring.h"
#include "clist.h"
#include "cdict.h"

typedef struct fuzzyset
{
    cstring * name;
    clist * values;
} Fuzzyset;

Fuzzyset * InitFuzzyset( clist * values, char * name );
void FreeFuzzyset( Fuzzyset * self );
cdict * getDictOfFuzzyset( Fuzzyset * self );

typedef struct triangularFuzzyset
{
    cstring * name;
    cstring * shape;
    clist * values;
} TriangularFuzzyset;

TriangularFuzzyset * InitTriangularFuzzyset( clist * values, char * name );
void FreeTriangularFuzzyset( TriangularFuzzyset * self );
char * __str__TriangularFuzzyset( TriangularFuzzyset * self );
cdict * getDictOfTriangularFuzzyset( TriangularFuzzyset * self );
float degreeOfTriangularFuzzyset( TriangularFuzzyset * self, float crisp );
float center_of_gravity_OfTriangularFuzzyset( TriangularFuzzyset * self, float degree );
float areaOfTriangularFuzzyset( TriangularFuzzyset * self, float degree );

typedef struct trapezioidalFuzzyset
{
    cstring * name;
    cstring * shape;
    clist * values;
} TrapezioidalFuzzyset;

TrapezioidalFuzzyset * InitTrapezioidalFuzzyset( clist * values, char * name );
void FreeTrapezioidalFuzzyset( TrapezioidalFuzzyset * self );
char * __str__TrapezioidalFuzzyset( TrapezioidalFuzzyset * self );
cdict * getDictOfTrapezioidalFuzzyset( TrapezioidalFuzzyset * self );
float degreeOfTrapezioidalFuzzyset( TrapezioidalFuzzyset * self, float crisp );
float center_of_gravity_OfTrapezioidalFuzzyset( TrapezioidalFuzzyset * self, float degree );
float areaOfTrapezioidalFuzzyset( TrapezioidalFuzzyset * self, float degree );

typedef struct gaussianFuzzySet
{
    cstring * name;
    cstring * shape;
    float average;
    float variance;
} GaussianFuzzySet;

GaussianFuzzySet * InitGaussianFuzzySet( clist * values, char * name );
void FreeGaussianFuzzyset( GaussianFuzzySet * self );
char * __str__GaussianFuzzySet( GaussianFuzzySet * self );
cdict * getDictOfGaussianFuzzySet( GaussianFuzzySet * self );
float degreeOfGaussianFuzzySet( GaussianFuzzySet * self, float crisp );

typedef struct _fnode
{
    cstring * name;
    Fuzzyset * fuzzy_set;
    TriangularFuzzyset * triangular_fuzzy_set;
    TrapezioidalFuzzyset * trapezioidal_fuzzy_set;
    GaussianFuzzySet * gaussian_fuzzy_set;
    struct _fnode * next;
} fnode;

fnode * InitFnode( void );
void FlushFnode( fnode * self );
void FreeFnode( fnode * self );
void SetFnodeTriangular( fnode * self, TriangularFuzzyset * triangular_fuzzy_set, cstring * name );
void SetFnodeTrapezioidal( fnode * self, TrapezioidalFuzzyset * trapezioidal_fuzzy_set, cstring * name );
void SetFnodeGaussian( fnode * self, GaussianFuzzySet * gaussian_fuzzy_set, cstring * name );
char * __str__Fnode( fnode * self );
int __lt__( fnode * self, fnode * afnode );
int __le__( fnode * self, fnode * afnode );
int __gt__( fnode * self, fnode * afnode );
int __ge__( fnode * self, fnode * afnode );
int __eq__( fnode * self, fnode * afnode );
int __ne__( fnode * self, fnode * afnode );

typedef struct fuzzysets
{
    fnode * first;
    int count;
} Fuzzysets;

Fuzzysets * InitFuzzysets( void );
void FreeFuzzysets( Fuzzysets * self );
void AddFnode( Fuzzysets * self, fnode * fptr );
fnode * FindFnode( Fuzzysets * self, cstring * name );

typedef struct fuzzyVariable
{
    cstring * name;
    float max_value;
    float min_value;
    Fuzzysets * fuzzy_sets;
} FuzzyVariable;

void addFuzzyset( FuzzyVariable * self, cstring * name, clist * values );
int editFuzzyset( FuzzyVariable * self, cstring * name, clist * values );
FuzzyVariable * InitFuzzyVariable( char * name );
void FreeFuzzyVariable( FuzzyVariable * self );
float degreeOfFuzzyVariable( FuzzyVariable * self, float c, cstring * fuzzy_set );
cdictlist * get_fuzzysets( FuzzyVariable * self );
cdict * get_degrees( FuzzyVariable * self, float c );
char * __str__FuzzyVariable( FuzzyVariable * self );
cdictdict * getDictOfFuzzyVariable( FuzzyVariable * self );

FuzzyVariable * InitFuzzyBooleanVariable( char * name );

#endif // VARIABLES_H_INCLUDED
