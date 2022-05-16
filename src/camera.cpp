#include <algorithm>
#include <cmath>

#include "camera.h"

namespace camera {
    Camera::Camera(glm::vec3 position, glm::vec3 front, glm::vec3 up) : positionVec{position}, frontVec{front}, upVec{up} {}

    void Camera::move(Direction direction, float multiplier) {
        if (direction == Direction::Forward) {
            positionVec += speed * multiplier * frontVec;
        } else if (direction == Direction::Backward) {
            positionVec -= speed * multiplier * frontVec;
        } else if (direction == Direction::Right) {
            positionVec += speed * multiplier * glm::normalize(glm::cross(frontVec, upVec));
        } else {
            positionVec -= speed * multiplier * glm::normalize(glm::cross(frontVec, upVec));
        }
    }

    void Camera::rotate(float pitchDeg, float yawDeg) {
        pitch += sensitivity * pitchDeg;
        pitch = std::clamp(pitch, pitchMin, pitchMax);

        yaw += sensitivity * yawDeg;

        glm::vec3 direction {};
        direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        direction.y = sin(glm::radians(pitch));
        direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        frontVec = glm::normalize(direction);
    }

    glm::vec3 Camera::getTargetVec() const {
        return positionVec + frontVec;
    }

    const glm::vec3 &Camera::getPositionVec() const {
        return positionVec;
    }

    const glm::vec3 &Camera::getFrontVec() const {
        return frontVec;
    }

    const glm::vec3 &Camera::getUpVec() const {
        return upVec;
    }
}
