#ifndef MESH_CLASS_H
#define MESH_CLASS_H

#include<string>
#include <cstring>

#include"VAO.h"
#include"EBO.h"
#include"Camera.h"
#include"Tex.h"
#include"PhysicsWorld.h"
class Object
{
public:
	bool deleted = false;
	bool selected;
	Texture tex = Texture("");
	std::string texChar;
	float outlineWidth = 0;
	std::string name;
	bool drawOnRuntime = true;
	glm::vec3 OutlineColor = glm::vec3(0,0,0);
	glm::vec2* position;
	glm::vec2* scale;
	glm::vec2 scenePosition;
	glm::vec2 sceneScale;
	float* angle = 0;
	int layer = 0;

	float TileX = 1.0f, TileY = 1.0f;
	std::vector <Vertex> vertices;
	std::vector <GLuint> indices;
	std::vector <Texture> textures;
	VAO VAO;

	/// <summary>
	/// Degrees To Radians
	/// </summary>
	/// <param name="radians"></param>
	/// <returns></returns>
	float Deg(float radians)
	{

		return radians * 3.14159 / 180;
	}
	GLuint GetShaderSource() {
		return shader;
	}

	Object(std::vector <Vertex>& vertices, std::vector <GLuint>& indices);
	void Draw(GLFWwindow* window, GLuint shader, Camera& camera, glm::vec3 axis, float cameraX, float cameraY, bool TextureNearest);
	void Draw(GLFWwindow* window, GLuint shader, Camera& camera,glm::vec3 axis, bool TextureNearest);
	void DrawTMP(GLFWwindow* window, GLuint shader, Camera& camera, glm::vec2 pos, glm::vec2 scale);
	PhysicsBody* Body;
private :
	GLuint shader;
};
#endif