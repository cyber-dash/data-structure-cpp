//
// Created by cyberdash@163.com(抖音id:cyberdash_yuan) on 2021/5/16.
//


#include "test.h"


void TestSparseMatrixConstructor() {

  cout<<endl;
  cout<<"|------------------------ CyberDash ------------------------|"<<endl;
  cout<<"|                Test SparseMatrixConstructor               |"<<endl;
  cout<<"|                    测试队列稀疏矩阵构造函数                   |"<<endl<<endl<<endl;

  SparseMatrix<int> sparse_matrix(100);

  cout<<sparse_matrix;

  cout<<"-------------------------------------------------------------"<<endl<<endl;
}


void TestSparseMatrixCopyConstructor() {

  cout<<endl;
  cout<<"|------------------------ CyberDash ------------------------|"<<endl;
  cout<<"|              Test SparseMatrixCopyConstructor             |"<<endl;
  cout<<"|                  测试队列稀疏矩阵复制构造函数                 |"<<endl<<endl<<endl;

  SparseMatrix<int> sparse_matrix_1(100);
  SparseMatrix<int> sparse_matrix_2(sparse_matrix_1);

  // SparseMatrix<int>& sparse_matrix_3 = sparse_matrix_1.Transpose();
  SparseMatrix<int>* sparse_matrix_ptr_3 = sparse_matrix_1.Transpose();

  cout<<sparse_matrix_2;
  cout<<*sparse_matrix_ptr_3;

  cout<<"-------------------------------------------------------------"<<endl<<endl;
}


void TestSparseMatrixInput() {

  cout<<endl;
  cout<<"|------------------------ CyberDash ------------------------|"<<endl;
  cout<<"|                   Test SparseMatrixInput                  |"<<endl;
  cout<<"|                    测试队列稀疏矩阵输入构造                   |"<<endl<<endl<<endl;

  SparseMatrix<int> sparse_matrix_1(100);

  cin>>sparse_matrix_1;

  SparseMatrix<int>* sparse_matrix_ptr_3 = sparse_matrix_1.Transpose();

  cout << *sparse_matrix_ptr_3 << endl;

  cout<<"-------------------------------------------------------------"<<endl<<endl;
}


void TestSparseMatrixTranspose() {
  cout<<endl;
  cout<<"|------------------------ CyberDash ------------------------|"<<endl;
  cout<<"|                 Test SparseMatrixTranspose                |"<<endl;
  cout<<"|                     测试队列稀疏矩阵转置                     |"<<endl<<endl<<endl;

  SparseMatrix<double> sparse_matrix_1(100);

  sparse_matrix_1.SetRows(3);
  sparse_matrix_1.SetCols(3);

  sparse_matrix_1.AddElement(0, 1, 1.7);
  sparse_matrix_1.AddElement(1, 0, 8.2);

  cout<<"sparse_matrix_1矩阵:"<<endl;
  cout<<sparse_matrix_1<<endl;

  SparseMatrix<double>* sparse_matrix_ptr = sparse_matrix_1.Transpose();

  cout<<"转置后的矩阵:"<<endl;
  cout<<*sparse_matrix_ptr<<endl;

  cout<<"-------------------------------------------------------------"<<endl<<endl;
}