----------------------------------------------------------------------
-- Digital Design 101 Lab Assignment 1 - Y18
-- LFDetector Structural Model
----------------------------------------------------------------------
-- Student First Name : Kian
-- Student Last Name : Farsany
-- Student ID : 55375951
----------------------------------------------------------------------

LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
ENTITY NAND2 IS
   PORT (x: IN std_logic;
         y: IN std_logic;
         F: OUT std_logic);
END NAND2;  

ARCHITECTURE behav OF NAND2 IS
BEGIN
   PROCESS(x, y)
   BEGIN
      F <= NOT (x AND y) AFTER 1.4 ns; 
   END PROCESS;
END behav;
----------------------------------------------------------------------

LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
ENTITY LFDetector_structural IS
   PORT (Fuel3, Fuel2, Fuel1, Fuel0: IN std_logic;
         FuelWarningLight: OUT std_logic);
END LFDetector_structural;

ARCHITECTURE Structural OF LFDetector_structural IS

-- DO NOT modify any signals, ports, or entities above this line
-- add your code below this line
-- use the appropriate library component(s) specified in the lab handout
-- add the appropriate internal signals & wire your design below

    COMPONENT NAND2 IS
        PORT (x, y: IN std_logic;
              F: OUT std_logic);
    END COMPONENT;
    
    SIGNAL Fuel3_not, Fuel1_not, Fuel0_not,
           w1, w2, w3: std_logic;
           
BEGIN
    notF3: NAND2 PORT MAP (x => Fuel3, y => Fuel3, F => Fuel3_not);
    notF1: NAND2 PORT MAP (x => Fuel1, y => Fuel1, F => Fuel1_not);
    notF0: NAND2 PORT MAP (x => Fuel0, y => Fuel0, F => Fuel0_not);
    N1:    NAND2 PORT MAP (x => Fuel1_not, y => Fuel0_not, F => w1);
    N2:    NAND2 PORT MAP (x => Fuel2, y => w1, F => w2);
    N3:    NAND2 PORT MAP (x => Fuel3_not, y => w2, F => w3);
    N4:    NAND2 PORT MAP (x => w3, y => w3, F => FuelWarningLight);
END Structural;