# Inline ASM examples

Generally the inline term is used to instruct the compiler to insert the code
of a function into the code of its caller at the point where the actual call is
made. Such functions are called "inline functions". The benefit of inlining is
that it reduces function-call overhead.

Now, it's easier to guess about inline assembly. It is just a set of assembly
instructions written as inline functions. Inline assembly is used for speed,
and you ought to believe me that it is frequently used in system programming.

We can mix the assembly statements within C/C++ programs using keyword asm.
Inline assembly is important because of its ability to operate and make its
output visible on C/C++ variables.



## How to build these examples

``` make ```

How to assign a cpu to run it : 

``` ./add & taskset -cp 0 <PID> ```


