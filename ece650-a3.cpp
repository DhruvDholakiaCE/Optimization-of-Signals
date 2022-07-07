#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include<string>
#include<stdlib.h>
#include<vector>
#include<fstream>
using namespace std;

int main(int argc, char* argv[])
{
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
                if(s_k < min_s){std::cerr <<  "ERROR: s"; cout<< flush; return 0; }

            }
            if(allArgs[i] == "-n"){
//                if(!isNumber(allArgs[i+1])){std::cerr << "Error: stoi"; exit(0);}
                n_k = stoi(allArgs[i+1]);
                if(n_k < min_n){std::cerr <<  "ERROR: n"; cout<< flush; return 0; }
            }

            if(allArgs[i] == "-c"){
//                if(!isNumber(allArgs[i+1])){std::cerr << "Error: stoi"; exit(0);}
                c_k = stoi(allArgs[i+1]);
                if(c_k < min_c){std::cerr <<  "ERROR: c"; cout<< flush; return 0; }
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

    std::vector<pid_t> kids = {};


     int fd1[2];
     int fd2[2];
     int l = 5;


     //urandom for l
     std::ifstream urandom("/dev/urandom");

    urandom.close();


    if(pipe(fd1) == -1){return 0;}
    if(pipe(fd2) == -1){return 1;}

    string temp = argv[0];
     int p1;
     if((p1 = fork()) == -1){
         return 1;
     }

     if(p1 == 0) {

         dup2(fd1[1], STDOUT_FILENO);
         close(fd1[1]);
         close(fd1[0]);
         cout<< "wnv";
//         char *args[] = {"./rgen1", NULL};
         execv("./rgen", argv);


     }
     kids.push_back(p1);

     int p2;
     if((p2 = fork()) == -1){
         return 1;
     }
     if(p2 == 0) {

         dup2(fd1[0], STDIN_FILENO);
         close(fd1[1]);
         close(fd1[0]);

         dup2(fd2[1], STDOUT_FILENO);
         close(fd2[1]);
         close(fd2[0]);
//         char *args[] = {"python3", "./ece650-a1.py", nullptr};
         execlp("python3", "python3", "./ece650-a1.py", NULL);

     }
     kids.push_back(p2);
     close(fd1[1]);
     close(fd1[0]);

     int p3;
     if((p3 = fork()) == -1){
         return 1;
     }
     if(p3 == 0) {
         dup2(fd2[1], STDOUT_FILENO);
         close(fd2[1]);
         close(fd2[0]);
         struct timeval tmo;
         fd_set readfds;

        string sandc = "";

        while(!cin.eof()){
        getline(cin,sandc);
        if(sandc == ""){
                int status;
                kill(getppid(), SIGTERM);
                waitpid(getppid(), &status, 0);
                break;}
        cout<< sandc << endl;
        }

     }
     kids.push_back(p3);
//     if(ip == ""){break;}
     int p4;
     if((p4 = fork()) == -1){
         return 1;
     }
     if(p4 == 0) {

         dup2(fd2[0], STDIN_FILENO);
         close(fd2[1]);
         close(fd2[0]);

         execv("./ece650-a2", argv);

     }

    kids.push_back(p4);

    close(fd2[1]);
    close(fd2[0]);
//
     waitpid(p1,NULL,0);
     waitpid(p2,NULL,0);
     waitpid(p3,NULL,0);
     waitpid(p4,NULL,0);
     for (pid_t k : kids) {
        int status;
        kill(k, SIGTERM);
        waitpid(k, &status, 0);
      }

//    }


 return 0;

}

