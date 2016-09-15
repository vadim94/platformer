#include "ButtonAlignerActor.h"

#include "Stage.h"

const int ButtonAlignerActor::buttonPadding_ = 10;

oxygine::spButton ButtonAlignerActor::AddButton(const std::string& text)
{
	buttons_.push_back(createButton(text));
	addChild(buttons_.back());
	alignButtons();
	return buttons_.back();
}

oxygine::spButton ButtonAlignerActor::createButton(const std::string& text)
{
	oxygine::spButton button = new oxygine::Button();

	oxygine::spTextField textField = createText(text);
	textField->setSize(button->getSize());
	textField->attachTo(button);
	return button;
}

oxygine::spTextField ButtonAlignerActor::createText(const std::string& text)
{
	oxygine::spTextField textField = new oxygine::TextField();

	oxygine::TextStyle style = textField->getStyle();
	style.color = oxygine::Color::Black;
	style.vAlign = oxygine::TextStyle::VALIGN_MIDDLE;
	style.hAlign = oxygine::TextStyle::HALIGN_CENTER;
	style.multiline = true;
	style.fontSize = 20;

	textField->setStyle(style);
	textField->setText(text);

	return textField;
}

void ButtonAlignerActor::alignButtons()
{
	if (buttons_.size() == 0) return;

	const int heightPerButton = buttons_[0]->getHeight() + buttonPadding_;
	const int buttonBlockWidth = buttons_[0]->getWidth();
	const int buttonBlockHeight = heightPerButton * buttons_.size();
	
	const oxygine::Vector2 buttonBlockSize(buttonBlockWidth, buttonBlockHeight);
	setSize(buttonBlockSize);
	
	oxygine::Vector2 buttonBlockTopLeft(0, 0);
	for (auto& button : buttons_)
	{
		button->setPosition(buttonBlockTopLeft);
		buttonBlockTopLeft.y += heightPerButton;
	}
}