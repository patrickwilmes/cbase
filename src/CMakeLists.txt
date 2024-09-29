
SET(SOURCES
        lexer.c
        lexer.h
        ds/stack.c
        ds/stack.h
)
add_executable(cbase main.c ${SOURCES})
