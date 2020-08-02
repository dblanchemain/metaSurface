declare name "granulatorFaust";
declare version "0.0";
declare author "RM";
declare description "granulator mono";

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
en = library("envelopes.lib");//----------------------------`granulator`-------------------------
// granulator Mono.
//
// #### Usage
//
// ```
// _: granulator : _;
// ```
//------------------------------------------------------------
//--------------------------`(Grain generator`------------------------------


// FOR 4 grains - MONO

// UI //////////////////////////////////////////
grainGrp(x) = vgroup("GRANULATOR",x);
parGrain(x)=grainGrp(hgroup("[0]",x));

ctGrain(x)=grainGrp(hgroup("[1]",x));
	
popul = 1 - ctGrain(vslider("population[BELA: ANALOG_0]", 1, 0, 1, 0.001));  // Coef 1= maximum; 0 = almost nothing (0.95)
taille = ctGrain(vslider("taille[BELA: ANALOG_1]", 100, 4, 200, 0.001 ));        // Size in millisecondes
decal = 1 - ctGrain(vslider("decal[BELA: ANALOG_2]",0,0,1,0.001));               // read position compared to table srite position

speed = ctGrain(vslider("speed[BELA: ANALOG_3]", 1, 0.125, 4, 0.001));

feedback = ctGrain(vslider("feedback[BELA: ANALOG_4]",0,0,2,0.001)); 

freq = 1000/taille;
tmpTaille = taille*ma.SR/ 1000;
clocSize = int(tmpTaille + (tmpTaille*popul*10)); // duration between 2 clicks

// CLK GENERAL /////////////////////////////////
// 4 clicks vers 4 generateurs de grains.
// (idem clk freq/4 et un compteur...)
detect1(x) = select2 (x < 10, 0, 1);
detect2(x) = select2 (x > clocSize*1/3, 0, 1) : select2 (x < (clocSize*1/3)+10, 0, _);
detect3(x) = select2 (x > clocSize*2/3, 0, 1) : select2 (x < (clocSize*2/3)+10, 0, _);
detect4(x) = select2 (x > clocSize-10, 0, 1);
cloc = (%(_,clocSize))~(+(1)) <: (detect1: trig),(detect2: trig),(detect3: trig),(detect4: trig);

// SIGNAUX Ctrls Player ////////////////////////
trig = _<:_,mem: >;
genvelop = *(2*ma.PI):+(ma.PI):cos:*(0.5):+(0.5);

rampe(f, t) = delta : (+ : select2(t,_,delta<0) : max(0)) ~ _ : raz
    with {
        raz(x) = select2 (x > 1, x, 0);
        delta = sh(f,t)/ma.SR;
        sh(x,t) = ba.sAndH(t,x);
    };

rampe2(speed, t) = delta : (+ : select2(t,_,delta<0) : max(0)) ~ _ 
    with {
        delta = sh(speed,t);
        sh(x,t) = ba.sAndH(t,x);
    };

// RWTable //////////////////////////////////////
unGrain(input, clk) = (linrwtable( wf , rindex) : *(0.2 * EnvGrain))
    with {
        SR = 44100;
        buffer_sec = 1;
        size = int(SR * buffer_sec);
        init = 0.;

        EnvGrain = clk : (rampe(freq) : genvelop);   

        windex = (%(_,size) ) ~ ( +(1) );
        posTabl = int(ba.sAndH(clk, windex));
        rindex = %(int(rampe2(speed, clk)) + posTabl + int(size * decal), size);

        wf = size, init, int(windex), input;
    };

// LINEAR_INTERPOLATION_RWTABLE //////////////////////////////////
// read rwtable with linear interpolation
// wf : waveform to read ( wf is defined by (size_buffer,init, windex, input ))
// x  : position to read (0 <= x < size(wf)) and float
// nota: rwtable(size, init, windex, input, rindex)

linrwtable(wf,x) = linterpolation(y0,y1,d)
    with {
        x0 = int(x);                //
        x1 = int(x+1);              //
        d  = x-x0;
        y0 = rwtable(wf,x0);        //
        y1 = rwtable(wf,x1);        //
        linterpolation(v0,v1,c) = v0*(1-c)+v1*c;
    };

// FINALISATION /////////////////////////////////////////////////////////////////////////////////////
routeur (a, b, c, d, e) = a, b, a, c, a, d, a, e;

processus = _ , cloc : routeur : (unGrain, unGrain, unGrain, unGrain) :> fi.dcblockerat(20);
grainGenerator=_<: ((+(_,_) :processus) ~(*(feedback))),((+(_,_) :processus) ~(*(feedback))):>_;

process = _: grainGenerator : _;
