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
 *   which also must be licenced for commercial applications:
 *
 *   http://www.juce.com
 *
 *   ===========================================================================
 */

#pragma once

namespace scriptnode
{
using namespace juce;
using namespace hise;

struct NodeContainer : public AssignableObject
{
	struct MacroParameter : public NodeBase::Parameter
	{
		struct Connection
		{
			Connection(NodeBase* parent, ValueTree d);

			DspHelpers::ParameterCallback createCallbackForNormalisedInput();
			bool isValid() const { return p.get() != nullptr || nodeToBeBypassed.get() != nullptr; };

			bool matchesTarget(const Parameter* target) const
			{
				return target == p.get();
			}

			Identifier getOpType() const { return opType; };

		private:

			void updateConnectionInTargetParameter(Identifier id, var newValue);

			ValueTree targetNodeData;
			ValueTree connectionData;

			UndoManager* um = nullptr;
			NodeBase::Ptr nodeToBeBypassed;
			double rangeMultiplerForBypass = 1.0;

			valuetree::PropertyListener opSyncer;
			valuetree::PropertyListener idUpdater;
			
			valuetree::RemoveListener nodeRemoveUpdater;

			Identifier conversion = ConverterIds::Identity;
			Identifier opType = OperatorIds::SetValue;
			ReferenceCountedObjectPtr<Parameter> p;
			NormalisableRange<double> connectionRange;
			bool inverted = false;
		};

		ValueTree getConnectionTree();

		MacroParameter(NodeBase* parentNode, ValueTree data_);;

		void rebuildCallback();
		void updateRangeForConnection(ValueTree v, Identifier);

		Identifier getOpTypeForParameter(Parameter* target) const;

		bool matchesTarget(const Parameter* target) const;

		NormalisableRange<double> inputRange;

		valuetree::ChildListener connectionListener;
		valuetree::RecursivePropertyListener rangeListener;

		OwnedArray<Connection> connections;
	};

	NodeContainer();

	void resetNodes();

	NodeBase* asNode();
	const NodeBase* asNode() const;

	void prepareContainer(PrepareSpecs ps);

	void prepareNodes(PrepareSpecs ps);

	bool shouldCreatePolyphonicClass() const;

	virtual bool isPolyphonic() const;

	virtual void assign(const int index, var newValue) override;

	/** Return the value for the specified index. The parameter passed in must relate to the index created with getCachedIndex. */
	var getAssignedValue(int index) const override
	{
		return var(nodes[index]);
	}

	virtual int getBlockSizeForChildNodes() const { return originalBlockSize; }
	virtual double getSampleRateForChildNodes() const { return originalSampleRate; }

	virtual int getCachedIndex(const var &indexExpression) const override;

	// ===================================================================================

	void clear();

	String createCppClassForNodes(bool isOuterClass);
	String createTemplateAlias();
	NodeBase::List getChildNodesRecursive();
	void fillAccessors(Array<CppGen::Accessor>& accessors, Array<int> currentPath);
	virtual String getCppCode(CppGen::CodeLocation location);
	ValueTree getNodeTree() { return asNode()->getValueTree().getOrCreateChildWithName(PropertyIds::Nodes, asNode()->getUndoManager()); }

	NodeBase::List& getNodeList() { return nodes; }
	const NodeBase::List& getNodeList() const { return nodes; }

protected:

	void initListeners();

	friend class ContainerComponent;

	NodeBase::List nodes;

	double originalSampleRate = 0.0;
	int originalBlockSize = 0;

	virtual void channelLayoutChanged(NodeBase* nodeThatCausedLayoutChange) { ignoreUnused(nodeThatCausedLayoutChange); };

private:

	void nodeAddedOrRemoved(ValueTree v, bool wasAdded);
	void parameterAddedOrRemoved(ValueTree v, bool wasAdded);
	void updateChannels(ValueTree v, Identifier id);

	valuetree::ChildListener nodeListener;
	valuetree::ChildListener parameterListener;
	valuetree::RecursivePropertyListener channelListener;

	int* lastVoiceIndex = nullptr;
	bool channelRecursionProtection = false;
};

class SerialNode : public NodeBase,
				   public NodeContainer
{
public:

	class DynamicSerialProcessor: public HiseDspBase
	{
	public:

		SET_HISE_NODE_EXTRA_HEIGHT(0);
		SET_HISE_NODE_IS_MODULATION_SOURCE(false);

		bool handleModulation(double&);
		void handleHiseEvent(HiseEvent& e) final override;
		void initialise(NodeBase* p);
		void reset();
		void prepare(PrepareSpecs);
		void process(ProcessData& d);
		void processSingle(float* frameData, int numChannels);
		void createParameters(Array<ParameterData>& ) override {};

		DynamicSerialProcessor& getObject() { return *this; }
		const DynamicSerialProcessor& getObject() const { return *this; }

		NodeContainer* parent;
	};

	SerialNode(DspNetwork* root, ValueTree data);

	Identifier getObjectName() const override { return "SerialNode"; };
	NodeComponent* createComponent() override;
	Rectangle<int> getPositionInCanvas(Point<int> topLeft) const override;

	String createCppClass(bool isOuterClass) override;
	String getCppCode(CppGen::CodeLocation location) override;
};

class ParallelNode : public NodeBase,
	public NodeContainer
{
public:

	ParallelNode(DspNetwork* root, ValueTree data);
	String createCppClass(bool isOuterClass) override;
	String getCppCode(CppGen::CodeLocation location) override;
	NodeComponent* createComponent() override;
	Rectangle<int> getPositionInCanvas(Point<int> topLeft) const override;
};

class NodeContainerFactory : public NodeFactory
{
public:

	NodeContainerFactory(DspNetwork* parent);
	Identifier getId() const override { RETURN_STATIC_IDENTIFIER("container"); };
};

}
