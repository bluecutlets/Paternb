#include <iostream>
#include <string>
#include <memory>
#include <vector>


class Pizza {
public:
    void setDough(const std::string& dough)
    {
        dough_ = dough;
    }

    void setSauce(const std::string& sauce)
    {
        sauce_ = sauce;
    }

    void addTopping(const std::string& topping)
    {
        toppings_.push_back(topping);
    }

    void setSize(const std::string& size) 
    {
        size_ = size;
    }

    void displayPizza()
    {
        std::cout << "Pizza Size: " << size_
            << ", Dough: " << dough_
            << ", Sauce: " << sauce_
            << ", Toppings: ";
        for (const auto& topping : toppings_)
        {
            std::cout << topping << " ";
        }
        std::cout << std::endl;
    }

private:
    std::string size_;
    std::string dough_;
    std::string sauce_;
    std::vector<std::string> toppings_;
};


class PizzaBuilder 
{
public:
    virtual void buildDough() = 0;
    virtual void buildSauce() = 0;
    virtual void buildTopping() = 0;
    virtual void buildSize() = 0;
    virtual std::shared_ptr<Pizza> getPizza() = 0;
};

// Конкретный строитель для строительства пепперони пиццы
class PepperoniPizzaBuilder : public PizzaBuilder
{
public:
    PepperoniPizzaBuilder() : pizza_(std::make_shared<Pizza>()) {}

    void buildDough() override 
    {
        pizza_->setDough("Thick crust");
    }

    void buildSauce() override 
    {
        pizza_->setSauce("Tomato sauce");
    }

    void buildTopping() override 
    {
        pizza_->addTopping("Pepperoni");
        pizza_->addTopping("Cheese");
    }

    void buildSize() override 
    {
        pizza_->setSize("Medium");
    }

    std::shared_ptr<Pizza> getPizza() override 
    {
        return pizza_;
    }

private:
    std::shared_ptr<Pizza> pizza_;
};

// Руководитель
class Waiter {
public:
    void setPizzaBuilder(std::shared_ptr<PizzaBuilder> builder)
    {
        pizzaBuilder_ = builder;
    }

    std::shared_ptr<Pizza> getPizza() 
    {
        return pizzaBuilder_->getPizza();
    }

    void constructPizza() 
    {
        pizzaBuilder_->buildDough();
        pizzaBuilder_->buildSauce();
        pizzaBuilder_->buildTopping();
        pizzaBuilder_->buildSize();
    }

private:
    std::shared_ptr<PizzaBuilder> pizzaBuilder_;
};

int main() {
    Waiter waiter;
    std::shared_ptr<PizzaBuilder> pepperoniPizzaBuilder = std::make_shared<PepperoniPizzaBuilder>();

    waiter.setPizzaBuilder(pepperoniPizzaBuilder);
    waiter.constructPizza();
    std::shared_ptr<Pizza> pizza = waiter.getPizza();
    pizza->displayPizza();

    return 0;
}