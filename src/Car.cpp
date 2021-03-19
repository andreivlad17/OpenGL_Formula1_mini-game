#include "Car.hpp"
#include "Camera.hpp"
#include <iostream>

namespace gps {

    //car constructor
    Car::Car(glm::vec3 carPosition, glm::vec3 carTarget, glm::vec3 carUp) {
        this->carPosition = carPosition;
        this->carTarget = carTarget;
        this->carUpDirection = carUp;
        this->carFrontDirection = glm::normalize(carTarget - carPosition);
        this->carRightDirection = glm::normalize(glm::cross(this->carFrontDirection, glm::vec3(0.0f, 1.0f, 0.0f)));
    }

    //return the view matrix, using the glm::lookAt() function
    glm::mat4 Car::getViewMatrix() {
        return glm::lookAt(carPosition, carPosition + carFrontDirection, carUpDirection);
    }
    
    glm::vec3 Car::getCarPosition() {
        return this->carPosition;
    }

    //update the car internal parameters following a car move event
    void Car::move(gps::Camera camera, glm::vec3 offset) {
        this->carPosition = camera.getCameraPosition() + offset;
    }
    /*
    void Car::move(gps::CAR_MOVE_DIRECTION direction, float speed) {
        if (direction == gps::CAR_MOVE_FORWARD) {
            carPosition += carFrontDirection * speed;
            carTarget += carFrontDirection * speed;
            
        }
        else if (direction == gps::CAR_MOVE_BACKWARD) {
            carPosition -= carFrontDirection * speed;
            carTarget -= carFrontDirection * speed;
        }
        else if (direction == gps::CAR_MOVE_LEFT) {
            carPosition -= carRightDirection * speed;
            carTarget -= carRightDirection * speed;
        }
        else if (direction == gps::CAR_MOVE_RIGHT) {
            carPosition += carRightDirection * speed;
            carTarget += carRightDirection * speed;
        }
        carPosition.y = 0;
        std::cout << "Car: " << carPosition.x << " " << carPosition.y << " " << carPosition.z << std::endl;
    }*/

    //update the car internal parameters following a car rotate event
    //yaw - car rotation around the y axis
    //pitch - car rotation around the x axis
    void Car::rotate(float pitch, float yaw) {
        glm::vec3 direction;
        glm::vec3 currentPos = this->carPosition;
        //glm::vec3 currentTarget = this->carTarget;

        this->carPosition = glm::vec3();

        direction.x = cos(yaw) * cos(pitch);
        direction.y = sin(pitch);
        direction.z = sin(yaw) * cos(pitch);
        carTarget = direction;
        carFrontDirection = glm::normalize(carTarget - carPosition);
        carRightDirection = glm::normalize(glm::cross(this->carTarget, glm::vec3(0.0f, 1.0f, 0.0f)));
        this->carPosition = currentPos;
    }
}