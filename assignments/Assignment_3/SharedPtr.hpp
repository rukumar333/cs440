#include <cassert>
#include <mutex>

namespace cs540 {

  template <typename T>
  class SharedPtr {
   private:

	class Node {
	 public:
	  int reference_count_;
	  // void inc() {
	  // 	++ reference_count_;
	  // }
	  // void dec() {
	  // 	-- reference_count_;
	  // }
	  // bool is_zero() {
	  // 	return reference_count_ == 0;
	  // }
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
	
	Node *control_ptr_;
    T *ptr_;

	void dec() {
	  if (control_ptr_ != nullptr) {
		-- control_ptr_->reference_count_;
		if (control_ptr_->reference_count_ == 0) {
		  delete control_ptr_;
		  control_ptr_ = nullptr;
		  ptr_ = nullptr;
		}
	  }
	}

	void inc() {
	  if (control_ptr_ != nullptr)
		++ control_ptr_->reference_qcount_;
	}
   public:
	/*
	  Ctors, dtors, assignment
	 */
	SharedPtr() : ptr_{nullptr}, control_ptr_{nullptr} { }
	template <typename U>
	explicit SharedPtr(U *data) : control_ptr_{new NodeDerived<U>(data)}, ptr_{data} {}
	SharedPtr(const SharedPtr &p) : ptr_{p.ptr_}, control_ptr_{p.control_ptr_} {
	  if (ptr_ != nullptr) 
		inc();
	}
	template <typename U>
	SharedPtr(const SharedPtr<U> &p) : ptr_{p.ptr_}, control_ptr_{p.control_ptr_} {
	  if (ptr_ != nullptr)
		inc();
	}
	SharedPtr(const SharedPtr &&p) : ptr_{p.ptr_}, control_ptr_{p.control_ptr_} {
	  p.ptr_ = nullptr;
	  p.control_ptr_ = nullptr;
	}
	template <typename U>
	SharedPtr(const SharedPtr<U> &&p) : ptr_{p.ptr_}, control_ptr_{p.control_ptr_} {
	  p.ptr_ = nullptr;
	  p.control_ptr_ = nullptr;	  
	}
	SharedPtr &operator=(const SharedPtr &p) {
	  if (this != &p) {
		dec();
		ptr_ = p.ptr_;
		control_ptr_ = p.control_ptr_;
		if (control_ptr_ != nullptr)
		  control_ptr_->inc();
	  }
	}
	template <typename U>	
	SharedPtr &operator=(const SharedPtr<U> &p) {
	  if (this != &p) {
		dec();
		ptr_ = p.ptr_;
		control_ptr_ = p.control_ptr_;
		if (control_ptr_ != nullptr)
		  control_ptr_->inc();
	  }
	}
	SharedPtr &operator=(const SharedPtr &&p) {
	  if (this != &p) {
		dec();
		ptr_ = p.ptr_;
		control_ptr_ = p.control_ptr_;
		p.ptr = nullptr;
		p.control_ptr_ = nullptr;
	  }
	}
	template <typename U>	
	SharedPtr &operator=(const SharedPtr<U> &&p) {
	  if (this != &p) {
		dec();
		ptr_ = p.ptr_;
		control_ptr_ = p.control_ptr_;
		p.ptr = nullptr;
		p.control_ptr_ = nullptr;
	  }
	}
	~SharedPtr() {
	  dec();
	}
	/*
	  Modifiers
	 */
	void reset() {
	  
	}
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
