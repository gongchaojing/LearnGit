/************************************************************/
/*                �������ߣ�Willam                          */
/*                �������ʱ�䣺2017/3/8                    */
/*                ���κ���������ϵ��2930526477@qq.com       */
/************************************************************/
//@����д�������ĳ���

#pragma once
//#pragma once��һ���Ƚϳ��õ�C/C++��ע��
//ֻҪ��ͷ�ļ����ʼ����������ע��
//���ܹ���֤ͷ�ļ�ֻ������һ�Ρ�

#include<iostream>
#include<string>
#include<map> 
#include<vector>
#include<limits.h>

using namespace std;

/*
��������ʹ��Dijkstra�㷨ʵ��������·��������
���õ��ڽӾ������洢ͼ
*/
//��¼��㵽ÿ����������·������Ϣ
struct Dis {
    string path;
    double value;
    bool visit;
    Dis() {
        visit = false;
        value = 0;
        path = "";
    }
};

class Graph_DG {
private:
    int vexnum;   //ͼ�Ķ������
    int edge;     //ͼ�ı���
   	double **arc;   //�ڽӾ���
    Dis * dis;   //��¼�����������·������Ϣ
public:
    //���캯��
    Graph_DG(int vexnum, int edge);
    //��������
    ~Graph_DG();
    // �ж�����ÿ������ĵıߵ���Ϣ�Ƿ�Ϸ�
    //�����1��ʼ���
    bool check_edge_value(int start, int end, int weight);
    //����ͼ
    void createGraph();
    //
    map<int,string> createGraph(string infilename);
    //��ӡ�ڽӾ���
    void print();
    
    void print(string outfilename,map<int,string> map_intid,map<string,string> map_meta);
    //�����·��
    void Dijkstra(int begin);
    void Dijkstra(int begin,map<int,string> map_intid,map<string,string> map_meta,vector< vector<string> > &matrix_path);
    //��ӡ���·��
    void print_path(int);
    void print_path(int begin,string outfilename,map<int,string> map_intid);
    void print_path(string outfilename_graph, vector< vector<string> > &matrix_path, map<int,string> map_intid);
};
