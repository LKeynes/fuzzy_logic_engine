#ifndef CLIST_H_INCLUDED
#define CLIST_H_INCLUDED

typedef struct _inode
{
    float number;
    struct _inode * next;
} inode;

inode * InitInode( float number );
void FreeInode( inode * iptr );

typedef struct _clist
{
    inode * first;
    int count;
} clist;

void AddInode( clist * self, inode * iptr );
clist * InitClist( float * values, int count );
void FreeClist( clist * cptr );
void SetClist( clist ** target, clist * source );
void ClistAppend( clist * List, float number );
inode * ClistDel( clist * list, int place );
void ClistSort( clist * List );
float ClistMax( clist * List );
float ClistMin( clist * List );
float GetInodeNum( clist * self, int key );
char * GetClist( clist * self );
float Sum( clist * List );
float Mul( clist * List );
float MulSum( clist * List1, clist * List2 );
float SumMul( clist * List1, clist * List2 );

#endif // CLIST_H_INCLUDED
