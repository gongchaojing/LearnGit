#include"Dijkstra.h"
#include <string>
#include <map>
#include <fstream>
#include <sstream>

//���캯��
Graph_DG::Graph_DG(int vexnum, int edge) {
    //��ʼ���������ͱ���
    this->vexnum = vexnum;
    this->edge = edge;
    //Ϊ�ڽӾ��󿪱ٿռ�͸���ֵ
    arc = new double*[this->vexnum];
    dis = new Dis[this->vexnum];
    for (int i = 0; i < this->vexnum; i++) {
        arc[i] = new double[this->vexnum];
        for (int k = 0; k < this->vexnum; k++) {
            //�ڽӾ����ʼ��Ϊ�����
                arc[i][k] = INT_MAX;
        }
    }
}
//��������
Graph_DG::~Graph_DG() {
    delete[] dis;
    for (int i = 0; i < this->vexnum; i++) {
        delete this->arc[i];
    }
    delete arc;
}

// �ж�����ÿ������ĵıߵ���Ϣ�Ƿ�Ϸ�
//�����1��ʼ���
bool Graph_DG::check_edge_value(int start, int end, int weight) {
    if (start<1 || end<1 || start>vexnum || end>vexnum || weight < 0) {
        return false;
    }
    return true;
}

void Graph_DG::createGraph() {
    cout << "������ÿ���ߵ������յ㣨�����Ŵ�1��ʼ���Լ���Ȩ��" << endl;
    int start;
    int end;
    double weight;
    int count = 0;
    while (count != this->edge) {
        cin >> start >> end >> weight;
        //�����жϱߵ���Ϣ�Ƿ�Ϸ�
        while (!this->check_edge_value(start, end, weight)) {
            cout << "����ıߵ���Ϣ���Ϸ�������������" << endl;
            cin >> start >> end >> weight;
        }
        //���ڽӾ����Ӧ�ϵĵ㸳ֵ
        arc[start - 1][end - 1] = weight;
        //����ͼ��������д���
        //arc[end - 1][start - 1] = weight;
        ++count;
    }
}

map<int,string> Graph_DG::createGraph(string infile_name) {
	ifstream infile(infile_name.c_str(),ios::in);
	string buffer;
	map<string,int> map_id;
	map<int,string> map_intid;
	map<string,int> :: iterator map_it;
	int count=0;
	while(getline(infile,buffer)){
		stringstream str_buffer(buffer);
		string node_source,node_target,edge_weight,tmp_query;
		str_buffer>>tmp_query>>node_source;
		map_it=map_id.find(node_source);
		if(map_it==map_id.end()){
			map_id[node_source]=count;
			map_intid[count]=node_source;
			count++;
		}
		while(str_buffer>>node_target>>edge_weight){
			double edge_weight_d=stod(edge_weight);
			map_it=map_id.find(node_target);
			if(map_it==map_id.end()){
				map_id[node_target]=count;
				map_intid[count]=node_target;
				count++;
			}
			if(edge_weight_d>=0.917)
				arc[map_id[node_source]][map_id[node_target]] = 1.00-edge_weight_d;
			//else
			//	arc[map_id[node_source]][map_id[node_target]] = INT_MAX;
		}
		
	}
    
    return map_intid;
}

void Graph_DG::print() {
    cout << "ͼ���ڽӾ���Ϊ��" << endl;
    int count_row = 0; //��ӡ�еı�ǩ
    int count_col = 0; //��ӡ�еı�ǩ
    //��ʼ��ӡ
    while (count_row != this->vexnum) {
        count_col = 0;
        while (count_col != this->vexnum) {
            if (arc[count_row][count_col] == INT_MAX)
                cout << "��" << " ";
            else
            cout << arc[count_row][count_col] << " ";
            ++count_col;
        }
        cout << endl;
        ++count_row;
    }
}

void Graph_DG::print(string outfilename,map<int,string> map_intid,map<string,string> map_meta) {
    
    ofstream outfile(outfilename.c_str(),ios::out);
    outfile<<"\t"<<"\t";
	for(int i=0;i<this->vexnum;i++){
		outfile<<map_meta[map_intid[i]]<<"\t";
	}
    outfile<<endl;
    int count_row = 0; //��ӡ�еı�ǩ
    int count_col = 0; //��ӡ�еı�ǩ
    //��ʼ��ӡ
    while (count_row != this->vexnum) {
    	outfile<<map_meta[map_intid[count_row]]<<"\t";
        count_col = 0;
        while (count_col != this->vexnum) {
            if (arc[count_row][count_col] == INT_MAX)
                outfile << "oo" << "\t";
            else
            outfile << arc[count_row][count_col] << "\t";
            ++count_col;
        }
        outfile << endl;
        ++count_row;
    }
}


void Graph_DG::Dijkstra(int begin){
    //���ȳ�ʼ�����ǵ�dis����
    
    int i;
    for (i = 0; i < this->vexnum; i++) {
        //���õ�ǰ��·��
        dis[i].path = "v" + to_string(begin) + "-->v" + to_string(i + 1);
        dis[i].value = arc[begin - 1][i];
    }
    //�������ĵ�����·��Ϊ0
    dis[begin - 1].value = 0;
    dis[begin - 1].visit = true;

    int count = 1;
    //����ʣ��Ķ�������·����ʣ��this->vexnum-1�����㣩
    while (count != this->vexnum) {
        //temp���ڱ��浱ǰdis��������С���Ǹ��±�
        //min��¼�ĵ�ǰ����Сֵ
        int temp=0;
        int min = INT_MAX;
        for (i = 0; i < this->vexnum; i++) {
            if (!dis[i].visit && dis[i].value<min) {
                min = dis[i].value;
                temp = i;
            }
        }
        //cout << temp + 1 << "  "<<min << endl;
        //��temp��Ӧ�Ķ�����뵽�Ѿ��ҵ������·���ļ�����
        dis[temp].visit = true;
        ++count;
        
        for (i = 0; i < this->vexnum; i++) {
        	 
            //ע�����������arc[temp][i]!=INT_MAX����ӣ���Ȼ�����������Ӷ���ɳ����쳣
            if (!dis[i].visit && arc[temp][i]!=INT_MAX && (dis[temp].value + arc[temp][i]) < dis[i].value) {
                //����µõ��ı߿���Ӱ������Ϊ���ʵĶ��㣬�Ǿ;͸����������·���ͳ���
                dis[i].value = dis[temp].value + arc[temp][i];
                dis[i].path = dis[temp].path + "-->v" + to_string(i + 1);
            }
        }
    }
    

}
void Graph_DG::Dijkstra(int begin,map<int,string> map_intid,map<string,string> map_meta){
    //���ȳ�ʼ�����ǵ�dis����
    for (int i = 0; i < this->vexnum; i++) {
        //���õ�ǰ��·��
        dis[i].path = map_meta[map_intid[begin-1]] + "-->" + map_meta[map_intid[i]];
        dis[i].value = arc[begin - 1][i];
        dis[i].visit = false;
    }
    //�������ĵ�����·��Ϊ0
    dis[begin - 1].value = 0;
    dis[begin - 1].visit = true;
	
    int count = 1;

    //����ʣ��Ķ�������·����ʣ��this->vexnum-1�����㣩
    while (count != this->vexnum) {
        //temp���ڱ��浱ǰdis��������С���Ǹ��±�
        //min��¼�ĵ�ǰ����Сֵ
        int temp=0;
        int min = INT_MAX;
        for (int i = 0; i < this->vexnum; i++) {
            if (!dis[i].visit && dis[i].value<min) {
                min = dis[i].value;
                temp = i;
            }
        }
        //cout << temp + 1 << "  "<<min << endl;
        //��temp��Ӧ�Ķ�����뵽�Ѿ��ҵ������·���ļ�����
        dis[temp].visit = true;
        ++count;
     
        for (int i = 0; i < this->vexnum; i++) {
        	
            //ע�����������arc[temp][i]!=INT_MAX����ӣ���Ȼ�����������Ӷ���ɳ����쳣
            if (!dis[i].visit && arc[temp][i]!=INT_MAX && (dis[temp].value + arc[temp][i]) < dis[i].value) {
                //����µõ��ı߿���Ӱ������Ϊ���ʵĶ��㣬�Ǿ;͸����������·���ͳ���
                dis[i].value = dis[temp].value + arc[temp][i];
                dis[i].path = dis[temp].path + "-->" + map_meta[map_intid[i]];
                
            }
            
        }
    }
    
     
    

}


void Graph_DG::print_path(int begin) {
    string str;
    str = "v" + to_string(begin);
    cout << "��"<<str<<"Ϊ����ͼ�����·��Ϊ��" << endl;
    for (int i = 0; i < this->vexnum; i++) {
    	
        if(dis[i].value!=INT_MAX)
        cout << dis[i].path << "=" << dis[i].value << "\t";
        else {
            cout << dis[i].path << "�������·����" << endl;
        }
    }
}


void Graph_DG::print_path(int begin,string outfilename,map<int,string> map_intid) {
    ofstream outfile(outfilename.c_str(),ios::app);
	string str;
    //str = "v" + to_string(begin);
    //cout << "��"<<str<<"Ϊ����ͼ�����·��Ϊ��" << endl;
    outfile<<map_intid[begin-1]<<"\t";
    for (int i = 0; i != this->vexnum; i++) {
    	
        if(dis[i].value!=INT_MAX)
        outfile << dis[i].path << "=" << dis[i].value << "\t";
        else {
            outfile << "oo" << "\t";
        }
    }
    outfile<<endl;
}
