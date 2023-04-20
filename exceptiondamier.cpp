#include "exceptiondamier.h"


ExceptionDamier::ExceptionDamier(int borne, int value,
                                 string filename, string fctname) throw():
                    FileName(filename), FctName(fctname)
{
    Borne = borne;
    Value = value;
    Answer += "Borne = " + to_string(Borne) + "\n";
    Answer += "Valeur rejetée : " + to_string(Value) + "\n";
    Answer += "Fichier : " + filename + "\n";
    Answer += "Fonction : " + fctname + "\n";
}

const char* ExceptionDamier::what() const throw()
{
    return Answer.c_str();
}
