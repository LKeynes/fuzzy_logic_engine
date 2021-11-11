#include <stdlib.h>
#include <math.h>
#include "clist.h"
#include "cdict.h"
#include "cstring.h"
#include "variables.h"

#define ABS(x) ((x)>0?(x):(-(x)))

Fuzzyset * InitFuzzyset( clist * values, char * name  )
{
    Fuzzyset * self = malloc( sizeof(Fuzzyset) );
    self->values = values;

    char * source = name;

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

    self->name = str;

    return self;
}

void FreeFuzzyset( Fuzzyset * self )
{
    if ( self != NULL )
    {
        FreeCstring( &(self->name) );
        FreeClist( self->values );
        free( self );
        self = NULL;
    }
    return ;
}

cdict * getDictOfFuzzyset( Fuzzyset * self )
{
    dnode * dptr = InitDnode();
    cdict * dict = InitCdict();

    char * source = CstrtoStr(self->name);

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

    cstring * name = str;

    clist * List = InitClist( NULL, 0 );

    SetClist( &List, self->values );
    SetDnodeValues( dptr, name, List );
    AddDnode( dict, dptr );

    return dict;
}

TriangularFuzzyset * InitTriangularFuzzyset( clist * values, char * name )
{
    TriangularFuzzyset * self = malloc( sizeof(TriangularFuzzyset) );

    char * source =  "TRIANGULAR";

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

    self->shape = str;

    self->values = values;

    self->name = InitCstring(name);

    return self;
}

void FreeTriangularFuzzyset( TriangularFuzzyset * self )
{
    if ( self != NULL )
    {
        FreeCstring( &(self->name) );
        FreeCstring( &(self->shape) );
        FreeClist( self->values );
        free( self );
        self = NULL;
    }
    return ;
}

char * __str__TriangularFuzzyset( TriangularFuzzyset * self )
{
    cstring * string = NULL;
    clist * values = self->values;
    inode * node = values->first;
    int i = 0;
    char * numStr = NumtoStr( node->number );
    char * TriangularFuzzysetStr = NULL;

    char * source = CstrtoStr(self->name);

    cstring * str = NULL;
    i = 0;
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

    string = str;

    Cstradd( &string, " - " );
    Cstrcon( &string, self->shape );
    Cstradd( &string, ":\t" );
    for ( i = 0; i < 3; i++ )
    {
        Cstradd( &string, " " );
        Cstradd( &string, numStr );
        Cstradd( &string, "\t|" );
        node = node->next;
    }

    TriangularFuzzysetStr = CstrtoStr( string );
    return TriangularFuzzysetStr;
}

cdict * getDictOfTriangularFuzzyset( TriangularFuzzyset * self )
{
    cdict * dict = InitCdict();
    dnode * dptr = InitDnode();

    char * source = CstrtoStr(self->name);

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

    cstring * name = str;

    clist * List = InitClist( NULL, 0 );

    SetClist( &List, self->values );
    SetDnodeValues( dptr, name, List );
    AddDnode( dict, dptr );

    return dict;
}

float degreeOfTriangularFuzzyset( TriangularFuzzyset * self, float crisp )
{
    float c = crisp;
    clist * values = self->values;
    inode * cur = values->first;
    float v0 = 0;
    float v1 = 0;
    float v2 = 0;

    v0 = cur->number;
    cur = cur->next;
    v1 = cur->number;
    cur = cur->next;
    v2 = cur->number;

    if ( c < v0 )
        c = v0;
    else if ( c > v2 )
        c = v2;

    if ( c == v1 )
        return 1;
    else if ( c == v0 )
        return 0;
    else if ( c == v2 )
        return 0;
    else if ( c > v0 && c < v2 )
        return ( c - v0 ) / ( v1 - v0 );
    else
        return ABS( (v2 - c) / ( v1 - v2 ) );
}

float center_of_gravity_OfTriangularFuzzyset( TriangularFuzzyset * self, float degree )
{
    clist * values = self->values;
    inode * cur = values->first;
    float v0 = 0;
    float v1 = 0;
    float v2 = 0;
    float x1 = 0;
    float x2 = 0;
    float sum = 0;
    float center_of_gravity = 0;

    v0 = cur->number;
    cur = cur->next;
    v1 = cur->number;
    cur = cur->next;
    v2 = cur->number;

    x1 = v0 - degree * ( v0 - v1 );
    x2 = v2 - degree * ( v2 - v1 );

    sum = v0 + x1 + x2 + v2;
    center_of_gravity = sum / 4.0;

    return center_of_gravity;
}

float areaOfTriangularFuzzyset( TriangularFuzzyset * self, float degree )
{
    clist * values = self->values;
    inode * cur = values->first;
    float v0 = 0;
    float v1 = 0;
    float v2 = 0;
    float x1 = 0;
    float x2 = 0;
    float b1 = 0;
    float b2 = 0;
    float sum = 0;
    float area = 0;

    v0 = cur->number;
    cur = cur->next;
    v1 = cur->number;
    cur = cur->next;
    v2 = cur->number;

    if ( degree == 1.0 )
        return (v2 - v0) * 0.5;
    x1 = v0 - degree * ( v0 - v1 );
    x2 = v2 - degree * ( v2 - v1 );
    b1 = v2 - v0;
    b2 = x2 - x1;

    sum = b1 + b2;
    area = sum * degree * 0.5;

    return area;
}

TrapezioidalFuzzyset * InitTrapezioidalFuzzyset( clist * values, char * name )
{
    int orderCount = 4;

    TrapezioidalFuzzyset * self = malloc( sizeof(TrapezioidalFuzzyset) );

    char * source = name;

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

    self->name = str;

    self->shape = InitCstring( "TRAPEZIOIDAL" );
    if ( values->count == orderCount )
    {
        SetClist( &(self->values), values );

        int count = self->values->count;
        inode * i1 = NULL;
        inode * i2 = NULL;
        inode * i3 = NULL;
        inode * i4 = NULL;
        i = 0;
        int j = 0;
        int k = 0;
        float temp = 0;
        float array[4] = { 0, 0, 0, 0 };
        int maxi = 3;
        int maxj = 4;

        switch ( count )
        {
        case 2:
            i1 = self->values->first;
            i2 = i1->next;
            if ( i1->number > i2->number )
            {
                temp = i1->number;
                i1->number = i2->number;
                i2->number = temp;
            }
            break;
        case 3:
            i1 = self->values->first;
            i2 = i1->next;
            i3 = i2->next;
            if ( i1->number > i2->number )
            {
                temp = i1->number;
                i1->number = i2->number;
                i2->number = temp;
            }
            if ( i1->number > i3->number )
            {
                temp = i1->number;
                i1->number = i3->number;
                i3->number = temp;
            }
            if ( i2->number > i3->number )
            {
                temp = i2->number;
                i2->number = i3->number;
                i3->number = temp;
            }
            break;
        case 4:
            i1 = self->values->first;
            i2 = i1->next;
            i3 = i2->next;
            i4 = i3->next;
            array[0] = i1->number;
            array[1] = i2->number;
            array[2] = i3->number;
            array[3] = i4->number;
            for ( i = 0; i < maxi; i++ )
            {
                k = i;
                temp = array[i];
                for ( j = i; j < maxj; j++ )
                    if ( temp > array[j] )
                    {
                        temp = array[j];
                        k = j;
                    }
                array[k] = array[i];
                array[i] = temp;
                i1->number = array[0];
                i2->number = array[1];
                i3->number = array[2];
                i4->number = array[3];
            }
            break;
        default:
            exit(0);
        }
    }
    return self;
}

void FreeTrapezioidalFuzzyset( TrapezioidalFuzzyset * self )
{
    if ( self != NULL )
    {
        FreeCstring( &(self->name) );
        FreeCstring( &(self->shape) );
        FreeClist( self->values );
        free( self );
        self = NULL;
    }
    return ;
}

char * __str__TrapezioidalFuzzyset( TrapezioidalFuzzyset * self )
{
    cstring * string = NULL;
    clist * values = self->values;
    inode * node = values->first;
    int i = 0;
    int orderCount = 4;
    char * numStr = NULL;
    char * TrapezioidalFuzzysetStr = NULL;

    char * source = CstrtoStr(self->name);

    cstring * str = NULL;
    i = 0;
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

    string = str;

    Cstradd( &string, " - " );
    Cstrcon( &string, self->shape );
    Cstradd( &string, ":\t" );
    for ( i = 0; i < orderCount; i++ )
    {
        Cstradd( &string, " " );
        numStr = NumtoStr( node->number );
        Cstradd( &string, numStr );
        Cstradd( &string, "\t|" );
        node = node->next;
    }

    TrapezioidalFuzzysetStr = CstrtoStr( string );
    return TrapezioidalFuzzysetStr;
}

cdict * getDictOfTrapezioidalFuzzyset( TrapezioidalFuzzyset * self )
{
    dnode * dptr = InitDnode();
    cdict * dict = InitCdict();

    char * source = NULL;

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

    cstring * name = str;

    clist * List = InitClist(NULL, 0);

    SetCstring( &name, self->name );
    SetClist( &List, self->values );
    SetDnodeValues( dptr, name, List );
    AddDnode( dict, dptr );
    return dict;
}

float degreeOfTrapezioidalFuzzyset( TrapezioidalFuzzyset * self, float crisp )
{
    float c = crisp;
    clist * values = self->values;
    inode * cur = values->first;
    float v0 = 0;
    float v1 = 0;
    float v2 = 0;
    float v3 = 0;

    v0 = cur->number;
    cur = cur->next;
    v1 = cur->number;
    cur = cur->next;
    v2 = cur->number;
    cur = cur->next;
    v3 = cur->number;

    if ( c < v0 )
        c = v0;
    else if ( c > v3 )
        c = v3;

    if ( v1 <= c && c <= v2 )
        return 1;
    else if ( c == v0 )
        return 0;
    else if ( c == v3 )
        return 0;
    else if ( c < v1 )
        return ( c - v0 ) / ( v1 - v0 );
    else
        return ABS( ( v3 - c ) / ( v2 - v3 ) );
}

float center_of_gravity_OfTrapezioidalFuzzyset( TrapezioidalFuzzyset * self, float degree )
{
    clist * values = self->values;
    inode * cur = values->first;
    float v0 = 0;
    float v1 = 0;
    float v2 = 0;
    float v3 = 0;
    float x1 = 0;
    float x2 = 0;
    float sum = 0;
    float center_of_gravity = 0;

    v0 = cur->number;
    cur = cur->next;
    v1 = cur->number;
    cur = cur->next;
    v2 = cur->number;
    cur = cur->next;
    v3 = cur->number;

    x1 = v0 - degree * ( v0 - v1 );
    x2 = v3 - degree * ( v3 - v2 );

    sum = v0 + x1 + x2 + v3;
    center_of_gravity = sum / 4.0;

    return center_of_gravity;
}

float areaOfTrapezioidalFuzzyset( TrapezioidalFuzzyset * self, float degree )
{
    clist * values = self->values;
    inode * cur = values->first;
    float v0 = 0;
    float v1 = 0;
    float v2 = 0;
    float v3 = 0;
    float x1 = 0;
    float x2 = 0;
    float b1 = 0;
    float b2 = 0;
    float sum = 0;
    float area = 0;

    v0 = cur->number;
    cur = cur->next;
    v1 = cur->number;
    cur = cur->next;
    v2 = cur->number;
    cur = cur->next;
    v3 = cur->number;

    if ( degree == 1.0 )
    {
        b1 = v3 - v0;
        b2 = v2 - v1;
    }
    else
    {
        x1 = v0 - degree * ( v0 - v1 );
        x2 = v3 - degree * ( v3 - v2 );
        b1 = v3 - v0;
        b2 = x2 - x1;
    }

    sum = b1 + b2;
    area = sum * degree * 0.5;

    return area;
}

GaussianFuzzySet * InitGaussianFuzzySet( clist * values, char * name )
{
    int orderCount = 2;
    inode * firstNode = NULL;
    inode * secondNode = NULL;

    GaussianFuzzySet * self = malloc( sizeof(GaussianFuzzySet) );

    char * source = name;

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

    self->name = str;

    self->shape = InitCstring( "GAUSSIAN" );
    if ( values->count == orderCount )
    {
        firstNode = values->first;
        secondNode = firstNode->next;
        self->average = firstNode->number;
        self->variance = secondNode->number;
    }
    return self;
}

void FreeGaussianFuzzyset( GaussianFuzzySet * self )
{
    if ( self != NULL )
    {
        FreeCstring( &(self->name) );
        FreeCstring( &(self->shape) );
        free( self );
        self = NULL;
    }
    return ;
}

char * __str__GaussianFuzzySet( GaussianFuzzySet * self )
{
    cstring * string = NULL;
    char * averageStr = NULL;
    char * varianceStr = NULL;
    char * GaussianFuzzySetStr = NULL;

    char * source = CstrtoStr(self->name);

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

    string = str;

    Cstradd( &string, " - " );
    Cstrcon( &string, self->shape );
    Cstradd( &string, ":\t" );

    Cstradd( &string, " " );
    averageStr = NumtoStr(self->average);
    Cstradd( &string, averageStr );
    Cstradd( &string, "\t|" );

    Cstradd( &string, " " );
    varianceStr = NumtoStr(self->variance);
    Cstradd( &string, varianceStr );
    Cstradd( &string, "\t|" );

    GaussianFuzzySetStr = CstrtoStr( string );
    return GaussianFuzzySetStr;
}

cdict * getDictOfGaussianFuzzySet( GaussianFuzzySet * self )
{
    dnode * dptr = InitDnode();
    cdict * dict = InitCdict();

    char * source = NULL;

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

    cstring * name = str;

    float array[2] = { 0, 0 };
    clist * values = NULL;

    SetCstring( &name, self->name );
    array[0] = self->average;
    array[1] = self->variance;
    values = InitClist( array, 2 );
    SetDnodeValues( dptr, name, values );
    AddDnode( dict, dptr );

    return dict;
}

float degreeOfGaussianFuzzySet( GaussianFuzzySet * self, float crisp )
{
    float x = crisp;

    return ((1.0/(sqrt(2*3.14159)*self->variance)) * pow(2.71828, ((-0.5)* pow(((x-self->average)/self->variance), 2))));
}

fnode * InitFnode( void )
{
    fnode * self = malloc( sizeof(fnode) );
    self->fuzzy_set = NULL;
    self->triangular_fuzzy_set = NULL;
    self->trapezioidal_fuzzy_set = NULL;
    self->gaussian_fuzzy_set = NULL;
    self->name = NULL;
    self->next = NULL;
    return self;
}

void FlushFnode( fnode * self )
{
    if ( self->fuzzy_set != NULL )
        FreeFuzzyset( self->fuzzy_set );
    self->fuzzy_set = NULL;
    if ( self->triangular_fuzzy_set != NULL )
        FreeTriangularFuzzyset( self->triangular_fuzzy_set );
    self->triangular_fuzzy_set = NULL;
    if ( self->trapezioidal_fuzzy_set != NULL )
        FreeTrapezioidalFuzzyset( self->trapezioidal_fuzzy_set );
    self->trapezioidal_fuzzy_set = NULL;
    if ( self->gaussian_fuzzy_set != NULL )
        FreeGaussianFuzzyset( self->gaussian_fuzzy_set );
    self->gaussian_fuzzy_set = NULL;
    if ( self->name != NULL )
        FreeCstring( &(self->name) );
    self->name = NULL;
}

void FreeFnode( fnode * self )
{
    if ( self != NULL )
    {
        FreeFuzzyset( self->fuzzy_set );
        FreeTriangularFuzzyset( self->triangular_fuzzy_set );
        FreeTrapezioidalFuzzyset( self->trapezioidal_fuzzy_set );
        FreeGaussianFuzzyset( self->gaussian_fuzzy_set );
        FreeCstring( &(self->name) );
        free( self );
        self = NULL;
    }
    return ;
}

void SetFnodeTriangular( fnode * self, TriangularFuzzyset * triangular_fuzzy_set, cstring * name )
{
    self->triangular_fuzzy_set = triangular_fuzzy_set;
    self->name = name;
}

void SetFnodeTrapezioidal( fnode * self, TrapezioidalFuzzyset * trapezioidal_fuzzy_set, cstring * name )
{
    self->trapezioidal_fuzzy_set = trapezioidal_fuzzy_set;
    self->name = name;
}

void SetFnodeGaussian( fnode * self, GaussianFuzzySet * gaussian_fuzzy_set, cstring * name )
{
    self->gaussian_fuzzy_set = gaussian_fuzzy_set;
    self->name = name;
}

char * __str__Fnode( fnode * self )
{
    if ( self->triangular_fuzzy_set != NULL )
        return __str__TriangularFuzzyset( self->triangular_fuzzy_set );
    if ( self->trapezioidal_fuzzy_set != NULL )
        return __str__TrapezioidalFuzzyset( self->trapezioidal_fuzzy_set );
    if ( self->gaussian_fuzzy_set != NULL )
        return __str__GaussianFuzzySet( self->gaussian_fuzzy_set );
    return NULL;
}

int __lt__( fnode * self, fnode * afnode )
{
    float result1 = -1.0;
    float result2 = -1.0;

    if ( self->triangular_fuzzy_set != NULL )
        result1 = center_of_gravity_OfTriangularFuzzyset( self->triangular_fuzzy_set, 1 );
    if ( self->trapezioidal_fuzzy_set != NULL )
        result1 = center_of_gravity_OfTrapezioidalFuzzyset( self->trapezioidal_fuzzy_set, 1 );
    if ( afnode->triangular_fuzzy_set != NULL )
        result2 = center_of_gravity_OfTriangularFuzzyset( afnode->triangular_fuzzy_set, 1 );
    if ( afnode->trapezioidal_fuzzy_set != NULL )
        result2 = center_of_gravity_OfTrapezioidalFuzzyset( afnode->trapezioidal_fuzzy_set, 1 );
    if ( result1 != -1 )
    {
        if ( result2 != -1 )
            return result1 < result2;
        else
            return -1;
    }
    else
        return -1;
}

int __le__( fnode * self, fnode * afnode )
{
    float result1 = -1.0;
    float result2 = -1.0;

    if ( self->triangular_fuzzy_set != NULL )
        result1 = center_of_gravity_OfTriangularFuzzyset( self->triangular_fuzzy_set, 1 );
    if ( self->trapezioidal_fuzzy_set != NULL )
        result1 = center_of_gravity_OfTrapezioidalFuzzyset( self->trapezioidal_fuzzy_set, 1 );
    if ( afnode->triangular_fuzzy_set != NULL )
        result2 = center_of_gravity_OfTriangularFuzzyset( afnode->triangular_fuzzy_set, 1 );
    if ( afnode->trapezioidal_fuzzy_set != NULL )
        result2 = center_of_gravity_OfTrapezioidalFuzzyset( afnode->trapezioidal_fuzzy_set, 1 );
    if ( result1 != -1 )
    {
        if ( result2 != -1 )
            return result1 <= result2;
        else
            return -1;
    }
    else
        return -1;
}

int __gt__( fnode * self, fnode * afnode )
{
    float result1 = -1.0;
    float result2 = -1.0;

    if ( self->triangular_fuzzy_set != NULL )
        result1 = center_of_gravity_OfTriangularFuzzyset( self->triangular_fuzzy_set, 1 );
    if ( self->trapezioidal_fuzzy_set != NULL )
        result1 = center_of_gravity_OfTrapezioidalFuzzyset( self->trapezioidal_fuzzy_set, 1 );
    if ( afnode->triangular_fuzzy_set != NULL )
        result2 = center_of_gravity_OfTriangularFuzzyset( afnode->triangular_fuzzy_set, 1 );
    if ( afnode->trapezioidal_fuzzy_set != NULL )
        result2 = center_of_gravity_OfTrapezioidalFuzzyset( afnode->trapezioidal_fuzzy_set, 1 );
    if ( result1 != -1 )
    {
        if ( result2 != -1 )
            return result1 > result2;
        else
            return -1;
    }
    else
        return -1;
}

int __ge__( fnode * self, fnode * afnode )
{
    float result1 = -1.0;
    float result2 = -1.0;

    if ( self->triangular_fuzzy_set != NULL )
        result1 = center_of_gravity_OfTriangularFuzzyset( self->triangular_fuzzy_set, 1 );
    if ( self->trapezioidal_fuzzy_set != NULL )
        result1 = center_of_gravity_OfTrapezioidalFuzzyset( self->trapezioidal_fuzzy_set, 1 );
    if ( afnode->triangular_fuzzy_set != NULL )
        result2 = center_of_gravity_OfTriangularFuzzyset( afnode->triangular_fuzzy_set, 1 );
    if ( afnode->trapezioidal_fuzzy_set != NULL )
        result2 = center_of_gravity_OfTrapezioidalFuzzyset( afnode->trapezioidal_fuzzy_set, 1 );
    if ( result1 != -1 )
    {
        if ( result2 != -1 )
            return result1 >= result2;
        else
            return -1;
    }
    else
        return -1;
}

int __eq__( fnode * self, fnode * afnode )
{
    float result1 = -1.0;
    float result2 = -1.0;

    if ( self->triangular_fuzzy_set != NULL )
        result1 = center_of_gravity_OfTriangularFuzzyset( self->triangular_fuzzy_set, 1 );
    if ( self->trapezioidal_fuzzy_set != NULL )
        result1 = center_of_gravity_OfTrapezioidalFuzzyset( self->trapezioidal_fuzzy_set, 1 );
    if ( afnode->triangular_fuzzy_set != NULL )
        result2 = center_of_gravity_OfTriangularFuzzyset( afnode->triangular_fuzzy_set, 1 );
    if ( afnode->trapezioidal_fuzzy_set != NULL )
        result2 = center_of_gravity_OfTrapezioidalFuzzyset( afnode->trapezioidal_fuzzy_set, 1 );
    if ( result1 != -1 )
    {
        if ( result2 != -1 )
            return result1 == result2;
        else
            return -1;
    }
    else
        return -1;
}

int __ne__( fnode * self, fnode * afnode )
{
    float result1 = -1.0;
    float result2 = -1.0;

    if ( self->triangular_fuzzy_set != NULL )
        result1 = center_of_gravity_OfTriangularFuzzyset( self->triangular_fuzzy_set, 1 );
    if ( self->trapezioidal_fuzzy_set != NULL )
        result1 = center_of_gravity_OfTrapezioidalFuzzyset( self->trapezioidal_fuzzy_set, 1 );
    if ( afnode->triangular_fuzzy_set != NULL )
        result2 = center_of_gravity_OfTriangularFuzzyset( afnode->triangular_fuzzy_set, 1 );
    if ( afnode->trapezioidal_fuzzy_set != NULL )
        result2 = center_of_gravity_OfTrapezioidalFuzzyset( afnode->trapezioidal_fuzzy_set, 1 );
    if ( result1 != -1 )
    {
        if ( result2 != -1 )
            return result1 != result2;
        else
            return -1;
    }
    else
        return -1;
}

Fuzzysets * InitFuzzysets(void)
{
    Fuzzysets * self = malloc( sizeof(Fuzzysets) );
    self->count = 0;
    self->first = NULL;
    return self;
}

void FreeFuzzysets( Fuzzysets * self )
{
    fnode * cur = NULL;
    fnode * next = NULL;

    if ( self != NULL )
    {
        cur = self->first;
        while ( cur != NULL )
        {
            next = cur->next;
            FreeFnode(cur);
            cur = next;
        }
        free(self);
        self = NULL;
    }
    return ;
}

void AddFnode( Fuzzysets * self, fnode * fptr )
{
    fnode * cur = self->first;

    if ( cur == NULL )
        self->first = fptr;
    else
    {
        while ( cur->next != NULL )
            cur = cur->next;
        cur->next = fptr;
    }
    self->count++;
}

void addFuzzyset( FuzzyVariable * self, cstring * name, clist * values )
{
    fnode * fptr = NULL;
    TriangularFuzzyset * triangular_fuzzy_set = NULL;
    TrapezioidalFuzzyset * trapezioidal_fuzzy_set = NULL;
    GaussianFuzzySet * gaussian_fuzzy_set = NULL;
    inode * cur = NULL;
    float v0 = 0;
    float v1 = 0;
    float v2 = 0;
    float v3 = 0;
    clist * array = NULL;

    if ( self->max_value == -1 && self->min_value )
    {
        self->max_value = ClistMax( values );
        self->min_value = ClistMin( values );
    }
    else
    {
        if ( self->max_value < ClistMax( values ) )
            self->max_value = ClistMax( values );
        if ( self->min_value > ClistMin( values ) )
            self->min_value = ClistMin( values );
    }
    if ( values->count == 3 )
    {
        triangular_fuzzy_set = InitTriangularFuzzyset( values, CstrtoStr(name) );
        fptr = FindFnode( self->fuzzy_sets, name );
        if ( fptr != NULL )
        {
            FlushFnode( fptr );
            SetFnodeTriangular( fptr, triangular_fuzzy_set, name );
        }
        else
        {
            fptr = InitFnode();
            SetFnodeTriangular( fptr, triangular_fuzzy_set, name );
            AddFnode( self->fuzzy_sets, fptr );
        }
    }
    else if ( values->count == 4 )
    {
        cur = values->first;
        v0 = cur->number;
        cur = cur->next;
        v1 = cur->number;
        cur = cur->next;
        v2 = cur->number;
        cur = cur->next;
        v3 = cur->number;
        if ( v1 == v2 )
        {
            array = InitClist( NULL, 0 );
            ClistAppend( array, v0 );
            ClistAppend( array, v1 );
            ClistAppend( array, v3 );
            triangular_fuzzy_set = InitTriangularFuzzyset( array, CstrtoStr(name) );
            fptr = FindFnode( self->fuzzy_sets, name );
            if ( fptr != NULL )
            {
                FlushFnode( fptr );
                SetFnodeTriangular( fptr, triangular_fuzzy_set, name );
            }
            else
            {
                fptr = InitFnode();
                SetFnodeTriangular( fptr, triangular_fuzzy_set, name );
                AddFnode( self->fuzzy_sets, fptr );
            }
        }
        else
        {
            trapezioidal_fuzzy_set = InitTrapezioidalFuzzyset( values, CstrtoStr(name) );
            fptr = FindFnode( self->fuzzy_sets, name );
            if ( fptr != NULL )
            {
                FlushFnode( fptr );
                SetFnodeTrapezioidal( fptr, trapezioidal_fuzzy_set, name );
            }
            else
            {
                fptr = InitFnode();
                SetFnodeTrapezioidal( fptr, trapezioidal_fuzzy_set, name );
                AddFnode( self->fuzzy_sets, fptr );
            }
        }
    }
    else if ( values->count == 2 )
    {
        gaussian_fuzzy_set = InitGaussianFuzzySet( values, CstrtoStr(name) );
        fptr = FindFnode( self->fuzzy_sets, name );
        if ( fptr != NULL )
        {
            FlushFnode( fptr );
            SetFnodeGaussian( fptr, gaussian_fuzzy_set, name );
        }
        else
        {
            fptr = InitFnode();
            SetFnodeGaussian( fptr, gaussian_fuzzy_set, name );
            AddFnode( self->fuzzy_sets, fptr );
        }
    }
}

fnode * FindFnode( Fuzzysets * self, cstring * name )
{
    fnode * cur = self->first;

    while ( cur != NULL )
    {
        if ( !Cstrcmp( cur->name, name)  )
            return cur;
        cur = cur->next;
    }

    return cur;
}

int editFuzzyset( FuzzyVariable * self, cstring * name, clist * values )
{
    fnode * fptr = NULL;
    TriangularFuzzyset * triangular_fuzzy_set = NULL;
    TrapezioidalFuzzyset * trapezioidal_fuzzy_set = NULL;
    GaussianFuzzySet * gaussian_fuzzy_set = NULL;

    fptr = FindFnode( self->fuzzy_sets, name );
    if ( fptr != NULL )
    {
        if ( self->max_value < ClistMax( values ) )
            self->max_value = ClistMax( values );
        if ( self->min_value > ClistMin( values ) )
            self->min_value = ClistMin( values );
        if ( values->count == 3 )
        {
            triangular_fuzzy_set = InitTriangularFuzzyset( values, CstrtoStr(name) );
            FlushFnode( fptr );
            SetFnodeTriangular( fptr, triangular_fuzzy_set, name );
        }
        else if ( values->count == 4 )
        {
            trapezioidal_fuzzy_set = InitTrapezioidalFuzzyset( values, CstrtoStr(name) );
            FlushFnode( fptr );
            SetFnodeTrapezioidal( fptr, trapezioidal_fuzzy_set, name );
        }
        else if ( values->count == 2 )
        {
            gaussian_fuzzy_set = InitGaussianFuzzySet( values, CstrtoStr(name) );
            FlushFnode( fptr );
            SetFnodeGaussian( fptr, gaussian_fuzzy_set, name );
        }
        return 1;
    }
    else
        return 0;
}

FuzzyVariable * InitFuzzyVariable( char * name )
{
    FuzzyVariable * self = malloc( sizeof(FuzzyVariable) );

    char * source = name;

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

    self->name = str;

    self->max_value = -1;
    self->min_value = -1;
    self->fuzzy_sets = InitFuzzysets();
    return self;
}

void FreeFuzzyVariable( FuzzyVariable * self )
{
    if ( self != NULL )
    {
        FreeCstring(&(self->name));
        FreeFuzzysets(self->fuzzy_sets);
        free(self);
        self = NULL;
    }
    return ;
}

float degreeOfFuzzyVariable( FuzzyVariable * self, float c, cstring * fuzzy_set )
{
    float crisp = c;
    fnode * fptr = NULL;

    if ( crisp > self->max_value )
        crisp = self->max_value;
    if ( crisp < self->min_value )
        crisp = self->min_value;
    fptr = FindFnode( self->fuzzy_sets, fuzzy_set );
    if ( fptr->triangular_fuzzy_set != NULL )
        return degreeOfTriangularFuzzyset( fptr->triangular_fuzzy_set, crisp );
    if ( fptr->trapezioidal_fuzzy_set != NULL )
        return degreeOfTrapezioidalFuzzyset( fptr->trapezioidal_fuzzy_set, crisp );
    if ( fptr->gaussian_fuzzy_set != NULL )
        return degreeOfGaussianFuzzySet( fptr->gaussian_fuzzy_set, crisp );
    return -1.0;
}

cdictlist * get_fuzzysets( FuzzyVariable * self )
{
    cdictlist * lptr = NULL;
    cdictnode * cptr = NULL;
    fnode * fptr = NULL;
    Fuzzysets * fuzzy_sets = self->fuzzy_sets;

    lptr = InitCdictlist();
    fptr = fuzzy_sets->first;
    while ( fptr != NULL )
    {
        cptr = InitCdictnode();
        if ( fptr->triangular_fuzzy_set != NULL )
            SetCdictnode( cptr, getDictOfTriangularFuzzyset(fptr->triangular_fuzzy_set) );
        if ( fptr->trapezioidal_fuzzy_set != NULL )
            SetCdictnode( cptr, getDictOfTrapezioidalFuzzyset(fptr->trapezioidal_fuzzy_set) );
        if ( fptr->gaussian_fuzzy_set != NULL )
            SetCdictnode( cptr, getDictOfGaussianFuzzySet(fptr->gaussian_fuzzy_set) );
        CdictlistAddCdictnode( lptr, cptr );
        fptr = fptr->next;
    }
    CdictlistSort( lptr );

    return lptr;
}

cdict * get_degrees( FuzzyVariable * self, float c )
{
    float crisp = c;
    cdict * d = InitCdict();
    fnode * cur = NULL;
    fnode * next = NULL;
    dnode * dk = NULL;
    Fuzzysets * fuzzy_sets = self->fuzzy_sets;
    float degree = 0;
    cstring * curName = NULL;

    cur = fuzzy_sets->first;
    while ( cur != NULL )
    {
        curName = cur->name;
        next = cur->next;

        dk = InitDnode();
        degree = degreeOfFuzzyVariable( self, crisp, cur->name );
        SetDnodeDegree( dk, curName, degree );
        AddDnode( d, dk );
        cur = next;
    }

    return d;
}

char * __str__FuzzyVariable( FuzzyVariable * self )
{
    cstring * string = NULL;
    Fuzzysets * fuzzy_sets = self->fuzzy_sets;
    fnode * fptr = fuzzy_sets->first;
    int i = 0;
    int count = fuzzy_sets->count;
    char * minValueStr = NULL;
    char * maxValueStr = NULL;
    char * FuzzyVariableStr = NULL;

    char * source = NULL;

    cstring * str = NULL;
    i = 0;
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

    string = str;

    SetCstring( &string, self->name );
    Cstradd( &string, ": MIN(" );
    minValueStr = NumtoStr( self->min_value );
    Cstradd( &string, minValueStr );
    Cstradd( &string, ") - MAX(" );
    maxValueStr = NumtoStr( self->max_value );
    Cstradd( &string, NumtoStr( self->max_value ) );
    Cstradd( &string, ")" );

    for ( i = 0; i < count; i++ )
    {
        Cstradd( &string, "\n" );
        Cstradd( &string, __str__Fnode( fptr ) );
        fptr = fptr->next;
    }

    FuzzyVariableStr = CstrtoStr( string );
    return FuzzyVariableStr;
}

cdictdict * getDictOfFuzzyVariable( FuzzyVariable * self )
{
    cdictdict * d = InitCdictdict();
    fnode * fptr = NULL;
    cdictnode * ptr = InitCdictnode();
    Fuzzysets * fuzzy_sets = self->fuzzy_sets;

    SetCdictnodeDict( ptr, InitCstring( "name" ), NULL, InitCstring( CstrtoStr(self->name) ) );
    CdictdictAddCdictnode( d, ptr );
    fptr = fuzzy_sets->first;
    while ( fptr != NULL )
    {
        ptr = InitCdictnode();
        if ( fptr->fuzzy_set != NULL )
            SetCdictnodeDict( ptr, InitCstring( CstrtoStr(fptr->name) ), getDictOfFuzzyset( fptr->fuzzy_set ), NULL);
        if ( fptr->triangular_fuzzy_set != NULL )
            SetCdictnodeDict( ptr, InitCstring( CstrtoStr(fptr->name) ), getDictOfTriangularFuzzyset( fptr->triangular_fuzzy_set ), NULL);
        if ( fptr->trapezioidal_fuzzy_set != NULL )
            SetCdictnodeDict( ptr, InitCstring( CstrtoStr(fptr->name) ), getDictOfTrapezioidalFuzzyset( fptr->trapezioidal_fuzzy_set ), NULL);
        if ( fptr->gaussian_fuzzy_set != NULL )
            SetCdictnodeDict( ptr, InitCstring( CstrtoStr(fptr->name) ), getDictOfGaussianFuzzySet( fptr->gaussian_fuzzy_set ), NULL);
        CdictdictAddCdictnode( d, ptr );
        fptr = fptr->next;
    }

    return d;
}

FuzzyVariable * InitFuzzyBooleanVariable( char * name )
{
    FuzzyVariable * self = malloc( sizeof(FuzzyVariable) );
    fnode * fptr = NULL;
    float array1[3] = { 0, 1, 2 }, array2[3] = { -1, 0, 1 };
    clist * tmpClist1 = NULL;
    clist * tmpClist2 = NULL;

    char * source = name;

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

    self->name = str;

    self->max_value = 1;
    self->min_value = 0;
    self->fuzzy_sets = InitFuzzysets();
    fptr = InitFnode();
    Cstradd( &(fptr->name), "True" );
    tmpClist1 = InitClist(array1, 3);
    fptr->triangular_fuzzy_set = InitTriangularFuzzyset( InitClist(array1, 3), "True" );
    AddFnode( self->fuzzy_sets, fptr );
    fptr = InitFnode();
    Cstradd( &(fptr->name), "False" );
    tmpClist2 = InitClist(array2, 3);
    fptr->triangular_fuzzy_set = InitTriangularFuzzyset( InitClist(array2, 3), "False" );
    AddFnode( self->fuzzy_sets, fptr );
    return self;
}
