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

    class basic_task : public runnable {
    protected:
        bool was_interrupted() { /* TODO */ return false; }
    
    public:
        basic_task() {}
        virtual ~basic_task() {}
        void interrupt() { /* TODO */ }
    };

    template<typename T>
    class task : public basic_task {
    public:
        typedef T  arg_type;

    private:
        T  value;
    
    protected:
        T& get() { return value; }
        T& get() const { return value; }

    public:
        task(T _value) : value(_value) {}
        virtual ~task() {}
    };

    }
}

#endif
