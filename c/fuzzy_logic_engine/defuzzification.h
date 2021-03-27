#ifndef DEFUZZIFICATION_H_INCLUDED
#define DEFUZZIFICATION_H_INCLUDED

#include "cstring.h"
#include "cdict.h"
#include "variables.h"

typedef struct _defuzzyMethod
{
    ;
} DefuzzyMethod;

DefuzzyMethod * InitDefuzzyMethod( void );
void FreeDefuzzyMethod( DefuzzyMethod * self );

typedef struct _defuzzyCenterOfGravity
{
    cstring * description;
    cstring * type;
} DefuzzyCenterOfGravity;

DefuzzyCenterOfGravity * InitDefuzzyCenterOfGravity( void );
void FreeDefuzzyCenterOfGravity( DefuzzyCenterOfGravity * self );
char * getType( DefuzzyCenterOfGravity * d );
int CallDefuzzyCenterOfGravity( FuzzyVariable * variable,  cdict * degrees );
char * __str__DefuzzyCenterOfGravity( DefuzzyCenterOfGravity * d );

#endif // DEFUZZIFICATION_H_INCLUDED
