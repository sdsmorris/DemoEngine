#include "CollisionRenderer.h"
#include "vector"
#include <glm/gtc/constants.hpp>

Shader CollisionRenderer::debugShader;

void CollisionRenderer::init()
{
	debugShader = Shader("C:/Users/sammo/source/repos/DemoEngine/DemoEngine/src/Debug/debugColliderVertex.glsl", "C:/Users/sammo/source/repos/DemoEngine/DemoEngine/src/Debug/debugColliderFragment.glsl");
}

void CollisionRenderer::drawAlignedBoundingBox(glm::vec3 bboxMin, glm::vec3 bboxMax, glm::mat4 projection, glm::mat4 view)
{
	debugShader.setMat4("view", view);
	debugShader.setMat4("projection", projection);
	//Optimal rendering strategy would be to use strips, but maybe even lines would work better? Doesn't matter too much though its debug
	float quad[] = { bboxMax.x, bboxMax.y, bboxMax.z,		//TOP
						bboxMax.x, bboxMax.y, bboxMin.z,
						bboxMin.x, bboxMax.y, bboxMax.z,
						bboxMax.x, bboxMax.y, bboxMin.z,
						bboxMin.x, bboxMax.y, bboxMax.z,
						bboxMin.x, bboxMax.y, bboxMin.z,
						bboxMax.x, bboxMin.y, bboxMax.z,	//BOTTOM
						bboxMax.x, bboxMin.y, bboxMin.z,
						bboxMin.x, bboxMin.y, bboxMax.z,
						bboxMax.x, bboxMin.y, bboxMin.z,
						bboxMin.x, bboxMin.y, bboxMax.z,
						bboxMin.x, bboxMin.y, bboxMin.z,
						bboxMax.x, bboxMax.y, bboxMax.z,	//SIDE
						bboxMax.x, bboxMin.y, bboxMax.z,
						bboxMax.x, bboxMax.y, bboxMin.z,
						bboxMax.x, bboxMin.y, bboxMax.z,
						bboxMax.x, bboxMin.y, bboxMin.z,
						bboxMax.x, bboxMax.y, bboxMin.z,
						bboxMin.x, bboxMax.y, bboxMax.z,	//SIDE
						bboxMin.x, bboxMin.y, bboxMax.z,
						bboxMin.x, bboxMax.y, bboxMin.z,
						bboxMin.x, bboxMin.y, bboxMax.z,
						bboxMin.x, bboxMin.y, bboxMin.z,
						bboxMin.x, bboxMax.y, bboxMin.z,
						bboxMax.x, bboxMax.y, bboxMin.z, //SIDE
						bboxMax.x, bboxMin.y, bboxMin.z,
						bboxMin.x, bboxMin.y, bboxMin.z,
						bboxMin.x, bboxMax.y, bboxMin.z,
						bboxMax.x, bboxMax.y, bboxMin.z,
						bboxMin.x, bboxMin.y, bboxMin.z,
						bboxMax.x, bboxMax.y, bboxMax.z, //SIDE
						bboxMax.x, bboxMin.y, bboxMax.z,
						bboxMin.x, bboxMin.y, bboxMax.z,
						bboxMin.x, bboxMax.y, bboxMax.z,
						bboxMax.x, bboxMax.y, bboxMax.z,
						bboxMin.x, bboxMin.y, bboxMax.z
	};
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glLineWidth(5.0f);

	unsigned int vao, vbo;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quad), &quad, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), 0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);

	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, sizeof(quad) / 12);
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void CollisionRenderer::drawBoundingSphere(glm::vec3 position, float radius)
{
	const int stacks = 20;
	const int slices = 20;

	std::vector<float> vertices;
	std::vector<unsigned short> indices;

	for (int i = 0; i <= stacks; ++i) {

		float V = i / (float)stacks;
		float phi = V * glm::pi <float>();

		// Loop Through Slices
		for (int j = 0; j <= slices; ++j) {

			float U = j / (float)slices;
			float theta = U * (glm::pi <float>() * 2);

			// Calc The Vertex Positions
			float x = cosf(theta) * sinf(phi);
			float y = cosf(phi);
			float z = sinf(theta) * sinf(phi);

			// Push Back Vertex Data
			vertices.push_back(x * radius + position.x);
			vertices.push_back(y * radius + position.y);
			vertices.push_back(z* radius + position.z);
		}
	}

	// Calc The Index Positions
	for (int i = 0; i < slices * stacks + slices; ++i) {

		indices.push_back(i);
		indices.push_back(i + slices + 1);
		indices.push_back(i + slices);

		indices.push_back(i + slices + 1);
		indices.push_back(i);
		indices.push_back(i + 1);
	}

	unsigned int vao, vbo, ebo;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), &vertices[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), 0);
	glEnableVertexAttribArray(0);
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(short), &indices[0], GL_STATIC_DRAW);

	glBindVertexArray(0);

	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_SHORT, 0);

	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ebo);
}
