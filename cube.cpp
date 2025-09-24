#include <iostream>
using namespace std;

// Colors
enum class Color { WHITE, GREEN, RED, BLUE, ORANGE, YELLOW };

// Faces
enum class Face { UP, LEFT, FRONT, RIGHT, BACK, DOWN };

// Convert color enum → letter for printing
char colorToChar(Color c) {
    switch (c) {
        case Color::WHITE:  return 'W';
        case Color::GREEN:  return 'G';
        case Color::RED:    return 'R';
        case Color::BLUE:   return 'B';
        case Color::ORANGE: return 'O';
        case Color::YELLOW: return 'Y';
    }
    return '?'; // default
}

// Cube: 6 faces × 9 stickers
Color cube[6][9];

// Convert Face enum → index (0–5) for array access
int faceIndex(Face f) {
    return static_cast<int>(f);
}

// Initialize cube to solved state
void initCube() {
    for (int i = 0; i < 9; i++) cube[faceIndex(Face::UP)][i]    = Color::WHITE;
    for (int i = 0; i < 9; i++) cube[faceIndex(Face::LEFT)][i]  = Color::GREEN;
    for (int i = 0; i < 9; i++) cube[faceIndex(Face::FRONT)][i] = Color::RED;
    for (int i = 0; i < 9; i++) cube[faceIndex(Face::RIGHT)][i] = Color::BLUE;
    for (int i = 0; i < 9; i++) cube[faceIndex(Face::BACK)][i]  = Color::ORANGE;
    for (int i = 0; i < 9; i++) cube[faceIndex(Face::DOWN)][i]  = Color::YELLOW;
}

// Rotate a face clockwise
void rotateFaceClockwise(Face face) {
    int f = faceIndex(face);
    Color tmp[9];
    for (int i = 0; i < 9; i++) tmp[i] = cube[f][i];
    cube[f][0] = tmp[6];
    cube[f][1] = tmp[3];
    cube[f][2] = tmp[0];
    cube[f][3] = tmp[7];
    cube[f][4] = tmp[4];
    cube[f][5] = tmp[1];
    cube[f][6] = tmp[8];
    cube[f][7] = tmp[5];
    cube[f][8] = tmp[2];
}

// Apply U move (Up face clockwise)
void moveU() {
    int U = faceIndex(Face::UP);
    int L = faceIndex(Face::LEFT);
    int F = faceIndex(Face::FRONT);
    int R = faceIndex(Face::RIGHT);
    int B = faceIndex(Face::BACK);

    // 1. Rotate UP face
    rotateFaceClockwise(Face::UP);

    // 2. Cycle top rows of L, F, R, B
    Color tmp[3];
    for (int i = 0; i < 3; i++) tmp[i] = cube[L][i];

    for (int i = 0; i < 3; i++) cube[L][i] = cube[B][i];
    for (int i = 0; i < 3; i++) cube[B][i] = cube[R][i];
    for (int i = 0; i < 3; i++) cube[R][i] = cube[F][i];
    for (int i = 0; i < 3; i++) cube[F][i] = tmp[i];
}

// Print cube in net layout
void printCube() {
    int U = faceIndex(Face::UP);
    int L = faceIndex(Face::LEFT);
    int F = faceIndex(Face::FRONT);
    int R = faceIndex(Face::RIGHT);
    int B = faceIndex(Face::BACK);
    int D = faceIndex(Face::DOWN);

    cout << "    ";
    for (int i = 0; i < 3; i++) cout << colorToChar(cube[U][i]) << " ";
    cout << "\n    ";
    for (int i = 3; i < 6; i++) cout << colorToChar(cube[U][i]) << " ";
    cout << "\n    ";
    for (int i = 6; i < 9; i++) cout << colorToChar(cube[U][i]) << " ";
    cout << "\n\n";

    for (int row = 0; row < 3; row++) {
        for (int f : {L, F, R, B}) {
            for (int col = 0; col < 3; col++) {
                cout << colorToChar(cube[f][row*3 + col]) << " ";
            }
            cout << " ";
        }
        cout << "\n";
    }

    cout << "\n    ";
    for (int i = 0; i < 3; i++) cout << colorToChar(cube[D][i]) << " ";
    cout << "\n    ";
    for (int i = 3; i < 6; i++) cout << colorToChar(cube[D][i]) << " ";
    cout << "\n    ";
    for (int i = 6; i < 9; i++) cout << colorToChar(cube[D][i]) << " ";
    cout << "\n";
}

int main() {
    initCube();

    cout << "Solved Cube:\n";
    printCube();

    cout << "\nAfter U move:\n";
    moveU();
    printCube();

    return 0;
}
