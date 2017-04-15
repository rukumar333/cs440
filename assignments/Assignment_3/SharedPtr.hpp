#include <cassert>
#include <iostream>
#include <mutex>

namespace cs540 {
  std::mutex mutex_;
  /**
   * Node class 
   */
  class Node {
   public:
	int reference_count_;
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

  template <typename T>
  class SharedPtr {
   private:

	T *ptr_;
	Node *control_ptr_;

	void dec() {
	  if (control_ptr_ != nullptr) {
		std::unique_lock<std::mutex> lock(mutex_);
		-- control_ptr_->reference_count_;
		if (control_ptr_->reference_count_ == 0) {
		  delete control_ptr_;
		  control_ptr_ = nullptr;
		  ptr_ = nullptr;
		}
	  }
	}

	void inc() {
	  if (control_ptr_ != nullptr){
		std::unique_lock<std::mutex> lock(mutex_);
		++ control_ptr_->reference_count_;
	  }
	}
   public:
	template <typename U>
	friend class SharedPtr;
	/*
	  Ctors, dtors, assignment
	 */
	template <typename U>
	SharedPtr(T *data, const SharedPtr<U> &sp) : ptr_(data), control_ptr_(sp.control_ptr_) {
	  if (ptr_) {
		inc();
	  } else {
		control_ptr_ = nullptr;
	  }
	}
	SharedPtr() : ptr_(nullptr), control_ptr_(nullptr) { }
	template <typename U>
	explicit SharedPtr(U *data) : ptr_(data), control_ptr_(new NodeDerived<U>(data)) {}
	SharedPtr(const SharedPtr &p) : ptr_(p.ptr_), control_ptr_(p.control_ptr_) {
	  if (ptr_ != nullptr) 
		inc();
	}
	template <typename U>
	SharedPtr(const SharedPtr<U> &p) : ptr_(p.ptr_), control_ptr_(p.control_ptr_) {
	  if (ptr_ != nullptr)
		inc();
	}
	SharedPtr(SharedPtr &&p) : ptr_(p.ptr_), control_ptr_(p.control_ptr_) {
	  p.ptr_ = nullptr;
	  p.control_ptr_ = nullptr;
	}
	template <typename U>
	SharedPtr(SharedPtr<U> &&p) : ptr_(p.ptr_), control_ptr_(p.control_ptr_) {
	  p.ptr_ = nullptr;
	  p.control_ptr_ = nullptr;	  
	}
	SharedPtr &operator=(const SharedPtr &p) {
	  if (*this != p) {
		dec();
		ptr_ = p.ptr_;
		control_ptr_ = p.control_ptr_;
		if (control_ptr_ != nullptr)
		  inc();
	  }
	  return *this;
	}
	template <typename U>	
	SharedPtr &operator=(const SharedPtr<U> &p) {
	  if (*this != p) {
		dec();
		ptr_ = p.ptr_;
		control_ptr_ = p.control_ptr_;
		if (control_ptr_ != nullptr)
		  inc();
	  }
	  return *this;
	}
	SharedPtr &operator=(SharedPtr &&p) {
	  if (*this != p) {
		dec();
		ptr_ = p.ptr_;
		control_ptr_ = p.control_ptr_;
		p.ptr_ = nullptr;
		p.control_ptr_ = nullptr;
	  }
	  return *this;
	}
	template <typename U>	
	SharedPtr &operator=(SharedPtr<U> &&p) {
	  if (*this != p) {
		dec();
		ptr_ = p.ptr_;
		control_ptr_ = p.control_ptr_;
		p.ptr_ = nullptr;
		p.control_ptr_ = nullptr;
	  }
	  return *this;
	}
	~SharedPtr() {
	  dec();
	}
	/*
	  Modifiers
	 */
	void reset() {
	  dec();
	  control_ptr_ = nullptr;
	  ptr_ = nullptr;
	}
	template <typename U>
	void reset(U *p) {
	  dec();
	  control_ptr_ = new NodeDerived<U>(p);
	  ptr_ = p;
	}
	/*
	  Observers
	 */
	T *get() const {
	  return ptr_;
	}
	T &operator*() const {
	  return *ptr_;
	}
	T *operator->() const {
	  return ptr_;
	}
	explicit operator bool() const {
	  return ptr_ != nullptr;
	}
  };
  /*
	Free functions
  */
  template <typename T1, typename T2>
  bool operator==(const SharedPtr<T1> &p1, const SharedPtr<T2> &p2) {
	return p1.get() == p2.get();
  }
  template <typename T>
  bool operator==(const SharedPtr<T> &p1, std::nullptr_t) {
	return !p1;
  }
  template <typename T>
  bool operator==(std::nullptr_t, const SharedPtr<T> &p1) {
	return !p1;
  }
  template <typename T1, typename T2>
  bool operator!=(const SharedPtr<T1> &p1, const SharedPtr<T2> &p2) {
	return p1.get() != p2.get();
  }
  template <typename T>
  bool operator!=(const SharedPtr<T> &p1, std::nullptr_t) {
	return p1;
  }
  template <typename T>
  bool operator!=(std::nullptr_t, const SharedPtr<T> &p1) {
	return p1;
  }
  template <typename T, typename U>
  SharedPtr<T> static_pointer_cast(const SharedPtr<U> &sp) {
	return SharedPtr<T>(static_cast<T *>(sp.get()), sp);
  }
  template <typename T, typename U>
  SharedPtr<T> dynamic_pointer_cast(const SharedPtr<U> &sp) {
	return SharedPtr<T>(dynamic_cast<T *>(sp.get()), sp);
  }
}
