//
// Created by USER on 09/11/2021.
//

#include "explore_shared_ptr.h"

#include <vector>
#include <memory>
using std::cout;
using std::shared_ptr;
using std:: make_shared;
using std::vector;

int main()
{
    vector<shared_ptr<Entity>> a;

    a.resize(5);
    vector<shared_ptr<Entity>> b;
    b.resize(5);
    //vector<shared_ptr<Entity>> c;
 //   b.resize(5, nullptr);
    for(int i = 0 ; i < a.size() ; i++) {
        a[i] = nullptr;
        b[i] = nullptr;
    }
    for(int i = 0 ; i < a.size() ; i++) {
        a[i] = make_shared<Entity>(Entity(i));
        b[i] = a[i];
    }
    cout<<std::endl;
    cout<<std::endl;
    cout<<std::endl;
    cout<<std::endl;
    for(int i = 0 ; i < a.size() ; i++) {
        a[i] = nullptr;
    }
    cout<<std::endl;
    cout<<std::endl;
    cout<<std::endl;
  //  a[0]->printEntity();
    cout<<std::endl;
    if(b[0] != nullptr ) {
        b[0]->printEntity();
        cout << "\n ohhh yeah \n";
    }
    if(a[0] != nullptr) {
        a[0]->printEntity();
        cout << std::endl;
    }

    return 0;
}