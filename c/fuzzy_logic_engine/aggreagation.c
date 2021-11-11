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
    {
        char * source1 = "Set Degree of consequent as the minimum between the degrees of truth of antecedents";

        cstring * str1 = NULL;
        int i1 = 0;
        snode * sptr1 = NULL;
        snode * cur1 = NULL;

        str1 = malloc( sizeof(cstring) );
        if ( source1 == NULL )
        {
            str1->first = NULL;
            str1->count = 0;
        }
        else
        {
            sptr1 = InitSnode(source1[0]);
            str1->first = cur1 = sptr1;
            for ( i1 = 1; source1[i1] != '\0'; i1++ )
            {
                sptr1 = InitSnode(source1[i1]);
                cur1->next = sptr1;
                cur1 = sptr1;
            }
            str1->count = i1;
        }

        self->description = str1;
        break;
    }
    case 2:
    {
        char * source2 = "Set Degree of consequent as the maximum between the degrees of truth of antecedents";

        cstring * str2 = NULL;
        int i2 = 0;
        snode * sptr2 = NULL;
        snode * cur2 = NULL;

        str2 = malloc( sizeof(cstring) );
        if ( source2 == NULL )
        {
            str2->first = NULL;
            str2->count = 0;
        }
        else
        {
            sptr2 = InitSnode(source2[0]);
            str2->first = cur2 = sptr2;
            for ( i2 = 1; source2[i2] != '\0'; i2++ )
            {
                sptr2 = InitSnode(source2[i2]);
                cur2->next = sptr2;
                cur2 = sptr2;
            }
            str2->count = i2;
        }

        self->description = str2;
        break;
    }
    case 3:
    {
        char * source3 = "Set Degree of consequent as the avarage of the degrees of truth of antecedents";

        cstring * str3 = NULL;
        int i3 = 0;
        snode * sptr3 = NULL;
        snode * cur3 = NULL;

        str3 = malloc( sizeof(cstring) );
        if ( source3 == NULL )
        {
            str3->first = NULL;
            str3->count = 0;
        }
        else
        {
            sptr3 = InitSnode(source3[0]);
            str3->first = cur3 = sptr3;
            for ( i3 = 1; source3[i3] != '\0'; i3++ )
            {
                sptr3 = InitSnode(source3[i3]);
                cur3->next = sptr3;
                cur3 = sptr3;
            }
            str3->count = i3;
        }

        self->description = str3;
        break;
    }
    case 4:
    {
        char * source4 = "Set Degree of consequent using one of the values in the vector";

        cstring * str4 = NULL;
        int i4 = 0;
        snode * sptr4 = NULL;
        snode * cur4 = NULL;

        str4 = malloc( sizeof(cstring) );
        if ( source4 == NULL )
        {
            str4->first = NULL;
            str4->count = 0;
        }
        else
        {
            sptr4 = InitSnode(source4[0]);
            str4->first = cur4 = sptr4;
            for ( i4 = 1; source4[i4] != '\0'; i4++ )
            {
                sptr4 = InitSnode(source4[i4]);
                cur4->next = sptr4;
                cur4 = sptr4;
            }
            str4->count = i4;
        }

        self->description = str4;
        break;
    }
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
