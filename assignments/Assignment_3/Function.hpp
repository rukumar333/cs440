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
	};

	template <typename FunctionType>
	class CallDerived {
	 public:
	  CallDerived(FunctionType f) : function_(f) { }
	  ResultType operator()(ArgumentTypes... arguments) {
		return function_(std::forward(arguments)...);
		// return function_(arguments);
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
	  
	}

	Function &operator=(const Function &other) {
	  if (call_ref != nullptr) {
		delete call_ref;
	  }
	  
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
	  return *call_ref;
	}
  };
}

#endif
