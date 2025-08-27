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
            std::cout << "[경고] 이미 존재하는 물약 이름입니다: " << name << "\n";
            return;
        }
        recipes_.emplace_back(name, ingredients);
    }

    void displayAllRecipes() const {
        if (recipes_.empty()) {
            std::cout << "(레시피 없음)\n";
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

// -------------------- main (테스트) --------------------
int main() {
    AlchemyWorkshop lab;

    lab.addRecipe("힐 포션", std::vector<std::string>{"허브", "물"});
    lab.addRecipe("마나 포션", std::vector<std::string>{"마력가루", "물"});
    lab.addRecipe("해독제", std::vector<std::string>{"해독초", "허브", "물"});

    std::cout << "== 모든 레시피 ==\n";
    lab.displayAllRecipes();

    std::cout << "\n== 이름으로 검색: '마나 포션' ==\n";
    if (const PotionRecipe* r = lab.searchRecipeByName("마나 포션")) r->print();
    else std::cout << "없음\n";

    std::cout << "\n== 재료로 검색: '허브' 포함 레시피 ==\n";
    for (const auto& r : lab.searchRecipeByIngredient("허브")) r.print();

    std::cout << "\n== 재고 조회/지급/반환 ==\n";
    std::cout << "힐 포션 재고: " << lab.getStock("힐 포션") << "\n";
    std::cout << "모험가에게 힐 포션 지급 → " << (lab.dispensePotion("힐 포션") ? "성공" : "실패") << "\n";
    std::cout << "힐 포션 재고: " << lab.getStock("힐 포션") << "\n";
    std::cout << "반환(빈 병) → " << (lab.returnPotion("힐 포션") ? "성공" : "실패") << "\n";
    std::cout << "힐 포션 재고: " << lab.getStock("힐 포션") << "\n";

    std::cout << "\n== 상한(3) 초과 반환 테스트 ==\n";
    std::cout << "현재: " << lab.getStock("힐 포션") << "\n";
    std::cout << "반환 시도: " << (lab.returnPotion("힐 포션") ? "성공" : "실패") << "\n";
    std::cout << "현재: " << lab.getStock("힐 포션") << "\n";

    return 0;
}
