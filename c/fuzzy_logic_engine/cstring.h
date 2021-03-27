#ifndef CSTRING_H_INCLUDED
#define CSTRING_H_INCLUDED

typedef struct _snode
{
    char ch;
    struct _snode * next;
} snode;

snode * InitSnode( char ch );   //�ַ�
void FreeSnode( snode * self );

typedef struct _cstring
{
    snode * first;
    int count;
} cstring;  //�ַ���

cstring * InitCstring( char * source ); //Ϊ�ַ�������ռ䲢��ʼ��Ϊsource�����ݺ󷵻�ָ��
void FreeCstring( cstring ** str ); //�ͷ��ַ����ռ�
void SetCstring( cstring ** target, cstring * source ); //�����ַ���source�������Ը����ַ���*target
void Cstradd( cstring ** self, char * str );    //�����ַ�����str�������*self�ַ���֮��
int Cstrcmp( cstring * s1, cstring * s2 );  //�Ƚ��ַ���s1��s2����ͬ�򷵻�0
void Cstrcat( cstring * s1, cstring * s2 );    //���ַ���s2�����ַ���*s1֮��
void Cstrcon( cstring ** s1, cstring * s2 );    //�����ַ���s2�������*s1�ַ���֮��
char * CstrtoStr( cstring * s );    //���ַ���sת��Ϊ�ַ����鲢����ָ��
char * NumtoStr( float num );   //������ת��Ϊ�ַ����鲢����ָ��
snode * Cstrdel( cstring * s, int place );    //ɾ���ַ�����placeλ�õ��ַ�������snode

#endif // CSTRING_H_INCLUDED
