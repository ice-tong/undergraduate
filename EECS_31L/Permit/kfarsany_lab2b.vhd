----------------------------------------------------------------------
-- EECS31L/CSE31L Assignment2
-- FSM Behavioral Model
----------------------------------------------------------------------
-- Student First Name : Kian
-- Student Last Name : Farsany
-- Student ID : 55375951
----------------------------------------------------------------------

LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
USE ieee.std_logic_arith.ALL;
USE ieee.std_logic_unsigned.ALL;

entity Lab2b_FSM is
    Port ( Input : in  STD_LOGIC_VECTOR(2 DOWNTO 0);
           Clk : in  STD_LOGIC;
           Permit : out  STD_LOGIC;
           ReturnChange : out  STD_LOGIC);
end Lab2b_FSM;

architecture Behavioral of Lab2b_FSM is

-- DO NOT modify any signals, ports, or entities above this line
-- Recommendation: Create 2 processes (one for updating state status and the other for describing transitions and outputs)
-- Figure out the appropriate sensitivity list of both the processes.
-- Use CASE statements and IF/ELSE/ELSIF statements to describe your processes.
-- add your code here

type StateType is 
    (s0, s5, s10, s15, s20, s25, s30, s35);
    
    Signal Curr_State, Next_State: StateType;
    
BEGIN

CombLogic: Process (Input, Curr_State)
BEGIN
    case Curr_State is
    
       when s0 =>
        if (Input'EVENT) then
            Permit <= '0';
            ReturnChange <= '0';
            if (Input = "100") then
                Next_State <= s5;
            elsif (Input = "010") then
                Next_State <= s10;
            elsif (Input = "001") then
                Next_State <= s20;
            else
                Next_State <= s0;
            end if;
        end if;
        
        when s5 =>
         if (Input'EVENT) then
            Permit <= '0';
            ReturnChange <= '0';
            if (Input = "100") then
                Next_State <= s10;
            elsif (Input = "010") then
                Next_State <= s15;
            elsif (Input = "001") then
                Next_State <= s25;
            elsif (Input = "111") then
                Next_State <= s0;
                ReturnChange <= '1';
            else
                Next_State <= s5;
            end if;
         end if;
           
        when s10 =>
        if (Input'EVENT) then
            Permit <= '0';
            ReturnChange <= '0';
            if (Input = "100") then
                Next_State <= s15;
            elsif (Input = "010") then
                Next_State <= s20;
            elsif (Input = "001") then
                Next_State <= s30;
            elsif (Input = "111") then
                Next_State <= s0;
                ReturnChange <= '1';
            else
                Next_State <= s10;
            end if;
         end if;
            
         when s15 =>
          if (Input'EVENT) then
            Permit <= '0';
            ReturnChange <= '0';
            if (Input = "100") then
                Next_State <= s20;
            elsif (Input = "010") then
                Next_State <= s25;
            elsif (Input = "001") then
                Next_State <= s35;
            elsif (Input = "111") then
                Next_State <= s0;
                ReturnChange <= '1';
            else
                Next_State <= s15;
            end if;
         end if;
            
         when s20 =>
            Permit <= '1';
            ReturnChange <= '0';
            Next_State <= s0;
            
         when s25 =>
            Permit <= '1';
            ReturnChange <= '1';
            Next_state <= s0;
         
         when s30 =>
            Permit <= '1';
            ReturnChange <= '1';
            Next_state <= s0;
                        
         when s35 =>
            Permit <= '1';
            ReturnChange <= '1';
            Next_state <= s0;
    end case;
END PROCESS CombLogic;

StateRegister: Process (Clk)
BEGIN
    if (clk = '1' and clk'EVENT) then
        Curr_State <= Next_State;
    end if;
END PROCESS StateRegister;

END Behavioral;