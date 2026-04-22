#include<string>
#pragma once
#include<memory>

//Base class (for Ingredients-still required) for inheritance 
class IngredientBase {
public:
    virtual ~IngredientBase() noexcept = default;

    virtual std::string getName() const = 0;
    virtual std::string getUnit() const = 0;
    virtual double getAmountValue() const = 0;

    virtual void scaleAmount(double ratio) = 0;

    virtual void displayIngredient()  const = 0;
};
//Note theres no .cpp file and thats because the functionality lives in the header
