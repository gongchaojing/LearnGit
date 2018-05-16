#include"Dijkstra.cpp"
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <omp.h>

//检验输入边数和顶点数的值是否有效，可以自己推算为啥：
//顶点数和边数的关系是：((Vexnum*(Vexnum - 1)) / 2) < edge
bool check(int Vexnum, int edge) {
    if (Vexnum <= 0 || edge <= 0 || ((Vexnum*(Vexnum - 1)) / 2) < edge)
        return false;
    return true;
}

vector <int> find_vex_edge(string infilename){
	
	ifstream infile(infilename.c_str(),ios::in);
	string buffer,node_target,node_source,tmp_weight;
	map<string,int> map_id;
	int vexnum=0,edge=0;
	map<string,int> :: iterator map_it;
	while(getline(infile,buffer)){
		stringstream str_buf(buffer);
		str_buf>>tmp_weight>>node_source;
		map_it=map_id.find(node_source);
		if(map_it==map_id.end()){
			map_id[node_source]=vexnum++;
			
		}
		while(str_buf>>node_target>>tmp_weight){
			map_it=map_id.find(node_target);
			if(map_it==map_id.end()){
				map_id[node_target]=vexnum++;
				edge++;
			}
			else{
				edge++;
			}
		}
	}
	vector<int> vec_vex_edge;

	vec_vex_edge.push_back(vexnum);
	vec_vex_edge.push_back(edge);
	infile.close();
	return vec_vex_edge;
	
}

map<string,string> gene_meta(string infile_name){
	ifstream infile(infile_name.c_str(),ios::in);
	map<string,string> map_meta;
	string buffer,id,meta;
	while(getline(infile,buffer)){
		stringstream str_buffer(buffer);
		str_buffer>>id>>meta;
		map_meta[id]=meta;
	}
	infile.close();
	return map_meta; 
}

int main() {
    //int vexnum; int edge;
	string buf_infile="2011.out";
	string meta_infile="all_dup.meta";
	map<string,string> map_meta;
	map_meta = gene_meta(meta_infile); 
	vector<int> vec_vex_edge;
	vec_vex_edge=find_vex_edge(buf_infile);
	vector<vector<string> > matrix_path;
	for(int i=0;i<vec_vex_edge[0];i++)
	{
		vector<string> vec_temp;
		for(int j=0;j<vec_vex_edge[0];j++)
			vec_temp.push_back("");
		matrix_path.push_back(vec_temp);
	}  
    
	Graph_DG graph(vec_vex_edge[0],vec_vex_edge[1]);
   	cout<<"Now the graph init completed!"<<endl;
    
    
    map<int,string> map_intid;
    map_intid=graph.createGraph(buf_infile);
	cout<<"Now the graph create completed!"<<endl;
	
	
    //graph.print();
    string outfilename="matrix.all.out";
    string outfilename_graph="Dijstra.all.out";
    graph.print(outfilename,map_intid,map_meta);
    cout<<"Now the graph print completed!"<<endl;
    
    
    #pragma omp parallel for num_threads(50)
    for(int i=1;i<=vec_vex_edge[0];i++){
    	cout<<i<<endl;
    	graph.Dijkstra(i,map_intid,map_meta,matrix_path);
    	//graph.print_path(i,outfilename_graph,map_intid);
	}
	cout<<"Now the Dijkstra for everynode complete!"<<endl;
    
    ofstream outfile_graph(outfilename_graph.c_str(),ios::out);
    outfile_graph<<" "<<"\t";
	for(int i=0;i<vec_vex_edge[0];i++){
		outfile_graph<<map_intid[i]<<"\t";
	}
	outfile_graph<<endl;
	graph.print_path(outfilename_graph,matrix_path,map_intid);
    outfile_graph.close(); 
    system("pause");
    return 0;
}
