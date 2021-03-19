#ifndef Car_hpp
#define Car_hpp

#include <glm/glm.hpp>
#include "Camera.hpp"
#include <glm/gtx/transform.hpp>

#include <string>

namespace gps {

    enum CAR_MOVE_DIRECTION { CAR_MOVE_FORWARD, CAR_MOVE_BACKWARD, CAR_MOVE_RIGHT, CAR_MOVE_LEFT};

    class Car
    {
    public:
        //Car constructor
        Car(glm::vec3 carPosition, glm::vec3 carTarget, glm::vec3 carUp);
        //return the view matrix, using the glm::lookAt() function
        glm::mat4 getViewMatrix();
        glm::vec3 getCarPosition();
        //update the car internal parameters following a car move event
        
        //void move(gps::CAR_MOVE_DIRECTION direction, float speed);
        void move(gps::Camera camera, glm::vec3 offset);

        //update the car internal parameters following a car rotate event
        //yaw - car rotation around the y axis
        //pitch - car rotation around the x axis
        void rotate(float pitch, float yaw);
        glm::vec3 carPosition;
        glm::vec3 carTarget;
    
    private:

        glm::vec3 carFrontDirection;
        glm::vec3 carRightDirection;
        glm::vec3 carUpDirection;
    };

}

#endif /* Car_hpp */
