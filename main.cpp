#include <iostream>
#include <concepts>
#include <string>

template<typename T>
concept HasHashCalculationConvertibleToLong = requires(T v) {
    { v.hash() } -> std::convertible_to<long>;
};

template<typename T>
concept HasToStringMethod = requires(T v) {
    { v.toString() } -> std::same_as<std::string>;
};

template<typename T>
concept ComplexConcept = HasHashCalculationConvertibleToLong<T> && HasToStringMethod<T> && !std::has_virtual_destructor<T>::value;

void printHash(ComplexConcept auto& t) {
    std::cout << "Hash(\"" << t.toString() << "\") = " << t.hash() << std::endl;
}

class TestClassSuitable {
public:
    TestClassSuitable(const std::string& value) : _data(value) {}

    size_t hash() const {
        return std::hash<std::string>{}(_data);
    }

    std::string toString() const {
        return _data;
    }

private:
    std::string _data;
};

class TestClassUnSuitable {
public:
    TestClassUnSuitable(const std::string& value) {}

    virtual ~TestClassUnSuitable() {}

    std::string hash() const {
        return std::string();
    }

    int toString() const {
        return 1;
    }
};

int main() {
    TestClassSuitable correct("Test");
    printHash(correct);
    return 0;
}