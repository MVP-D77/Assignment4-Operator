#include <iostream>
#include "Matrix.hpp"
using namespace std;

int main() {
    float matrixValue[10] = {1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0};

    Matrix matrix;
    cin>>matrix;
    cout<<matrix<<endl;

    Matrix matrix1(2,5,matrixValue);
    Matrix matrix2(5,2,matrixValue);

    Matrix matrix3 = matrix1+matrix1;
    cout<<matrix3<<endl;

    Matrix matrix4 = matrix1*matrix2;
    cout<<matrix4<<endl;

    Matrix matrix5 = matrix1*3;
    cout<<matrix5<<endl;

    Matrix matrix6 = 4*matrix1;
    cout<<matrix6<<endl;

    Matrix matrix7(matrix1);
    cout<<"copy constructor :"<<endl;
    cout<<matrix7<<endl;

    Matrix matrix8;
    matrix8 = matrix1;
    cout<<"Assignment = override : "<<endl;
    cout<<matrix8<<endl;


//    float vectorValue[5] = {1.0,1.0,1.0,1.0,1.0};
//    Vector vector(5,vectorValue);
//
//    cout<<matrix1*vector<<endl;
//    cout<<vector*matrix1<<endl;

//    VectorInherit vectorInherit(5,vectorValue);
//    Matrix temp(5,1,vectorValue,fals);
//    cout<<vectorInherit<<endl;
//
//    cout<<matrix1*vectorInherit<<endl;
////    cout<<vectorInherit*matrix2<<endl;
//
//    Matrix matrix7(matrix1);
//    Matrix matrix8(matrix7);



    float matrixValue1 [16]= {1,2,3,4,5,6,0,8,9,3,11,12,12,14,18,19};
    Matrix matrixI(4,4,matrixValue1);
    cout<<~matrixI;


//    threadTest();

    return 0;
}

