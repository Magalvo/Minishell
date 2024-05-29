import ply.lex as lex

tokens = (
    'IDENTIFIER',
    'PIPE',
    'REDIRECT_OUT',
    'REDIRECT_IN',
    'SEMICOLON',
    # 'OPTION',
    # 'STRING',
    # 'OPENPAR',
    # 'CLOSEPARPAR',
)

t_PIPE = r'\|'
t_REDIRECT_OUT = r'>'
t_REDIRECT_IN = r'<'
t_SEMICOLON = r';'
# t_OPENPAR = r'\('
# t_CLOSEPARPAR = r'\)'

t_ignore = ' \t\n'

# def t_OPTION(t):
# 	r'\-\w+'
# 	return t

# def t_STRING(t):
# 	r'\w+'
# 	return t

def t_IDENTIFIER(t):
    r'[a-zA-Z0-9_]+'
    return t

def t_error(t):
    print(f"Illegal character '{t.value[0]}'")
    t.lexer.skip(1)

lexer = lex.lex()
