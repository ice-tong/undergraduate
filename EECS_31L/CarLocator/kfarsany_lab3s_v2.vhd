----------------------------------------------------------------------
-- EECS31L/CSE31L Assignment3 - updated version Summer 2018
-- Locator Structural Model
----------------------------------------------------------------------
-- Student First Name : Kian
-- Student Last Name : Farsany
-- Student ID : 55375951
----------------------------------------------------------------------

---------- Components library ----------

---------- 8x16 Register File ----------

LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
USE ieee.std_logic_unsigned.ALL;

ENTITY RegFile IS
   PORT (R_Addr1, R_Addr2, W_Addr: IN std_logic_vector(2 DOWNTO 0);
         R_en, W_en: IN std_logic;
         Reg_Data1 : OUT std_logic_vector(15 DOWNTO 0); 
			Reg_Data2 : OUT std_logic_vector(15 DOWNTO 0); 
         W_Data: IN std_logic_vector(15 DOWNTO 0); 
         Clk, Rst: IN std_logic);
END RegFile;

ARCHITECTURE Beh OF RegFile IS 
   TYPE regArray_type IS 
      ARRAY (0 TO 7) OF std_logic_vector(15 DOWNTO 0); 
   SIGNAL regArray : regArray_type;
BEGIN
   WriteProcess: PROCESS(Clk)    
   BEGIN
      IF (Clk = '1' AND Clk'EVENT) THEN
         IF (Rst = '1') THEN
            regArray(0) <= X"0000" AFTER 6.0 NS;
            regArray(1) <= X"000B" AFTER 6.0 NS;
            regArray(2) <= X"0003" AFTER 6.0 NS;
            regArray(3) <= X"0005" AFTER 6.0 NS;
            regArray(4) <= X"0008" AFTER 6.0 NS;
            regArray(5) <= X"0000" AFTER 6.0 NS;
            regArray(6) <= X"0000" AFTER 6.0 NS;
            regArray(7) <= X"0000" AFTER 6.0 NS;
         ELSE
            IF (W_en = '1') THEN
                regArray(conv_integer(W_Addr)) <= W_Data AFTER 6.0 NS;
                END IF;
        END IF;
     END IF;
   END PROCESS;
            
   ReadProcess1: PROCESS(R_en, R_Addr1, regArray)
   BEGIN
      IF (R_en = '1') THEN
        CASE R_Addr1 IS
            WHEN "000" =>
                Reg_Data1 <= regArray(0) AFTER 6.0 NS;
            WHEN "001" =>
                Reg_Data1 <= regArray(1) AFTER 6.0 NS;
            WHEN "010" =>
                Reg_Data1 <= regArray(2) AFTER 6.0 NS;
            WHEN "011" =>
                Reg_Data1 <= regArray(3) AFTER 6.0 NS;
            WHEN "100" =>
                Reg_Data1 <= regArray(4) AFTER 6.0 NS;
            WHEN "101" =>
                Reg_Data1 <= regArray(5) AFTER 6.0 NS;
            WHEN "110" =>
                Reg_Data1 <= regArray(6) AFTER 6.0 NS;
            WHEN "111" =>
                Reg_Data1 <= regArray(7) AFTER 6.0 NS;
            WHEN OTHERS =>
                Reg_Data1 <= (OTHERS=>'0') AFTER 6.0 NS;
        END CASE;
      ELSE
        Reg_Data1 <= (OTHERS=>'0') AFTER 6.0 NS;
      END IF;
   END PROCESS;
	
	ReadProcess2: PROCESS(R_en, R_Addr2, regArray)
   BEGIN
      IF (R_en = '1') THEN
        CASE R_Addr2 IS
            WHEN "000" =>
                Reg_Data2 <= regArray(0) AFTER 6.0 NS;
            WHEN "001" =>
                Reg_Data2 <= regArray(1) AFTER 6.0 NS;
            WHEN "010" =>
                Reg_Data2 <= regArray(2) AFTER 6.0 NS;
            WHEN "011" =>
                Reg_Data2 <= regArray(3) AFTER 6.0 NS;
            WHEN "100" =>
                Reg_Data2 <= regArray(4) AFTER 6.0 NS;
            WHEN "101" =>
                Reg_Data2 <= regArray(5) AFTER 6.0 NS;
            WHEN "110" =>
                Reg_Data2 <= regArray(6) AFTER 6.0 NS;
            WHEN "111" =>
                Reg_Data2 <= regArray(7) AFTER 6.0 NS;
            WHEN OTHERS =>
                Reg_Data2 <= (OTHERS=>'0') AFTER 6.0 NS;
        END CASE;
      ELSE
        Reg_Data2 <= (OTHERS=>'0') AFTER 6.0 NS;
      END IF;
   END PROCESS;
END Beh;


---------- 16-Bit ALU ----------

LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
USE ieee.std_logic_unsigned.ALL;


ENTITY ALU IS
    PORT (Sel: IN std_logic;
            A: IN std_logic_vector(15 DOWNTO 0);
            B: IN std_logic_vector(15 DOWNTO 0);
            ALU_Out: OUT std_logic_vector (15 DOWNTO 0) );
END ALU;

ARCHITECTURE Beh OF ALU IS

BEGIN
    PROCESS (A, B)
         variable temp: std_logic_vector(31 DOWNTO 0):= X"00000000";
    BEGIN
        IF (Sel = '0') THEN
            ALU_Out <= A + B AFTER 12 NS;                
        ELSIF (Sel = '1') THEN
            temp := A * B ;
                ALU_Out <= temp(15 downto 0) AFTER 12 NS; 
        END IF;
          
    END PROCESS;
END Beh;


---------- 16-bit Shifter ----------

LIBRARY ieee;
USE ieee.std_logic_1164.ALL;

ENTITY Shifter IS
   PORT (I: IN std_logic_vector(15 DOWNTO 0);
         Q: OUT std_logic_vector(15 DOWNTO 0);
         sel: IN std_logic );
END Shifter;

ARCHITECTURE Beh OF Shifter IS 
BEGIN
   PROCESS (I,sel) 
   BEGIN
         IF (sel = '1') THEN 
            Q <= I(14 downto 0) & '0' AFTER 4.0 NS;
         ELSE
            Q <= '0' & I(15 downto 1) AFTER 4.0 NS;
         END IF;   
   END PROCESS; 
END Beh;


---------- 2-to-1 Selector ----------

LIBRARY ieee;
USE ieee.std_logic_1164.ALL;

ENTITY Selector IS
   PORT (sel: IN std_logic;
         x,y: IN std_logic_vector(15 DOWNTO 0);
         f: OUT std_logic_vector(15 DOWNTO 0));
END Selector;

ARCHITECTURE Beh OF Selector IS 
BEGIN
   PROCESS (x,y,sel)
   BEGIN
         IF (sel = '0') THEN
            f <= x AFTER 3.0 NS;
         ELSE
            f <= y AFTER 3.0 NS;
         END IF;   
   END PROCESS; 
END Beh;


---------- 16-bit Register ----------

LIBRARY ieee;
USE ieee.std_logic_1164.ALL;

ENTITY Reg IS
   PORT (I: IN std_logic_vector(15 DOWNTO 0);
         Q: OUT std_logic_vector(15 DOWNTO 0);
         Ld: IN std_logic; 
         Clk, Rst: IN std_logic );
END Reg;

ARCHITECTURE Beh OF Reg IS 
BEGIN
   PROCESS (Clk)
   BEGIN
      IF (Clk = '1' AND Clk'EVENT) THEN
         IF (Rst = '1') THEN
            Q <= X"0000" AFTER 4.0 NS;
         ELSIF (Ld = '1') THEN
            Q <= I AFTER 4.0 NS;
         END IF;   
      END IF;
   END PROCESS; 
END Beh;

---------- 16-bit Three-state Buffer ----------

LIBRARY ieee;
USE ieee.std_logic_1164.ALL;

ENTITY ThreeStateBuff IS
    PORT (Control_Input: IN std_logic;
          Data_Input: IN std_logic_vector(15 DOWNTO 0);
          Output: OUT std_logic_vector(15 DOWNTO 0) );
END ThreeStateBuff;

ARCHITECTURE Beh OF ThreeStateBuff IS
BEGIN
    PROCESS (Control_Input, Data_Input)
    BEGIN
        IF (Control_Input = '1') THEN
            Output <= Data_Input AFTER 2 NS;
        ELSE
            Output <= (OTHERS=>'Z') AFTER 2 NS;
        END IF;
    END PROCESS;
END Beh;

---------- Controller ----------

LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
USE ieee.std_logic_unsigned.ALL;

ENTITY Controller IS
    PORT(R_en: OUT std_logic;
         W_en: OUT std_logic;
         R_Addr1: OUT std_logic_vector(2 DOWNTO 0);
			R_Addr2: OUT std_logic_vector(2 DOWNTO 0);
         W_Addr: OUT std_logic_vector(2 DOWNTO 0);
         Shifter_Sel: OUT std_logic;
         Selector_Sel: OUT std_logic;
         ALU_sel : OUT std_logic;
         OutReg_Ld: OUT std_logic;
         Oe: OUT std_logic;
         Done: OUT std_logic;
         Start, Clk, Rst: IN std_logic); 
END Controller;


ARCHITECTURE Beh OF Controller IS

-------------------------------------------------------
-- Hint:
-- Controller shall consist of a CombLogic process 
-- containing case-statement and a StateReg process.
--      
-------------------------------------------------------

 -- add your code here

TYPE StateType IS
    (S_Start, S_On1, S_On2, S_On3, S_On4, S_On5, S_On6, S_On7);
    
SIGNAL CurrState, NextState: StateType;

BEGIN
    CtrlLogic : PROCESS (CurrState, Start)
    BEGIN
        R_en <= '1'; W_en <= '1'; W_Addr <= "101";
        ALU_sel <= '1'; Shifter_Sel <= '0'; Selector_Sel <= '1';
        OutReg_Ld <= '0'; Oe <= '0'; Done <= '0';
        -- The assignments above are set before the case statement because
        -- they will either always be that value or they will only change once
        -- for some given state thanks to don't care conditions; 
        -- so when they change, I will assign them accordingly
        -- inside the case statemnt for the proper state.
        CASE CurrState IS
            when S_Start =>
                R_en <= '0'; W_en <= '0';
                if (Start = '1') then
                    NextState <= S_On1 after 11 ns;
                else
                    NextState <= S_Start after 11 ns;
                end if;
            when S_On1 =>
                R_Addr1 <= "100"; R_Addr2 <= "100";
                NextState <= S_On2 after 11 ns;
            when S_On2 =>
                R_Addr1 <= "101"; R_Addr2 <= "001";
                NextState <= S_On3 after 11 ns;
            when S_On3 =>
                R_Addr2 <= "101"; Selector_Sel <= '0';
                NextState <= S_On4 after 11 ns;
            When S_On4 =>
                R_Addr1 <= "010"; R_Addr2 <= "100"; W_Addr <= "110";
                NextState <= S_On5 after 11 ns;
            When S_On5 =>
                R_Addr1 <= "101"; R_Addr2 <= "110"; ALU_Sel <= '0';
                NextState <= S_On6 after 11 ns;
            When S_On6 =>
                R_Addr1 <= "101"; R_Addr2 <= "011"; ALU_Sel <= '0'; OutReg_Ld <= '1';
                NextState <= S_On7 after 11 ns;
            When S_On7 =>
                Oe <= '1'; Done <= '1';
                NextState <= S_Start after 11 ns;
        END CASE;
    END PROCESS CtrlLogic;
    
    CtrlReg : PROCESS (Clk)
    BEGIN
        if (Clk = '1' and Clk'EVENT) then
            if (Rst = '1') then
                CurrState <= S_Start after 4 ns;
            else
                CurrState <= NextState after 4 ns;
            end if;
        end if;
    END PROCESS CtrlReg;
END Beh;


---------- Locator (with clock cycle =  37 NS )----------
--         INDICATE YOUR CLOCK CYCLE TIME ABOVE      ----

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
USE ieee.std_logic_unsigned.ALL;

entity Locator_struct is
    Port ( Start : in  STD_LOGIC;
           Rst : in  STD_LOGIC;
           Clk : in  STD_LOGIC;
           Loc : out  STD_LOGIC_VECTOR (15 downto 0);
           Done : out  STD_LOGIC);
end Locator_struct;

architecture Struct of Locator_struct is
    
    COMPONENT RegFile IS
        PORT (  R_Addr1, R_Addr2, W_Addr: IN std_logic_vector(2 DOWNTO 0);
                R_en, W_en: IN std_logic;
                Reg_Data1: OUT std_logic_vector(15 DOWNTO 0); 
				Reg_Data2: OUT std_logic_vector(15 DOWNTO 0);
                W_Data: IN std_logic_vector(15 DOWNTO 0); 
                Clk, Rst: IN std_logic );
    END COMPONENT;
    
    COMPONENT ALU IS
        PORT (Sel: IN std_logic;
                A: IN STD_LOGIC_VECTOR(15 DOWNTO 0);
                B: IN STD_LOGIC_VECTOR(15 DOWNTO 0);
                ALU_Out: OUT STD_LOGIC_VECTOR (15 DOWNTO 0) );
    END COMPONENT;

    COMPONENT Shifter IS
         PORT (I: IN std_logic_vector(15 DOWNTO 0);
               Q: OUT std_logic_vector(15 DOWNTO 0);
               sel: IN std_logic );
    END COMPONENT;

    COMPONENT Selector IS
        PORT (sel: IN std_logic;
              x,y: IN std_logic_vector(15 DOWNTO 0);
              f: OUT std_logic_vector(15 DOWNTO 0) );
    END COMPONENT;
   
    COMPONENT Reg IS
        PORT (I: IN std_logic_vector(15 DOWNTO 0);
              Q: OUT std_logic_vector(15 DOWNTO 0);
              Ld: IN std_logic; 
              Clk, Rst: IN std_logic );
    END COMPONENT;
    
    COMPONENT ThreeStateBuff IS
        PORT (Control_Input: IN std_logic;
              Data_Input: IN std_logic_vector(15 DOWNTO 0);
              Output: OUT std_logic_vector(15 DOWNTO 0) );
    END COMPONENT;
    
    COMPONENT Controller IS
       PORT(R_en: OUT std_logic;
            W_en: OUT std_logic;
            R_Addr1: OUT std_logic_vector(2 DOWNTO 0);
				R_Addr2: OUT std_logic_vector(2 DOWNTO 0);
            W_Addr: OUT std_logic_vector(2 DOWNTO 0);
            Shifter_sel: OUT std_logic;
            Selector_sel: OUT std_logic;
            ALU_sel : OUT std_logic;
            OutReg_Ld: OUT std_logic;
            Oe: OUT std_logic;
            Done: OUT std_logic;
            Start, Clk, Rst: IN std_logic); 
     END COMPONENT;

-- do not modify any code above this line
-- add signals needed below. hint: name them something you can keep track of while debugging/testing
-- add your code starting here

-- CONTROLLER OUTPUTS
SIGNAL R_en, W_en, Shifter_sel, Selector_sel, ALU_sel, OutReg_Ld, Oe: std_logic;
SIGNAL R_Addr1, R_Addr2, W_Addr: std_logic_vector(2 DOWNTO 0);

-- REGFILE OUTPUTS
SIGNAL Reg_Data1, Reg_Data2: std_logic_vector(15 DOWNTO 0);

-- COMPUTATIONAL RESULTS
SIGNAL ALU_Out, Shift_Out, Sel_Out, Reg_Out: std_logic_vector(15 DOWNTO 0);

BEGIN
    Ctrl: Controller PORT MAP (Start => Start, Clk => Clk, Rst => Rst, Done => Done,
                               R_en => R_en, R_Addr1 => R_Addr1, R_Addr2 => R_Addr2,
                               W_en => W_en, W_Addr => W_Addr, OutReg_Ld => OutReg_Ld, Oe => Oe,
                               Shifter_sel => Shifter_sel, Selector_sel => Selector_sel, ALU_sel => ALU_sel);
    RF: RegFile PORT MAP (R_Addr1 => R_Addr1, R_Addr2 => R_Addr2, W_Addr => W_Addr,
                          R_en => R_en, W_en => W_en, W_Data => Sel_Out, Clk => Clk, Rst => Rst,
                          Reg_Data1 => Reg_Data1, Reg_Data2 => Reg_Data2);
    ALG: ALU PORT MAP (Sel => ALU_sel, A => Reg_Data1, B => Reg_Data2, ALU_Out => ALU_Out);
    Shift: Shifter PORT MAP (sel => Shifter_sel, I => Reg_Data2, Q => Shift_Out);
    Sel: Selector PORT MAP (sel => Selector_sel, x => Shift_Out, y => ALU_Out, f => Sel_Out);
    OutReg: Reg PORT MAP (Clk => Clk, Rst => Rst, Ld => OutReg_Ld, I => Sel_Out, Q => Reg_Out);
    Buf: ThreeStateBuff PORT MAP (Control_Input => Oe, Data_Input => Reg_Out, Output => Loc);
end Struct;

