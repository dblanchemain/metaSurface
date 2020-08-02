declare name "parametricEqFaust";
declare version "0.0";
declare author "JOS";
declare description "parametric_eq mono";
import("stdfaust.lib");
ma = library("maths.lib");
ba = library("basics.lib");
de = library("delays.lib");
si = library("signals.lib");
an = library("analyzers.lib");
fi = library("filters.lib");
os = library("oscillators.lib");
no = library("noises.lib");
ef = library("misceffects.lib");
co = library("compressors.lib");
ve = library("vaeffects.lib");
pf = library("phaflangers.lib");
re = library("reverbs.lib");
en = library("envelopes.lib");
//--------------------------`(dm.)parametric_eq_demo`------------------------------
// A parametric equalizer application.
//
// #### Usage:
//
// ```
// _ : parametric_eq_demo : _ ;
// ```
//------------------------------------------------------------
parametric_eq = fi.low_shelf(LL,FL) : fi.peak_eq(LP,FP,BP) : fi.high_shelf(LH,FH)
with{
	eq_group(x) = vgroup("[0] PARAMETRIC EQ SECTIONS [tooltip: See Faust's filters.lib for info and pointers]",x);
	ctrl_group(x) = eq_group(hgroup("[0] CTRL",x));
	
	ls_group(x) = ctrl_group(vgroup("[1] Low Shelf",x));
	
	
	LL = ls_group(hslider("[0] Low Boost_Cut [unit:dB] [style:knob]
		[tooltip: Amount of low-frequency boost or cut in decibels]",0,-40,40,0.1));
	FL = ls_group(hslider("[1] Transition Frequency [unit:Hz] [style:knob] [scale:log]
		[tooltip: Transition-frequency from boost (cut) to unity gain]",200,1,5000,1));

	pq_group(x) =  ctrl_group(vgroup("[2] Peaking Equalizer[tooltip: Parametric Equalizer
		sections from filters.lib]",x));
	LP = pq_group(hslider("[0] Peak Boost_Cut [unit:dB] [style:knob][tooltip: Amount of
		local boost or cut in decibels]",0,-40,40,0.1));
	FP = pq_group(hslider("[1] Peak Frequency [unit:PK] [style:knob] [tooltip: Peak
		Frequency in Piano Key (PK) units (A440 = 49PK)]",49,1,100,1)) : si.smooth(0.999)
		: ba.pianokey2hz;
	Q = pq_group(hslider("[2] Peak Q [style:knob] [scale:log] [tooltip: Quality factor
		(Q) of the peak = center-frequency/bandwidth]",40,1,1000,0.1));

	BP = FP/Q;

	hs_group(x) =  ctrl_group(vgroup("[3] High Shelf [tooltip: A high shelf provides a boost
		or cut above some frequency]",x));
	LH = hs_group(hslider("[0] High Boost_Cut [unit:dB] [style:knob] [tooltip: Amount of
		high-frequency boost or cut in decibels]",0,-40,40,.1));
	FH = hs_group(hslider("[1] Transition Frequency [unit:Hz] [style:knob] [scale:log]
	[tooltip: Transition-frequency from boost (cut) to unity gain]",8000,20,10000,1));
};
process = _: parametric_eq : _;
