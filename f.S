.intel_syntax noprefix
.text
.global main
init:
push rbp
mov rbp, rsp
sub rsp, 8
mov [rbp - 8], rdi
mov r10, 0
push r10
lea r10, [rbp - 8]
push r10
pop r10
mov r10, [r10]
push r10
pop r10
add r10, 0
push r10
pop r10
pop r11
mov [r10], r11
push r11
pop r10
mov r10, 1
push r10
lea r10, [rbp - 8]
push r10
pop r10
mov r10, [r10]
push r10
pop r10
add r10, 16
push r10
pop r10
pop r11
mov [r10], r11
push r11
pop r10
mov r10, [rip + realloc@GOTPCREL]
push r10
mov r10, 0
push r10
mov r10, 8
push r10
pop rsi
pop rdi
pop rax
sub rsp, 8
call rax
add rsp, 8
push rax
lea r10, [rbp - 8]
push r10
pop r10
mov r10, [r10]
push r10
pop r10
add r10, 8
push r10
pop r10
pop r11
mov [r10], r11
push r11
pop r10
L0:
lea rsp, [rbp - 8]
mov r10, 1
push r10
pop r10
cmp r10, 0
jz L1
lea r10, [rbp - 8]
push r10
pop r10
mov r10, [r10]
push r10
pop r10
add r10, 8
push r10
pop r10
mov r10, [r10]
cmp r10, 0
jz L2
jmp L1
lea rsp, [rbp - 8]
jmp L3
L2:
L3:
mov r10, [rip + realloc@GOTPCREL]
push r10
mov r10, 0
push r10
mov r10, 8
push r10
pop rsi
pop rdi
pop rax
sub rsp, 8
call rax
add rsp, 8
push rax
lea r10, [rbp - 8]
push r10
pop r10
mov r10, [r10]
push r10
pop r10
add r10, 8
push r10
pop r10
pop r11
mov [r10], r11
push r11
pop r10
lea rsp, [rbp - 8]
jmp L0
L1:
lea rsp, [rbp - 8]
mov r10, 0
push r10
pop rax
mov rsp, rbp
pop rbp
ret
lea rsp, [rbp - 8]
mov rsp, rbp
pop rbp
ret
push:
push rbp
mov rbp, rsp
sub rsp, 8
mov [rbp - 8], rdi
sub rsp, 8
mov [rbp - 16], rsi
lea r10, [rbp - 8]
push r10
pop r10
mov r10, [r10]
push r10
pop r10
add r10, 0
push r10
lea r10, [rbp - 8]
push r10
pop r10
mov r10, [r10]
push r10
pop r10
add r10, 16
push r10
pop r11
pop r10
mov r10, [r10]
mov r11, [r11]
cmp r10, r11
sete r10b
movzx r10, r10b
push r10
pop r10
cmp r10, 0
jz L4
sub rsp, 8
lea r10, [rbp - 8]
push r10
pop r10
mov r10, [r10]
push r10
pop r10
add r10, 16
push r10
mov r10, 2
push r10
xor rdx, rdx
pop r10
pop rax
mov rax, [rax]
imul r10
mov r10, rax
push r10
lea r10, [rbp - 8]
push r10
pop r10
mov r10, [r10]
push r10
pop r10
add r10, 16
push r10
pop r10
pop r11
mov [r10], r11
push r11
pop r10
mov r10, [rip + realloc@GOTPCREL]
push r10
lea r10, [rbp - 8]
push r10
pop r10
mov r10, [r10]
push r10
pop r10
add r10, 8
push r10
lea r10, [rbp - 8]
push r10
pop r10
mov r10, [r10]
push r10
pop r10
add r10, 16
push r10
mov r10, 8
push r10
xor rdx, rdx
pop r10
pop rax
mov rax, [rax]
imul r10
mov r10, rax
push r10
pop rsi
pop rdi
mov rdi, [rdi]
pop rax
sub rsp, 8
call rax
add rsp, 8
push rax
lea r10, [rbp - 24]
push r10
pop r10
pop r11
mov [r10], r11
push r11
pop r10
L6:
lea rsp, [rbp - 24]
mov r10, 1
push r10
pop r10
cmp r10, 0
jz L7
lea r10, [rbp - 24]
push r10
pop r10
mov r10, [r10]
cmp r10, 0
jz L8
jmp L7
lea rsp, [rbp - 24]
jmp L9
L8:
L9:
mov r10, [rip + realloc@GOTPCREL]
push r10
lea r10, [rbp - 8]
push r10
pop r10
mov r10, [r10]
push r10
pop r10
add r10, 8
push r10
lea r10, [rbp - 8]
push r10
pop r10
mov r10, [r10]
push r10
pop r10
add r10, 16
push r10
mov r10, 8
push r10
xor rdx, rdx
pop r10
pop rax
mov rax, [rax]
imul r10
mov r10, rax
push r10
pop rsi
pop rdi
mov rdi, [rdi]
pop rax
sub rsp, 8
call rax
add rsp, 8
push rax
lea r10, [rbp - 24]
push r10
pop r10
pop r11
mov [r10], r11
push r11
pop r10
lea rsp, [rbp - 24]
jmp L6
L7:
lea rsp, [rbp - 24]
lea r10, [rbp - 24]
push r10
lea r10, [rbp - 8]
push r10
pop r10
mov r10, [r10]
push r10
pop r10
add r10, 8
push r10
pop r10
pop r11
mov r11, [r11]
mov [r10], r11
push r11
pop r10
lea rsp, [rbp - 16]
jmp L5
L4:
L5:
lea r10, [rbp - 16]
push r10
lea r10, [rbp - 8]
push r10
pop r10
mov r10, [r10]
push r10
pop r10
add r10, 8
push r10
pop r10
mov r10, [r10]
push r10
lea r10, [rbp - 8]
push r10
pop r10
mov r10, [r10]
push r10
pop r10
add r10, 0
push r10
pop r11
mov r11, [r11]
imul r11, 8
pop r10
add r10, r11
push r10
pop r10
pop r11
mov r11, [r11]
mov [r10], r11
push r11
pop r10
lea r10, [rbp - 8]
push r10
pop r10
mov r10, [r10]
push r10
pop r10
add r10, 0
push r10
mov r10, 1
push r10
pop r11
pop r10
mov r10, [r10]
add r10, r11
push r10
lea r10, [rbp - 8]
push r10
pop r10
mov r10, [r10]
push r10
pop r10
add r10, 0
push r10
pop r10
pop r11
mov [r10], r11
push r11
pop rax
mov rsp, rbp
pop rbp
ret
lea rsp, [rbp - 16]
mov rsp, rbp
pop rbp
ret
pop:
push rbp
mov rbp, rsp
sub rsp, 8
mov [rbp - 8], rdi
lea r10, [rbp - 8]
push r10
pop r10
mov r10, [r10]
push r10
pop r10
add r10, 0
push r10
mov r10, 1
push r10
pop r11
pop r10
mov r10, [r10]
sub r10, r11
push r10
lea r10, [rbp - 8]
push r10
pop r10
mov r10, [r10]
push r10
pop r10
add r10, 0
push r10
pop r10
pop r11
mov [r10], r11
push r11
pop rax
mov rsp, rbp
pop rbp
ret
lea rsp, [rbp - 8]
mov rsp, rbp
pop rbp
ret
binary_search:
push rbp
mov rbp, rsp
sub rsp, 8
mov [rbp - 8], rdi
sub rsp, 8
mov [rbp - 16], rsi
sub rsp, 8
sub rsp, 8
sub rsp, 8
mov r10, 0
push r10
mov r10, 1
push r10
pop r11
pop r10
sub r10, r11
push r10
lea r10, [rbp - 24]
push r10
pop r10
pop r11
mov [r10], r11
push r11
pop r10
lea r10, [rbp - 8]
push r10
pop r10
mov r10, [r10]
push r10
pop r10
add r10, 0
push r10
lea r10, [rbp - 32]
push r10
pop r10
pop r11
mov r11, [r11]
mov [r10], r11
push r11
pop r10
L10:
lea rsp, [rbp - 40]
lea r10, [rbp - 32]
push r10
lea r10, [rbp - 24]
push r10
pop r11
pop r10
mov r10, [r10]
mov r11, [r11]
sub r10, r11
push r10
mov r10, 1
push r10
pop r11
pop r10
cmp r10, r11
setg r10b
movzx r10, r10b
push r10
pop r10
cmp r10, 0
jz L11
lea r10, [rbp - 24]
push r10
lea r10, [rbp - 32]
push r10
pop r11
pop r10
mov r10, [r10]
mov r11, [r11]
add r10, r11
push r10
mov r10, 2
push r10
xor rdx, rdx
pop r10
pop rax
idiv r10
mov r10, rax
push r10
lea r10, [rbp - 40]
push r10
pop r10
pop r11
mov [r10], r11
push r11
pop r10
lea r10, [rbp - 8]
push r10
pop r10
mov r10, [r10]
push r10
pop r10
add r10, 8
push r10
pop r10
mov r10, [r10]
push r10
lea r10, [rbp - 40]
push r10
pop r11
mov r11, [r11]
imul r11, 8
pop r10
add r10, r11
push r10
lea r10, [rbp - 16]
push r10
pop r11
pop r10
mov r10, [r10]
mov r11, [r11]
cmp r10, r11
setge r10b
movzx r10, r10b
push r10
pop r10
cmp r10, 0
jz L12
lea r10, [rbp - 40]
push r10
lea r10, [rbp - 32]
push r10
pop r10
pop r11
mov r11, [r11]
mov [r10], r11
push r11
pop r10
lea rsp, [rbp - 40]
jmp L13
L12:
lea r10, [rbp - 40]
push r10
lea r10, [rbp - 24]
push r10
pop r10
pop r11
mov r11, [r11]
mov [r10], r11
push r11
pop r10
lea rsp, [rbp - 40]
jmp L15
L14:
L15:
L13:
lea rsp, [rbp - 40]
jmp L10
L11:
lea rsp, [rbp - 40]
lea r10, [rbp - 32]
push r10
pop rax
mov rax, [rax]
mov rsp, rbp
pop rbp
ret
lea rsp, [rbp - 16]
mov rsp, rbp
pop rbp
ret
dfs:
push rbp
mov rbp, rsp
sub rsp, 8
mov [rbp - 8], rdi
sub rsp, 8
mov [rbp - 16], rsi
sub rsp, 8
mov [rbp - 24], rdx
sub rsp, 8
mov [rbp - 32], rcx
sub rsp, 8
mov [rbp - 40], r8
sub rsp, 8
mov [rbp - 48], r9
sub rsp, 16
sub rsp, 8
mov r10, [rip + binary_search@GOTPCREL]
push r10
lea r10, [rbp - 32]
push r10
lea r10, [rbp - 24]
push r10
pop r10
mov r10, [r10]
push r10
lea r10, [rbp - 8]
push r10
pop r11
mov r11, [r11]
imul r11, 8
pop r10
add r10, r11
push r10
pop rsi
mov rsi, [rsi]
pop rdi
mov rdi, [rdi]
pop rax
sub rsp, 8
call rax
add rsp, 8
push rax
lea r10, [rbp - 64]
push r10
pop r10
add r10, 0
push r10
pop r10
pop r11
mov [r10], r11
push r11
pop r10
lea r10, [rbp - 64]
push r10
pop r10
add r10, 0
push r10
lea r10, [rbp - 32]
push r10
pop r10
mov r10, [r10]
push r10
pop r10
add r10, 0
push r10
pop r11
pop r10
mov r10, [r10]
mov r11, [r11]
cmp r10, r11
sete r10b
movzx r10, r10b
push r10
pop r10
cmp r10, 0
jz L16
mov r10, [rip + push@GOTPCREL]
push r10
lea r10, [rbp - 32]
push r10
mov r10, 0
push r10
pop rsi
pop rdi
mov rdi, [rdi]
pop rax
sub rsp, 8
call rax
add rsp, 8
push rax
pop r10
lea r10, [rbp - 40]
push r10
mov r10, 1
push r10
pop r11
pop r10
mov r10, [r10]
add r10, r11
push r10
lea r10, [rbp - 48]
push r10
pop r10
mov r10, [r10]
push r10
lea r10, [rbp - 8]
push r10
pop r11
mov r11, [r11]
imul r11, 8
pop r10
add r10, r11
push r10
pop r10
pop r11
mov [r10], r11
push r11
pop r10
lea rsp, [rbp - 72]
jmp L17
L16:
lea r10, [rbp - 40]
push r10
lea r10, [rbp - 48]
push r10
pop r10
mov r10, [r10]
push r10
lea r10, [rbp - 8]
push r10
pop r11
mov r11, [r11]
imul r11, 8
pop r10
add r10, r11
push r10
pop r10
pop r11
mov r11, [r11]
mov [r10], r11
push r11
pop r10
lea rsp, [rbp - 72]
jmp L19
L18:
L19:
L17:
lea r10, [rbp - 32]
push r10
pop r10
mov r10, [r10]
push r10
pop r10
add r10, 8
push r10
pop r10
mov r10, [r10]
push r10
lea r10, [rbp - 64]
push r10
pop r10
add r10, 0
push r10
pop r11
mov r11, [r11]
imul r11, 8
pop r10
add r10, r11
push r10
lea r10, [rbp - 64]
push r10
pop r10
add r10, 8
push r10
pop r10
pop r11
mov r11, [r11]
mov [r10], r11
push r11
pop r10
lea r10, [rbp - 24]
push r10
pop r10
mov r10, [r10]
push r10
lea r10, [rbp - 8]
push r10
pop r11
mov r11, [r11]
imul r11, 8
pop r10
add r10, r11
push r10
lea r10, [rbp - 32]
push r10
pop r10
mov r10, [r10]
push r10
pop r10
add r10, 8
push r10
pop r10
mov r10, [r10]
push r10
lea r10, [rbp - 64]
push r10
pop r10
add r10, 0
push r10
pop r11
mov r11, [r11]
imul r11, 8
pop r10
add r10, r11
push r10
pop r10
pop r11
mov r11, [r11]
mov [r10], r11
push r11
pop r10
mov r10, 0
push r10
lea r10, [rbp - 72]
push r10
pop r10
pop r11
mov [r10], r11
push r11
pop r10
L20:
lea rsp, [rbp - 72]
lea r10, [rbp - 72]
push r10
mov r10, [rip + gp@GOTPCREL]
push r10
pop r10
mov r10, [r10]
push r10
lea r10, [rbp - 8]
push r10
pop r11
mov r11, [r11]
imul r11, 24
pop r10
add r10, r11
push r10
pop r10
add r10, 0
push r10
pop r11
pop r10
mov r10, [r10]
mov r11, [r11]
cmp r10, r11
setl r10b
movzx r10, r10b
push r10
pop r10
cmp r10, 0
jz L21
mov r10, [rip + gp@GOTPCREL]
push r10
pop r10
mov r10, [r10]
push r10
lea r10, [rbp - 8]
push r10
pop r11
mov r11, [r11]
imul r11, 24
pop r10
add r10, r11
push r10
pop r10
add r10, 8
push r10
pop r10
mov r10, [r10]
push r10
lea r10, [rbp - 72]
push r10
pop r11
mov r11, [r11]
imul r11, 8
pop r10
add r10, r11
push r10
lea r10, [rbp - 16]
push r10
pop r11
pop r10
mov r10, [r10]
mov r11, [r11]
cmp r10, r11
sete r10b
movzx r10, r10b
push r10
pop r10
cmp r10, 0
jz L22
lea r10, [rbp - 72]
push r10
mov r10, 1
push r10
pop r11
pop r10
mov r10, [r10]
add r10, r11
push r10
lea r10, [rbp - 72]
push r10
pop r10
pop r11
mov [r10], r11
push r11
pop r10
jmp L20
lea rsp, [rbp - 72]
jmp L23
L22:
L23:
mov r10, [rip + dfs@GOTPCREL]
push r10
mov r10, [rip + gp@GOTPCREL]
push r10
pop r10
mov r10, [r10]
push r10
lea r10, [rbp - 8]
push r10
pop r11
mov r11, [r11]
imul r11, 24
pop r10
add r10, r11
push r10
pop r10
add r10, 8
push r10
pop r10
mov r10, [r10]
push r10
lea r10, [rbp - 72]
push r10
pop r11
mov r11, [r11]
imul r11, 8
pop r10
add r10, r11
push r10
lea r10, [rbp - 8]
push r10
lea r10, [rbp - 24]
push r10
lea r10, [rbp - 32]
push r10
lea r10, [rbp - 48]
push r10
pop r10
mov r10, [r10]
push r10
lea r10, [rbp - 8]
push r10
pop r11
mov r11, [r11]
imul r11, 8
pop r10
add r10, r11
push r10
lea r10, [rbp - 48]
push r10
pop r9
mov r9, [r9]
pop r8
mov r8, [r8]
pop rcx
mov rcx, [rcx]
pop rdx
mov rdx, [rdx]
pop rsi
mov rsi, [rsi]
pop rdi
mov rdi, [rdi]
pop rax
sub rsp, 8
call rax
add rsp, 8
push rax
pop r10
lea r10, [rbp - 72]
push r10
mov r10, 1
push r10
pop r11
pop r10
mov r10, [r10]
add r10, r11
push r10
lea r10, [rbp - 72]
push r10
pop r10
pop r11
mov [r10], r11
push r11
pop r10
lea rsp, [rbp - 72]
jmp L20
L21:
lea rsp, [rbp - 72]
lea r10, [rbp - 64]
push r10
pop r10
add r10, 8
push r10
mov r10, 0
push r10
pop r11
pop r10
mov r10, [r10]
cmp r10, r11
setg r10b
movzx r10, r10b
push r10
pop r10
cmp r10, 0
jz L24
lea r10, [rbp - 64]
push r10
pop r10
add r10, 8
push r10
lea r10, [rbp - 32]
push r10
pop r10
mov r10, [r10]
push r10
pop r10
add r10, 8
push r10
pop r10
mov r10, [r10]
push r10
lea r10, [rbp - 64]
push r10
pop r10
add r10, 0
push r10
pop r11
mov r11, [r11]
imul r11, 8
pop r10
add r10, r11
push r10
pop r10
pop r11
mov r11, [r11]
mov [r10], r11
push r11
pop r10
lea rsp, [rbp - 72]
jmp L25
L24:
mov r10, [rip + pop@GOTPCREL]
push r10
lea r10, [rbp - 32]
push r10
pop rdi
mov rdi, [rdi]
pop rax
sub rsp, 8
call rax
add rsp, 8
push rax
pop r10
lea rsp, [rbp - 72]
jmp L27
L26:
L27:
L25:
mov r10, 0
push r10
pop rax
mov rsp, rbp
pop rbp
ret
lea rsp, [rbp - 48]
mov rsp, rbp
pop rbp
ret
main:
push rbp
mov rbp, rsp
sub rsp, 4800000
sub rsp, 8
sub rsp, 8
sub rsp, 1600000
sub rsp, 24
sub rsp, 1600000
lea r10, [rbp - 4800000]
push r10
mov r10, [rip + gp@GOTPCREL]
push r10
pop r10
pop r11
mov [r10], r11
push r11
pop r10
mov r10, [rip + init@GOTPCREL]
push r10
lea r10, [rbp - 6400040]
push r10
pop rdi
pop rax
sub rsp, 8
call rax
add rsp, 8
push rax
pop r10
mov r10, [rip + scanf@GOTPCREL]
push r10
lea r10, [rip + L28]
push r10
lea r10, [rbp - 4800008]
push r10
pop rsi
pop rdi
pop rax
sub rsp, 8
call rax
add rsp, 8
push rax
pop r10
mov r10, 0
push r10
lea r10, [rbp - 4800016]
push r10
pop r10
pop r11
mov [r10], r11
push r11
pop r10
L29:
lea rsp, [rbp - 8000040]
lea r10, [rbp - 4800016]
push r10
lea r10, [rbp - 4800008]
push r10
pop r11
pop r10
mov r10, [r10]
mov r11, [r11]
cmp r10, r11
setl r10b
movzx r10, r10b
push r10
pop r10
cmp r10, 0
jz L30
mov r10, [rip + init@GOTPCREL]
push r10
lea r10, [rbp - 4800000]
push r10
lea r10, [rbp - 4800016]
push r10
pop r11
mov r11, [r11]
imul r11, 24
pop r10
add r10, r11
push r10
pop rdi
pop rax
sub rsp, 8
call rax
add rsp, 8
push rax
pop r10
mov r10, [rip + scanf@GOTPCREL]
push r10
lea r10, [rip + L31]
push r10
lea r10, [rbp - 6400016]
push r10
lea r10, [rbp - 4800016]
push r10
pop r11
mov r11, [r11]
imul r11, 8
pop r10
add r10, r11
push r10
pop rsi
pop rdi
pop rax
sub rsp, 8
call rax
add rsp, 8
push rax
pop r10
lea r10, [rbp - 4800016]
push r10
mov r10, 1
push r10
pop r11
pop r10
mov r10, [r10]
add r10, r11
push r10
lea r10, [rbp - 4800016]
push r10
pop r10
pop r11
mov [r10], r11
push r11
pop r10
lea rsp, [rbp - 8000040]
jmp L29
L30:
lea rsp, [rbp - 8000040]
mov r10, 0
push r10
lea r10, [rbp - 4800016]
push r10
pop r10
pop r11
mov [r10], r11
push r11
pop r10
L32:
lea rsp, [rbp - 8000040]
lea r10, [rbp - 4800016]
push r10
lea r10, [rbp - 4800008]
push r10
mov r10, 1
push r10
pop r11
pop r10
mov r10, [r10]
sub r10, r11
push r10
pop r11
pop r10
mov r10, [r10]
cmp r10, r11
setl r10b
movzx r10, r10b
push r10
pop r10
cmp r10, 0
jz L33
sub rsp, 8
sub rsp, 8
mov r10, [rip + scanf@GOTPCREL]
push r10
lea r10, [rip + L34]
push r10
lea r10, [rbp - 8000048]
push r10
lea r10, [rbp - 8000056]
push r10
pop rdx
pop rsi
pop rdi
pop rax
sub rsp, 8
call rax
add rsp, 8
push rax
pop r10
mov r10, [rip + push@GOTPCREL]
push r10
lea r10, [rbp - 4800000]
push r10
lea r10, [rbp - 8000048]
push r10
mov r10, 1
push r10
pop r11
pop r10
mov r10, [r10]
sub r10, r11
push r10
pop r11
imul r11, 24
pop r10
add r10, r11
push r10
lea r10, [rbp - 8000056]
push r10
mov r10, 1
push r10
pop r11
pop r10
mov r10, [r10]
sub r10, r11
push r10
pop rsi
pop rdi
pop rax
sub rsp, 8
call rax
add rsp, 8
push rax
pop r10
mov r10, [rip + push@GOTPCREL]
push r10
lea r10, [rbp - 4800000]
push r10
lea r10, [rbp - 8000056]
push r10
mov r10, 1
push r10
pop r11
pop r10
mov r10, [r10]
sub r10, r11
push r10
pop r11
imul r11, 24
pop r10
add r10, r11
push r10
lea r10, [rbp - 8000048]
push r10
mov r10, 1
push r10
pop r11
pop r10
mov r10, [r10]
sub r10, r11
push r10
pop rsi
pop rdi
pop rax
sub rsp, 8
call rax
add rsp, 8
push rax
pop r10
lea r10, [rbp - 4800016]
push r10
mov r10, 1
push r10
pop r11
pop r10
mov r10, [r10]
add r10, r11
push r10
lea r10, [rbp - 4800016]
push r10
pop r10
pop r11
mov [r10], r11
push r11
pop r10
lea rsp, [rbp - 8000040]
jmp L32
L33:
lea rsp, [rbp - 8000040]
mov r10, [rip + dfs@GOTPCREL]
push r10
mov r10, 0
push r10
mov r10, 0
push r10
lea r10, [rbp - 6400016]
push r10
lea r10, [rbp - 6400040]
push r10
mov r10, 0
push r10
lea r10, [rbp - 8000040]
push r10
pop r9
pop r8
pop rcx
pop rdx
pop rsi
pop rdi
pop rax
sub rsp, 8
call rax
add rsp, 8
push rax
pop r10
mov r10, [rip + free@GOTPCREL]
push r10
lea r10, [rbp - 6400040]
push r10
pop r10
add r10, 8
push r10
pop rdi
mov rdi, [rdi]
pop rax
sub rsp, 8
call rax
add rsp, 8
push rax
pop r10
mov r10, 0
push r10
lea r10, [rbp - 4800016]
push r10
pop r10
pop r11
mov [r10], r11
push r11
pop r10
L35:
lea rsp, [rbp - 8000040]
lea r10, [rbp - 4800016]
push r10
lea r10, [rbp - 4800008]
push r10
pop r11
pop r10
mov r10, [r10]
mov r11, [r11]
cmp r10, r11
setl r10b
movzx r10, r10b
push r10
pop r10
cmp r10, 0
jz L36
mov r10, [rip + free@GOTPCREL]
push r10
lea r10, [rbp - 4800000]
push r10
lea r10, [rbp - 4800016]
push r10
pop r11
mov r11, [r11]
imul r11, 24
pop r10
add r10, r11
push r10
pop r10
add r10, 8
push r10
pop rdi
mov rdi, [rdi]
pop rax
sub rsp, 8
call rax
add rsp, 8
push rax
pop r10
mov r10, [rip + printf@GOTPCREL]
push r10
lea r10, [rip + L37]
push r10
lea r10, [rbp - 8000040]
push r10
lea r10, [rbp - 4800016]
push r10
pop r11
mov r11, [r11]
imul r11, 8
pop r10
add r10, r11
push r10
pop rsi
mov rsi, [rsi]
pop rdi
pop rax
sub rsp, 8
call rax
add rsp, 8
push rax
pop r10
lea r10, [rbp - 4800016]
push r10
mov r10, 1
push r10
pop r11
pop r10
mov r10, [r10]
add r10, r11
push r10
lea r10, [rbp - 4800016]
push r10
pop r10
pop r11
mov [r10], r11
push r11
pop r10
lea rsp, [rbp - 8000040]
jmp L35
L36:
lea rsp, [rbp - 8000040]
mov r10, 0
push r10
pop rax
mov rsp, rbp
pop rbp
ret
lea rsp, [rbp - 0]
mov rsp, rbp
pop rbp
ret
.data
.align 8
L28: .asciz "%lld*c"
.align 8
L31: .asciz "%lld%*c"
.align 8
L34: .asciz "%lld %lld%*c"
.align 8
L37: .asciz "%lld\n"
.align 8
gp:
.byte 0, 0, 0, 0, 0, 0, 0, 0
