#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

using namespace std;
using namespace boost;

typedef struct _Triange {
    float normal[3];
    float vertices[3][3];
    unsigned int normalId;
    unsigned int verticesId[3];
    unsigned short s;
} Triangle;

typedef struct _Vector3d {
    float v[3];
} Vector3d;

//for import
vector<Triangle> mesh;
//for export
vector<Vector3d> vertices;
vector<Vector3d> normals;

int insertToNormals(Vector3d n)
{
    for(int i=0; i<normals.size(); i++)
    {
        Vector3d normal = normals[i];
        if(normal.v[0] == n.v[0] && normal.v[1] == n.v[1] && normal.v[2] == n.v[2]){
            return i;
        }
    }
    normals.push_back(n);
    return normals.size()-1;
}

int insertToVertices(Vector3d v)
{
    for(int i=0; i<vertices.size(); i++)
    {
        Vector3d vertex = vertices[i];
        if(vertex.v[0] == v.v[0] && vertex.v[1] == v.v[1] && vertex.v[2] == v.v[2]){
            return i;
        }
    }
    vertices.push_back(v);
    return vertices.size()-1;
}

void fillVerticesAndNormals()
{
    //iterate over triangles in mesh
    for(int i=0;i<mesh.size();i++){
        Vector3d normal;
        for(int n=0; n<3;n++) { normal.v[n] = mesh[i].normal[n]; }
        mesh[i].normalId = insertToNormals(normal);
        //iterate over vertices in triangle
        for(int j=0;j<3;j++){
            Vector3d vertex;
            for(int n=0; n<3;n++) { vertex.v[n] = mesh[i].vertices[j][n]; }
            mesh[i].verticesId[j] = insertToVertices(vertex);
        }

    }
}

unsigned int numberOfTriangles;

int readSTLAscii(char* fileName){
    ifstream file;
    Triangle t;
    string line;
    unsigned int vertexCount;
    vector<string> strings;

    file.open(fileName);
    if (file.is_open()){
        while(getline(file,line)){
            trim(line);
            split(strings, line, is_any_of(" "));
            //handle new triangle and normal
            if(strings[0].compare("facet")==0){
                t.normal[0]=lexical_cast<float>(strings[2]);
                t.normal[1]=lexical_cast<float>(strings[3]);
                t.normal[2]=lexical_cast<float>(strings[4]);
                vertexCount=0;
                numberOfTriangles++;
            }
            //handle points of triangle
            if(strings[0].compare("vertex")==0){
                t.vertices[vertexCount][0]=lexical_cast<float>(strings[1]);
                t.vertices[vertexCount][1]=lexical_cast<float>(strings[2]);
                t.vertices[vertexCount][2]=lexical_cast<float>(strings[3]);
                vertexCount++;
            }
            //add new triangle to mesh
            if(strings[0].compare("endfacet")==0){
                mesh.push_back(t);
            }
        }
    }else{
        cout << "Error: could not open file " << fileName << endl;
        file.close();
        return 0;
    }

    file.close();
    return 1;
}

int readSTLBinary(char* fileName){
    ifstream file (fileName, ios::in|ios::binary|ios::ate);

    if (file.is_open()){
        //jump over the first 80chars, they only contain the name and blabla
        file.seekg(80);
        //read total number of triangles
        file.read((char *)&numberOfTriangles, sizeof(unsigned int));
        cout << "Number of triangles: " << numberOfTriangles << endl;
        for(unsigned int i=0; i<numberOfTriangles; i++){
            Triangle t;
            file.read((char *)&t.normal[0], sizeof(float));
            file.read((char *)&t.normal[1], sizeof(float));
            file.read((char *)&t.normal[2], sizeof(float));
            file.read((char *)&t.vertices[0][0], sizeof(float));
            file.read((char *)&t.vertices[0][1], sizeof(float));
            file.read((char *)&t.vertices[0][2], sizeof(float));
            file.read((char *)&t.vertices[1][0], sizeof(float));
            file.read((char *)&t.vertices[1][1], sizeof(float));
            file.read((char *)&t.vertices[1][2], sizeof(float));
            file.read((char *)&t.vertices[2][0], sizeof(float));
            file.read((char *)&t.vertices[2][1], sizeof(float));
            file.read((char *)&t.vertices[2][2], sizeof(float));
            file.read((char *)&t.s, sizeof(unsigned short));
            mesh.push_back(t);
        }
    }else{
        cout << "Error: could not open file " << fileName << endl;
        file.close();
        return 0;
    }

    file.close();
    return 1;
}

int readSTL(char * fileName){
    cout << "=== Converting " <<  fileName << " ===" << endl;
    ifstream file;
    file.open(fileName);
    if (file.is_open()){
        string line1, line2;
        vector<string> strings1, strings2;
        getline(file,line1);
        getline(file,line2);
        trim(line1);
        trim(line2);
        split(strings1, line1, is_any_of(" "));
        split(strings2, line2, is_any_of(" "));
        if(!strings1[0].compare("solid") && !strings2[0].compare("facet")){
            cout << "Interpreting as ascii STL file." << endl;
            readSTLAscii(fileName);
        }else{
            cout << "Interpreting as binary STL file." << endl;
            readSTLBinary(fileName);
        }
    }
    file.close();
    return 1;
}

int writeDAE(string fileName){
    cout << "Preparing data for .DAE export." << endl;
    fillVerticesAndNormals();
    cout << "Starting export..." << endl;
    if(numberOfTriangles==0)
    {
        cout << "ERROR: number of read triangles is zero. No data available to export." << endl;
        return 0;
    }
    ofstream file;
    file.open(fileName.c_str(),ios::trunc|ios::out);

    file <<"<?xml version='1.0' encoding='utf-8'?>" << endl;
    file <<"<COLLADA xmlns='http://www.collada.org/2005/11/COLLADASchema' version='1.4.1'>" << endl;
    file <<"    <asset>" << endl;
    file <<"        <contributor>" << endl;
    file <<"            <authoring_tool>Converter</authoring_tool>" << endl;
    file <<"        </contributor>" << endl;
    file <<"        <created>2012-02-07T03:30:22Z</created>" << endl;
    file <<"        <modified>2012-02-07T03:30:22Z</modified>" << endl;
    file <<"        <unit meter='0.01' name='centimeter'/>" << endl;
    file <<"        <up_axis>Y_UP</up_axis>" << endl;
    file <<"    </asset>" << endl;
    file <<"    <library_geometries>" << endl;
    file <<"        <geometry id='Cube'>" << endl;
    file <<"            <mesh>" << endl;
    file <<"                <source id='mesh-positions'>" << endl;
    file <<"                    <float_array id='mesh-positions-array' count='"<< vertices.size()*3 <<"'>" << endl;

    for(unsigned int i=0; i<vertices.size(); i++){
        file << vertices[i].v[0] << " " << vertices[i].v[1] << " " << vertices[i].v[2] << endl;
    }

    file <<"                    </float_array>" << endl;
    file <<"                    <technique_common>" << endl;
    file <<"                        <accessor count='" << vertices.size() <<"' source='#mesh-positions-array' stride='3'>" << endl;
    file <<"                            <param name='X' type='float'/>" << endl;
    file <<"                            <param name='Y' type='float'/>" << endl;
    file <<"                            <param name='Z' type='float'/>" << endl;
    file <<"                        </accessor>" << endl;
    file <<"                    </technique_common>" << endl;
    file <<"                </source>" << endl;
    file <<"                <source id='mesh-normals'>" << endl;
    file <<"                    <float_array id='mesh-normals-array' count='" <<normals.size()*3<< "'>" << endl;

    for(unsigned int i=0; i<normals.size(); i++){
        file << normals[i].v[0] << " " << normals[i].v[1] << " " << normals[i].v[2] << endl;
    }

    file <<"                    </float_array>" << endl;
    file <<"                    <technique_common>" << endl;
    file <<"                        <accessor count='"<< normals.size() <<"' source='#mesh-normals-array' stride='3'>" << endl;
    file <<"                            <param name='X' type='float'/>" << endl;
    file <<"                            <param name='Y' type='float'/>" << endl;
    file <<"                            <param name='Z' type='float'/>" << endl;
    file <<"                        </accessor>" << endl;
    file <<"                    </technique_common>" << endl;
    file <<"                </source>" << endl;
    file <<"                <vertices id='mesh-vertices'>" << endl;
    file <<"                    <input semantic='POSITION' source='#mesh-positions'/>" << endl;
    file <<"                </vertices>" << endl;
    file <<"                <triangles count='"<< numberOfTriangles << "'>" << endl;
    file <<"                    <input offset='0' semantic='VERTEX' source='#mesh-vertices'/>" << endl;
    file <<"                    <input offset='1' semantic='NORMAL' source='#mesh-normals'/>" << endl;
    file <<"                    <p>" << endl;

    for(unsigned int i=0; i<mesh.size(); i++){
        file << mesh[i].verticesId[0] << " " << mesh[i].normalId << " "
             << mesh[i].verticesId[1] << " " << mesh[i].normalId << " "
             << mesh[i].verticesId[2] << " " << mesh[i].normalId << " " << endl;
    }

    file <<"                    </p>" << endl;
    file <<"                </triangles>" << endl;
    file <<"            </mesh>" << endl;
    file <<"        </geometry>" << endl;
    file <<"    </library_geometries>" << endl;
    file <<"    <library_visual_scenes>" << endl;
    file <<"        <visual_scene id='mesh-scene'>" << endl;
    file <<"            <node name='Cube'>" << endl;
    file <<"                <instance_geometry url='#Cube'></instance_geometry>" << endl;
    file <<"            </node>" << endl;
    file <<"        </visual_scene>" << endl;
    file <<"    </library_visual_scenes>" << endl;
    file <<"    <scene>" << endl;
    file <<"        <instance_visual_scene url='#mesh-scene'/>" << endl;
    file <<"    </scene>" << endl;
    file <<"</COLLADA>" << endl;
    cout << "== DONE ==" << endl;
    return 1;
}

void printUsage(){
    cout << "Usage: input.stl [output.dae]" << endl;
}

int main(int argc, char* args[])
{
    numberOfTriangles = 0;
    switch(argc){
        case 3: //normal behavior
            if(!readSTL(args[1])) return 1;
            if(!writeDAE(args[2])) return 1;
            break;
        case 2: //normal behavior with default output file name
            if(!readSTL(args[1])) return 1;
            if(!writeDAE("output.dae")) return 1;
            break;
        case 1:
            cout << "ERROR: No input file specified!" << endl;
            printUsage();
            return 1;
            break;
        default:
            printUsage();
            return 1;
            break;
    }
    return 0;
}
