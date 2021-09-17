//
// Created by cyberdash@163.com(抖音: cyberdash_yuan) on 2020/7/29.
//

#include <iostream>
#include <cstdlib>
#include <cstring>
#include "cyber_dash_string.h"


using namespace std;


CyberDashString::CyberDashString(int size) {

  max_size_ = size;

  char_array_ = new char[max_size_ + 1];
  if (char_array_ == NULL) {
    cerr<<"Allocation Error"<<endl;
    exit(1);
  }

  length_ = 0;
  char_array_[0] = '\0';
}


CyberDashString::CyberDashString(const char* char_ptr) {
  int char_len = strlen(char_ptr);

  if (char_len > DEFAULT_SIZE) {
    max_size_ = char_len;
  } else {
    max_size_ = DEFAULT_SIZE;
  }

  char_array_ = new char[max_size_ + 1];
  if (char_array_ == NULL) {
    cerr<<"Allocation Error"<<endl;
    exit(1);
  }

  length_ = char_len;

  memcpy(char_array_, char_ptr, char_len);
}


CyberDashString::~CyberDashString() {
  delete[] char_array_;
}


int CyberDashString::Length() const {
  return length_;
}


CyberDashString CyberDashString::operator () (int index, int offset) const {

  CyberDashString ret_str(offset + 1);

  if (index < 0 || index + offset > max_size_ || offset <= 0 || index + 1 > length_) {

    ret_str.length_ = 0;
    ret_str.char_array_[0] = '\0';
  } else {

    if (index + offset > length_) {
      offset = length_ - index;
    }

    ret_str.length_ = offset;

    memcpy(ret_str.char_array_, char_array_ + index, offset);

    ret_str.char_array_[offset] = '\0';
  }

  return ret_str;
}


bool CyberDashString::operator == (const CyberDashString& cyber_dash_str) const {
  int cmp_res = strcmp(char_array_, cyber_dash_str.char_array_);
  if (cmp_res == 0) {
    return true;
  } else {
    return false;
  }
}


bool CyberDashString::operator != (CyberDashString& cyber_dash_str) const {
  int cmp_res = strcmp(char_array_, cyber_dash_str.char_array_);
  if (cmp_res != 0) {
    return true;
  } else {
    return false;
  }
}


bool CyberDashString::operator ! () const {
  return true;
}


CyberDashString& CyberDashString::operator = (const CyberDashString& src_str) {

  if (&src_str != this) {

    delete[] char_array_;

    char_array_ = new char[src_str.max_size_ + 1];
    if (char_array_ == NULL) {
      cerr<<"存储分配失败!"<<endl;
      exit(1);
    }

    memcpy(char_array_, src_str.char_array_, src_str.length_);

    length_ = src_str.length_;

  } else {
    cout<<"字符串自身赋值出错"<<endl;
  }

  return *this;
}


CyberDashString& CyberDashString::operator += (CyberDashString& cyber_dash_str) {
  return *this;
}


char& CyberDashString::operator[] (int index) {
  if (index < 0 || index >= Length()) {
    cerr<<"Out of Range."<<endl;
    exit(1);
  }

  return char_array_[index];
}


int CyberDashString::BruteForceFind(CyberDashString& pattern, int offset) const {

  int match_offset = -1;
  int pat_idx;

  for (int i = offset; i <= length_ - pattern.length_; i++) {
    for (pat_idx = 0; pat_idx < pattern.length_; pat_idx++) {
      if (char_array_[i + pat_idx] != pattern[pat_idx]) {
        break;
      }
    }

    if (pat_idx == pattern.length_) {
      match_offset = i;
      break;
    }
  }

  return match_offset;
}


int* CyberDashString::KMPNext(const char* pattern, int pattern_len) {

  int i = 0;
  int starting_index = -1;

  int* next = new int[pattern_len];
  if (next == NULL) {
    cerr<<"next array allocate error"<<endl;
    return NULL;
  }

  next[0] = starting_index;

  while (i < pattern_len) {

    if (starting_index == -1) {
      i++;
      starting_index = 0;
      next[i] = starting_index;
    } else { // 使用next[i]求next[i + 1]
      if (pattern[i] == pattern[starting_index]) {
        i++;
        starting_index++;
        next[i] = starting_index;
      }
      else
      {
        starting_index = next[starting_index];
      }
    }
  }

  return next;
}


int* CyberDashString::KMPNextByCyberDash(const char* pattern, int pattern_len) {

  int* next = new int[pattern_len];
  if (next == NULL) {
    cerr<<"next array allocate error"<<endl;
    return NULL;
  }

  next[0] = -1;
  next[1] = 0;

  int i = 1;
  int starting_index = 0;

  while (i < pattern_len) {
    if (pattern[i] == pattern[starting_index]) {
      i++;
      starting_index++;
      next[i] = starting_index;
    } else {
      if (starting_index == 0) {
        i++;
        next[i] = starting_index;
      } else {
        starting_index = next[starting_index];
      }
    }
  }

  return next;
}


void CyberDashString::PrintNextArray(const int* next_arr_ptr, int next_arr_len) {
  /// 示例
  /// 模式字符串:  a b c d 5 6 a b c d 7
  /// next数组:  -1 0 0 0 0 0 0 1 2 3 4
  for (int i = 0; i < next_arr_len; i++) {
    cout<<*(next_arr_ptr + i)<<" ";
  }
  cout<<endl;
}


int CyberDashString::KMPFind(CyberDashString& pattern, int offset) const {

  cout<<pattern;

  int pattern_len = pattern.Length();
  int* next = KMPNext(pattern.char_array_, pattern_len);
  PrintNextArray(next, pattern_len);
  if (!next) {
    cerr<<"next array allocation error"<<endl;
    return -2;
  }

  int pattern_str_i = 0;
  int target_str_i = offset;

  while (pattern_str_i < pattern_len && target_str_i < this->length_) {
    /// 如果模式串字符(位置pattern_str_i)和目标串字符(位置target_str_i)相同, 则向后移位
    if (pattern[pattern_str_i] == this->char_array_[target_str_i]) {
      pattern_str_i++;
      target_str_i++;
    }
    /// 如果模式串字符(位置pattern_str_i)和目标串字符(位置target_str_i)不同
    else
    {
      // 如果是模式串第1个字符不匹配, 则目标串向后移位
      if (pattern_str_i == 0) {
        target_str_i++;
      }
      // 如果不是模式串第1个字符不匹配,
      else
      {
        pattern_str_i = next[pattern_str_i];
      }
    }
  }

  delete[] next;

  int match_pos;

  if (pattern_str_i < pattern_len) {
    match_pos = -1;
  } else {
    match_pos = target_str_i - pattern_len;
  }

  return match_pos;
}


int CyberDashString::KMPFindCyberDash(CyberDashString& pattern, int offset) const {

  int match_pos;

  int pattern_len = pattern.Length();
  int* next = KMPNextByCyberDash(pattern.char_array_, pattern_len);
  PrintNextArray(next, pattern_len);
  if (!next) {
    cerr<<"next array allocation error"<<endl;
    return -2;
  }

  int pattern_index = 0;
  int target_str_index = offset;

  while (pattern_index < pattern_len && target_str_index < length_) {
    if (pattern_index == -1 || pattern[pattern_index] == char_array_[target_str_index]) {
      pattern_index++;
      target_str_index++;
    } else {
      pattern_index = next[pattern_index];
    }
  }

  delete[] next;

  if (pattern_index < pattern_len) {
    match_pos = -1;
  } else {
    match_pos = target_str_index - pattern_len;
  }

  return match_pos;
}


void CyberDashString::CyberDashShow() {
  cout<<endl
      <<"*************************************** CyberDash ***************************************"<<endl<<endl
      <<"抖音号\"CyberDash计算机考研\", id: cyberdash_yuan"<<endl<<endl
      <<"CyberDash成员:"<<endl
      <<"元哥(cyberdash@163.com), "<<"北京邮电大学(通信工程本科)/北京邮电大学(信息与通信系统研究生)"<<endl
      <<"磊哥(alei_go@163.com), "<<"山东理工大学(数学本科)/北京邮电大学(计算机研究生)"<<endl<<endl
      <<"数据结构开源代码(C++清华大学殷人昆)魔改升级版本: https://gitee.com/cyberdash/data-structure-cpp"<<endl
      <<endl<<"*************************************** CyberDash ***************************************"<<endl<<endl;
}
