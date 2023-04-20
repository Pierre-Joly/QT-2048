#ifndef DAMIEREXC_H
#define DAMIEREXC_H

#include <string>
#include <iostream>
using namespace std;

#include "exceptiondamier.h"

class DamierExc
{
public:
    DamierExc(int l, int c, int borne, int vd=0);
    DamierExc(const DamierExc &D);
    ~DamierExc();

    DamierExc& operator=  (const DamierExc &D); // opérateur d'affectation
    DamierExc& operator+= (const DamierExc &D);
    DamierExc& operator+= (int c);
    friend ostream& operator<< (ostream& sortie, DamierExc& V);

    void Init(int value);
    void Set(int x, int y, int value);
    void ReDim(int l, int c, int vd = 0);

protected:
    int L;
    int C;
    int Borne;
    int** T;

    virtual void InitJeu()=0; // rend la méthode virtuelle pure

private:
    // Méthode privée (factorisation  de code)
    void Alloc(int l, int c);
    void Free();
    bool sameDimensions (const DamierExc &D);
};

#endif // DAMIEREXC_H
