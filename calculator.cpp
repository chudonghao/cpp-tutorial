#include <iostream>
#include <stack>

void TakeBlank(const std::string &expr, double &opera, size_t &pos) {
  for (; pos < expr.size(); ++pos) {
    if (std::isblank(expr[pos])) {
      continue;
    } else {
      return;
    }
  }
}

bool TakeNumber(const std::string &expr, double &opera, size_t &pos) {
  size_t begin = pos;
  size_t len{};
  for (; pos < expr.size(); ++pos) {
    if (std::isdigit(expr[pos]) || expr[pos] == '.' || (len == 0 && expr[pos] == '-')) {
      ++len;
      continue;
    } else {
      break;
    }
  }
  if (!len) {
    return false;
  }
  opera = std::stod(expr.substr(begin, len));
  return true;
}

bool TakeOp(const std::string &expr, char &op, size_t &pos) {
  if (expr.size() <= pos) {
    return false;
  }
  switch (expr[pos]) {
    case '+':
    case '-':
    case '*':
    case '/':
    case '(':
    case ')':
      op = expr[pos];
      ++pos;
      return true;
    default:
      return false;
  }
}

bool TestOp(const std::string &expr, char op, size_t pos) {
  if (expr.size() <= pos) {
    return false;
  }
  return expr[pos] == op;
}

void ReportError(const std::string &expr, size_t pos, const std::string &message) {
  std::cerr << expr << std::endl;
  std::cerr << std::string(pos, ' ') << "^ " << message;
}

int GetPri(char op) {
  switch (op) {
    case '+':
    case '-':
      return 1;
    case '*':
    case '/':
      return 2;
    default:
      std::cerr << "ERROR: invalid operator" << std::endl;
      std::exit(1);
  }
}

void CalTop(std::stack<double> &opera_stack, std::stack<char> &op_stack) {
  if (opera_stack.size() < 2) {
    std::cerr << "ERROR: invalid cal top" << std::endl;
    std::exit(1);
  }

  if (op_stack.size() != opera_stack.size() - 1) {
    std::cerr << "ERROR: invalid op stack" << std::endl;
    std::exit(1);
  }

  char op = op_stack.top();
  op_stack.pop();
  double opera[2]{};
  opera[1] = opera_stack.top();
  opera_stack.pop();
  opera[0] = opera_stack.top();
  opera_stack.pop();
  double tmp_res{};

  switch (op) {
    case '+':
      tmp_res = opera[0] + opera[1];
      break;
    case '-':
      tmp_res = opera[0] - opera[1];
      break;
    case '*':
      tmp_res = opera[0] * opera[1];
      break;
    case '/':
      tmp_res = opera[0] / opera[1];
      break;
    default:
      std::cerr << "ERROR: invalid operator" << std::endl;
      std::exit(1);
  }
  opera_stack.push(tmp_res);
}

void Cal(std::stack<double> &opera_stack, std::stack<char> &op_stack) {
  for (; 2 <= opera_stack.size();) {
    CalTop(opera_stack, op_stack);
  }
}

double EvalExpr(const std::string &expr, size_t &pos) {
  size_t pos_start = pos;
  std::stack<double> opera_stack;
  std::stack<char> op_stack;
  for (;;) {
    char op{};
    double opera{};

    TakeBlank(expr, opera, pos);
    if (pos == expr.size()) {
      Cal(opera_stack, op_stack);
      if (opera_stack.size() == 1 && op_stack.empty()) {
        std::cout << "EXPR: " << expr << " RES: " << opera_stack.top() << std::endl;
        return opera_stack.top();
      } else {
        // ReportError(expr, pos, "ERROR: invalid expr");
        // std::exit(1);

        // let follow-up report error
      }
    }
    if (TestOp(expr, ')', pos)) {
      Cal(opera_stack, op_stack);
      if (opera_stack.size() == 1 && op_stack.empty()) {
        std::cout << "SUB EXPR: " << expr.substr(pos_start, pos - pos_start) << " RES: " << opera_stack.top() << std::endl;
        return opera_stack.top();
      } else {
        // ReportError(expr, pos, "ERROR: invalid expr");
        // std::exit(1);

        // let follow-up report error
      }
    }

    if (opera_stack.size() == op_stack.size()) {
      if (TestOp(expr, '(', pos)) {
        // take (
        TakeOp(expr, op, pos);

        // eval ()
        double tmp_result = EvalExpr(expr, pos);
        opera_stack.push(tmp_result);

        // take )
        if (!TestOp(expr, ')', pos)) {
          ReportError(expr, pos, "ERROR: expect )");
          std::exit(1);
        }
        TakeOp(expr, op, pos);
        continue;
      }

      if (TakeNumber(expr, opera, pos)) {
        opera_stack.push(opera);
        continue;
      } else {
        ReportError(expr, pos, "ERROR: expect number");
        std::exit(1);
      }
    }

    if (TakeOp(expr, op, pos)) {
      if (!op_stack.empty() && GetPri(op) <= GetPri(op_stack.top())) {
        CalTop(opera_stack, op_stack);
      }
      op_stack.push(op);
      continue;
    } else {
      ReportError(expr, pos, "ERROR: expect operator");
      std::exit(1);
    }
  }
}

int main() {
  std::cout << "Calculator!" << std::endl;
  std::cout << "Expression example: " << std::endl;
  std::cout << "  1 + 1" << std::endl;
  std::cout << "  2 * (2 + 2)" << std::endl;
  std::cout << "Please enter expression:" << std::endl;
  // handle line expr loop
  for (;;) {
    std::string expr;
    std::getline(std::cin, expr);

    if (expr.empty()) {
      break;
    }
    if (expr[0] == '#') {
      continue;
    }

    // eval expr
    size_t pos{};
    EvalExpr(expr, pos);
  }
  return 0;
}
