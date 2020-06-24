----------------------------------------------------------------------
-- Digital Design 101 Lab Assignment 1 - Y18
-- LFDetector Behavioral Model
----------------------------------------------------------------------
-- Student First Name : Kian
-- Student Last Name : Farsany
-- Student ID : 55375951
----------------------------------------------------------------------

LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
 
ENTITY LFDetector_behav IS
    PORT (Fuel3, Fuel2, Fuel1, Fuel0: IN std_logic;
         FuelWarningLight: OUT std_logic);
END LFDetector_behav;

ARCHITECTURE Behavior OF LFDetector_behav IS
BEGIN
    PROCESS (Fuel3, Fuel2, Fuel1, Fuel0)
    BEGIN
    FuelWarningLight <= (NOT Fuel3 AND NOT Fuel2)
                     OR (NOT Fuel3 AND NOT Fuel1 AND NOT Fuel0);
    END PROCESS;

END Behavior;