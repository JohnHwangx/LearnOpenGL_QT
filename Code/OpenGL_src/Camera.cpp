#include "Camera.h"

using namespace glm;

void CAMERA::Camera::updateCameraVector()
{
	vec3 front;
	front.x = cos(radians(Yaw))*cos(radians(Pitch));
	front.y = sin(radians(Pitch));
	front.z = sin(radians(Yaw))*cos(radians(Pitch));
	Front = normalize(front);
	Right = normalize(cross(Front, WorldUp));
	Up = normalize(cross(Right, Front));
}

CAMERA::Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch) :Front(vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
{
	Position = position;
	WorldUp = up;
	Yaw = yaw;
	Pitch = pitch;
	updateCameraVector();
}

CAMERA::Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) :Front(vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
{
	Position = vec3(posX, posY, posZ);
	WorldUp = vec3(upX, upY, upZ);
	Yaw = yaw;
	Pitch = pitch;
	updateCameraVector();
}

glm::mat4 CAMERA::Camera::GetViewMatrix()
{
	return lookAt(Position, Position + Front, Up);
}

void CAMERA::Camera::ProcessKeyboard(Camera_Movement direction, float delatTime)
{
	float velocity = MovementSpeed * delatTime;
	switch (direction)
	{
	case FORWARD:
		Position += Front * velocity;
		break;
	case BACKWARD:
		Position -= Front * velocity;
		break;
	case LEFT:
		Position -= Right * velocity;
		break;
	case RIGHT:
		Position += Right * velocity;
		break;
	default:
		break;
	}
}

void CAMERA::Camera::ProcessMouseMove(float xoffset, float yoffset, bool constrainPitch)
{
	xoffset *= MouseSensitivity;
	yoffset *= MouseSensitivity;

	Yaw += xoffset;
	Pitch += yoffset;

	if (constrainPitch)
	{
		if (Pitch > 89.0f)
			Pitch = 89.0f;
		if (Pitch < -89.0f)
			Pitch = -89.0f;
	}

	updateCameraVector();
}

void CAMERA::Camera::ProcessMouseScroll(float yoffset)
{
	if (Zoom >= 1.0f&&Zoom <= 45.0f)
		Zoom -= yoffset;
	else if (Zoom <= 1.0f)
		Zoom = 1.0f;
	else if (Zoom >= 45.0f)
		Zoom = 45.0f;
}
