#include "PresentationVoxel.hpp"

PresentationVoxel::PresentationVoxel(engine::SceneManager& sceneManager, Options& options)
	: engine::Scene(sceneManager), options(options), timeLimit(50000), pause(false)
{
	this->projection = glm::perspective(45.0f, 1.0f * this->options.width / this->options.height, 0.1f, 50.0f);
	this->view = this->camera.getViewMatrix();

	this->initializeShaders();
	this->initializeUserInterface();
	this->initializeObjects();
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
		this->skybox->setPosition(this->camera.getPosition());
		break;
	case 'e':
		this->camera.moveAccordingToDirection({ 0.0, -update, 0.0 });
		this->view = this->camera.getViewMatrix();
		this->skybox->setPosition(this->camera.getPosition());
		break;
	case 'w':
		this->camera.moveAccordingToDirection({ 0.0, 0.0, update });
		this->view = this->camera.getViewMatrix();
		this->skybox->setPosition(this->camera.getPosition());
		break;
	case 's':
		this->camera.moveAccordingToDirection({ 0.0, 0.0, -update });
		this->view = this->camera.getViewMatrix();
		this->skybox->setPosition(this->camera.getPosition());
		break;
	case 'a':
		this->camera.moveAccordingToDirection({ update, 0.0, 0.0 });
		this->view = this->camera.getViewMatrix();
		this->skybox->setPosition(this->camera.getPosition());
		break;
	case 'd':
		this->camera.moveAccordingToDirection({ -update, 0.0, 0.0 });
		this->view = this->camera.getViewMatrix();
		this->skybox->setPosition(this->camera.getPosition());
		break;
	}


}

void PresentationVoxel::OnMouseClick(int button, int state, int x, int y)
{
	this->userInterface.mouseClick(button, state, x, y);
}

void PresentationVoxel::RefreshDisplay(int t)
{
}

void PresentationVoxel::Time(int dt)
{
	static int time = 0;

	if (this->pause)
		return;

	if (time >= this->timeLimit)
	{
		this->world->update(dt);
		this->skybox->update();
		time = 0;
	}
	else
	{
		time++;
	}
}

void PresentationVoxel::initializeShaders()
{
	this->chunkProgram = sceneManager.createProgram();
	this->skyboxProgram = sceneManager.createProgram();
	engine::Program userInterfaceProgram = sceneManager.createProgram();

	engine::Shader temp_shader = sceneManager.createShader(GL_VERTEX_SHADER, "./shaders/chunk.vs");
	this->chunkProgram->addShader(temp_shader);

	temp_shader = sceneManager.createShader(GL_FRAGMENT_SHADER, "./shaders/chunk.fs");
	this->chunkProgram->addShader(temp_shader);

	temp_shader = sceneManager.createShader(GL_VERTEX_SHADER, "./shaders/simply.vs");
	this->skyboxProgram->addShader(temp_shader);
	userInterfaceProgram->addShader(temp_shader);

	temp_shader = sceneManager.createShader(GL_FRAGMENT_SHADER, "./shaders/simply.fs");
	this->skyboxProgram->addShader(temp_shader);
	userInterfaceProgram->addShader(temp_shader);

	this->chunkProgram->createUniform(glUniformMatrix4fv, "projection", 1, GL_FALSE, &this->projection[0][0]);
	this->chunkProgram->createUniform(glUniformMatrix4fv, "view", 1, GL_FALSE, &this->view[0][0]);
	this->chunkProgram->createUniform(glUniformMatrix4fv, "model", 1, GL_FALSE, &this->model[0][0]);
	this->chunkProgram->createUniform(glUniform3fv, "viewPosition", 1, &this->camera.getViewPosition()[0]);

	this->skyboxProgram->createUniform(glUniformMatrix4fv, "projection", 1, GL_FALSE, &this->projection[0][0]);
	this->skyboxProgram->createUniform(glUniformMatrix4fv, "view", 1, GL_FALSE, &this->view[0][0]);
	this->skyboxProgram->createUniform(glUniformMatrix4fv, "model", 1, GL_FALSE, &this->model[0][0]);
	this->skyboxProgram->createUniform(glUniform1i, "textureSampler", 0);

	userInterfaceProgram->createUniform(glUniformMatrix4fv, "model", 1, GL_FALSE, &this->model[0][0]);

	this->userInterface.setProgram(userInterfaceProgram);
}

void PresentationVoxel::initializeUserInterface()
{
	this->userInterface.resize(this->options.width, this->options.height);
	this->rainOffTexture.load("./textures/rainOff.jpg");
	this->rainOnTexture.load("./textures/rainOn.jpg");
	this->pauseTexture.load("./textures/pause.png");
	this->playTexture.load("./textures/play.png");
	this->playx2Texture.load("./textures/playx2.png");
	this->playx3Texture.load("./textures/playx3.png");

	//auto buttonPreDrawSettings = [this](auto button) {
	//	this->model = button->getModelMatrix();
	//};
	
	Button* temp_button = this->createObject<Button>();
	temp_button->setPosition({ 0.03f, 0.02f });
	temp_button->setSize({ 0.05f, 0.03f });
	temp_button->textures.push_back(this->rainOffTexture);
	temp_button->textures.push_back(this->rainOnTexture);
	temp_button->setCallback([this](bool status) {
		this->world->isRaining = status;
	});
	/*temp_button->setPreDrawSettings(buttonPreDrawSettings);*/
	this->userInterface.add(temp_button);

	temp_button = this->createObject<Button>();
	temp_button->setPosition({ 0.015f, 0.06f });
	temp_button->setSize({ 0.015f, 0.025f });
	temp_button->textures.push_back(this->pauseTexture);
	temp_button->setCallback([this](bool status) {
		this->pause = true;
		});
	this->userInterface.add(temp_button);

	temp_button = this->createObject<Button>();
	temp_button->setPosition({ 0.035f, 0.06f });
	temp_button->setSize({ 0.015f, 0.025f });
	temp_button->textures.push_back(this->playTexture);
	temp_button->setCallback([this](bool status) {
		this->timeLimit = 50000;
		this->pause = false;
		});
	this->userInterface.add(temp_button);

	temp_button = this->createObject<Button>();
	temp_button->setPosition({ 0.055f, 0.06f });
	temp_button->setSize({ 0.02f, 0.025f });
	temp_button->textures.push_back(this->playx2Texture);
	temp_button->setCallback([this](bool status) {
		this->timeLimit = 25000;
		this->pause = false;
		});
	this->userInterface.add(temp_button);

	temp_button = this->createObject<Button>();
	temp_button->setPosition({ 0.080f, 0.06f });
	temp_button->setSize({ 0.025f, 0.025f });
	temp_button->textures.push_back(this->playx3Texture);
	temp_button->setCallback([this](bool status) {
		this->timeLimit = 16666;
		this->pause = false;
		});
	this->userInterface.add(temp_button);
}

void PresentationVoxel::initializeObjects()
{
	//auto preDrawSettings = [this](auto object) {
	//	this->model = object->getModelMatrix();
	//};

	this->skyTexture.load("./textures/sky.jpg");

	this->skybox = this->createObject<Skybox>();
	this->skybox->setPosition(this->camera.getPosition());
	this->skybox->setProgram(skyboxProgram);
	this->skybox->textures.push_back(skyTexture);
	//this->skydome->setPreDrawSettings(preDrawSettings);

	this->chunkProgram->createUniform(glUniform3fv, "lightPosition", 2, this->skybox->getLights());

	this->world = this->createObject<World>();
	this->world->setPosition({ 0.0f, 0.0f, 0.0f });
	this->world->setProgram(chunkProgram);
	//this->world->setPreDrawSettings(preDrawSettings);
}
