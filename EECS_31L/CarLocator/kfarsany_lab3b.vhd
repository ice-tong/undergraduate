----------------------------------------------------------------------
-- EECS31L/CSE31L Assignment3
-- Locator Behavioral Model
----------------------------------------------------------------------
-- Student First Name : Kian
-- Student Last Name : Farsany
-- Student ID : 55375951
----------------------------------------------------------------------

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
USE ieee.std_logic_unsigned.ALL;


entity Locator_beh  is
    Port ( Start : in  STD_LOGIC;
           Rst : in  STD_LOGIC;
           Clk : in  STD_LOGIC;
           Loc : out  STD_LOGIC_VECTOR (15 downto 0);
           Done : out  STD_LOGIC);
end Locator_beh;

architecture Behavioral of Locator_beh  is

   TYPE regArray_type IS 
      ARRAY (0 TO 7) OF std_logic_vector(15 DOWNTO 0); 
   SIGNAL regArray : regArray_type :=  (X"0000", X"000B", X"0003", X"0005", X"0008", X"0000", X"0000", X"0000");     

-- do not modify any code above this line
-- additional variables/signals can be declared if needed below
-- add your code starting here
   
   TYPE StateType IS
        (S_Start, S_On1, S_On2, S_On3, S_On4, S_On5, S_On6, S_On7);
   SIGNAL CurrState, NextState: StateType;
   SIGNAL OutReg: std_logic_vector(15 downto 0);
   
   
begin

   StateReg: PROCESS (Clk)
   BEGIN
        if (Clk = '1' and Clk'EVENT) then
            if (Rst = '1') then
                CurrState <= S_Start;
            else
                CurrState <= NextState;
            end if;
        end if;
   END PROCESS StateReg;
   
   CombLogic: PROCESS (CurrState, Start)
        VARIABLE v32: STD_LOGIC_VECTOR (31 DOWNTO 0);
   BEGIN
        Loc <= (others => 'Z');
        Done <= '0';
        
        CASE CurrState IS
            when S_Start =>
                if (Start = '1') then
                    NextState <= S_On1;
                else 
                    NextState <= S_Start;
                end if;
            when S_On1 =>
                v32 := regArray(4) * regArray(4);
                regArray(5) <= v32(15 downto 0);
                NextState <= S_On2;
            when S_On2 =>
                v32 := regArray(5) * regArray(1);
                regArray(5) <= v32(15 downto 0);
                NextState <= S_On3;
            when S_On3 =>
                regArray(5) <= '0' & regArray(5)(15 downto 1);
                NextState <= S_On4; 
            when S_On4 =>
                v32 := regArray(2) * regArray(4);
                regArray(6) <= v32(15 downto 0);
                NextState <= S_On5;
            when S_On5 =>
                regArray(5) <= regArray(5) + regArray(6);
                NextState <= S_On6;
            when S_On6 =>
                regArray(5) <= regArray(5) + regArray(3);
                OutReg <= regArray(5) + regArray(3);
                NextState <= S_On7;
            when S_On7 =>
                Loc <= OutReg;
                Done <= '1';
                NextState <= S_Start;
        END CASE;
   END PROCESS CombLogic;

end Behavioral;

