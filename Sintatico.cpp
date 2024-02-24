#include "./Sintatico.h"
#include <exception>
#include <iostream>
#include <list>
#include <vector>

/*
int control = 0; // onde estamos

if(this->tokens[control] == "program"){
    control++;
    if(this->tokens[control] == "id"){
        control++;
        if(this->tokens[control] == ";"){

        }else{
            printf("ERRO");
        }
    }
}

*/

void Sintatico::analyse() {
  TOKEN_ITERATOR token = this->tokens.begin();
  token = this->program(token);
};

TOKEN_ITERATOR Sintatico::program(TOKEN_ITERATOR token) {
  if (token->name == "program") {
    token++;
    if (token->type == Type::IDENTIFIER) {
      token++;
      if (token->name == ";") {
        token++;
        token = variable_declaration(token);
      } else {
        std::cerr << "[" << token->line << "] ERROR: Expected ;" << std::endl;
        throw std::exception();
      }
    } else {
      std::cerr << "[" << token->line << "] ERROR: Expected IDENTIFIER"
                << std::endl;
      throw std::exception();
    }
  } else {
    std::cerr << "[" << token->line << "] ERROR: Expected program" << std::endl;
  }

  token = subprograms_declarations(token);

  return token;
}

TOKEN_ITERATOR Sintatico::variable_declaration(TOKEN_ITERATOR token) {
  if (token->name == "var") {
    token++;
    token = variable_declaration_list(token);
  }

  return token;
}

TOKEN_ITERATOR Sintatico::variable_declaration_list(TOKEN_ITERATOR token) {
  try {
    token = identifiers_list(token);
    token++;
    if (token->name == ":") {
      token++;
      token = type(token);
      token++;
      token = variable_declaration_list2(token);
    }
    return token;
  } catch (std::exception err) {
    std::cerr << "[" << token->line
              << "] ERROR: variable_declaration_list error" << std::endl;
    throw err;
  }
}

TOKEN_ITERATOR Sintatico::variable_declaration_list2(TOKEN_ITERATOR token) {
  if (token->name == ";") {
    token = identifiers_list(token);
    token++;
    if (token->name == ":") {
      token++;
      token = type(token);
      token++;
      token = variable_declaration_list2(token);
    }
  }
  return token;
}

TOKEN_ITERATOR Sintatico::identifiers_list(TOKEN_ITERATOR token) {
  if (token->type == Type::IDENTIFIER) {
    token++;
    token = identifiers_list2(token);
  }

  return token;
}

TOKEN_ITERATOR Sintatico::identifiers_list2(TOKEN_ITERATOR token) {
  if (token->name == ",") {
    token++;
    if (token->type == Type::IDENTIFIER) {
      token++;
      token = identifiers_list2(token);
    }
  }

  return token;
}

TOKEN_ITERATOR Sintatico::type(TOKEN_ITERATOR token) {
  if (token->type == Type::INTEGER || token->type == Type::REAL ||
      token->type == Type::BOOLEAN) {
    return token;
  }

  std::cerr << "[" << token->line << "] ERROR: Expected TYPE" << std::endl;
  throw std::exception();
};

TOKEN_ITERATOR Sintatico::subprograms_declarations(TOKEN_ITERATOR token) {
  token = subprogram_declaration(token);

  return token;
}

TOKEN_ITERATOR Sintatico::subprograms_declarations2(TOKEN_ITERATOR token) {}

TOKEN_ITERATOR Sintatico::subprogram_declaration(TOKEN_ITERATOR token) {
  if (token->type == Type::PROCEDURE) {
    token++;
    if (token->type == Type::IDENTIFIER) {
      token++;
      token = arguments(token);
      token++;
      if (token->name == ";") {
        token++;
        token = variable_declaration(token);
        token++;
        token = subprograms_declarations(token);
        token++;
        token = compost_command(token);
      }
    }
  }
};

TOKEN_ITERATOR Sintatico::compost_command(TOKEN_ITERATOR token) {
  if (token->name == "begin") {
    token = optinals_command(token);
    token++;
    if (token->name == "end") {
      return token;
    }
  }

  throw std::exception();
}

TOKEN_ITERATOR Sintatico::optinals_command(TOKEN_ITERATOR token) {
  token = command_list(token);
}

TOKEN_ITERATOR Sintatico::command_list(TOKEN_ITERATOR token) {
  token = command(token);
  token++;
  token = command_list2(token);

  return token;
}

TOKEN_ITERATOR Sintatico::command_list2(TOKEN_ITERATOR token) {
  if (token->name == ";") {
    token++;
    token = command(token);
    token++;
    token = command_list2(token);
  }

  return token;
}

TOKEN_ITERATOR Sintatico::command(TOKEN_ITERATOR token) {
  if (token->type == Type::IDENTIFIER) {
    token++;
    if (token->name == ":=") {
      token++;
    }
  }
}

TOKEN_ITERATOR Sintatico::expression(TOKEN_ITERATOR token) {
  try {
    token = simple_expression(token);
  } catch (std::exception) {
    token = simple_expression(token);
    token++;
    if (token->type == Type::RELACIONAL_OPERATOR) {
      token++;
      token = simple_expression(token);
    }
  }

  return token;
};

TOKEN_ITERATOR Sintatico::simple_expression(TOKEN_ITERATOR token) {
  token = term(token);
  token++;
};

TOKEN_ITERATOR Sintatico::term(TOKEN_ITERATOR token) {
  token = factor(token);
  token++;
  token = term2(token);

  return token;
}

TOKEN_ITERATOR Sintatico::term2(TOKEN_ITERATOR token) {
  if (token->name == "*") {
    token++;
    token = term2(token);
  }

  return token;
}

TOKEN_ITERATOR Sintatico::factor(TOKEN_ITERATOR token) {
  if (token->type == Type::IDENTIFIER) {
    token++;
    if (token->name == "(") {
      token++;
      token = expression_list(token);
      token++;
      if (token->name == ")") {
        return token;
      }
    }
  }
}

TOKEN_ITERATOR Sintatico::arguments(TOKEN_ITERATOR token) {
  if (token->name == "(") {
    token++;
    token = parameters_list(token);
    token++;
    if (token->name == ")") {
      return token;
    }
  }

  return token;
};

TOKEN_ITERATOR Sintatico::parameters_list(TOKEN_ITERATOR token) {
  token = identifiers_list(token);
  token++;
  if (token->name == ":") {
    token++;
    token = type(token);
    token++;
    token = parameters_list2(token);
  }

  return token;
}

TOKEN_ITERATOR Sintatico::parameters_list2(TOKEN_ITERATOR token) {
  if (token->name == ";") {
    token++;
    token = identifiers_list(token);
    token++;
    if (token->name == ":") {
      token++;
      token = type(token);
      token++;
      token = parameters_list2(token);
    }
  }

  return token;
}

void Sintatico::saveToFile(std::string){};

Type stringToType(std::string s) {
  if (s == "REAL") {
    return Type::REAL;
  } else if (s == "INTEGER") {
    return Type::INTEGER;
  } else if (s == "RELACIONAL_OPERATOR") {
    return Type::RELACIONAL_OPERATOR;
  } else if (s == "LOGICAL_OPERATOR") {
    return Type::LOGICAL_OPERATOR;
  } else if (s == "OPERATOR") {
    return Type::OPERATOR;
  } else if (s == "KEYWORD") {
    return Type::KEYWORD;
  } else if (s == "IDENTIFIER") {
    return Type::IDENTIFIER;
  } else if (s == "DELIMITER") {
    return Type::DELIMITER;
  } else if (s == "ASSIGN") {
    return Type::ASSIGN;
  }

  throw std::exception();
}