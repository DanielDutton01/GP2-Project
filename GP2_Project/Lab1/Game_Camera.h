#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
//used for the game camera
struct Game_Camera
{
public:
	Game_Camera()
	{
	}
	//sets up game camera
	void init_Game_Camera(const glm::vec3& pos, float fov, float aspect, float nearClip, float farClip)
	{
		this->pos = pos;
		this->forward = glm::vec3(0.0f, 0.0f, 1.0f);
		this->up = glm::vec3(0.0f, 1.0f, 0.0f);
		this->projection = glm::perspective(fov, aspect, nearClip, farClip);
	}
	//creates and returns MVP
	inline glm::mat4 GetViewProjection() const
	{
		return projection * glm::lookAt(pos, pos + forward, up);
	}

	glm::vec3 getPos()
	{
		return this->pos;
	}
	//move camera forwards/backwards
	void MoveForward(float amt)
	{
		pos += forward * amt;
	}
	//move camera left/right
	void MoveSide(float amt)
	{
		pos += glm::cross(up, forward) * amt;
	}	

protected:
private:
	glm::mat4 projection;
	glm::vec3 pos;
	glm::vec3 forward;
	glm::vec3 up;
};



