//
// Created by loghin on 07.03.2021.
//

#ifndef CDS_GENERATOR_HPP
#define CDS_GENERATOR_HPP

#include <CDS/Semaphore>
#include <CDS/Thread>

#include <atomic>

template <typename T, typename ... Args>
class Generator: public Object {
private:
    T                           _promiseObject;
    Semaphore                   _promiseReady;
    Semaphore                   _promiseAchieved;
    UniquePointer < Thread >    _pThread;

    std::atomic<bool>           _taskEnded {false};

    template < int ... > struct seq { };

    template < int N, int ... S >
    struct gens : gens < N - 1, N - 1, S ... > {};

    template < int ... S >
    struct gens < 0, S ... > { typedef seq < S ... > type; };

    class Iterator {
    private:
        Generator mutable * pGen {nullptr};

    public:
        explicit Iterator ( Generator * pGen ) noexcept : pGen(pGen) {}

        auto get () const noexcept (false) -> T {
            if ( pGen == nullptr )
                throw GeneratorTaskEnded ();

            return pGen->ret();
        }

        auto next () noexcept -> Iterator & {
            if ( pGen->_taskEnded )
                pGen = nullptr;
            return * this;
        }

        auto operator ++ () noexcept -> Iterator & { return this->next(); }
        auto operator ++ (int) noexcept -> Iterator { auto copy = * this; this->next(); return copy; }
        auto operator * () const noexcept -> T { return this->get(); }
        auto operator == (Iterator const & o) const noexcept -> bool { return this->pGen == o.pGen; }
        auto operator != (Iterator const & o) const noexcept -> bool { return this->pGen != o.pGen; }
    };

    auto ret () noexcept -> T {
        decltype(this->_promiseObject) copy;

        if ( ! this->_taskEnded ) {
            this->_promiseReady.wait();
            copy = this->_promiseObject;
            this->_promiseAchieved.notify();
        } else {
            copy = this->_promiseObject;
        }

        return copy;
    }

protected:
    auto yield(T const & obj, bool stop = false) noexcept -> void {
        if ( stop )
            this->_taskEnded = true;
        this->_promiseObject = obj;
        this->_promiseReady.notify();
        this->_promiseAchieved.wait();
    }

    virtual auto task (Args ... ) noexcept -> T = 0;

public:
    class GeneratorTaskEnded : public std::exception {
        [[nodiscard]] auto what() const noexcept -> StringLiteral override {
            return "Task has Ended, attempted to acquire out of range data";
        }
    };

    class IterableObject {
    private:
        Generator * pGen {nullptr};

    public:
        explicit IterableObject(Generator * pGen) noexcept : pGen(pGen) {

        }

        operator T () const noexcept {
            return this->pGen->ret();
        }

        auto begin () noexcept -> Generator::Iterator { return Generator::Iterator(this->pGen); }
        auto end () noexcept -> Generator::Iterator { return Generator::Iterator(nullptr); }
    };

    auto restart (Args && ... args) noexcept -> IterableObject {
        if ( ! this->_pThread.isNull() ) {
            this->_pThread->kill();
            this->_promiseAchieved.reset();
            this->_promiseReady.reset();
            this->_taskEnded = false;
        }

        this->_pThread.reset(
            new Runnable (
                [ args = std::make_tuple(std::forward<Args>(args) ... ), this ] () mutable {
                    return std::apply([this](Args && ... args){
                        this->yield(this->task( std::forward<Args>(args) ... ), true);
                    }, std::move(args));
                }
            )
        );

        this->_pThread->start();

        return IterableObject(this);
    }

    auto operator () (Args && ... args ) noexcept (false) -> IterableObject {
        if ( this->_taskEnded == true )
            throw GeneratorTaskEnded();

        if ( this->_pThread.isNull() )
            this->restart ( std::forward < Args > ( args ) ... );

        return IterableObject(this);
    }

    ~Generator() noexcept override {
        this->_pThread->kill();
    }

    auto toString() const noexcept -> String override {
        return String()
            .append("Generator{isRunning=")
            .append(!(bool)this->_taskEnded)
            .append(",thread=")
            .append(this->_pThread->toString())
            .append(",promiseReadySem=")
            .append(this->_promiseReady.toString())
            .append(",promiseAchievedSem=")
            .append(this->_promiseAchieved.toString())
            .append("}");
    }
};

#endif //CDS_GENERATOR_HPP
