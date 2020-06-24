----------------------------------------------------------------------
-- EECS31L/CSE31L Assignment2
-- FSM Structural Model
----------------------------------------------------------------------
-- Student First Name : Kian
-- Student Last Name : Farsany
-- Student ID : 55375951
----------------------------------------------------------------------

LIBRARY ieee;
USE ieee.std_logic_1164.ALL;

ENTITY Lab2s_FSM IS
     Port (Input : in  STD_LOGIC_VECTOR(2 DOWNTO 0);
           Clk : in  STD_LOGIC;
           Permit : out  STD_LOGIC;
           ReturnChange : out  STD_LOGIC);
END Lab2s_FSM;

ARCHITECTURE Structural OF Lab2s_FSM IS

-- DO NOT modify any signals, ports, or entities above this line
-- Required: Create 2 processes (one for updating state status and the other for describing transitions and outputs)
-- For the combinatorial process, use Boolean equations consisting of AND, OR, and NOT gates while expressing the delay in terms of the NAND gates. Remember to use your calculated delay from the lab handout.
-- For the state register process, use IF statements. Remember to use the calculated delay from the lab handout.
-- Figure out the appropriate sensitivity list of both the processes.
-- add your code here

    SUBTYPE StateType is STD_LOGIC_VECTOR (3 downto 0);
    SIGNAL C, N: StateType := "0000";
    
BEGIN

CombLogic: PROCESS (C, Input)
    BEGIN
    
    N(3) <= ( ( not C(3) and not C(2) and C(1) and not C(0) and Input(0) )
            or ( not C(3) and C(2) and not C(1) and not C(0) and Input(0) )
            or ( (not C(3) and C(2) and C(1) and not C(0)) and 
               (Input(1) or Input(0)) )
            or ( C(3) and ( Input(2) or Input(1) or Input(0) ) )
            ) after 5.6 ns;
            
    N(2) <= ( ( not C(3) and not C(2) and not C(1) and not C(0) and not Input(1) and Input(0) )
            or ( not C(3) and not C(2) and C(1) and not C(0) and Input(1) and not Input(0) )
            or ( not C(3) and not C(2) and C(1) and C(0) and not Input(2) and not Input(1) and not Input(0) )
            or ( not C(3) and C(2) and not C(1) and not C(0) and not Input(0) )
            or ( not C(3) and C(2) and not C(1) and C(0) )
            or ( not C(3) and C(2) and C(1) and not C(0) and not Input(1) and not Input(0) )
            or ( (not C(3) and C(2) and C(1) and C(0)) and
               (Input(2) or Input(1) or Input(0)) )
            ) after 5.6 ns;
            
    N(1) <= ( ( (not C(3) and not C(2) and not C(1) and not C(0)) and
              ( Input(1) xor Input(0) ) )
            or ( not C(3) and not C(2) and not C(1) and C(0) and not Input(2) and not Input(1) and not Input(0) )
            or ( not C(3) and not C(2) and C(1) and not C(0) and not Input(1) and not Input(0) )
            or ( (not C(3) and not C(2) and C(1) and C(0)) and
               (Input(2) or Input(1) or Input(0)) )
            or ( not C(3) and C(2) and not C(1) and not C(0) and Input(1) and not Input(0) )
            or ( not C(3) and C(2) and not C(1) and C(0) and not Input(2) and not Input(1) and not Input(0) )
            or ( not C(3) and C(2) and C(1) and not C(0) and not Input(1) and not Input(0) )
            or ( (not C(3) and C(2) and C(1) and C(0)) and
               (Input(2) or Input(1) or Input(0)) )
            ) after 5.6 ns;
            
    N(0) <= ( ( (not C(3) and not C(2) and not C(1) and not C(0)) and
                ( (Input(2) and not Input(1) and not Input(0))
                or (not Input(2) and Input(1) and not Input(0))
                or (not Input(2) and not Input(1) and Input(0)) ) )
            or ( (not C(3) and not C(2) and not C(1) and C(0)) and
               (Input(2) or Input(1) or Input(0)) )
            or ( (not C(3) and not C(2) and C(1) and not C(0)) and
               (Input(2) or Input(1)) )
            or ( (not C(3) and not C(2) and C(1) and C(0)) and
               (Input(2) or Input(1) or Input(0)) )               
            or ( (not C(3) and C(2) and not C(1) and not C(0)) and
               (Input(2) or Input(1)) )
            or ( (not C(3) and C(2) and not C(1) and C(0)) and
               (Input(2) or Input(1) or Input(0)) ) 
            or ( not C(3) and C(2) and C(1) and not C(0) and Input(2) ) 
            or ( (not C(3) and C(2) and C(1) and C(0)) and
               (Input(2) or Input(1) or Input(0)) )
            or ( (C(3) and C(0)) and
               (Input(2) or Input(1) or Input(0)) )
            ) after 5.6 ns;
            
   
          
    
    Permit <= ( (not C(3) and C(2) and C(1) and C(0)) or 
               (C(3) and not C(2) and not C(1) and not C(0)) );
               
    ReturnChange <= C(3);
    
    END PROCESS CombLogic;
    
 
StateRegister: Process (clk)
    BEGIN
        if (clk = '1' and clk'EVENT) then
         C <= N after 4 ns;
        end if;
    END PROCESS StateRegister;

END Structural;