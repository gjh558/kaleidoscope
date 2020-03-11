#include "object_pool.h"
#include <iostream>
using namespace std;

struct Test {
  Test() {
    cout << "Constructor\n";
  }
  ~Test() {
    cout << "Destroy\n";
  }
};

int main() {
  ObjectPool<Test> object_pool([]() -> std::unique_ptr<Test> {
        return std::unique_ptr<Test>(new Test);
      }, -1);

  cout << "init: object pool size " << object_pool.GetObjectNum() << endl;
  
  std::shared_ptr<Test> object = object_pool.Get();
  cout << "Get: object pool size " << object_pool.GetObjectNum() << endl;
  object = object_pool.Get();
  cout << "Get: object pool size " << object_pool.GetObjectNum() << endl;
  std::shared_ptr<Test> object1 = object_pool.Get();
  cout << "Get: object pool size " << object_pool.GetObjectNum() << endl;
  std::shared_ptr<Test> object2 = object_pool.Get();
  cout << "Get: object pool size " << object_pool.GetObjectNum() << endl;
  return 0;
}
