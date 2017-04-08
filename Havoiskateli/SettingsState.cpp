#include "stdafx.h"
#include "SettingsState.h"
#include "ResourceManager.h"
#include "AudioManager.h"


SettingsState::SettingsState(sf::RenderWindow &window) : State(window), m_gui(window)
{
}


SettingsState::~SettingsState()
{
	m_gui.removeAllWidgets();
}

StateCode SettingsState::complete()
{
	if (m_stateCode != StateCode::NONE) {
		m_window->setMouseCursorVisible(false);
		m_gui.removeAllWidgets();
	}
	return m_stateCode;
}

void SettingsState::load()
{
	m_background.emplace_back(MSprite("content/images/main_menu/background_1.png", 0, 0, 1366, 768, 0, 0));
	m_background.emplace_back(MSprite("content/images/main_menu/background_2.png", 0, 0, 1366, 768, 0, 0));
	m_background.emplace_back(MSprite("content/images/main_menu/background_3.png", 0, 0, 1366, 768, 0, 0));
	m_background.emplace_back(MSprite("content/images/main_menu/background_4.png", 0, 0, 1366, 768, 0, 0));
}

void SettingsState::init()
{
	m_window->setMouseCursorVisible(true);
	m_title.setCharacterSize(45);
	m_title.setString("Options");
	m_title.setFont(*ResourceManager::getInstance()->getFont(Fonts::titleFont));
	m_title.setFillColor(sf::Color(255, 251, 75));
	m_title.setPosition(m_window->getSize().x / 2 - m_title.getGlobalBounds().width / 2, 50);

	m_settingsBack.setSize(sf::Vector2f(455, 384));
	m_settingsBack.setFillColor(sf::Color(128, 109, 176, 217));
	m_settingsBack.setPosition(
		m_window->getSize().x / 2 - m_settingsBack.getSize().x / 2,
		m_window->getSize().y / 2 - m_settingsBack.getSize().y / 2);
	createGui();
}

void SettingsState::handleInput(sf::Event & event)
{
	m_gui.handleEvent(event);
	if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape) {
		m_stateCode = StateCode::MENU;
	}
}

void SettingsState::update(float elapsed)
{
	m_timer += sf::seconds(1);
	if (m_timer >= sf::seconds(10000)) {
		m_currentBackground = rand() % 4;
		m_timer = sf::seconds(0);
	}

}

void SettingsState::draw()
{
	m_window->draw(m_background.at(m_currentBackground));
	m_window->draw(m_settingsBack);
	m_window->draw(m_title);
	m_gui.draw();

}

void SettingsState::saveSettings()
{
	//Saving graphics parameters
	tgui::ComboBox::Ptr screenResBox = m_gui.get<tgui::ComboBox>("screenResBox");
	if (screenResBox->getSelectedItem() == "640X480") {
		GameConfig::instance()->setScreenSize(Vector2(640, 480));
	}
	else if (screenResBox->getSelectedItem() == "800X600") {
		GameConfig::instance()->setScreenSize(Vector2(800, 600));
	}
	else if (screenResBox->getSelectedItem() == "1024X768") {
		GameConfig::instance()->setScreenSize(Vector2(1024, 768));
	}
	else if (screenResBox->getSelectedItem() == "1366X768") {
		GameConfig::instance()->setScreenSize(Vector2(1366, 768));
	}

	tgui::CheckBox::Ptr screenModeBox = m_gui.get<tgui::CheckBox>("screenModeBox");
	GameConfig::instance()->setScreenMode(screenModeBox->isChecked());

	tgui::CheckBox::Ptr screenVersSyncBox = m_gui.get<tgui::CheckBox>("screenVertSyncBox");
	GameConfig::instance()->setVerticalSync(screenVersSyncBox->isChecked());

	//Saving audio parameters
	tgui::Slider::Ptr musicSlider = m_gui.get<tgui::Slider>("musicVolume");
	GameConfig::instance()->setMusicVolume(musicSlider->getValue());

	tgui::Slider::Ptr soundSlider = m_gui.get<tgui::Slider>("soundVolume");
	GameConfig::instance()->setSoundVolume(soundSlider->getValue());
	
	m_window->close();
	m_window->create(sf::VideoMode(GameConfig::instance()->getScreenSize().x, GameConfig::instance()->getScreenSize().y), "Havoiskateli", GameConfig::instance()->getScreenMode() ? sf::Style::Fullscreen : sf::Style::Default);
	m_window->setVerticalSyncEnabled(GameConfig::instance()->getVerticalSync());
	m_window->setMouseCursorVisible(false);
	m_stateCode = StateCode::MENU;
}

void SettingsState::createGui()
{
	tgui::Label::Ptr graphicsTitle = tgui::Label::create("Graphics");
	tgui::Label::Ptr screenResLabel = tgui::Label::create("Screen Resolution: ");
	tgui::Label::Ptr screenMode = tgui::Label::create("fullscreen: ");
	tgui::Label::Ptr screenVertSync = tgui::Label::create("Vertical Sync: ");

	tgui::Label::Ptr audioTitle = tgui::Label::create("Audio");
	tgui::Label::Ptr musicVolume = tgui::Label::create("Music Volume: ");
	tgui::Label::Ptr soundsVolume = tgui::Label::create("Sounds Volume: ");

	tgui::ComboBox::Ptr screenResBox = tgui::ComboBox::create();
	tgui::CheckBox::Ptr screenModeBox = tgui::CheckBox::create();
	tgui::CheckBox::Ptr screenVertSyncBox = tgui::CheckBox::create();

	//Screen Labels
	graphicsTitle->setPosition("parent.width / 2 - width / 2", "parent.height / 4");
	screenResLabel->setPosition("parent.width / 2 - 200", "parent.height / 4 + 40");
	screenMode->setPosition("parent.width / 2 - 200", "parent.height / 4 + 80");
	screenVertSync->setPosition("parent.width / 2 - 200", "parent.height / 4 + 120");

	//Audio labels
	audioTitle->setPosition("parent.width / 2 - width / 2", "parent.height / 4 + 160");
	musicVolume->setPosition("parent.width / 2 - 200", "parent.height / 4 + 200");
	soundsVolume->setPosition("parent.width / 2 - 200", "parent.height / 4 + 240");

	//Screen  boxes
	screenResBox->setPosition("parent.width / 2 - screenResBox.width / 2", "parent.height / 4 + 40");
	screenResBox->addItem("640X480");
	screenResBox->addItem("800X600");
	screenResBox->addItem("1024X768");
	screenResBox->addItem("1366X768");
	std::stringstream ss;
	ss << GameConfig::instance()->getScreenSize().x << "X" << GameConfig::instance()->getScreenSize().y;
	screenResBox->setSelectedItem(ss.str());
	screenModeBox->setPosition("parent.width / 2 - width / 2", "parent.height / 4 + 80");
	if (GameConfig::instance()->getScreenMode()) {
		screenModeBox->check();
	}
	else {
		screenModeBox->uncheck();
	}
	screenVertSyncBox->setPosition("parent.width / 2 - width / 2", "parent.height / 4 + 120");
	if (GameConfig::instance()->getVerticalSync()) {
		screenVertSyncBox->check();
	}
	else {
		screenVertSyncBox->uncheck();
	}

	//Audio boxes
	auto musicSlider = tgui::Slider::create();
	musicSlider->setPosition("parent.width / 2", "parent.height / 4 + 200");
	musicSlider->setSize(200, 18);
	musicSlider->setValue(GameConfig::instance()->getMusicVolume() / 10);
	musicSlider->connect("ValueChanged", [&](int newValue) { AudioManager::instance()->changeVolume(newValue * 10); });

	auto soundSlider = tgui::Slider::create();
	soundSlider->setPosition("parent.width / 2", "parent.height / 4 + 240");
	soundSlider->setSize(200, 18);
	soundSlider->setValue(GameConfig::instance()->getSoundVolume() / 10);

	//Buttons
	auto saveButton = tgui::Button::create();
	saveButton->setPosition("parent.width / 2 - 200", "parent.height / 4 + 320");
	saveButton->setText("Save");
	saveButton->setSize(100, 30);
	saveButton->connect("pressed", [&]() { this->saveSettings(); });

	auto backButton = tgui::Button::create();
	backButton->setPosition("parent.width / 2 + 100", "parent.height / 4 + 320");
	backButton->setText("Back");
	backButton->setSize(100, 30);
	backButton->connect("pressed", [=]() { m_stateCode = StateCode::MENU; });

	//Adding to gui
	m_gui.add(graphicsTitle);
	m_gui.add(screenResLabel);
	m_gui.add(screenMode);
	m_gui.add(screenVertSync);
	m_gui.add(audioTitle);
	m_gui.add(musicVolume);
	m_gui.add(soundsVolume);
	m_gui.add(screenResBox, "screenResBox");
	m_gui.add(screenModeBox, "screenModeBox");
	m_gui.add(screenVertSyncBox, "screenVertSyncBox");
	m_gui.add(musicSlider, "musicVolume");
	m_gui.add(soundSlider, "soundVolume");
	m_gui.add(saveButton);
	m_gui.add(backButton);
}
