#include <functional>
#include <type_traits>

#ifndef FUNCTION_CS440
#define FUNCTION_CS440

namespace cs540 {
  template <typename> class Function;
  template <typename ResultType, typename... ArgumentTypes>
  class Function<ResultType(ArgumentTypes...)> {
   private:
	class CallBase {
	 public:
	  virtual ResultType operator()(ArgumentTypes... arguments) = 0;
	  virtual ~CallBase() {}
	  virtual explicit operator bool() const = 0;
	  virtual CallBase *clone() = 0;
	};

	template <typename FunctionType>
	class CallDerived {
	 public:
	  CallDerived(FunctionType f) : function_(f) { }
	  CallDerived *clone() {
		return new CallDerived(function_);
	  }
	  ResultType operator()(ArgumentTypes... arguments) {
		return function_(std::forward(arguments)...);
		// return std::invoke(function_, std::forward<ArgumentTypes>(arguments)...);
	  }
	  virtual explicit operator bool() const {
		// return (bool)(struct is_invocable<(FunctionType(ArgumentTypes...)>(function_));
		return true;
	  };
	  FunctionType function_;
	};
	CallBase *call_ref;
   public:
	Function() {
	  call_ref = nullptr;
	}

	template <typename FunctionType>
	Function(FunctionType f) {
	  call_ref = new CallDerived<FunctionType>(f);
	}

	Function(const Function &other) {
	  if (other.call_ref)
		call_ref = other.call_ref->clone();
	  else
		call_ref = nullptr;
	}

	Function &operator=(const Function &other) {
	  if (call_ref != nullptr) {
		delete call_ref;
	  }
	  if (other.call_ref)
		call_ref = other.call_ref->clone();
	  else
		call_ref = nullptr;
	}

	~Function() {
	  if (call_ref != nullptr) {
		delete call_ref;
	  }
	}

	ResultType operator()(ArgumentTypes... arguments) {
	  *(call_ref)(std::forward(arguments...));
	}

	explicit operator bool() const {
	  if (call_ref)
		return *call_ref;
	  else
		return false;
	}
  };
}

#endif
