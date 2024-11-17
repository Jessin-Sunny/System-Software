ASSUME CS: CODE, DS: DATA
DATA SEGMENT
    MSG1 DB 10,13,"Enter a String : $"
    MSG2 DB 10,13,"Palindrome$"
    MSG3 DB 10,13,"Not Palindrome$"
    STRING DB 20 DUP('$')
DATA ENDS
PRTMSG MACRO MSG
    LEA DX,MSG
    MOV AH,09H
    INT 21H
ENDM
GETDCM MACRO
    MOV AH,01H
    INT 21H
ENDM
CODE SEGMENT
    START:  MOV AX,DATA
            MOV DS,AX
            PRTMSG MSG1
            LEA SI,STRING
            LEA DI,STRING
            MOV CL,00H
    STRIN:  GETDCM
            CMP AL,0DH
            JZ ENDIN
            MOV [SI],AL
            INC SI
            INC CL
            JMP STRIN
    ENDIN:  MOV [SI],'$'
            DEC SI
    LOOPSP: MOV AL,[SI]
            MOV BL,[DI]
            CMP AL,BL
            JNZ NP
            INC DI
            DEC SI
            LOOPNZ LOOPSP
            PRTMSG MSG2
            JMP ENDPR
    NP:     PRTMSG MSG3
    ENDPR:  MOV AH,4CH
            INT 21H
CODE ENDS
END START