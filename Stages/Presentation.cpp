#include "Presentation.hpp"

Presentation::Presentation(engine::SceneManager& sceneManager, Options& options)
	: engine::Scene(sceneManager), options(options), timeLimit(50000), rotationAngle(0.0f), pause(false)
{
	this->projection = glm::perspective(45.0f, 1.0f * this->options.width / this->options.height, 0.1f, 50.0f);
	this->view = this->camera.getViewMatrix();

	this->initializeShaders();
	this->initializeUserInterface();
	this->initializeObjects();
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
		this->skybox->setPosition(this->camera.getPosition());
		this->rain->setPosition(this->camera.getPosition());
		break;
	case 'e':
		this->camera.moveAccordingToDirection({ 0.0, -update, 0.0 });
		this->view = this->camera.getViewMatrix();
		this->skybox->setPosition(this->camera.getPosition());
		this->rain->setPosition(this->camera.getPosition());
		break;
	case 'w':
		this->camera.moveAccordingToDirection({ 0.0, 0.0, update });
		this->view = this->camera.getViewMatrix();
		this->skybox->setPosition(this->camera.getPosition());
		this->rain->setPosition(this->camera.getPosition());
		break;
	case 's':
		this->camera.moveAccordingToDirection({ 0.0, 0.0, -update });
		this->view = this->camera.getViewMatrix();
		this->skybox->setPosition(this->camera.getPosition());
		this->rain->setPosition(this->camera.getPosition());
		break;
	case 'a':
		this->camera.moveAccordingToDirection({ update, 0.0, 0.0 });
		this->view = this->camera.getViewMatrix();
		this->skybox->setPosition(this->camera.getPosition());
		this->rain->setPosition(this->camera.getPosition());
		break;
	case 'd':
		this->camera.moveAccordingToDirection({ -update, 0.0, 0.0 });
		this->view = this->camera.getViewMatrix();
		this->skybox->setPosition(this->camera.getPosition());
		this->rain->setPosition(this->camera.getPosition());
		break;
	}


}

void Presentation::OnMouseClick(int button, int state, int x, int y)
{
	this->userInterface.mouseClick(button, state, x, y);
}

void Presentation::RefreshDisplay(int t)
{
}

void Presentation::Time(int dt)
{
	static int time = 0;

	if (this->pause)
		return;
	
	if (time % 10000 == 0)
	{
		this->rain->run();
		this->rotationAngle = this->rotationAngle > glm::radians(359.0f) ? glm::radians(0.0f) : this->rotationAngle + glm::radians(1.0f);
	}

	if (time >= this->timeLimit)
	{
		this->water->update(this->rain->isRaining);
		this->skybox->update();	
		time = 0;
	}
	else
	{
		time++;
	}
}

void Presentation::initializeShaders()
{
	this->terrainProgram = sceneManager.createProgram();
	this->rainProgram = sceneManager.createProgram();
	this->waterProgram = sceneManager.createProgram();
	this->skyboxProgram = sceneManager.createProgram();
	engine::Program userInterfaceProgram = sceneManager.createProgram();

	engine::Shader temp_shader = sceneManager.createShader(GL_VERTEX_SHADER, "./shaders/mesh.vs");
	this->terrainProgram->addShader(temp_shader);
	this->waterProgram->addShader(temp_shader);

	temp_shader = sceneManager.createShader(GL_TESS_CONTROL_SHADER, "./shaders/mesh.tc");
	this->terrainProgram->addShader(temp_shader);
	this->waterProgram->addShader(temp_shader);

	temp_shader = sceneManager.createShader(GL_TESS_EVALUATION_SHADER, "./shaders/mesh.te");
	this->terrainProgram->addShader(temp_shader);

	temp_shader = sceneManager.createShader(GL_TESS_EVALUATION_SHADER, "./shaders/water.te");
	this->waterProgram->addShader(temp_shader);

	temp_shader = sceneManager.createShader(GL_FRAGMENT_SHADER, "./shaders/terrain.fs");
	this->terrainProgram->addShader(temp_shader);

	temp_shader = sceneManager.createShader(GL_FRAGMENT_SHADER, "./shaders/water.fs");
	this->waterProgram->addShader(temp_shader);

	temp_shader = sceneManager.createShader(GL_VERTEX_SHADER, "./shaders/rain.vs");
	this->rainProgram->addShader(temp_shader);

	temp_shader = sceneManager.createShader(GL_FRAGMENT_SHADER, "./shaders/rain.fs");
	this->rainProgram->addShader(temp_shader);

	temp_shader = sceneManager.createShader(GL_GEOMETRY_SHADER, "./shaders/rain.gs");
	this->rainProgram->addShader(temp_shader);

	temp_shader = sceneManager.createShader(GL_VERTEX_SHADER, "./shaders/simply.vs");
	this->skyboxProgram->addShader(temp_shader);
	userInterfaceProgram->addShader(temp_shader);

	temp_shader = sceneManager.createShader(GL_FRAGMENT_SHADER, "./shaders/simply.fs");
	this->skyboxProgram->addShader(temp_shader);
	userInterfaceProgram->addShader(temp_shader);

	this->terrainProgram->createUniform(glUniformMatrix4fv, "projection", 1, GL_FALSE, &this->projection[0][0]);
	this->terrainProgram->createUniform(glUniformMatrix4fv, "view", 1, GL_FALSE, &this->view[0][0]);
	this->terrainProgram->createUniform(glUniformMatrix4fv, "model", 1, GL_FALSE, &this->model[0][0]);
	this->terrainProgram->createUniform(glUniform3fv, "viewPosition", 1, &this->camera.getViewPosition()[0]);
	this->terrainProgram->createUniform(glUniform1i, "textureSampler", 0);

	this->rainProgram->createUniform(glUniformMatrix4fv, "projection", 1, GL_FALSE, &this->projection[0][0]);
	this->rainProgram->createUniform(glUniformMatrix4fv, "view", 1, GL_FALSE, &this->view[0][0]);
	this->rainProgram->createUniform(glUniformMatrix4fv, "model", 1, GL_FALSE, &this->model[0][0]);

	this->waterProgram->createUniform(glUniformMatrix4fv, "projection", 1, GL_FALSE, &this->projection[0][0]);
	this->waterProgram->createUniform(glUniformMatrix4fv, "view", 1, GL_FALSE, &this->view[0][0]);
	this->waterProgram->createUniform(glUniformMatrix4fv, "model", 1, GL_FALSE, &this->model[0][0]);
	this->waterProgram->createUniform(glUniform3fv, "viewPosition", 1, &this->camera.getViewPosition()[0]);
	this->waterProgram->createUniform(glUniform1fv, "rotationAngle", 1, &this->rotationAngle);
	this->waterProgram->createUniform(glUniform1i, "textureSampler", 0);

	this->skyboxProgram->createUniform(glUniformMatrix4fv, "projection", 1, GL_FALSE, &this->projection[0][0]);
	this->skyboxProgram->createUniform(glUniformMatrix4fv, "view", 1, GL_FALSE, &this->view[0][0]);
	this->skyboxProgram->createUniform(glUniformMatrix4fv, "model", 1, GL_FALSE, &this->model[0][0]);
	this->skyboxProgram->createUniform(glUniform1i, "textureSampler", 0);

	userInterfaceProgram->createUniform(glUniformMatrix4fv, "model", 1, GL_FALSE, &this->model[0][0]);

	this->userInterface.setProgram(userInterfaceProgram);
}

void Presentation::initializeUserInterface()
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
		this->rain->isRaining = status;
		});
	//temp_button->setPreDrawSettings(buttonPreDrawSettings);
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

void Presentation::initializeObjects()
{
	//auto meshPreDrawSettings = [this](auto mesh) {
	//	this->model = mesh->getModelMatrix();
	//};

	this->texture.load("./textures/noise.jpg");
	this->skyTexture.load("./textures/sky.jpg");

	this->terrain = this->createObject<Terrain>();
	this->terrain->textures.push_back(texture);
	this->terrain->setPosition({ 0.0f, 0.0f, 0.0f });
	this->terrain->setProgram(terrainProgram);
	//this->terrain->setPreDrawSettings(meshPreDrawSettings);

	this->water = this->createObject<Water>(terrain);
	this->water->textures.push_back(texture);
	this->water->setProgram(waterProgram);
	//this->water->setPreDrawSettings(meshPreDrawSettings);

	this->rain = this->createObject<Rain>();
	this->rain->setProgram(rainProgram);
	this->rain->setPosition(this->camera.getPosition());
	//this->rain->setPreDrawSettings(meshPreDrawSettings);

	this->skybox = this->createObject<Skybox>();
	this->skybox->setPosition(this->camera.getPosition());
	this->skybox->setProgram(skyboxProgram);
	this->skybox->textures.push_back(skyTexture);
	//this->skydome->setPreDrawSettings(preDrawSettings);

	this->terrainProgram->createUniform(glUniform3fv, "lightPosition", 2, this->skybox->getLights());
	this->waterProgram->createUniform(glUniform3fv, "lightPosition", 2, this->skybox->getLights());
}