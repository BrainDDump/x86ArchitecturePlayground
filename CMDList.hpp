//------------------------------------------<< CPU COMMANDS >>-------------------------------------
//------------------------------------------<< STOP EXECUTING MODULE >>----------------------------
//       NAME    | NUMBER | ARG | ACTION                       | DESCRIPTION
COMMAND( STOP    , 0      , 0   , exe_stop  ();                , "End       programm      " )
//------------------------------------------<< REG SCAN / PRINT >>---------------------------------
//       NAME    | NUMBER | ARG | ACTION                       | DESCRIPTION
COMMAND( SCN     , 1      , 2   , reg_scn   (arg_1, arg_2);    , "Scan      REG_1   _TYPE " )
COMMAND( PRT     , 2      , 2   , reg_prt   (arg_1, arg_2);    , "Print     REG_1   _TYPE " )
//------------------------------------------<< REG COMMANDS (INT) >>-------------------------------
//       NAME    | NUMBER | ARG | ACTION                       | DESCRIPTION
COMMAND( SET     , 3      , 2   , reg_set   (arg_1, arg_2);    , "SET       REG     INT   " )
COMMAND( MOV     , 4      , 2   , reg_mov   (arg_1, arg_2);    , "Move      REG_1   REG_2 " )
COMMAND( CMP     , 5      , 2   , reg_cmp   (arg_1, arg_2);    , "Compare   REG_1   REG_2 " )

COMMAND( ADD     , 6      , 2   , reg_add   (arg_1, arg_2);    , "Add       REG_1   REG_2 " )
COMMAND( MUL     , 7      , 2   , reg_mul   (arg_1, arg_2);    , "Multiply  REG_1   REG_2 " )
COMMAND( DIV     , 8      , 2   , reg_div   (arg_1, arg_2);    , "Divide    REG_1   REG_2 " )

COMMAND( AND     , 9      , 2   , reg_and   (arg_1, arg_2);    , "AND       REG_1   REG_2 " )
COMMAND( OR      , 10     , 2   , reg_or    (arg_1, arg_2);    , "OR        REG_1   REG_2 " )
COMMAND( XOR     , 11     , 2   , reg_xor   (arg_1, arg_2);    , "XOR       REG_1   REG_2 " )
//------------------------------------------<< REG COMMANDS (FLOAT) >>-----------------------------
//       NAME    | NUMBER | ARG | ACTION                       | DESCRIPTION
COMMAND( SET_F   , 12     , 2   , reg_set_f (arg_1, arg_2);    , "Move      REG     FLOAT " )
COMMAND( CMP_F   , 13     , 2   , reg_cmp_f (arg_1, arg_2);    , "Compare   REG_1   REG_2 " )

COMMAND( ADD_F   , 14     , 2   , reg_add_f (arg_1, arg_2);    , "Add       REG_1   REG_2 " )
COMMAND( MUL_F   , 15     , 2   , reg_mul_f (arg_1, arg_2);    , "Multiply  REG_1   REG_2 " )
COMMAND( DIV_F   , 16     , 2   , reg_div_f (arg_1, arg_2);    , "Divide    REG_1   REG_2 " )
//------------------------------------------<< JUMP COMMANDS >>------------------------------------
//       NAME    | NUMBER | ARG | ACTION                       | DESCRIPTION
COMMAND( JMP     , 17     , 1   , prg_jmp   (arg_1);           , "Jump to   LABLE         " )
COMMAND( JEE     , 18     , 1   , prg_jee   (arg_1);           , "Jump to   LABLE if ==   " )
COMMAND( JNE     , 19     , 1   , prg_jne   (arg_1);           , "Jump to   LABLE if !=   " )
COMMAND( JLE     , 20     , 1   , prg_jle   (arg_1);           , "Jump to   LABLE if <=   " )
COMMAND( JME     , 21     , 1   , prg_jme   (arg_1);           , "Jump to   LABLE if >=   " )

COMMAND( CALL    , 22     , 1   , func_call (arg_1);           , "Call func ptr           " )
COMMAND( RET     , 23     , 0   , func_ret  ();                , "Return                  " )
//------------------------------------------<< MEMORY COMMANDS >>----------------------------------
//------------------------------------------<< VARIABLE COMMANDS >>--------------------------------
//       NAME    | NUMBER | ARG | ACTION                       | DESCRIPTION
COMMAND( DEC     , 24     , 2   , var_dec    (arg_1, arg_2);   , "Reserve   VAR     TYPE  " )
COMMAND( SET_V   , 25     , 2   , var_set_v  (arg_1, arg_2);   , "Set       VAR     $I/F  " )

COMMAND( POP_V   , 26     , 2   , var_pop_v  (arg_1, arg_2);   , "Pop       VAR     REG   " )        // QUE!
COMMAND( PSH_V   , 27     , 2   , var_psh_v  (arg_1, arg_2);   , "Push      VAR     REG   " )

COMMAND( SET_VF  , 28     , 2   , var_set_vf (arg_1, arg_2);   , "Set       VAR     $I/F  " )
//------------------------------------------<< ARG stack commands >>-------------------------------
//       NAME    | NUMBER | ARG | ACTION                       | DESCRIPTION
COMMAND( PSH     , 29     , 1   , arg_psh    (arg_1);          , "Psh  from REG           " )
COMMAND( POP     , 30     , 1   , arg_pop    (arg_1);          , "Pop  to   REG           " )        // QUE!
//-------------------------------------------------------------------------------------------------
