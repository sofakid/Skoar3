SkoarOps {

    var <assignment;

    var <addition;
	var <subtraction;
    var <multiplication;
    var <division;

    *new { ^super.new.init; }

    init {
		this.init_assignments;
		this.init_addition;
		this.init_subtraction;
		this.init_multiplication;
		this.init_division;
	}

	// -----------------
	// Assignment Tables
	// -----------------
	init_assignments {
	
        // v => settable
        assignment = (
        
            // settable
            SkoarpuscleSymbol: (

                // v
                Any: {
                    | minstrel, v, symbol |
					var s = symbol.val;

					if (s == \key) {
						v = SkoarpuscleKey(v);
					};

					//"settable: ".post; v.dump;

                    minstrel.koar[s] = v;
                    v
                }

            ),

			// settable
            SkoarpuscleSymbolColon: (

                // v
                Any: {
                    | minstrel, v, symbol |
					var s = symbol.val;

					if (s == \key) {
						v = SkoarpuscleKey(v);
					};

					//"key: ".post; s.postln;
					//"settable: ".post; v.dump;

                    minstrel.koar[s] = v;
                    v
                }

            ),

            // settable
            SkoarpuscleBeat: (

                // v - the bpm
                SkoarpuscleInt:   {
                    | minstrel, bpm, beat |
                    var x = bpm.val / 60 * beat.val;
                    minstrel.koar[\tempo] = x;
                    SkoarpuscleInt(x)
                },

                SkoarpuscleFloat: {
                    | minstrel, bpm, beat |
                    var x = bpm.val / 60.0 * beat.val;
                    minstrel.koar[\tempo] = x;
                    SkoarpuscleFloat(x)
                }
			)
            
        );
	}

	// ---------------
	// Addition Tables
	// ---------------
	init_addition {
	
		// x + y
        addition = (

			SkoarpuscleCat:   ( Any: { | x, y, m | SkoarpuscleCat.new } ),
			SkoarpuscleFalse: ( Any: { | x, y, m | x } ),
			SkoarpuscleTrue:  ( Any: { | x, y, m | y } ),

			SkoarpuscleEnvelope:  ( Any: { | x, y, m | SkoarpuscleCat.new } ),

			// x +
			SkoarpuscleUGen:  (
				// y
                SkoarpuscleInt:       { | x, y, m | x.add(y) },
                SkoarpuscleFloat:     { | x, y, m | x.add(y) },
				SkoarpuscleHashLevel: { | x, y, m | x.add(y) },
				SkoarpuscleFreq:      { | x, y, m | SkoarpuscleCat.new },

				SkoarpuscleNoat:      { | x, y, m | SkoarpuscleCat.new },
				SkoarpuscleChoard:    { | x, y, m | SkoarpuscleCat.new },

				SkoarpuscleFalse:     { | x, y, m | SkoarpuscleUGen(x.val * 0.0) },
				SkoarpuscleTrue:      { | x, y, m | x },

				SkoarpuscleSymbol:    { | x, y, m | SkoarpuscleCat.new },
				SkoarpuscleString:    { | x, y, m | SkoarpuscleCat.new },

                SkoarpuscleList:      { | x, y, m | SkoarpuscleCat.new },
				SkoarpuscleUGen:      { | x, y, m | x.add(y) },
				SkoarpuscleEnvelope:  { | x, y, m | x.add(y) },
			),

            // x +
            SkoarpuscleInt: (
                // y
                SkoarpuscleInt:       { | x, y, m | SkoarpuscleInt(x.val + y.val) },
                SkoarpuscleFloat:     { | x, y, m | SkoarpuscleFloat(x.val + y.val) },
				SkoarpuscleHashLevel: { | x, y, m | SkoarpuscleFloat(x.val + y.val) },
				SkoarpuscleFreq:      { | x, y, m | SkoarpuscleFreq(x.val + y.val) },

				SkoarpuscleNoat:      { | x, y, m | SkoarpuscleList([x, y]) },
				SkoarpuscleChoard:    { | x, y, m | SkoarpuscleList([x, y]) },

				SkoarpuscleFalse:     { | x, y, m | y },
				SkoarpuscleTrue:      { | x, y, m | x },

				SkoarpuscleSymbol:    { | x, y, m | SkoarpuscleSymbol(x.val.asSymbol ++ y.val) },
				SkoarpuscleString:    { | x, y, m | SkoarpuscleString(x.val.asString ++ y.val) },

                SkoarpuscleList:      { | x, y, m | SkoarpuscleList([x] ++ y.val) },
				SkoarpuscleUGen:      { | x, y, m | y.add(x) },
				SkoarpuscleEnvelope:  { | x, y, m | SkoarpuscleCat.new },

            ),

            // x +
            SkoarpuscleFloat: (
                // y
                SkoarpuscleInt:       { | x, y, m | SkoarpuscleFloat(x.val + y.val) },
                SkoarpuscleFloat:     { | x, y, m | SkoarpuscleFloat(x.val + y.val) },
				SkoarpuscleHashLevel: { | x, y, m | SkoarpuscleFloat(x.val + y.val) },
				SkoarpuscleFreq:      { | x, y, m | SkoarpuscleFreq(x.val + y.val) },

				SkoarpuscleNoat:      { | x, y, m | SkoarpuscleList([x, y]) },
				SkoarpuscleChoard:    { | x, y, m | SkoarpuscleList([x, y]) },

				SkoarpuscleFalse:     { | x, y, m | y },
				SkoarpuscleTrue:      { | x, y, m | x },
				SkoarpuscleCat:       { | x, y, m | SkoarpuscleCat.new },

				SkoarpuscleSymbol:    { | x, y, m | SkoarpuscleSymbol(x.val.asSymbol ++ y.val) },
				SkoarpuscleString:    { | x, y, m | SkoarpuscleString(x.val.asString ++ y.val) },

                SkoarpuscleList:      { | x, y, m | SkoarpuscleList([x] ++ y.val) },
				SkoarpuscleUGen:      { | x, y, m | y.add(x) },
				SkoarpuscleEnvelope:  { | x, y, m | SkoarpuscleCat.new },
			),

			// x +
            SkoarpuscleHashLevel: (
                // y
                SkoarpuscleInt:       { | x, y, m | SkoarpuscleFloat(x.val + y.val) },
                SkoarpuscleFloat:     { | x, y, m | SkoarpuscleFloat(x.val + y.val) },
				SkoarpuscleHashLevel: { | x, y, m | SkoarpuscleFloat(x.val + y.val) },
				SkoarpuscleFreq:      { | x, y, m | SkoarpuscleFreq(x.val + y.val) },

				SkoarpuscleNoat:      { | x, y, m | SkoarpuscleList([x, y]) },
				SkoarpuscleChoard:    { | x, y, m | SkoarpuscleList([x, y]) },

				SkoarpuscleFalse:     { | x, y, m | y },
				SkoarpuscleTrue:      { | x, y, m | x },

				SkoarpuscleSymbol:    { | x, y, m | SkoarpuscleSymbol(x.val.asSymbol ++ y.val) },
				SkoarpuscleString:    { | x, y, m | SkoarpuscleString(x.val.asString ++ y.val) },
                SkoarpuscleList:      { | x, y, m | SkoarpuscleList([x] ++ y.val) },
				SkoarpuscleUGen:      { | x, y, m | y.add(x) },
				SkoarpuscleEnvelope:  { | x, y, m | SkoarpuscleCat.new },

			),

			SkoarpuscleList: (
				// y
                SkoarpuscleInt:       { | x, y, m | SkoarpuscleList(x.val ++ [y]) },
                SkoarpuscleFloat:     { | x, y, m | SkoarpuscleList(x.val ++ [y]) },
				SkoarpuscleHashLevel: { | x, y, m | SkoarpuscleList(x.val ++ [y]) },
				SkoarpuscleFreq:      { | x, y, m | SkoarpuscleList(x.val ++ [y]) },

				SkoarpuscleNoat:      { | x, y, m | SkoarpuscleList(x.val ++ [y]) },
				SkoarpuscleChoard:    { | x, y, m | SkoarpuscleList(x.val ++ [y]) },

				SkoarpuscleFalse:     { | x, y, m | y },
				SkoarpuscleTrue:      { | x, y, m | x },
				SkoarpuscleCat:       { | x, y, m | SkoarpuscleCat.new },

				SkoarpuscleSymbol:    { | x, y, m | SkoarpuscleList(x.val ++ [y]) },
				SkoarpuscleString:    { | x, y, m | SkoarpuscleList(x.val ++ [y]) },

                SkoarpuscleList:      { | x, y, m | SkoarpuscleList(x.val ++ y.val)},
				SkoarpuscleUGen:      { | x, y, m | SkoarpuscleCat.new }, 
				SkoarpuscleEnvelope:  { | x, y, m | SkoarpuscleCat.new },
			),

			SkoarpuscleNoat: (
				SkoarpuscleInt:       { | x, y, m | x.raiseBy(y) },
                SkoarpuscleFloat:     { | x, y, m | x.raiseBy(y) },
				SkoarpuscleHashLevel: { | x, y, m | x.raiseBy(y) },
				SkoarpuscleFreq:      { | x, y, m | x.raiseBy(y) },

				SkoarpuscleNoat:      { | x, y, m | SkoarpuscleList([x, y]) },
				SkoarpuscleChoard:    { | x, y, m | SkoarpuscleList([x, y]) },

				SkoarpuscleFalse:     { | x, y, m | y },
				SkoarpuscleTrue:      { | x, y, m | x },

				SkoarpuscleSymbol:    { | x, y, m | SkoarpuscleSymbol(x.asSymbol ++ y.val) },
				SkoarpuscleString:    { | x, y, m | SkoarpuscleString(x.asString ++ y.val) },

                SkoarpuscleList:      { | x, y, m | SkoarpuscleList([x] ++ y.val) },
				SkoarpuscleUGen:      { | x, y, m | SkoarpuscleCat.new }, 
				SkoarpuscleEnvelope:  { | x, y, m | SkoarpuscleCat.new },
			),

			SkoarpuscleChoard: (
				SkoarpuscleInt:       { | x, y, m | x.raiseBy(y) },
                SkoarpuscleFloat:     { | x, y, m | x.raiseBy(y) },
				SkoarpuscleHashLevel: { | x, y, m | x.raiseBy(y) },
				SkoarpuscleFreq:      { | x, y, m | x.raiseBy(y) },

				SkoarpuscleNoat:      { | x, y, m | SkoarpuscleList([x, y]) },
				SkoarpuscleChoard:    { | x, y, m | SkoarpuscleList([x, y]) },

				SkoarpuscleFalse:     { | x, y, m | y },
				SkoarpuscleTrue:      { | x, y, m | x },

				SkoarpuscleSymbol:    { | x, y, m | SkoarpuscleSymbol(x.asSymbol ++ y.val) },
				SkoarpuscleString:    { | x, y, m | SkoarpuscleString(x.asString ++ y.val) },

                SkoarpuscleList:      { | x, y, m | SkoarpuscleList([x] ++ y.val) },
				SkoarpuscleUGen:      { | x, y, m | SkoarpuscleCat.new },
				SkoarpuscleEnvelope:  { | x, y, m | SkoarpuscleCat.new },
			),

			SkoarpuscleSymbol: (
				SkoarpuscleInt:       { | x, y, m | SkoarpuscleSymbol(x.val ++ y.val.asSymbol) },
                SkoarpuscleFloat:     { | x, y, m | SkoarpuscleSymbol(x.val ++ y.val.asSymbol) },
				SkoarpuscleHashLevel: { | x, y, m | SkoarpuscleSymbol(x.val ++ y.val.asSymbol) },
				SkoarpuscleFreq:      { | x, y, m | SkoarpuscleSymbol(x.val ++ y.val.asSymbol ++ 'Hz') },

				SkoarpuscleNoat:      { | x, y, m | SkoarpuscleSymbol(x.val ++ y.asSymbol) },
				SkoarpuscleChoard:    { | x, y, m | SkoarpuscleSymbol(x.val ++ y.asSymbol) },

				SkoarpuscleFalse:     { | x, y, m | y },
				SkoarpuscleTrue:      { | x, y, m | x },
				SkoarpuscleCat:       { | x, y, m | SkoarpuscleCat.new },

				SkoarpuscleSymbol:    { | x, y, m | SkoarpuscleSymbol(x.val ++ y.val) },
				SkoarpuscleString:    { | x, y, m | SkoarpuscleSymbol(x.val ++ y.val.asSymbol) },

                SkoarpuscleList:      { | x, y, m | SkoarpuscleList([x] ++ y.val) },
				SkoarpuscleUGen:      { | x, y, m | SkoarpuscleCat.new }, 
				SkoarpuscleEnvelope:  { | x, y, m | SkoarpuscleCat.new },
			),

			SkoarpuscleString: (
				SkoarpuscleInt:       { | x, y, m | SkoarpuscleString(x.val ++ y.val.asString) },
                SkoarpuscleFloat:     { | x, y, m | SkoarpuscleString(x.val ++ y.val.asString) },
				SkoarpuscleHashLevel: { | x, y, m | SkoarpuscleString(x.val ++ y.val.asString) },
				SkoarpuscleFreq:      { | x, y, m | SkoarpuscleString(x.val ++ y.val.asString ++ "Hz") },

				SkoarpuscleNoat:      { | x, y, m | SkoarpuscleString(x.val ++ y.asString) },
				SkoarpuscleChoard:    { | x, y, m | SkoarpuscleString(x.val ++ y.asString) },

				SkoarpuscleFalse:     { | x, y, m | y },
				SkoarpuscleTrue:      { | x, y, m | x },

				SkoarpuscleSymbol:    { | x, y, m | SkoarpuscleString(x.val ++ y.val.asString) },
				SkoarpuscleString:    { | x, y, m | SkoarpuscleString(x.val ++ y.val) },

                SkoarpuscleList:      { | x, y, m | SkoarpuscleList([x] ++ y.val) },
				SkoarpuscleUGen:      { | x, y, m | SkoarpuscleCat.new }, 
				SkoarpuscleEnvelope:  { | x, y, m | SkoarpuscleCat.new },
			),

			SkoarpuscleFreq: (
				
                // y
                SkoarpuscleInt:       { | x, y, m | SkoarpuscleFreq(x.val + y.val) },
                SkoarpuscleFloat:     { | x, y, m | SkoarpuscleFreq(x.val + y.val) },			 
				SkoarpuscleHashLevel: { | x, y, m | SkoarpuscleFreq(x.val + y.val) },			 
				SkoarpuscleFreq:      { | x, y, m | SkoarpuscleFreq(x.val + y.val) },

				SkoarpuscleNoat:      { | x, y, m | SkoarpuscleList([x, y]) },
				SkoarpuscleChoard:    { | x, y, m | SkoarpuscleList([x, y]) },
				
				SkoarpuscleFalse:     { | x, y, m | y },
				SkoarpuscleTrue:      { | x, y, m | x },

				SkoarpuscleSymbol:    { | x, y, m | SkoarpuscleSymbol(x.val.asSymbol ++ 'Hz' ++ y.val) },
				SkoarpuscleString:    { | x, y, m | SkoarpuscleString(x.val.asString ++ "Hz" ++ y.val) },

                SkoarpuscleList:      { | x, y, m | SkoarpuscleList([x] ++ y.val) },
				SkoarpuscleUGen:      { | x, y, m | SkoarpuscleCat.new }, 
				SkoarpuscleEnvelope:  { | x, y, m | SkoarpuscleCat.new },
				  
			)

        );
	}
	
	// ------------------
	// Subtraction Tables
	// ------------------
	init_subtraction {
	
		// x - y
        subtraction = (

			SkoarpuscleCat:   ( Any: { | x, y, m | SkoarpuscleCat.new } ),
			SkoarpuscleFalse: ( Any: { | x, y, m | x } ),
			SkoarpuscleTrue:  ( Any: { | x, y, m | y } ),

			SkoarpuscleEnvelope:  ( Any: { | x, y, m | SkoarpuscleCat.new } ),

			// x -
			SkoarpuscleUGen:  (
				// y
                SkoarpuscleInt:       { | x, y, m | x.sub(y) },
                SkoarpuscleFloat:     { | x, y, m | x.sub(y) },
				SkoarpuscleHashLevel: { | x, y, m | x.sub(y) },
				SkoarpuscleFreq:      { | x, y, m | SkoarpuscleCat.new },

				SkoarpuscleNoat:      { | x, y, m | SkoarpuscleCat.new },
				SkoarpuscleChoard:    { | x, y, m | SkoarpuscleCat.new },

				SkoarpuscleFalse:     { | x, y, m | y },
				SkoarpuscleTrue:      { | x, y, m | x },

				SkoarpuscleSymbol:    { | x, y, m | SkoarpuscleCat.new },
				SkoarpuscleString:    { | x, y, m | SkoarpuscleCat.new },

                SkoarpuscleList:      { | x, y, m | SkoarpuscleCat.new },
				SkoarpuscleUGen:      { | x, y, m | x.sub(y) },
				SkoarpuscleEnvelope:  { | x, y, m | x.sub(y) },
			),
			
            // x -
            SkoarpuscleInt: (
                // y
                SkoarpuscleInt:       { | x, y, m | SkoarpuscleInt(x.val - y.val) },
                SkoarpuscleFloat:     { | x, y, m | SkoarpuscleFloat(x.val - y.val) },
				SkoarpuscleHashLevel: { | x, y, m | SkoarpuscleFloat(x.val - y.val) },
				SkoarpuscleFreq:      { | x, y, m | SkoarpuscleFreq(x.val - y.val) },

				SkoarpuscleFalse:     { | x, y, m | y },
				SkoarpuscleTrue:      { | x, y, m | x },
            	SkoarpuscleUGen:      { | x, y, m | y.sub(x) },
				SkoarpuscleEnvelope:  { | x, y, m | SkoarpuscleCat.new },
			),

            // x -
            SkoarpuscleFloat: (
                // y
                SkoarpuscleInt:       { | x, y, m | SkoarpuscleFloat(x.val - y.val) },
                SkoarpuscleFloat:     { | x, y, m | SkoarpuscleFloat(x.val - y.val) },
				SkoarpuscleHashLevel: { | x, y, m | SkoarpuscleFloat(x.val - y.val) },
				SkoarpuscleFreq:      { | x, y, m | SkoarpuscleFreq(x.val - y.val) },
			
				SkoarpuscleFalse:     { | x, y, m | y },
				SkoarpuscleTrue:      { | x, y, m | x },
            	SkoarpuscleUGen:      { | x, y, m | y.sub(x) },
				SkoarpuscleEnvelope:  { | x, y, m | SkoarpuscleCat.new },
			),

			// x -
            SkoarpuscleHashLevel: (
                // y
                SkoarpuscleInt:       { | x, y, m | SkoarpuscleFloat(x.val - y.val) },
                SkoarpuscleFloat:     { | x, y, m | SkoarpuscleFloat(x.val - y.val) },
				SkoarpuscleHashLevel: { | x, y, m | SkoarpuscleFloat(x.val - y.val) },
				SkoarpuscleFreq:      { | x, y, m | SkoarpuscleFreq(x.val - y.val) },

				SkoarpuscleFalse:     { | x, y, m | y },
				SkoarpuscleTrue:      { | x, y, m | x },
            	SkoarpuscleUGen:      { | x, y, m | y.sub(x) },
				SkoarpuscleEnvelope:  { | x, y, m | SkoarpuscleCat.new },
			),

			
			SkoarpuscleNoat: (
				SkoarpuscleInt:       { | x, y, m | x.raiseBy(y) },
                SkoarpuscleFloat:     { | x, y, m | x.raiseBy(y) },
				SkoarpuscleHashLevel: { | x, y, m | x.raiseBy(y) },
				SkoarpuscleFreq:      { | x, y, m | x.raiseBy(y) },

				SkoarpuscleFalse:     { | x, y, m | y },
				SkoarpuscleTrue:      { | x, y, m | x },
				SkoarpuscleUGen:      { | x, y, m | SkoarpuscleCat.new },
				SkoarpuscleEnvelope:  { | x, y, m | SkoarpuscleCat.new },
			),

			SkoarpuscleChoard: (
				SkoarpuscleInt:       { | x, y, m | x.lowerBy(y) },
                SkoarpuscleFloat:     { | x, y, m | x.lowerBy(y) },
				SkoarpuscleHashLevel: { | x, y, m | x.lowerBy(y) },
				SkoarpuscleFreq:      { | x, y, m | x.lowerBy(y) },

				SkoarpuscleFalse:     { | x, y, m | y },
				SkoarpuscleTrue:      { | x, y, m | x },
				SkoarpuscleUGen:      { | x, y, m | SkoarpuscleCat.new },
				SkoarpuscleEnvelope:  { | x, y, m | SkoarpuscleCat.new },
			
			),

			SkoarpuscleFreq: (
				
                // y
                SkoarpuscleInt:        { | x, y, m | SkoarpuscleFreq(x.val - y.val) },
                SkoarpuscleFloat:      { | x, y, m | SkoarpuscleFreq(x.val - y.val) },			 
				SkoarpuscleHashLevel:  { | x, y, m | SkoarpuscleFreq(x.val - y.val) },			 
				SkoarpuscleFreq:       { | x, y, m | SkoarpuscleFreq(x.val - y.val) },

				SkoarpuscleFalse:      { | x, y, m | y },
				SkoarpuscleTrue:       { | x, y, m | x },
				SkoarpuscleUGen:       { | x, y, m | SkoarpuscleCat.new },
				SkoarpuscleEnvelope:   { | x, y, m | SkoarpuscleCat.new },
				
			)

        );
	}

	// ---------------------
	// Multiplication Tables
	// ---------------------
	init_multiplication {

		// x * y
        multiplication = (

			SkoarpuscleCat:   ( Any: { | x, y, m | SkoarpuscleCat.new } ),
			SkoarpuscleFalse: ( Any: { | x, y, m | x } ),
			SkoarpuscleTrue:  ( Any: { | x, y, m | y } ),


			// x *
			SkoarpuscleEnvelope:  (
				// y
                SkoarpuscleInt:         { | x, y, m | SkoarpuscleCat.new },
                SkoarpuscleFloat:       { | x, y, m | SkoarpuscleCat.new },
				SkoarpuscleHashLevel:   { | x, y, m | SkoarpuscleCat.new },
				SkoarpuscleFreq:        { | x, y, m | SkoarpuscleCat.new },

				SkoarpuscleNoat:        { | x, y, m | SkoarpuscleCat.new },
				SkoarpuscleChoard:      { | x, y, m | SkoarpuscleCat.new },

				SkoarpuscleFalse:       { | x, y, m | y },
				SkoarpuscleTrue:        { | x, y, m | x },

				SkoarpuscleSymbol:      { | x, y, m | SkoarpuscleCat.new },
				SkoarpuscleString:      { | x, y, m | SkoarpuscleCat.new },

                SkoarpuscleList:        { | x, y, m | SkoarpuscleCat.new },
				SkoarpuscleUGen:        { | x, y, m | y.mul(x) },
				SkoarpuscleEnvelope:    { | x, y, m | y.mul(x) }

			),

			// x *
			SkoarpuscleUGen:  (
				// y
                SkoarpuscleInt:         { | x, y, m | x.mul(y) },
                SkoarpuscleFloat:       { | x, y, m | x.mul(y) },
				SkoarpuscleHashLevel:   { | x, y, m | x.mul(y) },
				SkoarpuscleFreq:        { | x, y, m | SkoarpuscleCat.new },

				SkoarpuscleNoat:        { | x, y, m | SkoarpuscleCat.new },
				SkoarpuscleChoard:      { | x, y, m | SkoarpuscleCat.new },

				SkoarpuscleFalse:       { | x, y, m | y },
				SkoarpuscleTrue:        { | x, y, m | x },

				SkoarpuscleSymbol:      { | x, y, m | SkoarpuscleCat.new },
				SkoarpuscleString:      { | x, y, m | SkoarpuscleCat.new },

                SkoarpuscleList:        { | x, y, m | y.mul(m, x) },
				SkoarpuscleUGen:        { | x, y, m | x.mul(y) },
				SkoarpuscleEnvelope:    { | x, y, m | x.mul(y) }

			),
			
			// x
            SkoarpuscleInt: (
                // y
                SkoarpuscleInt:       { | x, y, m | SkoarpuscleInt(x.val * y.val) },
                SkoarpuscleFloat:     { | x, y, m | SkoarpuscleFloat(x.val * y.val) },
                SkoarpuscleHashLevel: { | x, y, m | SkoarpuscleFloat(x.val * y.val) },
                SkoarpuscleFreq:      { | x, y, m | SkoarpuscleFreq(x.val * y.val) },

				SkoarpuscleNoat:      { | x, y, m | SkoarpuscleCat.new },
				SkoarpuscleChoard:    { | x, y, m | SkoarpuscleCat.new },
			
				SkoarpuscleFalse:     { | x, y, m | y },
				SkoarpuscleTrue:      { | x, y, m | x },
				SkoarpuscleCat:       { | x, y, m | SkoarpuscleCat.new },
				
				SkoarpuscleList:      { | x, y, m | y.mul(m, x) },
				SkoarpuscleUGen:      { | x, y, m | y.mul(x) },
				SkoarpuscleEnvelope:  { | x, y, m | SkoarpuscleCat.new },

				    
            ),

            // x
            SkoarpuscleFloat: (
                // y
                SkoarpuscleInt:       { | x, y, m | SkoarpuscleFloat(x.val * y.val) },
                SkoarpuscleFloat:     { | x, y, m | SkoarpuscleFloat(x.val * y.val) },
                SkoarpuscleHashLevel: { | x, y, m | SkoarpuscleFloat(x.val * y.val) },
                SkoarpuscleFreq:      { | x, y, m | SkoarpuscleCat.new },

				SkoarpuscleNoat:      { | x, y, m | SkoarpuscleCat.new },
				SkoarpuscleChoard:    { | x, y, m | SkoarpuscleCat.new },
				
				SkoarpuscleFalse:     { | x, y, m | y },
				SkoarpuscleTrue:      { | x, y, m | x },
				
				SkoarpuscleList:      { | x, y, m | y.mul(m, x) },
				SkoarpuscleUGen:      { | x, y, m | y.mul(x) },
				SkoarpuscleEnvelope:  { | x, y, m | SkoarpuscleCat.new },

            ),

			// x
            SkoarpuscleHashLevel: (
                // y
                SkoarpuscleInt:       { | x, y, m | SkoarpuscleFloat(x.val * y.val) },
                SkoarpuscleFloat:     { | x, y, m | SkoarpuscleFloat(x.val * y.val) },
                SkoarpuscleHashLevel: { | x, y, m | SkoarpuscleFloat(x.val * y.val) },
                SkoarpuscleFreq:      { | x, y, m | SkoarpuscleCat.new },

				SkoarpuscleFalse:     { | x, y, m | y },
				SkoarpuscleTrue:      { | x, y, m | x },
				
				SkoarpuscleList:      { | x, y, m | y.mul(m, x) },
				SkoarpuscleUGen:      { | x, y, m | y.mul(x) },
				SkoarpuscleEnvelope:  { | x, y, m | SkoarpuscleCat.new },

            ),

			SkoarpuscleList: (
				// y
                SkoarpuscleInt:       { | x, y, m | x.mul(m, y) },
                SkoarpuscleFloat:     { | x, y, m | x.mul(m, y) },
                SkoarpuscleHashLevel: { | x, y, m | x.mul(m, y) },
                SkoarpuscleFreq:      { | x, y, m | x.mul(m, y) },

				SkoarpuscleNoat:      { | x, y, m | x.mul(m, y) },
				SkoarpuscleChoard:    { | x, y, m | x.mul(m, y) },
				
				SkoarpuscleFalse:     { | x, y, m | y },
				SkoarpuscleTrue:      { | x, y, m | x },
				
				SkoarpuscleList:      { | x, y, m | x.mul(m, y) },
				SkoarpuscleUGen:      { | x, y, m | x.mul(m, y) },
				SkoarpuscleEnvelope:  { | x, y, m | x.mul(m, y) },
		
			),

			SkoarpuscleNoat: (
				SkoarpuscleInt:       { | x, y, m | SkoarpuscleCat.new },
                SkoarpuscleFloat:     { | x, y, m | SkoarpuscleCat.new },
                SkoarpuscleHashLevel: { | x, y, m | SkoarpuscleCat.new },
                SkoarpuscleFreq:      { | x, y, m | SkoarpuscleCat.new },

				SkoarpuscleFalse:     { | x, y, m | y },
				SkoarpuscleTrue:      { | x, y, m | x },
				
				SkoarpuscleList:      { | x, y, m | SkoarpuscleCat.new },
				SkoarpuscleUGen:      { | x, y, m | SkoarpuscleCat.new },
				SkoarpuscleEnvelope:  { | x, y, m | SkoarpuscleCat.new },
			),

			SkoarpuscleChoard: (
				SkoarpuscleInt:       { | x, y, m | SkoarpuscleCat.new },
                SkoarpuscleFloat:     { | x, y, m | SkoarpuscleCat.new },
                SkoarpuscleHashLevel: { | x, y, m | SkoarpuscleCat.new },
				SkoarpuscleFreq:      { | x, y, m | SkoarpuscleCat.new },
				SkoarpuscleFalse:     { | x, y, m | y },
				SkoarpuscleTrue:      { | x, y, m | x },
				SkoarpuscleList:      { | x, y, m | SkoarpuscleCat.new },
				SkoarpuscleUGen:      { | x, y, m | SkoarpuscleCat.new },
				SkoarpuscleEnvelope:  { | x, y, m | SkoarpuscleCat.new },
			),

			SkoarpuscleFreq: (
              
                // y
                SkoarpuscleInt:       { | x, y, m | SkoarpuscleFreq(x.val * y.val) },
                SkoarpuscleFloat:     { | x, y, m | SkoarpuscleFreq(x.val * y.val) },
                SkoarpuscleHashLevel: { | x, y, m | SkoarpuscleFreq(x.val * y.val) },
                SkoarpuscleFreq:      { | x, y, m | SkoarpuscleFreq(x.val * y.val) },

				SkoarpuscleNoat:      { | x, y, m | SkoarpuscleCat.new },
				SkoarpuscleChoard:    { | x, y, m | SkoarpuscleCat.new },
				
				SkoarpuscleSymbol:    { | x, y, m | SkoarpuscleCat.new },
				SkoarpuscleString:    { | x, y, m | SkoarpuscleCat.new },
				
				SkoarpuscleFalse:     { | x, y, m | y },
				SkoarpuscleTrue:      { | x, y, m | x },
				SkoarpuscleCat:       { | x, y, m | SkoarpuscleCat.new },
				
				SkoarpuscleList:      { | x, y, m | y.mul(m, x) },
				SkoarpuscleUGen:      { | x, y, m | SkoarpuscleCat.new },
				SkoarpuscleEnvelope:  { | x, y, m | SkoarpuscleCat.new },
			  
			)
		);
    }

	// ---------------
	// Division Tables
	// ---------------
	init_division {

		// x / y
        division = (

			SkoarpuscleCat:   ( Any: { | x, y, m | SkoarpuscleCat.new } ),
			SkoarpuscleFalse: ( Any: { | x, y, m | x } ),
			SkoarpuscleTrue:  ( Any: { | x, y, m | y } ),


			// x /
			SkoarpuscleEnvelope:  (
				// y
                SkoarpuscleInt:         { | x, y, m | x.div(y) },
                SkoarpuscleFloat:       { | x, y, m | x.div(y) },
				SkoarpuscleHashLevel:   { | x, y, m | SkoarpuscleCat.new },
				SkoarpuscleFreq:        { | x, y, m | SkoarpuscleCat.new },

				SkoarpuscleNoat:        { | x, y, m | SkoarpuscleCat.new },
				SkoarpuscleChoard:      { | x, y, m | SkoarpuscleCat.new },

				SkoarpuscleFalse:       { | x, y, m | y },
				SkoarpuscleTrue:        { | x, y, m | x },

				SkoarpuscleSymbol:      { | x, y, m | SkoarpuscleCat.new },
				SkoarpuscleString:      { | x, y, m | SkoarpuscleCat.new },

                SkoarpuscleList:        { | x, y, m | SkoarpuscleCat.new },
				SkoarpuscleUGen:        { | x, y, m | SkoarpuscleCat.new },
				SkoarpuscleEnvelope:    { | x, y, m | x.div(y) }

			),

			// x /
			SkoarpuscleUGen:  (
				// y
                SkoarpuscleInt:         { | x, y, m | x.div(y) },
                SkoarpuscleFloat:       { | x, y, m | x.div(y) },
				SkoarpuscleHashLevel:   { | x, y, m | x.div(y) },
				SkoarpuscleFreq:        { | x, y, m | SkoarpuscleCat.new },

				SkoarpuscleNoat:        { | x, y, m | SkoarpuscleCat.new },
				SkoarpuscleChoard:      { | x, y, m | SkoarpuscleCat.new },

				SkoarpuscleFalse:       { | x, y, m | y },
				SkoarpuscleTrue:        { | x, y, m | x },

				SkoarpuscleSymbol:      { | x, y, m | SkoarpuscleCat.new },
				SkoarpuscleString:      { | x, y, m | SkoarpuscleCat.new },

                SkoarpuscleList:        { | x, y, m | y.div(m, x) },
				SkoarpuscleUGen:        { | x, y, m | x.div(y) },
				SkoarpuscleEnvelope:    { | x, y, m | x.div(y) }

			),
			
			// x /
            SkoarpuscleInt: (
                // y
                SkoarpuscleInt:       { | x, y, m | SkoarpuscleInt(x.val / y.val) },
                SkoarpuscleFloat:     { | x, y, m | SkoarpuscleFloat(x.val / y.val) },
                SkoarpuscleHashLevel: { | x, y, m | SkoarpuscleFloat(x.val / y.val) },
                SkoarpuscleFreq:      { | x, y, m | SkoarpuscleFreq(x.val / y.val) },

				SkoarpuscleNoat:      { | x, y, m | SkoarpuscleCat.new },
				SkoarpuscleChoard:    { | x, y, m | SkoarpuscleCat.new },
			
				SkoarpuscleFalse:     { | x, y, m | y },
				SkoarpuscleTrue:      { | x, y, m | x },
				SkoarpuscleCat:       { | x, y, m | SkoarpuscleCat.new },
				
				SkoarpuscleList:      { | x, y, m | y.div(m, x) },
				SkoarpuscleUGen:      { | x, y, m | y.div(x) },
				SkoarpuscleEnvelope:  { | x, y, m | SkoarpuscleCat.new },

				    
            ),

            // x /
            SkoarpuscleFloat: (
                // y
                SkoarpuscleInt:       { | x, y, m | SkoarpuscleFloat(x.val / y.val) },
                SkoarpuscleFloat:     { | x, y, m | SkoarpuscleFloat(x.val / y.val) },
                SkoarpuscleHashLevel: { | x, y, m | SkoarpuscleFloat(x.val / y.val) },
                SkoarpuscleFreq:      { | x, y, m | SkoarpuscleCat.new },

				SkoarpuscleNoat:      { | x, y, m | SkoarpuscleCat.new },
				SkoarpuscleChoard:    { | x, y, m | SkoarpuscleCat.new },
				
				SkoarpuscleFalse:     { | x, y, m | y },
				SkoarpuscleTrue:      { | x, y, m | x },
				
				SkoarpuscleList:      { | x, y, m | y.div(m, x) },
				SkoarpuscleUGen:      { | x, y, m | y.div(x) },
				SkoarpuscleEnvelope:  { | x, y, m | SkoarpuscleCat.new },

            ),

			// x
            SkoarpuscleHashLevel: (
                // y
                SkoarpuscleInt:       { | x, y, m | SkoarpuscleFloat(x.val / y.val) },
                SkoarpuscleFloat:     { | x, y, m | SkoarpuscleFloat(x.val / y.val) },
                SkoarpuscleHashLevel: { | x, y, m | SkoarpuscleFloat(x.val / y.val) },
                SkoarpuscleFreq:      { | x, y, m | SkoarpuscleCat.new },

				SkoarpuscleFalse:     { | x, y, m | y },
				SkoarpuscleTrue:      { | x, y, m | x },
				
				SkoarpuscleList:      { | x, y, m | y.div(m, x) },
				SkoarpuscleUGen:      { | x, y, m | y.div(x) },
				SkoarpuscleEnvelope:  { | x, y, m | SkoarpuscleCat.new },

            ),

			SkoarpuscleList: (
				// y
                SkoarpuscleInt:       { | x, y, m | x.divBy(m, y) },
                SkoarpuscleFloat:     { | x, y, m | x.divBy(m, y) },
                SkoarpuscleHashLevel: { | x, y, m | x.divBy(m, y) },
                SkoarpuscleFreq:      { | x, y, m | x.divBy(m, y) },

				SkoarpuscleNoat:      { | x, y, m | SkoarpuscleCat.new },
				SkoarpuscleChoard:    { | x, y, m | SkoarpuscleCat.new },
				
				SkoarpuscleFalse:     { | x, y, m | y },
				SkoarpuscleTrue:      { | x, y, m | x },
				
				SkoarpuscleList:      { | x, y, m | x.divBy(m, y) },
				SkoarpuscleUGen:      { | x, y, m | x.divBy(m, y) },
				SkoarpuscleEnvelope:  { | x, y, m | x.divBy(m, y) },
		
			),

			SkoarpuscleNoat: (
				SkoarpuscleInt:       { | x, y, m | SkoarpuscleCat.new },
                SkoarpuscleFloat:     { | x, y, m | SkoarpuscleCat.new },
                SkoarpuscleHashLevel: { | x, y, m | SkoarpuscleCat.new },
                SkoarpuscleFreq:      { | x, y, m | SkoarpuscleCat.new },

				SkoarpuscleFalse:     { | x, y, m | y },
				SkoarpuscleTrue:      { | x, y, m | x },
				
				SkoarpuscleList:      { | x, y, m | SkoarpuscleCat.new },
				SkoarpuscleUGen:      { | x, y, m | SkoarpuscleCat.new },
				SkoarpuscleEnvelope:  { | x, y, m | SkoarpuscleCat.new },
			),

			SkoarpuscleChoard: (
				SkoarpuscleInt:       { | x, y, m | SkoarpuscleCat.new },
                SkoarpuscleFloat:     { | x, y, m | SkoarpuscleCat.new },
                SkoarpuscleHashLevel: { | x, y, m | SkoarpuscleCat.new },
				SkoarpuscleFreq:      { | x, y, m | SkoarpuscleCat.new },
				SkoarpuscleFalse:     { | x, y, m | y },
				SkoarpuscleTrue:      { | x, y, m | x },
				SkoarpuscleList:      { | x, y, m | SkoarpuscleCat.new },
				SkoarpuscleUGen:      { | x, y, m | SkoarpuscleCat.new },
				SkoarpuscleEnvelope:  { | x, y, m | SkoarpuscleCat.new },
			),

			SkoarpuscleFreq: (
              
                // y
                SkoarpuscleInt:       { | x, y, m | SkoarpuscleFreq(x.val / y.val) },
                SkoarpuscleFloat:     { | x, y, m | SkoarpuscleFreq(x.val / y.val) },
                SkoarpuscleHashLevel: { | x, y, m | SkoarpuscleFreq(x.val / y.val) },
                SkoarpuscleFreq:      { | x, y, m | SkoarpuscleFreq(x.val / y.val) },

				SkoarpuscleNoat:      { | x, y, m | SkoarpuscleCat.new },
				SkoarpuscleChoard:    { | x, y, m | SkoarpuscleCat.new },
				
				SkoarpuscleSymbol:    { | x, y, m | SkoarpuscleCat.new },
				SkoarpuscleString:    { | x, y, m | SkoarpuscleCat.new },
				
				SkoarpuscleFalse:     { | x, y, m | y },
				SkoarpuscleTrue:      { | x, y, m | x },
				SkoarpuscleCat:       { | x, y, m | SkoarpuscleCat.new },
				
				SkoarpuscleList:      { | x, y, m | y.div(m, x) },
				SkoarpuscleUGen:      { | x, y, m | SkoarpuscleCat.new },
				SkoarpuscleEnvelope:  { | x, y, m | SkoarpuscleCat.new },
			  
			)
		);
    }

    lookup {
        | op, x, y |
		var f;
        var table = op[x.class.asSymbol];
        
		if (table.isNil) {
			^{ | x, y, m | SkoarpuscleCat.new };
		};
		
		f = table[y.class.asSymbol];

        if (f.isNil) {
            f = table[\Any];
        };

        if (f.notNil) {
            ^f
        };

		^{ | x, y, m | SkoarpuscleCat.new };
        //SkoarError("Lookup fail.").throw;
    }

    // v => settable
    assign {
        | minstrel, v, settable |
        var f = this.lookup(assignment, settable, v);
        //"assign ".post; v.val.post; v.dump;
        ^minstrel.fairy.impress(f.(minstrel, v, settable, minstrel));
    }

    // x + y
    add {
        | minstrel, x, y |
        var f = this.lookup(addition, x, y);
        //"add".postln;
        ^minstrel.fairy.impress(f.(x, y, minstrel));
    }

	// x - y
    sub {
        | minstrel, x, y |
        var f = this.lookup(subtraction, x, y);
        //"sub".postln;
        ^minstrel.fairy.impress(f.(x, y, minstrel));
    }

    // x * y
    multiply {
        | minstrel, x, y |
        var f = this.lookup(multiplication, x, y);
        //("multiply " ++ x.asString ++ " * " ++ y.asString).postln;
        ^minstrel.fairy.impress(f.(x, y, minstrel));
    }

	// x / y
    divide {
        | minstrel, x, y |
        var f = this.lookup(division, x, y);
        //("divide " ++ x.asString ++ " / " ++ y.asString).postln;
		
        ^minstrel.fairy.impress(
			if (y.isZero) {
				SkoarpuscleCat.new
			} {
				f.(x, y, minstrel)
			});
    }

	// x +> y
    increment {
        | minstrel, x, y |
        var f = this.lookup(addition, y, x);
        //"increment".postln;
		^minstrel.fairy.impress(f.(x, y, minstrel));
	}

	// x -> y
    decrement {
        | minstrel, x, y |
        var f = this.lookup(subtraction, y, x);
        //"decrement".postln;
		^minstrel.fairy.impress(f.(x, y, minstrel));
	}
	 
	// x *> y
	multr {
        | minstrel, x, y |
        var f = this.lookup(multiplication, y, x);
        //"multr".postln;
		^minstrel.fairy.impress(f.(x, y, minstrel));
	}


	// x * y
    multiply_unimpressively {
        | minstrel, x, y |
        var f = this.lookup(multiplication, x, y);
        //("multiply " ++ x.asString ++ " * " ++ y.asString).postln;
        ^f.(x, y, minstrel);
    }

	// x / y
    divide_unimpressively {
        | minstrel, x, y |
        var f = this.lookup(division, x, y);
        //("divide " ++ x.asString ++ " / " ++ y.asString).postln;
        ^if (y.isZero) {
			SkoarpuscleCat.new
		} {
			f.(x, y, minstrel)
		};
    }
}