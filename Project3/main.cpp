#include <iostream>
#include "Inventory.h"
#include "Item.h"
using namespace std;

int main() {
    Inventory<Item> inv(3);   

    cout << "== AddItem 기본 동작 ==\n";
    inv.AddItem(Item("포션", 50));
    inv.AddItem(Item("하급 검", 120));
    inv.AddItem(Item("방패", 90));
    inv.AddItem(Item("넘침", 1));       

    cout << "\n== PrintAllItems ==\n";
    inv.PrintAllItems();
    cout << "size=" << inv.GetSize() << ", cap=" << inv.GetCapacity() << "\n";

    cout << "\n== SortItems (가격 오름차순) ==\n";
    inv.SortItems();
    inv.PrintAllItems();

    cout << "\n== RemoveLastItem ==\n";
    inv.RemoveLastItem();
    inv.PrintAllItems();
    cout << "size=" << inv.GetSize() << ", cap=" << inv.GetCapacity() << "\n";

    cout << "\n== AutoExpand + AddItemWithAutoExpand ==\n";
    inv.AddItemWithAutoExpand(Item("활", 150)); 
    inv.AddItemWithAutoExpand(Item("단검", 70));
    inv.PrintAllItems();
    cout << "size=" << inv.GetSize() << ", cap=" << inv.GetCapacity() << "\n";

    cout << "\n== Resize(2) 후 유지 확인 ==\n";
    inv.Resize(2);
    inv.PrintAllItems();
    cout << "size=" << inv.GetSize() << ", cap=" << inv.GetCapacity() << "\n";

    cout << "\n== Deep Copy / Assign 테스트 ==\n";
    Inventory<Item> copy(inv);    
    Inventory<Item> other(1);
    other.Assign(inv);            
    cout << "[copy]\n";  copy.PrintAllItems();
    cout << "[other]\n"; other.PrintAllItems();

    return 0;
}
