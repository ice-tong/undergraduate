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
 
ENTITY tb_beh IS
END tb_beh;
 
ARCHITECTURE behavior OF tb_beh IS 
 
    -- Component Declaration for the Unit Under Test (UUT)
 
    COMPONENT DCT_beh
    PORT(
         Clk : IN  std_logic;
         Start : IN  std_logic;
         Din : IN  integer;
         Done : OUT  std_logic;
         Dout : OUT  integer
        );
    END COMPONENT;
    

   --Inputs
   signal Clk : std_logic := '0';
   signal Start : std_logic := '0';
   signal Din : integer := 0;

 	--Outputs
   signal Done : std_logic;
   signal Dout : integer;

   -- Clock period definitions
   constant Clk_period : time := 10 ns;
 
BEGIN
 
	-- Instantiate the Unit Under Test (UUT)
   uut: DCT_beh PORT MAP (
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

                -- variable Result : RF := (
				   -- (...),
				   -- (...),
				   -- (...),
				   -- (...),
				   -- (...),
				   -- (...),
				   -- (...),
				   -- (...)
				 -- );
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
                    if (i /= 0) then
                        wait until Clk = '1';
                    end if;
                    Din <= 255;
                end loop;

				-- continue feeding in rest of sandwich
				-- your code here
				
				for i in 0 to 7 loop
				    wait until Clk = '1';
				    Din <= 255;
                end loop;
                
                for i in 0 to 3 loop
                    for j in 0 to 7 loop
                        wait until Clk = '1';
                        Din <= 0;
                    end loop;
                end loop;
                
                for i in 0 to 1 loop
                    for j in 0 to 7 loop
                        wait until Clk = '1';
                        Din <= 255;
                    end loop;
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
				wait for 5 ns;
				-- asserting row 1
			    ASSERT Dout = 56195370 REPORT "ERROR AT 1,1" SEVERITY WARNING;
			    wait for 10 ns;
                ASSERT Dout = -11595870 REPORT "ERROR AT 1,2" SEVERITY WARNING;
                wait for 10 ns;
                ASSERT Dout = 14515110 REPORT "ERROR AT 1,3" SEVERITY WARNING;
                wait for 10 ns;
                ASSERT Dout = -1054170 REPORT "ERROR AT 1,4" SEVERITY WARNING;
                wait for 10 ns;
                ASSERT Dout = 9325350 REPORT "ERROR AT 1,5" SEVERITY WARNING;
                wait for 10 ns;
                ASSERT Dout = 2513790 REPORT "ERROR AT 1,6" SEVERITY WARNING;
                wait for 10 ns;
                ASSERT Dout = 6568290 REPORT "ERROR AT 1,7" SEVERITY WARNING;
                wait for 10 ns;
                ASSERT Dout = 4622130 REPORT "ERROR AT 1,8" SEVERITY WARNING;
                wait for 10 ns;
                
                -- asserting row 2
                ASSERT Dout = 7775460 REPORT "ERROR AT 2,1" SEVERITY WARNING;
                wait for 10 ns;
                ASSERT Dout = -1604460 REPORT "ERROR AT 2,2" SEVERITY WARNING;
                wait for 10 ns;
                ASSERT Dout = 2008380 REPORT "ERROR AT 2,3" SEVERITY WARNING;
                wait for 10 ns;
                ASSERT Dout = -145860 REPORT "ERROR AT 2,4" SEVERITY WARNING;
                wait for 10 ns;
                ASSERT Dout = 1290300 REPORT "ERROR AT 2,5" SEVERITY WARNING;
                wait for 10 ns;
                ASSERT Dout = 347820 REPORT "ERROR AT 2,6" SEVERITY WARNING;
                wait for 10 ns;
                ASSERT Dout = 908820 REPORT "ERROR AT 2,7" SEVERITY WARNING;
                wait for 10 ns;
                ASSERT Dout = 639540 REPORT "ERROR AT 2,8" SEVERITY WARNING;
                wait for 10 ns;
                
                -- asserting row 3
                ASSERT Dout = 72806580 REPORT "ERROR AT 3,1" SEVERITY WARNING;
                wait for 10 ns;
                ASSERT Dout = -15023580 REPORT "ERROR AT 3,2" SEVERITY WARNING;
                wait for 10 ns;
                ASSERT Dout = 18805740 REPORT "ERROR AT 3,3" SEVERITY WARNING;
                wait for 10 ns;
                ASSERT Dout = -1365780 REPORT "ERROR AT 3,4" SEVERITY WARNING;
                wait for 10 ns;
                ASSERT Dout = 12081900 REPORT "ERROR AT 3,5" SEVERITY WARNING;
                wait for 10 ns;
                ASSERT Dout = 3256860 REPORT "ERROR AT 3,6" SEVERITY WARNING;
                wait for 10 ns;
                ASSERT Dout = 8509860 REPORT "ERROR AT 3,7" SEVERITY WARNING;
                wait for 10 ns;
                ASSERT Dout = 5988420 REPORT "ERROR AT 3,8" SEVERITY WARNING;
                wait for 10 ns;
                
                -- asserting row 4
                ASSERT Dout = -3534300 REPORT "ERROR AT 4,1" SEVERITY WARNING;
                wait for 10 ns;
                ASSERT Dout = 729300 REPORT "ERROR AT 4,2" SEVERITY WARNING;
                wait for 10 ns;
                ASSERT Dout = -912900 REPORT "ERROR AT 4,3" SEVERITY WARNING;
                wait for 10 ns;
                ASSERT Dout = 66300 REPORT "ERROR AT 4,4" SEVERITY WARNING;
                wait for 10 ns;
                ASSERT Dout = -586500 REPORT "ERROR AT 4,5" SEVERITY WARNING;
                wait for 10 ns;
                ASSERT Dout = -158100 REPORT "ERROR AT 4,6" SEVERITY WARNING;
                wait for 10 ns;
                ASSERT Dout = -413100 REPORT "ERROR AT 4,7" SEVERITY WARNING;
                wait for 10 ns;
                ASSERT Dout = -290700 REPORT "ERROR AT 4,8" SEVERITY WARNING;
                wait for 10 ns;
                
                -- asserting row 5
                ASSERT Dout = 31101840 REPORT "ERROR AT 5,1" SEVERITY WARNING;
                wait for 10 ns;
                ASSERT Dout = -6417840 REPORT "ERROR AT 5,2" SEVERITY WARNING;
                wait for 10 ns;
                ASSERT Dout = 8033520 REPORT "ERROR AT 5,3" SEVERITY WARNING;
                wait for 10 ns;
                ASSERT Dout = -583440 REPORT "ERROR AT 5,4" SEVERITY WARNING;
                wait for 10 ns;
                ASSERT Dout = 5161200 REPORT "ERROR AT 5,5" SEVERITY WARNING;
                wait for 10 ns;
                ASSERT Dout = 1391280 REPORT "ERROR AT 5,6" SEVERITY WARNING;
                wait for 10 ns;
                ASSERT Dout = 3635280 REPORT "ERROR AT 5,7" SEVERITY WARNING;
                wait for 10 ns;
                ASSERT Dout = 2558160 REPORT "ERROR AT 5,8" SEVERITY WARNING;
                wait for 10 ns;
                
                -- asserting row 6
                ASSERT Dout = 12016620 REPORT "ERROR AT 6,1" SEVERITY WARNING;
                wait for 10 ns;
                ASSERT Dout = -2479620 REPORT "ERROR AT 6,2" SEVERITY WARNING;
                wait for 10 ns;
                ASSERT Dout = 3103860 REPORT "ERROR AT 6,3" SEVERITY WARNING;
                wait for 10 ns;
                ASSERT Dout = -225420 REPORT "ERROR AT 6,4" SEVERITY WARNING;
                wait for 10 ns;
                ASSERT Dout = 1994100 REPORT "ERROR AT 6,5" SEVERITY WARNING;
                wait for 10 ns;
                ASSERT Dout = 537540 REPORT "ERROR AT 6,6" SEVERITY WARNING;
                wait for 10 ns;
                ASSERT Dout = 1404540 REPORT "ERROR AT 6,7" SEVERITY WARNING;
                wait for 10 ns;
                ASSERT Dout = 988380 REPORT "ERROR AT 6,8" SEVERITY WARNING;
                wait for 10 ns;
                
                -- asserting row 7
                ASSERT Dout = -4241160 REPORT "ERROR AT 7,1" SEVERITY WARNING;
                wait for 10 ns;
                ASSERT Dout = 875160 REPORT "ERROR AT 7,2" SEVERITY WARNING;
                wait for 10 ns;
                ASSERT Dout = -1095480 REPORT "ERROR AT 7,3" SEVERITY WARNING;
                wait for 10 ns;
                ASSERT Dout = 79560 REPORT "ERROR AT 7,4" SEVERITY WARNING;
                wait for 10 ns;
                ASSERT Dout = -703800 REPORT "ERROR AT 7,5" SEVERITY WARNING;
                wait for 10 ns;
                ASSERT Dout = -189720 REPORT "ERROR AT 7,6" SEVERITY WARNING;
                wait for 10 ns;
                ASSERT Dout = -495720 REPORT "ERROR AT 7,7" SEVERITY WARNING;
                wait for 10 ns;
                ASSERT Dout = -348840 REPORT "ERROR AT 7,8" SEVERITY WARNING;
                wait for 10 ns;
                
                -- asserting row 8
                ASSERT Dout = 4594590 REPORT "ERROR AT 8,1" SEVERITY WARNING;
                wait for 10 ns;
                ASSERT Dout = -948090 REPORT "ERROR AT 8,2" SEVERITY WARNING;
                wait for 10 ns;
                ASSERT Dout = 1186770 REPORT "ERROR AT 8,3" SEVERITY WARNING;
                wait for 10 ns;
                ASSERT Dout = -86190 REPORT "ERROR AT 8,4" SEVERITY WARNING;
                wait for 10 ns;
                ASSERT Dout = 762450 REPORT "ERROR AT 8,5" SEVERITY WARNING;
                wait for 10 ns;
                ASSERT Dout = 205530 REPORT "ERROR AT 8,6" SEVERITY WARNING;
                wait for 10 ns;
                ASSERT Dout = 537030 REPORT "ERROR AT 8,7" SEVERITY WARNING;
                wait for 10 ns;
                ASSERT Dout = 377910 REPORT "ERROR AT 8,8" SEVERITY WARNING;
                wait for 10 ns;
                
			    
				-- for each clock cycle now, start comparing values
				WRITE (stringbuff, string'("Verification completed. Simulation Ends at "));
				WRITE (stringbuff, now);
				WRITELINE (output, stringbuff);
				wait;
        end process;

END;