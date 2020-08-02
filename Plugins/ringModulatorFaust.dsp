declare name "ringModulatorFaust";
declare version "0.0";
declare author "RM";
declare description "ringModulator";
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
//-------------------------Ring modulator---------------------------
// Ring Modulator effect  application.
//
// #### Usage
//
// ```
// _:ringModulator : _;
// ```
//------------------------------------------------------------
ringModulator = groupRM(hgroup("[1]",*(1-rmdepth*(os.osc(rmfreq)*0.5+0.5))))
with{
	groupRM(x)=vgroup("RING MODULATOR",x);
	
	rmfreq = vslider("frequency",5,0.1,1000,0.01) : si.smooth(0.999);
	rmdepth = vslider("depth",0,0,1,0.01) : si.smooth(0.999);
};
process = _: ringModulator : _;
