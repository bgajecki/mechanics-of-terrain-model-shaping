#include "Menu.hpp"

Menu::Menu(engine::SceneManager& sceneManager, Options& options)
	: engine::Scene(sceneManager), options(options)
{
	this->initializeShaders();
	this->initializeUserInterface();
}

void Menu::Display()
{
}

void Menu::Reshape(int width, int height)
{
}

void Menu::Special(int key, int x, int y)
{
}

void Menu::OnKeyDown(unsigned char key, int x, int y)
{
}

void Menu::Motion(int x, int y)
{
	this->mouseMove(x, y);
}

void Menu::OnMouseClick(int button, int state, int x, int y)
{
	this->mouseClick(button, state, x, y);
}

void Menu::RefreshDisplay(int dt)
{
}

void Menu::Time(int dt)
{
}

void Menu::initializeShaders()
{
	this->program = sceneManager.createProgram();

	engine::Shader temp_shader = sceneManager.createShader(GL_VERTEX_SHADER, "./shaders/simply.vs");
	this->program->addShader(temp_shader);

	temp_shader = sceneManager.createShader(GL_FRAGMENT_SHADER, "./shaders/simply.fs");
	this->program->addShader(temp_shader);

	this->program->createUniform(glUniformMatrix4fv, "model", 1, GL_FALSE, &this->model[0][0]);
	this->setProgram(this->program);
}

void Menu::initializeUserInterface()
{
	constexpr float BUTTON_X_POSITION = 0.5f;
	constexpr float BUTTON_Y_POSITION_SCALE = 0.25f;
	constexpr float BUTTON_WIDTH = 0.3f;
	constexpr float BUTTON_HEIGHT = 0.2f;

	this->resize(this->options.width, this->options.height);

	this->presentationMeshTexture.load("./textures/mesh.jpg");
	this->presentationVoxelTexture.load("./textures/voxel.jpg");
	this->exitTexture.load("./textures/exit.jpg");
	this->presentationMeshActiveTexture.load("./textures/meshActive.jpg");
	this->presentationVoxelActiveTexture.load("./textures/voxelActive.jpg");
	this->exitActiveTexture.load("./textures/exitActive.jpg");
	this->backgroundTexture.load("./textures/background.jpg");

	StageSetter* stageSetter = this->options.stageSetter;

	//auto buttonPreDrawSettings = [this](auto button) {
	//	this->model = button->getModelMatrix();
	//};

	Button* temp_button = this->createObject<Button>();
	temp_button->setPosition({ BUTTON_X_POSITION, BUTTON_Y_POSITION_SCALE });
	temp_button->setSize({ BUTTON_WIDTH, BUTTON_HEIGHT });
	temp_button->textures.push_back(presentationMeshTexture);
	temp_button->textures.push_back(presentationMeshActiveTexture);
	temp_button->setCallback([stageSetter](bool& status) {
		stageSetter->setCurrentStageToPresentation();
		status = false;
	});
	//temp_button->setPreDrawSettings(buttonPreDrawSettings);
	this->add(temp_button);

	temp_button = this->createObject<Button>();
	temp_button->setPosition({ BUTTON_X_POSITION, BUTTON_Y_POSITION_SCALE * 2.f });
	temp_button->setSize({ BUTTON_WIDTH, BUTTON_HEIGHT });
	temp_button->textures.push_back(presentationVoxelTexture);
	temp_button->textures.push_back(presentationVoxelActiveTexture);
	temp_button->setCallback([stageSetter](bool& status) {
		stageSetter->setCurrentStageToPresentationVoxel();
		status = false;
	});
	//temp_button->setPreDrawSettings(buttonPreDrawSettings);
	this->add(temp_button);
	

	temp_button = this->createObject<Button>();
	temp_button->setPosition({ BUTTON_X_POSITION, BUTTON_Y_POSITION_SCALE * 3.f });
	temp_button->setSize({ BUTTON_WIDTH, BUTTON_HEIGHT });
	temp_button->textures.push_back(exitTexture);
	temp_button->textures.push_back(exitActiveTexture);
	temp_button->setCallback([](bool& status) {
		glutLeaveMainLoop();
		status = false;
	});
	//temp_button->setPreDrawSettings(buttonPreDrawSettings);
	this->add(temp_button);

	auto backgroundPreDrawSettings = [this](auto background) {
		this->model = background->getModelMatrix();
	};

	Element* background = this->createObject<Element>();
	background->setPosition({ 0.5f, 0.5f });
	background->setSize({ 1.0f, 1.0f });
	background->textures.push_back(backgroundTexture);
	//background->setPreDrawSettings(backgroundPreDrawSettings);
	this->add(background);
}
