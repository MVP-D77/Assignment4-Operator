//
// Created by 任艺伟 on 2020/12/3.
//

#ifndef ASSIGNMENT4_MATRIX_HPP
#define ASSIGNMENT4_MATRIX_HPP
#include <iostream>
#include <atomic>
#include <thread>

using namespace std;
class Vector;

class Matrix {
private:
    int rowNumber;
    int columnNumber;
    float * valueItem;
//    int * counter;
    atomic_int * counter;

public:
    Matrix();
    Matrix(int rowNumber,int columnNumber,float * value =NULL);
    ~Matrix();
    Matrix(const Matrix& matrix);
    Matrix& operator =(const Matrix & matrix);
    void transposition();
    float getDet() const;
    void setRowColumn(int row){rowNumber = row;}
    void setColumeColumn(int column){columnNumber = column;}



    virtual Matrix operator *(const Matrix & matrix) const;
    Matrix operator *(const Vector &vector) const;
    Matrix operator *(const float multiply) const;
    Matrix operator +(const Matrix & matrix) const;
    Matrix operator -(const Matrix & matrix) const;

    bool operator ==(const Matrix &other) const;
    bool operator !=(const Matrix &other) const;

    friend Matrix operator *(const float multiply ,const Matrix & matrix);
    friend Matrix operator *(const Vector &vector, const Matrix & matrix);
    friend Matrix operator ~(const Matrix &matrix);

    friend istream& operator >>(istream& os ,Matrix& other);
    friend ostream & operator<<(ostream& os,const Matrix & matrix);

};

class VectorInherit: public Matrix{
private:
    bool ifTransition = false;
public:
    VectorInherit();
    VectorInherit(int length,bool ifTransition,float * value = NULL);
//    ~VectorInherit();
    VectorInherit(const VectorInherit& vector);
//    Matrix operator *(const Matrix &matrix) const;
//    friend Matrix operator *(const Matrix &matrix,const VectorInherit&vector);



//    VectorInherit& operator =(const VectorInherit & vector);
};


class Vector{
private:
    int length;
    float * valueItem;
    atomic_int * use_counter;

public:
    Vector();
    Vector(int length,float * value = NULL);
    ~Vector();
    Vector(const Vector& vector);
    Vector& operator =(const Vector & vector);
    int getLength() const;
    float * getValue() const;
};


void threadTest();
bool judge(string data);

float getA(int num,float * value);


#endif //ASSIGNMENT4_MATRIX_HPP
