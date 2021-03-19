#include "Camera.hpp"
#include <iostream>

namespace gps {

    //Camera constructor
    Camera::Camera(glm::vec3 cameraPosition, glm::vec3 cameraTarget, glm::vec3 cameraUp) {
        this->cameraPosition = cameraPosition;
        this->cameraTarget = cameraTarget;
        this->cameraUpDirection = cameraUp;
        this->cameraFrontDirection = glm::normalize(cameraTarget - cameraPosition);
        this->cameraRightDirection = glm::normalize(glm::cross(this->cameraFrontDirection, glm::vec3(0.0f, 1.0f, 0.0f)));
    }

    //return the view matrix, using the glm::lookAt() function
    glm::mat4 Camera::getViewMatrix() {
        return glm::lookAt(cameraPosition, cameraPosition + cameraFrontDirection, cameraUpDirection);
    }

    glm::vec3 Camera::getCameraPosition() {
        return this->cameraPosition;
    }

    glm::vec3 Camera::getCameraTarget() {
        return this->cameraTarget;
    }

    void Camera::setCameraTarget(glm::vec3 target) {
        this->cameraTarget = target;
        cameraFrontDirection = glm::normalize(cameraTarget - cameraPosition);
        cameraRightDirection = glm::normalize(glm::cross(this->cameraFrontDirection, glm::vec3(0.0f, 1.0f, 0.0f)));
    }

    //update the camera internal parameters following a camera move event
    void Camera::move(MOVE_DIRECTION direction, float speed, int type) {
        float auxCameraHeight = cameraPosition.y;
        if (direction == gps::MOVE_FORWARD) {
            cameraPosition += cameraFrontDirection * speed;
            if (type != 2) {
                cameraTarget += cameraFrontDirection * speed;
            }
            if (type == 2) {
                cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
            }
     
        }
        else if (direction == gps::MOVE_BACKWARD) {
            glm::vec3 oldFrontDirection = this->cameraFrontDirection;
            cameraPosition -= cameraFrontDirection * speed;
            if (type != 2) {
                cameraTarget -= cameraFrontDirection * speed;
            }
            
           
        }
        else if (direction == gps::MOVE_LEFT) {
            cameraPosition -= cameraRightDirection * speed;
            if (type != 2) {
                cameraTarget -= cameraRightDirection * speed;
            }
            if (type == 2) {
                cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
            }
      
        }
        else if (direction == gps::MOVE_RIGHT) {
            cameraPosition += cameraRightDirection * speed;
            if (type != 2) {
                cameraTarget += cameraRightDirection * speed;
            }
      
        }
        if (type != 1) {
            cameraPosition.y = auxCameraHeight;
        }
        if (direction == gps::MOVE_UP) {
            cameraPosition += cameraUpDirection * speed;
            cameraTarget += cameraUpDirection * speed;
      
        }
        if (direction == gps::MOVE_DOWN) {
            cameraPosition -= cameraUpDirection * speed;
            cameraTarget -= cameraUpDirection * speed;
           
        }
        
        std::cout << "Camera: " << cameraPosition.x << " " << cameraPosition.y << " " << cameraPosition.z << std::endl;
    }

    //update the camera internal parameters following a camera rotate event
    //yaw - camera rotation around the y axis
    //pitch - camera rotation around the x axis
    void Camera::rotate(float pitch, float yaw) {
        glm::vec3 direction;
        glm::vec3 currentPos = this->cameraPosition;
        //glm::vec3 currentTarget = this->cameraTarget;

        if (pitch > 89) {
            pitch = 89;
        }
        if (pitch < 89) {
            pitch = -pitch;
        }

        this->cameraPosition = glm::vec3();

        direction.x = cos(yaw) * cos(pitch);
        direction.y = sin(pitch);
        direction.z = sin(yaw) * cos(pitch);
        cameraTarget = direction;
        cameraFrontDirection = glm::normalize(cameraTarget - cameraPosition);
        cameraRightDirection = glm::normalize(glm::cross(this->cameraFrontDirection, glm::vec3(0.0f, 1.0f, 0.0f)));
        this->cameraPosition = currentPos;
    }
}