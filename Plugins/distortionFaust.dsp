declare name "distortionFaust";
declare version "0.0";
declare author "JOS, revised by RM";
declare description "Distortion demo application.";

import("stdfaust.lib");
cubicnl_mono = ef.cubicnl_nodc(drive:si.smoo,offset:si.smoo)
with{
	cnl_group(x)  = vgroup("CUBIC NONLINEARITY cubicnl [tooltip: Reference:
		https://ccrma.stanford.edu/~jos/pasp/Cubic_Soft_Clipper.html]", x);
	drive = cnl_group(hslider("[1] Drive [tooltip: Amount of distortion]",
		0, 0, 1, 0.01));
	offset = cnl_group(hslider("[2] Offset [tooltip: Brings in even harmonics]",
		0, 0, 1, 0.01));
};
process = cubicnl_mono;
