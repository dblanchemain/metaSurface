declare name "filtersFaust";
declare version "0.0";
declare author "JOS, revised by RM";
declare description "Filters mono";
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
//================ Butterworth Lowpass/Highpass Filters ======================
// Nth-order Butterworth lowpass or highpass filters
//
// USAGE: 
//   _ : lowpass(N,fc) : _
//   _ : highpass(N,fc) : _
// where
//   N = filter order (number of poles) [nonnegative constant integer]
//   fc = desired cut-off frequency (-3dB frequency) in Hz
// REFERENCE: 
//  https://ccrma.stanford.edu/~jos/filters/Butterworth_Lowpass_Design.html
//  'butter' function in Octave ("[z,p,g] = butter(N,1,'s');")
// ACKNOWLEDGMENT
//  Generalized recursive formulation initiated by Yann Orlarey.

LPF=fi.lowpass(3,lfc)
	with {
		lfc=vslider("LPF Freq",1000, 20, 20000, 1);
};
HPF=fi.highpass(3,hfc)
	with {
		hfc=vslider("HPF Freq",1000, 20, 10000, 1);
};
filters=vgroup("FILTERS",hgroup("[1]",HPF:LPF));
process = _: filters : _;
