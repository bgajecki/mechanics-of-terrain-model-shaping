#include "Menu.hpp"

Menu::Menu(engine::SceneManager& sceneManager, Options& options)
	: engine::Scene(sceneManager), options(options)
{
	/*
	vertexShader = sceneManager.createShader(GL_VERTEX_SHADER, "./shaders/vertexShader");
	fragmentShader = sceneManager.createShader(GL_FRAGMENT_SHADER, "./shaders/fragmentShader");
	program = sceneManager.createProgram();
	program->addShader(vertexShader);
	program->addShader(fragmentShader);
	program->link();
	program->deleteShaders();

	float height = glutGet(GLUT_SCREEN_HEIGHT);
	float width = glutGet(GLUT_SCREEN_WIDTH);

	this->projection = glm::ortho(0.0f, width, height, 0.0f, 0.0f, 10.f);
	this->model = glm::scale(model, glm::vec3(width, height, 1.0));

	this->camera.eye = { 0.0f, 0.0f, 1.0f};
	this->camera.center = { 0.0f, 0.0f, 0.0f };
	this->camera.up = { 0.0f, 1.0f, 0.0 };
	this->view = glm::lookAt(this->camera.eye, this->camera.center, this->camera.up);

	this->updateMvpMatrix();

	program->createUniform(glUniformMatrix4fv, "mvp", 1, GL_FALSE, &this->mvp[0][0]);
	program->createUniform(glUniform1i, "textureSampler", 0);

	mesh = this->createMesh<engine::Mesh>();
	mesh->vertices.push_back(engine::Vertex({ {-0.5,-0.5,0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0} }));
	mesh->vertices.push_back(engine::Vertex({ {0.5,-0.5,0.0}, {0.0, 0.0, 0.0}, {1.0, 0.0} }));
	mesh->vertices.push_back(engine::Vertex({ {0.5,0.5,0.0}, {0.0, 0.0, 0.0}, {1.0, 1.0} }));
	mesh->vertices.push_back(engine::Vertex({ {-0.5,0.5,0.0}, {0.0, 0.0, 0.0}, {0.0, 1.0}}));
	mesh->indices.push_back(0.0);
	mesh->indices.push_back(1.0);
	mesh->indices.push_back(2.0);
	mesh->indices.push_back(1.0);
	mesh->indices.push_back(2.0);
	mesh->indices.push_back(3.0);
	texture.load("./textures/texture.png");
	mesh->textures.push_back(texture);
	mesh->program = program;
	*/
}

void Menu::Display()
{
}

void Menu::Reshape(int width, int height)
{
	/*
	this->projection = glm::ortho(0.0f, static_cast<float>(width), static_cast<float>(height), 0.0f, 0.1f, 10.f);
	this->model = glm::scale(model, glm::vec3(width, height, 1.0));
	this->updateMvpMatrix();
	*/
}

void Menu::Special(int key, int x, int y)
{
}

void Menu::OnKeyDown(unsigned char key, int x, int y)
{
}

void Menu::OnMouseClick(int button, int state, int x, int y)
{
}

void Menu::RefreshDisplay(int t)
{
}

void Menu::Time(int t)
{
}
