----------------------------------------------------------------------
-- EECS31L/CSE31L Assignment4 DCT - Summer '18
-- Structural Model
-- Author: Kian Farsany
-- ucinetid: kfarsany
----------------------------------------------------------------------
-- Version 8-27-2018

Library IEEE;
use IEEE.STD_LOGIC_1164.all;
use IEEE.STD_LOGIC_MISC.all;
use IEEE.STD_LOGIC_ARITH.all;

----------------integer register--------------------

Library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.std_logic_misc.all;
use IEEE.std_logic_arith.all;


Entity Reg is
      Generic ( Delay:   Time := 4 ns ); 
      Port (    Clk : In    std_logic;
                Din : In    INTEGER;
                Rst:  In    std_logic;
                Ld : In    std_logic;
                Dout : Out   INTEGER );
End Reg;

Architecture BEHAVIORAL of Reg is

   Begin
    P: Process (Clk)
    Variable Value : INTEGER := 0;
    Begin
     if( Clk'event and Clk = '1' ) then
       if (Rst = '1') then
           Dout <= 0;           
       elsif( Ld = '1' ) then
           Dout <=  Din after Delay;
       End if;
     End if; 
    End Process P;
End BEHAVIORAL;

-----------256x32(integer) Register file-------------------

Library ieee;
USE ieee.std_logic_1164.ALL;
USE ieee.std_logic_unsigned.ALL;
 
Entity RegFile IS
   Generic ( Delay:   Time := 8 ns );
   Port (R_addr1,R_addr2,W_addr: IN std_logic_vector(7 DOWNTO 0);
         R_en1,R_en2, W_en: IN std_logic;
         R_data1, R_data2: OUT INTEGER; 
         W_data: IN INTEGER; 
         Clk: IN std_logic );
End RegFile;

Architecture Behavioral OF RegFile IS 
    type RF is array ( 0 to 31, 0 to 7 ) of INTEGER;
    signal Storage : RF := (
             --------OutBlock--------
            ( 0, 0, 0, 0, 0, 0, 0, 0 ),
            ( 0, 0, 0, 0, 0, 0, 0, 0 ),
            ( 0, 0, 0, 0, 0, 0, 0, 0 ),
            ( 0, 0, 0, 0, 0, 0, 0, 0 ),
            ( 0, 0, 0, 0, 0, 0, 0, 0 ),
            ( 0, 0, 0, 0, 0, 0, 0, 0 ),
            ( 0, 0, 0, 0, 0, 0, 0, 0 ),
            ( 0, 0, 0, 0, 0, 0, 0, 0 ),
             --------TempBlock--------
            ( 0, 0, 0, 0, 0, 0, 0, 0 ),
            ( 0, 0, 0, 0, 0, 0, 0, 0 ),
            ( 0, 0, 0, 0, 0, 0, 0, 0 ),
            ( 0, 0, 0, 0, 0, 0, 0, 0 ),
            ( 0, 0, 0, 0, 0, 0, 0, 0 ),
            ( 0, 0, 0, 0, 0, 0, 0, 0 ),
            ( 0, 0, 0, 0, 0, 0, 0, 0 ),
            ( 0, 0, 0, 0, 0, 0, 0, 0 ),
             --------InBlock--------
            ( 0, 0, 0, 0, 0, 0, 0, 0 ),
            ( 0, 0, 0, 0, 0, 0, 0, 0 ),
            ( 0, 0, 0, 0, 0, 0, 0, 0 ),
            ( 0, 0, 0, 0, 0, 0, 0, 0 ),
            ( 0, 0, 0, 0, 0, 0, 0, 0 ),
            ( 0, 0, 0, 0, 0, 0, 0, 0 ),
            ( 0, 0, 0, 0, 0, 0, 0, 0 ),
            ( 0, 0, 0, 0, 0, 0, 0, 0 ),
           --------COS-------------
            ( 125, 122,  115, 103,  88,  69,   47,   24  ),
            ( 125, 103,  47,  -24,  -88, -122, -115, -69  ),
            ( 125, 69,   -47, -122, -88, 24,   115,  103  ),
            ( 125, 24,   -115, -69, 88,  103,  -47,  -122  ),
            ( 125, -24,  -115, 69,  88,  -103, -47,  122  ),
            ( 125, -69,  -47, 122,  -88, -24,  115,  -103  ),
            ( 125, -103, 47,  24,   -88, 122,  -115, 69  ),
            ( 125, -122, 115, -103, 88,  -69,  47,   -24 )          
            );
Begin
    WriteProcess: Process(Clk)
    Variable col_w:std_logic_vector(2 DOWNTO 0);    
    Variable row_w:std_logic_vector(4 DOWNTO 0);
    Begin
          row_w := W_addr(7 downto 3);
          col_w := W_addr(2 downto 0);
        
    if( Clk'event and Clk = '1' ) then   
      if(W_en = '1') then 
        -- write --
        Storage( CONV_INTEGER(row_w), CONV_INTEGER(col_w)) <= W_data after Delay;
      End if;
        
    End if;
    
    End Process;

    ReadProcess: Process(R_en1, R_addr1, R_en2, R_addr2,Storage)
    Variable  col_r1, col_r2:std_logic_vector(2 DOWNTO 0);  
    Variable  row_r1, row_r2:std_logic_vector(4 DOWNTO 0);
    Begin
        row_r1 := R_addr1(7 downto 3);
        col_r1 := R_addr1(2 downto 0);
        row_r2 := R_addr2(7 downto 3);
        col_r2 := R_addr2(2 downto 0);
    
    if(R_en1 = '1') then 
        R_data1 <= Storage( CONV_INTEGER(row_r1), CONV_INTEGER(col_r1) ) after Delay;
    else
        R_data1 <= INTEGER'left;    
    End if;
    
    if(R_en2 = '1') then 
        R_data2 <= Storage( CONV_INTEGER(row_r2), CONV_INTEGER(col_r2) ) after Delay;
    else
        R_data2 <= INTEGER'left;    
    End if;
    End Process;
End Behavioral;


-------------------------------Counter------------------------------

Library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.std_logic_misc.all;
use IEEE.std_logic_arith.all;



Entity Counter is
      Generic ( Delay:   Time := 8 ns );
      Port (    Clk : In    std_logic;
                Inc : In    std_logic;
                Rst : In    std_logic;
                i : Out   std_logic_vector(2 downto 0);
                j : Out   std_logic_vector(2 downto 0);
                k : Out   std_logic_vector(2 downto 0) );
End Counter;

Architecture BEHAVIORAL of Counter is

   Begin
    P: Process ( Clk )
    Variable Value : UNSIGNED( 8 downto 0 ) := "000000000";
    Begin
        if( Clk'event and Clk = '1' ) then 
            if( Rst = '1' ) then
                Value := "000000000";
            elsif( Inc = '1' ) then
                Value := Value + 1;
            End if;
        End if;
                i(2) <= Value(8) after Delay;
                i(1) <= Value(7) after Delay;
                i(0) <= Value(6) after Delay;
                j(2) <= Value(5) after Delay; 
                j(1) <= Value(4) after Delay;
                j(0) <= Value(3) after Delay;
                k(2) <= Value(2) after Delay;
                k(1) <= Value(1) after Delay; 
                k(0) <= Value(0) after Delay;                    
    End Process P;

End BEHAVIORAL;

---------------------------Multiplier--------------------------

library IEEE;
   use IEEE.std_logic_1164.all;
   use IEEE.std_logic_misc.all;
   use IEEE.std_logic_arith.all;


entity Multiplier is
          generic ( Delay:   Time := 25 ns );
       Port (A : In    integer;
             B : In    integer;
             Product : Out   integer );
end Multiplier;

architecture BEHAVIORAL of Multiplier is
   begin
    P: process ( A, B )
        variable Result : integer := 0;
    begin
        if( A /= integer'left and B /= integer'left ) then
            Result := A * B;
        end if;
        Product <= Result after Delay;
    end process P;
end BEHAVIORAL;


-------------------------Adder-------------------------------

library IEEE;
   use IEEE.std_logic_1164.all;
   use IEEE.std_logic_misc.all;
   use IEEE.std_logic_arith.all;


entity Adder is
         generic ( Delay:   Time := 15 ns ); 
      Port (     A : In    integer;
                 B : In    integer;
                 Sum : Out   integer );
end Adder;

architecture BEHAVIORAL of Adder is

   begin
    P: process ( A, B )
        variable Result : integer := 0;
    begin
        if( A /= integer'left and B /= integer'left ) then
            Result := A + B;
        end if;
        Sum <= Result after Delay;
    end process P;

end BEHAVIORAL;


----------------------32-bit(integer) Mux----------------------

Library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.std_logic_misc.all;
use IEEE.std_logic_arith.all;



Entity MuxInt is
      Generic ( Delay:   Time := 4 ns );
      Port (    C : In    std_logic;
                D0 : In    INTEGER;
                D1 : In    INTEGER;
                Dout : Out   INTEGER );
End MuxInt;

Architecture BEHAVIORAL of MuxInt is
   Begin
    P: Process ( D0, D1, C )
    Variable data_out : INTEGER;
    Begin
        if( C = '0' ) then
            data_out := D0;
        else
            data_out := D1;
        End if;
        Dout <= data_out after Delay;
    End Process P;
End BEHAVIORAL;


--------------------3-bit Mux--------------------------
Library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.std_logic_misc.all;
use IEEE.std_logic_arith.all;



Entity Mux3 is
      Generic ( Delay:   Time := 4 ns );
      Port (    C : In    std_logic;
                D0 : In    std_logic_vector(2 downto 0);
                D1 : In    std_logic_vector(2 downto 0);
                Dout : Out   std_logic_vector(2 downto 0) );
End Mux3;

Architecture BEHAVIORAL of Mux3 is

   Begin
    P: Process ( D0, D1, C )
        Begin
        if( C = '0' ) then
            Dout <= D0 after Delay;
        else
            Dout <= D1 after Delay;
        End if;
        
    End Process P;
End BEHAVIORAL;

---------- 32-bit (integer) Three-state Buffer ----------

Library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.std_logic_misc.all;
use IEEE.std_logic_arith.all;


Entity ThreeStateBuff IS
    Generic ( Delay:   Time := 1 ns );
    Port (Control_Input: IN std_logic;
          Data_Input: IN INTEGER;
          Output: OUT INTEGER );
End ThreeStateBuff;

Architecture Beh OF ThreeStateBuff IS
Begin
    Process (Control_Input, Data_Input)
    Begin
        IF (Control_Input = '1') THEN
            Output <= Data_Input AFTER Delay;
        ELSE
            Output <= INTEGER'left AFTER Delay;
        End IF;
    End Process;
End Beh;

  

 -------------------------------------------------------------
 --      Controller
 -------------------------------------------------------------
Library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.std_logic_misc.all;
use IEEE.std_logic_arith.all;



Entity Controller is
     Generic ( Delay:   Time := 6.2 ns );
     Port (  Clk   : In    std_logic;
             Start : In    std_logic;
             Count : In    std_logic_vector(8 downto 0);
             Inc : Out   std_logic := '0';
             R_en1 : Out   std_logic := '0';
             R_en2 : Out   std_logic := '0';
             W_en : Out   std_logic := '0';
             LoadSum : Out   std_logic := '0';               
             Rst_counter : Out   std_logic := '0';
             Rst_sum : Out   std_logic := '0'; 
             Rst_p : Out   std_logic := '0'; 
             Sel1 : Out   std_logic := '0';
             Sel2 : Out   std_logic := '0';
             Sel3 : Out   std_logic := '0';
             Sel4 : Out   std_logic := '0';
             Sel5 : Out   std_logic := '0';
             Sel6 : Out   std_logic := '0';
             Sel7 : Out   std_logic := '0'; 
             Sel8 : Out   std_logic := '0'; 
             Oe   : Out   std_logic := '0';                  
             Done : Out   std_logic := '0');
End Controller;

Architecture BEHAVIORAL of Controller is

  -- you can have as many states as necessary
  -- no need to encode unless you really want to
  type STATE_VALUE is (S1, S2, S3, S4, S5, S6, S7, S8, S9,
                       S10, S11, S12, S13, S14, S15, S16); 
  SIGNAL CurrState :   STATE_VALUE;
  SIGNAL NextState :   STATE_VALUE;

begin
 StateReg: process (Clk)
           begin
                if (Clk = '1' and clk'EVENT) then
                    CurrState <= NextState after 4 ns;
                end if;
           end process StateReg;
 
 CombLogic: process( CurrState, Start, Count )
            -- some suggested variables, you can use or you can remove.
            -- variable  NextStateValue : STATE_VALUE := <initialize your state here>;
            -- variable  VarDone : std_logic;
            variable  i, j, k : INTEGER;
        
        begin
           
            -- convert from our Count std_logic_vector into an integer we can use easier
            -- optional to use; you can add/remove whatever code you feel necessary for the Controller
            if( Count(0) /= 'U' and Start /= 'U' ) then
                i := CONV_INTEGER( unsigned(Count( 8 downto 6 )) );
                j := CONV_INTEGER( unsigned(Count( 5 downto 3 )) );
                k := CONV_INTEGER( unsigned(Count( 2 downto 0 )) );
            end if;
            
            W_en <= '0'; Inc <= '0'; Rst_counter <= '0';
            Rst_sum <= '0'; LoadSum <= '0'; Rst_p <= '0';
            R_en1 <= '0'; R_en2 <= '0';
            Sel1 <= '1'; Sel2 <= '1'; Sel3 <= '1'; Sel4 <= '1';
            Sel5 <= '0'; Sel6 <= '0'; Sel7 <= '0'; Sel8 <= '0';
            Oe <= '0'; Done <= '0';
            CASE CurrState IS
            
                -- Init state, Starts when Start = 1
                when S1 =>
                    if (Start = '0') then
                        NextState <= S1 after Delay;
                    else
                        Rst_counter <= '1';
                        NextState <= S2 after Delay;
                    end if;
                    
                -- Reads input and writes it into InBlock
                when S2 =>
                    Sel2 <= '0'; Sel3 <= '0'; Sel6 <= '1';
                    W_en <= '1'; Inc <= '1';
                    if (j = 7 and k = 7) then 
                        NextState <= S3 after Delay;
                    else
                        NextState <= S2 after Delay;
                    end if;
                
                -- Resets Count and Sum
                when S3 =>
                    Rst_counter <= '1'; Rst_sum <= '1';
                    NextState <= S4 after Delay;
                    
                -- Read COSBlock and InBlock addresses into Reg A and Reg B
                when S4 =>
                    Sel3 <= '0'; Sel5 <= '1'; Sel7 <= '1'; Sel8 <= '1';
                    R_en1 <= '1'; R_en2 <= '1'; Rst_p <= '1';
                    NextState <= S5 after Delay;
                    
                -- Multiply A and B
                when S5 =>
                    NextState <= S6 after Delay;
                    
                -- Add P and Sum to Sum.
                when S6 =>
                    LoadSum <= '1';
                    if (k = 7) then
                        NextState <= S8 after Delay; -- Goes to S8 if done with row.
                    else
                        NextState <= S7 after Delay; -- Goes to S7 if not done with row.
                    end if;
                    
                -- Increments Count and goes back to S4 for new calculation.
                when S7 =>
                    Inc <= '1';
                    NextState <= S4 after Delay;
                    
                -- Puts Sum into TempBlock address and resets Sum.
                when S8 =>
                    Sel1 <= '0';
                    W_en <= '1'; Rst_sum <= '1';               
                    if (i = 7 and j = 7 and k = 7) then
                        NextState <= S9 after Delay; -- Goes to next matrix multiplication if Count = 511
                    else
                        NextState <= S7 after Delay; -- Goes to S7 to continue with current matrix multiplicaton.
                    end if;
                    
                -- Resets Count
                when S9 =>
                    Rst_counter <= '1';
                    NextState <= S10 after Delay;
                    
                -- Read TempBlock and COSBlock(T) addresses into Reg A and Reg B
                when S10 =>
                    -- Selector Stuff
                    R_en1 <= '1'; R_en2 <= '1'; Rst_p <= '1';
                    NextState <= S11 after Delay;
                
                -- Multiply A and B    
                when S11 =>
                    NextState <= S12 after Delay;
                    
                -- Add P and Sum to Sum
                when S12 =>
                    LoadSum <= '1';
                    if (k = 7) then
                        NextState <= S14 after Delay; -- Goes to S14 if done with row.
                    else
                        NextState <= S13 after Delay; -- Goes to S13 if not done with row.
                    end if;
                    
                -- Increments Count and goes back to S10 for new calculation.
                when S13 =>
                    Inc <= '1';
                    NextState <= S10 after Delay;
                    
                -- Puts Sum into OutBlock address and resets Sum.
                when S14 =>
                    Sel1 <= '0'; Sel4 <= '0';
                    W_en <= '1'; Rst_sum <= '1'; 
                    if (i = 7 and j = 7 and k = 7) then
                        NextState <= S15 after Delay; -- Finished calculations and prepare for Done = 1
                    else
                        NextState <= S13 after Delay; -- Goes to S13 to continue with current matrix multiplicaton.
                    end if;
                    
                -- Reset Count and Set Done = 1
                when S15 =>
                    Rst_counter <= '1'; Done <= '1';
                    NextState <= S16 after Delay;
                    
                -- Finally output Dout from OutBlock
                when S16 =>
                    Sel2 <= '0'; Sel4 <= '0';
                    Oe <= '1'; R_en1 <= '1'; Inc <= '1';
                    if (j = 7 and k = 7) then
                        NextState <= S1 after Delay; -- Go back to init state if done
                    else
                        NextState <= S16 after Delay; -- Keep outputting otherwise
                    end if;
            END CASE;

        end process; 

End BEHAVIORAL;

 -------------------------------------------------------------
 --      top level: structure for DCT
 --      minimal clock cycle = 31.2 ns
 -------------------------------------------------------------
 
Library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.std_logic_misc.all;
use IEEE.std_logic_arith.all;


Entity DCT_str IS
      Port (
                Clk :           in std_logic;
                Start :         in std_logic;
                Din :           in INTEGER;
                Done :          out std_logic;
                Dout :          out INTEGER
              );
End DCT_str;


Architecture struct OF DCT_str IS

COMPONENT Multiplier IS
      PORT ( A : In    integer;
             B : In    integer;
             Product : Out   integer );
END COMPONENT;

COMPONENT Adder IS
      PORT (     A : In    integer;
                 B : In    integer;
                 Sum : Out   integer );
END COMPONENT;

COMPONENT Counter IS
      Port (    Clk : In    std_logic;
                Inc : In    std_logic;
                Rst : In    std_logic;
                i : Out   std_logic_vector(2 downto 0);
                j : Out   std_logic_vector(2 downto 0);
                k : Out   std_logic_vector(2 downto 0)  );
End COMPONENT;

COMPONENT MuxInt is
       Port (    C : In    std_logic;
                D0 : In    INTEGER;
                D1 : In    INTEGER;
                Dout : Out   INTEGER );
End COMPONENT;

COMPONENT Mux3 is
      Port (    C : In    std_logic;
                D0 : In    std_logic_vector(2 downto 0);
                D1 : In    std_logic_vector(2 downto 0);
                Dout : Out   std_logic_vector(2 downto 0) );
End COMPONENT;

COMPONENT Reg is
      Port (    Clk : In    std_logic;
                DIN : In    INTEGER;
                Rst : In    std_logic;
                Ld : In    std_logic;
                Dout : Out   INTEGER );
End COMPONENT;

COMPONENT RegFile IS
      Port (    R_addr1,R_addr2,W_addr: IN std_logic_vector(7 DOWNTO 0);
                R_en1,R_en2, W_en: IN std_logic;
                R_data1, R_data2: OUT INTEGER; 
                W_data: IN INTEGER; 
                Clk: IN std_logic );
End COMPONENT;

COMPONENT ThreeStateBuff IS
      Port (    Control_Input: IN std_logic;
                Data_Input: IN INTEGER;
                Output: OUT INTEGER );
End COMPONENT;

COMPONENT Controller IS
      Port (    Clk   : In    std_logic;
                Start : In    std_logic;
                Count : In    std_logic_vector(8 downto 0);
                Inc : Out   std_logic ;
                R_en1 : Out   std_logic ;
                R_en2 : Out   std_logic ;
                W_en : Out   std_logic ;
                LoadSum : Out   std_logic ;              
                Rst_counter : Out   std_logic;
                Rst_sum : Out   std_logic; 
                Rst_p : Out   std_logic := '0'; 
                Sel1 : Out   std_logic;
                Sel2 : Out   std_logic ;
                Sel3 : Out   std_logic ;
                Sel4 : Out   std_logic ;
                Sel5 : Out   std_logic ;
                Sel6 : Out   std_logic ;
                Sel7 : Out   std_logic ;
                Sel8 : Out   std_logic ;
                Oe   : Out   std_logic ;                 
                Done : Out   std_logic );
End COMPONENT;

--------------------------------------------------
--you may modify below signals or declare new ones  
--for the interconnections of the structural model
--------------------------------------------------

SIGNAL Inc, Rst_counter, Rst_sum, Rst_p:std_logic;
SIGNAL R_en1_s, R_en2_s :std_logic;
SIGNAL W_en_s :std_logic;
SIGNAL Write_sel_s, ij_sel_s, jk_sel_s, temp_out_sel_s, jk2_sel_s, in_to_s, cos_to_s, in_cos_s:std_logic;
SIGNAL muxout_ij, muxout_jk, muxout_temp_out, muxout_jk2, muxout_in_to, muxout_cos_to, muxout_in_cos: std_logic_vector(2 downto 0);
SIGNAL muxoutW: INTEGER;
SIGNAL mult_out: INTEGER;
SIGNAL add_out: INTEGER;
SIGNAL R_data1_out, R_data2_out : INTEGER;
SIGNAL i_s, j_s, k_s: std_logic_vector(2 downto 0);
SIGNAL LoadSum:std_logic;
SIGNAL reg_sum_out,reg_p_out,reg_a_out,reg_b_out: INTEGER;
SIGNAL Oe_s :std_logic;

Begin
    -- Major components that deal with the heavy work
    Ctrl: Controller PORT MAP (Clk => Clk, Start => Start, Count(8 downto 6) => i_s, Count(5 downto 3) => j_s,
                               Count(2 downto 0) => k_s, Inc => Inc, R_en1 => R_en1_s, R_en2 => R_en2_s, Rst_p => Rst_p, Oe => Oe_s,
                               W_en => W_en_s, Rst_counter => Rst_counter, LoadSum => LoadSum, Rst_sum => Rst_sum, Done => Done,
                               Sel1 => Write_sel_s, Sel2 => ij_sel_s, Sel3 => jk_sel_s, Sel4 => temp_out_sel_s,
                               Sel5 => jk2_sel_s, Sel6 => in_to_s, Sel7 => cos_to_s, Sel8 => in_cos_s);
    Cnt: Counter PORT MAP (Clk => Clk, Inc => Inc, Rst => Rst_counter, i => i_s, j => j_s, k => k_s);
    RF: RegFile PORT MAP (Clk => Clk, R_en1 => R_en1_s, R_en2 => R_en2_s, W_en => W_en_s,
                          W_data => muxoutW, R_data1 => R_data1_out, R_data2 => R_data2_out,
                          W_addr(7 downto 6) => muxout_in_to(1 downto 0), W_addr(5 downto 3) => muxout_ij, W_addr(2 downto 0) => muxout_jk,
                          R_addr1(7 downto 6) => muxout_cos_to(1 downto 0), R_addr1(5 downto 3) => muxout_ij, R_addr1(2 downto 0) => k_s,
                          R_addr2(7 downto 6) => muxout_in_cos(1 downto 0), R_addr2(5 downto 3) => muxout_jk, R_addr2(2 downto 0) => muxout_jk2);
    
    -- Registers that store intermediary values to reduce clock cycle
    RegA: Reg PORT MAP (Clk => Clk, DIN => R_data1_out, Rst => '0', Ld => '1', Dout => reg_a_out);
    RegB: Reg PORT MAP (Clk => Clk, DIN => R_data2_out, Rst => '0', Ld => '1', Dout => reg_b_out);
    RegP: Reg PORT MAP (Clk => Clk, DIN => mult_out, Rst => Rst_p, Ld => '1', Dout => reg_p_out);
    RegSum: Reg PORT MAP (Clk => Clk, DIN => add_out, Rst => Rst_sum, Ld => LoadSum, Dout => reg_sum_out);
    
    -- Algebraic components
    P: Multiplier PORT MAP (A => reg_a_out, B => reg_b_out, Product => mult_out);
    Sum: Adder PORT MAP (A => reg_p_out, B => reg_sum_out, Sum => add_out);
    
    -- Selectors that deal with RF addressing
    Write_sel: MuxInt PORT MAP (C => Write_sel_s, D1 => Din, D0 => reg_sum_out, Dout => muxoutW);
    i_j_sel: Mux3 PORT MAP (C => ij_sel_s, D1 => i_s, D0 => j_s, Dout => muxout_ij);
    j_k_sel: Mux3 PORT MAP (C => jk_sel_s, D1 => j_s, D0 => k_s, Dout => muxout_jk);
    temp_out_sel: Mux3 PORT MAP (C => temp_out_sel_s, D1 => "001", D0 => "000", Dout => muxout_temp_out);
    j_k_2_sel: Mux3 PORT MAP (C => jk2_sel_s, D1 => j_s, D0 => k_s, Dout => muxout_jk2);
    in_to_sel: Mux3 PORT MAP (C => in_to_s, D1 => "010", D0 => muxout_temp_out, Dout => muxout_in_to);
    cos_to_sel: Mux3 PORT MAP (C => cos_to_s, D1 => "011", D0 => muxout_temp_out, Dout => muxout_cos_to);
    in_cos_sel: Mux3 PORT MAP (C => in_cos_s, D1 => "010", D0 => "011", Dout => muxout_in_cos);
    
    -- Final Buffer to hold or release output
    Buf: ThreeStateBuff PORT MAP (Control_Input => Oe_s, Data_Input => R_data1_out, Output => Dout);
End struct;
 