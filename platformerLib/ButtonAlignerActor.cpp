#include "ButtonAlignerActor.h"

#include "Stage.h"

#include "ResourceSingleton.h"

const int ButtonAlignerActor::kButtonPadding = 10;

oxygine::spButton ButtonAlignerActor::AddButton(const std::string& text)
{
    buttons_.push_back(CreateButton(text));
    addChild(buttons_.back());
    AlignButtons();
    return buttons_.back();
}

oxygine::spButton ButtonAlignerActor::CreateButton(const std::string& text)
{
    oxygine::spButton button = new oxygine::Button();
    button->setResAnim(ResourceSingleton::GetRes().getResAnim("button"));

    oxygine::spTextField text_field = CreateText(text);
    text_field->setSize(button->getSize());
    text_field->attachTo(button);
    return button;
}

oxygine::spTextField ButtonAlignerActor::CreateText(const std::string& text)
{
    oxygine::spTextField text_field = new oxygine::TextField();

    oxygine::TextStyle style = text_field->getStyle();
    style.color = oxygine::Color::Black;
    style.vAlign = oxygine::TextStyle::VALIGN_MIDDLE;
    style.hAlign = oxygine::TextStyle::HALIGN_MIDDLE;
    style.multiline = true;
    style.fontSize = 20;
    style.font = ResourceSingleton::GetRes().getResFont("comic_sans");

    text_field->setStyle(style);
    text_field->setText(text);

    return text_field;
}

void ButtonAlignerActor::AlignButtons()
{
    if (buttons_.size() == 0) return;

    const float height_per_button = buttons_[0]->getHeight() + kButtonPadding;
    const float button_block_width = buttons_[0]->getWidth();
    const float button_block_height = height_per_button * buttons_.size();
    
    const oxygine::Vector2 button_blocksize(button_block_width, button_block_height);
    setSize(button_blocksize);
    
    oxygine::Vector2 button_block_top_left(0, 0);
    for (auto& button : buttons_)
    {
        button->setPosition(button_block_top_left);
        button_block_top_left.y += height_per_button;
    }
}