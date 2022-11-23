#include "PresentationVoxel.hpp"

PresentationVoxel::PresentationVoxel(engine::SceneManager& sceneManager, Options& options)
	: engine::Scene(sceneManager), options(options)
{
	chunkVertexShader = sceneManager.createShader(GL_VERTEX_SHADER, "./shaders/chunk.vs");
	chunkFragmentShader = sceneManager.createShader(GL_FRAGMENT_SHADER, "./shaders/chunk.fs");
	meshVertexShader = sceneManager.createShader(GL_VERTEX_SHADER, "./shaders/mesh.vs");
	skydomeFragmentShader = sceneManager.createShader(GL_FRAGMENT_SHADER, "./shaders/skydome.fs");

	userInterfaceVertexShader = sceneManager.createShader(GL_VERTEX_SHADER, "./shaders/userInterface.vs");
	userInterfaceFragmentShader = sceneManager.createShader(GL_FRAGMENT_SHADER, "./shaders/userInterface.fs");

	chunkProgram = sceneManager.createProgram();
	skydomeProgram = sceneManager.createProgram();
	userInterfaceProgram = sceneManager.createProgram();

	chunkProgram->addShader(chunkVertexShader);
	chunkProgram->addShader(chunkFragmentShader);
	skydomeProgram->addShader(meshVertexShader);
	skydomeProgram->addShader(skydomeFragmentShader);
	userInterfaceProgram->addShader(userInterfaceVertexShader);
	userInterfaceProgram->addShader(userInterfaceFragmentShader);
	
	sceneManager.linkPrograms();
	sceneManager.deleteShaders();

	float height = glutGet(GLUT_SCREEN_HEIGHT);
	float width = glutGet(GLUT_SCREEN_WIDTH);

	this->projection = glm::perspective(45.0f, 1.0f * width / height, 0.1f, 50.0f);
	
	this->userInterfaceProjection = glm::ortho(0.0f, width, height, 0.0f, -10.0f, 10.0f);

	chunkProgram->createUniform(glUniformMatrix4fv, "projection", 1, GL_FALSE, &this->projection[0][0]);
	chunkProgram->createUniform(glUniformMatrix4fv, "view", 1, GL_FALSE, &this->view[0][0]);
	chunkProgram->createUniform(glUniformMatrix4fv, "model", 1, GL_FALSE, &this->model[0][0]);
	chunkProgram->createUniform(glUniform3fv, "viewPosition", 1, &this->camera.getViewPosition()[0]);

	skydomeProgram->createUniform(glUniformMatrix4fv, "projection", 1, GL_FALSE, &this->projection[0][0]);
	skydomeProgram->createUniform(glUniformMatrix4fv, "view", 1, GL_FALSE, &this->view[0][0]);
	skydomeProgram->createUniform(glUniformMatrix4fv, "model", 1, GL_FALSE, &this->model[0][0]);
	skydomeProgram->createUniform(glUniform1i, "textureSampler", 0);

	userInterfaceProgram->createUniform(glUniformMatrix4fv, "projection", 1, GL_FALSE, &this->userInterfaceProjection[0][0]);
	userInterfaceProgram->createUniform(glUniformMatrix4fv, "model", 1, GL_FALSE, &this->model[0][0]);
	userInterfaceProgram->createUniform(glUniform1i, "textureSampler", 0);

	skyTexture.load("./textures/sky.jpg");

	skydome = this->createObject<Skydome>();
	skydome->setPosition(this->camera.getPosition());
	skydome->setProgram(skydomeProgram);
	skydome->textures.push_back(skyTexture);

	world = this->createObject<World>();
	world->setPosition({ 0.0f, 0.0f, 0.0f });
	world->setProgram(chunkProgram);

	buttonTexture.load("./textures/texture.jpg");

	button = this->createObject<Button>();
	button->setPosition({ 0.0f, 0.0f, 0.0f });
	button->setSize({ 200.0f, 200.0f });
;	button->setProgram(userInterfaceProgram);
	button->textures.push_back(buttonTexture);

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
		this->camera.rotate(update, 0.0f);
		this->view = this->camera.getViewMatrix();
		break;
	}

}

void PresentationVoxel::OnKeyDown(unsigned char key, int x, int y)
{
	const float update = 0.1f;
	switch (key)
	{
	case 'q':
		this->camera.moveAccordingToDirection({ 0.0, update, 0.0 });
		this->view = this->camera.getViewMatrix();
		skydome->setPosition(this->camera.getPosition());
		break;
	case 'e':
		this->camera.moveAccordingToDirection({ 0.0, -update, 0.0 });
		this->view = this->camera.getViewMatrix();
		skydome->setPosition(this->camera.getPosition());
		break;
	case 'w':
		this->camera.moveAccordingToDirection({ 0.0, 0.0, update });
		this->view = this->camera.getViewMatrix();
		skydome->setPosition(this->camera.getPosition());
		break;
	case 's':
		this->camera.moveAccordingToDirection({ 0.0, 0.0, -update });
		this->view = this->camera.getViewMatrix();
		skydome->setPosition(this->camera.getPosition());
		break;
	case 'a':
		this->camera.moveAccordingToDirection({ update, 0.0, 0.0 });
		this->view = this->camera.getViewMatrix();
		skydome->setPosition(this->camera.getPosition());
		break;
	case 'd':
		this->camera.moveAccordingToDirection({ -update, 0.0, 0.0 });
		this->view = this->camera.getViewMatrix();
		skydome->setPosition(this->camera.getPosition());
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