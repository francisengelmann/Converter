#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

typedef struct _Triange {
    float normal[3];
    float vertex1[3];
    float vertex2[3];
    float vectex3[3];
    short s=0;
} Triangle;

int readSTL(string fileName){
    cout << "Reading stl..." << endl;

    vector<Triangle> mesh;

    return 0;
}

int writeDAE(string fileName){
    cout << "Exporting dae..." << endl;
    ofstream file;
    file.open(fileName.c_str());

    file << "<COLLADA>" << endl;
    file << "   <library_geometries>" << endl;
    file << "      <geometry>" << endl;
    file << "         <mesh>" << endl;
    file << "         </mesh>" << endl;
    file << "      </geometry>" << endl;
    file << "   </library_geometries>" << endl;
    file << "</COLLADA>" << endl;

    file.close();
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
