
SkoarpuscleSample : Skoarpuscle {

	var <buffer;
	var <bufnum;
	var <channels;

	flatten {
		| m |
		^bufnum;
	}

	skoar_msg {
		| msg, minstrel |
		var sel = msg.val;
		var should_compile_ugen = false;
		var ret;
		("SKRP_Sample :: msg :: " ++ sel).postln;
		
		case {sel == \a} {
			
			var func = {
				| controls, sustain |
				PlayBuf.ar(channels, bufnum, BufRateScale.kr(bufnum), doneAction:2)
			};

			var debug = "{ | controls, sustain | PlayBuf.ar("++channels++", "++bufnum++", BufRateScale.kr("++bufnum++"), doneAction:2) };";

			should_compile_ugen = true;
			ret = SkoarpuscleUGen.new_with(\PlayBuf, func, debug, \audio);
			
		} {sel == \k} {
			var func = {
				| controls, sustain |
				PlayBuf.kr(channels, bufnum, BufRateScale.kr(bufnum), doneAction:2)
			};

			var debug = "{ | controls, sustain | PlayBuf.kr("++channels++", "++bufnum++", BufRateScale.kr("++bufnum++"), doneAction:2) };";

			ret = SkoarpuscleUGen.new_with(\PlayBuf, func, debug, \control);

		} {sel == \kDur} {
			var func = {
				| controls, sustain |
				BufDur.kr(bufnum)
			};

			var debug = "{ | controls, sustain | BufDur.kr("++bufnum++") };";

			ret = SkoarpuscleUGen.new_with(\BufDur, func, debug, \control);

		} {sel == \kFrames} {
			var func = {
				| controls, sustain |
				BufFrames.kr(bufnum)
			};

			var debug = "{ | controls, sustain | BufFrames.kr("++bufnum++") };";

			ret = SkoarpuscleUGen.new_with(\BufFrames, func, debug, \control);

		} {sel == \kChannels} {
			var func = {
				| controls, sustain |
				BufChannels.kr(bufnum)
			};

			var debug = "{ | controls, sustain | BufChannels.kr("++bufnum++") };";

			ret = SkoarpuscleUGen.new_with(\BufChannels, func, debug, \control);

		} {sel == \kSampleRate} {
			var func = {
				| controls, sustain |
				BufSampleRate.kr(bufnum)
			};

			var debug = "{ | controls, sustain | BufSampleRate.kr("++bufnum++") };";

			ret = SkoarpuscleUGen.new_with(\BufSampleRate, func, debug, \control);

		} {sel == \kSamples} {
			var func = {
				| controls, sustain |
				BufSamples.kr(bufnum)
			};

			var debug = "{ | controls, sustain | BufSamples.kr("++bufnum++") };";

			ret = SkoarpuscleUGen.new_with(\BufSamples, func, debug, \control);

		} {sel == \kRateScale} {
			var func = {
				| controls, sustain |
				BufRateScale.kr(bufnum)
			};

			var debug = "{ | controls, sustain | BufRateScale.kr("++bufnum++") };";

			ret = SkoarpuscleUGen.new_with(\BufRateScale, func, debug, \control);

		} {
			if (buffer.respondsTo(sel)) {
				ret = buffer.performMsg(msg.get_msg_arr(minstrel));
			};
		};

		minstrel.fairy.impress(ret);
		if (should_compile_ugen == true) {
			minstrel.fairy.compile_ugen;
		};
		^ret;
		
	}
	
}

SkoarpuscleFileSample : SkoarpuscleSample {

	var <filename;

	init {
		| x |
		if (Server.default.sampleRate.isNil) {
			SkoarError("SkoarpuscleFileSample :: scsynth appears offline :: boot the server.").throw;
		};
		
		filename = x;
		buffer = Buffer.read(Server.default, filename);
		bufnum = buffer.bufnum;
		channels = 1;
	}

	asString { ^("File Sample: " ++ filename) }

	
}
