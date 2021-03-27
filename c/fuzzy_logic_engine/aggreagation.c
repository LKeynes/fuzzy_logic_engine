#include "cstring.h"
#include "clist.h"
#include "cdict.h"
#include "aggreagation.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

float ArrayMax( float * values, int len )
{
    float maxValue = values[0];
    int i = 0;

    while ( i < len )
    {
        if ( values[i] > maxValue )
            maxValue = values[i];
        i++;
    }

    return maxValue;
}

float ArrayMin( float * values, int len )
{
    float minValue = values[0];
    int i = 0;

    while ( i < len )
    {
        if ( values[i] < minValue )
            minValue = values[i];
        i++;
    }

    return minValue;
}

float ArraySum( float * values, int len )
{
    int i = 0;
    float result = 0;

    for ( i = 0; i < len; i++ )
        result += values[i];

    return result;
}

float ArrayMul( float * values, int len )
{
    int i = 0;
    float result = 1;

    for ( i = 0; i < len; i++ )
        result *= values[i];

    return result;
}

float RandomChoice( float * values, int len )
{
    srand((unsigned)time(NULL));
    return values[ rand() % len ];
}

char * getTypeOfAggregate( Aggregate * self )
{
    switch (self->kind)
    {
    case 0:
        return NULL;
    case 1:
        return "AggregateMin()";
        break;
    case 2:
        return "AggregateMax()";
        break;
    case 3:
        return "AggregateAvarage()";
        break;
    case 4:
        return "AggregateRandom()";
        break;
    default:
        return NULL;
    }
}

Aggregate * InitAggregate( int kind )
{
    Aggregate * self = malloc( sizeof(Aggregate) );
    self->kind = kind;
    switch (self->kind)
    {
    case 0:
        break;
    case 1:
        self->description = InitCstring( "Set Degree of consequent as the minimum between the degrees of truth of antecedents" );
        break;
    case 2:
        self->description = InitCstring( "Set Degree of consequent as the maximum between the degrees of truth of antecedents" );
        break;
    case 3:
        self->description = InitCstring( "Set Degree of consequent as the avarage of the degrees of truth of antecedents" );
        break;
    case 4:
        self->description = InitCstring( "Set Degree of consequent using one of the values in the vector" );
        break;
    default:
        printf("ERROR!");
        exit(0);
    }
    return self;
}

void FreeAggregate( Aggregate * self )
{
    if ( self != NULL )
    {
        FreeCstring(&(self->description));
        free(self);
        self = NULL;
    }
    return ;
}

float __call__Aggregate( Aggregate * self, float * vector, int len )
{
    float result = 0;

    switch (self->kind)
    {
    case 0:
        result = -1;
        break;
    case 1:
        result = ArrayMin( vector, len );
        break;
    case 2:
        result = ArrayMax( vector, len );
        break;
    case 3:
        result = ArraySum( vector, len ) / len;
        break;
    case 4:
        result = RandomChoice( vector, len );
        break;
    default:
        printf("ERROR!");
        exit(0);
    }

    return result;
}

char * __str__Aggregate( Aggregate * self )
{
    switch (self->kind)
    {
    case 0:
        return NULL;
    case 1:
        return "AggregateMin(): Set Degree of consequent as the minimum between the degrees of truth of antecedents";
        break;
    case 2:
        return "AggregateMax(): Set Degree of consequent as the maximum between the degrees of truth of antecedents";
        break;
    case 3:
        return "AggregateAvarage(): Set Degree of consequent as the avarage of the degrees of truth of antecedents";
        break;
    case 4:
        return "AggregateRandom(): Set Degree of consequent using one of the values in the vector";
        break;
    default:
        return NULL;
    }
}
