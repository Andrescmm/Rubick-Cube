#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#include "shader_m.h"
#include "transformations.h"

#include <vector>
#include <limits>

using namespace std;

//GLOBAL VARIABLES------------------------------------------------------------------------------------------------------------------------
//colors
vector<float> black = { 0.0f, 0.0f, 0.0f };
vector<float> white = { 1.0f, 1.0f, 1.0f };
vector<float> red = { 1.0f, 0.0f, 0.0f };
vector<float> green = { 0.0f, 1.0f, 0.0f };
vector<float> blue = { 0.0f, 0.0f, 1.0f };
vector<float> yellow = { 1.0f, 1.0f, 0.0f };
vector<float> orange = { 1.0f, 0.5f, 0.0f };

//STRUCTURE FOR EACH CUBE----------------------------------------------------------------------------------------------------------------
struct SLittleCube
{
    int id;
    glm::vec3 initialPosition;
    vector<float> vertices;
    vector<vector<float>> listOfColors;
    vector<char> camadas;
    vector<float> textureIndices;
    vector<float> animation2Parameters; //ac - alfa - b0
    glm::mat4 modelo;
    glm::vec3 centro_cubo;
    SLittleCube(int _id, glm::vec3 iP, vector<float> _vertices) {
        id = _id;
        initialPosition = iP;
        vertices = _vertices;
    };
    void Alejarse(glm::vec3 centro, float distancia);
};



class CCube
{
public:
    vector<SLittleCube> littleCubes;
    //methods
    void moveR(float angle);
    void moveL(float angle);
    void moveU(float angle);
    void moveD(float angle);
    void moveF(float angle);
    void moveB(float angle);
    void moveM(float angle);
    void moveE(float angle);
    void moveS(float angle);

    void createLittleCubes();
    void drawCube(unsigned int* VBO, unsigned int* VAO);
    void restartValues(int littleCubeIndex);
    void animation1(float distancia);
    void animation2(bool reverse, float b1, float angle);
   
    CCube();
    ~CCube();

private:
    float vertices[288] = {
        //position                colors              texture
        -0.5f, -0.5f, -0.5f,    1.0f, 0.0f, 0.0f,     0.0f, 0.0f,//r - B
         0.5f, -0.5f, -0.5f,    1.0f, 0.0f, 0.0f,     0.0f, 0.0f,
         0.5f,  0.5f, -0.5f,    1.0f, 0.0f, 0.0f,     0.0f, 0.0f,
         0.5f,  0.5f, -0.5f,    1.0f, 0.0f, 0.0f,     0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,    1.0f, 0.0f, 0.0f,     0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,    1.0f, 0.0f, 0.0f,     0.0f, 0.0f,
                                                      
        -0.5f, -0.5f,  0.5f,    1.0f, 1.0f, 0.0f,     0.0f, 0.0f,//am - F
         0.5f, -0.5f,  0.5f,    1.0f, 1.0f, 0.0f,     0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,    1.0f, 1.0f, 0.0f,     0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,    1.0f, 1.0f, 0.0f,     0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,    1.0f, 1.0f, 0.0f,     0.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,    1.0f, 1.0f, 0.0f,     0.0f, 0.0f,
                                                      
        -0.5f,  0.5f,  0.5f,    0.0f, 0.0f, 1.0f,     0.0f, 0.0f,//az - L
        -0.5f,  0.5f, -0.5f,    0.0f, 0.0f, 1.0f,     0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,    0.0f, 0.0f, 1.0f,     0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,    0.0f, 0.0f, 1.0f,     0.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,    0.0f, 0.0f, 1.0f,     0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,    0.0f, 0.0f, 1.0f,     0.0f, 0.0f,
                                                      
         0.5f,  0.5f,  0.5f,    0.0f, 1.0f, 0.0f,     0.0f, 0.0f,//verde - R
         0.5f,  0.5f, -0.5f,    0.0f, 1.0f, 0.0f,     0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,    0.0f, 1.0f, 0.0f,     0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,    0.0f, 1.0f, 0.0f,     0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,    0.0f, 1.0f, 0.0f,     0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,    0.0f, 1.0f, 0.0f,     0.0f, 0.0f,
                                                      
        -0.5f, -0.5f, -0.5f,    1.0f, 1.0f, 1.0f,     0.0f, 0.0f,//blanco - D
         0.5f, -0.5f, -0.5f,    1.0f, 1.0f, 1.0f,     0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,    1.0f, 1.0f, 1.0f,     0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,    1.0f, 1.0f, 1.0f,     0.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,    1.0f, 1.0f, 1.0f,     0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,    1.0f, 1.0f, 1.0f,     0.0f, 0.0f,
                                                      
        -0.5f,  0.5f, -0.5f,    0.0f, 0.0f, 0.0f,     0.0f, 0.0f,//negro - U
         0.5f,  0.5f, -0.5f,    0.0f, 0.0f, 0.0f,     0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,    0.0f, 0.0f, 0.0f,     0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,    0.0f, 0.0f, 0.0f,     0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,    0.0f, 0.0f, 0.0f,     0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,    0.0f, 0.0f, 0.0f,     0.0f, 0.0f
    };
    glm::vec3 iPlittleCubes[26] = {
        glm::vec3(-1.2f, 1.2f, 1.2f),   //0
        glm::vec3(0.0f, 1.2f, 1.2f),   //1
        glm::vec3(1.2f, 1.2f, 1.2f),   //2

        glm::vec3(-1.2f, 0.0f, 1.2f),  //3
        glm::vec3(0.0f, 0.0f, 1.2f),  //4
        glm::vec3(1.2f, 0.0f, 1.2f),  //5

        glm::vec3(-1.2f, -1.2f, 1.2f),  //6
        glm::vec3(0.0f, -1.2f, 1.2f),  //7
        glm::vec3(1.2f, -1.2f, 1.2f),  //8

        glm::vec3(-1.2f, 1.2f, 0.0f),  //9
        glm::vec3(0.0f, 1.2f, 0.0f),  //10
        glm::vec3(1.2f, 1.2f, 0.0f),  //11

        glm::vec3(-1.2f, 0.0f, 0.0f), //12
        glm::vec3(1.2f, 0.0f, 0.0f), //13

        glm::vec3(-1.2f, -1.2f, 0.0f), //14
        glm::vec3(0.0f, -1.2f, 0.0f), //15
        glm::vec3(1.2f, -1.2f, 0.0f), //16

        glm::vec3(-1.2f, 1.2f, -1.2f),  //17
        glm::vec3(0.0f, 1.2f, -1.2f),  //18
        glm::vec3(1.2f, 1.2f, -1.2f),  //19

        glm::vec3(-1.2f, 0.0f, -1.2f), //20
        glm::vec3(0.0f, 0.0f, -1.2f), //21
        glm::vec3(1.2f, 0.0f, -1.2f), //22

        glm::vec3(-1.2f, -1.2f, -1.2f), //23
        glm::vec3(0.0f, -1.2f, -1.2f), //24
        glm::vec3(1.2f, -1.2f, -1.2f)  //25
    };    
};

void CCube::createLittleCubes() {
    //VERTICES*****************************************************************************************************************************
    //define vertices and positions
    for (int i = 0; i < 26; i++) {
        vector<float> vecCube;
        copy(&vertices[0], &vertices[sizeof(vertices) / sizeof(float)], back_inserter(vecCube));
        SLittleCube cube(i, iPlittleCubes[i], vecCube);
        littleCubes.push_back(cube);
    }
    
    //COLORS*****************************************************************************************************************************
    //set list of colors (L R F B D U)
    vector<vector<float>> colorCube0 = { black, red, blue, black, black, yellow };
    littleCubes[0].listOfColors = colorCube0;
    vector<vector<float>> colorCube1 = { black, red, black, black, black, yellow };
    littleCubes[1].listOfColors = colorCube1;
    vector<vector<float>> colorCube2 = { black, red, black, green, black, yellow };
    littleCubes[2].listOfColors = colorCube2;
    vector<vector<float>> colorCube3 = { black, red, blue, black, black, black };
    littleCubes[3].listOfColors = colorCube3;
    vector<vector<float>> colorCube4 = { black, red, black, black, black, black };
    littleCubes[4].listOfColors = colorCube4;
    vector<vector<float>> colorCube5 = { black, red, black, green, black, black };
    littleCubes[5].listOfColors = colorCube5;
    vector<vector<float>> colorCube6 = { black, red, blue, black, white, black };
    littleCubes[6].listOfColors = colorCube6;
    vector<vector<float>> colorCube7 = { black, red, black, black, white, black };
    littleCubes[7].listOfColors = colorCube7;
    vector<vector<float>> colorCube8 = { black, red, black, green, white, black };
    littleCubes[8].listOfColors = colorCube8;

    vector<vector<float>> colorCube9 = { black, black, blue, black, black, yellow };
    littleCubes[9].listOfColors = colorCube9;
    vector<vector<float>> colorCube10 = { black, black, black, black, black, yellow };
    littleCubes[10].listOfColors = colorCube10;
    vector<vector<float>> colorCube11 = { black, black, black, green, black, yellow };
    littleCubes[11].listOfColors = colorCube11;
    vector<vector<float>> colorCube12 = { black, black, blue, black, black, black };
    littleCubes[12].listOfColors = colorCube12;
    vector<vector<float>> colorCube13 = { black, black, black, green, black, black };
    littleCubes[13].listOfColors = colorCube13;
    vector<vector<float>> colorCube14 = { black, black, blue, black, white, black };
    littleCubes[14].listOfColors = colorCube14;
    vector<vector<float>> colorCube15 = { black, black, black, black, white, black };
    littleCubes[15].listOfColors = colorCube15;
    vector<vector<float>> colorCube16 = { black, black, black, green, white, black };
    littleCubes[16].listOfColors = colorCube16;

    vector<vector<float>> colorCube17 = { orange, black, blue, black, black, yellow };
    littleCubes[17].listOfColors = colorCube17;
    vector<vector<float>> colorCube18 = { orange, black, black, black, black, yellow };
    littleCubes[18].listOfColors = colorCube18;
    vector<vector<float>> colorCube19 = { orange, black, black, green, black, yellow };
    littleCubes[19].listOfColors = colorCube19;
    vector<vector<float>> colorCube20 = { orange, black, blue, black, black, black };
    littleCubes[20].listOfColors = colorCube20;
    vector<vector<float>> colorCube21 = { orange, black, black, black, black, black };
    littleCubes[21].listOfColors = colorCube21;
    vector<vector<float>> colorCube22 = { orange, black, black, green, black, black };
    littleCubes[22].listOfColors = colorCube22;
    vector<vector<float>> colorCube23 = { orange, black, blue, black, white, black };
    littleCubes[23].listOfColors = colorCube23;
    vector<vector<float>> colorCube24 = { orange, black, black, black, white, black };
    littleCubes[24].listOfColors = colorCube24;
    vector<vector<float>> colorCube25 = { orange, black, black, green, white, black };
    littleCubes[25].listOfColors = colorCube25;

    //define colors
    for (size_t i = 0; i < 26; i++)//each cube
    {
        for (int indexVertices = 3, indexColor = 0; indexVertices < 288; indexColor++)
        {
            for (int line = 0; line < 6; line++)
            {
                littleCubes[i].vertices[indexVertices] = littleCubes[i].listOfColors[indexColor][0];
                littleCubes[i].vertices[indexVertices + 1] = littleCubes[i].listOfColors[indexColor][1];
                littleCubes[i].vertices[indexVertices + 2] = littleCubes[i].listOfColors[indexColor][2];
                indexVertices += 8;
            }
        }
    }

    //TEXTURES*****************************************************************************************************************************
    //set textures indices
    vector<float> textureTest = {
        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,

        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,

        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,

        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,

        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,

        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0
    };

    vector<float> texture0 = {
        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,

        3.0 / 9, 2.0 / 3,
        3.5 / 9, 2.0 / 3,
        3.5 / 9, 1.0,
        3.5 / 9, 1.0,
        3.0 / 9, 1.0,
        3.0 / 9, 2.0 / 3,

        3.0 / 9, 1.0,
        2.5 / 9, 1.0,
        2.5 / 9, 2.0 / 3,
        2.5 / 9, 2.0 / 3,
        3.0 / 9, 2.0 / 3,
        3.0 / 9, 1.0,

        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,

        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,

        0 , 1.0 / 3,
        0.5 / 9 , 1.0 / 3,
        0.5 / 9 , 0,
        0.5 / 9 , 0,
        0, 0,
        0 , 1.0 / 3
    };
    littleCubes[0].textureIndices = texture0;
    vector<float> texture1 = {
        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,

        3.5 / 9, 2.0 / 3,
        4.0 / 9, 2.0 / 3,
        4.0 / 9, 1.0,
        4.0 / 9, 1.0,
        3.5 / 9, 1.0,
        3.5 / 9, 2.0 / 3,

        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,

        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,

        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,

        0.5 / 9, 1.0 / 3,
        1.0 / 9, 1.0 / 3,
        1.0 / 9, 0.0,
        1.0 / 9, 0.0,
        0.5 / 9, 0.0,
        0.5 / 9, 1.0 / 3
    };
    littleCubes[1].textureIndices = texture1;
    vector<float> texture2 = {
        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,

        4.0 / 9, 2.0 / 3,
        0.5, 2.0 / 3,
        0.5, 1.0,
        0.5, 1.0,
        4.0 / 9, 1.0,
        4.0 / 9, 2.0 / 3,

        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,

        6.0 / 9, 1.0,
        6.5 / 9, 1.0,
        6.5 / 9, 2.0 / 3,
        6.5 / 9, 2.0 / 3,
        6.0 / 9, 2.0 / 3,
        6.0 / 9, 1.0,

        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,

        1.0 / 9, 1.0 / 3,
        1.5 / 9, 1.0 / 3,
        1.5 / 9, 0.0,
        1.5 / 9, 0.0,
        1.0 / 9, 0.0,
        1.0 / 9, 1.0 / 3
    };
    littleCubes[2].textureIndices = texture2;
    vector<float> texture3 = {
        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,

        3.0 / 9, 1.0 / 3,
        3.5 / 9, 1.0 / 3,
        3.5 / 9, 2.0 / 3,
        3.5 / 9, 2.0 / 3,
        3.0 / 9, 2.0 / 3,
        3.0 / 9, 1.0 / 3,

        3.0 / 9, 2.0 / 3,
        2.5 / 9, 2.0 / 3,
        2.5 / 9, 1.0 / 3,
        2.5 / 9, 1.0 / 3,
        3.0 / 9, 1.0 / 3,
        3.0 / 9, 2.0 / 3,

        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,

        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,
        
        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0
    };
    littleCubes[3].textureIndices = texture3;
    vector<float> texture4 = {
        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,

        3.5 / 9, 1.0 / 3,
        4.0 / 9, 1.0 / 3,
        4.0 / 9, 2.0 / 3,
        4.0 / 9, 2.0 / 3,
        3.5 / 9, 2.0 / 3,
        3.5 / 9, 1.0 / 3,

        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,

        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,

        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,

        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0
    };
    littleCubes[4].textureIndices = texture4;
    vector<float> texture5 = {
        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,

        4.0 / 9, 1.0 / 3,
        0.5, 1.0 / 3,
        0.5, 2.0 / 3,
        0.5, 2.0 / 3,
        4.0 / 9, 2.0 / 3,
        4.0 / 9, 1.0 / 3,

        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,

        6.0 / 9, 2.0 / 3,
        6.5 / 9, 2.0 / 3,
        6.5 / 9, 1.0 / 3,
        6.5 / 9, 1.0 / 3,
        6.0 / 9, 1.0 / 3,
        6.0 / 9, 2.0 / 3,

        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,

        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0
    };
    littleCubes[5].textureIndices = texture5;
    vector<float> texture6 = {
        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,

        3.0 / 9, 0.0,
        3.5 / 9, 0.0,
        3.5 / 9, 1.0 / 3,
        3.5 / 9, 1.0 / 3,
        3.0 / 9, 1.0 / 3,
        3.0 / 9, 0.0,

        3.0 / 9, 1.0 / 3,
        2.5 / 9, 1.0 / 3,
        2.5 / 9, 0.0,
        2.5 / 9, 0.0,
        3.0 / 9, 0.0,
        3.0 / 9, 1.0 / 3,

        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,

        0.5 , 2.0 / 3,
        5.0 / 9 , 2.0 / 3,
        5.0 / 9 , 1.0,
        5.0 / 9 , 1.0,
        0.5 , 1.0,
        0.5 , 2.0 / 3,

        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0
    };
    littleCubes[6].textureIndices = texture6;
    vector<float> texture7 = {
        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,

        3.5 / 9, 0.0,
        4.0 / 9, 0.0,
        4.0 / 9, 1.0 / 3,
        4.0 / 9, 1.0 / 3,
        3.5 / 9, 1.0 / 3,
        3.5 / 9, 0.0,

        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,

        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,

        5.0 / 9, 2.0 / 3,
        5.5 / 9, 2.0 / 3,
        5.5 / 9, 1.0,
        5.5 / 9, 1.0,
        5.0 / 9, 1.0,
        5.0 / 9, 2.0 / 3,

        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0
    };
    littleCubes[7].textureIndices = texture7;
    vector<float> texture8 = {
        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,

        4.0 / 9, 0.0,
        0.5, 0.0,
        0.5, 1.0 / 3,
        0.5, 1.0 / 3,
        4.0 / 9, 1.0 / 3,
        4.0 / 9, 0.0,

        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,

        6.0 / 9, 1.0 / 3,
        6.5 / 9, 1.0 / 3,
        6.5 / 9, 0.0,
        6.5 / 9, 0.0,
        6.0 / 9, 0.0,
        6.0 / 9, 1.0 / 3,

        5.5 / 9, 2.0 / 3,
        6.0 / 9, 2.0 / 3,
        6.0 / 9, 1.0,
        6.0 / 9, 1.0,
        5.5 / 9, 1.0,
        5.5 / 9, 2.0 / 3,

        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0
    };
    littleCubes[8].textureIndices = texture8;
    vector<float> texture9 = {
        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,

        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,

        2.5 / 9, 1.0,
        2.0 / 9, 1.0,
        2.0 / 9, 2.0 / 3,
        2.0 / 9, 2.0 / 3,
        2.5 / 9, 2.0 / 3,
        2.5 / 9, 1.0,

        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,

        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,

        0.0, 2.0 / 3,
        0.5 / 9, 2.0 / 3,
        0.5 / 9, 1.0 / 3,
        0.5 / 9, 1.0 / 3,
        0.0, 1.0 / 3,
        0.0, 2.0 / 3
    };
    littleCubes[9].textureIndices = texture9;
    vector<float> texture10 = {
        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,

        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,

        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,

        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,

        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,

        0.5 / 9, 2.0 / 3,
        1.0 / 9, 2.0 / 3,
        1.0 / 9, 1.0 / 3,
        1.0 / 9, 1.0 / 3,
        0.5 / 9, 1.0 / 3,
        0.5 / 9, 2.0 / 3
    };
    littleCubes[10].textureIndices = texture10;
    vector<float> texture11 = {
        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,

        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,

        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,

        6.5 / 9, 1.0,
        7.0 / 9, 1.0,
        7.0 / 9, 2.0 / 3,
        7.0 / 9, 2.0 / 3,
        6.5 / 9, 2.0 / 3,
        6.5 / 9, 1.0,

        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,

        1.0 / 9, 2.0 / 3,
        1.5 / 9, 2.0 / 3,
        1.5 / 9, 1.0 / 3,
        1.5 / 9, 1.0 / 3,
        1.0 / 9, 1.0 / 3,
        1.0 / 9, 2.0 / 3
    };
    littleCubes[11].textureIndices = texture11;
    vector<float> texture12 = {
        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,

        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,

        2.5 / 9, 2.0 / 3,
        2.0 / 9, 2.0 / 3,
        2.0 / 9, 1.0 / 3,
        2.0 / 9, 1.0 / 3,
        2.5 / 9, 1.0 / 3,
        2.5 / 9, 2.0 / 3,

        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,

        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,

        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0
    };
    littleCubes[12].textureIndices = texture12;
    vector<float> texture13 = {
        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,

        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,

        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,

        6.5 / 9, 2.0 / 3,
        7.0 / 9, 2.0 / 3,
        7.0 / 9, 1.0 / 3,
        7.0 / 9, 1.0 / 3,
        6.5 / 9, 1.0 / 3,
        6.5 / 9, 2.0 / 3,

        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,

        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0
    };
    littleCubes[13].textureIndices = texture13;
    vector<float> texture14 = {
        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,

        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,

        2.5 / 9, 1.0 / 3,
        2.0 / 9, 1.0 / 3,
        2.0 / 9, 0.0,
        2.0 / 9, 0.0,
        2.5 / 9, 0.0,
        2.5 / 9, 1.0 / 3,

        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,

        0.5, 1.0 / 3,
        5.0 / 9, 1.0 / 3,
        5.0 / 9, 2.0 / 3,
        5.0 / 9, 2.0 / 3,
        0.5, 2.0 / 3,
        0.5, 1.0 / 3,

        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0
    };
    littleCubes[14].textureIndices = texture14;
    vector<float> texture15 = {
        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,

        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,

        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,

        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,

        5.0 / 9, 1.0 / 3,
        5.5 / 9, 1.0 / 3,
        5.5 / 9, 2.0 / 3,
        5.5 / 9, 2.0 / 3,
        5.0 / 9, 2.0 / 3,
        5.0 / 9, 1.0 / 3,

        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0
    };
    littleCubes[15].textureIndices = texture15;
    vector<float> texture16 = {
        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,

        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,

        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,

        6.5 / 9, 1.0 / 3,
        7.0 / 9, 1.0 / 3,
        7.0 / 9, 0.0,
        7.0 / 9, 0.0,
        6.5 / 9, 0.0,
        6.5 / 9, 1.0 / 3,

        5.5 / 9, 1.0 / 3,
        6.0 / 9, 1.0 / 3,
        6.0 / 9, 2.0 / 3,
        6.0 / 9, 2.0 / 3,
        5.5 / 9, 2.0 / 3,
        5.5 / 9, 1.0 / 3,

        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0
    };
    littleCubes[16].textureIndices = texture16;
    vector<float> texture17 = {
        1.0, 2.0 / 3,
        8.5 / 9, 2.0 / 3,
        8.5 / 9, 1.0,
        8.5 / 9, 1.0,
        1.0, 1.0,
        1.0, 2.0 / 3,

        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,

        2.0 / 9, 1.0,
        1.5 / 9, 1.0,
        1.5 / 9, 2.0 / 3,
        1.5 / 9, 2.0 / 3,
        2.0 / 9, 2.0 / 3,
        2.0 / 9, 1.0,

        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,

        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,

        0.0, 1.0,
        0.5 / 9, 1.0,
        0.5 / 9, 2.0 / 3,
        0.5 / 9, 2.0 / 3,
        0.0, 2.0 / 3,
        0.0, 1.0
    };
    littleCubes[17].textureIndices = texture17;
    vector<float> texture18 = {
        8.5 / 9, 2.0 / 3,
        8.0 / 9, 2.0 / 3,
        8.0 / 9, 1.0,
        8.0 / 9, 1.0,
        8.5 / 9, 1.0,
        8.5 / 9, 2.0 / 3,

        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,

        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,

        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,

        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,

        0.5 / 9, 1.0,
        1.0 / 9, 1.0,
        1.0 / 9, 2.0 / 3,
        1.0 / 9, 2.0 / 3,
        0.5 / 9, 2.0 / 3,
        0.5 / 9, 1.0
    };
    littleCubes[18].textureIndices = texture18;
    vector<float> texture19 = {
        8.0 / 9, 2.0 / 3,
        7.5 / 9, 2.0 / 3,
        7.5 / 9, 1.0,
        7.5 / 9, 1.0,
        8.0 / 9, 1.0,
        8.0 / 9, 2.0 / 3,

        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,

        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,

        7.0 / 9, 1.0,
        7.5 / 9, 1.0,
        7.5 / 9, 2.0 / 3,
        7.5 / 9, 2.0 / 3,
        7.0 / 9, 2.0 / 3,
        7.0 / 9, 1.0,

        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,

        1.0 / 9, 1.0,
        1.5 / 9, 1.0,
        1.5 / 9, 2.0 / 3,
        1.5 / 9, 2.0 / 3,
        1.0 / 9, 2.0 / 3,
        1.0 / 9, 1.0
    };
    littleCubes[19].textureIndices = texture19;
    vector<float> texture20 = {
        1.0, 1.0 / 3,
        8.5 / 9, 1.0 / 3,
        8.5 / 9, 2.0 / 3,
        8.5 / 9, 2.0 / 3,
        1.0, 2.0 / 3,
        1.0, 1.0 / 3,

        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,

        2.0 / 9, 2.0 / 3,
        1.5 / 9, 2.0 / 3,
        1.5 / 9, 1.0 / 3,
        1.5 / 9, 1.0 / 3,
        2.0 / 9, 1.0 / 3,
        2.0 / 9, 2.0 / 3,

        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,

        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,

        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0
    };
    littleCubes[20].textureIndices = texture20;
    vector<float> texture21 = {
        8.5 / 9, 1.0 / 3,
        8.0 / 9, 1.0 / 3,
        8.0 / 9, 2.0 / 3,
        8.0 / 9, 2.0 / 3,
        8.5 / 9, 2.0 / 3,
        8.5 / 9, 1.0 / 3,

        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,

        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,

        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,

        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,

        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0
    };
    littleCubes[21].textureIndices = texture21;
    vector<float> texture22 = {
        8.0 / 9, 1.0 / 3,
        7.5 / 9, 1.0 / 3,
        7.5 / 9, 2.0 / 3,
        7.5 / 9, 2.0 / 3,
        8.0 / 9, 2.0 / 3,
        8.0 / 9, 1.0 / 3,

        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,

        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,

        7.0 / 9, 2.0 / 3,
        7.5 / 9, 2.0 / 3,
        7.5 / 9, 1.0 / 3,
        7.5 / 9, 1.0 / 3,
        7.0 / 9, 1.0 / 3,
        7.0 / 9, 2.0 / 3,

        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,

        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0
    };
    littleCubes[22].textureIndices = texture22;
    vector<float> texture23 = {
        1.0, 0.0,
        8.5 / 9, 0.0,
        8.5 / 9, 1.0 / 3,
        8.5 / 9, 1.0 / 3,
        1.0, 1.0 / 3,
        1.0, 0.0,

        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,

        2.0 / 9, 1.0 / 3,
        1.5 / 9, 1.0 / 3,
        1.5 / 9, 0.0,
        1.5 / 9, 0.0,
        2.0 / 9, 0.0,
        2.0 / 9, 1.0 / 3,

        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,

        0.5, 0.0,
        5.0 / 9, 0.0,
        5.0 / 9, 1.0 / 3,
        5.0 / 9, 1.0 / 3,
        0.5, 1.0 / 3,
        0.5, 0.0,

        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0
    };
    littleCubes[23].textureIndices = texture23;
    vector<float> texture24 = {
        8.5 / 9, 0.0,
        8.0 / 9, 0.0,
        8.0 / 9, 1.0 / 3,
        8.0 / 9, 1.0 / 3,
        8.5 / 9, 1.0 / 3,
        8.5 / 9, 0.0,

        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,

        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,

        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,

        5.0 / 9, 0.0,
        5.5 / 9, 0.0,
        5.5 / 9, 1.0 / 3,
        5.5 / 9, 1.0 / 3,
        5.0 / 9, 1.0 / 3,
        5.0 / 9, 0.0,

        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0
    };
    littleCubes[24].textureIndices = texture24;
    vector<float> texture25 = {
        8.0 / 9, 0.0,
        7.5 / 9, 0.0,
        7.5 / 9, 1.0 / 3,
        7.5 / 9, 1.0 / 3,
        8.0 / 9, 1.0 / 3,
        8.0 / 9, 0.0,

        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,

        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,

        7.0 / 9, 1.0 / 3,
        7.5 / 9, 1.0 / 3,
        7.5 / 9, 0.0,
        7.5 / 9, 0.0,
        7.0 / 9, 0.0,
        7.0 / 9, 1.0 / 3,

        5.5 / 9, 0.0,
        6.0 / 9, 0.0,
        6.0 / 9, 1.0 / 3,
        6.0 / 9, 1.0 / 3,
        5.5 / 9, 1.0 / 3,
        5.5 / 9, 0.0,

        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0
    };
    littleCubes[25].textureIndices = texture25;
    
    //define textures
    for (size_t i = 0; i < 26; i++)//each cube
    {
        for (int indexVertices = 6, indexTexture = 0;
            indexVertices < 288;
            indexTexture+=2, indexVertices += 8)
        {
            littleCubes[i].vertices[indexVertices] = littleCubes[i].textureIndices[indexTexture];
            littleCubes[i].vertices[indexVertices + 1] = littleCubes[i].textureIndices[indexTexture + 1];
        }
    }

    //set groups*************************************************************************************************************************
    vector<char> camada0 = { 'R', 'U', 'F' };
    littleCubes[0].camadas = camada0;
    vector<char> camada1 = { 'R', 'U', 'S' };
    littleCubes[1].camadas = camada1;
    vector<char> camada2 = { 'R', 'U', 'B' };
    littleCubes[2].camadas = camada2;

    vector<char> camada3 = { 'R', 'E', 'F' };
    littleCubes[3].camadas = camada3;
    vector<char> camada4 = { 'R', 'E', 'S' };
    littleCubes[4].camadas = camada4;
    vector<char> camada5 = { 'R', 'E', 'B' };
    littleCubes[5].camadas = camada5;

    vector<char> camada6 = { 'R', 'D', 'F' };
    littleCubes[6].camadas = camada6;
    vector<char> camada7 = { 'R', 'D', 'S' };
    littleCubes[7].camadas = camada7;
    vector<char> camada8 = { 'R', 'D', 'B' };
    littleCubes[8].camadas = camada8;

    vector<char> camada9 = { 'M', 'U', 'F' };
    littleCubes[9].camadas = camada9;
    vector<char> camada10 = { 'M', 'U', 'S' };
    littleCubes[10].camadas = camada10;
    vector<char> camada11 = { 'M', 'U', 'B' };
    littleCubes[11].camadas = camada11;

    vector<char> camada12 = { 'M', 'E', 'F' };
    littleCubes[12].camadas = camada12;
    vector<char> camada13 = { 'M', 'E', 'B' };
    littleCubes[13].camadas = camada13;

    vector<char> camada14 = { 'M', 'D', 'F' };
    littleCubes[14].camadas = camada14;
    vector<char> camada15 = { 'M', 'D', 'S' };
    littleCubes[15].camadas = camada15;
    vector<char> camada16 = { 'M', 'D', 'B' };
    littleCubes[16].camadas = camada16;

    vector<char> camada17 = { 'L', 'U', 'F' };
    littleCubes[17].camadas = camada17;
    vector<char> camada18 = { 'L', 'U', 'S' };
    littleCubes[18].camadas = camada18;
    vector<char> camada19 = { 'L', 'U', 'B' };
    littleCubes[19].camadas = camada19;

    vector<char> camada20 = { 'L', 'E', 'F' };
    littleCubes[20].camadas = camada20;
    vector<char> camada21 = { 'L', 'E', 'S' };
    littleCubes[21].camadas = camada21;
    vector<char> camada22 = { 'L', 'E', 'B' };
    littleCubes[22].camadas = camada22;

    vector<char> camada23 = { 'L', 'D', 'F' };
    littleCubes[23].camadas = camada23;
    vector<char> camada24 = { 'L', 'D', 'S' };
    littleCubes[24].camadas = camada24;
    vector<char> camada25 = { 'L', 'D', 'B' };
    littleCubes[25].camadas = camada25;

    //set initial positions
    for (size_t i = 0; i < 26; i++)
        translatePoints(littleCubes[i].vertices, littleCubes[i].initialPosition.x, littleCubes[i].initialPosition.y, littleCubes[i].initialPosition.z);

    //FOR ANIMATION 2*************************************************************************************************************************
    vector<float> a2Par_0 = { 5.0, 135.0, 0.0};
    vector<float> a2Par_1 = { 5.0, 180.0, 0.0};
    vector<float> a2Par_2 = { 5.0, 225.0, 0.0};
    vector<float> a2Par_3 = { 3.5, 135.0, 0.0 };
    vector<float> a2Par_4 = { 3.5, 180.0, 0.0};
    vector<float> a2Par_5 = { 3.5, 225.0, 0.0};
    vector<float> a2Par_6 = { 2.0, 135.0, 0.0 };
    vector<float> a2Par_7 = { 2.0, 180.0, 0.0};
    vector<float> a2Par_8 = { 2.0, 225.0, 0.0};
    vector<float> a2Par_9 = { 5.0, 90.0, 0.0 };
    vector<float> a2Par_10 = { 5.0, 60.0, 0.0 };
    vector<float> a2Par_11 = { 5.0, 270.0, 0.0 };
    vector<float> a2Par_12 = { 3.5, 90.0, 0.0 };
    vector<float> a2Par_13 = { 3.5, 270.0, 0.0 };
    vector<float> a2Par_14 = { 2.0, 90.0, 0.0 };
    vector<float> a2Par_15 = { 2.0, 60.0, 0.0 };
    vector<float> a2Par_16 = { 2.0, 270.0, 0.0 };
    vector<float> a2Par_17 = { 5.0, 45.0, 0.0 };
    vector<float> a2Par_18 = { 5.0, 0.0, 0.0 };
    vector<float> a2Par_19 = { 5.0, 315.0, 0.0 };
    vector<float> a2Par_20 = { 3.5, 45.0, 0.0 };
    vector<float> a2Par_21 = { 3.5, 0.0, 0.0 };
    vector<float> a2Par_22 = { 3.5, 315.0, 0.0 };
    vector<float> a2Par_23 = { 2.0, 45.0, 0.0 };
    vector<float> a2Par_24 = { 2.0, 0.0, 0.0 };
    vector<float> a2Par_25 = { 2.0, 315.0, 0.0 };
    littleCubes[0].animation2Parameters = a2Par_0;
    littleCubes[1].animation2Parameters = a2Par_1;
    littleCubes[2].animation2Parameters = a2Par_2;
    littleCubes[3].animation2Parameters = a2Par_3;
    littleCubes[4].animation2Parameters = a2Par_4;
    littleCubes[5].animation2Parameters = a2Par_5;
    littleCubes[6].animation2Parameters = a2Par_6;
    littleCubes[7].animation2Parameters = a2Par_7;
    littleCubes[8].animation2Parameters = a2Par_8;
    littleCubes[9].animation2Parameters = a2Par_9;
    littleCubes[10].animation2Parameters = a2Par_10;
    littleCubes[11].animation2Parameters = a2Par_11;
    littleCubes[12].animation2Parameters = a2Par_12;
    littleCubes[13].animation2Parameters = a2Par_13;
    littleCubes[14].animation2Parameters = a2Par_14;
    littleCubes[15].animation2Parameters = a2Par_15;
    littleCubes[16].animation2Parameters = a2Par_16;
    littleCubes[17].animation2Parameters = a2Par_17;
    littleCubes[18].animation2Parameters = a2Par_18;
    littleCubes[19].animation2Parameters = a2Par_19;
    littleCubes[20].animation2Parameters = a2Par_20;
    littleCubes[21].animation2Parameters = a2Par_21;
    littleCubes[22].animation2Parameters = a2Par_22;
    littleCubes[23].animation2Parameters = a2Par_23;
    littleCubes[24].animation2Parameters = a2Par_24;
    littleCubes[25].animation2Parameters = a2Par_25;
}

void CCube::drawCube(unsigned int* VBO, unsigned int* VAO) {
    for (int i = 0; i < 26; i++) {
        glBindVertexArray(*(VAO + i));
        glBindBuffer(GL_ARRAY_BUFFER, *(VBO + i));
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &(littleCubes[i].vertices[0]), GL_STATIC_DRAW);
        //POSITIONS
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        //COLORS
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        //TEXTURES
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);
    }
}

void CCube::restartValues(int littleCubeIndex) {
    //reset vertices values
    vector<float> vecCube;
    copy(&vertices[0], &vertices[sizeof(vertices) / sizeof(float)], back_inserter(vecCube));
    littleCubes[littleCubeIndex].vertices = vecCube;
    //store values again
    //position
    translatePoints(littleCubes[littleCubeIndex].vertices, littleCubes[littleCubeIndex].initialPosition.x, littleCubes[littleCubeIndex].initialPosition.y, littleCubes[littleCubeIndex].initialPosition.z);
    
    //color
    for (int indexVertices = 3, indexColor = 0; indexVertices < 288; indexColor++)
    {
        for (int line = 0; line < 6; line++)
        {
            littleCubes[littleCubeIndex].vertices[indexVertices] = littleCubes[littleCubeIndex].listOfColors[indexColor][0];
            littleCubes[littleCubeIndex].vertices[indexVertices + 1] = littleCubes[littleCubeIndex].listOfColors[indexColor][1];
            littleCubes[littleCubeIndex].vertices[indexVertices + 2] = littleCubes[littleCubeIndex].listOfColors[indexColor][2];
            indexVertices += 8;
        }
    }
    //texture
    for (int indexVertices = 6, indexTexture = 0;
        indexVertices < 288;
        indexTexture += 2, indexVertices += 8)
    {
        littleCubes[littleCubeIndex].vertices[indexVertices] = littleCubes[littleCubeIndex].textureIndices[indexTexture];
        littleCubes[littleCubeIndex].vertices[indexVertices + 1] = littleCubes[littleCubeIndex].textureIndices[indexTexture + 1];
    }
}

void CCube::moveR(float angle) {
    bool selectedCube = false;
    for (unsigned int indexCube = 0; indexCube < 26; indexCube++)
    {
        for (int i = 0; i < 3; i++) {
            if (littleCubes[indexCube].camadas[i] == 'R') {
                selectedCube = true;
                break;
            }
        }
        if (selectedCube) {
            Zrotation(littleCubes[indexCube].vertices, angle);
            selectedCube = false;
        }
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
}

void CCube::moveL(float angle) {
    bool selectedCube = false;
    for (unsigned int indexCube = 0; indexCube < 26; indexCube++)
    {
        for (int i = 0; i < 3; i++) {
            if (littleCubes[indexCube].camadas[i] == 'L') {
                selectedCube = true;
                break;
            }
        }
        if (selectedCube) {
            Zrotation(littleCubes[indexCube].vertices, angle);
            selectedCube = false;
        }
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
}

void CCube::moveU(float angle) {
    bool selectedCube = false;
    for (unsigned int indexCube = 0; indexCube < 26; indexCube++)
    {
        for (int i = 0; i < 3; i++) {
            if (littleCubes[indexCube].camadas[i] == 'U') {
                selectedCube = true;
                break;
            }
        }
        if (selectedCube) {
            Yrotation(littleCubes[indexCube].vertices, angle);
            selectedCube = false;
        }
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
}

void CCube::moveD(float angle) {
    bool selectedCube = false;
    for (unsigned int indexCube = 0; indexCube < 26; indexCube++)
    {
        for (int i = 0; i < 3; i++) {
            if (littleCubes[indexCube].camadas[i] == 'D') {
                selectedCube = true;
                break;
            }
        }
        if (selectedCube) {
            Yrotation(littleCubes[indexCube].vertices, angle);
            selectedCube = false;
        }
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
}

void CCube::moveF(float angle) {
    bool selectedCube = false;
    for (unsigned int indexCube = 0; indexCube < 26; indexCube++)
    {
        for (int i = 0; i < 3; i++) {
            if (littleCubes[indexCube].camadas[i] == 'F') {
                selectedCube = true;
                break;
            }
        }
        if (selectedCube) {
            Xrotation(littleCubes[indexCube].vertices, angle);
            selectedCube = false;
        }
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
}

void CCube::moveB(float angle) {
    bool selectedCube = false;
    for (unsigned int indexCube = 0; indexCube < 26; indexCube++)
    {
        for (int i = 0; i < 3; i++) {
            if (littleCubes[indexCube].camadas[i] == 'B') {
                selectedCube = true;
                break;
            }
        }
        if (selectedCube) {
            Xrotation(littleCubes[indexCube].vertices, angle);
            selectedCube = false;
        }
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
}

void CCube::animation1(float distancia) {
    for (unsigned int indexCube = 0; indexCube < 26; indexCube++){
        littleCubes[indexCube].Alejarse(littleCubes[indexCube].initialPosition, distancia);
    }
}

void SLittleCube::Alejarse(glm::vec3 centro, float distancia) {
    glm::vec3 direccion_alej = centro;
    if (direccion_alej.x > 0) {
        direccion_alej.x = 1;
    }
    if (direccion_alej.y > 0) {
        direccion_alej.y = 1;
    }
    if (direccion_alej.z > 0) {
        direccion_alej.z = 1;
    }
    modelo = glm::translate(glm::mat4(1.0), direccion_alej * distancia) * modelo;
    centro_cubo = glm::mat3(glm::translate(glm::mat4(1.0), direccion_alej * distancia)) * centro_cubo;
}

void CCube::animation2(bool reverse, float b1, float angle) {
    for (unsigned int indexCube = 0; indexCube < 26; indexCube++)
    {
        //it was used parametric ecuations and derivation
        /*
        * difX = (a * sen(alfa) * cos(theta))| thetaF/thetaI
        * difY = (-b * sen(theta))| thetaF/thetaI
        * difZ = (c * cos(alfa) * cos(theta))| thetaF/thetaI
        * 
        * where:    b = b0 + b1
        *           a,c : cte.
        *           b0 = highest 'y' for each little cube
        *           b1 = yFloor
        */
        //calculate b0 only for the first time
        if (angle == 1.0 && !reverse) {
            float b0 = numeric_limits<float>::min();
            for (int vertexIndex = 1; vertexIndex < 288; vertexIndex += 8)//iterate in each 'y' value
            {
                if (b0 < littleCubes[indexCube].vertices[vertexIndex])
                    b0 = littleCubes[indexCube].vertices[vertexIndex];
            }
            littleCubes[indexCube].animation2Parameters[2] = b0;
        }        
        //calculate variations of 'x' 'y' 'z'
        float difX, difY, difZ;
        if (!reverse) {
            difX = littleCubes[indexCube].animation2Parameters[0] * sin(glm::radians(littleCubes[indexCube].animation2Parameters[1])) * (cos(glm::radians(angle)) - cos(glm::radians(angle - 1)));
            difY = -(b1 + littleCubes[indexCube].animation2Parameters[2]) * (sin(glm::radians(angle)) - sin(glm::radians(angle - 1)));
            difZ = littleCubes[indexCube].animation2Parameters[0] * cos(glm::radians(littleCubes[indexCube].animation2Parameters[1])) * (cos(glm::radians(angle)) - cos(glm::radians(angle - 1)));
        }
        else {
            difX = littleCubes[indexCube].animation2Parameters[0] * sin(glm::radians(littleCubes[indexCube].animation2Parameters[1])) * (cos(glm::radians(angle)) - cos(glm::radians(angle + 1)));
            difY = -(b1 + littleCubes[indexCube].animation2Parameters[2]) * (sin(glm::radians(angle)) - sin(glm::radians(angle + 1)));
            difZ = littleCubes[indexCube].animation2Parameters[0] * cos(glm::radians(littleCubes[indexCube].animation2Parameters[1])) * (cos(glm::radians(angle)) - cos(glm::radians(angle + 1)));
        }
        translatePoints(littleCubes[indexCube].vertices, difX, difY, difZ);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    
}

CCube::CCube()
{

}

CCube::~CCube()
{
}