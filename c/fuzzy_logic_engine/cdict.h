#ifndef CDICT_H_INCLUDED
#define CDICT_H_INCLUDED

#include "cstring.h"
#include "clist.h"

typedef struct _dnode
{
    cstring * name;
    float degree;
    clist * List;
    struct _dnode * next;
} dnode;

dnode * InitDnode( void );
void FreeDnode( dnode * dptr );
void SetDnodeValues( dnode * self, cstring * name, clist * values );
void SetDnodeDegree( dnode * self, cstring * name, float degree );

typedef struct _cdict
{
    dnode * first;
    int count;
} cdict;

cdict * InitCdict( void );
void FreeCdict( cdict * cptr );
void AddDnode( cdict * self, dnode * dk );
dnode * DelDnode( cdict * self, int place );
dnode * FindDnode( cdict * self, char * name );
char * GetCdict( cdict * self );

typedef struct _cdictnode
{
    cstring * key;
    cdict * dict;
    cstring * name;
    struct _cdictnode * next;
} cdictnode;

cdictnode * InitCdictnode( void );
void FreeCdictnode( cdictnode * self );
void SetCdictnode( cdictnode * self, cdict * dict );
void SetCdictnodeDict( cdictnode * self, cstring * key, cdict * dict, cstring * name );

typedef struct _cdictlist
{
    cdictnode * first;
    int count;
} cdictlist;

cdictlist * InitCdictlist( void );
void CdictlistAddCdictnode( cdictlist * self, cdictnode * ptr );
void CdictlistSort( cdictlist * self );
char * GetCdictlist( cdictlist * self );

typedef struct _cdictdict
{
    cdictnode * first;
    int count;
} cdictdict;

cdictdict * InitCdictdict( void );
void FreeCdictlist( cdictlist * self );
void CdictdictAddCdictnode( cdictdict * self, cdictnode * ptr );
char * GetCdictdict( cdictdict * self );

#endif // CDICT_H_INCLUDED
