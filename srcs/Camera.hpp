#ifndef CAMERA_HPP__
# define CAMERA_HPP__

#include <iostream>
#include <cmath>
#include <scopm.hpp>

enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
	UP,
	DOWN
};

// Default camera values
const float YAW         = -90.0f;
const float PITCH       =  0.0f;
const float SPEED       =  7.5f;
const float SENSITIVITY =  0.1f;
const float ZOOM        =  45.0f;

class Camera
{
public:
	// camera Attributes
	Vector3	position;
	Vector3	front;
	Vector3	up;
	Vector3	right;
	Vector3	worldUp;
	// euler Angles
	float yaw;
	float pitch;
	// camera options
	float	movementSpeed;
	float	mouseSensitivity;
	float	zoom;

	Vector3	inputAxis;

	Camera(Vector3 _position = Vector3(0.0f, 0.0f, 0.0f), Vector3 _up = Vector3(0.0f, 1.0f, 0.0f), float _yaw = YAW, float _pitch = PITCH) :
		front(Vector3(0.0f, 0.0f, -1.0f)),
		movementSpeed(SPEED),
		mouseSensitivity(SENSITIVITY),
		zoom(ZOOM)
	{
		position = _position;
		worldUp = _up;
		yaw = _yaw;
		pitch = _pitch;
		updateCameraVectors();
	}
	~Camera() {}

	// returns the view matrix calculated using Euler Angles and the LookAt Matrix
	Matrix4x4 GetViewMatrix() {
		return Matrix4x4::LookAt(position, position + front, up);
	}

	// processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
    void ProcessKeyboard(Camera_Movement direction, float deltaTime)
    {
        float velocity = movementSpeed * deltaTime;
        if (direction == FORWARD)
            position = position + front * velocity;
        if (direction == BACKWARD)
            position = position - front * velocity;
        if (direction == LEFT)
            position = position - right * velocity;
        if (direction == RIGHT)
            position = position + right * velocity;
        if (direction == UP)
            position = position + up * velocity;
        if (direction == DOWN)
            position = position - up * velocity;
    }

    // processes input received from a mouse input system. Expects the offset value in both the x and y direction.
    void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true)
    {
        xoffset *= mouseSensitivity;
        yoffset *= mouseSensitivity;

        yaw   += xoffset;
        pitch += yoffset;

        // make sure that when pitch is out of bounds, screen doesn't get flipped
        if (constrainPitch)
        {
            if (pitch > 89.0f)
                pitch = 89.0f;
            if (pitch < -89.0f)
                pitch = -89.0f;
        }

        // update Front, Right and Up Vectors using the updated Euler angles
        updateCameraVectors();
    }

    // processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
    void ProcessMouseScroll(float yoffset)
    {
        zoom -= (float)yoffset;
        if (zoom < 1.0f)
            zoom = 1.0f;
        if (zoom > 45.0f)
            zoom = 45.0f;
    }

private:
    // calculates the front vector from the Camera's (updated) Euler Angles
    void updateCameraVectors()
    {
        // calculate the new Front vector
        Vector3 n_front;
        n_front.x = cos(radians(yaw)) * cos(radians(pitch));
        n_front.y = sin(radians(pitch));
        n_front.z = sin(radians(yaw)) * cos(radians(pitch));
        front = (n_front).normalized();
        // also re-calculate the Right and Up vector
        right = (Vector3::Cross(front, worldUp)).normalized();  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
        up    = (Vector3::Cross(right, front)).normalized();
    }

};

#endif
