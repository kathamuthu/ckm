/*  ===========================================================================
*
*   This file is part of HISE.
*   Copyright 2016 Christoph Hart
*
*   HISE is free software: you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation, either version 3 of the License, or
*   (at your option) any later version.
*
*   HISE is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
*
*   Commercial licenses for using HISE in an closed source project are
*   available on request. Please visit the project's website to get more
*   information about commercial licensing:
*
*   http://www.hartinstruments.net/hise/
*
*   HISE is based on the JUCE library,
*   which must be separately licensed for closed source applications:
*
*   http://www.juce.com
*
*   ===========================================================================
*/

/******************************************************************************

BEGIN_JUCE_MODULE_DECLARATION

  ID:               hi_frontend
  vendor:           Hart Instruments
  version:          1.6.0
  name:             HISE Frontend Module
  description:      use this module for compiled plugins
  website:          http://hise.audio
  license:          GPL / Commercial

  dependencies:      juce_audio_basics, juce_audio_devices, juce_audio_formats, juce_audio_processors, juce_core, juce_cryptography, juce_data_structures, juce_events, juce_graphics, juce_gui_basics, juce_gui_extra, juce_opengl, hi_core, hi_dsp, hi_components, hi_sampler, hi_scripting, hi_modules

END_JUCE_MODULE_DECLARATION

******************************************************************************/

#ifndef HI_FRONTEND_INCLUDED
#define HI_FRONTEND_INCLUDED

#include "../hi_modules/hi_modules.h"

#if 0
#if USE_FRONTEND_STATIC_LIB

extern char* getPluginName();
#define JucePlugin_Name getPluginName()

extern char* getVersionString();
#define JucePlugin_VersionString getVersionString()

extern char* getManufacturer();
#define JucePlugin_Manufacturer getManufacturer()

AudioProcessor* createPlugin(ValueTree &presetData, ValueTree &imageData, ValueTree &externalScripts, ValueTree &userPresets);

#endif
#endif


#ifndef USE_FRONTEND
#define USE_FRONTEND 1
#endif

#include "frontend/FrontEndProcessor.h"
#include "frontend/FrontendProcessorEditor.h"

#define USER_PRESET_OFFSET 8192

#if HISE_IOS

#define CREATE_PLUGIN(deviceManager, callback) { LOG_START("Loading embedded instrument data");\
    ValueTree presetData = ValueTree::readFromData(PresetData::preset, PresetData::presetSize);\
    LOG_START("Loading embedded other data")\
    ValueTree externalFiles = hise::PresetHandler::loadValueTreeFromData(PresetData::externalFiles, PresetData::externalFilesSize, true);\
    LOG_START("Creating Frontend Processor")\
    auto fp = new hise::FrontendProcessor(presetData, deviceManager, callback, nullptr, nullptr, nullptr, &externalFiles, nullptr);\
        hise::UserPresetHelpers::extractUserPresets(PresetData::userPresets, PresetData::userPresetsSize);\
    hise::AudioProcessorDriver::restoreSettings(fp);\
    hise::GlobalSettingManager::restoreGlobalSettings(fp);\
    GET_PROJECT_HANDLER(fp->getMainSynthChain()).loadSamplesAfterSetup(); \
    return fp; }

#define CREATE_PLUGIN_WITH_AUDIO_FILES CREATE_PLUGIN // same same


#elif DONT_EMBED_FILES_IN_FRONTEND

#define CREATE_PLUGIN(deviceManager, callback) {ValueTree presetData = ValueTree::readFromData(PresetData::preset, PresetData::presetSize);\
ValueTree externalFiles = hise::PresetHandler::loadValueTreeFromData(PresetData::externalFiles, PresetData::externalFilesSize, true);\
	\
	hise::FrontendProcessor* fp = new hise::FrontendProcessor(presetData, deviceManager, callback, nullptr, nullptr, &externalFiles, nullptr);\
	hise::AudioProcessorDriver::restoreSettings(fp);\
	hise::GlobalSettingManager::restoreGlobalSettings(fp); \
	fp->loadSamplesAfterSetup();\
	return fp;\
}

#define CREATE_PLUGIN_WITH_AUDIO_FILES CREATE_PLUGIN // same same

#else

#define CREATE_PLUGIN(deviceManager, callback) {ValueTree presetData = ValueTree::readFromData(PresetData::preset, PresetData::presetSize);\
	ValueTree externalFiles = hise::PresetHandler::loadValueTreeFromData(PresetData::externalFiles, PresetData::externalFilesSize, true);\
	\
	auto fp = new hise::FrontendProcessor(presetData, deviceManager, callback, nullptr, nullptr, &externalFiles, nullptr);\
	hise::AudioProcessorDriver::restoreSettings(fp);\
	hise::GlobalSettingManager::restoreGlobalSettings(fp); \
	fp->loadSamplesAfterSetup();\
	return fp;\
}

namespace hise
{


struct FrontendFactory
{
	static juce::MemoryInputStream* getEmbeddedData(FileHandlerBase::SubDirectories directory);

	static FrontendProcessor* createPluginWithAudioFiles(juce::AudioDeviceManager* deviceManager, juce::AudioProcessorPlayer* callback);

	static FrontendProcessor* createPlugin(juce::AudioDeviceManager* deviceManager, juce::AudioProcessorPlayer* callback);
};

}

#define CREATE_PLUGIN_WITH_AUDIO_FILES(deviceManager, callback) return hise::FrontendFactory::createPluginWithAudioFiles(deviceManager, callback);

#define BEGIN_EMBEDDED_DATA() juce::MemoryInputStream* hise::FrontendFactory::getEmbeddedData(hise::FileHandlerBase::SubDirectories directory) { switch (directory) {
#define DEFINE_EMBEDDED_DATA(subdirectory, data, size) case subdirectory: return new MemoryInputStream(data, size, false);
#define END_EMBEDDED_DATA() default: jassertfalse; return nullptr; }}

#endif



#endif   // HI_FRONTEND_INCLUDED
