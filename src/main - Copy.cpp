#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp> //core glm functionality
#include <glm/gtc/matrix_transform.hpp> //glm extension for generating common transformation matrices
#include <glm/gtc/matrix_inverse.hpp> //glm extension for computing inverse matrices
#include <glm/gtc/type_ptr.hpp> //glm extension for accessing the internal data structure of glm types

#include "Window.h"
#include "Shader.hpp"
#include "Camera.hpp"
#include "Car.hpp"
#include "Model3D.hpp"

#include <iostream>
#include <Windows.h>
#include <MMSystem.h>


void increaseFog();
void decreaseFog();

int glWindowWidth = 1920;
int glWindowHeight = 1080;
GLFWwindow* glWindow = NULL;

bool makeFogVisible = false;

float mouseSpeed;
float horizontalAngle;
float verticalAngle;


// window
gps::Window myWindow;

// matrices
glm::mat4 model;
glm::mat4 view;
glm::mat4 projection;
glm::mat4 lightRotation;
glm::mat3 normalMatrix;

// light parameters
glm::vec3 lightDir;
glm::vec3 lightColor;
glm::vec3 lightPosEye;

// shader uniform locations
GLuint modelLoc;
GLuint viewLoc;
GLuint projectionLoc;
GLuint normalMatrixLoc;
GLuint lightDirLoc;
GLuint lightColorLoc;
GLuint lightPosEyeLoc;
GLuint fogDensityLoc;

glm::vec3 spotDir_0;
GLuint spotDir_0Loc;
glm::vec3 spotPos_0;
GLuint spotPos_0Loc;
GLfloat spotTheta_0;
GLuint spotTheta_0Loc;

glm::vec3 spotDir_1;
GLuint spotDir_1Loc;
glm::vec3 spotPos_1;
GLuint spotPos_1Loc;
GLfloat spotTheta_1;
GLuint spotTheta_1Loc;

glm::vec3 spotDir_2;
GLuint spotDir_2Loc;
glm::vec3 spotPos_2;
GLuint spotPos_2Loc;
GLfloat spotTheta_2;
GLuint spotTheta_2Loc;

glm::vec3 spotDir_3;
GLuint spotDir_3Loc;
glm::vec3 spotPos_3;
GLuint spotPos_3Loc;
GLfloat spotTheta_3;
GLuint spotTheta_3Loc;

glm::vec3 spotDir_4;
GLuint spotDir_4Loc;
glm::vec3 spotPos_4;
GLuint spotPos_4Loc;
GLfloat spotTheta_4;
GLuint spotTheta_4Loc;

glm::vec3 spotDir_5;
GLuint spotDir_5Loc;
glm::vec3 spotPos_5;
GLuint spotPos_5Loc;
GLfloat spotTheta_5;
GLuint spotTheta_5Loc;

glm::vec3 spotDir_6;
GLuint spotDir_6Loc;
glm::vec3 spotPos_6;
GLuint spotPos_6Loc;
GLfloat spotTheta_6;
GLuint spotTheta_6Loc;

glm::vec3 spotDir_7;
GLuint spotDir_7Loc;
glm::vec3 spotPos_7;
GLuint spotPos_7Loc;
GLfloat spotTheta_7;
GLuint spotTheta_7Loc;

glm::vec3 spotDir_8;
GLuint spotDir_8Loc;
glm::vec3 spotPos_8;
GLuint spotPos_8Loc;
GLfloat spotTheta_8;
GLuint spotTheta_8Loc;


// camera
bool carCameraToggle = true;
// free camera
glm::vec3 cameraPos = glm::vec3(1.3f, 0.387016f, 28.885);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.38f, 0.0);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
gps::Camera freeCamera(cameraPos, cameraFront, cameraUp);
GLfloat freeCameraSpeed = 0.1f;

// car camera
glm::vec3 carCameraPos = glm::vec3(1.3f, 0.387016f, 33.884f);
glm::vec3 carCameraFront = glm::vec3(-2.435f, 0.387016f, 33.884);
glm::vec3 carCameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
gps::Camera carCamera(carCameraPos, carCameraFront, carCameraUp);
GLfloat carCameraSpeed = 0.1f;

GLboolean pressedKeys[1024];

// models
GLfloat steeringAngle = 0;
GLfloat carCameraAngle = 0;
GLfloat angle;
GLfloat lightAngle;

gps::Model3D terrain;
gps::Model3D circuit;
//gps::Model3D circuitTires;
gps::Model3D pitLane;
gps::Model3D water;
gps::Model3D kerbsInside;
gps::Model3D kerbsOutside;
gps::Model3D parkedCar_body;
gps::Model3D parkedCar_front_wheels;
gps::Model3D parkedCar_rear_wheels;
gps::Model3D building;
gps::Model3D garage;
gps::Model3D fence;
gps::Model3D car_body;
gps::Model3D car_front_right_wheel;
gps::Model3D car_front_left_wheel;
gps::Model3D car_rear_wheels;
gps::Model3D steeringWheel;
gps::Model3D start_light;
gps::Model3D ferris_wheel_base;
gps::Model3D ferris_wheel_center;
gps::Model3D light_tower_0;
gps::Model3D light_tower_1;
gps::Model3D light_tower_2;
gps::Model3D light_tower_3;
gps::Model3D light_tower_4;
gps::Model3D light_tower_5;
gps::Model3D light_tower_6;
gps::Model3D light_tower_7;
gps::Model3D light_tower_8;
gps::Model3D car_prop_1;
gps::Model3D car_prop_2;
gps::Model3D car_prop_3;
gps::Model3D car_prop_4;
gps::Model3D car_prop_5;
gps::Model3D car_prop_6;
gps::Model3D car_prop_7;
gps::Model3D car_prop_8;
gps::Model3D car_prop_9;
gps::Model3D car_prop_10;
gps::Model3D car_prop_11;
gps::Model3D car_prop_12;
gps::Model3D car_parking_1;
gps::Model3D car_parking_2;
gps::Model3D building_0;
gps::Model3D building_1;
gps::Model3D building_2;

gps::Model3D skydome;

gps::Model3D trees_0;
gps::Model3D bird;

gps::Model3D screenQuad;
gps::Model3D lightCube;

gps::Car car(cameraPos + glm::vec3(0.67f, -0.387016f, -00.0021f), carCameraFront, carCameraUp);
glm::vec3 steeringWheelPos(car.getCarPosition() + glm::vec3(-0.97f, 0.287016f, 0.0f));
GLfloat carSpeed = 0.3f;
GLfloat carVelocity = 0.0f;
GLfloat wheelsSteeringAngle = 0.0f;

// shaders
gps::Shader mainGameShader;
gps::Shader depthMapShader;
gps::Shader lightShader;
gps::Shader screenQuadShader;

GLuint shadowMapFBO;
GLuint depthMapTexture;

const unsigned int SHADOW_WIDTH = 1920;
const unsigned int SHADOW_HEIGHT = 1080;

bool showDepthMap = false;

float fogDensity = 0.0f;

bool animateObjects = true;
float birdRotation = 0.0f;

GLenum glCheckError_(const char* file, int line)
{
    GLenum errorCode;
    while ((errorCode = glGetError()) != GL_NO_ERROR) {
        std::string error;
        switch (errorCode) {
        case GL_INVALID_ENUM:
            error = "INVALID_ENUM";
            break;
        case GL_INVALID_VALUE:
            error = "INVALID_VALUE";
            break;
        case GL_INVALID_OPERATION:
            error = "INVALID_OPERATION";
            break;
        case GL_STACK_OVERFLOW:
            error = "STACK_OVERFLOW";
            break;
        case GL_STACK_UNDERFLOW:
            error = "STACK_UNDERFLOW";
            break;
        case GL_OUT_OF_MEMORY:
            error = "OUT_OF_MEMORY";
            break;
        case GL_INVALID_FRAMEBUFFER_OPERATION:
            error = "INVALID_FRAMEBUFFER_OPERATION";
            break;
        }
        std::cout << error << " | " << file << " (" << line << ")" << std::endl;
    }
    return errorCode;
}
#define glCheckError() glCheckError_(__FILE__, __LINE__)

void windowResizeCallback(GLFWwindow* window, int width, int height) {
    fprintf(stdout, "Window resized! New width: %d , and height: %d\n", width, height);
    //TODO
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
    projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 1000.0f);
    projectionLoc = glGetUniformLocation(mainGameShader.shaderProgram, "projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

}

void keyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mode) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }

    if (key == GLFW_KEY_M && action == GLFW_PRESS) {
        showDepthMap = !showDepthMap;
    }

    if (key == GLFW_KEY_C && action == GLFW_PRESS) {
        carCameraToggle = !carCameraToggle;
    }

    if (key == GLFW_KEY_J && action == GLFW_PRESS) {
        lightAngle -= 5.0f;
    }

    if (key == GLFW_KEY_L && action == GLFW_PRESS) {
        lightAngle += 5.0f;
    }

    if (key == GLFW_KEY_F && action == GLFW_PRESS) {
        makeFogVisible = !makeFogVisible;
    }

    if (key == GLFW_KEY_G && action == GLFW_PRESS) {
        decreaseFog();
    }

    if (key == GLFW_KEY_1 && action == GLFW_PRESS) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }

    if (key == GLFW_KEY_2 && action == GLFW_PRESS) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }

    if (key == GLFW_KEY_3 && action == GLFW_PRESS) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
    }

    if (key == GLFW_KEY_4 && action == GLFW_PRESS) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_POLYGON_SMOOTH);
    }

    if (key == GLFW_KEY_ENTER && action == GLFW_PRESS) {
        animateObjects = !animateObjects;
    }

    if (key >= 0 && key < 1024) {
        if (action == GLFW_PRESS) {
            pressedKeys[key] = true;
        }
        else if (action == GLFW_RELEASE) {
            pressedKeys[key] = false;
        }
    }
}

void mouseCallback(GLFWwindow* window, double xpos, double ypos) {
    mouseSpeed = 0.003f;
    horizontalAngle += mouseSpeed * float(glWindowWidth / 2 - xpos);
    verticalAngle += mouseSpeed * float(glWindowHeight / 2 - ypos);

    if (carCameraToggle) {
        //carCamera.rotate(verticalAngle, -horizontalAngle);
        //view = carCamera.getViewMatrix();
    }
    else {
        freeCamera.rotate(verticalAngle, -horizontalAngle);
        view = freeCamera.getViewMatrix();
    }
    mainGameShader.useShaderProgram();
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    normalMatrix = glm::mat3(glm::inverseTranspose(view * model));
    glUniformMatrix3fv(normalMatrixLoc, 1, GL_FALSE, glm::value_ptr(normalMatrix));
    glUniform3fv(lightDirLoc, 1, glm::value_ptr(glm::inverseTranspose(glm::mat3(view)) * lightDir));

    glfwSetCursorPos(window, glWindowWidth / 2, glWindowHeight / 2);
}

void processMovement() {
    if (pressedKeys[GLFW_KEY_W]) {
        if (carCameraToggle) {
            PlaySound(TEXT("sounds/accelerate.wav"), NULL, SND_NOSTOP | SND_ASYNC | SND_FILENAME);
            carCamera.move(gps::MOVE_FORWARD, (carCameraSpeed * 3), true);
            car.move(carCamera, glm::vec3(0.0f, -0.307016f, 0.0));

            //if (carSpeed <= 250.0f) {
            carSpeed += 10.0f;
            carVelocity += 10.0f;
            //}
            //update view matrix
            view = carCamera.getViewMatrix();
        }
        else {
            freeCamera.move(gps::MOVE_FORWARD, freeCameraSpeed, false);
            //update view matrix
            view = freeCamera.getViewMatrix();
        }
        mainGameShader.useShaderProgram();
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        normalMatrix = glm::mat3(glm::inverseTranspose(view * model));
        glUniformMatrix3fv(normalMatrixLoc, 1, GL_FALSE, glm::value_ptr(normalMatrix));
        glUniform3fv(lightDirLoc, 1, glm::value_ptr(glm::inverseTranspose(glm::mat3(view)) * lightDir));
    }

    /*
    if (carVelocity >= 20 && !pressedKeys[GLFW_KEY_W]) {
        carCamera.move(gps::MOVE_FORWARD, (carCameraSpeed * carSpeed + carVelocity) / 70, true);
        car.move(carCamera, glm::vec3(0.67f, -0.387016f, -00.0021f));
        carVelocity -= 20;
        view = carCamera.getViewMatrix();
        mainGameShader.useShaderProgram();
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        normalMatrix = glm::mat3(glm::inverseTranspose(view * model));
        glUniformMatrix3fv(normalMatrixLoc, 1, GL_FALSE, glm::value_ptr(normalMatrix));
        glUniform3fv(lightDirLoc, 1, glm::value_ptr(glm::inverseTranspose(glm::mat3(view)) * lightDir));
    }*/

    if (pressedKeys[GLFW_KEY_S]) {
        if (carCameraToggle) {
            PlaySound(TEXT("sounds/downshifts.wav"), NULL, SND_NOSTOP | SND_ASYNC | SND_FILENAME);
            carCamera.move(gps::MOVE_BACKWARD, carCameraSpeed, true);
            car.move(carCamera, glm::vec3(0.67f, -0.387016f, -00.0021f));

            //if (carSpeed >= -250.0f) {
            carSpeed -= 10.0f;
            carVelocity -= 10.0f;
            //}
            //update view matrix
            view = carCamera.getViewMatrix();
        }
        else {
            freeCamera.move(gps::MOVE_BACKWARD, freeCameraSpeed, false);
            //update view matrix
            view = freeCamera.getViewMatrix();
        }
        mainGameShader.useShaderProgram();
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        normalMatrix = glm::mat3(glm::inverseTranspose(view * model));
        glUniformMatrix3fv(normalMatrixLoc, 1, GL_FALSE, glm::value_ptr(normalMatrix));
        glUniform3fv(lightDirLoc, 1, glm::value_ptr(glm::inverseTranspose(glm::mat3(view)) * lightDir));
    }

    if (pressedKeys[GLFW_KEY_A]) {
        if (carCameraToggle) {
            steeringAngle += 6.0f;
            carCameraAngle += 6.0f;
            carCamera.rotate(0, -carCameraAngle * 0.01);
            car.rotate(0, -steeringAngle * 0.01);

            if (wheelsSteeringAngle <= 25) {
                wheelsSteeringAngle += 4.0f;
            }

            view = carCamera.getViewMatrix();

        }
        else {
            freeCamera.move(gps::MOVE_LEFT, freeCameraSpeed, true);
            //update view matrix
            view = freeCamera.getViewMatrix();
        }
        mainGameShader.useShaderProgram();
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        normalMatrix = glm::mat3(glm::inverseTranspose(view * model));
        glUniformMatrix3fv(normalMatrixLoc, 1, GL_FALSE, glm::value_ptr(normalMatrix));
        glUniform3fv(lightDirLoc, 1, glm::value_ptr(glm::inverseTranspose(glm::mat3(view)) * lightDir));
    }

    if (pressedKeys[GLFW_KEY_D]) {
        if (carCameraToggle) {
            steeringAngle -= 6.0f;
            carCameraAngle -= 6.0f;
            carCamera.rotate(0, -carCameraAngle * 0.01);
            car.rotate(0, -steeringAngle * 0.01);

            if (wheelsSteeringAngle >= -25) {
                wheelsSteeringAngle -= 4.0f;
            }

            view = carCamera.getViewMatrix();
        }
        else {
            freeCamera.move(gps::MOVE_RIGHT, freeCameraSpeed, false);
            //update view matrix
            view = freeCamera.getViewMatrix();
        }
        mainGameShader.useShaderProgram();
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        normalMatrix = glm::mat3(glm::inverseTranspose(view * model));
        glUniformMatrix3fv(normalMatrixLoc, 1, GL_FALSE, glm::value_ptr(normalMatrix));
        glUniform3fv(lightDirLoc, 1, glm::value_ptr(glm::inverseTranspose(glm::mat3(view)) * lightDir));
    }

    if (pressedKeys[GLFW_KEY_X]) {
        if (carCameraToggle) {
            carCamera.move(gps::MOVE_UP, carCameraSpeed, true);
            //update view matrix
            view = carCamera.getViewMatrix();
        }
        else {
            freeCamera.move(gps::MOVE_UP, freeCameraSpeed, false);
            //update view matrix
            view = freeCamera.getViewMatrix();
        }
        mainGameShader.useShaderProgram();
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        normalMatrix = glm::mat3(glm::inverseTranspose(view * model));
        glUniformMatrix3fv(normalMatrixLoc, 1, GL_FALSE, glm::value_ptr(normalMatrix));
        glUniform3fv(lightDirLoc, 1, glm::value_ptr(glm::inverseTranspose(glm::mat3(view)) * lightDir));
    }

    if (pressedKeys[GLFW_KEY_Z]) {
        if (carCameraToggle) {
            carCamera.move(gps::MOVE_DOWN, carCameraSpeed, true);
            //update view matrix
            view = carCamera.getViewMatrix();
        }
        else {
            freeCamera.move(gps::MOVE_DOWN, freeCameraSpeed, false);
            //update view matrix
            view = freeCamera.getViewMatrix();
        }
        mainGameShader.useShaderProgram();
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        normalMatrix = glm::mat3(glm::inverseTranspose(view * model));
        glUniformMatrix3fv(normalMatrixLoc, 1, GL_FALSE, glm::value_ptr(normalMatrix));
        glUniform3fv(lightDirLoc, 1, glm::value_ptr(glm::inverseTranspose(glm::mat3(view)) * lightDir));
    }

    if (pressedKeys[GLFW_KEY_Q]) {
        carCameraAngle += 6.0f;
        carCamera.rotate(0, -carCameraAngle * 0.01);
        view = carCamera.getViewMatrix();
        mainGameShader.useShaderProgram();
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        normalMatrix = glm::mat3(glm::inverseTranspose(view * model));
        glUniformMatrix3fv(normalMatrixLoc, 1, GL_FALSE, glm::value_ptr(normalMatrix));
        glUniform3fv(lightDirLoc, 1, glm::value_ptr(glm::inverseTranspose(glm::mat3(view)) * lightDir));
    }

    if (pressedKeys[GLFW_KEY_E]) {
        carCameraAngle -= 6.0f;
        carCamera.rotate(0, -carCameraAngle * 0.01);
        view = carCamera.getViewMatrix();
        mainGameShader.useShaderProgram();
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        normalMatrix = glm::mat3(glm::inverseTranspose(view * model));
        glUniformMatrix3fv(normalMatrixLoc, 1, GL_FALSE, glm::value_ptr(normalMatrix));
        glUniform3fv(lightDirLoc, 1, glm::value_ptr(glm::inverseTranspose(glm::mat3(view)) * lightDir));
    }

    if (animateObjects) {
        birdRotation += 0.4f;
    }
}

void increaseFog() {
    if (fogDensity >= 0.03f) {
        makeFogVisible = false;
    }

    mainGameShader.useShaderProgram();
    fogDensity += 0.00009;
    fogDensityLoc = glGetUniformLocation(mainGameShader.shaderProgram, "fogDensity");
    glUniform1f(fogDensityLoc, fogDensity);
}

void decreaseFog() {
    mainGameShader.useShaderProgram();
    fogDensity -= 0.00018;
    fogDensityLoc = glGetUniformLocation(mainGameShader.shaderProgram, "fogDensity");
    glUniform1f(fogDensityLoc, fogDensity);
}

void initOpenGLWindow() {
    myWindow.Create(glWindowWidth, glWindowHeight, "OpenGL Formula 1");
}

void setWindowCallbacks() {
    glfwSetWindowSizeCallback(myWindow.getWindow(), windowResizeCallback);
    glfwSetKeyCallback(myWindow.getWindow(), keyboardCallback);
    glfwSetCursorPosCallback(myWindow.getWindow(), mouseCallback);
}

void initOpenGLState() {
    glClearColor(0.7f, 0.7f, 0.7f, 1.0f);
    glViewport(0, 0, myWindow.getWindowDimensions().width, myWindow.getWindowDimensions().height);
    glEnable(GL_FRAMEBUFFER_SRGB);
    glEnable(GL_DEPTH_TEST); // enable depth-testing
    glDepthFunc(GL_LESS); // depth-testing interprets a smaller value as "closer"
    glEnable(GL_CULL_FACE); // cull face
    glCullFace(GL_BACK); // cull back face
    glFrontFace(GL_CCW); // GL_CCW for counter clock-wise
}

void initModels() {
    // Env objects
    terrain.LoadModel("models/ground/ground.obj");
    circuit.LoadModel("models/circuit/circuit.obj");
    //circuitTires.LoadModel("models/circuit/tires.obj");
    pitLane.LoadModel("models/pit_lane/pit_lane.obj");
    water.LoadModel("models/water/water.obj");
    kerbsInside.LoadModel("models/kerbs/kerbs_inside.obj");
    kerbsOutside.LoadModel("models/kerbs/kerbs_outside.obj");
    building.LoadModel("models/center_building/center_building_final.obj");
    garage.LoadModel("models/garage/garages.obj");
    fence.LoadModel("models/fence/fence.obj");
    ferris_wheel_base.LoadModel("models/ferris_wheel/ferris_base.obj");
    ferris_wheel_center.LoadModel("models/ferris_wheel/ferris_torus.obj");
    car_prop_1.LoadModel("models/car_parking/car_1.obj");
    car_prop_2.LoadModel("models/car_parking/car_2.obj");
    car_prop_3.LoadModel("models/car_parking/car_3.obj");
    car_prop_4.LoadModel("models/car_parking/car_4.obj");
    car_prop_5.LoadModel("models/car_parking/car_5.obj");
    car_prop_6.LoadModel("models/car_parking/car_6.obj");
    car_prop_7.LoadModel("models/car_parking/car_7.obj");
    car_prop_8.LoadModel("models/car_parking/car_8.obj");
    car_prop_9.LoadModel("models/car_parking/car_9.obj");
    car_prop_10.LoadModel("models/car_parking/car_10.obj");
    car_prop_11.LoadModel("models/car_parking/car_11.obj");
    car_prop_12.LoadModel("models/car_parking/car_12.obj");
    car_parking_1.LoadModel("models/car_parking/parking_1.obj");
    car_parking_2.LoadModel("models/car_parking/parking_2.obj");
    building_0.LoadModel("models/buildings/building_0.obj");
    building_1.LoadModel("models/buildings/building_1.obj");
    building_2.LoadModel("models/buildings/building_2.obj");

    // Prop car objects
    parkedCar_body.LoadModel("models/car_static/static_car_body.obj");
    parkedCar_front_wheels.LoadModel("models/car_static/static_car_front_wheels.obj");
    parkedCar_rear_wheels.LoadModel("models/car_static/static_car_rear_wheels.obj");

    // Drivable car objects
    car_body.LoadModel("models/f1_car/car_body_center.obj");
    car_front_right_wheel.LoadModel("models/f1_car/front_right_wheel_final.obj");
    car_front_left_wheel.LoadModel("models/f1_car/front_left_wheel_final.obj");
    car_rear_wheels.LoadModel("models/f1_car/rear_wheels_final.obj");
    steeringWheel.LoadModel("models/steering_wheel/steering_wheel_final.obj");

    // World light and background objects
    light_tower_0.LoadModel("models/light_tower/light_tower_0.obj");
    light_tower_1.LoadModel("models/light_tower/light_tower_1.obj");
    light_tower_2.LoadModel("models/light_tower/light_tower_2.obj");
    light_tower_3.LoadModel("models/light_tower/light_tower_3.obj");
    light_tower_4.LoadModel("models/light_tower/light_tower_4.obj");
    light_tower_5.LoadModel("models/light_tower/light_tower_5.obj");
    light_tower_6.LoadModel("models/light_tower/light_tower_6.obj");
    light_tower_7.LoadModel("models/light_tower/light_tower_7.obj");
    light_tower_8.LoadModel("models/light_tower/light_tower_8.obj");
    start_light.LoadModel("models/skydome/skydome.obj");

    skydome.LoadModel("models/start_light/start_light.obj");

    trees_0.LoadModel("models/trees/trees_0.obj");

    screenQuad.LoadModel("models/quad/quad.obj");
    lightCube.LoadModel("models/cube/cube.obj");
}

void initShaders() {
    mainGameShader.loadShader("shaders/shaderStart.vert", "shaders/shaderStart.frag");
    mainGameShader.useShaderProgram();
    lightShader.loadShader("shaders/lightCube.vert", "shaders/lightCube.frag");
    lightShader.useShaderProgram();
    screenQuadShader.loadShader("shaders/screenQuad.vert", "shaders/screenQuad.frag");
    screenQuadShader.useShaderProgram();
    depthMapShader.loadShader("shaders/simpleDepthMap.vert", "shaders/simpleDepthMap.frag");
    depthMapShader.useShaderProgram();
}

void initUniforms() {
    mainGameShader.useShaderProgram();

    modelLoc = glGetUniformLocation(mainGameShader.shaderProgram, "model");
    normalMatrixLoc = glGetUniformLocation(mainGameShader.shaderProgram, "normalMatrix");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

    // get view matrix for current camera
    if (carCameraToggle) {
        view = carCamera.getViewMatrix();
    }
    else {
        view = freeCamera.getViewMatrix();
    }
    viewLoc = glGetUniformLocation(mainGameShader.shaderProgram, "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

    normalMatrix = glm::mat3(glm::inverseTranspose(view * model));
    normalMatrixLoc = glGetUniformLocation(mainGameShader.shaderProgram, "normalMatrix");
    glUniformMatrix3fv(normalMatrixLoc, 1, GL_FALSE, glm::value_ptr(normalMatrix));

    // Main light
    // create projection matrix

    projection = glm::perspective(glm::radians(45.0f), (float)myWindow.getWindowDimensions().width / (float)myWindow.getWindowDimensions().height, 0.1f, 300.0f);
    projectionLoc = glGetUniformLocation(mainGameShader.shaderProgram, "projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

    //set the light direction (direction towards the light)
    lightDir = glm::vec3(9.44158f, 32.7871f, -15.1525f);
    lightRotation = glm::rotate(glm::mat4(1.0f), glm::radians(lightAngle), glm::vec3(0.0f, 1.0f, 0.0f));
    lightDirLoc = glGetUniformLocation(mainGameShader.shaderProgram, "lightDir");
    glUniform3fv(lightDirLoc, 1, glm::value_ptr(lightDir));

    //set light color
    lightColor = glm::vec3(1.0f, 1.0f, 1.0f); //white light
    lightColorLoc = glGetUniformLocation(mainGameShader.shaderProgram, "lightColor");
    glUniform3fv(lightColorLoc, 1, glm::value_ptr(lightColor));

    lightPosEye = glm::vec3(9.44158f, 32.7871f, -15.1525f);
    lightPosEyeLoc = glGetUniformLocation(mainGameShader.shaderProgram, "lPosEye");
    glUniform3fv(lightPosEyeLoc, 1, glm::value_ptr(lightPosEye));

    /*
    // Spot lights
    //set the light direction (direction towards the light)
    spotDir_0 = glm::vec3(2.91863f, 0.1f, 24.8352f);
    spotDir_0Loc = glGetUniformLocation(mainGameShader.shaderProgram, "spot.direction");
    glUniform3fv(spotDir_0Loc, 1, glm::value_ptr(spotDir_0));

    spotPos_0 = glm::vec3(2.91863f, 5.08701f, 27.8352f);
    spotPos_0Loc = glGetUniformLocation(mainGameShader.shaderProgram, "spot.position");
    glUniform3fv(spotPos_0Loc, 1, glm::value_ptr(spotPos_0));

    spotTheta_0 = glm::cos(glm::radians(12.5f));
    spotTheta_0Loc = glGetUniformLocation(mainGameShader.shaderProgram, "spot.cutoff");
    glUniform3fv(spotPos_0Loc, 1, glm::value_ptr(spotPos_0));
    */



    lightShader.useShaderProgram();
    glUniformMatrix4fv(glGetUniformLocation(lightShader.shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));



}

void initFBOs() {
    //generate FBO ID
    glGenFramebuffers(1, &shadowMapFBO);

    //create depth texture for FBO
    glGenTextures(1, &depthMapTexture);
    glBindTexture(GL_TEXTURE_2D, depthMapTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    float borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    //attach texture to FBO
    glBindFramebuffer(GL_FRAMEBUFFER, shadowMapFBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMapTexture, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void driveCar(gps::Shader shader, bool depthPass) {
    // Body
    model = glm::mat4(1.0f);
    model = glm::translate(model, carCamera.getCameraPosition());
    glUniformMatrix4fv(glGetUniformLocation(shader.shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
    model = glm::translate(model, glm::vec3(0.0f, -0.307016f, 0.0));
    glUniformMatrix4fv(glGetUniformLocation(shader.shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
    model = glm::rotate(model, glm::radians(steeringAngle / 1.745f), glm::vec3(0, 1, 0));
    glUniformMatrix4fv(glGetUniformLocation(shader.shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
    // do not send the normal matrix if we are rendering in the depth map
    if (!depthPass) {
        normalMatrix = glm::mat3(glm::inverseTranspose(view * model));
        glUniformMatrix3fv(normalMatrixLoc, 1, GL_FALSE, glm::value_ptr(normalMatrix));
    }
    car_body.Draw(mainGameShader);


    // Front right wheel
    model = glm::mat4(1.0f);
    model = glm::translate(model, car.getCarPosition());
    glUniformMatrix4fv(glGetUniformLocation(shader.shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
    model = glm::rotate(model, glm::radians(steeringAngle / 1.745f), glm::vec3(0, 1, 0));
    glUniformMatrix4fv(glGetUniformLocation(shader.shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
    model = glm::translate(model, glm::vec3(-0.90f, 0.15f, -0.7f));
    glUniformMatrix4fv(glGetUniformLocation(shader.shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
    model = glm::rotate(model, glm::radians(wheelsSteeringAngle), glm::vec3(0, 1, 0));
    glUniformMatrix4fv(glGetUniformLocation(shader.shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
    model = glm::rotate(model, glm::radians(carSpeed * 2), glm::vec3(0, 0, 1));
    glUniformMatrix4fv(glGetUniformLocation(shader.shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
    // do not send the normal matrix if we are rendering in the depth map
    if (!depthPass) {
        normalMatrix = glm::mat3(glm::inverseTranspose(view * model));
        glUniformMatrix3fv(normalMatrixLoc, 1, GL_FALSE, glm::value_ptr(normalMatrix));
    }
    car_front_right_wheel.Draw(mainGameShader);


    // Front right wheel
    model = glm::mat4(1.0f);
    model = glm::translate(model, car.getCarPosition());
    glUniformMatrix4fv(glGetUniformLocation(shader.shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
    model = glm::rotate(model, glm::radians(steeringAngle / 1.745f), glm::vec3(0, 1, 0));
    glUniformMatrix4fv(glGetUniformLocation(shader.shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
    model = glm::translate(model, glm::vec3(-0.90f, 0.15f, 0.7f));
    glUniformMatrix4fv(glGetUniformLocation(shader.shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
    model = glm::rotate(model, glm::radians(wheelsSteeringAngle), glm::vec3(0, 1, 0));
    glUniformMatrix4fv(glGetUniformLocation(shader.shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
    model = glm::rotate(model, glm::radians(carSpeed * 2), glm::vec3(0, 0, 1));
    glUniformMatrix4fv(glGetUniformLocation(shader.shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
    // do not send the normal matrix if we are rendering in the depth map
    if (!depthPass) {
        normalMatrix = glm::mat3(glm::inverseTranspose(view * model));
        glUniformMatrix3fv(normalMatrixLoc, 1, GL_FALSE, glm::value_ptr(normalMatrix));
    }
    car_front_left_wheel.Draw(mainGameShader);


    // Rear wheels
    model = glm::mat4(1.0f);
    model = glm::translate(model, car.getCarPosition());
    glUniformMatrix4fv(glGetUniformLocation(shader.shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
    model = glm::rotate(model, glm::radians(steeringAngle / 1.745f), glm::vec3(0, 1, 0));
    glUniformMatrix4fv(glGetUniformLocation(shader.shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
    model = glm::translate(model, glm::vec3(0.75f, 0.12f, 0.0f));
    glUniformMatrix4fv(glGetUniformLocation(shader.shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
    model = glm::rotate(model, glm::radians(carSpeed * 2), glm::vec3(0, 0, 1));
    glUniformMatrix4fv(glGetUniformLocation(shader.shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
    // do not send the normal matrix if we are rendering in the depth map
    if (!depthPass) {
        normalMatrix = glm::mat3(glm::inverseTranspose(view * model));
        glUniformMatrix3fv(normalMatrixLoc, 1, GL_FALSE, glm::value_ptr(normalMatrix));
    }
    car_rear_wheels.Draw(mainGameShader);


    // Steering wheel
    model = glm::mat4(1.0f);
    model = glm::translate(model, car.getCarPosition());
    glUniformMatrix4fv(glGetUniformLocation(shader.shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
    model = glm::rotate(model, glm::radians(steeringAngle / 1.745f), glm::vec3(0, 1, 0));
    glUniformMatrix4fv(glGetUniformLocation(shader.shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
    model = glm::translate(model, glm::vec3(-0.21f, 0.207016f, 0.0f));
    glUniformMatrix4fv(glGetUniformLocation(shader.shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
    model = glm::rotate(model, glm::radians(steeringAngle), glm::vec3(1, 0, 0));
    glUniformMatrix4fv(glGetUniformLocation(shader.shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
    // do not send the normal matrix if we are rendering in the depth map
    if (!depthPass) {
        normalMatrix = glm::mat3(glm::inverseTranspose(view * model));
        glUniformMatrix3fv(normalMatrixLoc, 1, GL_FALSE, glm::value_ptr(normalMatrix));
    }
    steeringWheel.Draw(mainGameShader);
}

void drawObjects(gps::Shader shader, bool depthPass) {

    shader.useShaderProgram();

    if (makeFogVisible == true) {
        increaseFog();
    }

    // Terrain
    model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
    glUniformMatrix4fv(glGetUniformLocation(shader.shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
    // do not send the normal matrix if we are rendering in the depth map
    if (!depthPass) {
        normalMatrix = glm::mat3(glm::inverseTranspose(view * model));
        glUniformMatrix3fv(normalMatrixLoc, 1, GL_FALSE, glm::value_ptr(normalMatrix));
    }
    terrain.Draw(shader);

    model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    if (!depthPass) {
        normalMatrix = glm::mat3(glm::inverseTranspose(view * model));
        glUniformMatrix3fv(normalMatrixLoc, 1, GL_FALSE, glm::value_ptr(normalMatrix));
    }
    water.Draw(shader);

    // Circuit
    model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
    glUniformMatrix4fv(glGetUniformLocation(shader.shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
    // do not send the normal matrix if we are rendering in the depth map
    if (!depthPass) {
        normalMatrix = glm::mat3(glm::inverseTranspose(view * model));
        glUniformMatrix3fv(normalMatrixLoc, 1, GL_FALSE, glm::value_ptr(normalMatrix));
    }
    circuit.Draw(shader);

    /*
    model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
    glUniformMatrix4fv(glGetUniformLocation(shader.shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
    // do not send the normal matrix if we are rendering in the depth map
    if (!depthPass) {
        normalMatrix = glm::mat3(glm::inverseTranspose(view * model));
        glUniformMatrix3fv(normalMatrixLoc, 1, GL_FALSE, glm::value_ptr(normalMatrix));
    }
    circuitTires.Draw(shader);
    */
    // Pit Lane
    model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
    glUniformMatrix4fv(glGetUniformLocation(shader.shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
    // do not send the normal matrix if we are rendering in the depth map
    if (!depthPass) {
        normalMatrix = glm::mat3(glm::inverseTranspose(view * model));
        glUniformMatrix3fv(normalMatrixLoc, 1, GL_FALSE, glm::value_ptr(normalMatrix));
    }
    pitLane.Draw(shader);

    // Kerbs
    model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
    glUniformMatrix4fv(glGetUniformLocation(shader.shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
    // do not send the normal matrix if we are rendering in the depth map
    if (!depthPass) {
        normalMatrix = glm::mat3(glm::inverseTranspose(view * model));
        glUniformMatrix3fv(normalMatrixLoc, 1, GL_FALSE, glm::value_ptr(normalMatrix));
    }
    kerbsInside.Draw(shader);

    model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
    glUniformMatrix4fv(glGetUniformLocation(shader.shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
    // do not send the normal matrix if we are rendering in the depth map
    if (!depthPass) {
        normalMatrix = glm::mat3(glm::inverseTranspose(view * model));
        glUniformMatrix3fv(normalMatrixLoc, 1, GL_FALSE, glm::value_ptr(normalMatrix));
    }
    kerbsOutside.Draw(shader);

    // Parked car
    model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
    glUniformMatrix4fv(glGetUniformLocation(shader.shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
    // do not send the normal matrix if we are rendering in the depth map
    if (!depthPass) {
        normalMatrix = glm::mat3(glm::inverseTranspose(view * model));
        glUniformMatrix3fv(normalMatrixLoc, 1, GL_FALSE, glm::value_ptr(normalMatrix));
    }
    parkedCar_body.Draw(shader);

    model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
    glUniformMatrix4fv(glGetUniformLocation(shader.shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
    // do not send the normal matrix if we are rendering in the depth map
    if (!depthPass) {
        normalMatrix = glm::mat3(glm::inverseTranspose(view * model));
        glUniformMatrix3fv(normalMatrixLoc, 1, GL_FALSE, glm::value_ptr(normalMatrix));
    }
    parkedCar_front_wheels.Draw(shader);

    model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
    glUniformMatrix4fv(glGetUniformLocation(shader.shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
    // do not send the normal matrix if we are rendering in the depth map
    if (!depthPass) {
        normalMatrix = glm::mat3(glm::inverseTranspose(view * model));
        glUniformMatrix3fv(normalMatrixLoc, 1, GL_FALSE, glm::value_ptr(normalMatrix));
    }
    parkedCar_rear_wheels.Draw(shader);

    // Center building
    model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
    glUniformMatrix4fv(glGetUniformLocation(shader.shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
    // do not send the normal matrix if we are rendering in the depth map
    if (!depthPass) {
        normalMatrix = glm::mat3(glm::inverseTranspose(view * model));
        glUniformMatrix3fv(normalMatrixLoc, 1, GL_FALSE, glm::value_ptr(normalMatrix));
    }
    building.Draw(shader);

    // Ferris wheel
    model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
    glUniformMatrix4fv(glGetUniformLocation(shader.shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
    // do not send the normal matrix if we are rendering in the depth map
    if (!depthPass) {
        normalMatrix = glm::mat3(glm::inverseTranspose(view * model));
        glUniformMatrix3fv(normalMatrixLoc, 1, GL_FALSE, glm::value_ptr(normalMatrix));
    }
    ferris_wheel_base.Draw(shader);

    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(14.0f, 9.0f, -10.0f));
    glUniformMatrix4fv(glGetUniformLocation(shader.shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
    model = glm::rotate(model, glm::radians(-45.0f), glm::vec3(0, 1, 0));
    glUniformMatrix4fv(glGetUniformLocation(shader.shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
    model = glm::rotate(model, glm::radians(birdRotation), glm::vec3(0, 0, 1));
    glUniformMatrix4fv(glGetUniformLocation(shader.shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
    model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0, 1, 0));
    glUniformMatrix4fv(glGetUniformLocation(shader.shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
    // do not send the normal matrix if we are rendering in the depth map
    if (!depthPass) {
        normalMatrix = glm::mat3(glm::inverseTranspose(view * model));
        glUniformMatrix3fv(normalMatrixLoc, 1, GL_FALSE, glm::value_ptr(normalMatrix));
    }
    ferris_wheel_center.Draw(shader);

    // Garage
    model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
    glUniformMatrix4fv(glGetUniformLocation(shader.shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
    // do not send the normal matrix if we are rendering in the depth map
    if (!depthPass) {
        normalMatrix = glm::mat3(glm::inverseTranspose(view * model));
        glUniformMatrix3fv(normalMatrixLoc, 1, GL_FALSE, glm::value_ptr(normalMatrix));
    }
    garage.Draw(shader);

    // Residential buildings
    model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
    glUniformMatrix4fv(glGetUniformLocation(shader.shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
    // do not send the normal matrix if we are rendering in the depth map
    if (!depthPass) {
        normalMatrix = glm::mat3(glm::inverseTranspose(view * model));
        glUniformMatrix3fv(normalMatrixLoc, 1, GL_FALSE, glm::value_ptr(normalMatrix));
    }
    building_0.Draw(shader);

    model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
    glUniformMatrix4fv(glGetUniformLocation(shader.shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
    // do not send the normal matrix if we are rendering in the depth map
    if (!depthPass) {
        normalMatrix = glm::mat3(glm::inverseTranspose(view * model));
        glUniformMatrix3fv(normalMatrixLoc, 1, GL_FALSE, glm::value_ptr(normalMatrix));
    }
    building_1.Draw(shader);

    model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
    glUniformMatrix4fv(glGetUniformLocation(shader.shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
    // do not send the normal matrix if we are rendering in the depth map
    if (!depthPass) {
        normalMatrix = glm::mat3(glm::inverseTranspose(view * model));
        glUniformMatrix3fv(normalMatrixLoc, 1, GL_FALSE, glm::value_ptr(normalMatrix));
    }
    building_2.Draw(shader);

    // Fence
    model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
    glUniformMatrix4fv(glGetUniformLocation(shader.shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
    // do not send the normal matrix if we are rendering in the depth map
    if (!depthPass) {
        normalMatrix = glm::mat3(glm::inverseTranspose(view * model));
        glUniformMatrix3fv(normalMatrixLoc, 1, GL_FALSE, glm::value_ptr(normalMatrix));
    }
    fence.Draw(shader);

    // F1 car
    driveCar(shader, depthPass);

    // Light towers
    model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
    glUniformMatrix4fv(glGetUniformLocation(shader.shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
    // do not send the normal matrix if we are rendering in the depth map
    if (!depthPass) {
        normalMatrix = glm::mat3(glm::inverseTranspose(view * model));
        glUniformMatrix3fv(normalMatrixLoc, 1, GL_FALSE, glm::value_ptr(normalMatrix));
    }
    light_tower_0.Draw(shader);

    model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
    glUniformMatrix4fv(glGetUniformLocation(shader.shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
    // do not send the normal matrix if we are rendering in the depth map
    if (!depthPass) {
        normalMatrix = glm::mat3(glm::inverseTranspose(view * model));
        glUniformMatrix3fv(normalMatrixLoc, 1, GL_FALSE, glm::value_ptr(normalMatrix));
    }
    light_tower_1.Draw(shader);

    model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
    glUniformMatrix4fv(glGetUniformLocation(shader.shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
    // do not send the normal matrix if we are rendering in the depth map
    if (!depthPass) {
        normalMatrix = glm::mat3(glm::inverseTranspose(view * model));
        glUniformMatrix3fv(normalMatrixLoc, 1, GL_FALSE, glm::value_ptr(normalMatrix));
    }
    light_tower_2.Draw(shader);

    model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
    glUniformMatrix4fv(glGetUniformLocation(shader.shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
    // do not send the normal matrix if we are rendering in the depth map
    if (!depthPass) {
        normalMatrix = glm::mat3(glm::inverseTranspose(view * model));
        glUniformMatrix3fv(normalMatrixLoc, 1, GL_FALSE, glm::value_ptr(normalMatrix));
    }
    light_tower_3.Draw(shader);

    model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
    glUniformMatrix4fv(glGetUniformLocation(shader.shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
    // do not send the normal matrix if we are rendering in the depth map
    if (!depthPass) {
        normalMatrix = glm::mat3(glm::inverseTranspose(view * model));
        glUniformMatrix3fv(normalMatrixLoc, 1, GL_FALSE, glm::value_ptr(normalMatrix));
    }
    light_tower_4.Draw(shader);

    model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
    glUniformMatrix4fv(glGetUniformLocation(shader.shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
    // do not send the normal matrix if we are rendering in the depth map
    if (!depthPass) {
        normalMatrix = glm::mat3(glm::inverseTranspose(view * model));
        glUniformMatrix3fv(normalMatrixLoc, 1, GL_FALSE, glm::value_ptr(normalMatrix));
    }
    light_tower_5.Draw(shader);

    model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
    glUniformMatrix4fv(glGetUniformLocation(shader.shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
    // do not send the normal matrix if we are rendering in the depth map
    if (!depthPass) {
        normalMatrix = glm::mat3(glm::inverseTranspose(view * model));
        glUniformMatrix3fv(normalMatrixLoc, 1, GL_FALSE, glm::value_ptr(normalMatrix));
    }
    light_tower_6.Draw(shader);

    model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
    glUniformMatrix4fv(glGetUniformLocation(shader.shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
    // do not send the normal matrix if we are rendering in the depth map
    if (!depthPass) {
        normalMatrix = glm::mat3(glm::inverseTranspose(view * model));
        glUniformMatrix3fv(normalMatrixLoc, 1, GL_FALSE, glm::value_ptr(normalMatrix));
    }
    light_tower_7.Draw(shader);

    model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
    glUniformMatrix4fv(glGetUniformLocation(shader.shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
    // do not send the normal matrix if we are rendering in the depth map
    if (!depthPass) {
        normalMatrix = glm::mat3(glm::inverseTranspose(view * model));
        glUniformMatrix3fv(normalMatrixLoc, 1, GL_FALSE, glm::value_ptr(normalMatrix));
    }
    light_tower_8.Draw(shader);

    // Start light
    model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
    glUniformMatrix4fv(glGetUniformLocation(shader.shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
    // do not send the normal matrix if we are rendering in the depth map
    if (!depthPass) {
        normalMatrix = glm::mat3(glm::inverseTranspose(view * model));
        glUniformMatrix3fv(normalMatrixLoc, 1, GL_FALSE, glm::value_ptr(normalMatrix));
    }
    start_light.Draw(shader);

    // Skydome
    model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
    glUniformMatrix4fv(glGetUniformLocation(shader.shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
    // do not send the normal matrix if we are rendering in the depth map
    if (!depthPass) {
        normalMatrix = glm::mat3(glm::inverseTranspose(view * model));
        glUniformMatrix3fv(normalMatrixLoc, 1, GL_FALSE, glm::value_ptr(normalMatrix));
    }
    skydome.Draw(mainGameShader);

    // Parking
    model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
    glUniformMatrix4fv(glGetUniformLocation(shader.shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
    // do not send the normal matrix if we are rendering in the depth map
    if (!depthPass) {
        normalMatrix = glm::mat3(glm::inverseTranspose(view * model));
        glUniformMatrix3fv(normalMatrixLoc, 1, GL_FALSE, glm::value_ptr(normalMatrix));
    }
    car_prop_1.Draw(shader);

    model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
    glUniformMatrix4fv(glGetUniformLocation(shader.shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
    // do not send the normal matrix if we are rendering in the depth map
    if (!depthPass) {
        normalMatrix = glm::mat3(glm::inverseTranspose(view * model));
        glUniformMatrix3fv(normalMatrixLoc, 1, GL_FALSE, glm::value_ptr(normalMatrix));
    }
    car_prop_2.Draw(shader);

    model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
    glUniformMatrix4fv(glGetUniformLocation(shader.shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
    // do not send the normal matrix if we are rendering in the depth map
    if (!depthPass) {
        normalMatrix = glm::mat3(glm::inverseTranspose(view * model));
        glUniformMatrix3fv(normalMatrixLoc, 1, GL_FALSE, glm::value_ptr(normalMatrix));
    }
    car_prop_3.Draw(shader);

    model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
    glUniformMatrix4fv(glGetUniformLocation(shader.shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
    // do not send the normal matrix if we are rendering in the depth map
    if (!depthPass) {
        normalMatrix = glm::mat3(glm::inverseTranspose(view * model));
        glUniformMatrix3fv(normalMatrixLoc, 1, GL_FALSE, glm::value_ptr(normalMatrix));
    }
    car_prop_4.Draw(shader);

    model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
    glUniformMatrix4fv(glGetUniformLocation(shader.shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
    // do not send the normal matrix if we are rendering in the depth map
    if (!depthPass) {
        normalMatrix = glm::mat3(glm::inverseTranspose(view * model));
        glUniformMatrix3fv(normalMatrixLoc, 1, GL_FALSE, glm::value_ptr(normalMatrix));
    }
    car_prop_5.Draw(shader);

    model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
    glUniformMatrix4fv(glGetUniformLocation(shader.shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
    // do not send the normal matrix if we are rendering in the depth map
    if (!depthPass) {
        normalMatrix = glm::mat3(glm::inverseTranspose(view * model));
        glUniformMatrix3fv(normalMatrixLoc, 1, GL_FALSE, glm::value_ptr(normalMatrix));
    }
    car_prop_6.Draw(shader);

    model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
    glUniformMatrix4fv(glGetUniformLocation(shader.shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
    // do not send the normal matrix if we are rendering in the depth map
    if (!depthPass) {
        normalMatrix = glm::mat3(glm::inverseTranspose(view * model));
        glUniformMatrix3fv(normalMatrixLoc, 1, GL_FALSE, glm::value_ptr(normalMatrix));
    }
    car_prop_7.Draw(shader);

    model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
    glUniformMatrix4fv(glGetUniformLocation(shader.shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
    // do not send the normal matrix if we are rendering in the depth map
    if (!depthPass) {
        normalMatrix = glm::mat3(glm::inverseTranspose(view * model));
        glUniformMatrix3fv(normalMatrixLoc, 1, GL_FALSE, glm::value_ptr(normalMatrix));
    }
    car_prop_8.Draw(shader);

    model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
    glUniformMatrix4fv(glGetUniformLocation(shader.shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
    // do not send the normal matrix if we are rendering in the depth map
    if (!depthPass) {
        normalMatrix = glm::mat3(glm::inverseTranspose(view * model));
        glUniformMatrix3fv(normalMatrixLoc, 1, GL_FALSE, glm::value_ptr(normalMatrix));
    }
    car_prop_9.Draw(shader);

    model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
    glUniformMatrix4fv(glGetUniformLocation(shader.shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
    // do not send the normal matrix if we are rendering in the depth map
    if (!depthPass) {
        normalMatrix = glm::mat3(glm::inverseTranspose(view * model));
        glUniformMatrix3fv(normalMatrixLoc, 1, GL_FALSE, glm::value_ptr(normalMatrix));
    }
    car_prop_10.Draw(shader);

    model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
    glUniformMatrix4fv(glGetUniformLocation(shader.shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
    // do not send the normal matrix if we are rendering in the depth map
    if (!depthPass) {
        normalMatrix = glm::mat3(glm::inverseTranspose(view * model));
        glUniformMatrix3fv(normalMatrixLoc, 1, GL_FALSE, glm::value_ptr(normalMatrix));
    }
    car_prop_11.Draw(shader);

    model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
    glUniformMatrix4fv(glGetUniformLocation(shader.shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
    // do not send the normal matrix if we are rendering in the depth map
    if (!depthPass) {
        normalMatrix = glm::mat3(glm::inverseTranspose(view * model));
        glUniformMatrix3fv(normalMatrixLoc, 1, GL_FALSE, glm::value_ptr(normalMatrix));
    }
    car_prop_12.Draw(shader);

    model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
    glUniformMatrix4fv(glGetUniformLocation(shader.shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
    // do not send the normal matrix if we are rendering in the depth map
    if (!depthPass) {
        normalMatrix = glm::mat3(glm::inverseTranspose(view * model));
        glUniformMatrix3fv(normalMatrixLoc, 1, GL_FALSE, glm::value_ptr(normalMatrix));
    }
    car_parking_1.Draw(shader);

    model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
    glUniformMatrix4fv(glGetUniformLocation(shader.shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
    // do not send the normal matrix if we are rendering in the depth map
    if (!depthPass) {
        normalMatrix = glm::mat3(glm::inverseTranspose(view * model));
        glUniformMatrix3fv(normalMatrixLoc, 1, GL_FALSE, glm::value_ptr(normalMatrix));
    }
    car_parking_2.Draw(shader);

    // Trees
    model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::scale(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    if (!depthPass) {
        normalMatrix = glm::mat3(glm::inverseTranspose(view * model));
        glUniformMatrix3fv(normalMatrixLoc, 1, GL_FALSE, glm::value_ptr(normalMatrix));
    }
    trees_0.Draw(shader);


}

glm::mat4 computeLightSpaceTrMatrix() {
    glm::mat4 lightView = glm::lookAt(lightDir, glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));;
    const GLfloat near_plane = 1.0f, far_plane = 10.0f;
    glm::mat4 lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
    glm::vec3 lightDirTr = glm::vec3(glm::rotate(glm::mat4(1.0f), glm::radians(lightAngle), glm::vec3(0.0f, 50.0f, 0.0f)) * glm::vec4(lightDir, 1.0f));

    /*
    if (carCameraToggle) {
        lightView = glm::lookAt(lightDirTr, carCamera.getCameraTarget(), glm::vec3(0.0f, 80.0f, 0.0f));
    }
    else {
        lightView = glm::lookAt(lightDirTr, freeCamera.getCameraTarget(), glm::vec3(0.0f, 80.0f, 0.0f));
    }
    */
    return lightProjection * lightView;
}

void renderScene() {
    //render the scene to the depth buffer
    depthMapShader.useShaderProgram();
    glUniformMatrix4fv(glGetUniformLocation(depthMapShader.shaderProgram, "lightSpaceTrMatrix"), 1, GL_FALSE, glm::value_ptr(computeLightSpaceTrMatrix()));
    glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
    glBindFramebuffer(GL_FRAMEBUFFER, shadowMapFBO);
    glClear(GL_DEPTH_BUFFER_BIT);
    drawObjects(depthMapShader, true);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // render depth map on screen - toggled with the M key
    if (showDepthMap) {
        glViewport(0, 0, glWindowWidth, glWindowHeight);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        screenQuadShader.useShaderProgram();

        //bind the depth map
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, depthMapTexture);
        glUniform1i(glGetUniformLocation(screenQuadShader.shaderProgram, "depthMap"), 0);

        glDisable(GL_DEPTH_TEST);
        model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(screenQuadShader.shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
        model = glm::scale(glm::mat4(1.0f), glm::vec3(3.0f, 3.0f, 3.0f));
        glUniformMatrix4fv(glGetUniformLocation(screenQuadShader.shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
        screenQuad.Draw(screenQuadShader);
        glEnable(GL_DEPTH_TEST);

    }
    else {

        // final scene rendering pass (with shadows)

        glViewport(0, 0, glWindowWidth, glWindowHeight);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        mainGameShader.useShaderProgram();

        if (carCameraToggle) {
            view = carCamera.getViewMatrix();
        }
        else {
            view = freeCamera.getViewMatrix();
        }
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

        lightRotation = glm::rotate(glm::mat4(1.0f), glm::radians(lightAngle), glm::vec3(0.0f, 1.0f, 0.0f));
        glUniform3fv(lightDirLoc, 1, glm::value_ptr(glm::inverseTranspose(glm::mat3(view * lightRotation)) * lightDir));

        //bind the shadow map
        glActiveTexture(GL_TEXTURE3);
        glBindTexture(GL_TEXTURE_2D, depthMapTexture);
        glUniform1i(glGetUniformLocation(mainGameShader.shaderProgram, "shadowMap"), 3);
        glUniformMatrix4fv(glGetUniformLocation(mainGameShader.shaderProgram, "lightSpaceTrMatrix"), 1, GL_FALSE, glm::value_ptr(computeLightSpaceTrMatrix()));

        drawObjects(mainGameShader, false);

        //draw a white cube around the light

        lightShader.useShaderProgram();

        glUniformMatrix4fv(glGetUniformLocation(lightShader.shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));

        model = lightRotation;
        model = glm::translate(model, 1.0f * lightDir);
        model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));
        glUniformMatrix4fv(glGetUniformLocation(lightShader.shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));

        lightCube.Draw(lightShader);
    }
}

void cleanup() {
    glDeleteTextures(1, &depthMapTexture);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glDeleteFramebuffers(1, &shadowMapFBO);
    myWindow.Delete();
    //cleanup code for your own data
}

int main(int argc, const char* argv[]) {

    try {
        initOpenGLWindow();
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    initOpenGLState();
    initModels();
    initShaders();
    initUniforms();
    setWindowCallbacks();

    glCheckError();
    // application loop
    while (!glfwWindowShouldClose(myWindow.getWindow())) {
        processMovement();
        renderScene();

        glfwPollEvents();
        glfwSwapBuffers(myWindow.getWindow());

        glCheckError();
    }

    cleanup();

    return EXIT_SUCCESS;
}
