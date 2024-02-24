#include <string>
#include <vector>

#define TOKEN_ITERATOR std::vector<Token>::iterator

enum Type {
  REAL,
  INTEGER,
  BOOLEAN,
  RELACIONAL_OPERATOR,
  LOGICAL_OPERATOR,
  OPERATOR,
  KEYWORD,
  IDENTIFIER,
  DELIMITER,
  ASSIGN,
  EXPRESSION,
  PROGRAM,
  PROCEDURE,
};

struct Token {
  Type type;
  std::string name;
  unsigned long line;
};

class Sintatico {
public:
  std::vector<Token> tokens;
  void analyse();
  void saveToFile(std::string);

  TOKEN_ITERATOR program(TOKEN_ITERATOR token);
  TOKEN_ITERATOR variable_declaration(TOKEN_ITERATOR token);
  TOKEN_ITERATOR variable_declaration_list(TOKEN_ITERATOR token);
  TOKEN_ITERATOR variable_declaration_list2(TOKEN_ITERATOR token);
  TOKEN_ITERATOR identifiers_list(TOKEN_ITERATOR token);
  TOKEN_ITERATOR identifiers_list2(TOKEN_ITERATOR token);
  TOKEN_ITERATOR type(TOKEN_ITERATOR token);

  TOKEN_ITERATOR subprogram_declaration(TOKEN_ITERATOR token);
  TOKEN_ITERATOR subprograms_declarations(TOKEN_ITERATOR token);
  TOKEN_ITERATOR subprograms_declarations2(TOKEN_ITERATOR token);
  TOKEN_ITERATOR arguments(TOKEN_ITERATOR token);
  TOKEN_ITERATOR parameters_list(TOKEN_ITERATOR token);
  TOKEN_ITERATOR parameters_list2(TOKEN_ITERATOR token);
  TOKEN_ITERATOR compost_command(TOKEN_ITERATOR token);
  TOKEN_ITERATOR optinals_command(TOKEN_ITERATOR token);
  TOKEN_ITERATOR command_list(TOKEN_ITERATOR token);
  TOKEN_ITERATOR command_list2(TOKEN_ITERATOR token);
  TOKEN_ITERATOR command(TOKEN_ITERATOR token);
  TOKEN_ITERATOR expression(TOKEN_ITERATOR token);
  TOKEN_ITERATOR simple_expression(TOKEN_ITERATOR token);
  TOKEN_ITERATOR term(TOKEN_ITERATOR token);
  TOKEN_ITERATOR term2(TOKEN_ITERATOR token);
  TOKEN_ITERATOR factor(TOKEN_ITERATOR token);
  TOKEN_ITERATOR expression_list(TOKEN_ITERATOR token);
  TOKEN_ITERATOR expression_list2(TOKEN_ITERATOR token);
};

Type stringToType(std::string s);
