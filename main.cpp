#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

typedef struct _Triange {
    float normal[3];
    float vertex0[3];
    float vertex1[3];
    float vertex2[3];
    unsigned short s;
} Triangle;

vector<Triangle> mesh;
unsigned int numberOfTriangles;

int readSTL(char* fileName){
    cout << "Reading stl..." << endl;
    ifstream file (fileName, ios::in|ios::binary|ios::ate);

    if (file.is_open()){
        //file.seekg(0,file.end);
        //int length = file.tellg();
        //file.seekg(0,file.beg);

        //jump over the first 80chars, they only contain the name and blabla
        file.seekg(80);
        //read total number of triangles
        file.read((char *)&numberOfTriangles, sizeof(unsigned int));

        for(unsigned int i=0; i<numberOfTriangles; i++){
            Triangle t;
            file.read((char *)&t.normal[0], sizeof(float));
            file.read((char *)&t.normal[1], sizeof(float));
            file.read((char *)&t.normal[2], sizeof(float));
            file.read((char *)&t.vertex0[0], sizeof(float));
            file.read((char *)&t.vertex0[1], sizeof(float));
            file.read((char *)&t.vertex0[2], sizeof(float));
            file.read((char *)&t.vertex1[0], sizeof(float));
            file.read((char *)&t.vertex1[1], sizeof(float));
            file.read((char *)&t.vertex1[2], sizeof(float));
            file.read((char *)&t.vertex2[0], sizeof(float));
            file.read((char *)&t.vertex2[1], sizeof(float));
            file.read((char *)&t.vertex2[2], sizeof(float));
            file.read((char *)&t.s, sizeof(unsigned short));
            mesh.push_back(t);
        }

        cout << endl;
    }else{
        cout << "Error: could not open file " << fileName << endl;
        file.close();
        return 0;
    }

    file.close();
    return 1;
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

    cout << "Triangels in mesh: "<<mesh.size() << endl;
    for(unsigned int i=0; i<numberOfTriangles; i++){
        cout << mesh[i].normal[0] <<" "<< mesh[i].normal[1]  <<" "<<mesh[i].normal[2] <<endl;
        cout << mesh[i].vertex0[0] <<" "<< mesh[i].vertex0[1]  <<" "<<mesh[i].vertex0[2] <<endl;
        cout << mesh[i].vertex1[0] <<" "<< mesh[i].vertex1[1]  <<" "<<mesh[i].vertex1[2] <<endl;
        cout << mesh[i].vertex2[0] <<" "<< mesh[i].vertex2[1]  <<" "<<mesh[i].vertex2[2] <<endl;
    }
    return 1;
}

void printUsage(){
    cout << "Usage: input.stl [output.dae]" << endl;
}

int main(int argc, char* args[])
{
    switch(argc){
        case 3: //normal behavior
            if(!readSTL(args[1])) return 1;
            if(!writeDAE(args[2])) return 1;
            break;
        case 2: //normal behavior
            if(!readSTL(args[1])) return 1;
            if(!writeDAE("output.dae")) return 1;
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
