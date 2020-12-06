//
// Created by 任艺伟 on 2020/12/3.
//

#include "Matrix.hpp"
void testCorrect(Matrix & matrix){
    for(int i=0;i<10000;i++){
        Matrix a (matrix);
    }
}

void threadTest(){
    Matrix matrix (1,1);

    auto start = std::chrono::steady_clock::now();
    thread th1 = thread(testCorrect,ref(matrix));
    thread th2 = thread(testCorrect,ref(matrix));
    thread th3 = thread(testCorrect,ref(matrix));
    thread th4 = thread(testCorrect,ref(matrix));
    testCorrect(matrix);
    th1.join();
    th2.join();
    th3.join();
    th4.join();

    auto end = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    cout << "matrixProduct 1 , duration = " << duration <<" us"<< std::endl;
}


float dotProduct(const float *p1, const float * p2, size_t n, size_t temp)
{
    float sum = 0.0f;
    for (size_t i = 0,j=0; i < n; i++,j += temp)
        sum += (p1[i] * p2[j]);
    return sum;
}

Matrix::Matrix() :rowNumber(0),columnNumber(0),valueItem(nullptr){
//    counter = new int;
    counter = new atomic_int;
    *(counter) = 0;
}

Matrix::Matrix(int rowNumber, int columnNumber,float * value) {
    this->columnNumber = columnNumber;
    this->rowNumber = rowNumber;
    this->valueItem = new float [rowNumber*columnNumber]();
    if(value!=NULL){
        for(int i=0;i<rowNumber*columnNumber;i++){
            *(this->valueItem+i) = *(value+i);
        }
    }
//    counter = new int;
    counter = new atomic_int;
    *(counter) = 1;
}

Matrix::Matrix(const Matrix &matrix) {
    this->columnNumber = matrix.columnNumber;
    this->rowNumber = matrix.rowNumber;
    this->valueItem = matrix.valueItem;
    this->counter = matrix.counter;
//    mutex m;
//    m.lock();
    (*counter) +=1;
//    m.unlock();
}


Matrix Matrix::operator*(const float multiply) const {
    cout<<"type A*b :"<<endl;
    Matrix resultMatrix(this->rowNumber,this->columnNumber);
    resultMatrix.valueItem = new float [resultMatrix.rowNumber*resultMatrix.columnNumber]();
    for(int i=0;i<rowNumber*columnNumber;i++){
        *(resultMatrix.valueItem+i) = *(valueItem+i)*multiply;
    }
    return resultMatrix;
}

Matrix::~Matrix() {
//    cout<<*counter<<endl;
    if(*(counter) == 1) {
//        cout<<"You really delete the pointer of object Matrix"<<endl;
        delete [] valueItem ;
        delete counter;
    }
    else {
//        mutex m;
//
//        m.lock();
        (*counter) -=1;
//        m.unlock();
    }
}

Matrix & Matrix::operator=(const Matrix &matrix) {
    if(this == &matrix) return *this;

    if(*(counter) == 1)  {
        delete counter;
        delete [] valueItem ;
    }else if(*(counter)==0){
        delete counter;
    }
    else (*counter)--;

    this->counter = matrix.counter;
    this->rowNumber = matrix.rowNumber;
    this->columnNumber = matrix.columnNumber;
    this->valueItem = matrix.valueItem;
    (*counter)++;
    return *this;
}

Matrix Matrix::operator+(const Matrix &matrix) const {
    cout<<"type A+B :"<<endl;

    if(matrix.rowNumber == this->rowNumber&&matrix.columnNumber==this->columnNumber){
        Matrix resultMatrix(matrix.rowNumber,matrix.columnNumber);
        resultMatrix.valueItem = new float [resultMatrix.rowNumber*resultMatrix.columnNumber]();
        for(int i=0;i<matrix.columnNumber*matrix.rowNumber;i++){
            *(resultMatrix.valueItem+i) = *(matrix.valueItem+i)+(*(this->valueItem+i));
        }
        return resultMatrix;
    } else{
        cout<<"You are do wrong things matrix addition must two matrix with same rowNumber and columnNumber";
        exit(0);
    }
}

bool Matrix::operator==(const Matrix & matrix) const {
    cout<<"type A==B :"<<endl;

    if(matrix.rowNumber == this->rowNumber&&matrix.columnNumber==this->columnNumber){
        bool judge = true;
        for(int i=0;i<rowNumber*columnNumber;i++){
            if(*(matrix.valueItem+i)!= *(this->valueItem+i)){
                judge = false;
                break;
            }
        }
        return judge;
    } else return false;
}

bool Matrix::operator!=(const Matrix &matrix) const {
    cout<<"type A!=B :"<<endl;

    if(matrix.rowNumber == this->rowNumber&&matrix.columnNumber==this->columnNumber){
        bool judge = false;
        for(int i=0;i<rowNumber*columnNumber;i++){
            if(*(matrix.valueItem+i)!= *(this->valueItem+i)){
                judge = true;
                break;
            }
        }
        return judge;
    } else return true;
}


Matrix Matrix::operator-(const Matrix &matrix) const {
    cout<<"type A-B :"<<endl;

    if(matrix.rowNumber == this->rowNumber&&matrix.columnNumber==this->columnNumber){
        Matrix resultMatrix(matrix.rowNumber,matrix.columnNumber);
        resultMatrix.valueItem = new float [resultMatrix.rowNumber*resultMatrix.columnNumber]();
        for(int i=0;i<matrix.columnNumber*matrix.rowNumber;i++){
            *(resultMatrix.valueItem+i) = *(this->valueItem+i)-(*(matrix.valueItem+i));
        }
        return resultMatrix;
    } else{
        cout<<"You are do wrong things matrix addition must two matrix with same rowNumber and columnNumber";
        exit(0);
    }
}

Matrix Matrix::operator*(const Vector &vector) const {

    if(this->columnNumber!=vector.getLength()){
        cout<<"Matrix * Vector error"<<endl;
        exit(0);
    } else{
        Matrix resultMatrix(this->rowNumber,1);
        resultMatrix.valueItem = new float[this->rowNumber];
        for(int i=0;i<this->rowNumber;i++){
            *(resultMatrix.valueItem+i) = dotProduct(this->valueItem+i*this->columnNumber,vector.getValue(),this->columnNumber,1);
        }
        return resultMatrix;
    }
}

Matrix Matrix::operator*(const Matrix &matrix) const {
    cout<<"type A*B :"<<endl;

    if(this->columnNumber!=matrix.rowNumber){
        cout<<"Wrong!! Please input right mxn and nxp matrixes!"<<endl;
        exit(0);
    }else{
        Matrix resultMatrix(this->rowNumber,matrix.columnNumber);
        resultMatrix.valueItem = new float [this->rowNumber*matrix.columnNumber];
        int k=0;
        for(int i=0;i<this->rowNumber;i++){
            for(int j=0;j<matrix.columnNumber;j++){
                *(resultMatrix.valueItem+k)=
                        dotProduct(this->valueItem+i*this->columnNumber,matrix.valueItem+j,
                                    this->columnNumber,matrix.columnNumber);
                k++;
            }
        }
        return resultMatrix;
    }
}

Matrix operator *(const float multiply ,const Matrix & matrix){
    cout<<"type b*A :"<<endl;

    return matrix*multiply;
}


Matrix operator *(const Vector &vector, const Matrix & matrix){
    return matrix*vector;
}


ostream & operator<<(ostream& os,const Matrix & matrix){
    os.setf(ios_base::fixed,ios_base::floatfield);
    os.precision(3);

    for(int i=0;i<matrix.rowNumber*matrix.columnNumber;i++){
        os<<*(matrix.valueItem+i)<<" ";
        if((i+1)%matrix.columnNumber==0) os<<endl;
    }

    return os;
}

bool judgeLength(string text)
{
    int i;
    for(i=0;i<text.length();i++){
        if(!isdigit(text[i])) break;
    }
    if(i == text.length()) return true;
    else return false;
}

istream& operator >>(istream& is ,Matrix& matrix){
    cout<<"Please input the row number of  matrix: ";
    string number1;
    is>>number1;
    while(!judgeLength(number1)){
        cout<<"The row number must be a integer,please check!";
        is>>number1;
    }
    matrix.rowNumber  = stoi(number1);
    cout<<"Please input the column number of matrix: ";
    string number2;
    cin>>number2;
    while(!judgeLength(number2)){
        cout<<"The column number must be a integer,please check!";
        cin>>number2;
    }
    matrix.columnNumber  = stoi(number2);

    if(*matrix.counter!=0) {
        cout<<"You can not cin>>matrix for which has already has information";
        exit(0);
    }

    matrix.valueItem = new float [matrix.rowNumber*matrix.columnNumber]();
    *(matrix.counter) = 1;

    for(int i=0;i<matrix.rowNumber*matrix.columnNumber;i++){
        string temp;
        is>>temp;
        if(judge(temp))  *(matrix.valueItem+i) = stof(temp);
        else{
            cout<<"Your input has illegal items ,Please check!"<<endl;
            exit(0);
        }
//        cout<<*(matrix.value+i);
    }

    return is;
}

bool judge(string data){
    char signal = data[0]=='-'?'-':'+';
    int sigNum =0;
    int pointNum=0;
    int eNum = 0;
    string dara_real = data[0]=='-'?data.substr(1):data;

    for(int i=0;i<dara_real.length();i++){
        if(!isdigit(dara_real[i])&&dara_real[i]!='+'&&dara_real[i]!='-'&&dara_real[i]!='.'&&dara_real[i]!='E'&&dara_real[i]!='e'){
            return false;
        }else if(dara_real[i]=='+'||dara_real[i]=='-'){
            if(sigNum>0) return false;
            else if(i==0||dara_real[i-1]!='E'&&dara_real[i-1]!='e') return false;
            else sigNum++;
        }else if(dara_real[i]=='.'){
            if(pointNum>0) return false;
            else if(i==dara_real.length()-1) return false;
            else pointNum++;
        }else if(dara_real[i]=='E'||dara_real[i]=='e'){
            if(eNum>0) return false;
            else if(i==dara_real.length()-1) return false;
            else eNum++;
        }
    }
    return true;
}

float getA(int num,float * value) {
    if(num==1) return value[0];
    float ans = 0;
    float * subValue = new float [(num-1)*(num-1)]();

    for(int i=0;i<num;i++){
        int m = 0;
        for(int k=num;k<num*num;k++){
            if(k%num!=i){
                subValue[m]= value[k];
                m++;
            }
        }
        double t = getA(num-1,subValue);
        if(i%2==0) ans += value[i]*t;
        else ans -= value[i]*t;
    }
    return ans;
    delete []  subValue;
}

Matrix operator ~(const Matrix &matrix){
    cout<<"type ~A :"<<endl;

    if(matrix.rowNumber!=matrix.columnNumber){
        cout<<"Matrix must be square can inverse!"<<endl;
        exit(0);
    }
    int num = matrix.rowNumber;
    float A = getA(num,matrix.valueItem);
    if(A==0){
        cout<<"Matrix is not full rank,it has no inverse!!"<<endl;
        exit(0);
    }
    float * resultValue = new float [num*num]();
    float * tempValue = new float [(num-1)*(num-1)]();
    for(int i=0;i<num;i++){
        for(int j=0;j<num;j++){
            int m=0;
            for(int k=0;k<num*num;k++){
                if(k%num!=j&&!(k>=i*num&&k<(i+1)*num)){
                    *(tempValue+m) = matrix.valueItem[k];
                    m++;
                }
            }
            resultValue [i*num+j] = (i+j)%2==0?1/A*getA(num-1,tempValue):-1/A*getA(num-1,tempValue);
        }
    }
    delete [] tempValue;
    Matrix resultMatrix =  Matrix (num,num,resultValue);
    resultMatrix.transposition();
    delete [] resultValue;
    return resultMatrix;
}

float Matrix::getDet() const{
    if(rowNumber!=columnNumber){
        cout<<"Matrix must be square have determinant!"<<endl;
        exit(0);
    }
    int num = rowNumber;
    return getA(num,valueItem);
}

void Matrix:: transposition(){
    for(int i=0;i<rowNumber;i++){
        for(int j=i+1;j<columnNumber;j++){
            float temp = *(valueItem+i*rowNumber+j);
            *(valueItem+i*rowNumber+j) = *(valueItem+j*rowNumber+i);
            *(valueItem+j*rowNumber+i) = temp;
        }
    }
    int temp = rowNumber;
    columnNumber = rowNumber;
    rowNumber = temp;
}


Vector::Vector() {
    length = 0;
    *(use_counter) = 0;
}


Vector::Vector(int length,float * value) {
    this->length = length;
    this->valueItem = new float [length];
    if(value!=NULL) {
        for(int i=0;i<length;i++){
            *(valueItem+i) = *(value+i);
        }
    }
    use_counter = new atomic_int ;
    *use_counter = 1;
}

Vector::Vector(const Vector &vector) {
    this->length = vector.length;
    this->valueItem = vector.valueItem;
    this->use_counter = vector.use_counter;
    (*use_counter)++;
}


Vector::~Vector() {
    if(*(use_counter) == 1) {
        cout<<"You really delete the pointer of object Vector"<<endl;
        delete [] valueItem ;
        delete use_counter;
    }
    else (*use_counter)--;
}

Vector & Vector::operator=(const Vector &vector) {
    if(this==&vector) return *this;
    if(*(use_counter) == 1) {
        delete use_counter;
        delete [] valueItem ;
    }
    else (*use_counter)--;

    this->length = vector.length;
    this->valueItem = vector.valueItem;
    this->use_counter = vector.use_counter;
    (*use_counter)++;

    return *this;
}

int Vector::getLength() const {return length;}

float * Vector::getValue() const {return valueItem;}

VectorInherit::VectorInherit() {
    Matrix();
}

VectorInherit::VectorInherit(int length,bool ifTransition,float *value) :Matrix(length,1,value){
    this->ifTransition = ifTransition;
    if(ifTransition){
        setColumeColumn(length);
        setRowColumn(1);
    }
}

VectorInherit::VectorInherit(const VectorInherit &vector):Matrix(vector) {}


