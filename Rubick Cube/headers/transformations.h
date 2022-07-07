#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <math.h>

#include <vector>

using namespace std;

void multMatrix(vector<float>& result, vector<vector<float>>& A, float x, float y, float z, float w) {
    result[0] = A[0][0] * x + A[0][1] * y + A[0][2] * z + A[0][3] * w;
    result[1] = A[1][0] * x + A[1][1] * y + A[1][2] * z + A[1][3] * w;
    result[2] = A[2][0] * x + A[2][1] * y + A[2][2] * z + A[2][3] * w;
    result[3] = A[3][0] * x + A[3][1] * y + A[3][2] * z + A[3][3] * w;
}

void translatePoints(vector<float>& vert, float x, float y, float z) {
    vector<vector<float>> matrix_translation{
        {1, 0, 0, x},
        {0, 1, 0, y},
        {0, 0, 1, z},
        {0, 0, 0, 1}
    };
    for (vector<float>::iterator it = vert.begin(); it < vert.end(); it += 8) {
        vector<float> result(4, 0);
        multMatrix(result, matrix_translation, *it, *(it + 1), *(it + 2), 1);
        *it = result[0];
        *(it + 1) = result[1];
        *(it + 2) = result[2];
    }
}

void Xrotation(vector<float>& vert, float angle) {
    vector<vector<float>> matrix_translation{
        {1, 0, 0, 0},
        {0, static_cast<float>(cos(glm::radians(angle))), static_cast<float>(-sin(glm::radians(angle))), 0},
        {0, static_cast<float>(sin(glm::radians(angle))), static_cast<float>(cos(glm::radians(angle))), 0},
        {0, 0, 0, 1}
    };
    for (vector<float>::iterator it = vert.begin(); it < vert.end(); it += 8) {
        vector<float> result(4, 0);
        multMatrix(result, matrix_translation, *it, *(it + 1), *(it + 2), 1);
        *it = result[0];
        *(it + 1) = result[1];
        *(it + 2) = result[2];
    }
}

void Yrotation(vector<float>& vert, float angle) {
    vector<vector<float>> matrix_translation{
        {static_cast<float>(cos(glm::radians(angle))), 0, static_cast<float>(sin(glm::radians(angle))), 0},
        {0, 1, 0, 0},
        {static_cast<float>(-sin(glm::radians(angle))), 0, static_cast<float>(cos(glm::radians(angle))), 0},
        {0, 0, 0, 1}
    };
    for (vector<float>::iterator it = vert.begin(); it < vert.end(); it += 8) {
        vector<float> result(4, 0);
        multMatrix(result, matrix_translation, *it, *(it + 1), *(it + 2), 1);
        *it = result[0];
        *(it + 1) = result[1];
        *(it + 2) = result[2];
    }
}

void Zrotation(vector<float>& vert, float angle) {
    vector<vector<float>> matrix_translation{
        {static_cast<float>(cos(glm::radians(angle))), static_cast<float>(-sin(glm::radians(angle))), 0, 0},
        {static_cast<float>(sin(glm::radians(angle))), static_cast<float>(cos(glm::radians(angle))), 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1}
    };
    for (vector<float>::iterator it = vert.begin(); it < vert.end(); it += 8) {
        vector<float> result(4, 0);
        multMatrix(result, matrix_translation, *it, *(it + 1), *(it + 2), 1);
        *it = result[0];
        *(it + 1) = result[1];
        *(it + 2) = result[2];
    }
}