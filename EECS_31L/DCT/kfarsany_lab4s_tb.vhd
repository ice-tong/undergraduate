--------------------------------------------------------------------------------
-- Company: QV's Minions
-- Engineer: Kian Farsany
--
-- Create Date:   
-- Design Name:   
-- Module Name:   
-- Project Name:  
-- Target Device:  
-- Tool versions:  
-- Description:   
-- 
-- VHDL Test Bench Created by ISE for module: DCT_str
-- 
-- Dependencies:
-- 
-- Revision:
-- Revision 0.01 - File Created
-- Additional Comments:
--
-- Notes: 
-- This testbench has been automatically generated using types std_logic and
-- std_logic_vector for the ports of the unit under test.  Xilinx recommends
-- that these types always be used for the top-level I/O of a design in order
-- to guarantee that the testbench will bind correctly to the post-implementation 
-- simulation model.
--------------------------------------------------------------------------------
LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
USE std.textio.ALL;
 
-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--USE ieee.numeric_std.ALL;
 
ENTITY tb_str IS
END tb_str;
 
ARCHITECTURE behavior OF tb_str IS 
 
    -- Component Declaration for the Unit Under Test (UUT)
 
    COMPONENT DCT_str
    PORT(
         Clk : IN  std_logic;
         Start : IN  std_logic;
         Din : IN  INTEGER;
         Done : OUT  std_logic;
         Dout : OUT  INTEGER
        );
    END COMPONENT;
    

   --Inputs
   signal Clk : std_logic := '0';
   signal Start : std_logic := '0';
   signal Din : INTEGER := 0;

    --Outputs
   signal Done : std_logic;
   signal Dout : INTEGER;

   -- Clock period definitions
   -- Adjust to your actual clock cycle!
   constant Clk_period : time := 32 ns;
 
BEGIN
 
    -- Instantiate the Unit Under Test (UUT)
   uut: DCT_str PORT MAP (
          Clk => Clk,
          Start => Start,
          Din => Din,
          Done => Done,
          Dout => Dout
        );

   -- Clock process definitions
   Clk_process :process
   begin
        Clk <= '0';
        wait for Clk_period/2;
        Clk <= '1';
        wait for Clk_period/2;
   end process;

	-- Feel free to modify any code below; this is just a template

    Start <= '0' after 0 ns,
             '1' after 50 ns,
             '0' after 100 ns;


   -- Stimulus process
   stim_proc: process
                  variable stringbuff : LINE;
                     variable a:integer:= 1;
                type RF is array ( 0 to 7, 0 to 7 ) of INTEGER;

                variable Result : RF := (
                   (56195370, -11595870, 14515110, -1054170, 9325350, 2513790, 6568290, 4622130),
                   (7775460, -1604460, 2008380, -145860, 1290300, 347820, 908820, 639540),
                   (72806580, -15023580, 18805740, -1365780, 12081900, 3256860, 8509860, 5988420),
                   (-3534300, 729300, -912900, 66300, -586500, -158100, -413100, -290700),
                   (31101840, -6417840, 8033520, -583440, 5161200, 1391280, 3635280, 2558160),
                   (12016620, -2479620, 3103860, -225420, 1994100, 537540, 1404540, 988380),
                   (-4241160, 875160, -1095480, 79560, -703800, -189720, -495720, -348840),
                   (4594590, -948090, 1186770, -86190, 762450, 205530, 537030, 377910)
                 );
        begin
                WRITE (stringbuff, string'("Starts Structural Simulation at "));
                WRITE (stringbuff, now);
                WRITELINE (output, stringbuff);
                ---------------------------------
                --      Handshaking/synchronizing
                ---------------------------------
                wait until Start =  '1';
                
                ---------------------------------
                --      Feed Data -- Sandwich Case
                ---------------------------------
                for i in 0 to 7 loop
                    wait until Clk = '1';
                    Din <= 255;
                end loop;
 
                -- continue feeding in rest of sandwich
				-- your code here
                for i in 0 to 7 loop
                    wait until Clk = '1';
                    Din <= 255;
                end loop;
                
                for i in 0 to 31 loop
                    wait until Clk = '1';
                    Din <= 0;
                end loop;
                
                for i in 0 to 15 loop
                    wait until Clk = '1';
                    Din <= 255;
                end loop;
                
                ---------------------------------
                --      Handshaking/synchronizing
                ---------------------------------
                wait until Done = '1';
                     wait for 5 ns;
                wait until Clk = '1' AND Clk'EVENT; 

                --------------------------------
                --      Verify
                --------------------------------
                
				-- check output values / you can check at the edge or anywhere in the clock cycle
				-- your code here
				for i in 0 to 7 loop
				    for j in 0 to 7 loop
				        wait until Clk = '1';
				        ASSERT (Dout = Result(i,j)) REPORT "ERROR: value incorrect at: " 
				        & integer'image(i) & "," & integer'image(j) & "; dout: " 
				        & integer'image(Dout) & "; expected: " & integer'image(Result(i,j)) SEVERITY warning;
				    end loop;
                end loop;
				
				
                -- for each clock cycle, start comparing values
                WRITE (stringbuff, string'("Verification completed. Simulation Ends at "));
                WRITE (stringbuff, now);
                WRITELINE (output, stringbuff);
                wait;
        end process;

END;