#ifndef AGGREAGATION_H_INCLUDED
#define AGGREAGATION_H_INCLUDED

#include "cstring.h"

float ArrayMax( float * values, int len );
float ArrayMin( float * values, int len );
float ArraySum( float * values, int len );
float ArrayMul( float * values, int len );
float RandomChoice( float * values, int len );

typedef struct _Aggregate
{
    cstring * description;
    int kind; // 0-Method, 1-Min, 2-Max, 3-Avarage, 4-Random
} Aggregate;

char * getTypeOfAggregate( Aggregate * self );
Aggregate * InitAggregate( int kind );
void FreeAggregate( Aggregate * self );
float __call__Aggregate( Aggregate * self, float * vector, int len );
char * __str__Aggregate( Aggregate * self );

#endif // AGGREAGATION_H_INCLUDED
