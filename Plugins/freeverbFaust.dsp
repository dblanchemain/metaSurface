declare name "freeverbFaust";
declare version "0.0";
declare author "RM";
declare description "Freeverb mono";

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
en = library("envelopes.lib");//----------------------------`(dm.)freeverb`-------------------------
// Freeverb Mono.
//
// #### Usage
//
// ```
// _: freeverb_demo : _;
// ```
//------------------------------------------------------------
freeverb = _<: (*(g)*fixedgain :re.mono_freeverb(combfeed, allpassfeed, damping, spatSpread)),*(1-g):> _
with{
	scaleroom   = 0.28;
	offsetroom  = 0.7;
	allpassfeed = 0.5;
	scaledamp   = 0.4;
	fixedgain   = 0.1;
	origSR = 48000;
	
	parameters(x) = hgroup("Freeverb",x);
	
	knobGroup(x) = parameters(vgroup("[1]",x));
	damping = knobGroup(vslider("[1] Damp [style: knob] [tooltip: Somehow control the
		density of the reverb.]",0.5, 0, 1, 0.025)*scaledamp*origSR/ma.SR);
	combfeed = knobGroup(vslider("[2] RoomSize [style: knob] [tooltip: The room size
		between 0 and 1 with 1 for the largest room.]", 0.5, 0, 1, 0.025)*scaleroom*
		origSR/ma.SR + offsetroom);
	spatSpread = knobGroup(vslider("[3] Stereo Spread [style: knob] [tooltip: Spatial
		spread between 0 and 1 with 1 for maximum spread.]",0.5,0,1,0.01)*46*ma.SR/origSR
		: int);
	g = parameters(vslider("[1] Wet [tooltip: The amount of reverb applied to the signal
		between 0 and 1 with 1 for the maximum amount of reverb.]", 0.3333, 0, 1, 0.025));
};
process = _: freeverb : _;
