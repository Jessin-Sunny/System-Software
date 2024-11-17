ASSUME CS: CODE, DS: DATA
DATA SEGMENT
    MSG1 DB 10,13,"Enter a number : $"
    MSG2 DB 10,13,"Number of Zeroes : $"
    MSG3 DB 10,13,"Number of Ones : $"
    ZC DB 0
    OC DB 0
DATA ENDS
PRTMSG MACRO M1
    LEA DX, M1
    MOV AH, 09H
    INT 21H
ENDM
GETDCM MACRO
    MOV AH, 01H
    INT 21H
    SUB AL, 30H
ENDM
PRTDCM MACRO
    MOV DL, [SI]
    ADD DL, 30H
    MOV AH, 02H
    INT 21H
ENDM
CODE SEGMENT
    START:  MOV AX, DATA
            MOV DS, AX
            MOV CX, 8H
            MOV ZC, 0H
            MOV OC, 0H
            PRTMSG MSG1
            GETDCM
            MOV BL, AL
    LP:     SHR BL, 01
            JC ONE
            INC ZC
            JMP ENDL
    ONE:    INC OC
    ENDL:   LOOP LP
            LEA SI, ZC
            PRTMSG MSG2
            PRTDCM
            LEA SI, OC
            PRTMSG MSG3
            PRTDCM
            MOV AH, 4CH
            INT 21H
CODE ENDS
END START
