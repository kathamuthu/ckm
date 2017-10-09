/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 4.3.0

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright (c) 2015 - ROLI Ltd.

  ==============================================================================
*/

#ifndef __JUCE_HEADER_2557D757746C7D52__
#define __JUCE_HEADER_2557D757746C7D52__

//[Headers]     -- You can add your own extra header files here --

//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    \cond HIDDEN_SYMBOLS
	An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class GroupBody  : public ProcessorEditorBody,
                   public LabelListener,
                   public ComboBoxListener,
                   public ButtonListener,
                   public SliderListener
{
public:
    //==============================================================================
    GroupBody (ProcessorEditor *p);
    ~GroupBody();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.

	int getBodyHeight() const override { return h; };

	void updateGui() override
	{
		fmStateLabel->setText(dynamic_cast<ModulatorSynthGroup*>(getProcessor())->getFMState(), dontSendNotification);

		if (getProcessor()->getAttribute(ModulatorSynthGroup::EnableFM))
		{
			modSelector->setVisible(true);
			carrierSelector->setVisible(true);

			modSelector->clear(dontSendNotification);
			carrierSelector->clear(dontSendNotification);

			auto offset = (int)ModulatorSynthGroup::InternalChains::numInternalChains;

			for (int i = offset; i < getProcessor()->getNumChildProcessors(); i++)
			{
				modSelector->addItem(getProcessor()->getChildProcessor(i)->getId(), i - offset + 1);
				carrierSelector->addItem(getProcessor()->getChildProcessor(i)->getId(), i - offset + 1);
			}

			modSelector->updateValue();
			carrierSelector->updateValue();


		}
		else
		{
			modSelector->setVisible(false);
			carrierSelector->setVisible(false);
		}

		fmButton->updateValue();

		fadeTimeEditor->setText(String((int)getProcessor()->getAttribute(ModulatorSynth::KillFadeTime)), dontSendNotification);
		voiceAmountEditor->setText(String((int)getProcessor()->getAttribute(ModulatorSynth::VoiceLimit)), dontSendNotification);

	};

    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void labelTextChanged (Label* labelThatHasChanged) override;
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged) override;
    void buttonClicked (Button* buttonThatWasClicked) override;
    void sliderValueChanged (Slider* sliderThatWasMoved) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	int h;
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<Label> fadeTimeLabel;
    ScopedPointer<Label> voiceAmountLabel;
    ScopedPointer<Label> voiceAmountEditor;
    ScopedPointer<Label> fadeTimeEditor;
    ScopedPointer<HiComboBox> carrierSelector;
    ScopedPointer<HiToggleButton> fmButton;
    ScopedPointer<HiComboBox> modSelector;
    ScopedPointer<Label> fmStateLabel;
    ScopedPointer<Label> label;
    ScopedPointer<HiSlider> unisonoSlider;
    ScopedPointer<HiSlider> detuneSlider;
    ScopedPointer<HiSlider> spreadSlider;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GroupBody)
};

//[EndFile] You can add extra defines here...
/** \endcond */
//[/EndFile]

#endif   // __JUCE_HEADER_2557D757746C7D52__
