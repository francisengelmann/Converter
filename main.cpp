#include <iostream>

using namespace std;

int readSTL(string fileName){
    cout << "Reading stl..." << endl;
    return 0;
}

int writeDAE(string fileName){
    cout << "Exporting dae..." << endl;
    return 0;
}

void printUsage(){
    cout << "Usage: input.stl [output.dae]" << endl;
}

int main(int argc, char* args[])
{
    switch(argc){
        case 3: //normal behavior
            readSTL(args[0]);
            writeDAE(args[1]);
            break;
        case 2: //normal behavior
            readSTL(args[0]);
            writeDAE("output.dae");
        break;
        case 1:
            cout << "No input file specified!" << endl;
            printUsage();
            return 1;
            break;
        default:
          printUsage();
          return 1;
          break;
    }

    if(argc!=2){
        if(argc==0){
        }
    }

    return 0;
}
