#ifndef OPENGL_CAMERA_H
#define OPENGL_CAMERA_H

#include <glm/glm.hpp>

namespace camera {
    enum class Direction {
        Forward, Backward, Left, Right
    };

    class Camera {
    private:
        glm::vec3 positionVec{0.0f, 0.0f, 1.0f};
        glm::vec3 frontVec{0.0f, 0.0f, -1.0f};
        glm::vec3 upVec{0.0f, 1.0f, 0.0f};

        float yaw{-90.0f};
        float pitch{0.0f};
        float pitchMax{89.0f};
        float pitchMin{-89.0f};
        float sensitivity{0.1f};

        float speed{2.5f};
    public:
        explicit Camera(glm::vec3 position = glm::vec3{0.0f, 0.0f, 0.0f},
               glm::vec3 front = glm::vec3{0.0f, 0.0f, -1.0f},
               glm::vec3 up = glm::vec3{0.0f, 1.0f, 0.0f});

        void move(Direction direction, float multiplier);

        void rotate(float pitchDeg, float yawDeg);

        [[nodiscard]] glm::vec3 getTargetVec() const;

        [[nodiscard]] const glm::vec3 &getPositionVec() const;

        [[nodiscard]] const glm::vec3 &getFrontVec() const;

        [[nodiscard]] const glm::vec3 &getUpVec() const;
    };
}

#endif
