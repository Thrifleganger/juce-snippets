#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    addAndMakeVisible(label);
    label.setText("This text is too long to be entirely visible within this short label component.", juce::dontSendNotification);
    label.setFont(20.f);
    label.getLookAndFeel().setColour(juce::Label::backgroundColourId, juce::Colours::darkgrey);
    setSize (600, 400);
}

MainComponent::~MainComponent()
{
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
}

void MainComponent::resized()
{
    label.setBounds(juce::Rectangle<int>{300, 40}.withCentre(getLocalBounds().getCentre()));
}
