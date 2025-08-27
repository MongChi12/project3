#include <iostream>
#include "Inventory.h"
#include "Item.h"
using namespace std;

int main() {
    Inventory<Item> inv(3);   

    cout << "== AddItem �⺻ ���� ==\n";
    inv.AddItem(Item("����", 50));
    inv.AddItem(Item("�ϱ� ��", 120));
    inv.AddItem(Item("����", 90));
    inv.AddItem(Item("��ħ", 1));       

    cout << "\n== PrintAllItems ==\n";
    inv.PrintAllItems();
    cout << "size=" << inv.GetSize() << ", cap=" << inv.GetCapacity() << "\n";

    cout << "\n== SortItems (���� ��������) ==\n";
    inv.SortItems();
    inv.PrintAllItems();

    cout << "\n== RemoveLastItem ==\n";
    inv.RemoveLastItem();
    inv.PrintAllItems();
    cout << "size=" << inv.GetSize() << ", cap=" << inv.GetCapacity() << "\n";

    cout << "\n== AutoExpand + AddItemWithAutoExpand ==\n";
    inv.AddItemWithAutoExpand(Item("Ȱ", 150)); 
    inv.AddItemWithAutoExpand(Item("�ܰ�", 70));
    inv.PrintAllItems();
    cout << "size=" << inv.GetSize() << ", cap=" << inv.GetCapacity() << "\n";

    cout << "\n== Resize(2) �� ���� Ȯ�� ==\n";
    inv.Resize(2);
    inv.PrintAllItems();
    cout << "size=" << inv.GetSize() << ", cap=" << inv.GetCapacity() << "\n";

    cout << "\n== Deep Copy / Assign �׽�Ʈ ==\n";
    Inventory<Item> copy(inv);    
    Inventory<Item> other(1);
    other.Assign(inv);            
    cout << "[copy]\n";  copy.PrintAllItems();
    cout << "[other]\n"; other.PrintAllItems();

    return 0;
}
