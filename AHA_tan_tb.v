

module tb;

	// Inputs
	reg i_clk;
	reg i_reset;
	reg i_ce;
	reg [11:0] i_xval;
	reg [11:0] i_yval;
	reg i_aux;

	// Outputs
	wire [11:0] o_mag;
	wire [18:0] o_phase;
	wire o_aux;

	// Instantiate the Unit Under Test (UUT)
	topolar uut (
		.i_clk(i_clk), 
		.i_reset(i_reset), 
		.i_ce(i_ce), 
		.i_xval(i_xval), 
		.i_yval(i_yval), 
		.i_aux(i_aux), 
		.o_mag(o_mag), 
		.o_phase(o_phase), 
		.o_aux(o_aux)
	);

	initial begin
		// Initialize Inputs
		i_clk = 0;
		i_reset = 1;
		i_ce = 0;
		i_xval = 0;
		i_yval = 0;
		i_aux = 1;

		// Wait 100 ns for global reset to finish
		#4;
		
		i_reset = 0;
		i_ce = 1;
		i_xval = 0;
		i_yval = 0;
		
		#4
        
		i_reset = 0;
		i_ce = 1;
		i_xval = 1;
		i_yval = 1;
		
		
		#4;
        
		i_reset = 0;
		i_xval = 1;
		i_yval = 2;
		
		#4 
		
		i_xval = 2;
		i_yval = 3;
		
		#4
		
		i_yval = 4;
		
		
		// Add stimulus here

	end
	
	always #1 i_clk=~i_clk;
      
endmodule

