#include <iostream>
#include<cstdlib>

using namespace std;

int main(int argc,char *argv[]){
    double sum;
    if(argc <= 1){
        cout << "Please input numbers to find average.\n";
    }else{
        for(int i = 0; i < argc; i++){
            double a = atoi(argv[i]);
            sum += a;
        }
        cout << "---------------------------------\n";
        cout << "Average of " << argc-1 << " numbers = " << sum/(argc-1.000) << endl;
        cout << "---------------------------------\n";
    }
}