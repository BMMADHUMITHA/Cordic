#include <systemc.h>
#define c_parameter 16 
#define STG 16

SC_MODULE(sine_cosine) 
{
  
    sc_in <bool> clk;
    sc_in <sc_uint<32> >angle;
    sc_in <sc_uint<c_parameter> > Xin, Yin;
    sc_out <sc_uint<c_parameter + 1> > Xout,Yout;

    // Signals
    sc_uint <32> atan_table[31];
    sc_uint <c_parameter + 1> X[STG];
    sc_uint <c_parameter + 1> Y[STG];
    sc_uint <32> Z[STG]; // 32bit
    sc_uint <2> quadrant;
  
   

    void process() {
            switch (quadrant.to_uint()) {
                case 0b00:
                case 0b11:
                    X[0] = Xin.read();
                    Y[0] = Yin.read();
                    Z[0] = sc_uint<32>(angle.read().range(29,0).to_uint());
                    break;

                case 0b01:
                    X[0] = -Yin.read();
                    Y[0] = Xin.read();
                    Z[0] = sc_uint<32>("0b00" + angle.read().range(29,0).to_uint());
                    break;

                case 0b10:
                    X[0] = Yin.read();
                    Y[0] = -Xin.read();
                    Z[0] = sc_uint<32>("0b11" + angle.read().range(29, 0).to_uint());
                    break;
            }
        }
void assign_outputs() {
        Xout.write(X[STG-1]);
        Yout.write(Y[STG-1]);
    }
  void cal()
  {
    atan_table[0]= (0b00100000000000000000000000000000); // 45.000 degrees -> atan(2^0)
    atan_table[1]= (0b00010010111001000000010100011101); // 26.565 degrees -> atan(2^-1)
    atan_table[2]= (0b00001001111110110011100001011011); // 14.036 degrees -> atan(2^-2)
    atan_table[3]= (0b00000101000100010001000111010100); // atan(2^-3)
    atan_table[4]= (0b00000010100010110000110101000011);
    atan_table[5]= (0b00000001010001011101011111100001);
    atan_table[6]= (0b00000000101000101111011000011110);
    atan_table[7]= (0b00000000010100010111110001010101);
    atan_table[8]= (0b00000000001010001011111001010011);
    atan_table[9]= (0b00000000000101000101111100101110);
    atan_table[10]= (0b00000000000010100010111110011000);
    atan_table[11]= (0b00000000000001010001011111001100);
    atan_table[12]= (0b00000000000000101000101111100110);
    atan_table[13]= (0b00000000000000010100010111110011);
    atan_table[14]= (0b00000000000000001010001011111001);
    atan_table[15]= (0b00000000000000000101000101111101);
    atan_table[16]= (0b00000000000000000010100010111110);
    atan_table[17]= (0b00000000000000000001010001011111);
    atan_table[18]= (0b00000000000000000000101000101111);
    atan_table[19]= (0b00000000000000000000010100011000);
    atan_table[20]= (0b00000000000000000000001010001100);
    atan_table[21]= (0b00000000000000000000000101000110);
    atan_table[22]= (0b00000000000000000000000010100011);
    atan_table[23]= (0b00000000000000000000000001010001);
    atan_table[24]= (0b00000000000000000000000000101000);
    atan_table[25]= (0b00000000000000000000000000010100);
    atan_table[26]= (0b00000000000000000000000000001010);
    atan_table[27]= (0b00000000000000000000000000000101);
    atan_table[28]= (0b00000000000000000000000000000010);
    atan_table[29]= (0b00000000000000000000000000000001); // atan(2^-29)
    atan_table[30]= (0b00000000000000000000000000000000);
     for (int i = 0; i < STG - 1; i++) {
            sc_uint<c_parameter + 1> X_shr = X[i] >> i;
            sc_uint<c_parameter + 1> Y_shr = Y[i] >> i;
            bool Z_sign = Z[i][31];

            X[i+1] = Z_sign ? X[i] + Y_shr : X[i] - Y_shr;
            Y[i+1] = Z_sign ? Y[i] - X_shr : Y[i] + X_shr;
            Z[i+1] = Z_sign ? Z[i] + atan_table[i] : Z[i] - atan_table[i];
        }
  }
    // Constructor
    SC_CTOR(sine_cosine) {
        SC_METHOD(process);
        sensitive_pos << clk;
      SC_METHOD(cal);
      SC_METHOD(assign_outputs);

       
    }

    
};
