package edu.uci.cs142a.crux.backend;
import java.util.*;
import edu.uci.cs142a.crux.midend.ir.core.*;
import edu.uci.cs142a.crux.midend.ir.core.insts.*;

public class CodeGen extends InstVisitor {
    Program p;
    CodePrinter out;
    HashMap<Variable, Integer> variableOffsets = new HashMap<>();
    HashMap<Instruction, String> labels = new HashMap<>();
  
    public CodeGen(Program p) {
        this.p = p;
        out = new CodePrinter("a.s");
    }

    public void genCode() {
        Iterator<AllocateInst> globalIt = p.getGlobals();
        while (globalIt.hasNext()) {
            AllocateInst global = globalIt.next();
            global.accept(this);
        }

        Iterator<Function> functionIt = p.getFunctions();
        while (functionIt.hasNext()) {
            Function f = functionIt.next();
            genCode(f);
        }
        out.close();
    }

    private int labelcount = 1;
    private int stackCount = 0;

    void resetStack() {
        stackCount = 0;
    }

    String getNewLabel() {
        return  "L"+ (labelcount++);
    }

    void genCode(Function f) {
        handleArguments(f);

        boolean hasHadJump = false;
        labels = assignLabels(f);
        Stack<Instruction> needToRevisit = new Stack<>();

        Instruction inst = f.getStart();
        inst.accept(this);
        while (f.getChildren(inst).hasNext() || !needToRevisit.empty()) {
            if (!f.getChildren(inst).hasNext()) {
                out.bufferCode("leave");
                out.bufferCode("ret");
                inst = needToRevisit.pop();
            }
            else {
                Iterator<Instruction> childrenIt = f.getChildren(inst);
                Instruction child = childrenIt.next();
                if (childrenIt.hasNext()) {
                    hasHadJump = true;
                    if (f.isJump(inst, child)) {
                        inst = childrenIt.next();
                        needToRevisit.push(child);
                    } else {
                        inst = child;
                        needToRevisit.push(childrenIt.next());
                    }
                } else
                    inst = child;
            }

            if (labels.containsKey(inst)) {
                if (labels.get(inst).equals("NOPE"))
                    break;
                out.bufferLabel(labels.get(inst) + ":");
                labels.replace(inst, "NOPE");
            }
            inst.accept(this);
        }

        printPrologue(f);
        printBody();
        if (!hasHadJump)
            printEpilogue();
        else
            out.printCode("jmp L2");
        resetStack();
    }

    void printPrologue(Function f) {
        out.printCode(".globl " + f.getName());
        out.printLabel(f.getName() + ":");
        if (stackCount % 2 == 1)
            out.printCode("enter $(8 * " + (stackCount + 1) + "), $0");
        else
            out.printCode("enter $(8 * " + stackCount + "), $0");
    }

    void handleArguments(Function f) {
        for (LocalVar arg : f.getArguments()) {
            variableOffsets.put(arg, (++stackCount)*8);
            switch(stackCount) {
                case 1:
                    out.bufferCode("movq %rdi, -8(%rbp)");
                    break;
                case 2:
                    out.bufferCode("movq %rsi, -16(%rbp)");
                    break;
                case 3:
                    out.bufferCode("movq %rdx, -24(%rbp)");
                    break;
                case 4:
                    out.bufferCode("movq %rcx, -32(%rbp)");
                    break;
                case 5:
                    out.bufferCode("movq %r8, -40(%rbp)");
                    break;
                case 6:
                    out.bufferCode("movq %r9, -48(%rbp)");
                    break;
            }
        }
    }

    void printBody() {
        out.outputBuffer();
    }

    void printEpilogue() {
        out.printCode("leave");
        out.printCode("ret");
    }

    /** Assigns Labels to any Instruction that might be the target of a
     * conditional or unconditional jump. */

    HashMap<Instruction, String> assignLabels(Function f) {
        HashMap<Instruction, String> labelMap = new HashMap<>();
        Stack<Instruction> tovisit= new Stack<>();
        HashSet<Instruction> discovered= new HashSet<>();
        tovisit.push(f.getStart());
        while(!tovisit.isEmpty()) {
          Instruction inst = tovisit.pop();

          for(Iterator<Instruction> childit = f.getChildren(inst); childit.hasNext(); ) {
              Instruction child = childit.next();
              if (discovered.contains(child)) {
                  //Found the node for a second time...need a label for merge points
                  if (!labelMap.containsKey(child)) {
                      labelMap.put(child, getNewLabel());
                  }
              } else {
                  discovered.add(child);
                  tovisit.push(child);
                  //Need a label for jump targets also
                  if (f.isJump(inst, child) && !labelMap.containsKey(child)) {
                      labelMap.put(child, getNewLabel());
                  }
              }
          }
        }        
        return labelMap;
    }

    public void visit(AllocateInst i) {
        IntegerConstant c = (IntegerConstant) i.getNumElement();
        out.printCode(".comm " + i.getAllocatedAddress().getName().substring(1) + ", " + (c.getValue()*8) + ", 8");
    }

    public void visit(AddressAt i) {
        out.bufferCode("/* AddressAt */");
        if (i.getOffset() == null) {
            out.bufferCode("movq " + i.getBase().getName().substring(1) + "@GOTPCREL(%rip), %r11");
        }
        else {
            out.bufferCode("movq -" + variableOffsets.get(i.getOffset()) + "(%rbp), %r11");
            out.bufferCode("movq $8, %r10");
            out.bufferCode("imul %r10, %r11");
            out.bufferCode("movq " + i.getBase().getName().substring(1) + "@GOTPCREL(%rip), %r10");
            out.bufferCode("addq %r10, %r11");
        }
        int offset = (++stackCount) * 8;
        out.bufferCode("movq %r11, -" + offset + "(%rbp)");
        variableOffsets.put(i.getDst(), offset);
    }
    
    public void visit(BinaryOperator i) {
        out.bufferCode("/* BinaryOperator */");
        out.bufferCode("movq -" + variableOffsets.get(i.getLeftOperand()) + "(%rbp), %r10");

        switch (i.getOperator()) {
            case Add:
                out.bufferCode("addq -" + variableOffsets.get(i.getRightOperand()) + "(%rbp), %r10");
                break;
            case Sub:
                out.bufferCode("subq -" + variableOffsets.get(i.getRightOperand()) + "(%rbp), %r10");
                break;
            case Mul:
                out.bufferCode("imulq -" + variableOffsets.get(i.getRightOperand()) + "(%rbp), %r10");
                break;
            case Div:
                break;
        }

        int offset = (++stackCount) * 8;
        out.bufferCode("movq %r10, -" + offset + "(%rbp)");
        variableOffsets.put(i.getDst(), offset);
    }
    
    public void visit(CompareInst i) {
        out.bufferCode("/* CompareInst */");
        out.bufferCode("movq -" + variableOffsets.get(i.getLeftOperand()) + "(%rbp), %r10");
        out.bufferCode("movq -" + variableOffsets.get(i.getRightOperand()) + "(%rbp), %r11");
        out.bufferCode("cmp %r11, %r10");
        out.bufferCode("movq $0, %r11");
        out.bufferCode("movq $1, %r10");

        switch (i.getPredicate()) {
            case GE:
                out.bufferCode("cmovge %r10, %r11");
                break;
            case GT:
                out.bufferCode("cmovg %r10, %r11");
                break;
            case LE:
                out.bufferCode("cmovle %r10, %r11");
                break;
            case LT:
                out.bufferCode("cmovl %r10, %r11");
                break;
            case EQ:
                out.bufferCode("cmove %r10, %r11");
                break;
            case NE:
                out.bufferCode("cmovne %r10, %r11");
                break;
        }

        int offset = (++stackCount) * 8;
        out.bufferCode("movq %r11, -" + offset + "(%rbp)");
        variableOffsets.put(i.getDst(), offset);
    }
    
    public void visit(CopyInst i) {
        out.bufferCode("/* CopyInst */");
        String s = "movq ";

        Value srcValue = i.getSrcValue();
        if (srcValue instanceof Variable) {
            Variable srcVar = (Variable) srcValue;
            s += "-" + variableOffsets.get(srcVar).toString() + "(%rbp)";
        }
        else if (srcValue instanceof IntegerConstant) {
            s += "$" + ((IntegerConstant) srcValue).getValue();
        }
        else if (srcValue instanceof BooleanConstant) {
            if (((BooleanConstant) srcValue).getValue())
                s += "$1";
            else
                s += "$0";
        }
        s += ", %r10";
        out.bufferCode(s);

        int offset = (++stackCount) * 8;
        s = "movq %r10, -" + offset + "(%rbp)";
        variableOffsets.put(i.getDstVar(), offset);
        out.bufferCode(s);
    }
    
    public void visit(JumpInst i) {
        out.bufferCode("/* JumpInst */");
        out.bufferCode("movq -" + variableOffsets.get(i.getPredicate()) + "(%rbp), %r10");
        out.bufferCode("cmp $1, %r10");
        out.bufferCode("je L1");
    }
      
    public void visit(LoadInst i) {
        out.bufferCode("/* LoadInst */");
        out.bufferCode("movq -" + variableOffsets.get(i.getSrcAddress()) + "(%rbp), %r10");
        out.bufferCode("movq 0(%r10), %r10");
        int offset = (++stackCount) * 8;
        out.bufferCode("movq %r10, -" + offset + "(%rbp)");
        variableOffsets.put(i.getDst(), offset);
    }
    
    public void visit(NopInst i) {
        out.bufferCode("/* Nop */");
    }
    
    public void visit(StoreInst i) {
        out.bufferCode("/* StoreInst */");
        out.bufferCode("movq -" + variableOffsets.get(i.getSrcValue()) + "(%rbp), %r10");
        out.bufferCode("movq -" + variableOffsets.get(i.getDestAddress()) + "(%rbp), %r11");
        out.bufferCode("movq %r10, 0(%r11)");
    }
    
    public void visit(ReturnInst i) {
        out.bufferCode("/* ReturnInst */");
        out.bufferCode("movq -" + variableOffsets.get(i.getReturnValue()) + "(%rbp), %rax");
    }

    public void visit(CallInst i) {
        out.bufferCode("/* CallInst */");
        List<Value> params = i.getParams();
        if (params.size() != 0) {
            int beginning_offset = stackCount - params.size() + 1;
            int argCount = 0;
            for (int offset = beginning_offset; offset <= stackCount; offset++) {
                argCount++;
                switch(argCount) {
                    case 1:
                        out.bufferCode("movq -" + (offset*8) + "(%rbp), %rdi");
                        break;
                    case 2:
                        out.bufferCode("movq -" + (offset*8) + "(%rbp), %rsi");
                        break;
                    case 3:
                        out.bufferCode("movq -" + (offset*8) + "(%rbp), %rdx");
                        break;
                    case 4:
                        out.bufferCode("movq -" + (offset*8) + "(%rbp), %rcx");
                        break;
                    case 5:
                        out.bufferCode("movq -" + (offset*8) + "(%rbp), %r8");
                        break;
                    case 6:
                        out.bufferCode("movq -" + (offset*8) + "(%rbp), %r9");
                        break;
                }
            }
        }

        out.bufferCode("call " + i.getCallee().getName().substring(1));
        if (i.getDst() != null) {
            int offset = (++stackCount) * 8;
            out.bufferCode("movq %rax, -" + offset + "(%rbp)");
            variableOffsets.put(i.getDst(), offset);
        }
    }
    
    public void visit(UnaryNotInst i) {

    } 
}
