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
