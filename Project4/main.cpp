#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

// -------------------- PotionRecipe --------------------
class PotionRecipe {
    std::string potionName_;
    std::vector<std::string> ingredients_;
public:
    PotionRecipe() = default;
    PotionRecipe(std::string name, std::vector<std::string> ingredients)
        : potionName_(std::move(name)), ingredients_(std::move(ingredients)) {
    }

    const std::string& getName() const { return potionName_; }
    const std::vector<std::string>& getIngredients() const { return ingredients_; }

    bool containsIngredient(const std::string& ing) const {
        return std::find(ingredients_.begin(), ingredients_.end(), ing) != ingredients_.end();
    }

    void print() const {
        std::cout << "- " << potionName_ << " : [";
        for (size_t i = 0; i < ingredients_.size(); ++i) {
            std::cout << ingredients_[i];
            if (i + 1 < ingredients_.size()) std::cout << ", ";
        }
        std::cout << "]\n";
    }
};

// -------------------- RecipeManager --------------------
class RecipeManager {
    std::vector<PotionRecipe> recipes_;
public:
    void addRecipe(const std::string& name, const std::vector<std::string>& ingredients) {
        auto it = std::find_if(recipes_.begin(), recipes_.end(),
            [&](const PotionRecipe& r) { return r.getName() == name; });
        if (it != recipes_.end()) {
            std::cout << "[���] �̹� �����ϴ� ���� �̸��Դϴ�: " << name << "\n";
            return;
        }
        recipes_.emplace_back(name, ingredients);
    }

    void displayAllRecipes() const {
        if (recipes_.empty()) {
            std::cout << "(������ ����)\n";
            return;
        }
        for (const auto& r : recipes_) r.print();
    }

    const PotionRecipe* findRecipeByName(const std::string& name) const {
        auto it = std::find_if(recipes_.begin(), recipes_.end(),
            [&](const PotionRecipe& r) { return r.getName() == name; });
        return (it == recipes_.end()) ? nullptr : &(*it);
    }

    std::vector<PotionRecipe> findRecipesByIngredient(const std::string& ingredient) const {
        std::vector<PotionRecipe> found;
        for (const auto& r : recipes_) {
            if (r.containsIngredient(ingredient)) found.push_back(r);
        }
        return found;
    }

    const std::vector<PotionRecipe>& getAllRecipes() const { return recipes_; }
};

// -------------------- StockManager --------------------
class StockManager {
    std::map<std::string, int> stock_;
    static const int MAX_STOCK = 3;
public:
    void initializeStock(const std::string& potionName) { stock_[potionName] = MAX_STOCK; }

    int getStock(const std::string& potionName) const {
        auto it = stock_.find(potionName);
        return (it == stock_.end()) ? 0 : it->second;
    }

    bool dispensePotion(const std::string& potionName) {
        auto it = stock_.find(potionName);
        if (it == stock_.end()) return false;
        if (it->second <= 0) return false;
        --(it->second);
        return true;
    }

    bool returnPotion(const std::string& potionName) {
        auto it = stock_.find(potionName);
        if (it == stock_.end()) return false;
        if (it->second >= MAX_STOCK) return false;
        ++(it->second);
        return true;
    }
};

// -------------------- AlchemyWorkshop --------------------
class AlchemyWorkshop {
    RecipeManager recipeMgr_;
    StockManager  stockMgr_;
public:
    void addRecipe(const std::string& name, const std::vector<std::string>& ingredients) {
        recipeMgr_.addRecipe(name, ingredients);
        if (recipeMgr_.findRecipeByName(name)) {
            stockMgr_.initializeStock(name);
        }
    }

    void displayAllRecipes() const { recipeMgr_.displayAllRecipes(); }

    const PotionRecipe* searchRecipeByName(const std::string& name) const {
        return recipeMgr_.findRecipeByName(name);
    }

    std::vector<PotionRecipe> searchRecipeByIngredient(const std::string& ingredient) const {
        return recipeMgr_.findRecipesByIngredient(ingredient);
    }

    int  getStock(const std::string& potionName) const { return stockMgr_.getStock(potionName); }
    bool dispensePotion(const std::string& potionName) { return stockMgr_.dispensePotion(potionName); }
    bool returnPotion(const std::string& potionName) { return stockMgr_.returnPotion(potionName); }
};

// -------------------- main (�׽�Ʈ) --------------------
int main() {
    AlchemyWorkshop lab;

    lab.addRecipe("�� ����", std::vector<std::string>{"���", "��"});
    lab.addRecipe("���� ����", std::vector<std::string>{"���°���", "��"});
    lab.addRecipe("�ص���", std::vector<std::string>{"�ص���", "���", "��"});

    std::cout << "== ��� ������ ==\n";
    lab.displayAllRecipes();

    std::cout << "\n== �̸����� �˻�: '���� ����' ==\n";
    if (const PotionRecipe* r = lab.searchRecipeByName("���� ����")) r->print();
    else std::cout << "����\n";

    std::cout << "\n== ���� �˻�: '���' ���� ������ ==\n";
    for (const auto& r : lab.searchRecipeByIngredient("���")) r.print();

    std::cout << "\n== ��� ��ȸ/����/��ȯ ==\n";
    std::cout << "�� ���� ���: " << lab.getStock("�� ����") << "\n";
    std::cout << "���谡���� �� ���� ���� �� " << (lab.dispensePotion("�� ����") ? "����" : "����") << "\n";
    std::cout << "�� ���� ���: " << lab.getStock("�� ����") << "\n";
    std::cout << "��ȯ(�� ��) �� " << (lab.returnPotion("�� ����") ? "����" : "����") << "\n";
    std::cout << "�� ���� ���: " << lab.getStock("�� ����") << "\n";

    std::cout << "\n== ����(3) �ʰ� ��ȯ �׽�Ʈ ==\n";
    std::cout << "����: " << lab.getStock("�� ����") << "\n";
    std::cout << "��ȯ �õ�: " << (lab.returnPotion("�� ����") ? "����" : "����") << "\n";
    std::cout << "����: " << lab.getStock("�� ����") << "\n";

    return 0;
}
