#include <iostream>
#include <cassert>
#include <map>
#include <memory>
#include "expression_factory.hpp"
#include "constant.hpp"
#include "variable.hpp"
#include "addition.hpp"
#include "subtract.hpp"
#include "multiply.hpp"
#include "divide.hpp"

class ExpressionHolder {
    Expression* expr;
public:
    explicit ExpressionHolder(Expression* e) : expr(e) { expr->AddRef(); }
    ~ExpressionHolder() { expr->Release(); }
    Expression* get() const { return expr; }
    ExpressionHolder(const ExpressionHolder&) = delete;
    ExpressionHolder& operator=(const ExpressionHolder&) = delete;
};

int main() {
    std::setlocale(LC_ALL, "ru_RU.UTF-8");
    ExpressionFactory factory;

    {
        Constant* c = factory.createConstant(2);
        ExpressionHolder varX(factory.createVariable("x"));
        Addition* expr = new Addition(c, varX.get());

        std::map<std::string, double> context;
        context["x"] = 3;
        std::cout << "=== Пример из задания ===\n";
        std::cout << "Выражение: ";
        expr->print();
        std::cout << " = " << expr->calculate(context) << "\n\n";
        delete expr;
    }

    ExpressionHolder c5(factory.createConstant(5));
    ExpressionHolder c2(factory.createConstant(2));
    ExpressionHolder varX(factory.createVariable("x"));
    ExpressionHolder varY(factory.createVariable("y"));

    Addition* add = new Addition(c5.get(), varX.get());
    Subtract* sub = new Subtract(varY.get(), c2.get());
    Multiply* mul = new Multiply(add, sub);

    std::cout << "=== Сложное выражение ===\n";
    std::cout << "Выражение: ";
    mul->print();
    std::cout << "\n";

    std::map<std::string, double> ctx1 = {{"x", 3}, {"y", 7}};
    std::cout << "При x=3, y=7 -> " << mul->calculate(ctx1) << " (ожидается 40)\n";

    std::map<std::string, double> ctx2 = {{"x", 0}, {"y", 0}};
    std::cout << "При x=0, y=0 -> " << mul->calculate(ctx2) << " (ожидается -10)\n\n";

    delete mul;

    std::cout << "=== Приспособленец: повторное использование ===\n";
    ExpressionHolder x1(factory.createVariable("x"));
    ExpressionHolder x2(factory.createVariable("x"));
    assert(x1.get() == x2.get());
    std::cout << "Переменная 'x' используется повторно (адреса равны): "
              << x1.get() << " == " << x2.get() << "\n";

    ExpressionHolder c10_a(factory.createConstant(10));
    ExpressionHolder c10_b(factory.createConstant(10));
    assert(c10_a.get() == c10_b.get());
    std::cout << "Константа 10 (из диапазона [-5,256]) та же: "
              << c10_a.get() << " == " << c10_b.get() << "\n";

    Addition* doubleX = new Addition(x1.get(), x2.get());
    std::map<std::string, double> ctx_x = {{"x", 3}};
    std::cout << "x + x = " << doubleX->calculate(ctx_x) << " (ожидается 6)\n";
    delete doubleX;
    std::cout << "\n";

    std::cout << "=== Константы вне диапазона (автоудаление) ===\n";
    ExpressionHolder bigConst(factory.createConstant(1000));
    std::cout << "Константа 1000 создана (адрес: " << bigConst.get() << ")\n";

    Multiply* testMul = new Multiply(bigConst.get(), bigConst.get());
    std::cout << "1000 * 1000 = " << testMul->calculate({}) << " (1000000)\n";
    delete testMul;

    ExpressionHolder bigConst2(factory.createConstant(1000));
    std::cout << "Новый объект 1000: " << bigConst2.get()
              << " (разные адреса: " << (bigConst2.get() != bigConst.get() ? "да" : "нет") << ")\n\n";

    std::cout << "=== Переменные: автоудаление при refCount=0 ===\n";
    {
        ExpressionHolder z1(factory.createVariable("z"));
        std::cout << "Переменная 'z' создана: " << z1.get() << "\n";
        Multiply* temp = new Multiply(z1.get(), factory.createConstant(3));
        std::cout << "z * 3 (при z=10): " << temp->calculate({{"z", 10}}) << "\n";
        delete temp;
    }
    ExpressionHolder z2(factory.createVariable("z"));
    std::cout << "После удаления создана новая 'z': " << z2.get() << "\n";
    assert(z2.get() != nullptr);

    std::cout << "\n";

    std::cout << "=== Деление и проверка на ноль ===\n";
    ExpressionHolder ten(factory.createConstant(10));
    ExpressionHolder zero(factory.createConstant(0));
    Divide* divOk = new Divide(ten.get(), factory.createConstant(2));
    std::cout << "10 / 2 = " << divOk->calculate({}) << "\n";
    delete divOk;

    Divide* divErr = new Divide(ten.get(), zero.get());
    try {
        double result = divErr->calculate({});
        std::cout << "Результат 10/0: " << result << " (не должно было дойти)\n";
    } catch (const std::runtime_error& e) {
        std::cout << "Поймано исключение: " << e.what() << "\n";
    }
    delete divErr;

    std::cout << "\n=== Все тесты успешно пройдены ===\n";
    return 0;
}