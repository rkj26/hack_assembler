// TortureTest.asm
// Tests all facets of the Hack Assembler

   @123          // 1. Literal A-instruction with whitespace
D=A              // 2. Simple C-instruction (Dest=Comp)

(START)          // 3. Label definition (Pseudo-command)

   @R0           // 4. Predefined Symbol (R0=0)
   D=M           // 5. Memory access
   @counter      // 6. User Variable (should be mapped to RAM[16])
   M=D+M         // 7. Arithmetic on Memory

   @START        // 8. Forward reference (Label usage)
   0;JMP         // 9. Unconditional Jump (Comp;Jump)

   D;JGT         // 10. Jump only (Comp;Jump)

   AMD=D+1;JLE   // 11. The "Kitchen Sink" (Dest=Comp;Jump)
                 // Note: This tests if you parse Dest, Comp, AND Jump together.

   @KBD          // 12. High address Predefined symbol (24576)
   D=A