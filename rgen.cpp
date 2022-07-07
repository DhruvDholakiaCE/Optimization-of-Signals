#include<iostream>
#include<stdio.h>
#include<fstream>
#include<vector>
#include <sys/wait.h>
#include<math.h>
#include<stdlib.h>
#include<unistd.h>
using namespace std;
float slope(float x1, float y1, float x2, float y2)
{

    return (y2 - y1) / (x2 - x1);
}



int generateNum(std::ifstream &urandom,int k, int min_arg = 0){
    unsigned int num = 42;
    urandom.read((char *)&num, sizeof(int));
    int rnum = (num%(k - min_arg + 1)) + min_arg;
    return rnum;

}



int main(int argc, char** argv){

    while(true){
    bool  flagex = true;
    std::ifstream urandom("/dev/urandom");
  // check that it did not fail
  if (urandom.fail()) {

    std::cerr << "Error: cannot open /dev/urandom\n";
    cout<< flush;
//    return 1;
  }
    int s_k = 10;
    int n_k = 5;
    int l_k = 5;
    int c_k = 20;
    int min_s = 2;
    int min_n = 1;
    int min_c = 1;
    int min_l = 5;

    std::vector<std::string> allArgs(argv, argv + argc);

    if(!allArgs.empty()){
        for(int i = 1 ; i < allArgs.size(); i+=2 ){
            try{
            if(allArgs[i] == "-s"){
//                if(!isNumber(allArgs[i+1])){std::cerr << "Error: stoi"; exit(0);}

                s_k= stoi(allArgs[i+1]);
                if(s_k < min_s){std::cerr <<  "ERROR: s"; cout<< flush; return 0;}

            }
            if(allArgs[i] == "-n"){
//                if(!isNumber(allArgs[i+1])){std::cerr << "Error: stoi"; exit(0);}
                n_k = stoi(allArgs[i+1]);
                if(n_k < min_n){std::cerr <<  "ERROR: n"; cout<< flush; return 0; }
            }

            if(allArgs[i] == "-c"){
//                if(!isNumber(allArgs[i+1])){std::cerr << "Error: stoi"; exit(0);}
                c_k = stoi(allArgs[i+1]);
                if(c_k < min_c){std::cerr <<  "ERROR: c"; cout<< flush;return 0; }
            }
            if(allArgs[i] == "-l"){
//                if(!isNumber(allArgs[i+1])){std::cerr << "Error: stoi"; exit(0);}
                l_k = stoi(allArgs[i+1]);

                if(l_k < min_l){std::cerr <<  "ERROR: l"; cout<< flush; return 0; }
            }
        }catch(exception e){
            std::cerr << "ERROR : ";
            cout<< endl;
            return 0;
        }

    }
    }

   int range[2] = {-1*c_k, 0};



  int nos, non, nol;
  nos = generateNum(urandom,s_k,min_s);


  //cout << "no of streets : " <<  nos << " no of line_segs : " << non << " waitNol : " << nol << endl;
  vector<vector<vector<int>>> line_segs = {};
  int count = 0;

  while(line_segs.size() < nos && count < 25){
    vector<vector<int>> line_coords;
    bool flag2 = false;
    non = generateNum(urandom,n_k,min_n);
    while(line_coords.size() != non +1 && count < 25){
        bool flag1 = false;

        int coor1 = generateNum(urandom,c_k) + range[generateNum(urandom,1)];
        int coor2 = generateNum(urandom,c_k) + range[generateNum(urandom,1)];
        vector<int> coords = {};
        coords.push_back(coor1);
        coords.push_back(coor2);
        for(int pp = 0 ; pp < line_coords.size(); pp++){
            if(line_coords[pp] == coords){
                flag1 = true;
                break;
            }
        }

        if(line_coords.size() > 0){
            for(int z = 0;  z < line_coords.size()-1; z++){
                int a = coor1;
                int b = coor2;
                float slope1 = (float(line_coords[z][1]) - float(line_coords[z+1][1]))/(float(line_coords[z][0]) - float(line_coords[z+1][0]));
                float slope2 =  (float(line_coords[line_coords.size()-1][1]) - float(b))/(float(line_coords[line_coords.size()-1][0]) - float(a));
                if(slope1 == slope2 || std::isinf(slope1) && std::isinf(slope2)){

                    float AB = sqrt((line_coords[z][0] - line_coords[z+1][0])*(line_coords[z][0] - line_coords[z+1][0]) +
                                    (line_coords[z][1] - line_coords[z+1][1])*(line_coords[z][1] - line_coords[z+1][1]));
                    float AP = sqrt((line_coords[z][0] - a)*(line_coords[z][0] - a) +
                                    (line_coords[z][1] - b)*(line_coords[z][1] - b));
                    float PB = sqrt((line_coords[z+1][0] - a)*(line_coords[z+1][0] - a) +
                                    (line_coords[z+1][1] - b)*(line_coords[z+1][1] - b));
                    if(AB == AP + PB){
                        flag1 = true;
                        break;
                    }

                    AB = sqrt((line_coords[z][0] - line_coords[z+1][0])*(line_coords[z][0] - line_coords[z+1][0]) +
                              (line_coords[z][1] - line_coords[z+1][1])*(line_coords[z][1] - line_coords[z+1][1]));
                    AP = sqrt((line_coords[z][0] - line_coords[line_coords.size()-1][0])*(line_coords[z][0] - line_coords[line_coords.size()-1][0]) +
                              (line_coords[z][1] - line_coords[line_coords.size()-1][1])*(line_coords[z][1] - line_coords[line_coords.size()-1][1]));
                    PB = sqrt((line_coords[z+1][0] - line_coords[line_coords.size()-1][0])*(line_coords[z+1][0] - line_coords[line_coords.size()-1][0]) +
                              (line_coords[z+1][1] - line_coords[line_coords.size()-1][1])*(line_coords[z+1][1] - line_coords[line_coords.size()-1][1]));
                    if(AB == AP + PB){
                        flag1 = true;
                        break;

                    }

                    AB = sqrt((line_coords[line_coords.size()-1][0]-a)*(line_coords[line_coords.size()-1][0]-a) +
                              (line_coords[line_coords.size()-1][1]-b)*(line_coords[line_coords.size()-1][1]-b));
                    AP = sqrt((line_coords[z][0] - a)*(line_coords[z][0] - a) +
                              (line_coords[z][1] - b)*(line_coords[z][1] - b));
                    PB = sqrt((line_coords[z][0] - line_coords[line_coords.size()-1][0])*(line_coords[z][0] - line_coords[line_coords.size()-1][0]) +
                              (line_coords[z][1] - line_coords[line_coords.size()-1][1])*(line_coords[z][1] - line_coords[line_coords.size()-1][1]));
                    if(AB == AP + PB){
                        flag1 = true;
                        break;
                    }
                    AB = sqrt((line_coords[line_coords.size()-1][0]-a)*(line_coords[line_coords.size()-1][0]-a) +
                              (line_coords[line_coords.size()-1][1]-b)*(line_coords[line_coords.size()-1][1]-b));
                    AP = sqrt((line_coords[z+1][0] - a)*(line_coords[z+1][0] - a) +
                              (line_coords[z+1][1] - b)*(line_coords[z+1][1] - b));
                    PB = sqrt((line_coords[z+1][0] - line_coords[line_coords.size()-1][0])*(line_coords[z+1][0] - line_coords[line_coords.size()-1][0]) +
                              (line_coords[z+1][1] - line_coords[line_coords.size()-1][1])*(line_coords[z+1][1] - line_coords[line_coords.size()-1][1]));
                    if(AB == AP + PB){
                        flag1 = true;
                        break;
                    }
                }



            }
        }

        if(!flag1){
            line_coords.push_back(coords);
        }else{count++;}
    }

    if(count == 25){break;}

    for(int  k = 0 ; k < line_segs.size(); k++){
        bool out = false;
        for(int l = 0; l < line_segs[k].size()-1; l++){
            bool in = false;
            for(int m = 0; m < line_coords.size()-1; m ++ ){

                  float slope1 = (float(line_segs[k][l][1]) - float(line_segs[k][l+1][1]))/(float(line_segs[k][l][0]) - float(line_segs[k][l+1][0]));
                  int a = line_coords[m+1][0];
                  int b = line_coords[m+1][1];
                    float slope2 =  (float(line_coords[m][1]) - float(b))/(float(line_coords[m][0]) - float(a));

                    if(slope1 == slope2 || std::isinf(slope1) && std::isinf(slope2)){
                        float AB = sqrt((line_segs[k][l][1] - line_segs[k][l+1][1])*(line_segs[k][l][1] - line_segs[k][l+1][1]) +
                                        (line_segs[k][l][0] - line_segs[k][l+1][0])*(line_segs[k][l][0] - line_segs[k][l+1][0]));
                        float AP = sqrt((line_segs[k][l][0] - a)*(line_segs[k][l][0] - a) +
                                        (line_segs[k][l][1] - b)*(line_segs[k][l][1] - b));
                        float PB = sqrt((line_segs[k][l+1][0] - a)*(line_segs[k][l+1][0] - a) +
                                        (line_segs[k][l+1][1] - b)*(line_segs[k][l+1][1] - b));

                        if(AB == AP + PB){
                            in = true;
                            break;
                        }

                        AB = sqrt((line_segs[k][l][1] - line_segs[k][l+1][1])*(line_segs[k][l][1] - line_segs[k][l+1][1]) +
                                  (line_segs[k][l][0] - line_segs[k][l+1][0])*(line_segs[k][l][0] - line_segs[k][l+1][0]));
                        AP = sqrt((line_segs[k][l][0] - line_coords[m][0])*(line_segs[k][l][0] - line_coords[m][0]) +
                                  (line_segs[k][l][1] - line_coords[m][1])*(line_segs[k][l][1] - line_coords[m][1]));
                        PB = sqrt((line_segs[k][l+1][0] - line_coords[m][0])*(line_segs[k][l+1][0] - line_coords[m][0]) +
                                  (line_segs[k][l+1][1] - line_coords[m][1])*(line_segs[k][l+1][1] - line_coords[m][1]));
                        if(AB == AP + PB){
                            in = true;
                            break;

                        }

                        AB = sqrt((line_coords[m][0]-a)*(line_coords[m][0]-a) +
                                  (line_coords[m][1]-b)*(line_coords[m][1]-b));
                        AP = sqrt((line_segs[k][l][0] - a)*(line_segs[k][l][0] - a) +
                                  (line_segs[k][l][1] - b)*(line_segs[k][l][1] - b));
                        PB = sqrt((line_segs[k][l][0] - line_coords[m][0])*(line_segs[k][l][0] - line_coords[m][0]) +
                                  (line_segs[k][l][1] - line_coords[m][1])*(line_segs[k][l][1] - line_coords[m][1]));

                        if(AB == AP + PB){
                            in = true;
                            break;
                        }
                        AB = sqrt((line_coords[m][0]-a)*(line_coords[m][0]-a) +
                                  (line_coords[m][1]-b)*(line_coords[m][1]-b));
                        AP = sqrt((line_segs[k][l+1][0] - a)*(line_segs[k][l+1][0] - a) +
                                  (line_segs[k][l+1][1] - b)*(line_segs[k][l+1][1] - b));
                        PB = sqrt((line_segs[k][l+1][0] - line_coords[m][0])*(line_segs[k][l+1][0] - line_coords[m][0]) +
                                  (line_segs[k][l+1][1] - line_coords[m][1])*(line_segs[k][l+1][1] - line_coords[m][1]));
                    }



            }
            if(in){out = true; break;}
           }
        if(out){flag2 = true; break;}
        }
        if(!(flag2)){
        line_segs.push_back(line_coords);
        }else{
            count++;
        }
    }
  if(line_segs.size() != nos){std::cerr << "ERROR: Not Possible in " << count << " tries" << endl;
    cout<< flush;
    flagex = false;
  }
  vector<string> streets_coords = {};

  vector<string> street_names = {};
  for(int i = 0 ; i < nos; i++){
    string s = "";
    char ck = char((i%26) +65);
    for(int k = 0; k < (int)(i/26) + 1; k++){
        s += string(1,ck);
    }
    street_names.push_back(s);
  }

  for(int k = 0; k < line_segs.size(); k ++){

      string street = "add \"" + street_names[k] + "\"";
      for(int j = 0 ; j < line_segs[k].size(); j++){
            street += " (" + to_string(line_segs[k][j][0]) +","+ to_string(line_segs[k][j][1]) +")";
        }
    street += "\n";
    streets_coords.push_back(street);

  }


  string final_street = "";
  for(int i = 0; i < streets_coords.size(); i++){
    final_street += streets_coords[i];
  }
  final_street += "gg";
  for(int i = 0; i < streets_coords.size(); i++){
    final_street += "\nrm \"" + street_names[i] +"\"";
  }
  if(flagex){
  cout << final_street <<endl; }

  int l = generateNum(urandom, l_k, min_l);
  sleep(l);
  urandom.close();

}
return 0;
}


















