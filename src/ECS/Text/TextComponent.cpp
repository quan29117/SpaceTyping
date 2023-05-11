// /*******************************************************************//*
//  * Implementation of the TextComponent class.
//  *
//  *********************************************************************/

#include <headers/ECS/Text/TextComponent.hpp>

TextComponent::TextComponent() {}

TextComponent::~TextComponent() {}

char TextComponent::getFirstChar() {
    if (m_text_ref.size() > 0)
		return m_text_ref[0];
    return '\0';
}

void TextComponent::init() {}

void TextComponent::update() {}

void TextComponent::render() {}

void TextComponent::Shot() {
    /**
		Erase the first char of text_ref when being * hit *
	 */

    if (m_text_ref.size() > 0)
        m_text_ref.erase(0,1);
}