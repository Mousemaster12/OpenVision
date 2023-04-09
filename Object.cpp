#include "Object.h"

Object::Object(std::vector <Vertex>& vertices, std::vector <GLuint>& indices)
{
	Object::vertices = vertices;
    Object::indices = indices;

	VAO.Bind();
	VBO VBO(vertices);
	EBO EBO(indices);
	VAO.LinkAttrib(VBO, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
	VAO.LinkAttrib(VBO, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)));
	VAO.LinkAttrib(VBO, 2, 3, GL_FLOAT, sizeof(Vertex), (void*)(6 * sizeof(float)));
	VAO.LinkAttrib(VBO, 3, 2, GL_FLOAT, sizeof(Vertex), (void*)(9 * sizeof(float)));

	VAO.Unbind();
	VBO.Unbind();
	EBO.Unbind();
}



void Object::Draw(GLFWwindow* window, GLuint shader, Camera& camera, glm::vec3 axis, float width, float height, glm::vec2 ratio)
{
    glUseProgram(shader);
    VAO.Bind();
	tex.Bind();
	
    unsigned int numDiffuse = 0;
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(calculatedPosition.x, -calculatedPosition.y, 0.0f));

    model = glm::rotate(model, Deg(angle), axis);
    model = glm::scale(model, glm::vec3(ScaleX, ScaleY, 1.0f));

    glUniformMatrix4fv(glGetUniformLocation(shader, "model"), 1, GL_FALSE, glm::value_ptr(model));

    glUniform3f(glGetUniformLocation(shader, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
    camera.Matrix(shader, "camMatrix");

    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}






