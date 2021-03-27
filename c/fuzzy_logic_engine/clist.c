#include <stdio.h>
#include <stdlib.h>
#include "clist.h"
#include "cstring.h"

#define FLT_MAX         3.402823466e+38F

inode * InitInode( float number )
{
    inode * iptr = malloc( sizeof(inode) );
    iptr->next = NULL;
    iptr->number = number;

    return iptr;
}

void FreeInode( inode * iptr )
{
    free(iptr);
    iptr = NULL;
}

void AddInode( clist * self, inode * iptr )
{
    inode * cur = NULL;

    cur = self->first;
    if ( cur == NULL )
    {
        self->first = iptr;
        self->count++;
        return ;
    }
    while ( cur->next != NULL )
        cur = cur->next;
    cur->next = iptr;
    self->count++;
}

clist * InitClist( float * values, int count )
{
    clist * cptr = NULL;
    int i = 0;

    cptr = malloc( sizeof(clist) );
    cptr->first = NULL;
    cptr->count = 0;
    if ( count > 0 )
        for ( i = 0; i < count; i++ )
            ClistAppend( cptr, values[i] );

    return cptr;
}

void FreeClist( clist * cptr )
{
    inode * sptr = NULL;
    inode * next = NULL;

    if ( cptr != NULL )
    {
        sptr = cptr->first;
        while ( sptr != NULL )
        {
            next = sptr->next;
            FreeInode(sptr);
            sptr = next;
        }
        free(cptr);
        cptr = NULL;
    }
    return ;
}

void SetClist( clist ** target, clist * source )
{
    inode * cur = NULL;
    int count = source->count;

    if ( count == 0 )
        return ;
    if ( *target == source )
        return ;
    *target = InitClist( NULL, 0 );
    for ( cur = source->first; cur != NULL; cur = cur->next )
        ClistAppend( *target, cur->number );
}

void ClistAppend( clist * List, float number )
{
    inode * iptr = NULL;
    inode * cur = NULL;

    iptr = InitInode( number );
    cur = List->first;
    if ( cur == NULL )
        List->first = iptr;
    else
    {
        for ( ; cur->next != NULL; cur = cur->next );
        cur->next = iptr;
    }
    List->count++;
}

inode * ClistDel( clist * list, int place )
{
    inode * cur = NULL;
    int length = -1;
    int i = 1;
    inode * iptr = NULL;
    inode * tmpNode = NULL;

    if ( list == NULL )
        return NULL;

    cur = list->first;
    length = list->count;
    if ( cur == NULL )
        return NULL;
    if ( length < place )
        return NULL;

    if ( place == 1 )
    {
        tmpNode = cur->next;
        cur->next = NULL;
        list->first = tmpNode;
        list->count -= 1;
        return cur;
    }
    while ( i + 1 < place )
    {
        cur = cur->next;
        i++;
    }
    tmpNode = cur->next;
    cur->next = tmpNode->next;
    tmpNode->next = NULL;
    iptr = tmpNode;
    list->count -= 1;
    return iptr;
}

void ClistSort( clist * List )
{
    int count = List->count;
    inode * i1 = NULL;
    inode * i2 = NULL;
    inode * i3 = NULL;
    inode * i4 = NULL;
    int i = 0;
    int j = 0;
    int k = 0;
    float temp = 0;
    float array[4] = { 0, 0, 0, 0 };
    int maxi = 3;
    int maxj = 4;

    switch ( count )
    {
    case 2:
        i1 = List->first;
        i2 = i1->next;
        if ( i1->number > i2->number )
        {
            temp = i1->number;
            i1->number = i2->number;
            i2->number = temp;
        }
        break;
    case 3:
        i1 = List->first;
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
        i1 = List->first;
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
        printf("ERROR!\n");
        exit(0);
    }
}

float ClistMax( clist * List )
{
    inode * cur = List->first;
    float maxValue = 0;
    float curNumber = 0;

    if ( cur == NULL )
        return -1;
    maxValue = cur->number;
    while ( cur != NULL )
    {
        curNumber = cur->number;
        if ( maxValue < curNumber )
            maxValue = cur->number;
        cur = cur->next;
    }

    return maxValue;
}

float ClistMin( clist * List )
{
    inode * cur = List->first;
    float minValue = 0;
    float curNumber = 0;

    if ( cur == NULL )
        return -1;
    curNumber = cur->number;
    minValue = cur->number;
    while ( cur != NULL )
    {
        if ( minValue > cur->number )
            minValue = cur->number;
        cur = cur->next;
    }

    return minValue;
}

float GetInodeNum( clist * self, int key )
{
    inode * cur = self->first;
    int i = 0;
    float curNumber = 0;

    for ( i = 0; i < key; i++ )
        cur = cur->next;
    curNumber = cur->number;
    return curNumber;
}

char * GetClist( clist * self )
{
    cstring * cstr = InitCstring( "[" );
    char * str = NULL;
    int i = 0;
    int count = self->count;
    int commaPlace = 0;

    for ( i = 0; i < count; i++ )
    {
        Cstradd( &cstr, NumtoStr( GetInodeNum( self, i ) ) );
        commaPlace = count - 1;
        if ( i < commaPlace )
            Cstradd( &cstr, ", " );
    }
    Cstradd( &cstr, "]" );
    str = CstrtoStr( cstr );
    FreeCstring( &cstr );
    return str;
}

float Sum( clist * List )
{
    inode * iptr = NULL;
    float result = 0;
    float iptrNumber = 0;

    for ( iptr = List->first; iptr != NULL; iptr = iptr->next )
    {
        iptrNumber = iptr->number;
        result += iptrNumber;
    }

    return result;
}

float Mul( clist * List )
{
    inode * iptr = NULL;
    float result = 1;
    float iptrNumber = 0;

    for ( iptr = List->first; iptr != NULL; iptr = iptr->next )
    {
        iptrNumber = iptr->number;
        result *= iptrNumber;
    }

    return result;
}

float MulSum( clist * List1, clist * List2 )
{
    inode * i1ptr = NULL;
    inode * i2ptr = NULL;
    float temp = 0;
    float result = 0;

    for ( i1ptr = List1->first, i2ptr = List2->first; i1ptr != NULL && i2ptr != NULL; i1ptr = i1ptr->next, i2ptr = i2ptr->next )
    {
        temp = i1ptr->number * i2ptr->number;
        result += temp;
    }

    return result;
}

float SumMul( clist * List1, clist * List2 )
{
    inode * i1ptr = NULL;
    inode * i2ptr = NULL;
    float temp = 0;
    float result = 1;

    for ( i1ptr = List1->first, i2ptr = List2->first; i1ptr != NULL && i2ptr != NULL; i1ptr = i1ptr->next, i2ptr = i2ptr->next )
    {
        temp = i1ptr->number + i2ptr->number;
        result *= temp;
    }

    return result;
}
