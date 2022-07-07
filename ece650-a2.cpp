
#include <iostream>
#include <vector>
#include<unistd.h>

using namespace std;


vector<vector<int>> make_graph(vector<vector<int>> graph, int vertices){

    vector <vector<int>>v ={};
    int graph_size = graph.size();

    for(int i=0;i <vertices;i++){
        vector <int>inv = {};
        v.push_back(inv);
    }
    // std::cout << v.size();
   for(int i = 0; i < graph_size; i++)
   {
    //   std::cout<<graph[i][0]<<" "<<graph[i][1]<<endl;
       v[graph[i][0]-1].push_back(graph[i][1]);
       v[graph[i][1]-1].push_back(graph[i][0]);
   }
//   std::cout<<v.size();


     return v;

}

void shortest_path(vector <vector<int>>v, int s, int d, int n){

    vector <int>visited = {};
    visited.assign(n, false);


    visited[s-1] = true;
    vector <int>path = {};
    path.assign(n,0);

    vector<int> q = {};
    q.push_back(s);

    int v_size = 0;
    while (!q.empty())
    {
        s = q[0];
        q.erase(q.begin());
        v_size = v[s-1].size();
        for(int i=0; i< v_size; i++)
        {
            if(!visited[v[s-1][i]-1])
            {
                visited[v[s-1][i]-1] = true;
                q.push_back(v[s-1][i]);
                path[v[s-1][i]-1] = s ;
            }
        }

    }

    vector <int>pathVector = {};
    for(int k = d; k != 0; k = path[k-1]){
        pathVector.push_back(k);
        // std::cout << k << std::endl;

    }


    if(pathVector.size() == 1){
        std::cerr<< "ERROR: No Path" << endl;
    }
    else{
        cout << pathVector[pathVector.size()-1];
        for(int i = pathVector.size()-2; i >=0; i--){
            cout << "-" << pathVector[i];
        }
        cout<<endl;
        cout<< flush;
    }


}

vector<vector<int>> process_input(string line, int vertices){


    vector<int> v = {};
    vector<vector<int>> edges = {};
    int line_length = line.length();
    for(int i = 0; i < line_length; i++){
        if(line[i] >= '0' && line[i] <= '9'){
            string st = "";
            while(line[i] >= '0' && line[i] <= '9'){
                st = st + line[i];
                i++;
            }
            // std::cout<<st<<std::endl;
            int vr = stoi(st);
            if(vr>vertices || vr==0){
                return edges;
            }
            v.push_back(stoi(st));
        }
    }


    int v_size = v.size();
    for(int i = 0 ; i < v_size; i+=2){
        if(v[i] != v[i+1]){
            edges.push_back({v[i],v[i+1]});
        }
        else{
            edges.clear();
            return edges;
        }

    }

    return edges;
}

int num_of_vertices(string line){

    int num = 0;
    string st = "";
    int line_length = line.length();
    for(int i = 0; i < line_length; i++){
        while(line[i] >= '0' && line[i] <= '9'){
            st = st + line[i];
            i++;
        }
    }

    num = stoi(st);
    if(num<=1){
        return 0;
    }
    return num;
}

vector<int> get_Source_and_Destination(string line, int vertices){
    vector<int> sandd = {};
    int line_length = line.length();

    for(int i = 0; i < line_length; i++){
        if(line[i] >= '0' && line[i] <= '9'){
            string st = "";
            while(line[i] >= '0' && line[i] <= '9'){
                st = st + line[i];
                i++;
            }

            int vr = stoi(st);
            if(vr>vertices || vr==0){
                sandd.clear();
                return sandd;
            }
            sandd.push_back(stoi(st));
        }
    }

    return sandd;
}

int main(int argc, char** argv)
{

    int vertices =0 ;
    vector<vector<int>> edges ={};
    vector <string> ipstring ;




    while (!cin.eof()) {

        string line;
        getline(cin, line);

        if(line[0] == 'V'){
            cout<<line<<endl;
            cout<< flush;
            vertices = num_of_vertices(line);
            if (vertices == 0) {
                std::cerr<<"ERROR: vertices error" << endl;
                cout<< flush;
            }


        }

        if(line[0] == 'E'){
            cout<<line<<endl;
            cout<< flush;
            edges = process_input(line, vertices);
            if(edges.empty()){
                std::cerr<<"ERROR: edges error"<<endl;
                cout<< flush;
            }

        }

        if(line[0] == 's'){

            vector<int> sandd ={};
            sandd = get_Source_and_Destination(line, vertices);
            if(sandd.empty()){
                std::cerr<<"ERROR: source and destination error"<<endl;
                cout<< flush;
            }else{
                shortest_path(make_graph(edges, vertices), sandd[0], sandd[1], vertices);

            }

        }

    }

    return 0;
}


