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
 *   along with HISE.  If not, see <http://www.gnu.org/licenses/>.
 *
 *   Commercial licenses for using HISE in an closed source project are
 *   available on request. Please visit the project's website to get more
 *   information about commercial licensing:
 *
 *   http://www.hise.audio/
 *
 *   HISE is based on the JUCE library,
 *   which must be separately licensed for closed source applications:
 *
 *   http://www.juce.com
 *
 *   ===========================================================================
 */

 namespace hise { using namespace juce;
 
// This is a autogenerated file that contains the template for the plugin exporter .jucer file

static const unsigned char projectTemplate_jucer_lines[] =
"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\r\n"
"\r\n"
"<JUCERPROJECT id=\"Tw64Zd\" name=\"%NAME%\" projectType=\"audioplug\" version=\"%VERSION%\"\r\n"
"              bundleIdentifier=\"%BUNDLE_ID%\" includeBinaryInAppConfig=\"1\" buildVST=\"%BUILD_VST%\"\r\n"
"              buildVST3=\"%BUILD_VST3%\" buildAU=\"%BUILD_AU%\" buildAUv3=\"%BUILD_AUV3%\" buildStandalone=\"%BUILD_AUV3%\" buildRTAS=\"0\" buildAAX=\"%BUILD_AAX%\" pluginName=\"%NAME%\"\r\n"
"              pluginDesc=\"%NAME%\" pluginManufacturer=\"%COMPANY%\" pluginManufacturerCode=\"%MC%\"\r\n"
"              pluginCode=\"%PC%\" pluginChannelConfigs=\"%CHANNEL_CONFIG%\" pluginIsSynth=\"%PLUGINISSYNTH%\"\r\n"
"              pluginWantsMidiIn=\"%PLUGINWANTSMIDIIN\" pluginProducesMidiOut=\"0\" pluginIsMidiEffectPlugin=\"0\"\r\n"
"              pluginEditorRequiresKeys=\"1\" pluginAUExportPrefix=\"DemoProjectAU\"\r\n"
"              pluginRTASCategory=\"\" aaxIdentifier=\"%AAX_IDENTIFIER%\"\r\n"
"              pluginAAXCategory=\"%AAX_CATEGORY%\" jucerVersion=\"5.2.0\"\r\n"
"              companyName=\"%COMPANY%\" companyWebsite=\"%COMPANY_WEBSITE%\" companyCopyright=\"%COMPANY_COPYRIGHT%\""
"   displaySplashScreen=\"0\""
"     reportAppUsage=\"0\" splashScreenColour=\"Dark\" enableIAA=\"1\" cppLanguageStandard=\"14\">\r\n"
"  <MAINGROUP id=\"SLR7uY\" name=\"%NAME%\">\r\n"
"    <GROUP id=\"{122C85F1-8B09-257A-B636-113E3EAC258A}\" name=\"Source\">\r\n"
"      <FILE id=\"eLP6Ii\" name=\"balanceKnob_200.png\" compile=\"0\" resource=\"1\"\r\n"
"            file=\"Source/Images/balanceKnob_200.png\"/>\r\n"
"	   <FILE id=\"O9wjCd\" name=\"FrontendKnob_Bipolar.png\" compile=\"0\" resource=\"1\""
"            file=\"Source/Images/FrontendKnob_Bipolar.png\"/>"
"	   <FILE id=\"UAxUWd\" name=\"FrontendKnob_Unipolar.png\" compile=\"0\" resource=\"1\""
"            file=\"Source/Images/FrontendKnob_Unipolar.png\"/>"
"	   <FILE id=\"KmyOlv\" name=\"infoError.png\" compile=\"0\" resource=\"1\" file=\"Source/Images/infoError.png\"/>\r\n"
"      <FILE id=\"CNpA5r\" name=\"infoInfo.png\" compile=\"0\" resource=\"1\" file=\"Source/Images/infoInfo.png\"/>\r\n"
"      <FILE id=\"MjbOy3\" name=\"infoQuestion.png\" compile=\"0\" resource=\"1\"\r\n"
"            file=\"Source/Images/infoQuestion.png\"/>\r\n"
"      <FILE id=\"zsTpOz\" name=\"infoWarning.png\" compile=\"0\" resource=\"1\" file=\"Source/Images/infoWarning.png\"/>\r\n"
"      <FILE id=\"d1rhrw\" name=\"knobEmpty_200.png\" compile=\"0\" resource=\"1\"\r\n"
"            file=\"Source/Images/knobEmpty_200.png\"/>\r\n"
"      <FILE id=\"u2SLs3\" name=\"knobModulated_200.png\" compile=\"0\" resource=\"1\"\r\n"
"            file=\"Source/Images/knobModulated_200.png\"/>\r\n"
"      <FILE id=\"rTpn8D\" name=\"knobUnmodulated_200.png\" compile=\"0\" resource=\"1\"\r\n"
"            file=\"Source/Images/knobUnmodulated_200.png\"/>\r\n"
"      <FILE id=\"jJzDA2\" name=\"CopyProtection.cpp\" compile=\"1\" resource=\"0\" file=\"Source/CopyProtection.cpp\"/>\r\n"
"      <FILE id=\"AOT2K8\" name=\"Plugin.cpp\" compile=\"1\" resource=\"0\" file=\"Source/Plugin.cpp\"/>\r\n"
"      <FILE id=\"esGQuC\" name=\"PresetData.cpp\" compile=\"1\" resource=\"0\" file=\"Source/PresetData.cpp\"/>\r\n"
"      <FILE id=\"q8WZ82\" name=\"PresetData.h\" compile=\"0\" resource=\"0\" file=\"Source/PresetData.h\"/>\r\n"
"      <FILE id=\"jjzOA2\" name=\"toggle_200.png\" compile=\"0\" resource=\"1\" file=\"Source/Images/toggle_200.png\"/>\r\n"
"%ADDITIONAL_FILES%"
"    </GROUP>\r\n"
"  </MAINGROUP>\r\n"
"  <EXPORTFORMATS>\r\n"
"    <%VS_VERSION% targetFolder=\"Builds/%TARGET_FOLDER%\" vstLegacyFolder=\"%VSTSDK_FOLDER%\" aaxFolder=\"%AAX_PATH%\" \r\n"
"            IPPLibrary=\"%IPP_WIN_SETTING%\" extraDefs=\"%PLUGIN_CHANNEL_AMOUNT%&#10;%EXTRA_DEFINES_WIN%\" >\r\n"
"      <CONFIGURATIONS>\r\n"
"        <CONFIGURATION name=\"Debug\" winWarningLevel=\"4\" generateManifest=\"1\" winArchitecture=\"32-bit\"\r\n"
"                       libraryPath=\"%AAX_DEBUG_LIB%;%WIN_STATIC_LIB_FOLDER_D32%/\" isDebug=\"1\" optimisation=\"1\" targetName=\"%NAME%_Debug x86\" binaryPath=\"Compiled/\" useRuntimeLibDLL=\"0\" prebuildCommand=\"%PREBUILD_COMMAND%\"/>\r\n"
"        <CONFIGURATION name=\"Debug\" winWarningLevel=\"4\" generateManifest=\"1\" winArchitecture=\"x64\"\r\n"
"                       isDebug=\"1\" optimisation=\"1\" targetName=\"%NAME%_Debug_x64\"\r\n"
"                       libraryPath=\"%AAX_DEBUG_LIB%;%WIN_STATIC_LIB_FOLDER_D64%\" binaryPath=\"Compiled/\" useRuntimeLibDLL=\"0\" prebuildCommand=\"%PREBUILD_COMMAND%\"/>\r\n"
"        <CONFIGURATION name=\"Release\" winWarningLevel=\"4\" generateManifest=\"1\" winArchitecture=\"32-bit\"\r\n"
"                       libraryPath=\"%AAX_RELEASE_LIB%;%WIN_STATIC_LIB_FOLDER_R32%\" isDebug=\"0\" optimisation=\"3\" targetName=\"%NAME% x86\" binaryPath=\"Compiled/\" useRuntimeLibDLL=\"0\" prebuildCommand=\"%PREBUILD_COMMAND%\"/>\r\n"
"        <CONFIGURATION name=\"Release\" winWarningLevel=\"4\" generateManifest=\"1\"\r\n"
"                       winArchitecture=\"x64\" isDebug=\"0\" optimisation=\"3\" targetName=\"%NAME% x64\"\r\n"
"                       libraryPath=\"%AAX_RELEASE_LIB%;%WIN_STATIC_LIB_FOLDER_R64%\" binaryPath=\"Compiled/\" useRuntimeLibDLL=\"0\" prebuildCommand=\"%PREBUILD_COMMAND%\"/>\r\n"
"      </CONFIGURATIONS>\r\n"
"      <MODULEPATHS>\r\n"
"        <MODULEPATH id=\"juce_core\" path=\"%JUCE_PATH%\"/>\r\n"
"        <MODULEPATH id=\"juce_events\" path=\"%JUCE_PATH%\"/>\r\n"
"        <MODULEPATH id=\"juce_graphics\" path=\"%JUCE_PATH%\"/>\r\n"
"        <MODULEPATH id=\"juce_data_structures\" path=\"%JUCE_PATH%\"/>\r\n"
"        <MODULEPATH id=\"juce_dsp\" path=\"%JUCE_PATH%\"/>\r\n"
"        <MODULEPATH id=\"juce_gui_basics\" path=\"%JUCE_PATH%\"/>\r\n"
"        <MODULEPATH id=\"juce_gui_extra\" path=\"%JUCE_PATH%\"/>\r\n"
"        <MODULEPATH id=\"juce_cryptography\" path=\"%JUCE_PATH%\"/>\r\n"
"        <MODULEPATH id=\"juce_audio_basics\" path=\"%JUCE_PATH%\"/>\r\n"
"        <MODULEPATH id=\"juce_audio_devices\" path=\"%JUCE_PATH%\"/>\r\n"
"        <MODULEPATH id=\"juce_audio_formats\" path=\"%JUCE_PATH%\"/>\r\n"
"        <MODULEPATH id=\"juce_audio_processors\" path=\"%JUCE_PATH%\"/>\r\n"
"        <MODULEPATH id=\"juce_audio_plugin_client\" path=\"%JUCE_PATH%\"/>\r\n"
"        <MODULEPATH id=\"juce_product_unlocking\" path=\"%JUCE_PATH%\"/>\r\n"
"        <MODULEPATH id=\"juce_audio_utils\" path=\"%JUCE_PATH%\"/>\r\n"
"        <MODULEPATH id=\"juce_opengl\" path=\"%JUCE_PATH%\"/>\r\n"
"        <MODULEPATH id=\"hi_dsp_library\" path=\"%HISE_PATH%\"/>\r\n"
"        <MODULEPATH id=\"hi_frontend\" path=\"%HISE_PATH%\"/>\r\n"
"        <MODULEPATH id=\"hi_modules\" path=\"%HISE_PATH%\"/>\r\n"
"        <MODULEPATH id=\"hi_scripting\" path=\"%HISE_PATH%\"/>\r\n"
"        <MODULEPATH id=\"hi_core\" path=\"%HISE_PATH%\"/>\r\n"
"        <MODULEPATH id=\"hi_lac\" path=\"%HISE_PATH%\"/>\r\n"
"		 <MODULEPATH id=\"hi_sampler\" path=\"%HISE_PATH%\"/>\r\n"
"	     <MODULEPATH id=\"hi_components\" path=\"%HISE_PATH%\"/>\r\n"
"        <MODULEPATH id=\"hi_dsp\" path=\"%HISE_PATH%\"/>\r\n"
"        <MODULEPATH id=\"hi_zstd\" path=\"%HISE_PATH%\"/>\r\n"
"        <MODULEPATH id=\"hi_streaming\" path=\"%HISE_PATH%\"/>\r\n"
"        <MODULEPATH id=\"hi_tools\" path=\"%HISE_PATH%\"/>\r\n"
"        <MODULEPATH id=\"stk_wrapper\" path=\"%HISE_PATH%\"/>\r\n"
"      </MODULEPATHS>\r\n"
"    </%VS_VERSION%>\r\n"
"    <XCODE_MAC targetFolder=\"Builds/MacOSX\"  vstLegacyFolder=\"%VSTSDK_FOLDER%\"  aaxFolder=\"%AAX_PATH%\" extraCompilerFlags=\"-Wno-reorder -Wno-inconsistent-missing-override\"\r\n"
"               extraLinkerFlags=\"%IPP_COMPILER_FLAGS% %OSX_STATIC_LIBS%\" extraDefs=\"%PLUGIN_CHANNEL_AMOUNT%&#10;%EXTRA_DEFINES_OSX%\">\r\n"
"                \r\n"
"      <CONFIGURATIONS>\r\n"
"        <CONFIGURATION name=\"Debug\" osxSDK=\"default\" osxCompatibility=\"10.7 SDK\" osxArchitecture=\"%MACOS_ARCHITECTURE%\"\r\n"
"                       isDebug=\"1\" optimisation=\"1\" enablePluginBinaryCopyStep=\"%COPY_PLUGIN%\" targetName=\"%NAME% Debug\" headerPath=\"%IPP_HEADER%\"\r\n"
"                       libraryPath=\"%IPP_LIBRARY%;%AAX_DEBUG_LIB%\" cppLibType=\"libc++\"/>\r\n"
"        <CONFIGURATION name=\"Release\" osxSDK=\"default\" osxCompatibility=\"10.7 SDK\" osxArchitecture=\"%MACOS_ARCHITECTURE%\"\r\n"
"                       isDebug=\"0\" optimisation=\"3\" enablePluginBinaryCopyStep=\"%COPY_PLUGIN%\" targetName=\"%NAME%\" headerPath=\"%IPP_HEADER%\"\r\n"
"                       libraryPath=\"%IPP_LIBRARY%;%AAX_RELEASE_LIB%\" cppLibType=\"libc++\" linkTimeOptimisation=\"1\"\r\n"
"                       cppLanguageStandard=\"c++11\" stripLocalSymbols=\"1\"/>\r\n"
"      </CONFIGURATIONS>\r\n"
"      <MODULEPATHS>\r\n"
"        <MODULEPATH id=\"juce_product_unlocking\" path=\"%JUCE_PATH%\"/>\r\n"
"        <MODULEPATH id=\"juce_gui_extra\" path=\"%JUCE_PATH%\"/>\r\n"
"        <MODULEPATH id=\"juce_gui_basics\" path=\"%JUCE_PATH%\"/>\r\n"
"        <MODULEPATH id=\"juce_graphics\" path=\"%JUCE_PATH%\"/>\r\n"
"        <MODULEPATH id=\"juce_events\" path=\"%JUCE_PATH%\"/>\r\n"
"        <MODULEPATH id=\"juce_data_structures\" path=\"%JUCE_PATH%\"/>\r\n"
"        <MODULEPATH id=\"juce_dsp\" path=\"%JUCE_PATH%\"/>\r\n"
"        <MODULEPATH id=\"juce_cryptography\" path=\"%JUCE_PATH%\"/>\r\n"
"        <MODULEPATH id=\"juce_core\" path=\"%JUCE_PATH%\"/>\r\n"
"        <MODULEPATH id=\"juce_audio_utils\" path=\"%JUCE_PATH%\"/>\r\n"
"        <MODULEPATH id=\"juce_audio_processors\" path=\"%JUCE_PATH%\"/>\r\n"
"        <MODULEPATH id=\"juce_audio_plugin_client\" path=\"%JUCE_PATH%\"/>\r\n"
"        <MODULEPATH id=\"juce_audio_formats\" path=\"%JUCE_PATH%\"/>\r\n"
"        <MODULEPATH id=\"juce_audio_devices\" path=\"%JUCE_PATH%\"/>\r\n"
"        <MODULEPATH id=\"juce_audio_basics\" path=\"%JUCE_PATH%\"/>\r\n"
"        <MODULEPATH id=\"juce_opengl\" path=\"%JUCE_PATH%\"/>\r\n"
"        <MODULEPATH id=\"hi_modules\" path=\"%HISE_PATH%\"/>\r\n"
"        <MODULEPATH id=\"hi_dsp_library\" path=\"%HISE_PATH%\"/>\r\n"
"        <MODULEPATH id=\"hi_frontend\" path=\"%HISE_PATH%\"/>\r\n"
"        <MODULEPATH id=\"hi_scripting\" path=\"%HISE_PATH%\"/>\r\n"
"        <MODULEPATH id=\"hi_core\" path=\"%HISE_PATH%\"/>\r\n"
"        <MODULEPATH id=\"hi_lac\" path=\"%HISE_PATH%\"/>\r\n"
"		 <MODULEPATH id=\"hi_sampler\" path=\"%HISE_PATH%\"/>\r\n"
"	     <MODULEPATH id=\"hi_components\" path=\"%HISE_PATH%\"/>\r\n"
"        <MODULEPATH id=\"hi_dsp\" path=\"%HISE_PATH%\"/>\r\n"
"        <MODULEPATH id=\"hi_zstd\" path=\"%HISE_PATH%\"/>\r\n"
"        <MODULEPATH id=\"hi_streaming\" path=\"%HISE_PATH%\"/>\r\n"
"        <MODULEPATH id=\"hi_tools\" path=\"%HISE_PATH%\"/>\r\n"
"        <MODULEPATH id=\"stk_wrapper\" path=\"%HISE_PATH%\"/>\r\n"
"      </MODULEPATHS>\r\n"
"    </XCODE_MAC>\r\n"
"    <XCODE_IPHONE targetFolder=\"Builds/iOS\" iosScreenOrientation=\"landscape\" extraCompilerFlags=\"-Wno-reorder -Wno-inconsistent-missing-override\" extraLinkerFlags=\"%OSX_STATIC_LIBS%\" extraDefs=\"%EXTRA_DEFINES_IOS%&#10;USE_IPP=0&#10;HISE_IOS=1&#10;JUCE_USE_CUSTOM_PLUGIN_STANDALONE_APP=1&#10;USE_VDSP_FFT=1\" %ICON_FILE% \r\n"
"                  UIStatusBarHidden=\"1\" iosBackgroundAudio=\"1\" iosBackgroundBle=\"0\""
"   customXcodeResourceFolders=\"../Samples\n../Images\nEmbeddedResources\n../UserPresets\""
"   iosAppGroups=\"%USE_APP_GROUPS%\" iosAppGroupsId=\"%APP_GROUP_ID%\""
"   iosAppExtensionDuplicateResourcesFolder=\"0\""
"   iosDevelopmentTeamID=\"%DEVELOPMENT_TEAM_ID%\" iosDeviceFamily=\"%TARGET_FAMILY%\">\r\n"
"      <CONFIGURATIONS>\r\n"
"        <CONFIGURATION name=\"Debug\" iosCompatibility=\"9.0\" isDebug=\"1\" optimisation=\"1\"\r\n"
"                       targetName=\"%NAME%\" cppLanguageStandard=\"c++11\" cppLibType=\"libc++\"/>\r\n"
"        <CONFIGURATION name=\"Release\" iosCompatibility=\"9.0\" isDebug=\"0\" optimisation=\"3\"\r\n"
"                       targetName=\"%NAME%\" cppLanguageStandard=\"c++11\" cppLibType=\"libc++\"\r\n"
"                       linkTimeOptimisation=\"1\" />\r\n"
"      </CONFIGURATIONS>\r\n"
"      <MODULEPATHS>\r\n"
"        <MODULEPATH id=\"juce_product_unlocking\" path=\"%JUCE_PATH%\"/>\r\n"
"        <MODULEPATH id=\"juce_gui_extra\" path=\"%JUCE_PATH%\"/>\r\n"
"        <MODULEPATH id=\"juce_gui_basics\" path=\"%JUCE_PATH%\"/>\r\n"
"        <MODULEPATH id=\"juce_graphics\" path=\"%JUCE_PATH%\"/>\r\n"
"        <MODULEPATH id=\"juce_events\" path=\"%JUCE_PATH%\"/>\r\n"
"        <MODULEPATH id=\"juce_data_structures\" path=\"%JUCE_PATH%\"/>\r\n"
"        <MODULEPATH id=\"juce_dsp\" path=\"%JUCE_PATH%\"/>\r\n"
"        <MODULEPATH id=\"juce_cryptography\" path=\"%JUCE_PATH%\"/>\r\n"
"        <MODULEPATH id=\"juce_core\" path=\"%JUCE_PATH%\"/>\r\n"
"        <MODULEPATH id=\"juce_audio_utils\" path=\"%JUCE_PATH%\"/>\r\n"
"        <MODULEPATH id=\"juce_audio_processors\" path=\"%JUCE_PATH%\"/>\r\n"
"        <MODULEPATH id=\"juce_audio_plugin_client\" path=\"%JUCE_PATH%\"/>\r\n"
"        <MODULEPATH id=\"juce_audio_formats\" path=\"%JUCE_PATH%\"/>\r\n"
"        <MODULEPATH id=\"juce_audio_devices\" path=\"%JUCE_PATH%\"/>\r\n"
"        <MODULEPATH id=\"juce_audio_basics\" path=\"%JUCE_PATH%\"/>\r\n"
"        <MODULEPATH id=\"juce_opengl\" path=\"%JUCE_PATH%\"/>\r\n"
"        <MODULEPATH id=\"hi_scripting\" path=\"%HISE_PATH%\"/>\r\n"
"        <MODULEPATH id=\"hi_modules\" path=\"%HISE_PATH%\"/>\r\n"
"        <MODULEPATH id=\"hi_frontend\" path=\"%HISE_PATH%\"/>\r\n"
"        <MODULEPATH id=\"hi_dsp_library\" path=\"%HISE_PATH%\"/>\r\n"
"        <MODULEPATH id=\"hi_core\" path=\"%HISE_PATH%\"/>\r\n"
"        <MODULEPATH id=\"hi_lac\" path=\"%HISE_PATH%\"/>\r\n"
"		 <MODULEPATH id=\"hi_sampler\" path=\"%HISE_PATH%\"/>\r\n"
"	     <MODULEPATH id=\"hi_components\" path=\"%HISE_PATH%\"/>\r\n"
"        <MODULEPATH id=\"hi_dsp\" path=\"%HISE_PATH%\"/>\r\n"
"        <MODULEPATH id=\"hi_zstd\" path=\"%HISE_PATH%\"/>\r\n"
"        <MODULEPATH id=\"hi_streaming\" path=\"%HISE_PATH%\"/>\r\n"
"        <MODULEPATH id=\"hi_tools\" path=\"%HISE_PATH%\"/>\r\n"
"        <MODULEPATH id=\"stk_wrapper\" path=\"%HISE_PATH%\"/>\r\n"
"      </MODULEPATHS>\r\n"
"    </XCODE_IPHONE>\r\n"
"    <LINUX_MAKE targetFolder=\"Builds/LinuxMakefile\" linuxExtraPkgConfig=\"%LINUX_GUI_LIBS%\">\r\n"
"      <CONFIGURATIONS>\r\n"
"        <CONFIGURATION name=\"Debug\" isDebug=\"1\" optimisation=\"1\" linkTimeOptimisation=\"0\"\r\n"
"                       targetName=\"%NAME%\" defines=\"USE_IPP=0\"/>\r\n"
"        <CONFIGURATION name=\"Release\" isDebug=\"0\" optimisation=\"3\" linkTimeOptimisation=\"1\"\r\n"
"                       targetName=\"%NAME%\" defines=\"USE_IPP=0\"/>\r\n"
"      </CONFIGURATIONS>\r\n"
"      <MODULEPATHS>\r\n"
"        <MODULEPATH id=\"juce_product_unlocking\" path=\"%JUCE_PATH%\"/>\r\n"
"        <MODULEPATH id=\"juce_gui_extra\" path=\"%JUCE_PATH%\"/>\r\n"
"        <MODULEPATH id=\"juce_gui_basics\" path=\"%JUCE_PATH%\"/>\r\n"
"        <MODULEPATH id=\"juce_graphics\" path=\"%JUCE_PATH%\"/>\r\n"
"        <MODULEPATH id=\"juce_events\" path=\"%JUCE_PATH%\"/>\r\n"
"        <MODULEPATH id=\"juce_data_structures\" path=\"%JUCE_PATH%\"/>\r\n"
"        <MODULEPATH id=\"juce_dsp\" path=\"%JUCE_PATH%\"/>\r\n"
"        <MODULEPATH id=\"juce_cryptography\" path=\"%JUCE_PATH%\"/>\r\n"
"        <MODULEPATH id=\"juce_core\" path=\"%JUCE_PATH%\"/>\r\n"
"        <MODULEPATH id=\"juce_audio_utils\" path=\"%JUCE_PATH%\"/>\r\n"
"        <MODULEPATH id=\"juce_audio_processors\" path=\"%JUCE_PATH%\"/>\r\n"
"        <MODULEPATH id=\"juce_audio_plugin_client\" path=\"%JUCE_PATH%\"/>\r\n"
"        <MODULEPATH id=\"juce_audio_formats\" path=\"%JUCE_PATH%\"/>\r\n"
"        <MODULEPATH id=\"juce_audio_devices\" path=\"%JUCE_PATH%\"/>\r\n"
"        <MODULEPATH id=\"juce_audio_basics\" path=\"%JUCE_PATH%\"/>\r\n"
"        <MODULEPATH id=\"juce_opengl\" path=\"%JUCE_PATH%\"/>\r\n"
"        <MODULEPATH id=\"hi_streaming\" path=\"%HISE_PATH%\"/>\r\n"
"        <MODULEPATH id=\"hi_scripting\" path=\"%HISE_PATH%\"/>\r\n"
"        <MODULEPATH id=\"hi_sampler\" path=\"%HISE_PATH%\"/>\r\n"
"        <MODULEPATH id=\"hi_modules\" path=\"%HISE_PATH%\"/>\r\n"
"        <MODULEPATH id=\"hi_lac\" path=\"%HISE_PATH%\"/>\r\n"
"        <MODULEPATH id=\"hi_frontend\" path=\"%HISE_PATH%\"/>\r\n"
"        <MODULEPATH id=\"hi_dsp_library\" path=\"%HISE_PATH%\"/>\r\n"
"        <MODULEPATH id=\"hi_dsp\" path=\"%HISE_PATH%\"/>\r\n"
"        <MODULEPATH id=\"hi_zstd\" path=\"%HISE_PATH%\"/>\r\n"
"        <MODULEPATH id=\"hi_core\" path=\"%HISE_PATH%\"/>\r\n"
"        <MODULEPATH id=\"hi_components\" path=\"%HISE_PATH%\"/>\r\n"
"        <MODULEPATH id=\"hi_tools\" path=\"%HISE_PATH%\"/>\r\n"
"        <MODULEPATH id=\"stk_wrapper\" path=\"%HISE_PATH%\"/>\r\n"
"      </MODULEPATHS>\r\n"
"    </LINUX_MAKE>\r\n"
"  </EXPORTFORMATS>\r\n"
"  <MODULES>\r\n"
"    <MODULE id=\"hi_core\" showAllCode=\"1\" useLocalCopy=\"0\"/>\r\n"
"    <MODULE id=\"hi_frontend\" showAllCode=\"1\" useLocalCopy=\"0\"/>\r\n"
"    <MODULE id=\"hi_scripting\" showAllCode=\"1\" useLocalCopy=\"0\"/>\r\n"
"    <MODULE id=\"hi_modules\" showAllCode=\"1\" useLocalCopy=\"0\"/>\r\n"
"    <MODULE id=\"hi_dsp_library\" showAllCode=\"1\" useLocalCopy=\"0\"/>\r\n"
"    <MODULE id=\"hi_lac\" showAllCode=\"1\" useLocalCopy=\"0\"/>\r\n"
"    <MODULE id=\"hi_sampler\" showAllCode=\"1\" useLocalCopy=\"0\"/>\r\n"
"    <MODULE id=\"hi_components\" showAllCode=\"1\" useLocalCopy=\"0\"/>\r\n"
"    <MODULE id=\"hi_dsp\" showAllCode=\"1\" useLocalCopy=\"0\"/>\r\n"
"    <MODULE id=\"hi_zstd\" showAllCode=\"1\" useLocalCopy=\"0\"/>\r\n"
"    <MODULE id=\"hi_streaming\" showAllCode=\"1\" useLocalCopy=\"0\"/>\r\n"
"    <MODULE id=\"hi_tools\" showAllCode=\"1\" useLocalCopy=\"0\"/>\r\n"
"    <MODULE id=\"juce_audio_basics\" showAllCode=\"1\" useLocalCopy=\"0\"/>\r\n"
"    <MODULE id=\"juce_audio_devices\" showAllCode=\"1\" useLocalCopy=\"0\"/>\r\n"
"    <MODULE id=\"juce_dsp\" showAllCode=\"1\" useLocalCopy=\"0\"/>\r\n"
"    <MODULE id=\"juce_audio_formats\" showAllCode=\"1\" useLocalCopy=\"0\"/>\r\n"
"    <MODULE id=\"juce_audio_plugin_client\" showAllCode=\"1\" useLocalCopy=\"0\"/>\r\n"
"    <MODULE id=\"juce_audio_processors\" showAllCode=\"1\" useLocalCopy=\"0\"/>\r\n"
"    <MODULE id=\"juce_audio_utils\" showAllCode=\"1\" useLocalCopy=\"0\"/>\r\n"
"    <MODULE id=\"juce_core\" showAllCode=\"1\" useLocalCopy=\"0\"/>\r\n"
"    <MODULE id=\"juce_cryptography\" showAllCode=\"1\" useLocalCopy=\"0\"/>\r\n"
"    <MODULE id=\"juce_data_structures\" showAllCode=\"1\" useLocalCopy=\"0\"/>\r\n"
"    <MODULE id=\"juce_events\" showAllCode=\"1\" useLocalCopy=\"0\"/>\r\n"
"    <MODULE id=\"juce_graphics\" showAllCode=\"1\" useLocalCopy=\"0\"/>\r\n"
"    <MODULE id=\"juce_gui_basics\" showAllCode=\"1\" useLocalCopy=\"0\"/>\r\n"
"    <MODULE id=\"juce_gui_extra\" showAllCode=\"1\" useLocalCopy=\"0\"/>\r\n"
"    <MODULE id=\"juce_product_unlocking\" showAllCode=\"1\" useLocalCopy=\"0\"/>\r\n"
"    <MODULE id=\"juce_opengl\" showAllCode=\"1\" useLocalCopy=\"0\"/>\r\n"
"    <MODULE id=\"stk_wrapper\" showAllCode=\"1\" useLocalCopy=\"0\" useGlobalPath=\"0\"/>\r\n"
"  </MODULES>\r\n"
"  <JUCEOPTIONS JUCE_QUICKTIME=\"disabled\" USE_BACKEND=\"disabled\" USE_FRONTEND=\"enabled\" USE_RAW_FRONTEND=\"%USE_RAW_FRONTEND%\" HI_EXPORT_DSP_LIBRARY=\"disabled\" USE_COPY_PROTECTION=\"%USE_COPY_PROTECTION%\" IS_STANDALONE_APP=\"disabled\"\r\n"
"               USE_IPP=\"%USE_IPP%\" FRONTEND_IS_PLUGIN=\"%FRONTEND_IS_PLUGIN%\" USE_CUSTOM_FRONTEND_TOOLBAR=\"%USE_CUSTOM_FRONTEND_TOOLBAR%\" IS_STANDALONE_FRONTEND=\"%IS_STANDALONE_FRONTEND%\" USE_GLITCH_DETECTION = \"enabled\" ENABLE_PLOTTER=\"disabled\" ENABLE_SCRIPTING_SAFE_CHECKS=\"disabled\""
"               ENABLE_ALL_PEAK_METERS=\"disabled\" USE_SPLASH_SCREEN=\"%USE_SPLASH_SCREEN%\" HI_SUPPORT_MONO_CHANNEL_LAYOUT=\"%SUPPORT_MONO%\" HI_SUPPORT_FULL_DYNAMICS_HLAC=\"%SUPPORT_FULL_DYNAMICS%\" ENABLE_CONSOLE_OUTPUT=\"disabled\" HLAC_MEASURE_DECODING_PERFORMANCE=\"disabled\" HLAC_DEBUG_LOG=\"disabled\" HLAC_INCLUDE_TEST_SUITE=\"disabled\" STANDALONE_STREAMING=\"disabled\""

"				JUCE_ASSERTION_FIRFILTER=\"disabled\" JUCE_WEB_BROWSER=\"disabled\" JUCE_USE_CURL=\"disabled\" JUCE_DSP_USE_INTEL_MKL=\"disabled\" JUCE_DSP_USE_SHARED_FFTW=\"disabled\" JUCE_DSP_USE_STATIC_FFTW=\"disabled\" JUCE_HEADLESS_PLUGIN_CLIENT=\"%JUCE_HEADLESS_PLUGIN_CLIENT%\"/>/>\r\n"
"</JUCERPROJECT>\r\n";

const char* projectTemplate_jucer = (const char*)projectTemplate_jucer_lines;

} // namespace hise
