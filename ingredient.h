#pragma once
#include <string>
#include "IngredientBase.h"
#include<iostream>
#include<memory>

class Ingredient : public IngredientBase {
public:
    Ingredient(double amountValue, const std::string& unit, const std::string& name);

    std::string getName() const override { return m_name; }
    std::string getUnit() const override { return m_unit; }
    double getAmountValue() const override { return m_amountValue; }

    void scaleAmount(double ratio) override;
    void displayIngredient() const override;

private:
    double m_amountValue;
    std::string m_unit;
    std::string m_name;
};
