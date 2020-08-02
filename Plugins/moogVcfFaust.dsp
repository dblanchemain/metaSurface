declare name "moogVcfFaust";
declare version "0.0";
declare author "RM";
declare description "moogVcfFaust mono";

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
re = library("reverbs.lib");//----------------------------------------------------
// Author: Romain Michon
// License: LGPL
//-------------------------`(dm.)moog_vcf_demo`---------------------------
// Illustrate and compare all three Moog VCF implementations above.
//
// #### Usage
//
// ```
// _ : moog_vcf_demo : _;
// ```
//------------------------------------------------------------
moog_vcf =  vcfarch : *(outgain)
with{
	mvcf_group(x) = vgroup("MOOG VCF (Voltage Controlled Filter) [tooltip: See Faust's
		vaeffects.lib for info and references]",x);
	cb_group(x) = mvcf_group(hgroup("[0]",x));

	archsw = cb_group(checkbox("[1] Use Biquads [tooltip: Select moog_vcf_2b (two-biquad)
		implementation, instead of the default moog_vcf (analog style) implementation]"));
	bqsw = cb_group(checkbox("[2] Normalized Ladders [tooltip: If using biquads, make
		them normalized ladders (moog_vcf_2bn)]"));

	freq = mvcf_group(hslider("[1] Corner Frequency [unit:PK] [tooltip: The VCF resonates
		at the corner frequency (specified in PianoKey (PK) units, with A440 = 49 PK).
		The VCF response is flat below the corner frequency, and rolls off -24 dB per
		octave above.]",
		25, 1, 88, 0.01) : ba.pianokey2hz) : si.smoo;

	res = mvcf_group(hslider("[2] Corner Resonance [style:knob] [tooltip: Amount of
		resonance near VCF corner frequency (specified between 0 and 1)]", 0.9, 0, 1, 0.01));

	outgain = mvcf_group(hslider("[3] VCF Output Level [unit:dB] [style:knob] [tooltip:
		output level in decibels]", 5, -60, 20, 0.1)) : ba.db2linear : si.smoo;

	vcfbq = _ <: select2(bqsw, ve.moog_vcf_2b(res,freq), ve.moog_vcf_2bn(res,freq));
	vcfarch = _ <: select2(archsw, ve.moog_vcf(res^4,freq), vcfbq);
};
process = _: moog_vcf : _;
