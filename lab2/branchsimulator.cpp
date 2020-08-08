#include <iostream>
#include <fstream>
#include <math.h>
#include <vector>

using namespace std;

int main (int argc, char** argv) {
	ifstream config;
	//config.open(argv[1]);
    config.open(argv[1]);
	int m, k;
	config >> m >> k;
 
	config.close();

	ofstream out;
	//string out_file_name = string(argv[2]) + ".out";
    string out_file_name = string(argv[2]) + ".out";
	out.open(out_file_name.c_str());
    
    vector<vector<int> > predictor;
    predictor.resize(pow(2,m));
    int index;
    int tag = 0;
    int temp;
    int BHR[9];
    ifstream trace;
    //trace.open(argv[2]);
    trace.open(argv[2]);
	
    for(int s=0; s<k; s++){
           BHR[s]=1;
       }
     predictor.resize(pow(2,m));
    for(int i = 0;i<pow(2,m); i++)
    {
        predictor[i].resize(pow(2,k));
    }
       for(int i = 0; i < pow(2,m);i++)
       {
           for(int j = 0; j < pow(2,k);j++)
           {
               predictor[i][j] = 3 ;
           }
       }
    
	while (!trace.eof()) {
		unsigned long pc; bool taken;
        trace >> std::hex >> pc >> taken;
        bool prediction;
        
        index = pc&((1<<m)-1);
        tag=0;
        for(int i = 0; i < k; i++){
            tag = BHR[i] * pow(2,i)+ tag;
        }
        
        
        temp = predictor[index][tag];
        // predictor update
        if(temp == 3){
            if(taken == 0){
                predictor[index][tag] = 2;
            }else{
                predictor[index][tag] = 3;
            }
            prediction = 1;
        }
        else if(temp == 2){
            if(taken == 0){
                predictor[index][tag] = 0;
            }else{
                predictor[index][tag] = 3;
            }
            prediction = 1;
        }
        else if(temp == 1){
            if(taken == 0){
                predictor[index][tag] = 0;
            }else{
                predictor[index][tag] = 3;
            }
            prediction = 0;
        }
        else if(temp == 0){
            if(taken == 0){
                predictor[index][tag] = 0;
            }else{
                predictor[index][tag] = 1;
            }
            prediction = 0;
        }
        //BHR update
        if (taken == 1) {
            for(int i=k;i>0;i--)
            {
                BHR[i]=BHR[i-1];
            }
            BHR[0] = 1;
        }else if(taken == 0){
            for(int i=k;i>0;i--)
            {
                BHR[i]=BHR[i-1];
            }
            BHR[0] = 0;
    }
        out << prediction<<endl;
	}
	trace.close();	
	out.close();
}
