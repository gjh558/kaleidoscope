#include <vector>
#include <memory>
#include <string.h>
#include <stdlib.h>

// TODO: this implementation is not thread safe
template <typename T>
class ObjectPool {
public:
  ObjectPool(std::function<std::unique_ptr<T>()> creator, int64_t capacity) :
      creator_fn_(creator),
      object_pool_capacity_(capacity),
      object_num_(0) {
    if (object_pool_capacity_ <= 0) {
      perror("wrong capacity");
      exit(0);
    }

    default_object_ = *(creator_fn_().get());
  
    AllocatePool();
  }
  
  std::shared_ptr<T> Get() {
    if (object_num_ == 0) {
      // TODO: there is no objects to use
      perror("no free objects int the pool");
      return nullptr;
    }
    
    std::unique_ptr<T> free_object(std::move(free_objects_.back()));
    free_objects_.pop_back();
    --object_num_;
    // construct shared_ptr
    std::shared_ptr<T> object(free_object.release(), [this](T* pt){
      ResetObject(pt);
      free_objects_.push_back(std::unique_ptr<T>(pt));
      ++object_num_;
    });

    return object;
  }

  size_t GetObjectNum() {
    return object_num_;
  }
private:
  void AllocatePool() {
    free_objects_.reserve(object_pool_capacity_);
    
    for (int64_t i = 0; i < object_pool_capacity_; ++i) {
      free_objects_.emplace_back(creator_fn_());
      ++object_num_;
    }
  }
  
  void ResetObject(T* t) {
    *t = default_object_;
  }
private:
  std::vector<std::unique_ptr<T>> free_objects_;
  std::function<std::unique_ptr<T>()> creator_fn_;
  const int64_t object_pool_capacity_;
  std::atomic<size_t> object_num_;
  T default_object_;
};
