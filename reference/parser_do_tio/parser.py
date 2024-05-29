import ply.yacc as yacc
from lexer import tokens

class ASTNode:
    def __init__(self, value, left=None, right=None):
        self.value = value
        self.left = left
        self.right = right

    def __repr__(self, level=0):
        ret = "\t" * level + repr(self.value) + "\n"
        if self.left:
            ret += self.left.__repr__(level + 1)
        if self.right:
            ret += self.right.__repr__(level + 1)
        return ret

def p_program(p):
    '''program : command_list'''
    p[0] = p[1]

def p_command_list(p):
    '''command_list : command_list SEMICOLON pipeline
                    | pipeline'''
    if len(p) == 2:
        p[0] = p[1]
    else:
        p[0] = ASTNode(';', p[1], p[3])

def p_pipeline(p):
    '''pipeline : pipeline PIPE command
                | command'''
    if len(p) == 2:
        p[0] = p[1]
    else:
        p[0] = ASTNode('|', p[1], p[3])

def p_command(p):
    '''command : IDENTIFIER redirect_list
               | IDENTIFIER'''
    if len(p) == 2:
        p[0] = ASTNode(p[1])
    else:
        p[0] = ASTNode(p[1], p[2])

def p_redirect_list(p):
    '''redirect_list : redirect_list REDIRECT_IN IDENTIFIER
                     | redirect_list REDIRECT_OUT IDENTIFIER
                     | REDIRECT_IN IDENTIFIER
                     | REDIRECT_OUT IDENTIFIER'''
    if len(p) == 3:
        p[0] = ASTNode(p[1], ASTNode(p[2]))
    else:
        p[0] = ASTNode(p[2], p[1], ASTNode(p[3]))

def p_error(p):
    print("Syntax error at '%s'" % p.value if p else "Syntax error at EOF")

parser = yacc.yacc()
