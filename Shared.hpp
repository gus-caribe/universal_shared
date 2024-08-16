#include <cstdlib>

template<typename T>
class Shared {
public:
    // Shared<int> myShared = Shared<int>(123);
    Shared(T instance): counter(new uint32_t(1)) {
        this->instance = (T*)malloc(sizeof(T));
        *this->instance = instance;
    }

    // Shared<int> myShared = 123;
    Shared(T const& instance): counter(new uint32_t(1)) {
        this->instance = (T*)malloc(sizeof(T));
        *this->instance = instance;
    }

    // Shared<int> myShared = Shared<int>(new int(123));
    Shared(new T instance): instance(instance), counter(new uint32_t(1)) {}

    // Shared<int> myShared = new int(123);
    Shared(new T const& instance): instance(instance), counter(new uint32_t(1)) {}

    // Shared<int> myShared1 = 123;
    // ...
    // Shared<int> myShared2 = myShared1;
    Shared(Shared<T> const& other): instance(other.instance), counter(other.counter) {
        *this->counter++;
    }

    // myShared1 = myShared2;
    Shared& operator=(Shared<T> const& other) {
        this->counter--;

        if(!*this->counter) {
            delete this->instance;
            delete this->counter;
        }

        this->instance = other.instance;
        this->counter = other.counter;

        this->counter++;

        return *this;
    }

    // myShared = 123;
    Shared& operator=(T const& other) {
        *this->instance = other;

        return *this;
    }

    // myShared1 == myShared2;
    bool operator==(Shared<T> const& other) {
        return this->instance == other.instance;
    }

    // myShared == 123;
    bool operator==(T const& other) {
        return *this->instance == other;
    }

    // int myCopy = myShared.valCopy();
    T valCopy() {
        return *this->instance;
    }

    // -- goes out of scope --
    ~Shared() {
        this->counter--;

        if(!*this->counter) {
            delete this->instance;
            delete this->counter;
        }
    }

private:
    T* instance = nullptr;
    uint32_t* counter = nullptr;
};
