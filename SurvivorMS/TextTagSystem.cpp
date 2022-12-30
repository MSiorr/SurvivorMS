#include "stdafx.h"
#include "TextTagSystem.h"

void TextTagSystem::initFonts(std::string fontFile) {

	if (!this->font.loadFromFile(fontFile))
		std::cout << "TAG SYSTEM FONT ERROR" << "\n";
}

void TextTagSystem::initVariables() {
}

void TextTagSystem::initTagTemplates() {

	this->tagTemplates[TAGTYPES::DEFAULT_TAG] = new TextTag(this->font, "", 100.f, 100.f, 0.f, -1.f, sf::Color::White, 40, 100.f, 200.f);
	this->tagTemplates[TAGTYPES::DAMAGE_TAG] = new TextTag(this->font, "", 100.f, 100.f, 0.f, -1.f, sf::Color::Red, 40, 100.f, 200.f);
	this->tagTemplates[TAGTYPES::EXPERIENCE_TAG] = new TextTag(this->font, "", 100.f, 100.f, 0.f, -1.f, sf::Color::Green, 55, 150.f, 250.f);
}

TextTagSystem::TextTagSystem(std::string fontFile) {

	this->initFonts(fontFile);
	this->initVariables();
	this->initTagTemplates();
}

TextTagSystem::~TextTagSystem() {

	for (auto& tag : this->tags) {

		delete tag;
	}

	for (auto& tag : this->tagTemplates) {

		delete tag.second;
	}

}

void TextTagSystem::addTextTag(const unsigned tagType, const float x, const float y, const std::string txt) {

	this->tags.push_back(new TextTag(this->tagTemplates[tagType], x, y, txt));
}

void TextTagSystem::addTextTag(const unsigned tagType, const float x, const float y, const int val) {

	std::stringstream ss;
	ss << val;

	this->tags.push_back(new TextTag(this->tagTemplates[tagType], x, y, ss.str()));
}

void TextTagSystem::addTextTag(const unsigned tagType, const float x, const float y, const float valF) {

	std::stringstream ss;
	ss << valF;

	this->tags.push_back(new TextTag(this->tagTemplates[tagType], x, y, ss.str()));
}

void TextTagSystem::removeTextTag() {
}

void TextTagSystem::update(const float& dt) {

	for (size_t i = 0; i < this->tags.size(); ++i) {

		this->tags[i]->update(dt);


		if (this->tags[i]->canBeRemoved()) {

			delete this->tags[i];
			this->tags.erase(this->tags.begin() + i);
		}
	}

}

void TextTagSystem::render(sf::RenderTarget& target) {

	for (auto& tag : this->tags) {

		tag->render(target);
	}
}
