#ifndef __EXPR_H___
#define __EXPR_H___
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <string>

class Expression
{
 public:
  Expression() {}
  virtual std::string toString() const = 0;
  virtual ~Expression() {}
};

class NumExpression : public Expression
{
  long number;

 public:
  NumExpression(long n) : number(n) {}
  virtual std::string toString() const {
    std::stringstream answer;
    answer << number;
    return answer.str();
  }
  virtual ~NumExpression() {}
};

class PlusExpression : public Expression
{
  Expression * l;
  Expression * r;

 public:
  PlusExpression(Expression * lhs, Expression * rhs) : l(lhs), r(rhs) {}
  virtual std::string toString() const {
    std::stringstream answer;
    answer << "(" << l->toString() << " + " << r->toString() << ")";
    return answer.str();
  }
  virtual ~PlusExpression() {
    delete l;
    delete r;
  }
};

class MinusExpression : public Expression
{
  Expression * l;
  Expression * r;

 public:
  MinusExpression(Expression * lhs, Expression * rhs) : l(lhs), r(rhs) {}
  virtual std::string toString() const {
    std::stringstream answer;
    answer << "(" << l->toString() << " - " << r->toString() << ")";
    return answer.str();
  }
  virtual ~MinusExpression() {
    delete l;
    delete r;
  }
};

class TimesExpression : public Expression
{
  Expression * l;
  Expression * r;

 public:
  TimesExpression(Expression * lhs, Expression * rhs) : l(lhs), r(rhs) {}
  virtual std::string toString() const {
    std::stringstream answer;
    answer << "(" << l->toString() << " * " << r->toString() << ")";
    return answer.str();
  }
  virtual ~TimesExpression() {
    delete l;
    delete r;
  }
};

class DivExpression : public Expression
{
  Expression * l;
  Expression * r;

 public:
  DivExpression(Expression * lhs, Expression * rhs) : l(lhs), r(rhs) {}
  virtual std::string toString() const {
    std::stringstream answer;
    answer << "(" << l->toString() << " / " << r->toString() << ")";
    return answer.str();
  }
  virtual ~DivExpression() {
    delete l;
    delete r;
  }
};

#endif
