/*
 * ScrollableLabel as showcased in the YouTube video: https://youtu.be/1_NYV8M4qto
 */

#pragma once

#include <JuceHeader.h>

class ScrollableLabel : public juce::Label,
                        public juce::Timer
{
public:
	void mouseEnter(const juce::MouseEvent& event) override
	{
		if (isTextLongerThanWidth)
		{
			juce::Timer::callAfterDelay(delayInMsBeforeScrollStarts, [this]
			{
				startTimerHz(24);
			});
		}
	}

	void mouseExit(const juce::MouseEvent& event) override
	{
		if (isTextLongerThanWidth)
		{
			phase = 0.f;
			animationProgress = 0.f;
			repaint();
		}
	}

	void timerCallback() override
	{
		if (!isMouseOver() || phase >= 1.f)
		{
			stopTimer();
			return;
		}
		phase += 0.02f;
		const auto pi = juce::MathConstants<float>::pi;
		animationProgress = std::cosf(phase * pi - pi) * 0.5f + 0.5f;
		repaint();
	}

	void paint(juce::Graphics& g) override
	{
		const auto labelTextArea = getBorderSize().subtractedFrom(getLocalBounds());
		const auto optimumTextWidth = getFont().getStringWidth(getText());
		isTextLongerThanWidth = optimumTextWidth > labelTextArea.getWidth();

		juce::Rectangle<int> textBounds = labelTextArea;
		if (isTextLongerThanWidth && animationProgress > 0.f)
		{
			const auto xTranslation = optimumTextWidth - labelTextArea.getWidth();
			textBounds = juce::Rectangle<int> {
				labelTextArea.getX() - (int)(xTranslation * animationProgress),
				labelTextArea.getY(),
				optimumTextWidth,
				labelTextArea.getHeight()
			};
		}

		g.setColour(findColour(juce::Label::backgroundColourId));
		g.fillRoundedRectangle(getLocalBounds().toFloat(), 4.f);

		g.setColour(findColour(juce::Label::textColourId));
		g.setFont(getFont());
		g.drawFittedText(getText(), textBounds, getJustificationType(), 1, 1.f);
	}

private:
	float phase{0.f};
	float animationProgress{0.f};
	int delayInMsBeforeScrollStarts{500};
	bool isTextLongerThanWidth{false};
};