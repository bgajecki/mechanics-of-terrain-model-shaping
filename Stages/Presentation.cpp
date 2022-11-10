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

	//chunkVertexShader = sceneManager.createShader(GL_VERTEX_SHADER, "./shaders/chunk.vs");
	//chunkFragmentShader = sceneManager.createShader(GL_FRAGMENT_SHADER, "./shaders/chunk.fs");
	

	terrainProgram = sceneManager.createProgram();
	rainProgram = sceneManager.createProgram();
	waterProgram = sceneManager.createProgram();
	//chunkProgram = sceneManager.createProgram();

	terrainProgram->addShader(meshVertexShader);
	terrainProgram->addShader(terrainFragmentShader);

	rainProgram->addShader(rainVertexShader);
	rainProgram->addShader(rainGeometryShader);
	rainProgram->addShader(rainFragmentShader);

	waterProgram->addShader(meshVertexShader);
	waterProgram->addShader(waterFragmentShader);

	//chunkProgram->addShader(chunkVertexShader);
	//chunkProgram->addShader(chunkFragmentShader);
	
	sceneManager.linkPrograms();
	sceneManager.deleteShaders();

	float height = glutGet(GLUT_SCREEN_HEIGHT);
	float width = glutGet(GLUT_SCREEN_WIDTH);

	this->projection = glm::perspective(45.0f, 1.0f * width / height, 0.1f, 100.0f);

	this->camera.eye = { 0.0f, 0.5f, 0.5f };
	yaw = 0.f;
	pitch = 0.f;
	this->camera.center.x = cos(this->pitch) * cos(this->yaw);
	this->camera.center.y = sin(this->yaw);
	this->camera.center.z = sin(this->pitch) * cos(this->yaw);
	this->camera.up = { 0.0f, 1.0f, 0.0 };
	this->view = glm::lookAt(this->camera.eye, this->camera.center, this->camera.up);

	this->updateMvpMatrix();

	terrainProgram->createUniform(glUniformMatrix4fv, "mvp", 1, GL_FALSE, &this->mvp[0][0]);
	terrainProgram->createUniform(glUniform1i, "textureSampler", 0);

	rainProgram->createUniform(glUniformMatrix4fv, "mvp", 1, GL_FALSE, &this->mvp[0][0]);

	waterProgram->createUniform(glUniformMatrix4fv, "mvp", 1, GL_FALSE, &this->mvp[0][0]);
	waterProgram->createUniform(glUniform1i, "textureSampler", 0);

	terrain = this->createObject<Terrain>();
	texture.load("./textures/noise.jpg");
	terrain->textures.push_back(texture);
	terrain->program = terrainProgram;

	water = this->createObject<Water>(terrain);
	water->textures.push_back(texture);
	water->program = waterProgram;

	rain = this->createObject<Rain>();
	rain->program = rainProgram;
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
	const float two_degrees = 0.034906585f;
	switch (key)
	{
	case GLUT_KEY_UP:
		this->rotateYaw(two_degrees);
		break;
	case GLUT_KEY_DOWN:
		this->rotateYaw(-two_degrees);
		break;
	case GLUT_KEY_LEFT:
		this->rotatePitch(-two_degrees);
		break;
	case GLUT_KEY_RIGHT:
		this->rotatePitch(two_degrees);
		break;
	}

}

void Presentation::OnKeyDown(unsigned char key, int x, int y)
{
	float update = 0.1f;
	switch (key)
	{
	case 'q':
		updateCameraPosition(this->camera.center.z, this->camera.eye.z, update);
		break;
	case 'e':
		updateCameraPosition(this->camera.center.z, this->camera.eye.z, -update);
		break;
	case 'w':
		updateCameraPosition(this->camera.center.y, this->camera.eye.y, update);
		break;
	case 's':
		updateCameraPosition(this->camera.center.y, this->camera.eye.y, -update);
		break;
	case 'a':
		updateCameraPosition(this->camera.center.x, this->camera.eye.x, -update);
		break;
	case 'd':
		updateCameraPosition(this->camera.center.x, this->camera.eye.x, update);
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

void Presentation::rotateYaw(float angle)
{
	const float full_turn = 6.28318530718f;
	this->yaw += angle;
	if (this->yaw > full_turn)
		this->yaw = 0.f;
	else if (this->yaw < -full_turn)
		this->yaw = 0.f;
	this->camera.center.x = cos(this->pitch) * cos(this->yaw);
	this->camera.center.y = sin(this->yaw);
	this->camera.center.z = sin(this->pitch) * cos(this->yaw);
	this->view = glm::lookAt(this->camera.eye, this->camera.center, this->camera.up);
	this->updateMvpMatrix();
}

void Presentation::rotatePitch(float angle)
{
	const float full_turn = 6.28318530718f;
	this->pitch += angle;
	if (this->pitch > full_turn)
		this->pitch = 0.f;
	else if (this->pitch < -full_turn)
		this->pitch = 0.f;
	this->camera.center.x = cos(this->pitch) * cos(this->yaw);
	this->camera.center.z = sin(this->pitch) * cos(this->yaw);
	this->view = glm::lookAt(this->camera.eye, this->camera.center, this->camera.up);
	this->updateMvpMatrix();
}

void Presentation::updateCameraPosition(float& center, float& eye, float update)
{
	center += update;
	eye += update;
	this->view = glm::lookAt(this->camera.eye, this->camera.center, this->camera.up);
	this->updateMvpMatrix();
}