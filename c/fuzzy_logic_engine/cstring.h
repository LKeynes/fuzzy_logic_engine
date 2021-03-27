#ifndef CSTRING_H_INCLUDED
#define CSTRING_H_INCLUDED

typedef struct _snode
{
    char ch;
    struct _snode * next;
} snode;

snode * InitSnode( char ch );   //字符
void FreeSnode( snode * self );

typedef struct _cstring
{
    snode * first;
    int count;
} cstring;  //字符串

cstring * InitCstring( char * source ); //为字符串分配空间并初始化为source的内容后返回指针
void FreeCstring( cstring ** str ); //释放字符串空间
void SetCstring( cstring ** target, cstring * source ); //复制字符串source的内容以覆盖字符串*target
void Cstradd( cstring ** self, char * str );    //复制字符数组str以添加在*self字符串之后
int Cstrcmp( cstring * s1, cstring * s2 );  //比较字符串s1和s2，相同则返回0
void Cstrcat( cstring * s1, cstring * s2 );    //把字符串s2接在字符串*s1之后
void Cstrcon( cstring ** s1, cstring * s2 );    //复制字符串s2以添加在*s1字符串之后
char * CstrtoStr( cstring * s );    //将字符串s转换为字符数组并返回指针
char * NumtoStr( float num );   //将数字转换为字符数组并返回指针
snode * Cstrdel( cstring * s, int place );    //删除字符串中place位置的字符并返回snode

#endif // CSTRING_H_INCLUDED
