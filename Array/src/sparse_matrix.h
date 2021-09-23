/**
 * @file sparse_matrix.h
 * @author cyberdash@163.com(抖音id:cyberdash_yuan)
 * @brief 稀疏矩阵 
 * @version 0.1
 * @date 2021-05-13
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef CYBER_DASH_TRI_TUPLE_H
#define CYBER_DASH_TRI_TUPLE_H


#include <iostream>
#include <cstdlib>


using namespace std;


template<class T>
struct TriTuple {
  int row;
  int col;
  T value;
  TriTuple<T>& operator=(TriTuple<T>& trituple) {
    row = trituple.row;
    col = trituple.col;
    value = trituple.value;
  }
};


/**
 * @brief 构造稀疏矩阵
 * 
 * @tparam T 存储的值
 */
template<class T>
class SparseMatrix {
public:

/**
 * @brief 构建一个新的稀疏矩阵
 * 
 * @param max_size 矩阵最大容量
 */
  SparseMatrix(int max_size = 100);
  SparseMatrix(SparseMatrix<T>& sparse_matrix);
  ~SparseMatrix() { delete[] sparse_matrix_array_; }

  int Rows() { return this->rows_; }
  void SetRows(int rows) { this->rows_ = rows; }

  int Cols() { return this->cols_; };
  void SetCols(int cols) { this->cols_ = cols; };

  int Terms() { return this->terms_; }
  int SetTerms(int terms) { this->terms_ = terms; }

  int MaxTerms() { return this->max_terms_; }
  int SetMaxTerms(int max_terms) { this->max_terms_ = max_terms; }

  bool GetElement(int row, int col, T& value);
  bool AddElement(int row, int col, T value);

  TriTuple<T>* SparseMatrixArray() { return this->sparse_matrix_array_; }

  SparseMatrix<T>& operator = (SparseMatrix<T>& sparse_matrix);

  // 转置运算
  SparseMatrix<T>* Transpose();

  // 快速转置运算
  SparseMatrix<T>& FastTranspose();

  // 当前矩阵与sparse_matrix相加
  SparseMatrix<T> Add(SparseMatrix<T>& sparse_matrix);

  // 当前矩阵与矩阵sparse_matrix相乘
  SparseMatrix<T> Multiply(SparseMatrix<T>& sparse_matrix);

  template <class U>
  friend ostream& operator << (ostream& out, SparseMatrix<T>& sparse_matrix);
  template <class U>
  friend istream& operator >> (istream& in, SparseMatrix<T>& sparse_matrix);

private:
  int rows_;
  int cols_;
  int terms_;
  int max_terms_;
  TriTuple<T>* sparse_matrix_array_;
};


/**
 * @brief 构造函数
 * @tparam T 数据模板类型
 * @param max_size 矩阵的最大维度
 */
template<class T>
SparseMatrix<T>::SparseMatrix(int max_size): max_terms_(max_size) {
  if (max_size < 1) {
    cerr<<"初始化max_size错误"<<endl;
    return;
  }

  this->sparse_matrix_array_ = new TriTuple<T>[max_size];
  /* error handler */

  this->max_terms_ = max_size;
  this->rows_ = 0;
  this->cols_ = 0;
  this->terms_ = 0;
}


template<class T>
SparseMatrix<T>::SparseMatrix(SparseMatrix<T>& sparse_matrix) :
  rows_(sparse_matrix.Rows()), cols_(sparse_matrix.Cols()),
  terms_(sparse_matrix.Terms()), max_terms_(sparse_matrix.MaxTerms())
{
  this->sparse_matrix_array_ = new TriTuple<T>[this->MaxTerms()];
  /* error handler */

  for (int i = 0; i < this->terms_; i++) {
    this->sparse_matrix_array_[i] = sparse_matrix.SparseMatrixArray()[i];
  }
}


template<class T>
SparseMatrix<T>& SparseMatrix<T>::operator = (SparseMatrix<T>& sparse_matrix) {

  this->SetRows(sparse_matrix.Rows());
  this->SetCols(sparse_matrix.Cols());
  this->SetTerms(sparse_matrix.Terms());
  this->SetMaxTerms(sparse_matrix.MaxTerms());

  this->sparse_matrix_array_ = new TriTuple<T>[this->MaxTerms()];
  /* error handler */

  for (int i = 0; i < this->terms_; i++) {
    this->sparse_matrix_array_[i] = sparse_matrix.SparseMatrixArray()[i];
  }
}


template<class T>
ostream& operator<<(ostream& out, SparseMatrix<T>& sparse_matrix) {
  out<<"rows = "<<sparse_matrix.Rows()<<endl;
  out<<"cols = "<<sparse_matrix.Cols()<<endl;
  out<<"NonZero terms: "<<sparse_matrix.Terms()<<endl;

  for (int i = 0; i < sparse_matrix.Terms(); i++) {
    out<<"M["<<sparse_matrix.SparseMatrixArray()[i].row<<"]["<<
      sparse_matrix.SparseMatrixArray()[i].col<<"] = "<<
      sparse_matrix.SparseMatrixArray()[i].value<<endl;
  }

  return out;
}


template<class T>
istream& operator>>(istream& in, SparseMatrix<T> &sparse_matrix) {
  cout << "输入rows, cols和terms" << endl;

  int rows = 0;
  int cols = 0;
  int terms = 0;

  in >> rows >> cols >> terms;

  if (terms > sparse_matrix.MaxTerms()) {
    /* error handler */
    exit(1);
  }

  sparse_matrix.SetRows(rows);
  sparse_matrix.SetCols(cols);
  sparse_matrix.SetTerms(terms);

  for (int i = 0; i < sparse_matrix.Terms(); i++) {
    cout << "输入第" << i << "个row, column和term的值" << endl;
    in >> sparse_matrix.SparseMatrixArray()[i].row
      >> sparse_matrix.SparseMatrixArray()[i].col
      >> sparse_matrix.SparseMatrixArray()[i].value;
  }

  cout << sparse_matrix << endl;

  return in;
}


/**
 * @brief 稀疏矩阵转置
 * @tparam T
 * @return
 */
template<class T>
SparseMatrix<T>* SparseMatrix<T>::Transpose() {
  SparseMatrix<T>* trans_sparse_matrix_ptr = new SparseMatrix<T>(this->MaxTerms());

  trans_sparse_matrix_ptr->SetRows(this->Cols());
  trans_sparse_matrix_ptr->SetCols(this->Rows());
  trans_sparse_matrix_ptr->SetTerms(this->Terms());

  if (this->Terms() == 0) {
    return trans_sparse_matrix_ptr;
  }

  int cur = 0;
  for (int i = 0; i < this->Cols(); i++) { // 用列号做扫描, 做Cols趟
    for (int j = 0; j < this->Terms(); j++) { // 在数组sparse_matrix_array_中找到列号为i的三元组
      if (this->SparseMatrixArray()[j].col == i) {
        trans_sparse_matrix_ptr->SparseMatrixArray()[cur].row = i; // row等于col
        trans_sparse_matrix_ptr->SparseMatrixArray()[cur].col = this->SparseMatrixArray()[j].row; // col等于row
        trans_sparse_matrix_ptr->SparseMatrixArray()[cur].value = this->SparseMatrixArray()[j].value; // value
        cur++;
      }
    }
  }

  return trans_sparse_matrix_ptr;
}


template<class T>
bool SparseMatrix<T>::GetElement(int row, int col, T &value) {
  for (int i = 0; i < this->Terms(); i++) {
    if (this->sparse_matrix_array_[i].row == row && this->sparse_matrix_array_[i].col == col) {
      value = this->sparse_matrix_array_[i].value;
      return true;
    }
  }

  return false;
}


template<class T>
bool SparseMatrix<T>::AddElement(int row, int col, T value) {

  if (row >= this->max_terms_ || col >= this->max_terms_) {
    return false;
  }

  for (int i = 0; i < this->Terms(); i++) {
    if (this->sparse_matrix_array_[i].row == row && this->sparse_matrix_array_[i].col == col) {
      this->sparse_matrix_array_[i].value = value;
      return true;
    }
  }

  if (this->Terms() == this->MaxTerms()) { // 不能再插入
    return false;
  }

  this->sparse_matrix_array_[this->terms_].row =  row;
  this->sparse_matrix_array_[this->terms_].col =  col;
  this->sparse_matrix_array_[this->terms_].value = value;

  this->terms_++;

  return true;
}


/*
template<class T>
SparseMatrix<T>& SparseMatrix<T>::FastTranspose() {
  return SparseMatrix<T>(0);
}
 */


#endif
/**
 * @brief  CYBER_DASH_TRI_TUPLE_H
 * 
 */