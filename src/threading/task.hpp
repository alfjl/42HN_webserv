#ifndef WEBSERV_THREADING_TASK_HPP
#define WEBSERV_THREADING_TASK_HPP

namespace webserv {
    namespace threading {

    class runnable {
    public:
        runnable() {}
        virtual ~runnable() {}
        virtual void run() = 0;
    };

    template<typename T>
    class task : public runnable {
    public:
        typedef T  arg_type;

    private:
        T  value;
    
    protected:
        T& get() { return value; }
        T& get() const { return value; }
        bool was_interrupted() { return false; }

    public:
        task(T _value) : value(_value) {}
        virtual ~task() {}
        virtual void run() = 0;

        void interrupt() { /* TODO */ }
    };

    }
}

#endif
