#include <stdlib.h>
#include "defuzzification.h"
#include "cstring.h"
#include "clist.h"

DefuzzyMethod * InitDefuzzyMethod( void )
{
    DefuzzyMethod * self = malloc( sizeof(DefuzzyMethod) );
    return self;
}

void FreeDefuzzyMethod( DefuzzyMethod * self )
{
    if ( self != NULL )
    {
        free(self);
        self = NULL;
    }
    return ;
}

DefuzzyCenterOfGravity * InitDefuzzyCenterOfGravity( void )
{
    DefuzzyCenterOfGravity * self = malloc( sizeof(DefuzzyCenterOfGravity) );

    char * source = "Uses center of gravity to define a crisp value for the fuzzy variable";

    cstring * str = NULL;
    int i = 0;
    snode * sptr = NULL;
    snode * cur = NULL;

    str = malloc( sizeof(cstring) );
    if ( source == NULL )
    {
        str->first = NULL;
        str->count = 0;
    }
    else
    {
        sptr = InitSnode(source[0]);
        str->first = cur = sptr;
        for ( i = 1; source[i] != '\0'; i++ )
        {
            sptr = InitSnode(source[i]);
            cur->next = sptr;
            cur = sptr;
        }
        str->count = i;
    }

    self->description = str;

    self->type = InitCstring("CENTER OF GRAVITY");
    return self;
}

void FreeDefuzzyCenterOfGravity( DefuzzyCenterOfGravity * self )
{
    if ( self != NULL )
    {
        FreeCstring(&(self->description));
        FreeCstring(&(self->type));
        free(self);
        self = NULL;
    }
    return ;
}

char * getType( DefuzzyCenterOfGravity * d )
{
    return "DefuzzyCenterOfGravity()";
}

int CallDefuzzyCenterOfGravity( FuzzyVariable * variable,  cdict * degrees )
{
    clist * center1 = NULL;
    clist * center2 = NULL;
    dnode * cur = NULL;
    fnode * fptr = NULL;
    float center_of_gravity = -1;
    float area = -1;
    float weighted_sum_of_centers = -1;
    float weights_sum = -1;
    float weighted_avarage = -1;

    center1 = InitClist(NULL, 0);
    center2 = InitClist(NULL, 0);
    cur = degrees->first;
    for ( cur = degrees->first; cur != NULL; cur = cur->next )
    {
        if ( cur->degree > 0 )
        {
            fptr = FindFnode( variable->fuzzy_sets, cur->name );
            if ( fptr->triangular_fuzzy_set != NULL )
            {
                center_of_gravity = center_of_gravity_OfTriangularFuzzyset( fptr->triangular_fuzzy_set, cur->degree );
                area = areaOfTriangularFuzzyset( fptr->triangular_fuzzy_set, cur->degree );
            }
            else if ( fptr->trapezioidal_fuzzy_set != NULL )
            {
                center_of_gravity = center_of_gravity_OfTrapezioidalFuzzyset( fptr->trapezioidal_fuzzy_set, cur->degree );
                area = areaOfTrapezioidalFuzzyset( fptr->trapezioidal_fuzzy_set, cur->degree );
            }
            ClistAppend( center1, center_of_gravity );
            ClistAppend( center2, area );
        }
    }
    weighted_sum_of_centers = MulSum( center1, center2 );
    weights_sum = Sum(center2);
    if ( weights_sum != 0 )
        weighted_avarage = weighted_sum_of_centers / weights_sum;

    return weighted_avarage;
}

char * __str__DefuzzyCenterOfGravity( DefuzzyCenterOfGravity * d )
{
    return "CENTER OF GRAVITY: Uses center of gravity to define a crisp value for the fuzzy variable";
}
