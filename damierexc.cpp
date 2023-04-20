#include "damierexc.h"

DamierExc::DamierExc(int l, int c, int borne, int vd)
{
    Borne = borne;
    Alloc(l, c);
    Init(vd);
}

DamierExc::DamierExc(const DamierExc &D)
{
    Alloc(D.L, D.C);
    Borne = D.Borne;
    for(int i=0; i<L; i++)
        for(int j=0; j<C; j++)
            T[i][j] = D.T[i][j];
}

DamierExc::~DamierExc(){
    if (T != NULL) {
        Free();
        T = NULL;
    }
}

void DamierExc::Free(){
    for (int i=0; i<L; i++)
        delete [] T[i];
    delete [] T;
}

void DamierExc::Alloc(int l, int c){
    L = l;
    C = c;
    T = new int*[L];
    for(int i=0; i<L; i++)
        T[i] = new int[C];
}

void DamierExc::Init(int value){
    if ((value<0) || (value>Borne)) {
        string file(__FILE__);
        string fonction(__PRETTY_FUNCTION__);
        ExceptionDamier e(Borne, value, file, fonction);
        throw(e);
    }

    for(int i=0; i<L; i++)
        for(int j=0; j<C; j++)
            T[i][j]=value;
}

void DamierExc::Set(int l, int c, int value) {
    if ( (l<0) || (l>=L) || (c<0) || (c>=C))
        throw("En dehors des dimensions!\n");

    if ((value<0) || (value>Borne)) {
        string file(__FILE__);
        string fonction(__PRETTY_FUNCTION__);
        ExceptionDamier e(Borne, value, file, fonction);
        throw(e);
    }
    T[l][c]=value;
}


void DamierExc::ReDim(int l, int c, int vd) {
    Free();
    Alloc(l, c);
    Init(vd);
}

DamierExc& DamierExc::operator= (const DamierExc &D){
    if ( this != &D) { // protection autoréférence
        Borne = D.Borne;
        Free();
        Alloc(D.L, D.C);
        for(int i=0; i<L; i++)
            for(int j=0; j<C; j++)
                T[i][j] = D.T[i][j];
    }
    return *this;
}

bool DamierExc::sameDimensions (const DamierExc &D) {
    if ((L == D.L) && (C == D.C))
        return true;
    return false;
}

DamierExc& DamierExc::operator+= (int c)
{
    Borne += c;
    for(int i=0; i<L; i++)
        for(int j=0; j<C; j++)
            T[i][j] += c;

    return *this;
}

DamierExc& DamierExc::operator+= (const DamierExc &D)
{
    if (!sameDimensions(D)){
        cerr << endl << __PRETTY_FUNCTION__ << " - Dimensions différentes !\n";
        exit(1);
    }
    Borne += D.Borne;
    for(int i=0; i<L; i++)
        for(int j=0; j<C; j++)
            T[i][j] += D.T[i][j];

    return *this;
}

ostream& operator<< (ostream& sortie, DamierExc& V)
{
    sortie << endl << "Borne = " << V.Borne;
    for(int i=0; i<V.L; i++) {
        sortie << endl;
        for(int j=0; j<V.C; j++)
            sortie << V.T[i][j] << ", ";
    }

    return sortie;
}
