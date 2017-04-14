#include <cassert>
#include <mutex>

namespace cs540 {

  template <typename T>
  class SharedPtr {
   private:

	class Node {
	 public:
	  int reference_count_;
	  void inc() {
		++ reference_count_;
	  }
	  void dec() {
		-- reference_count_;
	  }
	  bool is_zero() {
		return reference_count_ == 0;
	  }
	  virtual ~Node() {}
	};

	template <typename U>
	class NodeDerived : public Node {
	 public:
	  U *data_;
	  using Node::reference_count_;
	  NodeDerived(U *input_) {
		reference_count_ = 1;
		data_ = input_;
	  }
	  NodeDerived() {
		data_ = nullptr;
		reference_count_ = 0;
	  }
	  ~NodeDerived() {
		delete data_;
		data_ = nullptr;
	  }
	};
	Node *ptr_;

   public:
	/*
	  Ctors, dtors, assignment
	 */
	SharedPtr() {
	  ptr_ = nullptr;
	}
	template <typename U>
	explicit SharedPtr(U *data) {
	  ptr_ = new NodeDerived<U>(data);
	}
	SharedPtr(const SharedPtr &p);
	template <typename U>
	SharedPtr(const SharedPtr<U> &p);
	SharedPtr(const SharedPtr &&p);
	template <typename U>
	SharedPtr(const SharedPtr<U> &&p);
	SharedPtr &operator=(const SharedPtr &p);
	template <typename U>	
	SharedPtr &operator=(const SharedPtr<U> &p);
	~SharedPtr() {
	  if (ptr_ != nullptr) {
		assert(!ptr_->is_zero());
		ptr_->dec();
		if (ptr_->is_zero()) {
		  delete ptr_;
		}
	  }
	}
	/*
	  Modifiers
	 */
	void reset();
	template <typename U>
	void reset(U *p);
	/*
	  Observers
	 */
	T *get() const;
	T &operator*() const;
	T *operator->() const;
	explicit operator bool() const;
	/*
	  Free functions
	 */
	
  };
  
}
