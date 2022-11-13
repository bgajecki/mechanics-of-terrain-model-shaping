#include "PresentationVoxel.hpp"


PresentationVoxel::PresentationVoxel(engine::SceneManager& sceneManager, Options& options)
	: engine::Scene(sceneManager), options(options)
{
	chunkVertexShader = sceneManager.createShader(GL_VERTEX_SHADER, "./shaders/chunk.vs");
	chunkFragmentShader = sceneManager.createShader(GL_FRAGMENT_SHADER, "./shaders/chunk.fs");

	chunkProgram = sceneManager.createProgram();

	chunkProgram->addShader(chunkVertexShader);
	chunkProgram->addShader(chunkFragmentShader);
	
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

	chunkProgram->createUniform(glUniformMatrix4fv, "mvp", 1, GL_FALSE, &this->mvp[0][0]);
	chunkProgram->createUniform(glUniform3fv, "viewPosition", 1, &this->camera.eye[0]);

	world = this->createObject<World>();
	world->refresh();
	world->program = chunkProgram;

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	//glPolygonMode(GL_FRONT, GL_LINE);
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);
}

void PresentationVoxel::Display()
{
}

void PresentationVoxel::Reshape(int width, int height)
{
}

void PresentationVoxel::Special(int key, int x, int y)
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

void PresentationVoxel::OnKeyDown(unsigned char key, int x, int y)
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

void PresentationVoxel::OnMouseClick(int button, int state, int x, int y)
{
}

void PresentationVoxel::RefreshDisplay(int t)
{
}

void PresentationVoxel::Time(int t)
{
	world->update(t);
}

void PresentationVoxel::rotateYaw(float angle)
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

void PresentationVoxel::rotatePitch(float angle)
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

void PresentationVoxel::updateCameraPosition(float& center, float& eye, float update)
{
	center += update;
	eye += update;
	this->view = glm::lookAt(this->camera.eye, this->camera.center, this->camera.up);
	this->updateMvpMatrix();
}