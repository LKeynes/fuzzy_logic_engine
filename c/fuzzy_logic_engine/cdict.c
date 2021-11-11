#include <stdlib.h>
#include "cdict.h"
#include "cstring.h"

dnode * InitDnode( void )
{
    dnode * self = malloc( sizeof(dnode) );

    self->degree = -1;
    self->List = NULL;
    self->name = NULL;
    self->next = NULL;

    return self;
}

void FreeDnode( dnode * dptr )
{
    free(dptr);
    dptr = NULL;
}

void SetDnodeValues( dnode * self, cstring * name, clist * values )
{
    self->name = name;
    self->List = values;
    self->degree = -1;
}

void SetDnodeDegree( dnode * self, cstring * name, float degree )
{
    self->name = name;
    FreeClist(self->List);
    self->List = NULL;
    self->degree = degree;
}

cdict * InitCdict( void )
{
    cdict * self = malloc( sizeof(cdict) );

    self->count = 0;
    self->first = NULL;

    return self;
}

void FreeCdict( cdict * cptr )
{
    dnode * sptr = NULL;
    dnode * next = NULL;

    if ( cptr != NULL )
    {
        sptr = cptr->first;
        while ( sptr != NULL )
        {
            next = sptr->next;
            FreeDnode(sptr);
            sptr = next;
        }
        free(cptr);
        cptr = NULL;
    }
    return ;
}

void AddDnode( cdict * self, dnode * dk )
{
    dnode * cur = NULL;
    dnode * next = NULL;

    cur = self->first;
    if ( cur == NULL )
        self->first = dk;
    else
    {
        cur = FindDnode( self, CstrtoStr(dk->name) );
        if ( cur != NULL )
        {
            SetDnodeValues( cur, dk->name, dk->List );
            return ;
        }
        cur = self->first;
        next = cur->next;
        while ( next != NULL )
        {
            cur = next;
            next = cur->next;
        }
        cur->next = dk;
    }
    self->count++;
}

dnode * DelDnode( cdict * self, int place )
{
    dnode * cur = NULL;
    int length = -1;
    int i = 1;
    dnode * dptr = NULL;
    dnode * tmpNode = NULL;

    if ( self == NULL )
        return NULL;

    cur = self->first;
    length = self->count;
    if ( cur == NULL )
        return NULL;
    if ( length < place )
        return NULL;

    if ( place == 1 )
    {
        tmpNode = cur->next;
        cur->next = NULL;
        self->first = tmpNode;
        self->count -= 1;
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
    dptr = tmpNode;
    self->count -= 1;
    return dptr;
}

dnode * FindDnode( cdict * self, char * name )
{
    char * source = name;

    cstring * s = NULL;
    int i = 0;
    snode * sptr = NULL;
    snode * cur1 = NULL;

    s = malloc( sizeof(cstring) );
    if ( source == NULL )
    {
        s->first = NULL;
        s->count = 0;
    }
    else
    {
        sptr = InitSnode(source[0]);
        s->first = cur1 = sptr;
        for ( i = 1; source[i] != '\0'; i++ )
        {
            sptr = InitSnode(source[i]);
            cur1->next = sptr;
            cur1 = sptr;
        }
        s->count = i;
    }

    cstring * str = s;

    dnode * cur = NULL;
    dnode * next = NULL;

    cur = self->first;
    while ( cur != NULL )
    {
        next = cur->next;
        if ( !Cstrcmp(cur->name, str) )
        {
            FreeCstring( &str );
            return cur;
        }
        cur = next;
    }
    FreeCstring( &str );

    return NULL;
}

char * GetCdict( cdict * self )
{
    cstring * cstr = InitCstring("{");
    dnode * dptr = NULL;
    char * str = NULL;
    dnode * dptrNext = NULL;
    float dptrDegree = 0;
    cstring * dptrName = NULL;
    clist * dptrList = NULL;

    if ( self->count > 0 )
    {
        dptr = self->first;
        while ( dptr != NULL )
        {
            dptrNext = dptr->next;
            dptrName = dptr->name;
            dptrDegree = dptr->degree;
            dptrList = dptr->List;

            Cstradd( &cstr, "\"" );
            Cstradd( &cstr, CstrtoStr(dptrName) );
            Cstradd( &cstr, "\"" );
            Cstradd( &cstr, ": " );
            if ( dptrDegree != -1 )
                Cstradd( &cstr, NumtoStr(dptrDegree) );
            else
                Cstradd( &cstr, GetClist(dptrList) );
            if ( dptrNext != NULL )
                Cstradd( &cstr, ", " );
            dptr = dptrNext;
        }
    }
    Cstradd( &cstr, "}" );
    str = CstrtoStr( cstr );
    FreeCstring( &cstr );

    return str;
}

cdictnode * InitCdictnode( void )
{
    cdictnode * self = malloc( sizeof(cdictnode) );
    self->dict = NULL;
    self->key = NULL;
    self->name = NULL;
    self->next = NULL;
    return self;
}

void FreeCdictnode( cdictnode * self )
{
    FreeCdict(self->dict);
    FreeCstring(&(self->key));
    FreeCstring(&(self->name));
    free(self);
    self = NULL;
}

void SetCdictnode( cdictnode * self, cdict * dict )
{
    self->dict = dict;
}

void SetCdictnodeDict( cdictnode * self, cstring * key, cdict * dict, cstring * name )
{
    self->key = key;
    self->dict = dict;
    self->name = name;
}

cdictlist * InitCdictlist( void )
{
    cdictlist * self = malloc( sizeof(cdictlist) );
    self->first = NULL;
    self->count = 0;
    return self;
}

void FreeCdictlist( cdictlist * self )
{
    cdictnode * cur = NULL;
    cdictnode * next = NULL;

    if ( self != NULL )
    {
        cur = self->first;
        while ( cur != NULL )
        {
            next = cur->next;
            FreeCdictnode(cur);
            cur = next;
        }
        free(self);
        self = NULL;
    }
    return ;
}

void CdictlistAddCdictnode( cdictlist * self, cdictnode * dictnode )
{
    cdictnode * cur = NULL;

    cur = self->first;
    if ( cur == NULL )
        self->first = dictnode;
    else
    {
        while ( cur->next != NULL )
            cur = cur->next;
        cur->next = dictnode;
    }
    self->count++;
}

void CdictlistSort( cdictlist * self )
{
    cdictnode * start = NULL;
    cdictnode * cur = NULL;
    cdictnode * temp = NULL;
    cdict * dict = NULL;
    cstring * name = NULL;

    start = self->first;
    if ( start == NULL )
        return ;
    while ( start->next != NULL )
    {
        cur = start;
        temp = NULL;
        dict = cur->dict;
        name = dict->first->name;
        while ( cur != NULL )
        {
            if ( Cstrcmp(cur->dict->first->name, name) < 0 )
            {
                temp = cur;
                dict = temp->dict;
                name = temp->dict->first->name;
            }
            cur = cur->next;
        }
        if ( temp != NULL )
        {
            temp->dict = start->dict;
            start->dict = dict;
        }
        start = start->next;
    }
}

char * GetCdictlist( cdictlist * self )
{
    char * source = "[";

    cstring * str1 = NULL;
    int i = 0;
    snode * sptr = NULL;
    snode * cur = NULL;

    str1 = malloc( sizeof(cstring) );
    if ( source == NULL )
    {
        str1->first = NULL;
        str1->count = 0;
    }
    else
    {
        sptr = InitSnode(source[0]);
        str1->first = cur = sptr;
        for ( i = 1; source[i] != '\0'; i++ )
        {
            sptr = InitSnode(source[i]);
            cur->next = sptr;
            cur = sptr;
        }
        str1->count = i;
    }

    cstring * cstr = str1;

    cdictnode * dptr = NULL;
    char * str = NULL;
    cdictnode * dptrNext = NULL;
    cdict * dptrDict = NULL;

    if ( self->count > 0 )
    {
        dptr = self->first;
        while ( dptr != NULL )
        {
            dptrNext = dptr->next;
            dptrDict = dptr->dict;

            Cstradd( &cstr, GetCdict(dptrDict) );
            if ( dptrNext != NULL )
                Cstradd( &cstr, ", " );
            dptr = dptrNext;
        }
    }
    Cstradd( &cstr, "]" );
    str = CstrtoStr( cstr );
    FreeCstring( &cstr );

    return str;
}

cdictdict * InitCdictdict( void )
{
    cdictdict * self = malloc( sizeof(cdictdict) );
    self->first = NULL;
    self->count = 0;
    return self;
}

void CdictdictAddCdictnode( cdictdict * self, cdictnode * ptr )
{
    cdictnode * cur = self->first;
    cdictnode * curNext = NULL;

    if ( cur == NULL )
        self->first = ptr;
    else
    {
        curNext = cur->next;
        while ( curNext != NULL )
        {
            cur = curNext;
            curNext = cur->next;
        }
        cur->next = ptr;
    }
    self->count++;
}

char * GetCdictdict( cdictdict * self )
{
    char * source = "{";

    cstring * str1 = NULL;
    int i = 0;
    snode * sptr = NULL;
    snode * cur = NULL;

    str1 = malloc( sizeof(cstring) );
    if ( source == NULL )
    {
        str1->first = NULL;
        str1->count = 0;
    }
    else
    {
        sptr = InitSnode(source[0]);
        str1->first = cur = sptr;
        for ( i = 1; source[i] != '\0'; i++ )
        {
            sptr = InitSnode(source[i]);
            cur->next = sptr;
            cur = sptr;
        }
        str1->count = i;
    }

    cstring * cstr = str1;

    cdictnode * dptr = NULL;
    char * str = NULL;
    cstring * dptrKey = NULL;
    cstring * dptrName = NULL;
    cdict * dptrDict = NULL;
    cdictnode * dptrNext = NULL;

    if ( self->count > 0 )
    {
        dptr = self->first;
        while ( dptr != NULL )
        {
            dptrKey = dptr->key;
            dptrName = dptr->name;
            dptrDict = dptr->dict;
            dptrNext = dptr->next;

            Cstradd( &cstr, CstrtoStr(dptrKey) );
            Cstradd( &cstr, ": " );
            if ( dptrDict != NULL )
                Cstradd( &cstr, GetCdict(dptrDict) );
            else
            {
                Cstradd( &cstr, "\"" );
                Cstrcon( &cstr, dptrName );
                Cstradd( &cstr, "\"" );
            }
            if ( dptrNext != NULL )
                Cstradd( &cstr, ", " );
            dptr = dptrNext;
        }
    }
    Cstradd( &cstr, "}" );
    str = CstrtoStr( cstr );
    FreeCstring( &cstr );

    return str;
}
