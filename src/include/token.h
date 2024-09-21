#ifndef MP_TOKEN_H
#define MP_TOKEN_H
typedef struct TOKEN_STRUCT
{
    char* valor;
    enum // os tipos de token
    {
        // Operadores
        OP_EQ, // =
        OP_GE, // >=
        OP_MUL, // *
        OP_NE, // <>
        OP_LE, // <=
        OP_DIV, // '/'
        OP_GT, // >
        OP_AD, // +
        OP_DEC, // :
        OP_ASS, // :=
        OP_LT, // <
        OP_MIN, // -

        // Símbolos
        SMB_OBC, // {
        SMB_COM, // ,
        SMB_CBC, // }
        SMB_SEM, // ;
        SMB_OPA, // (
        SMB_CPA, // )
        SMB_EOP, // . end of program

        // Números
        NUM_INT,
        NUM_FLT,

        // Palavras-chave
        PAL_RES,
        T_ID,

        T_UNK, // unknown

        T_EOF // end of file
    } tipo;
} token_T;

token_T* init_token(char* valor, int tipo);

char* token_to_str(token_T* token);
#endif 