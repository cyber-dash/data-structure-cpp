/**
 * @file sparse_matrix.h
 * @author CyberDash计算机考研, cyberdash@163.com(抖音id:cyberdash_yuan)
 * @brief 稀疏矩阵 
 * @version 0.2.1
 * @date 2021-05-13
 * 
 * @copyright Copyright (c) 2021
 *  CyberDash计算机考研
 */

#ifndef CYBER_DASH_SPARSE_MATRIX_H
#define CYBER_DASH_SPARSE_MATRIX_H


#include <iostream>
#include <cstdlib>


using namespace std;


//! 稀疏矩阵三元组结构体
template<class T>
struct TriTuple {
  int row; //!< 行索引
  int col; //!< 列索引
  T value; //!< 值

  /*!
   * @brief 赋值运算符重载函数
   * @param tri_tuple 稀疏函数三元组数据
   * @return 当前对象本身
   */
  TriTuple<T>& operator=(TriTuple<T>& tri_tuple) {
    row = tri_tuple.row;
    col = tri_tuple.col;
    value = tri_tuple.value;

    return *this;
  }
};


//! 稀疏矩阵模板类
template<class T>
class SparseMatrix {
public:

  // 构造函数(参数为稀疏矩阵最大元素个数)
  SparseMatrix(int max_size = 100);

  // 复制构造函数(参数为稀疏矩阵)
  SparseMatrix(SparseMatrix<T>& sparse_matrix);

  // 析构函数
  virtual ~SparseMatrix() { delete[] sparse_matrix_array_; }

  // 获取行数
  int Rows() { return this->rows_; }
  // 设置行数
  void SetRows(int rows) { this->rows_ = rows; }

  // 获取列数
  int Cols() { return this->cols_; };
  // 设置行数
  void SetCols(int cols) { this->cols_ = cols; };

  // 获取元素数
  int Terms() { return this->terms_; }
  // 设置元素数
  int SetTerms(int terms) { this->terms_ = terms; }

  // 获取最大元素数
  int MaxTerms() { return this->max_terms_; }
  // 设置最大元素数
  int SetMaxTerms(int max_terms) { this->max_terms_ = max_terms; }

  // 获取元素
  bool GetElement(int row, int col, T& value);
  // 添加元素(如果此位置元素存在, 则覆盖)
  bool AddElement(int row, int col, T value);

  // 获取元素数组起始地址
  TriTuple<T>* SparseMatrixArray() { return this->sparse_matrix_array_; }

  // 赋值运算符重载函数
  SparseMatrix<T>& operator = (SparseMatrix<T>& sparse_matrix);

  // 转置运算
  SparseMatrix<T>* Transpose();

  // 快速转置运算
  SparseMatrix<T>* FastTranspose();

  // 当前矩阵与sparse_matrix相加 todo: 未实现
  SparseMatrix<T> Add(SparseMatrix<T>& sparse_matrix);

  // 当前矩阵与矩阵sparse_matrix相乘 todo: 未实现
  SparseMatrix<T> Multiply(SparseMatrix<T>& sparse_matrix);

  // 打印稀疏矩阵
  template <class U>
  friend ostream& operator << (ostream& out, SparseMatrix<T>& sparse_matrix);
  // 输入稀疏矩阵
  template <class U>
  friend istream& operator >> (istream& in, SparseMatrix<T>& sparse_matrix);

private:
  int rows_; //!< 行数

  int cols_; //!< 列数

  int terms_; //!< 当前元素数

  int max_terms_; //!< 最大元素数

  TriTuple<T>* sparse_matrix_array_; //!< 元素数组
};


/*!
 * @brief 构造函数(参数为稀疏矩阵最大元素个数)
 * @tparam T 模板参数类型
 * @param max_size 最大元素个数
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


/*!
 * @brief 复制构造函数(参数为稀疏矩阵)
 * @tparam T 模板参数类型
 * @param sparse_matrix 稀疏矩阵(的引用)
 */
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


/*!
 * @brief 赋值运算符重载函数
 * @tparam T 模板参数类型
 * @param sparse_matrix 稀疏矩阵(的引用)
 * @return 当前数组本身
 */
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

  return *this;
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


/**
 * @brief 稀疏矩阵快速转置
 * @tparam T 模板数据类型
 * @return 转置矩阵的指针
 */
template<class T>
SparseMatrix<T>* SparseMatrix<T>::FastTranspose() {
  int* row_size_arr = new int[this->Cols()];
  int* row_start_arr = new int[this->Cols()];

  SparseMatrix<T>* trans_sparse_matrix_ptr = new SparseMatrix<T>(this->MaxTerms());

  trans_sparse_matrix_ptr->SetRows(this->Cols());
  trans_sparse_matrix_ptr->SetCols(this->Rows());
  trans_sparse_matrix_ptr->SetTerms(this->Terms());

  if (this->Terms() == 0) {
    return trans_sparse_matrix_ptr;
  }

  for (int i = 0; i < this->Cols(); i++) {
    row_size_arr[i] = 0;
  }

  for (int i = 0; i < this->Terms(); i++) {
    row_size_arr[this->SparseMatrixArray()[i].col]++;  // 转置后的第this->SparseMatrixArray()[i].col行个数++
  }

  row_start_arr[0] = 0; // sparse_matrix_array_数组的索引0位置的数据, 保存转置后的0行
  for (int i = 1; i < this->Cols(); i++) {
    row_start_arr[i] = row_start_arr[i - 1] + row_size_arr[i - 1];
  }

  for (int i = 0; i < this->Terms(); i++) {
    int cur_start_pos = row_start_arr[this->SparseMatrixArray()[i].col];

    trans_sparse_matrix_ptr->SparseMatrixArray()[cur_start_pos].row = this->SparseMatrixArray()[i].col;
    trans_sparse_matrix_ptr->SparseMatrixArray()[cur_start_pos].col = this->SparseMatrixArray()[i].row;
    trans_sparse_matrix_ptr->SparseMatrixArray()[cur_start_pos].value = this->SparseMatrixArray()[i].value;

    row_start_arr[this->SparseMatrixArray()[i].col]++; // 完成后, 向后挪一位
  }

  delete[] row_start_arr;
  delete[] row_size_arr;

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


#endif