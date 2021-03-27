#include <stdio.h>
#include <stdlib.h>
#include "cstring.h"

snode * InitSnode( char ch )
{
    snode * ptr = NULL;

    ptr = malloc( sizeof(snode) );
    ptr->next = NULL;
    ptr->ch = ch;

    return ptr;
}

void FreeSnode( snode * self )
{
    free(self);
    self = NULL;
}

cstring * InitCstring( char * source )
{
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

    return str;
}

void Cstradd( cstring ** self, char * str )
{
    cstring * s2 = InitCstring( str );
    snode * cur = (*self)->first;

    if ( cur == NULL )
    {
        SetCstring( self, s2 );
        return ;
    }
    while ( cur->next != NULL )
        cur = cur->next;
    cur->next = s2->first;
    (*self)->count += s2->count;
}

void FreeCstring( cstring ** str )
{
    snode * sptr = NULL;
    snode * next = NULL;

    if ( str != NULL )
        if ( (*str) != NULL )
        {
            sptr = (*str)->first;
            while ( sptr != NULL )
            {
                next = sptr->next;
                FreeSnode(sptr);
                sptr = next;
            }
            free( (*str) );
            (*str) = NULL;
        }
    return ;
}

void SetCstring( cstring ** target, cstring * source )
{
    snode * sptr = NULL;
    snode * tptr = NULL;
    snode * cur = NULL;

    sptr = source->first;
    if ( sptr == NULL || !Cstrcmp( *target, source ) )
        return ;
    FreeCstring( target );
    *target = InitCstring( NULL );
    cur = InitSnode(sptr->ch);
    (*target)->first = cur;
    for ( sptr = sptr->next; sptr != NULL; sptr = sptr->next )
    {
        tptr = InitSnode(sptr->ch);
        cur->next = tptr;
        cur = tptr;
    }
    (*target)->count += source->count;
}

int Cstrcmp( cstring * s1, cstring * s2 )
{
    snode * s1ptr = s1->first;
    snode * s2ptr = s2->first;

    if ( s1->count != s2->count )
        return -1;
    while ( s1ptr != NULL )
    {
        if ( s1ptr->ch != s2ptr->ch )
            return s1ptr->ch - s2ptr->ch;
        s1ptr = s1ptr->next;
        s2ptr = s2ptr->next;
    }
    return 0;
}

void Cstrcat( cstring * s1, cstring * s2 )
{
    snode * cur = s1->first;

    if ( cur == NULL )
    {
        SetCstring( &s1, s2 );
        return ;
    }
    while ( cur->next != NULL )
        cur = cur->next;
    cur->next = s2->first;
    s1->count += s2->count;
}

void Cstrcon( cstring ** s1, cstring * s2 )
{
    cstring * temp = NULL;

    temp = InitCstring( CstrtoStr( s2 ) );
    Cstrcat( *s1, temp );
}

char * CstrtoStr( cstring * s )
{
    snode * cur = s->first;
    int i = 0;
    int count = s->count;
    char * string = malloc( sizeof(char) * (count + 1) );

    for ( i = 0; i < count; i++ )
    {
        string[i] = cur->ch;
        cur = cur->next;
    }
    string[i] = '\0';

    return string;
}

char * NumtoStr( float num )
{
    char * str = malloc( sizeof(char) * 25 );

    sprintf( str, "%.5f", num );

    return str;
}

snode * Cstrdel( cstring * s, int place )
{
    snode * cur = NULL;
    int length = -1;
    int i = 1;
    snode * tmpNode = NULL;

    if ( s == NULL )
        return NULL;

    cur = s->first;
    length = s->count;
    if ( cur == NULL )
        return NULL;
    if ( length < place )
        return NULL;

    if ( place == 1 )
    {
        tmpNode = cur->next;
        cur->next = NULL;
        s->first = tmpNode;
        s->count -= 1;
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
    s->count -= 1;
    return tmpNode;
}
