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
    file.open(fileName.c_str(),ios::trunc|ios::out);

/*    file << "<COLLADA>" << endl;
    file << "<library_geometries>" << endl;

    //one geometry per object in the scene
    file << "<geometry>" << endl;
    file << "<mesh>" << endl;

//---------------------------------------------------------------------------
//contains vertex coordinates
//---------------------------------------------------------------------------
    file << "<source id='mesh-vertices'>" << endl;
    file << "<float_array id='mesh-vertices-array' count='"<< numberOfTriangles*3*3 <<"'>" << endl;
    for(unsigned int i=0; i<numberOfTriangles; i++){
   //     file << mesh[i].vertex0[0] << " " << mesh[i].vertex0[1] << " " << mesh[i].vertex0[2] << endl;
   //     file << mesh[i].vertex1[0] << " " << mesh[i].vertex1[1] << " " << mesh[i].vertex1[2] << endl;
     //   file << mesh[i].vertex2[0] << " " << mesh[i].vertex2[1] << " " << mesh[i].vertex2[2] << endl;
    }
    file << "</float_array>" << endl;
    file << "<technique_common>";
    file << "<accessor source='#mesh-vertices-array' count='"<< numberOfTriangles*3 <<"' stride='3'>" << endl;
    file << "<param name='X' type='float'/>" << endl;
    file << "<param name='Y' type='float'/>" << endl;
    file << "<param name='Z' type='float'/>" << endl;
    file << "</accessor>" << endl;
    file << "</technique_common>";
    file << "</source>" << endl;

//---------------------------------------------------------------------------
//contains vertex normals
//---------------------------------------------------------------------------
    file << "<source id='mesh-normals'>" << endl;
    file << "<float_array id='mesh-normals-array' count='"<< numberOfTriangles*3 <<"'>" << endl;
    for(unsigned int i=0; i<numberOfTriangles; i++){
    //    file << mesh[i].normal[0] << ' ' << mesh[i].normal[1] << ' ' << mesh[i].normal[2] << endl;
    }
    file << "</float_array>" << endl;
    file << "<technique_common>";
    file << "<accessor source='#mesh-normals-array' count='"<< numberOfTriangles*3 <<"' stride='3'>" << endl;
    file << "<param name='X' type='float'/>" << endl;
    file << "<param name='Y' type='float'/>" << endl;
    file << "<param name='Z' type='float'/>" << endl;
    file << "</accessor>" << endl;
    file << "</technique_common>";
    file << "</source>" << endl;
 //---------------------------------------------------------------------------
 // vertices
 //---------------------------------------------------------------------------
    file << "<vertices id='vertices'>" << endl;
    file << "<input semantic='POSITION' id='mesh-vertices'>" << endl;
    file << "</vertices>" << endl;

//---------------------------------------------------------------------------
//contains vertex normals
//---------------------------------------------------------------------------
    file << "<triangles count='"<< numberOfTriangles <<"'>" << endl;
    file << "<input offset='0' semantic='VERTEX' source='#ID7'>" << endl;
    file << "<input offset='1' semantic='NORMAL' source='#ID6'>" << endl;
    file << "<p>" << endl;

    for(unsigned int i=0; i<numberOfTriangles*3; i+=3){
       // file << i << " " << (int)(i/(int)3) << " ";
    }

    file << "</p>" << endl;
    file << "</triangles>" << endl;
//---------------------------------------------------------------------------
    file << "</mesh>" << endl;
    file << "</geometry>" << endl;
    file << "</library_geometries>" << endl;
    file << "</COLLADA>" << endl;

    file.close();

    cout << "Triangels in mesh: "<<mesh.size() << endl;
    for(unsigned int i=0; i<numberOfTriangles; i++){
        //cout << mesh[i].normal[0] <<" "<< mesh[i].normal[1]  <<" "<<mesh[i].normal[2] <<endl;
        //cout << mesh[i].vertex0[0] <<" "<< mesh[i].vertex0[1]  <<" "<<mesh[i].vertex0[2] <<endl;
        //cout << mesh[i].vertex1[0] <<" "<< mesh[i].vertex1[1]  <<" "<<mesh[i].vertex1[2] <<endl;
        //cout << mesh[i].vertex2[0] <<" "<< mesh[i].vertex2[1]  <<" "<<mesh[i].vertex2[2] <<endl;
    }*/

    file <<"<?xml version='1.0' encoding='utf-8'?>" << endl;
    file <<"<COLLADA xmlns='http://www.collada.org/2005/11/COLLADASchema' version='1.4.1'>" << endl;
    file <<"    <asset>" << endl;
    file <<"        <created>2012-02-07T03:30:22Z</created>" << endl;
    file <<"        <modified>2012-02-07T03:30:22Z</modified>" << endl;
    file <<"    </asset>" << endl;
    file <<"    <library_geometries>" << endl;
    file <<"        <geometry id='Cube'>" << endl;
    file <<"            <mesh>" << endl;
    file <<"                <source id='mesh-positions'>" << endl;
    //file <<"                    <float_array id='mesh-positions-array' count='"<< 12 <<"'>" << endl;
    file <<"                    <float_array id='mesh-positions-array' count='"<< numberOfTriangles*3*3 <<"'>" << endl;

    for(unsigned int i=0; i<numberOfTriangles; i++){
        //file << mesh[i].normal[0] <<" "<< mesh[i].normal[1]  <<" "<<mesh[i].normal[2] <<endl;
        file << mesh[i].vertex0[0] <<" "<< mesh[i].vertex0[1]  <<" "<<mesh[i].vertex0[2] <<endl;
        file << mesh[i].vertex1[0] <<" "<< mesh[i].vertex1[1]  <<" "<<mesh[i].vertex1[2] <<endl;
        file << mesh[i].vertex2[0] <<" "<< mesh[i].vertex2[1]  <<" "<<mesh[i].vertex2[2] <<endl;
    }

    //file <<"-49.9658 -50.1369 50.0342 -49.9658 49.8631 50.0342 50 -50 50 50.0342 49.8631 50.0342" << endl;

    file <<"                    </float_array>" << endl;
    file <<"                    <technique_common>" << endl;
    file <<"                        <accessor count='4' source='#mesh-positions-array' stride='3'>" << endl;
    file <<"                            <param name='X' type='float'/>" << endl;
    file <<"                            <param name='Y' type='float'/>" << endl;
    file <<"                            <param name='Z' type='float'/>" << endl;
    file <<"                        </accessor>" << endl;
    file <<"                    </technique_common>" << endl;
    file <<"                </source>" << endl;
    file <<"                <source id='mesh-normals'>" << endl;
   // file <<"                    <float_array id='mesh-normals-array' count='9'>" << endl;
    file <<"                    <float_array id='mesh-normals-array' count='" <<numberOfTriangles*3 << "'>" << endl;

    for(unsigned int i=0; i<numberOfTriangles; i++){
        file << mesh[i].normal[0] <<" "<< mesh[i].normal[1]  <<" "<<mesh[i].normal[2] <<endl;
    }


    //file <<"0.000171171 -0.000171171 1 0 0 1 0.000342342 -0.000342342 1" << endl;

    file <<"                    </float_array>" << endl;
    file <<"                    <technique_common>" << endl;
    file <<"                        <accessor count='3' source='#mesh-normals-array' stride='3'>" << endl;
    file <<"                            <param name='X' type='float'/>" << endl;
    file <<"                            <param name='Y' type='float'/>" << endl;
    file <<"                            <param name='Z' type='float'/>" << endl;
    file <<"                        </accessor>" << endl;
    file <<"                    </technique_common>" << endl;
    file <<"                </source>" << endl;
    file <<"                <vertices id='mesh-vertices'>" << endl;
    file <<"                    <input semantic='POSITION' source='#mesh-positions'/>" << endl;
    file <<"                </vertices>" << endl;
    //file <<"                <triangles count='2'>" << endl;
    file <<"                <triangles count='"<< numberOfTriangles << "'>" << endl;
    file <<"                    <input offset='0' semantic='VERTEX' source='#mesh-vertices'/>" << endl;
    file <<"                    <input offset='1' semantic='NORMAL' source='#mesh-normals'/>" << endl;
    file <<"                    <p>" << endl;

    for(unsigned int i=0; i<numberOfTriangles*3; i+=3){
        file << i+0 << " " << (int)(i/3) << " " << i+1 << " " << (int)(i/3) << " " << i+2 << " " << (int)(i/3) << endl;
    }

    //file <<"                    3 0  1 1  0 0" << endl;
    //file <<"                    2 2  3 0  0 0" << endl;

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
    file <<"</COLLADA>";


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
        case 2: //normal behavior with default output file name
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
    return 0;
}
