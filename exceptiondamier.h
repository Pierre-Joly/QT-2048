#ifndef EXCEPTIONDAMIER_H
#define EXCEPTIONDAMIER_H

#include <iostream>
#include <sstream>
#include <string>
#include <exception>
using namespace std;

class ExceptionDamier : public exception
{
public:
    ExceptionDamier(int borne, int value, string filename, string fctname) throw();
    virtual const char* what() const throw();
private:
    int Borne;
    int Value;
    string FileName;
    string FctName;
    string Answer;
};

#endif // EXCEPTIONDAMIER_H
