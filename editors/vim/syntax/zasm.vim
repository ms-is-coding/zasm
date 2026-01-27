if exists("b:current_syntax")
  finish
endif

" --- Comments (defined early to match contained TODOs) ---
syn keyword zasmTodo    TODO FIXME XXX NOTE contained
syn match   zasmComment "//.*$" contains=zasmTodo,@Spell
syn region  zasmComment start="/\*" end="\*/" contains=zasmTodo,@Spell

" --- Directions & Types ---
" Assembler directives and data definitions
syn keyword zasmDirective section global extern entry
syn keyword zasmType      db dw dd dq dt
syn keyword zasmType      byte word dword qword ptr

" --- Instructions (Keywords) ---
" Control Flow
syn keyword zasmInstruction ret call jmp je jne jg jge jl jle jz jnz syscall
" Arithmetic
syn keyword zasmInstruction add sub mul div inc dec neg cmp
" Data Movement
syn keyword zasmInstruction mov lea push pop pushstr xchg
" Logic
syn keyword zasmInstruction and or xor not test shl shr sal sar

" --- Registers ---
" 64-bit
syn keyword zasmRegister rax rcx rdx rbx rsp rbp rsi rdi rip
syn keyword zasmRegister r8 r9 r10 r11 r12 r13 r14 r15
" 32-bit
syn keyword zasmRegister eax ecx edx ebx esp ebp esi edi
syn keyword zasmRegister r8d r9d r10d r11d r12d r13d r14d r15d
" 16-bit
syn keyword zasmRegister ax cx dx bx sp bp si di
syn keyword zasmRegister r8w r9w r10w r11w r12w r13w r14w r15w
" 8-bit
syn keyword zasmRegister al cl dl bl spl bpl sil dil
syn keyword zasmRegister ah ch dh bh sph bph sih dih
syn keyword zasmRegister r8b r9b r10b r11b r12b r13b r14b r15b

" --- Numbers ---
" Hexadecimal (0xFF)
syn match zasmNumber /\<0x[0-9a-fA-F]\+\>/
" Binary (0b1010)
syn match zasmNumber /\<0b[01]\+\>/
" Decimal & Floats
syn match zasmNumber /\<[0-9]\+\(\.[0-9]\+\)\?\>/

" --- Strings ---
syn region zasmString start=/"/ end=/"/ contains=@Spell
syn region zasmString start=/'/ end=/'/ contains=@Spell

" --- Labels & Functions ---
" Label definition (word followed by :)
syn match zasmLabel /\<[A-Za-z_.?][A-Za-z0-9_.?]*\>\ze:/
" Function call/definition (word followed by parenthesis)
syn match zasmFunction /\<[A-Za-z_][A-Za-z0-9_]*\>\ze\s*(/

" --- Identifiers ---
" Catch-all for variables/constants that aren't keywords
syn match zasmIdentifier /\<[A-Za-z_][A-Za-z0-9_]*\>\ze[^:( ]/
" And a version for the end of a line
syn match zasmIdentifier /\<[A-Za-z_][A-Za-z0-9_]*\>$/

" --- Operators ---
syn match zasmOperator /==\|!=\|<=\|>=\|=\|+\|-\|\*\|%\|&\|<\|>\|\^\||\|~/
" Only match / if it isn't followed by another / (which would be a comment)
syn match zasmOperator /\/\/\@!/
syn match zasmArrow    /=>/

" --- Delimiters ---
syn match zasmDelimiter /[(){}\[\],.;:]/

" --- Highlight Links ---
hi def link zasmTodo        Todo


hi def link zasmDirective   PreProc
hi def link zasmType        Type
hi def link zasmInstruction Statement

hi def link zasmRegister    StorageClass
hi def link zasmLabel       Label
hi def link zasmFunction    Function

hi def link zasmNumber      Number
hi def link zasmString      String
hi def link zasmIdentifier  Identifier

hi def link zasmOperator    Operator
hi def link zasmArrow       Operator
hi def link zasmDelimiter   Delimiter

hi def link zasmComment     Comment

let b:current_syntax = "zasm"
