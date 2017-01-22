////////////////////////////////////////////////////////////
//
// Roaming Robot - Created by Jegor Kharlamov
// Created for Games Programming Year 3 Coursework at DMU - Games Programming Course
//
// This project is a collectathon made with personally developed game engine components
//
////////////////////////////////////////////////////////////
#ifndef __ROBOT_H
#define __ROBOT_H

#include <glm.hpp>

// Constants for arm and leg movement states
const char BACKWARD_STATE = 0;
const char FORWARD_STATE  = 1;

// Index constants for accessing arm and leg array data
const char LEFT  = 0;
const char RIGHT = 1;

class Robot
{
private:
	// Body states
	char legStates[2];	
	char armStates[2];

	float legAngles[2];
	float armAngles[2];

	float m_fArmsRotation; // Speed at which robots arms animate

	float m_fLegRotation; // Speed at which robots legs animate



	// Draws a unit cube
	void DrawCube(float xPos, float yPos, float zPos);

	// Methods to draw the parts of the robot
	void DrawArm(float xPos, float yPos, float zPos);
	void DrawHead(float xPos, float yPos, float zPos);
	void DrawTorso(float xPos, float yPos, float zPos);
	void DrawLeg(float xPos, float yPos, float zPos);
	void DrawFoot(float xPos, float yPos, float zPos);
	
	glm::vec3 m_RobotPosition; // Robots position in 3D space
	

public:

	Robot();
	virtual ~Robot();
	float m_fRotationAngle; // Angle robot is facing
	// Draws the entire robot
	void DrawRobot(float xPos, float yPos, float zPos);
	void Move(float distance); // Allows movement of the robot 
	void ToggleArmsMovement(); // Stops arms movement 
	void ToggleAllMovement(); // Stops all movement
	void SetRobotPosition(glm::vec3 NewPosition); // Change robots position
	void ResetRotations(); // Resets all the rotations for the body parts
	glm::vec3 ReturnRobotPosition();
	bool Moving;
	// Updates the robot data
	void Prepare(float dt);
};

#endif