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

namespace scriptnode {
using namespace juce;
using namespace hise;

namespace meta
{

namespace width_bandpass_impl
{

using width_bandpass_ = container::chain<filters::svf, filters::svf>;

void instance::createParameters(Array<ParameterData>& data)
{
#define obj GET_PIMPL(width_bandpass_)
	// Node Registration ===============================================================
	registerNode(get<0>(obj), "hp");
	registerNode(get<1>(obj), "lp");

	// Parameter Initalisation =========================================================
	setParameterDefault("hp.Frequency", 20000.0);
	setParameterDefault("hp.Q", 1.0);
	setParameterDefault("hp.Gain", 0.0);
	setParameterDefault("hp.Smoothing", 0.00873185);
	setParameterDefault("hp.Mode", 1.0);
	setParameterDefault("lp.Frequency", 20000.0);
	setParameterDefault("lp.Q", 1.0);
	setParameterDefault("lp.Gain", 0.0);
	setParameterDefault("lp.Smoothing", 0.00873185);
	setParameterDefault("lp.Mode", 0.0);

	// Setting node properties =========================================================

	// Parameter Callbacks =============================================================
	{
		ParameterData p("Frequency", { 20.0, 20000.0, 0.1, 1.0 });
		p.setDefaultValue(20000.0);

		auto param_target1 = getCombinedParameter("hp.Frequency", { 20.0, 20000.0, 0.1, 0.229905 }, "SetValue");
		auto param_target2 = getCombinedParameter("lp.Frequency", { 20.0, 20000.0, 0.1, 0.229905 }, "SetValue");

		p.setCallback([param_target1, param_target2, outer = p.range](double newValue)
		{
			auto normalised = outer.convertTo0to1(newValue);
			param_target1->SetValue(normalised);
			param_target2->SetValue(normalised);
		});
		data.add(std::move(p));
	}
	{
		ParameterData p("Width", { 0.0, 1.0, 0.01, 1.0 });

		auto param_target1 = getCombinedParameter("hp.Frequency", { 0.0, 1.0, 0.1, 0.229905 }, "Multiply");
		auto param_target2 = getCombinedParameter("lp.Frequency", { 1.0, 16.0, 0.1, 0.229905 }, "Multiply");
		param_target2->addConversion(ConverterIds::SubtractFromOne, "Multiply");
		auto param_target3 = getParameter("hp.Q", { 1.0, 4.0, 0.1, 1.0 });
		auto param_target4 = getParameter("lp.Q", { 1.0, 4.0, 0.1, 1.0 });

		p.setCallback([param_target1, param_target2, param_target3, param_target4](double newValue)
		{
			param_target1->Multiply(newValue);
			param_target2->Multiply(newValue);
			param_target3(newValue);
			param_target4(newValue);
		});
		data.add(std::move(p));
	}
	{
		ParameterData p("Smoothing", { 0.0, 1.0, 0.01, 1.0 });
		p.setDefaultValue(0.24);

		auto param_target1 = getParameter("hp.Smoothing", { 0.0, 1.0, 0.01, 0.30103 });
		auto param_target2 = getParameter("lp.Smoothing", { 0.0, 1.0, 0.01, 0.30103 });

		p.setCallback([param_target1, param_target2](double newValue)
		{
			param_target1(newValue);
			param_target2(newValue);
		});
		data.add(std::move(p));
	}
#undef obj
}


String instance::getSnippetText() const
{
	return "737.3oc6V86aSCDE94ld7ihPJUvbGfUTTZ.DpSNhT0pH0j1hKvH5Z705S01mw4bCtvBBPBI9K.FfUlXhgxV+CfhPp+E.aHVBKLvBbmSSi+ET21zBEkawwWd268887688t5LcBnLR0IAk7nVTctwcVDaq6fa1DlB2fyb8mCyM.kQQMX1bL0l3Vngg3IT2yphA11lX1DTPJCA.LCqwJQ1VIWcQ.pvLYdtRiD1.UXVVDaNnLDp6uusLvx++RBKttuL52.a4r.0hTS3kSOLDrtRYMCVq4vtXKBm3J8+PcrlnKiUmn0DDttd.uNkjWCiLbhxkyhVhZJcPglqtzeEdnjqFS2yDyoL6EvtKS3BTCgXlvI67l3fUsWk3x6vxZT6agM8Hg8WM78ht2S2p7LrVD2YnVTdXKuoiS7cE1pwINZz0BN+Kdtb8NUsUHs5j1j6t4C9x0dj0lpxL5YPS4RtqGwtgOjHrPVv8kCVaoFF2a9d45hwvcWKih6t1t639Gu70e+Be6iA3NGZ9X3EZqBYOOWZiD4YnTp44RajRdVX6ti2tvRh2SflV1nEKhgKT1UHCPRH2VMMHCPZPtsZXHe+y+lo+zZONFj+o+ql6bSt01kFZVLF2fZubOb+r2NVQkO+P0CHtyWN63NejT8Nb4OjpqIULRo5vkI7NmJkUfHpJlCTUFnpLPUYfpxdUUQlpCqpDoAMWH1fh2Vj0lzdnDgJVX7jsSJJUXBQnFRkhf6K06UQDkpRU029lS6fG4NgAi3HA4ZAPGAUUWHTQ49vrNK36HuRIRiv6D2+cjYfeCMM+OilwqgNIpyLjr1ImV2YhCFuFZ3CgZnZdlbpioOzuzi1uI2QD8QkJMwDEuJb.KhFEo4sH2U32obYVyZS16zssZR5Vr7QLci+YUNFrO0qjF+x2WmfmCMdl+NdrhXHz3EJBPxgH8Ff1WDAVerm704W+Cp6+AI8.TeJ4dTdojrqAb7llQtmxuvJWgaG";
}

DSP_METHODS_PIMPL_IMPL(width_bandpass_);

REGISTER_MONO;

}

namespace filter_delay_impl
{

// Template Alias Definition =======================================================
using frame2_block2_ = container::frame2_block<routing::receive, meta::width_bandpass, core::fix_delay, routing::send>;
using filter_delay_ = container::chain<bypass::yes<routing::matrix>, bypass::yes<routing::matrix>, bypass::yes<routing::matrix>, wrap::mod<core::tempo_sync>, core::gain, frame2_block2_>;

String instance::getSnippetText() const
{
	return "1579.3oc6X0zbaSDFdUR1jlOZoLzYJ+BXfofFY4j51CfsiMt0M1ocrcKeLcFOxVqsUhjVUYojpxAlggCbqmgqbmgqbD9KvAlggKvufdggqrq9bWI4T2z3PNfujrR6p8884448ic2Gqh.Ba0rNP3JvQZ5NH69pHcEOPCkgNXauGn3LAH7lvgXSGEMSjs3vIj+B120n1DESSj9TfvxPYPK7vCS8PIv9jOeMrN10NXbMrgAxzAHrDL5++DMU5N.gEkj.65YoLcZGECqdZFn1juxJPYIP2I3iefhshAhXe9e5BfF1HzyPpA12aAIuRQjyAB9VH0fcNb5MUy3nBKSsxo.fvp66iFaRQiMg5nQN8wl5ofhqBswtNZliEMTbr0d54KRj3TBKU2yTwPaXvinFlOyTPLbiAMv5pAteAxpaiUc0Ubzvl8TrGibHNLnSfmzNvQDfDqtKwBGh3cnvQRAVdWjopD0b9fBQuoP3P5qh9e.CgQFXisP1NZ93rP3HJ1Gn79XiAHUhwVWwQA7HEcWBMffkjEKhu0t26Fc1qoWoNxx02Ca15Iip13yjb630tXo8lZdPWosa0okaoNsMlT8dMzZcrXsVhG5VcTwZGrWspFetJVT26FU2cz8viOpXsNcJN3SEEu6g0mb.3AtCz0FF3Y.F9+RvoDSGguHQ9uJDNiPY4EN4S2vyTtWCVZmydteTQu61qY655GzRTbjrkzwGNS9eKns13I+eBfTZf3v7yAQvDXoseMEA2.MZzntsc6Mxqp0AM1cx80DeXq6FoAZs8Qia0LOMvknl0kgNHCKb+odlCkyVPzFIl79yWUfvx4vlBBoeHPXc5FRK5sIon2SCq3ESLAunN8gzOOno4QDVIpjYaMyPlvejxSCGsJrfDwzZgOFY2RyPyIXBOzxJdb3T55fr5p8LD0ajDIxiCQGG.iDKi7jhREjJxKTDVJdDMRbtLnUfEt0IZN9SHwX7UpLlBcLkuWC1ixmQ5u0WA3+6cpTCSnvgTbk1pAa2Ch9318s54YQVwFvtHmfUCXbi0msaTf2MtYJ2nPZ23lygarErsqtilktFYyS4KWsBWjHqZeM3XR1iT57MCz4iO2a4KWENeVjkRkEYKXGzzH7mQnvEdmZMuA7gSQyyxdkknqRxAJwpRoulkcCm.KA6Wg8DiY1QbaYY4R977pv6PokTLL.vpVuFuZsookqyqgbcQlFHnq6tFXryDRMIPbTgbbV40BnrQTSUt+.ch9Kkd8sYNnB6zVPh2jyNrBSjzVPUcu9iFzmTcMcYindGrQCQZGgtvETktz7kgUUU6g6pM1TQGvj2Z1gGBu5YvoevSRH4mpKVEsJQyHketuMfMPH0AJDFONt3i1329dqO72KyFWbc93h3EkWnACydU3wTXt+.ESU+lt3X2qCG5N0AaHlZRbzITXIBlmgkCTRQbLTHHPNjk2D1v07PuAXuMRS2BuOYpYo6nrAaWYFbNKgsb9A+jUFSWIeuDRK7YeyuVgk5RlIKAlL2DZb8U9tuk96mJykPHb8unbPBAxA2ehKxbnWBg5urc94Jf42tAfL1MYGxytAfbraxbYs6u3Z+vc9ym80mfcuFLffh2xm+K+8693m+Wku.ay4j7MYClYaCrMVl5bR9sNj71KBo5lUY7M9urlWRC37vdkurR1N5oY5NkUqk29kZ4jo7xavjjjUQEkiA+ieUkSPmDVTjzxBmN4Jw0DmRN83E9BhaAYpiD59bE7mYgwYefXdc4pLr6JzsbcXzI5mE6tFTV71291Izwi8y27OkEDRrV+T8rEA2L4vgIW1I2gC2.FeeCjE5qynAKvlpD.VifI4Tu7zUwmFkrCmbDBKHVHUbzNYzifbcn3auaA5ME37F4En2vcWTKPORlyiJd13QoEyLcncRZiLcukVIKLCnhMRjGph22ErT9T07JKNACNcmeB1rsE7hxYaKPpRly4ymFe9PO9K7hC93tTgSA.lWCN46I40fyKJmWCNRbMSF2zStM3jQGx1Y4bIDeO+bp+wbJDybRgTW5VxleFAlmmclmALiZ2ct.xnVgOK.xnM9LBDOOa4NGPL35YlKPL5qLefXzc6wgcg2ezqc1vE6Mcw2nz+B0P7WfA";
}

void instance::createParameters(Array<ParameterData>& data)
{
#define obj GET_PIMPL(filter_delay_)

	// Node Registration ===============================================================
	registerNode(get<0>(obj), "left_only");
	registerNode(get<1>(obj), "stereo");
	registerNode(get<2>(obj), "right_only");
	registerNode(get<3>(obj), "tempo_sync2");
	registerNode(get<4>(obj), "gain2");
	registerNode(get<5, 0>(obj), "dly_fb_out");
	registerNode(get<5, 1>(obj), "width_bandpass");
	registerNode(get<5, 2>(obj), "fix_delay");
	registerNode(get<5, 3>(obj), "dly_fb_in");

	// Parameter Initalisation =========================================================
	setParameterDefault("tempo_sync2.Tempo", 11.0);
	setParameterDefault("tempo_sync2.Multiplier", 4.0);
	setParameterDefault("gain2.Gain", 0.0);
	setParameterDefault("gain2.Smoothing", 20.0);
	setParameterDefault("dly_fb_out.Feedback", 0.41);
	setParameterDefault("width_bandpass.Frequency", 8811.2);
	setParameterDefault("width_bandpass.Width", 0.58);
	setParameterDefault("width_bandpass.Smoothing", 0.0);
	setParameterDefault("fix_delay.DelayTime", 500.0);
	setParameterDefault("fix_delay.FadeTime", 598.0);

	// Setting node properties =========================================================
	setNodeProperty("left_only.EmbeddedData", "72.3o8BJ+RKIy7R22DKonLqfAFY0uRyM37KsnjS04LRLu7RMmhAJFiLw.CL.kuAf3CjKCAmZdo.ly+ABfJogv3CRR3bX..HkDhj", false);
	setNodeProperty("stereo.EmbeddedData", "75.3o8BJ+RKIy7R22DKonLqfAFY0uRyM37KsnjS04LRLu7RMmhAJFiLw.CL.kuAf3CjKCAmZdo.ly+ABfJogf3yHTIMDljL..f2p0wk", false);
	setNodeProperty("right_only.EmbeddedData", "74.3o8BJ+RKIy7R22DKonLqfAFY0uRyM37KsnjS04LRLu7RMmhAJFiLw.CL.kuAf3+efffSMuTfyApjFBhOi.ULHIMDljL..L4vgLI", false);
	setNodeProperty("gain2.ResetValue", "0", false);
	setNodeProperty("gain2.UseResetValue", "0", false);
	setNodeProperty("dly_fb_out.AddToSignal", "1", false);
	setNodeProperty("dly_fb_in.Connection", "dly_fb_out", false);

	// Internal Modulation =============================================================
	{
		auto mod_target1 = getParameter("fix_delay.DelayTime", { 0.0, 1000.0, 0.1, 0.30103 });
		auto f = [mod_target1](double newValue)
		{
			mod_target1.callUnscaled(newValue);
		};


		setInternalModulationParameter(get<3>(obj), f);
	}

	// Parameter Callbacks =============================================================
	{
		ParameterData p("Channel", { 0.0, 2.999, 0.01, 1.0 });
		p.setDefaultValue(1.46);

		auto bypass_target1 = getParameter("left_only.Bypassed", { 0.0, 1.0, 0.5, 1.0 });
		auto bypass_target2 = getParameter("stereo.Bypassed", { 1.0, 2.0, 0.5, 1.0 });
		auto bypass_target3 = getParameter("right_only.Bypassed", { 2.0, 3.0, 0.5, 1.0 });

		p.setCallback([bypass_target1, bypass_target2, bypass_target3, outer = p.range](double newValue)
		{
			auto normalised = outer.convertTo0to1(newValue);
			bypass_target1.setBypass(newValue);
			bypass_target2.setBypass(newValue);
			bypass_target3.setBypass(newValue);
		});
		data.add(std::move(p));
	}
	{
		ParameterData p("Feedback", { 0.0, 1.0, 0.01, 1.0 });
		p.setDefaultValue(0.41);

		auto param_target1 = getParameter("dly_fb_out.Feedback", { 0.0, 1.0, 0.01, 1.0 });

		p.setCallback([param_target1](double newValue)
		{
			param_target1(newValue);
		});
		data.add(std::move(p));
	}
	{
		ParameterData p("Time", { 1.0, 16.0, 1.0, 1.0 });
		p.setDefaultValue(4.0);

		auto param_target1 = getParameter("tempo_sync2.Multiplier", { 1.0, 16.0, 1.0, 1.0 });

		p.setCallback([param_target1, outer = p.range](double newValue)
		{
			auto normalised = outer.convertTo0to1(newValue);
			param_target1(normalised);
		});
		data.add(std::move(p));
	}
	{
		ParameterData p("Frequency", { 0.0, 1.0, 0.01, 1.0 });
		p.setDefaultValue(0.44);

		auto param_target1 = getParameter("width_bandpass.Frequency", { 20.0, 20000.0, 0.1, 1.0 });

		p.setCallback([param_target1](double newValue)
		{
			param_target1(newValue);
		});
		data.add(std::move(p));
	}
	{
		ParameterData p("Width", { 0.0, 1.0, 0.01, 1.0 });
		p.setDefaultValue(0.58);

		auto param_target1 = getParameter("width_bandpass.Width", { 0.0, 1.0, 0.01, 1.0 });

		p.setCallback([param_target1](double newValue)
		{
			param_target1(newValue);
		});
		data.add(std::move(p));
	}
	{
		ParameterData p("Input", { 0.0, 1.0, 0.01, 1.0 });
		p.setDefaultValue(1.0);

		auto param_target1 = getParameter("gain2.Gain", { -100.0, 0.0, 0.1, 5.42227 });

		p.setCallback([param_target1](double newValue)
		{
			param_target1(newValue);
		});
		data.add(std::move(p));
	}

#undef obj
}

DSP_METHODS_PIMPL_IMPL(filter_delay_);

REGISTER_MONO;

}

DEFINE_FACTORY_FOR_NAMESPACE

}

}
