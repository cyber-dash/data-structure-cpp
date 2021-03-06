/*!
 * @file matrix_graph.h
 * @author CyberDash计算机考研, cyberdash@163.com(抖音id:cyberdash_yuan)
 * @brief 矩阵图模板类
 * @version 0.2.1
 * @date 2021-07-14
 * @copyright Copyright (c) 2021
 *  CyberDash计算机考研
 */

#ifndef CYBER_DASH_MATRIX_GRAPH_H
#define CYBER_DASH_MATRIX_GRAPH_H


#include "graph.h"
#include <iostream>
#include <map>


using namespace std;


/*!
 * @brief 矩阵图模板类
 * @tparam Vertex 结点类型模板参数
 * @tparam Weight 边权值类型模板参数
 */
template<class Vertex, class Weight>
class MatrixGraph: public Graph<Vertex, Weight> {

public:
  // 构造函数
  MatrixGraph(int size = DEFAULT_VERTICES);

  // 析构函数
  ~MatrixGraph();

  /*!
   * @brief 获取节点(由结点索引)
   * @param vertex 结点(用于保存结果)
   * @param vertex_index 结点索引
   * @return 是否获取成功
   */
  bool GetVertexByIndex(Vertex& vertex, int vertex_index);

  // (由边的两个结点)获取边权值
  bool GetWeight(Weight& weight, Vertex v1, Vertex v2);

  // (由边的两个结点索引)获取边权值
  bool GetWeightByVertexIndex(Weight& weight, int v1_index, int v2_index);

  /*!
   * @brief 插入结点
   * @param vertex 节点
   * @return 是否插入成功
   */
  bool InsertVertex(const Vertex& vertex);

  /*!
   * @brief 删除结点
   * @param vertex 节点
   * @return 是否删除成功
   */
  bool RemoveVertex(Vertex vertex);

  /*!
   * @brief 插入边
   * @param vertex1 边节点1
   * @param vertex2 边节点2
   * @param weight 边权值
   * @return 是否插入成功
   */
  bool InsertEdge(Vertex vertex1, Vertex vertex2, Weight weight);

  /*!
   * @brief 删除边
   * @param vertex1 边结点1
   * @param vertex2 边结点2
   * @return 是否删除成功
   */
  bool RemoveEdge(Vertex vertex1, Vertex vertex2);

  /*!
   * 获取第一个相邻结点
   * @param first_neighbor 第一个相邻结点(用于保存节点)
   * @param vertex 节点
   * @return 是否获取成功
   */
  bool GetFirstNeighborVertex(Vertex& first_neighbor, const Vertex& vertex);

  /*!
   * @brief 获取下一个相邻结点
   * @param next_neighbor_vertex 下一个相邻结点(用于保存结点)
   * @param vertex 结点
   * @param neighbor_vertex 当前相邻结点
   * @return 是否获取成功
   */
  bool GetNextNeighborVertex(Vertex& next_neighbor_vertex, const Vertex& vertex, const Vertex& neighbor_vertex);

  /*!
   * @brief 获取结点索引
   * @param vertex 结点
   * @return 结点索引
   */
  int GetVertexIndex(Vertex vertex);

  template<class U>
  friend istream& operator>>(istream& in, MatrixGraph<Vertex, Weight>& graph_matrix);
  template<class U>
  friend ostream& operator<<(ostream& out, MatrixGraph<Vertex, Weight>& graph_matrix);

  void PrintMatrix();
  void CyberDashShow();

  map<pair<Vertex, Vertex>, Weight> edge_map; // todo: 用于保存边集合, 未实现

private:
  Vertex* vertices_list_; //!< 结点列表
  Weight** adjacency_matrix_; //!< 边矩阵
};


/*!
 * @brief 构造函数
 * @tparam Vertex 结点类型模板参数
 * @tparam Weight 边权值类型模板参数
 * @param size 最大结点数
 */
template<class Vertex, class Weight>
MatrixGraph<Vertex, Weight>::MatrixGraph(int size) {

  this->max_vertex_cnt_ = size;
  this->vertex_cnt_ = 0;
  this->edge_cnt_ = 0;

  // 所有节点
  this->vertices_list_ = new Vertex[this->max_vertex_cnt_];
  /* error handler */

  this->adjacency_matrix_ = (Weight**)new Weight*[this->max_vertex_cnt_];
  /* error handler */

  for (int i = 0; i < this->max_vertex_cnt_; i++) {
    this->adjacency_matrix_[i] = new Weight[this->max_vertex_cnt_]; // 节点i对应的所有边
    for (int j = 0; j < this->max_vertex_cnt_; j++) {
      this->adjacency_matrix_[i][j] = (i == j) ? 0 : MAX_WEIGHT;
    }
  }
}


/*!
 * @brief 析构函数
 * @tparam Vertex 结点类型模板参数
 * @tparam Weight 边权值类型模板参数
 */
template<class Vertex, class Weight>
MatrixGraph<Vertex, Weight>::~MatrixGraph() {
  delete[] this->vertices_list_;
  delete[] this->adjacency_matrix_;
}


/*!
 * @brief 使用结点索引获取结点
 * @param vertex 结点(保存结果的节点)
 * @param vertex_index 结点索引
 * @return 是否获取成功
 */
template<class Vertex, class Weight>
bool MatrixGraph<Vertex, Weight>::GetVertexByIndex(Vertex& vertex, int vertex_index) {
  if (vertex_index >= 0 && vertex_index <= this->vertex_cnt_) {
    vertex = this->vertices_list_[vertex_index];
    return true;
  } else {
    return false;
  }
}


/*!
 * @brief 获取边权值
 * @tparam Vertex
 * @tparam Weight
 * @param weight
 * @param v1
 * @param v2
 * @return
 */
template<class Vertex, class Weight>
bool MatrixGraph<Vertex, Weight>::GetWeight(Weight& weight, Vertex v1, Vertex v2) {

  int v1_index = GetVertexIndex(v1);
  int v2_index = GetVertexIndex(v2);
  if (v1_index < 0 || v2_index < 0) {
      return false;
  }

  bool res = GetWeightByVertexIndex(weight, v1_index, v2_index);

  return res;
}


template<class Vertex, class Weight>
bool MatrixGraph<Vertex, Weight>::GetWeightByVertexIndex(Weight& weight, int v1_index, int v2_index) {

    if (v1_index >= 0 && v2_index >= 0 &&
        v1_index != v2_index &&
        adjacency_matrix_[v1_index][v2_index] != MAX_WEIGHT &&
        adjacency_matrix_[v1_index][v2_index] > 0)
    {
        weight = adjacency_matrix_[v1_index][v2_index];

        return true;
    }

    return false;
}


template<class Vertex, class Weight>
bool MatrixGraph<Vertex, Weight>::GetFirstNeighborVertex(Vertex& first_neighbor, const Vertex& vertex) {

  int vertex_index = GetVertexIndex(vertex);

  if (vertex_index < 0) {
    return false;
  }

  for (int cur_index = 0; cur_index < this->vertex_cnt_; cur_index++) {
    Weight weight;
    Vertex cur_vertex;

    bool done = GetVertexByIndex(cur_vertex, cur_index);
    if (!done) {
      continue;
    }

    bool has_weight = GetWeight(weight, vertex, cur_vertex);
    if (has_weight) {
      first_neighbor = cur_vertex;
      return true;
    }
  }

  return false;
}


template<class Vertex, class Weight>
bool MatrixGraph<Vertex, Weight>::GetNextNeighborVertex(Vertex& next_neighbor_vertex, const Vertex& vertex, const Vertex& neighbor_vertex) {

  int vertex_index = GetVertexIndex(vertex);
  int neighbor_vertex_index = GetVertexIndex(neighbor_vertex);

  if (vertex_index < 0 && neighbor_vertex_index < 0) {
    return false;
  }

  for (int cur_index = neighbor_vertex_index + 1; cur_index < this->vertex_cnt_; cur_index ++) {
    Weight weight;
    Vertex cur_vertex;

    bool done = GetVertexByIndex(cur_vertex, cur_index);
    if (!done) {
      continue;
    }

    bool has_weight = GetWeight(weight, vertex, cur_vertex);
    if (has_weight) {
      next_neighbor_vertex = cur_vertex;
      return true;
    }
  }

  return false;
}


template<class Vertex, class Weight>
bool MatrixGraph<Vertex, Weight>::InsertVertex(const Vertex& vertex) {
  if (this->vertex_cnt_ >= this->max_vertex_cnt_) {
    return false;
  }

  this->vertices_list_[this->vertex_cnt_] = vertex;
  this->vertex_cnt_++;

  return true;
}


template<class Vertex, class Weight>
bool MatrixGraph<Vertex, Weight>::InsertEdge(Vertex vertex1, Vertex vertex2, Weight weight) {

  int v1_index = GetVertexIndex(vertex1);
  int v2_index = GetVertexIndex(vertex2);

  if (v1_index < 0 || v2_index < 0 || v1_index == v2_index)
  {
    return false;
  }

  this->adjacency_matrix_[v1_index][v2_index] = weight;
  this->adjacency_matrix_[v2_index][v1_index] = weight;

  this->edge_cnt_++;

  pair<Vertex, Vertex> edge1(vertex1, vertex2);
  pair<Vertex, Vertex> edge2(vertex2, vertex1);

  this->edge_map.insert(pair<pair<Vertex, Vertex>, Weight>(edge1, weight));
  this->edge_map.insert(pair<pair<Vertex, Vertex>, Weight>(edge2, weight));

  return true;
}


template<class Vertex, class Weight>
bool MatrixGraph<Vertex, Weight>::RemoveVertex(Vertex vertex) {

  int vertex_index = GetVertexIndex(vertex);

  if (vertex_index < 0 || vertex_index >= this->vertex_cnt_) {
    return false;
  }

  // 只剩1个顶点 todo: 实际上可以删除
  if (this->vertex_cnt_ == 1) {
    return false;
  }

  this->vertices_list_[vertex_index] = this->vertices_list_[this->vertex_cnt_ - 1];

  for (int i = 0; i < this->vertex_cnt_; i++) {
    if (this->adjacency_matrix_[i][vertex_index] > 0 && this->adjacency_matrix_[i][vertex_index] < MAX_WEIGHT) {
      this->edge_cnt_--;
    }
  }

  for (int row = 0; row < this->vertex_cnt_; row++) {
    this->adjacency_matrix_[row][vertex_index] = this->adjacency_matrix_[row][this->vertex_cnt_ - 1];
  }

  for (int col = 0; col < this->vertex_cnt_; col++) {
    this->adjacency_matrix_[vertex_index][col] = this->adjacency_matrix_[this->vertex_cnt_ - 1][col];
  }

  this->vertex_cnt_--;

  return true;
}


template<class Vertex, class Weight>
bool MatrixGraph<Vertex, Weight>::RemoveEdge(Vertex vertex1, Vertex vertex2) {

  int v1_index = GetVertexIndex(vertex1);
  int v2_index = GetVertexIndex(vertex2);

  Weight weight;
  bool has_weight = GetWeight(weight, vertex1, vertex2);
  if (has_weight) {
    this->adjacency_matrix_[v1_index][v2_index] = MAX_WEIGHT;
    this->adjacency_matrix_[v2_index][v1_index] = MAX_WEIGHT;

    this->edge_cnt_--;

    return true;
  }

  return false;
}


// todo: 需要测试, 但这个方法太笨重了, 懒得动 :-(
template<class Vertex, class Weight>
istream& operator>>(istream& in, MatrixGraph<Vertex, Weight>& graph_matrix) {

  int vertex_num;
  int edge_num;
  Vertex src_vertex;
  Vertex dest_vertex;
  Weight weight;

  cout<<"Input the vertex_num and edge_num"<<endl;
  in >> vertex_num >> edge_num;

  for (int i = 0; i < vertex_num; i++) {

    cout<<"src_vertex "<<i<<":"<<endl;
    in >> src_vertex;

    graph_matrix.InsertVertex(src_vertex);
  }

  for (int i = 0; i < edge_num; i++) {

    cout<<"AdjListEdge "<<i<<":"<<endl;
    in >> src_vertex >> dest_vertex >> weight;

    int src_vertex_index = graph_matrix.GetVertexIndex(src_vertex);
    int dest_vertex_index = graph_matrix.GetVertexIndex(dest_vertex);

    if (src_vertex_index < 0 || dest_vertex_index < 0) {
      cout<<"Error input"<<endl;
      continue;
    }

    graph_matrix.InsertEdge(src_vertex_index, dest_vertex_index, weight);
  }
}


template<class Vertex, class Weight>
ostream& operator<<(ostream& out, MatrixGraph<Vertex, Weight>& graph_matrix) {

  int vertex_num = graph_matrix.VertexCount();
  int edge_num = graph_matrix.EdgeCount();

  cout<<"vertex_num: "<<vertex_num<<", edge_num: "<<edge_num<<endl;

  for (int src_vertex_index = 0; src_vertex_index < vertex_num; src_vertex_index++) {
    for (int dest_vertex_index = 0; dest_vertex_index < vertex_num; dest_vertex_index++) {

      Weight weight = graph_matrix.GetWeight(src_vertex_index, dest_vertex_index);

      if (weight > 0 && weight < MAX_WEIGHT) {

        Vertex e1 = graph_matrix.GetValue(src_vertex_index);
        Vertex e2 = graph_matrix.GetValue(dest_vertex_index);

        out << "(" << e1 << "," << e2 << "," << weight << ")" << endl;
      }
    }
  }
}


/*!
 * 获取结点索引
 * @tparam Vertex 结点类型模板参数
 * @tparam Weight 边权值类型模板参数
 * @param vertex 结点
 * @return
 */
template<class Vertex, class Weight>
int MatrixGraph<Vertex, Weight>::GetVertexIndex(Vertex vertex) {

  int vertex_index = -1;

  for (int i = 0; i < this->vertex_cnt_; i++) {
    if (this->vertices_list_[i] == vertex) {
      vertex_index = i;
      break;
    }
  }

  return vertex_index;
}


/*!
 * 打印图邻接矩阵
 * @tparam Vertex 结点类型模板参数
 * @tparam Weight
 */
template<class Vertex, class Weight>
void MatrixGraph<Vertex, Weight>::PrintMatrix() {
  for (int i = 0; i < this->vertex_cnt_; i++) {
    for (int j = 0; j < this->vertex_cnt_; j++) {
      cout << this->adjacency_matrix_[i][j] << "  ";
    }
    cout<<endl;
  }
}


template<class Vertex, class Weight>
void MatrixGraph<Vertex, Weight>::CyberDashShow() {
  cout<<endl
      <<"*************************************** CyberDash ***************************************"<<endl<<endl
      <<"抖音号\"CyberDash计算机考研\", id: cyberdash_yuan"<<endl<<endl
      <<"CyberDash成员:"<<endl
      <<"元哥(cyberdash@163.com), "<<"北京邮电大学(通信工程本科)/北京邮电大学(信息与通信系统研究生)"<<endl
      <<"磊哥(alei_go@163.com), "<<"山东理工大学(数学本科)/北京邮电大学(计算机研究生)"<<endl<<endl
      <<"L_Dash(lyu2586@163.com), "<<"北京邮电大学(计算机在读研究生)"<<endl<<endl
      <<"数据结构开源代码(C++版本): https://gitee.com/cyberdash/data-structure-cpp"<<endl
      <<endl<<"*************************************** CyberDash ***************************************"<<endl<<endl;
}


#endif //CYBER_DASH_MATRIX_GRAPH_H
