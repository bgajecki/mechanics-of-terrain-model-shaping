#include "Presentation.hpp"

Presentation::Presentation(engine::SceneManager& sceneManager, Options& options)
	: engine::Scene(sceneManager), options(options)
{

	meshVertexShader = sceneManager.createShader(GL_VERTEX_SHADER, "./shaders/mesh.vs");
	rainVertexShader = sceneManager.createShader(GL_VERTEX_SHADER, "./shaders/rain.vs");
	terrainFragmentShader = sceneManager.createShader(GL_FRAGMENT_SHADER, "./shaders/terrain.fs");
	waterFragmentShader = sceneManager.createShader(GL_FRAGMENT_SHADER, "./shaders/water.fs");
	rainFragmentShader = sceneManager.createShader(GL_FRAGMENT_SHADER, "./shaders/rain.fs");
	rainGeometryShader = sceneManager.createShader(GL_GEOMETRY_SHADER, "./shaders/rain.gs");

	terrainProgram = sceneManager.createProgram();
	rainProgram = sceneManager.createProgram();
	waterProgram = sceneManager.createProgram();

	terrainProgram->addShader(meshVertexShader);
	terrainProgram->addShader(terrainFragmentShader);

	rainProgram->addShader(rainVertexShader);
	rainProgram->addShader(rainGeometryShader);
	rainProgram->addShader(rainFragmentShader);

	waterProgram->addShader(meshVertexShader);
	waterProgram->addShader(waterFragmentShader);

	sceneManager.linkPrograms();
	sceneManager.deleteShaders();

	float height = 600;//glutGet(GLUT_SCREEN_HEIGHT);
	float width = 800;//glutGet(GLUT_SCREEN_WIDTH);

	this->projection = glm::perspective(45.0f, 1.0f * width / height, 0.1f, 50.0f);

	this->view = this->camera.getViewMatrix();

	terrainProgram->createUniform(glUniformMatrix4fv, "projection", 1, GL_FALSE, &this->projection[0][0]);
	terrainProgram->createUniform(glUniformMatrix4fv, "view", 1, GL_FALSE, &this->view[0][0]);
	terrainProgram->createUniform(glUniformMatrix4fv, "model", 1, GL_FALSE, &this->model[0][0]);
	terrainProgram->createUniform(glUniform1i, "textureSampler", 0);

	rainProgram->createUniform(glUniformMatrix4fv, "projection", 1, GL_FALSE, &this->projection[0][0]);
	rainProgram->createUniform(glUniformMatrix4fv, "view", 1, GL_FALSE, &this->view[0][0]);
	rainProgram->createUniform(glUniformMatrix4fv, "model", 1, GL_FALSE, &this->model[0][0]);

	waterProgram->createUniform(glUniformMatrix4fv, "projection", 1, GL_FALSE, &this->projection[0][0]);
	waterProgram->createUniform(glUniformMatrix4fv, "view", 1, GL_FALSE, &this->view[0][0]);
	waterProgram->createUniform(glUniformMatrix4fv, "model", 1, GL_FALSE, &this->model[0][0]);
	waterProgram->createUniform(glUniform1i, "textureSampler", 0);

	texture.load("./textures/noise.jpg");

	terrain = this->createObject<Terrain>();
	terrain->textures.push_back(texture);
	terrain->setPosition({ 0.0f, 0.0f, 0.0f });
	terrain->setProgram(terrainProgram);

	water = this->createObject<Water>(terrain);
	water->textures.push_back(texture);
	water->setProgram(waterProgram);

	rain = this->createObject<Rain>();
	rain->setProgram(rainProgram);
	rain->setPosition({ 0.0f, 0.0f, 0.0f });
	rain->isRaining = true;

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);
	
}

void Presentation::Display()
{
}

void Presentation::Reshape(int width, int height)
{
}

void Presentation::Special(int key, int x, int y)
{
	const float update = 2.0f;
	switch (key)
	{
	case GLUT_KEY_UP:
		this->camera.rotate(0.0f, update);
		this->view = this->camera.getViewMatrix();
		break;
	case GLUT_KEY_DOWN:
		this->camera.rotate(0.0f, -update);
		this->view = this->camera.getViewMatrix();
		break;
	case GLUT_KEY_LEFT:
		this->camera.rotate(-update, 0.0f);
		this->view = this->camera.getViewMatrix();
		break;
	case GLUT_KEY_RIGHT:
		this->camera.rotate(update,0.0f);
		this->view = this->camera.getViewMatrix();
		break;
	}

}

void Presentation::OnKeyDown(unsigned char key, int x, int y)
{
	const float update = 0.1f;
	switch (key)
	{
	case 'q':
		this->camera.moveAccordingToDirection({ 0.0, update, 0.0 });
		this->view = this->camera.getViewMatrix();
		break;
	case 'e':
		this->camera.moveAccordingToDirection({ 0.0, -update, 0.0 });
		this->view = this->camera.getViewMatrix();
		break;
	case 'w':
		this->camera.moveAccordingToDirection({ 0.0, 0.0, update });
		this->view = this->camera.getViewMatrix();
		break;
	case 's':
		this->camera.moveAccordingToDirection({ 0.0, 0.0, -update });
		this->view = this->camera.getViewMatrix();
		break;
	case 'a':
		this->camera.moveAccordingToDirection({ update, 0.0, 0.0 });
		this->view = this->camera.getViewMatrix();
		break;
	case 'd':
		this->camera.moveAccordingToDirection({ -update, 0.0, 0.0 });
		this->view = this->camera.getViewMatrix();
		break;
	}


}

void Presentation::OnMouseClick(int button, int state, int x, int y)
{
}

void Presentation::RefreshDisplay(int t)
{
}

void Presentation::Time(int t)
{
	this->rain->run();
	this->water->update(this->rain->isRaining);
}