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
*   Commercial licences for using HISE in an closed source project are
*   available on request. Please visit the project's website to get more
*   information about commercial licencing:
*
*   http://www.hartinstruments.net/hise/
*
*   HISE is based on the JUCE library,
*   which also must be licenced for commercial applications:
*
*   http://www.juce.com
*
*   ===========================================================================
*/


FloatingFlexBoxWindow::FloatingFlexBoxWindow() :
	DocumentWindow("HISE Floating Window", Colour(0xFF333333), allButtons, true)
{
	ValueTree state;


	setContentOwned(new FloatingTile(nullptr, state), false);

	setResizable(true, true);
	setUsingNativeTitleBar(true);

	centreWithSize(1500, 1000);

	auto fsc = dynamic_cast<FloatingTile*>(getContentComponent());
	fsc->setLayoutModeEnabled(false, true);
	
	FloatingInterfaceBuilder ib(fsc);

	const int root = 0;

#if 0
	ib.setNewContentType<FloatingTabComponent>(root);

	const int firstVertical = ib.addChild<VerticalTile>(root);

	const int leftColumn = ib.addChild<HorizontalTile>(firstVertical);
	const int mainColumn = ib.addChild<HorizontalTile>(firstVertical);
	const int rightColumn = ib.addChild<HorizontalTile>(firstVertical);

	ib.setSizes(firstVertical, { -0.5, 900.0, -0.5 }, dontSendNotification);
	ib.setAbsoluteSize(firstVertical, { false, true, false }, dontSendNotification);
	ib.setLocked(firstVertical, { false, true, false}, sendNotification);
	ib.setDeletable(root, false, { false });
	ib.setDeletable(firstVertical, false, { false, false, false });


	const int mainArea = ib.addChild<EmptyComponent>(mainColumn);
	const int keyboard = ib.addChild<MidiKeyboardPanel>(mainColumn);

	ib.setSwappable(firstVertical, false, { false, false, false });
	ib.setSwappable(mainColumn, false, { false, false });

	ib.getPanel(firstVertical)->setDeletable(false);
	ib.getContainer(firstVertical)->setAllowInserting(false);
	ib.getPanel(mainColumn)->setReadOnly(true);
	ib.getPanel(root)->setDeletable(false);

	ib.setCustomName(firstVertical, "Main Workspace", { "Left Panel", "Mid Panel", "Right Panel" });
	

	ib.getPanel(mainColumn)->getParentContainer()->refreshLayout();

	ib.finalizeAndReturnRoot(true);
#endif

	//FloatingPanelTemplates::createMainPanel(fsc);
}

void FloatingFlexBoxWindow::closeButtonPressed()
{
	ValueTree v = dynamic_cast<FloatingTile*>(getContentComponent())->getCurrentFloatingPanel()->exportAsValueTree();

	File f("D:\\testa.xml");

	//v.createXml()->writeToFile(f, "");

	delete this;
}

BackendRootWindow* FloatingTileContent::getRootWindow()
{
	return getParentShell()->getRootWindow();
}

const BackendRootWindow* FloatingTileContent::getRootWindow() const
{
	return getParentShell()->getRootWindow();
}

ValueTree FloatingTileContent::exportAsValueTree() const
{
	ValueTree v(getIdentifierForBaseClass());

	v.setProperty("Title", getCustomTitle(), nullptr);

	getParentShell()->getLayoutData().updateValueTree(v);

	// Don't store the size for fixed width components
	if (getFixedSizeForOrientation() != 0)
		v.removeProperty("Size", nullptr);

	return v;
}

void FloatingTileContent::restoreFromValueTree(const ValueTree& v)
{
	setCustomTitle(v.getProperty("Title", {}));
}

FloatingTileContent* FloatingTileContent::createPanel(ValueTree& state, FloatingTile* parent)
{
	auto p = parent->getPanelFactory()->createFromId(state.getType(), parent);


	jassert(p != nullptr);

	if(p != nullptr)
		p->restoreFromValueTree(state);

	return p;
}


FloatingTileContent* FloatingTileContent::createNewPanel(const Identifier& id, FloatingTile* parent)
{
	return parent->getPanelFactory()->createFromId(id, parent);
}

void FloatingTileContent::setDynamicTitle(const String& newDynamicTitle)
{
	dynamicTitle = newDynamicTitle;
	getParentShell()->repaint();
}

const BackendProcessorEditor* FloatingTileContent::getMainPanel() const
{
	return getParentShell()->findParentComponentOfClass<BackendRootWindow>()->getMainPanel();
}

BackendProcessorEditor* FloatingTileContent::getMainPanel()
{
	return getParentShell()->findParentComponentOfClass<BackendRootWindow>()->getMainPanel();
}

int FloatingTileContent::getFixedSizeForOrientation() const
{
	auto pType = getParentShell()->getParentType();

	if (pType == FloatingTile::ParentType::Horizontal)
		return getFixedWidth();
	else if (pType == FloatingTile::ParentType::Vertical)
		return getFixedHeight();
	else
		return 0;
}

#if 0

FloatingPanel* FloatingPanel::createPanel(ValueTree& state, FloatingShellComponent* parent)
{
	auto pt = getPanelTypeForId(Identifier(state.getType()));

	FloatingPanel* p = createNewPanel(pt, parent);

	if (p != nullptr)
		p->restoreFromValueTree(state);

	return p;
}

FloatingPanel* FloatingPanel::Factory::createNewPanel(PanelType pt, FloatingShellComponent* parent)
{
	FloatingPanel* p = nullptr;

	switch (pt)
	{
	case PanelType::PTHorizontalTile: p = new HorizontalTile(parent); break;
	case PanelType::PTVerticalTile:	p = new VerticalTile(parent); break;
	case PanelType::PTTabs:			p = new FloatingTabComponent(parent); break;
	case PanelType::PTNote:			p = new Note(parent); break;
	}

	if (p == nullptr)
		return new EmptyComponent(parent);

	return p;
}
#endif

struct FloatingPanelTemplates::Helpers
{
	static void addNewShellTo(FloatingTileContainer* parent)
	{
		parent->addFloatingTile(new FloatingTile(parent));
	}

	static FloatingTileContainer* getChildContainer(FloatingTile* parent)
	{
		return dynamic_cast<FloatingTileContainer*>(parent->getCurrentFloatingPanel());
	}

	template <class PanelType> static void setContent(FloatingTile* parent)
	{
		parent->setNewContent(PanelType::getPanelId());
	};

	static FloatingTile* getChildShell(FloatingTile* parent, int index)
	{
		auto c = dynamic_cast<FloatingTileContainer*>(parent->getCurrentFloatingPanel());

		jassert(c != nullptr);

		return c->getComponent(index);
	}

	static void setShellSize(FloatingTileContainer* parent, int index, double size, bool isRelative)
	{
		if (isRelative)
			size *= -1.0;

		parent->getComponent(index)->getLayoutData().currentSize = size;
	}
};


void FloatingPanelTemplates::create2x2Matrix(FloatingTile* parent)
{
	Helpers::setContent<HorizontalTile>(parent);
	Helpers::addNewShellTo(Helpers::getChildContainer(parent));

	Helpers::setContent<VerticalTile>(Helpers::getChildShell(parent, 0));
	Helpers::setContent<VerticalTile>(Helpers::getChildShell(parent, 1));

	auto v1 = Helpers::getChildContainer(Helpers::getChildShell(parent, 0));
	auto v2 = Helpers::getChildContainer(Helpers::getChildShell(parent, 1));

	Helpers::addNewShellTo(v1);
	Helpers::addNewShellTo(v2);
}

void FloatingPanelTemplates::create3Columns(FloatingTile* parent)
{
	Helpers::setContent<VerticalTile>(parent);

	auto c = Helpers::getChildContainer(parent);

	Helpers::addNewShellTo(c);
	Helpers::addNewShellTo(c);
}

void FloatingPanelTemplates::create3Rows(FloatingTile* parent)
{
	Helpers::setContent<HorizontalTile>(parent);

	auto c = Helpers::getChildContainer(parent);

	Helpers::addNewShellTo(c);
	Helpers::addNewShellTo(c);
}



void FloatingTileContent::Factory::registerAllPanelTypes()
{
#if PUT_FLOAT_IN_CODEBASE
	registerType<MainPanel>();
	registerType<MainTopBar>();
#endif
	registerType<SpacerPanel>();
	registerType<HorizontalTile>();
	registerType<VerticalTile>();
	registerType<FloatingTabComponent>();
	registerType<EmptyComponent>();
	registerType<Note>();
	registerType<MidiKeyboardPanel>();
	registerType<TableEditorPanel>();
	registerType<CodeEditorPanel>();
	registerType<SampleMapEditorPanel>();
	registerType<SampleEditorPanel>();
	registerType<ScriptContentPanel>();
	registerType<SliderPackPanel>();
	registerType<GlobalConnectorPanel>();
	registerType<ConsolePanel>();
	registerType<GenericPanel<ApiCollection>>();
	registerType<ScriptWatchTablePanel>();
	registerType<GenericPanel<ModuleBrowser>>();
	registerType<GenericPanel<PatchBrowser>>();
	registerType<GenericPanel<FileBrowser>>();
	registerType<GenericPanel<ScriptComponentEditPanel>>();
	registerType<ApplicationCommandButtonPanel>();

}


Drawable* FloatingTileContent::Factory::getIcon(PopupMenuOptions type)
{
	Path path;
	

	switch (type)
	{
	case FloatingTileContent::Factory::PopupMenuOptions::Cancel:
		break;
	case FloatingTileContent::Factory::PopupMenuOptions::Empty:
		break;
	case FloatingTileContent::Factory::PopupMenuOptions::Spacer:
	{
		static const unsigned char pathData[] = { 110,109,0,120,111,66,255,167,242,66,108,0,120,111,66,0,84,4,67,108,0,134,111,66,0,84,4,67,108,0,134,111,66,128,86,4,67,108,0,195,141,66,128,86,4,67,108,0,195,141,66,128,86,1,67,108,0,120,123,66,128,86,1,67,108,0,120,123,66,255,167,242,66,108,0,120,111,
			66,255,167,242,66,99,109,0,150,20,66,0,180,242,66,108,0,150,20,66,128,93,1,67,108,0,24,233,65,128,93,1,67,108,0,24,233,65,128,93,4,67,108,0,140,32,66,128,93,4,67,108,0,140,32,66,0,90,4,67,108,0,150,32,66,0,90,4,67,108,0,150,32,66,0,180,242,66,108,0,150,
			20,66,0,180,242,66,99,109,0,120,232,65,0,61,24,67,108,0,120,232,65,0,61,27,67,108,0,74,20,66,0,61,27,67,108,0,74,20,66,128,63,35,67,108,0,74,32,66,128,63,35,67,108,0,74,32,66,128,63,24,67,108,0,60,32,66,128,63,24,67,108,0,60,32,66,0,61,24,67,108,0,120,
			232,65,0,61,24,67,99,109,0,84,112,66,0,86,24,67,108,0,84,112,66,128,89,24,67,108,0,74,112,66,128,89,24,67,108,0,74,112,66,128,89,35,67,108,0,74,124,66,128,89,35,67,108,0,74,124,66,0,86,27,67,108,0,42,142,66,0,86,27,67,108,0,42,142,66,0,86,24,67,108,0,
			84,112,66,0,86,24,67,99,101,0,0 };

		path.loadPathFromData(pathData, sizeof(pathData));

		break;
	}
	case FloatingTileContent::Factory::PopupMenuOptions::BigResizer:
		break;
	case FloatingTileContent::Factory::PopupMenuOptions::HorizontalTile:
	{
		static const unsigned char pathData[] = { 110,109,0,191,29,67,129,235,111,67,108,0,51,205,66,129,235,111,67,108,0,51,205,66,128,254,121,67,108,0,191,29,67,128,254,121,67,108,0,191,29,67,129,235,111,67,99,109,0,159,29,67,1,209,91,67,108,1,242,204,66,1,209,91,67,108,1,242,204,66,129,228,101,67,
			108,0,159,29,67,129,228,101,67,108,0,159,29,67,1,209,91,67,99,109,3,151,29,67,0,247,129,67,108,6,227,204,66,0,247,129,67,108,6,227,204,66,192,0,135,67,108,3,151,29,67,192,0,135,67,108,3,151,29,67,0,247,129,67,99,101,0,0 };

		path.loadPathFromData(pathData, sizeof(pathData));
		break;
	}
	case FloatingTileContent::Factory::PopupMenuOptions::VerticalTile:
	{
		static const unsigned char pathData[] = { 110,109,1,53,250,66,128,66,89,67,108,1,53,250,66,0,52,136,67,108,128,45,7,67,0,52,136,67,108,128,45,7,67,128,66,89,67,108,1,53,250,66,128,66,89,67,99,109,0,0,210,66,128,98,89,67,108,0,0,210,66,64,68,136,67,108,0,39,230,66,64,68,136,67,108,0,39,230,66,
			128,98,89,67,108,0,0,210,66,128,98,89,67,99,109,0,29,17,67,128,106,89,67,108,0,29,17,67,0,72,136,67,108,128,48,27,67,0,72,136,67,108,128,48,27,67,128,106,89,67,108,0,29,17,67,128,106,89,67,99,101,0,0 };

		path.loadPathFromData(pathData, sizeof(pathData));

		break;
	}	
	case FloatingTileContent::Factory::PopupMenuOptions::Tabs:
	{
		static const unsigned char pathData[] = { 110,109,0,0,170,66,64,174,153,67,108,0,0,170,66,64,46,176,67,108,0,205,189,66,64,46,176,67,108,0,205,189,66,0,142,158,67,108,0,0,2,67,0,142,158,67,108,0,0,2,67,64,174,153,67,108,0,0,170,66,64,174,153,67,99,109,0,126,199,66,192,250,160,67,108,0,126,199,
			66,192,122,183,67,108,0,191,16,67,192,122,183,67,108,0,191,16,67,192,250,160,67,108,0,126,199,66,192,250,160,67,99,101,0,0 };


		path.loadPathFromData(pathData, sizeof(pathData));

		break;
	}
	case FloatingTileContent::Factory::PopupMenuOptions::Matrix2x2:
		break;
	case FloatingTileContent::Factory::PopupMenuOptions::ThreeColumns:
		break;
	case FloatingTileContent::Factory::PopupMenuOptions::ThreeRows:
		break;
	case FloatingTileContent::Factory::PopupMenuOptions::Note:
	{
		static const unsigned char pathData[] = { 110,109,0,160,54,67,64,174,213,67,108,0,160,54,67,192,178,217,67,108,0,137,42,67,192,178,217,67,108,0,137,42,67,192,178,218,67,108,0,137,42,67,192,57,243,67,108,0,55,101,67,192,57,243,67,108,0,55,101,67,192,178,217,67,108,0,128,89,67,192,178,217,67,108,
			0,128,89,67,64,174,213,67,108,0,128,84,67,64,174,213,67,108,0,128,84,67,192,178,217,67,108,0,128,79,67,192,178,217,67,108,0,128,79,67,64,174,213,67,108,0,128,74,67,64,174,213,67,108,0,128,74,67,192,178,217,67,108,0,224,69,67,192,178,217,67,108,0,224,
			69,67,64,174,213,67,108,0,224,64,67,64,174,213,67,108,0,224,64,67,192,178,217,67,108,0,160,59,67,192,178,217,67,108,0,160,59,67,64,174,213,67,108,0,160,54,67,64,174,213,67,99,109,0,137,46,67,192,178,219,67,108,0,160,54,67,192,178,219,67,108,0,160,54,
			67,64,46,221,67,108,0,160,59,67,64,46,221,67,108,0,160,59,67,192,178,219,67,108,0,224,64,67,192,178,219,67,108,0,224,64,67,64,46,221,67,108,0,224,69,67,64,46,221,67,108,0,224,69,67,192,178,219,67,108,0,128,74,67,192,178,219,67,108,0,128,74,67,64,46,221,
			67,108,0,128,79,67,64,46,221,67,108,0,128,79,67,192,178,219,67,108,0,128,84,67,192,178,219,67,108,0,128,84,67,64,46,221,67,108,0,128,89,67,64,46,221,67,108,0,128,89,67,192,178,219,67,108,0,55,97,67,192,178,219,67,108,0,55,97,67,192,57,241,67,108,0,137,
			46,67,192,57,241,67,108,0,137,46,67,192,178,219,67,99,109,0,167,54,67,64,238,222,67,108,0,167,54,67,64,110,224,67,108,128,179,89,67,64,110,224,67,108,128,179,89,67,64,238,222,67,108,0,167,54,67,64,238,222,67,99,109,0,167,54,67,64,238,227,67,108,0,167,
			54,67,64,110,229,67,108,128,179,89,67,64,110,229,67,108,128,179,89,67,64,238,227,67,108,0,167,54,67,64,238,227,67,99,109,0,167,54,67,64,238,232,67,108,0,167,54,67,64,110,234,67,108,128,179,89,67,64,110,234,67,108,128,179,89,67,64,238,232,67,108,0,167,
			54,67,64,238,232,67,99,109,0,167,54,67,64,238,237,67,108,0,167,54,67,64,110,239,67,108,128,179,89,67,64,110,239,67,108,128,179,89,67,64,238,237,67,108,0,167,54,67,64,238,237,67,99,101,0,0 };

		path.loadPathFromData(pathData, sizeof(pathData));

		break;
	}
		
	case FloatingTileContent::Factory::PopupMenuOptions::MidiKeyboard:
		path.loadPathFromData(BackendBinaryData::ToolbarIcons::keyboard, sizeof(BackendBinaryData::ToolbarIcons::keyboard));
		break;
	case FloatingTileContent::Factory::PopupMenuOptions::GlobalConnectorPanel:
	{
		static const unsigned char pathData[] = { 110,109,0,0,52,67,0,57,195,66,108,0,0,52,67,0,57,195,66,108,7,192,51,67,51,60,195,66,108,55,128,51,67,202,69,195,66,108,184,64,51,67,191,85,195,66,108,180,1,51,67,8,108,195,66,108,83,195,50,67,150,136,195,66,108,188,133,50,67,87,171,195,66,108,23,73,
			50,67,53,212,195,66,108,139,13,50,67,22,3,196,66,108,62,211,49,67,219,55,196,66,108,86,154,49,67,100,114,196,66,108,246,98,49,67,138,178,196,66,108,66,45,49,67,36,248,196,66,108,92,249,48,67,7,67,197,66,108,103,199,48,67,1,147,197,66,108,129,151,48,67,
			224,231,197,66,108,201,105,48,67,110,65,198,66,108,92,62,48,67,114,159,198,66,108,87,21,48,67,174,1,199,66,108,212,238,47,67,228,103,199,66,108,235,202,47,67,212,209,199,66,108,179,169,47,67,56,63,200,66,108,65,139,47,67,203,175,200,66,108,170,111,47,
			67,70,35,201,66,108,253,86,47,67,93,153,201,66,108,77,65,47,67,198,17,202,66,108,165,46,47,67,52,140,202,66,108,19,31,47,67,88,8,203,66,108,160,18,47,67,226,133,203,66,108,84,9,47,67,131,4,204,66,108,53,3,47,67,233,131,204,66,108,71,0,47,67,196,3,205,
			66,108,0,0,47,67,0,57,205,66,108,0,0,47,67,0,57,205,66,108,0,0,47,67,0,57,205,66,108,74,2,47,67,232,184,205,66,108,197,7,47,67,108,56,206,66,108,128,9,47,67,0,86,206,66,108,128,9,47,67,0,86,206,66,108,128,152,35,67,0,199,217,66,108,128,152,35,67,0,199,
			217,66,108,234,106,35,67,43,109,217,66,108,37,59,35,67,2,24,217,66,108,78,9,35,67,186,199,216,66,108,134,213,34,67,135,124,216,66,108,237,159,34,67,153,54,216,66,108,166,104,34,67,30,246,215,66,108,212,47,34,67,61,187,215,66,108,156,245,33,67,29,134,
			215,66,108,34,186,33,67,224,86,215,66,108,142,125,33,67,164,45,215,66,108,4,64,33,67,131,10,215,66,108,174,1,33,67,149,237,214,66,108,179,194,32,67,234,214,214,66,108,59,131,32,67,147,198,214,66,108,110,67,32,67,153,188,214,66,108,118,3,32,67,3,185,214,
			66,108,0,0,32,67,0,185,214,66,108,0,0,32,67,0,185,214,66,108,0,0,32,67,0,185,214,66,108,7,192,31,67,51,188,214,66,108,55,128,31,67,202,197,214,66,108,184,64,31,67,191,213,214,66,108,180,1,31,67,8,236,214,66,108,83,195,30,67,150,8,215,66,108,188,133,30,
			67,87,43,215,66,108,23,73,30,67,53,84,215,66,108,139,13,30,67,22,131,215,66,108,62,211,29,67,219,183,215,66,108,86,154,29,67,100,242,215,66,108,246,98,29,67,138,50,216,66,108,66,45,29,67,36,120,216,66,108,92,249,28,67,7,195,216,66,108,103,199,28,67,1,
			19,217,66,108,129,151,28,67,224,103,217,66,108,201,105,28,67,110,193,217,66,108,92,62,28,67,114,31,218,66,108,87,21,28,67,174,129,218,66,108,212,238,27,67,228,231,218,66,108,235,202,27,67,212,81,219,66,108,179,169,27,67,56,191,219,66,108,65,139,27,67,
			203,47,220,66,108,170,111,27,67,70,163,220,66,108,253,86,27,67,93,25,221,66,108,77,65,27,67,198,145,221,66,108,165,46,27,67,52,12,222,66,108,19,31,27,67,88,136,222,66,108,160,18,27,67,226,5,223,66,108,84,9,27,67,131,132,223,66,108,53,3,27,67,233,3,224,
			66,108,71,0,27,67,196,131,224,66,108,0,0,27,67,0,185,224,66,108,0,0,27,67,0,185,224,66,108,0,0,27,67,0,185,224,66,108,154,1,27,67,242,56,225,66,108,101,6,27,67,147,184,225,66,108,96,14,27,67,144,55,226,66,108,132,25,27,67,152,181,226,66,108,203,39,27,
			67,91,50,227,66,108,43,57,27,67,137,173,227,66,108,154,77,27,67,210,38,228,66,108,11,101,27,67,234,157,228,66,108,110,127,27,67,132,18,229,66,108,178,156,27,67,85,132,229,66,108,197,188,27,67,21,243,229,66,108,146,223,27,67,125,94,230,66,108,4,5,28,67,
			72,198,230,66,108,1,45,28,67,52,42,231,66,108,113,87,28,67,0,138,231,66,108,56,132,28,67,112,229,231,66,108,57,179,28,67,72,60,232,66,108,87,228,28,67,82,142,232,66,108,115,23,29,67,89,219,232,66,108,106,76,29,67,43,35,233,66,108,29,131,29,67,155,101,
			233,66,108,102,187,29,67,126,162,233,66,108,36,245,29,67,174,217,233,66,108,47,48,30,67,6,11,234,66,108,100,108,30,67,103,54,234,66,108,155,169,30,67,182,91,234,66,108,173,231,30,67,218,122,234,66,108,114,38,31,67,193,147,234,66,108,194,101,31,67,88,
			166,234,66,108,117,165,31,67,150,178,234,66,108,99,229,31,67,114,184,234,66,108,0,0,32,67,0,185,234,66,108,0,0,32,67,0,185,234,66,108,0,0,32,67,0,185,234,66,108,249,63,32,67,168,181,234,66,108,200,127,32,67,237,171,234,66,108,68,191,32,67,212,155,234,
			66,108,69,254,32,67,104,133,234,66,108,162,60,33,67,183,104,234,66,108,52,122,33,67,211,69,234,66,108,211,182,33,67,211,28,234,66,108,88,242,33,67,208,237,233,66,108,157,44,34,67,234,184,233,66,108,126,101,34,67,65,126,233,66,108,213,156,34,67,252,61,
			233,66,108,127,210,34,67,67,248,232,66,108,90,6,35,67,67,173,232,66,108,68,56,35,67,44,93,232,66,108,30,104,35,67,50,8,232,66,108,201,149,35,67,138,174,231,66,108,128,151,35,67,255,170,231,66,108,128,151,35,67,255,170,231,66,108,0,37,47,67,0,57,243,66,
			108,0,37,47,67,0,57,243,66,108,7,27,47,67,108,183,243,66,108,58,20,47,67,175,54,244,66,108,157,16,47,67,120,182,244,66,108,0,16,47,67,0,249,244,66,108,0,16,47,67,0,249,244,66,108,0,16,47,67,0,249,244,66,108,154,17,47,67,242,120,245,66,108,101,22,47,67,
			147,248,245,66,108,96,30,47,67,144,119,246,66,108,132,41,47,67,152,245,246,66,108,203,55,47,67,91,114,247,66,108,43,73,47,67,137,237,247,66,108,154,93,47,67,210,102,248,66,108,11,117,47,67,234,221,248,66,108,110,143,47,67,132,82,249,66,108,178,172,47,
			67,85,196,249,66,108,197,204,47,67,21,51,250,66,108,146,239,47,67,125,158,250,66,108,4,21,48,67,72,6,251,66,108,1,61,48,67,52,106,251,66,108,113,103,48,67,0,202,251,66,108,56,148,48,67,112,37,252,66,108,57,195,48,67,72,124,252,66,108,87,244,48,67,82,
			206,252,66,108,115,39,49,67,89,27,253,66,108,106,92,49,67,43,99,253,66,108,29,147,49,67,155,165,253,66,108,102,203,49,67,126,226,253,66,108,36,5,50,67,174,25,254,66,108,47,64,50,67,6,75,254,66,108,100,124,50,67,103,118,254,66,108,155,185,50,67,182,155,
			254,66,108,173,247,50,67,218,186,254,66,108,114,54,51,67,193,211,254,66,108,194,117,51,67,88,230,254,66,108,117,181,51,67,150,242,254,66,108,99,245,51,67,114,248,254,66,108,0,16,52,67,0,249,254,66,108,0,16,52,67,0,249,254,66,108,0,16,52,67,0,249,254,
			66,108,249,79,52,67,205,245,254,66,108,201,143,52,67,54,236,254,66,108,72,207,52,67,65,220,254,66,108,76,14,53,67,248,197,254,66,108,173,76,53,67,106,169,254,66,108,68,138,53,67,169,134,254,66,108,233,198,53,67,203,93,254,66,108,116,2,54,67,235,46,254,
			66,108,193,60,54,67,37,250,253,66,108,170,117,54,67,157,191,253,66,108,10,173,54,67,119,127,253,66,108,190,226,54,67,220,57,253,66,108,163,22,55,67,250,238,252,66,108,153,72,55,67,255,158,252,66,108,127,120,55,67,32,74,252,66,108,55,166,55,67,146,240,
			251,66,108,163,209,55,67,143,146,251,66,108,168,250,55,67,83,48,251,66,108,44,33,56,67,28,202,250,66,108,21,69,56,67,45,96,250,66,108,77,102,56,67,201,242,249,66,108,191,132,56,67,53,130,249,66,108,86,160,56,67,187,14,249,66,108,2,185,56,67,164,152,248,
			66,108,179,206,56,67,58,32,248,66,108,91,225,56,67,205,165,247,66,108,237,240,56,67,169,41,247,66,108,96,253,56,67,31,172,246,66,108,172,6,57,67,126,45,246,66,108,203,12,57,67,23,174,245,66,108,185,15,57,67,61,46,245,66,108,0,16,57,67,0,249,244,66,108,
			0,16,57,67,0,249,244,66,108,0,16,57,67,0,249,244,66,108,102,14,57,67,14,121,244,66,108,155,9,57,67,109,249,243,66,108,160,1,57,67,112,122,243,66,108,124,246,56,67,104,252,242,66,108,53,232,56,67,166,127,242,66,108,213,214,56,67,120,4,242,66,108,102,194,
			56,67,47,139,241,66,108,245,170,56,67,23,20,241,66,108,147,144,56,67,125,159,240,66,108,78,115,56,67,172,45,240,66,108,59,83,56,67,236,190,239,66,108,110,48,56,67,132,83,239,66,108,253,10,56,67,185,235,238,66,108,0,227,55,67,206,135,238,66,108,144,184,
			55,67,2,40,238,66,108,201,139,55,67,146,204,237,66,108,199,92,55,67,185,117,237,66,108,169,43,55,67,175,35,237,66,108,142,248,54,67,168,214,236,66,108,150,195,54,67,214,142,236,66,108,228,140,54,67,102,76,236,66,108,154,84,54,67,130,15,236,66,108,221,
			26,54,67,83,216,235,66,108,210,223,53,67,251,166,235,66,108,157,163,53,67,154,123,235,66,108,102,102,53,67,75,86,235,66,108,84,40,53,67,38,55,235,66,108,143,233,52,67,64,30,235,66,108,62,170,52,67,168,11,235,66,108,139,106,52,67,106,255,234,66,108,158,
			42,52,67,142,249,234,66,108,0,16,52,67,0,249,234,66,108,0,16,52,67,0,249,234,66,108,0,16,52,67,0,249,234,66,108,8,208,51,67,69,252,234,66,108,56,144,51,67,238,5,235,66,108,187,80,51,67,244,21,235,66,108,184,17,51,67,78,44,235,66,108,89,211,50,67,238,
			72,235,66,108,196,149,50,67,192,107,235,66,108,34,89,50,67,175,148,235,66,108,154,29,50,67,160,195,235,66,108,81,227,49,67,118,248,235,66,108,108,170,49,67,14,51,236,66,108,16,115,49,67,67,115,236,66,108,97,61,49,67,237,184,236,66,108,129,9,49,67,222,
			3,237,66,108,145,215,48,67,230,83,237,66,108,177,167,48,67,211,168,237,66,108,128,135,48,67,0,231,237,66,108,128,135,48,67,0,231,237,66,108,128,238,36,67,0,78,226,66,108,128,238,36,67,0,78,226,66,108,121,247,36,67,71,207,225,66,108,68,253,36,67,209,79,
			225,66,108,223,255,36,67,239,207,224,66,108,0,0,37,67,0,185,224,66,108,0,0,37,67,0,185,224,66,108,0,0,37,67,0,185,224,66,108,66,254,36,67,16,57,224,66,108,81,249,36,67,117,185,223,66,108,50,241,36,67,129,58,223,66,108,128,239,36,67,1,37,223,66,108,128,
			239,36,67,1,37,223,66,108,128,64,48,67,0,211,211,66,108,128,64,48,67,0,211,211,66,108,239,107,48,67,254,48,212,66,108,169,153,48,67,135,138,212,66,108,146,201,48,67,97,223,212,66,108,138,251,48,67,85,47,213,66,108,114,47,49,67,50,122,213,66,108,40,101,
			49,67,198,191,213,66,108,138,156,49,67,229,255,213,66,108,116,213,49,67,103,58,214,66,108,194,15,50,67,38,111,214,66,108,80,75,50,67,0,158,214,66,108,245,135,50,67,214,198,214,66,108,141,197,50,67,144,233,214,66,108,239,3,51,67,23,6,215,66,108,244,66,
			51,67,88,28,215,66,108,115,130,51,67,70,44,215,66,108,67,194,51,67,213,53,215,66,108,0,0,52,67,0,57,215,66,108,0,0,52,67,0,57,215,66,108,0,0,52,67,0,57,215,66,108,249,63,52,67,205,53,215,66,108,201,127,52,67,54,44,215,66,108,72,191,52,67,65,28,215,66,
			108,76,254,52,67,248,5,215,66,108,173,60,53,67,106,233,214,66,108,68,122,53,67,169,198,214,66,108,233,182,53,67,203,157,214,66,108,116,242,53,67,235,110,214,66,108,193,44,54,67,37,58,214,66,108,170,101,54,67,157,255,213,66,108,10,157,54,67,119,191,213,
			66,108,190,210,54,67,220,121,213,66,108,163,6,55,67,250,46,213,66,108,153,56,55,67,255,222,212,66,108,127,104,55,67,32,138,212,66,108,55,150,55,67,146,48,212,66,108,163,193,55,67,143,210,211,66,108,168,234,55,67,83,112,211,66,108,44,17,56,67,28,10,211,
			66,108,21,53,56,67,45,160,210,66,108,77,86,56,67,201,50,210,66,108,191,116,56,67,53,194,209,66,108,86,144,56,67,187,78,209,66,108,2,169,56,67,164,216,208,66,108,179,190,56,67,58,96,208,66,108,91,209,56,67,205,229,207,66,108,237,224,56,67,169,105,207,
			66,108,96,237,56,67,31,236,206,66,108,172,246,56,67,126,109,206,66,108,203,252,56,67,23,238,205,66,108,185,255,56,67,61,110,205,66,108,0,0,57,67,0,57,205,66,108,0,0,57,67,0,57,205,66,108,0,0,57,67,0,57,205,66,108,102,254,56,67,14,185,204,66,108,155,249,
			56,67,109,57,204,66,108,160,241,56,67,112,186,203,66,108,124,230,56,67,104,60,203,66,108,53,216,56,67,166,191,202,66,108,213,198,56,67,120,68,202,66,108,102,178,56,67,47,203,201,66,108,245,154,56,67,23,84,201,66,108,147,128,56,67,125,223,200,66,108,78,
			99,56,67,172,109,200,66,108,59,67,56,67,236,254,199,66,108,110,32,56,67,132,147,199,66,108,253,250,55,67,185,43,199,66,108,0,211,55,67,206,199,198,66,108,144,168,55,67,2,104,198,66,108,201,123,55,67,146,12,198,66,108,199,76,55,67,185,181,197,66,108,169,
			27,55,67,175,99,197,66,108,142,232,54,67,168,22,197,66,108,150,179,54,67,214,206,196,66,108,228,124,54,67,102,140,196,66,108,154,68,54,67,130,79,196,66,108,221,10,54,67,83,24,196,66,108,210,207,53,67,251,230,195,66,108,157,147,53,67,154,187,195,66,108,
			102,86,53,67,75,150,195,66,108,84,24,53,67,38,119,195,66,108,143,217,52,67,64,94,195,66,108,62,154,52,67,168,75,195,66,108,139,90,52,67,106,63,195,66,108,158,26,52,67,142,57,195,66,108,0,0,52,67,0,57,195,66,108,0,0,52,67,0,57,195,66,99,101,0,0 };

		path.loadPathFromData(pathData, sizeof(pathData));

		break;
	}
	case FloatingTileContent::Factory::PopupMenuOptions::ScriptEditor:
	{
		path.loadPathFromData(HiBinaryData::SpecialSymbols::scriptProcessor, sizeof(HiBinaryData::SpecialSymbols::scriptProcessor));
		break;
	}
	case FloatingTileContent::Factory::PopupMenuOptions::ScriptContent:
	{
		path.loadPathFromData(BackendBinaryData::ToolbarIcons::customInterface, sizeof(BackendBinaryData::ToolbarIcons::customInterface));
		break;
	}
	case FloatingTileContent::Factory::PopupMenuOptions::TablePanel:
	{
		static const unsigned char pathData[] = { 110,109,0,208,241,65,0,192,141,66,108,0,208,241,65,0,192,144,66,108,0,208,241,65,0,38,222,66,108,0,219,140,66,0,38,222,66,108,0,219,140,66,0,192,141,66,108,0,208,241,65,0,192,141,66,99,109,0,232,4,66,0,192,147,66,108,0,88,134,66,0,192,147,66,98,169,221,
			125,66,48,89,190,66,241,53,32,66,226,20,210,66,0,232,4,66,0,249,214,66,108,0,232,4,66,0,192,147,66,99,109,0,219,134,66,0,85,166,66,108,0,219,134,66,0,38,216,66,108,0,66,31,66,0,38,216,66,98,108,248,64,66,21,141,208,66,248,121,117,66,254,2,193,66,0,219,
			134,66,0,85,166,66,99,101,0,0 };
		path.loadPathFromData(pathData, sizeof(pathData));

		break;
	}
	case FloatingTileContent::Factory::PopupMenuOptions::SliderPackPanel:
	{
		static const unsigned char pathData[] = { 110,109,0,128,157,66,0,185,141,66,108,0,128,157,66,0,185,144,66,108,0,128,157,66,0,185,227,66,108,0,128,243,66,0,185,227,66,108,0,128,243,66,0,185,141,66,108,0,128,157,66,0,185,141,66,99,109,0,128,163,66,0,185,147,66,108,0,128,237,66,0,185,147,66,108,
			0,128,237,66,0,185,221,66,108,0,0,233,66,0,185,221,66,108,0,0,233,66,0,185,154,66,108,0,0,227,66,0,185,154,66,108,0,0,227,66,0,185,221,66,108,0,0,223,66,0,185,221,66,108,0,0,223,66,0,185,164,66,108,0,0,217,66,0,185,164,66,108,0,0,217,66,0,185,221,66,
			108,0,0,213,66,0,185,221,66,108,0,0,213,66,0,185,174,66,108,0,0,207,66,0,185,174,66,108,0,0,207,66,0,185,221,66,108,0,0,203,66,0,185,221,66,108,0,0,203,66,0,185,194,66,108,0,0,197,66,0,185,194,66,108,0,0,197,66,0,185,221,66,108,0,0,193,66,0,185,221,66,
			108,0,0,193,66,0,185,184,66,108,0,0,187,66,0,185,184,66,108,0,0,187,66,0,185,221,66,108,0,0,183,66,0,185,221,66,108,0,0,183,66,0,185,194,66,108,0,0,177,66,0,185,194,66,108,0,0,177,66,0,185,221,66,108,0,0,173,66,0,185,221,66,108,0,0,173,66,0,185,204,66,
			108,0,0,167,66,0,185,204,66,108,0,0,167,66,0,185,221,66,108,0,128,163,66,0,185,221,66,108,0,128,163,66,0,185,147,66,99,101,0,0 };

		path.loadPathFromData(pathData, sizeof(pathData));


		break;
	}
	case FloatingTileContent::Factory::PopupMenuOptions::Console:
	{
		path.loadPathFromData(BackendBinaryData::ToolbarIcons::debugPanel, sizeof(BackendBinaryData::ToolbarIcons::debugPanel));
		break;
	}
	case FloatingTileContent::Factory::PopupMenuOptions::ApiCollection:
	{
		path.loadPathFromData(BackendBinaryData::ToolbarIcons::apiList, sizeof(BackendBinaryData::ToolbarIcons::apiList));
		break;
	}
	case FloatingTileContent::Factory::PopupMenuOptions::ScriptWatchTable:
	{
		path.loadPathFromData(BackendBinaryData::ToolbarIcons::viewPanel, sizeof(BackendBinaryData::ToolbarIcons::viewPanel));
		break;
	}
	case FloatingTileContent::Factory::PopupMenuOptions::ScriptComponentEditPanel:
	{
		path.loadPathFromData(BackendBinaryData::ToolbarIcons::mixer, sizeof(BackendBinaryData::ToolbarIcons::mixer));
		path.applyTransform(AffineTransform::rotation(float_Pi / 2.0f));

		break;
	}
	case FloatingTileContent::Factory::PopupMenuOptions::ModuleBrowser:
	{
		path.loadPathFromData(BackendBinaryData::ToolbarIcons::modulatorList, sizeof(BackendBinaryData::ToolbarIcons::modulatorList));
		break;
	}
	case FloatingTileContent::Factory::PopupMenuOptions::PatchBrowser:
	{

	}
		break;
	case FloatingTileContent::Factory::PopupMenuOptions::FileBrowser:
	{
		path.loadPathFromData(BackendBinaryData::ToolbarIcons::fileBrowser, sizeof(BackendBinaryData::ToolbarIcons::fileBrowser));
		break;
	}
		
	case FloatingTileContent::Factory::PopupMenuOptions::toggleLayoutMode:
		break;
	case FloatingTileContent::Factory::PopupMenuOptions::toggleGlobalLayoutMode:
		break;
	case FloatingTileContent::Factory::PopupMenuOptions::exportAsJSON:
		break;
	case FloatingTileContent::Factory::PopupMenuOptions::loadFromJSON:
		break;
	case FloatingTileContent::Factory::PopupMenuOptions::MenuCommandOffset:
		break;
	case FloatingTileContent::Factory::PopupMenuOptions::numOptions:
		break;
	default:
		break;
	}

	if (!path.isEmpty())
	{
		auto d = new DrawablePath();
		d->setPath(path);

		return d;
	}
	else
		return nullptr;
}



void FloatingTileContent::Factory::addToPopupMenu(PopupMenu& m, PopupMenuOptions type, const String& name, bool isEnabled, bool isTicked)
{
	m.addItem((int)type, name, isEnabled, isTicked, getIcon(type));
}

void addCommandIcon(FloatingTile* parent, PopupMenu& m, int commandID)
{
	ApplicationCommandInfo r(commandID);

	parent->getRootWindow()->getCommandInfo(commandID, r);

	m.addItem(10000 + commandID, r.shortName);
}

void FloatingTileContent::Factory::handlePopupMenu(PopupMenu& m, FloatingTile* parent)
{
	if (parent->canBeDeleted())
	{
		if (parent->isLayoutModeEnabled())
		{
			m.addSectionHeader("Layout Elements");

			addToPopupMenu(m, PopupMenuOptions::Tabs, "Tabs");
			addToPopupMenu(m, PopupMenuOptions::HorizontalTile, "Horizontal Tile");
			addToPopupMenu(m, PopupMenuOptions::VerticalTile, "Vertical Tile");
			addToPopupMenu(m, PopupMenuOptions::Spacer, "Spacer");

			PopupMenu combinedLayouts;

			addToPopupMenu(combinedLayouts, PopupMenuOptions::Matrix2x2, "2x2 Matrix");
			addToPopupMenu(combinedLayouts, PopupMenuOptions::ThreeColumns, "3 Columns");
			addToPopupMenu(combinedLayouts, PopupMenuOptions::ThreeRows, "3 Rows");

			m.addSubMenu("Combined Layouts", combinedLayouts);
		}

		m.addSectionHeader("Scripting Tools");
		
		addToPopupMenu(m, PopupMenuOptions::GlobalConnectorPanel, "Sibling Panel Setter");
		addToPopupMenu(m, PopupMenuOptions::ScriptEditor, "Script Editor");
		addToPopupMenu(m, PopupMenuOptions::ScriptContent, "Script Content");
		addToPopupMenu(m, PopupMenuOptions::ScriptComponentEditPanel, "Script Interface Property Editor");
		addToPopupMenu(m, PopupMenuOptions::ApiCollection, "API Browser");
		addToPopupMenu(m, PopupMenuOptions::ScriptWatchTable, "Live Variable View");
		addToPopupMenu(m, PopupMenuOptions::Console, "Console");
		
		m.addSectionHeader("Sampler Tools");

		addToPopupMenu(m, PopupMenuOptions::SampleMapEditor, "Sample Map Editor");
		addToPopupMenu(m, PopupMenuOptions::SampleEditor, "Sample Editor");


		m.addSectionHeader("Misc Tools");
		
		addToPopupMenu(m, PopupMenuOptions::TablePanel, "Table Editor");
		addToPopupMenu(m, PopupMenuOptions::ModuleBrowser, "Module Browser");
		addToPopupMenu(m, PopupMenuOptions::PatchBrowser, "Patch Browser");
		addToPopupMenu(m, PopupMenuOptions::FileBrowser, "File Browser");
		addToPopupMenu(m, PopupMenuOptions::SliderPackPanel, "Array Editor");
		addToPopupMenu(m, PopupMenuOptions::MidiKeyboard, "Virtual Keyboard");
		addToPopupMenu(m, PopupMenuOptions::Note, "Note");
		
		m.addSeparator();

		PopupMenu icons;

		addCommandIcon(parent, icons, BackendCommandTarget::MainToolbarCommands::MenuNewFile);
		addCommandIcon(parent, icons, BackendCommandTarget::MainToolbarCommands::MenuOpenFile);
		addCommandIcon(parent, icons, BackendCommandTarget::MainToolbarCommands::MenuSaveFile);
		addCommandIcon(parent, icons, BackendCommandTarget::MainToolbarCommands::MenuEditUndo);
		addCommandIcon(parent, icons, BackendCommandTarget::MainToolbarCommands::MenuEditRedo);
		addCommandIcon(parent, icons, BackendCommandTarget::MainToolbarCommands::Settings);
		
		m.addSubMenu("Icons", icons);
	}

	m.addItem((int)PopupMenuOptions::toggleGlobalLayoutMode, "Toggle Global Layout Mode", true, parent->isLayoutModeEnabled());
	m.addItem((int)PopupMenuOptions::exportAsJSON, "Export as JSON", true, false);
	m.addItem((int)PopupMenuOptions::loadFromJSON, "Load JSON from clipboard", parent->canBeDeleted(), false);



	const int result = m.show();

	if (result > (int)PopupMenuOptions::MenuCommandOffset)
	{
		int c = result - (int)PopupMenuOptions::MenuCommandOffset;
		parent->setNewContent("Icon");
		return;
	}

	PopupMenuOptions resultOption = (PopupMenuOptions)result;



	switch (resultOption)
	{
	case PopupMenuOptions::Cancel:				return;
	case PopupMenuOptions::Empty:				parent->setNewContent(GET_PANEL_NAME(EmptyComponent)); break;
	case PopupMenuOptions::Spacer:				parent->setNewContent(GET_PANEL_NAME(SpacerPanel)); break;
	case PopupMenuOptions::HorizontalTile:		parent->setNewContent(GET_PANEL_NAME(HorizontalTile)); break;
	case PopupMenuOptions::VerticalTile:		parent->setNewContent(GET_PANEL_NAME(VerticalTile)); break;
	case PopupMenuOptions::Tabs:				parent->setNewContent(GET_PANEL_NAME(FloatingTabComponent)); break;
	case PopupMenuOptions::Matrix2x2:			FloatingPanelTemplates::create2x2Matrix(parent); break;
	case PopupMenuOptions::ThreeColumns:		FloatingPanelTemplates::create3Columns(parent); break;
	case PopupMenuOptions::ThreeRows:			FloatingPanelTemplates::create3Rows(parent); break;
	case PopupMenuOptions::Note:				parent->setNewContent(GET_PANEL_NAME(Note)); break;
	case PopupMenuOptions::MidiKeyboard:		parent->setNewContent(GET_PANEL_NAME(MidiKeyboardPanel)); break;
	case PopupMenuOptions::TablePanel:			parent->setNewContent(GET_PANEL_NAME(TableEditorPanel)); break;
	case PopupMenuOptions::SampleMapEditor:		parent->setNewContent(GET_PANEL_NAME(SampleMapEditorPanel)); break;
	case PopupMenuOptions::SampleEditor:		parent->setNewContent(GET_PANEL_NAME(SampleEditorPanel)); break;
	case PopupMenuOptions::ScriptEditor:		parent->setNewContent(GET_PANEL_NAME(CodeEditorPanel)); break;
	case PopupMenuOptions::ScriptContent :		parent->setNewContent(GET_PANEL_NAME(ScriptContentPanel)); break;
	case PopupMenuOptions::ScriptComponentEditPanel: parent->setNewContent(GET_PANEL_NAME(GenericPanel<ScriptComponentEditPanel>)); break;
	case PopupMenuOptions::SliderPackPanel:		parent->setNewContent(GET_PANEL_NAME(SliderPackPanel)); break;
	case PopupMenuOptions::GlobalConnectorPanel:parent->setNewContent(GET_PANEL_NAME(GlobalConnectorPanel)); break;
	case PopupMenuOptions::Console:				parent->setNewContent(GET_PANEL_NAME(ConsolePanel)); break;
	case PopupMenuOptions::ApiCollection:		parent->setNewContent(GET_PANEL_NAME(GenericPanel<ApiCollection>)); break;
	case PopupMenuOptions::PatchBrowser:		parent->setNewContent(GET_PANEL_NAME(GenericPanel<PatchBrowser>)); break;
	case PopupMenuOptions::FileBrowser:			parent->setNewContent(GET_PANEL_NAME(GenericPanel<FileBrowser>)); break;
	case PopupMenuOptions::ModuleBrowser:		parent->setNewContent(GET_PANEL_NAME(GenericPanel<ModuleBrowser>)); break;
	case PopupMenuOptions::ScriptWatchTable:		parent->setNewContent(GET_PANEL_NAME(GenericPanel<ScriptWatchTable>)); break;
	case PopupMenuOptions::toggleGlobalLayoutMode:    parent->getRootComponent()->setLayoutModeEnabled(!parent->isLayoutModeEnabled()); break;
	case PopupMenuOptions::exportAsJSON:		SystemClipboard::copyTextToClipboard(parent->exportAsJSON()); break;
	case PopupMenuOptions::loadFromJSON:		parent->loadFromJSON(SystemClipboard::getTextFromClipboard()); break;
	case PopupMenuOptions::numOptions:
	default:
		jassertfalse;
		break;
	}
}

